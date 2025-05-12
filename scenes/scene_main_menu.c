#include <string.h>
#include <furi.h>
#include "scene_main_menu.h"
#include "../magic_beacon.h"
#define TAG "magic_beacon"

static void magic_beacon_scene_main_menu_init(LeData* data) {
    uint8_t mac_init[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    memcpy(data->address, mac_init, sizeof(mac_init));
    uint8_t payload_init[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    data->payload_length = sizeof(payload_init);
    memcpy(data->payload, payload_init, data->payload_length);
}

static void my_item_list_enter_callback(void* context, uint32_t index) {
    FURI_LOG_T(TAG, "my_item_list_enter_callback %ld", index);
    MagicBeaconApp* app = (MagicBeaconApp*)context;

    if(index == 0) {
        scene_manager_next_scene(app->scene_manager, APP_SCENE_TEMPLATE);
    } else if(index == 1) {
        scene_manager_next_scene(app->scene_manager, APP_SCENE_FILE);
    } else {
        app->message = HELP_MESSAGE_ABOUT;
        scene_manager_next_scene(app->scene_manager, APP_SCENE_HELP);
    }
}

void magic_beacon_scene_main_menu_on_enter(void* context) {
    FURI_LOG_T(TAG, "magic_beacon_scene_main_menu_on_enter");
    MagicBeaconApp* app = (MagicBeaconApp*)context;

    ble_stop_advertising();
    magic_beacon_scene_main_menu_init(&app->le_data);
    app->data_init = false;
    app->live_payload = false;

    submenu_reset(app->submenu);
    submenu_set_header(app->submenu, "MagicBeacon");
    submenu_add_item(
        app->submenu, "Payload from template", 0, my_item_list_enter_callback, context);
    submenu_add_item(app->submenu, "Payload from file", 1, my_item_list_enter_callback, context);
    submenu_add_item(app->submenu, "Help", 2, my_item_list_enter_callback, context);

    view_dispatcher_switch_to_view(app->view_dispatcher, APP_VIEW_SUBMENU);
}

bool magic_beacon_scene_main_menu_on_event(void* context, SceneManagerEvent event) {
    FURI_LOG_T(TAG, "magic_beacon_scene_main_menu_on_event");
    UNUSED(context);
    UNUSED(event);
    return false;
}

void magic_beacon_scene_main_menu_on_exit(void* context) {
    FURI_LOG_T(TAG, "magic_beacon_scene_main_menu_on_exit");
    MagicBeaconApp* app = (MagicBeaconApp*)context;
    submenu_reset(app->submenu);
}
