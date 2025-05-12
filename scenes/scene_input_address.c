#include <furi.h>
#include "scene_input_address.h"
#include "magic_beacon.h"
#define TAG "magic_beacon"

static uint8_t temp_address[6];

void byte_input_address_callback(void* context) {
    FURI_LOG_T(TAG, "byte_input_address_callback");
    MagicBeaconApp* app = (MagicBeaconApp*)context;

    memcpy(app->le_data.address, temp_address, sizeof(app->le_data.address));

    scene_manager_previous_scene(app->scene_manager);
}

void magic_beacon_scene_input_address_on_enter(void* context) {
    FURI_LOG_T(TAG, "magic_beacon_scene_input_address_on_enter");
    MagicBeaconApp* app = context;

    memcpy(temp_address, app->le_data.address, sizeof(temp_address));

    byte_input_set_header_text(app->byte_input, "Enter address (restart adv):");
    byte_input_set_result_callback(
        app->byte_input,
        byte_input_address_callback,
        NULL,
        context,
        temp_address,
        sizeof(temp_address));
    view_dispatcher_switch_to_view(app->view_dispatcher, APP_VIEW_BYTE_INPUT);
}

bool magic_beacon_scene_input_address_on_event(void* context, SceneManagerEvent event) {
    FURI_LOG_T(TAG, "magic_beacon_scene_input_address_on_event");
    UNUSED(context);
    UNUSED(event);
    return false;
}

void magic_beacon_scene_input_address_on_exit(void* context) {
    FURI_LOG_T(TAG, "magic_beacon_scene_input_address_on_exit");
    UNUSED(context);
}
