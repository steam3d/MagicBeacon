#include "ui_item_live_payload.h"
#include "ui_shared.h"
#include "magic_beacon.h"

static void magic_beacon_ui_item_live_payload_callback(VariableItem* item) {
    uint8_t index = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, le_states[index]);
    MagicBeaconApp* app = (MagicBeaconApp*)variable_item_get_context(item);
    app->live_payload = index == 1;
}

void magic_beacon_ui_item_live_payload(void* context) {
    MagicBeaconApp* app = (MagicBeaconApp*)context;
    VariableItem* item = variable_item_list_add(
        app->list, "Live payload", 2, magic_beacon_ui_item_live_payload_callback, context);

    uint8_t value = app->live_payload ? 1 : 0;
    magic_beacon_ui_shared_charge_text(item, value);
}
