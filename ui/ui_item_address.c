#include "ui_item_address.h"
#include "magic_beacon.h"

void magic_beacon_ui_item_address(void* context) {
    MagicBeaconApp* app = (MagicBeaconApp*)context;
    variable_item_list_add(app->list, "Edit address*", 1, NULL, context);
}