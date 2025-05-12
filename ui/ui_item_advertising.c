#include "ui_item_advertising.h"
#include <furi_hal.h>
#define TAG "magic_beacon"

static const char* le_states[] = {"Off", "On"};

static void magic_beacon_ui_item_advertising_callback(VariableItem* item) {
    uint8_t index = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, le_states[index]);

    if(index == 1) {
        MagicBeaconApp* app = (MagicBeaconApp*)variable_item_get_context(item);
        ble_start_advertising(&app->le_data);
    } else {
        ble_stop_advertising();
    }
}

void magic_beacon_ui_item_advertising(void* context) {
    MagicBeaconApp* app = (MagicBeaconApp*)context;
    VariableItem* item = variable_item_list_add(
        app->list, "Advertising", 2, magic_beacon_ui_item_advertising_callback, context);

    if(furi_hal_bt_extra_beacon_is_active()) {
        variable_item_set_current_value_index(item, 1);
        variable_item_set_current_value_text(item, le_states[1]);
    } else {
        variable_item_set_current_value_index(item, 0);
        variable_item_set_current_value_text(item, le_states[0]);
    }
}
