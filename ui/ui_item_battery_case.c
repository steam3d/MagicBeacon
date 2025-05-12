#include "ui_item_battery_case.h"
#include "ui_shared.h"
#include "magic_beacon.h"

static void magic_beacon_ui_item_case_battery_callback_callback(VariableItem* item) {
    uint8_t index = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, battery_states[index]);

    MagicBeaconApp* app = (MagicBeaconApp*)variable_item_get_context(item);
    if(index == 11) {
        app->le_data.payload[7] = (app->le_data.payload[7] & 0xF0) | 15;
        ble_update_payload(&app->le_data);
    } else {
        app->le_data.payload[7] = (app->le_data.payload[7] & 0xF0) | index;
        ble_update_payload(&app->le_data);
    }
}

void magic_beacon_ui_item_battery_case(void* context) {
    MagicBeaconApp* app = (MagicBeaconApp*)context;
    VariableItem* item = variable_item_list_add(
        app->list, "Case", 12, magic_beacon_ui_item_case_battery_callback_callback, context);

    uint8_t value = app->le_data.payload[7] & 0x0F;
    magic_beacon_ui_shared_battery_text(item, value);
}
