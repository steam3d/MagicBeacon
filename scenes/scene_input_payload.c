#include <furi.h>
#include "scene_input_payload.h"
#include "magic_beacon.h"
#define TAG "magic_beacon"

static uint8_t* temp_payload = NULL;
static size_t temp_payload_length = 0;

static void free_temp_payload() {
    if(temp_payload) {
        free(temp_payload);
        temp_payload = NULL;
        temp_payload_length = 0;
    }
}

static void byte_input_payload_callback(void* context) {
    FURI_LOG_T(TAG, "byte_input_payload_callback");
    MagicBeaconApp* app = (MagicBeaconApp*)context;

    memcpy(app->le_data.payload, temp_payload, temp_payload_length);
    free_temp_payload();

    ble_update_payload(&app->le_data);
    scene_manager_previous_scene(app->scene_manager);
}

static void byte_input_payload_changed_callback(void* context) {
    FURI_LOG_T(TAG, "byte_input_payload_changed_callback");
    MagicBeaconApp* app = (MagicBeaconApp*)context;
    if(app->live_payload) {
        memcpy(app->le_data.payload, temp_payload, temp_payload_length);
        ble_update_payload(&app->le_data);
    }
}

void magic_beacon_scene_input_payload_on_enter(void* context) {
    FURI_LOG_T(TAG, "magic_beacon_scene_input_payload_on_enter");
    MagicBeaconApp* app = (MagicBeaconApp*)context;

    free_temp_payload();
    temp_payload_length = app->le_data.payload_length;
    temp_payload = malloc(temp_payload_length);
    furi_check(temp_payload);

    memcpy(temp_payload, app->le_data.payload, temp_payload_length);

    byte_input_set_header_text(app->byte_input, "Enter payload:");
    byte_input_set_result_callback(
        app->byte_input,
        byte_input_payload_callback,
        byte_input_payload_changed_callback,
        context,
        temp_payload,
        temp_payload_length);
    view_dispatcher_switch_to_view(app->view_dispatcher, APP_VIEW_BYTE_INPUT);
}

bool magic_beacon_scene_input_payload_on_event(void* context, SceneManagerEvent event) {
    FURI_LOG_T(TAG, "magic_beacon_scene_input_payload_on_event");
    UNUSED(context);
    UNUSED(event);
    return false;
}

void magic_beacon_scene_input_payload_on_exit(void* context) {
    FURI_LOG_T(TAG, "magic_beacon_scene_input_payload_on_exit");
    UNUSED(context);
    free_temp_payload();
}
