#include "ui_item_payload_switch.h"
#include "magic_beacon.h"

static void magic_beacon_ui_item_payload_switch_callback(VariableItem* item) {
    uint8_t index = variable_item_get_current_value_index(item);

    MagicBeaconApp* app = (MagicBeaconApp*)variable_item_get_context(item);

    char payload_str[16];
    app->payloads_selected = index;
    snprintf(payload_str, sizeof(payload_str), "%zu", index + 1);
    variable_item_set_current_value_text(item, payload_str);

    memcpy(app->le_data.payload, app->payloads[index].data, app->payloads[index].length);
    ble_update_payload(&app->le_data);
}

void magic_beacon_ui_item_payload_switch(void* context) {
    MagicBeaconApp* app = (MagicBeaconApp*)context;
    VariableItem* item = variable_item_list_add(
        app->list,
        "Choose payload",
        app->payloads_length,
        magic_beacon_ui_item_payload_switch_callback,
        context);

    char payload_str[16];
    snprintf(payload_str, sizeof(payload_str), "%lu", app->payloads_selected + 1);

    variable_item_set_current_value_index(item, app->payloads_selected);
    variable_item_set_current_value_text(item, payload_str);
}
