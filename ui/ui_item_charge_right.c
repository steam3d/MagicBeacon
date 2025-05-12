#include "ui_item_charge_right.h"
#include "ui_shared.h"
#include "magic_beacon.h"

static void magic_beacon_ui_item_charge_right_callback(VariableItem* item) {
    uint8_t index = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, le_states[index]);

    MagicBeaconApp* app = (MagicBeaconApp*)variable_item_get_context(item);
    if(index == 1) {
        app->le_data.payload[7] = app->le_data.payload[7] | 0b00010000;
        ble_update_payload(&app->le_data);
    } else {
        app->le_data.payload[7] = app->le_data.payload[7] & 0b11101111;
        ble_update_payload(&app->le_data);
    }
}

void magic_beacon_ui_item_charge_right(void* context) {
    MagicBeaconApp* app = (MagicBeaconApp*)context;
    VariableItem* item = variable_item_list_add(
        app->list, "Right charge", 2, magic_beacon_ui_item_charge_right_callback, context);

    uint8_t value = (app->le_data.payload[7] & 0b00010000) ? 1 : 0; //0x0001_0000
    magic_beacon_ui_shared_charge_text(item, value);
}
