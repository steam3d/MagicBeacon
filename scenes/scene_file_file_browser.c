#include <furi.h>
#include <storage/storage.h>
#include <magic_beacon_icons.h>
#include "scene_file_file_browser.h"
#include "../magic_beacon.h"
#include "../utils.h"
#define TAG "magic_beacon"

static bool parse_mac_address(const char* mac_str, uint8_t mac[6]) {
    unsigned int tmp[6];
    int parsed = sscanf(
        mac_str,
        "%x:%x:%x:%x:%x:%x", // Используем %x вместо %hhx
        &tmp[0],
        &tmp[1],
        &tmp[2],
        &tmp[3],
        &tmp[4],
        &tmp[5]);
    if(parsed != 6) return false;
    for(int i = 0; i < 6; i++) {
        mac[i] = (uint8_t)tmp[i]; // Явное приведение к uint8_t
    }
    return true;
}

static bool parse_payload(PayloadArray** array, size_t* array_length, const FuriString* line) {
    if(furi_string_size(line) > MAX_LINE_LEN) {
        FURI_LOG_E(TAG, "Length size larger than 54");
        return false;
    }

    uint8_t* temp = NULL;
    size_t temp_length = 0;

    if(hex_string_to_bytes(furi_string_get_cstr(line), &temp, &temp_length) != 0) {
        FURI_LOG_E(TAG, "Unable parse hex string");
        return false;
    }

    PayloadArray* new_payloads = realloc(*array, (*array_length + 1) * sizeof(PayloadArray));

    if(!new_payloads) {
        free(temp);
        FURI_LOG_E(TAG, "Out of memory");
        return false;
    }

    *array = new_payloads;
    (*array)[*array_length].data = temp;
    (*array)[*array_length].length = temp_length;
    (*array_length)++;
    return true;
}

bool read_long_lines(void* context, const FuriString* path) {
    MagicBeaconApp* app = (MagicBeaconApp*)context;
    Storage* storage = furi_record_open(RECORD_STORAGE);
    File* file = storage_file_alloc(storage);
    storage_file_open(file, furi_string_get_cstr(path), FSAM_READ, FSOM_OPEN_EXISTING);

    const size_t read_chunk = 64;
    uint8_t buffer[read_chunk];
    FuriString* line = furi_string_alloc();

    bool is_first_line = true;

    while(!storage_file_eof(file)) {
        size_t read = storage_file_read(file, buffer, read_chunk);
        for(size_t i = 0; i < read; i++) {
            char c = buffer[i];
            furi_string_push_back(line, c);

            if(c == '\n') {
                furi_string_trim(line, " \n\r\t");
                if(furi_string_size(line) == 0) continue;

                FURI_LOG_T(TAG, "%s", furi_string_get_cstr(line));

                if(is_first_line) { //Firt line is mac
                    is_first_line = false;
                    parse_mac_address(furi_string_get_cstr(line), app->le_data.address);
                } else {
                    parse_payload(&app->payloads, &app->payloads_length, line);
                }
                furi_string_set(line, "");
            }
        }
    }

    if(furi_string_size(line) > 0) {
        parse_payload(&app->payloads, &app->payloads_length, line);
        furi_string_set(line, "");
    }

    furi_string_free(line);
    storage_file_close(file);
    storage_file_free(file);
    furi_record_close(RECORD_STORAGE);

    return app->payloads_length != 0;
}

static void free_payloads(void* context) {
    MagicBeaconApp* app = (MagicBeaconApp*)context;

    for(size_t i = 0; i < app->payloads_length; ++i) {
        if(app->payloads[i].data) {
            free(app->payloads[i].data);
            app->payloads[i].data = NULL;
            app->payloads[i].length = 0;
        }
    }

    if(app->payloads) {
        free(app->payloads);
        app->payloads = NULL;
        app->payloads_length = 0;
    };
}

static void file_browser_done_callback(void* context) {
    MagicBeaconApp* app = (MagicBeaconApp*)context;
    file_browser_stop(app->file_browser);

    if(furi_string_size(app->file_path) > 0) {
        if(read_long_lines(context, app->file_path)) {
            memcpy(app->le_data.payload, app->payloads[0].data, app->payloads[0].length);
            app->payloads_selected = 0;
            app->data_init = true;
            scene_manager_next_scene(app->scene_manager, APP_SCENE_FILE_MENU);
            return;
        }
    }
    scene_manager_previous_scene(app->scene_manager);
}

void magic_beacon_scene_file_file_browser_on_enter(void* context) {
    FURI_LOG_T(TAG, "magic_beacon_scene_file_file_browser_on_enter");
    MagicBeaconApp* app = (MagicBeaconApp*)context;
    free_payloads(app);
    app->payloads_selected = 0;
    app->data_init = false;

    file_browser_configure(app->file_browser, ".txt", "/", true, true, &I_txt_10x10, false);

    file_browser_set_callback(app->file_browser, file_browser_done_callback, context);
    view_dispatcher_switch_to_view(app->view_dispatcher, APP_VIEW_FILE_BROWSER);
    file_browser_start(app->file_browser, app->file_path);
}

bool magic_beacon_scene_file_file_browser_on_event(void* context, SceneManagerEvent event) {
    FURI_LOG_T(TAG, "magic_beacon_scene_file_file_browser_on_event");
    if(event.type == SceneManagerEventTypeBack) {
        MagicBeaconApp* app = (MagicBeaconApp*)context;
        free_payloads(app);
        app->data_init = false;
    }
    return false;
}

void magic_beacon_scene_file_file_browser_on_exit(void* context) {
    FURI_LOG_T(TAG, "magic_beacon_scene_file_file_browser_on_exit");
    MagicBeaconApp* app = (MagicBeaconApp*)context;
    variable_item_list_reset(app->list);
}
