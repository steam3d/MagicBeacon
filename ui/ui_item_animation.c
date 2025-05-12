#include "ui_item_animation.h"
#include "ui_shared.h"
#include "magic_beacon.h"

static void magic_beacon_ui_item_animation_callback(VariableItem* item) {
    uint8_t index = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, animation_states[index]);

    MagicBeaconApp* app = (MagicBeaconApp*)variable_item_get_context(item);

    if(app->template == TEMPLATE_AIRPODS_MAX || app->template == TEMPLATE_AIRPODS_MAX_2024) {
        //max
        if(index == 1) {
            app->le_data.payload[8] = 0x84; // case opened
            ble_update_payload(&app->le_data);
        } else {
            app->le_data.payload[8] = 0x04; // case closed
            ble_update_payload(&app->le_data);
        }
    } else {
        if(index == 1) {
            app->le_data.payload[8] = 0x11; // case opened
            ble_update_payload(&app->le_data);
        } else {
            app->le_data.payload[8] = 0x19; // case closed
            ble_update_payload(&app->le_data);
        }
    }
}

void magic_beacon_ui_item_animation(void* context) {
    MagicBeaconApp* app = (MagicBeaconApp*)context;
    VariableItem* item = variable_item_list_add(
        app->list, "Animation", 2, magic_beacon_ui_item_animation_callback, context);

    if(app->template == TEMPLATE_AIRPODS_MAX || app->template == TEMPLATE_AIRPODS_MAX_2024) {
        if(app->le_data.payload[8] == 0x84) {
            variable_item_set_current_value_index(item, 1);
            variable_item_set_current_value_text(item, animation_states[1]);
        } else if(app->le_data.payload[8] == 0x04) {
            variable_item_set_current_value_index(item, 0);
            variable_item_set_current_value_text(item, animation_states[0]);
        }
    } else {
        if(app->le_data.payload[8] == 0x11) {
            variable_item_set_current_value_index(item, 1);
            variable_item_set_current_value_text(item, animation_states[1]);
        } else if(app->le_data.payload[8] == 0x19) {
            variable_item_set_current_value_index(item, 0);
            variable_item_set_current_value_text(item, animation_states[0]);
        }
    }
}
