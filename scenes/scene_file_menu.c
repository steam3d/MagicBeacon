#include <furi.h>
#include "scene_file_menu.h"
#include "ui/ui_item_advertising.h"
#include "ui/ui_item_address.h"
#include "ui/ui_item_payload.h"
#include "ui/ui_item_payload_switch.h"
#include "ui/ui_item_live_payload.h"
#include "ui/ui_item_help.h"
#include "../magic_beacon.h"
#define TAG "magic_beacon"

static void magic_beacon_scene_cloning_list_enter_callback(void* context, uint32_t index) {
    FURI_LOG_T(TAG, "magic_beacon_scene_cloning_list_enter_callback %ld", index);
    MagicBeaconApp* app = (MagicBeaconApp*)context;
    if(index == 5) {
        scene_manager_next_scene(app->scene_manager, APP_SCENE_ADDRESS);
    } else if(index == 4) {
        app->message = HELP_MESSAGE_PAYLOAD;
        scene_manager_next_scene(app->scene_manager, APP_SCENE_HELP);
    } else if(index == 1) {
        scene_manager_next_scene(app->scene_manager, APP_SCENE_INPUT_PAYLOAD);
    }
}

void magic_beacon_scene_file_menu_on_enter(void* context) {
    FURI_LOG_T(TAG, "magic_beacon_scene_file_menu_on_enter");
    MagicBeaconApp* app = (MagicBeaconApp*)context;
    variable_item_list_reset(app->list);
    variable_item_list_set_enter_callback(
        app->list, magic_beacon_scene_cloning_list_enter_callback, app);

    magic_beacon_ui_item_advertising(context);
    magic_beacon_ui_item_payload(context);
    magic_beacon_ui_item_payload_switch(context);
    magic_beacon_ui_item_live_payload(context);
    magic_beacon_ui_item_help(context);
    magic_beacon_ui_item_address(context);

    view_dispatcher_switch_to_view(app->view_dispatcher, APP_VIEW_LIST);
}

bool magic_beacon_scene_file_menu_on_event(void* context, SceneManagerEvent event) {
    FURI_LOG_T(TAG, "magic_beacon_scene_file_menu_on_event");
    MagicBeaconApp* app = (MagicBeaconApp*)context;
    if(event.type == SceneManagerEventTypeBack) {
        FURI_LOG_T(TAG, "SceneManagerEventTypeBack");
        ble_stop_advertising();
        variable_item_list_set_selected_item(app->list, 0);
    }
    return false;
}

void magic_beacon_scene_file_menu_on_exit(void* context) {
    FURI_LOG_T(TAG, "magic_beacon_scene_file_menu_on_exit");
    MagicBeaconApp* app = (MagicBeaconApp*)context;
    variable_item_list_reset(app->list);
}
