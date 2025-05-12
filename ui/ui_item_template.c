#include "ui_item_template.h"
#include "ui_shared.h"
#include "magic_beacon.h"
#include "../scenes/scene_template_menu.h"

static void magic_beacon_ui_item_template_le_callback(VariableItem* item) {
    uint8_t index = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, type_states[index]);

    MagicBeaconApp* app = (MagicBeaconApp*)variable_item_get_context(item);
    magic_beacon_template_payload_init(&app->le_data, &app->template, template_order[index]);
    ble_update_payload(&app->le_data);
    scene_manager_search_and_switch_to_another_scene(app->scene_manager, APP_SCENE_TEMPLATE);
}

void magic_beacon_ui_item_template(void* context) {
    MagicBeaconApp* app = (MagicBeaconApp*)context;
    VariableItem* item = variable_item_list_add(
        app->list, "Template", 14, magic_beacon_ui_item_template_le_callback, context);

    for(size_t i = 0; i < sizeof(template_order) / sizeof(template_order[0]); i++) {
        if(template_order[i] == app->template) {
            variable_item_set_current_value_index(item, i);
            variable_item_set_current_value_text(item, type_states[i]);
            break;
        }
    }
}
