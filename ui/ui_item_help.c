#include "ui_item_help.h"
#include "magic_beacon.h"

void magic_beacon_ui_item_help(void* context) {
    MagicBeaconApp* app = (MagicBeaconApp*)context;
    variable_item_list_add(app->list, "Help", 1, NULL, context);
}