#include "ui_item_payload.h"
#include "magic_beacon.h"

void magic_beacon_ui_item_payload(void* context) {
    MagicBeaconApp* app = (MagicBeaconApp*)context;
    variable_item_list_add(app->list, "Edit payload", 1, NULL, context);
}