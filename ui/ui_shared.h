#pragma once
#include <gui/modules/variable_item_list.h>

extern const char* type_states[];
extern const char* animation_states[];
extern const char* le_states[];
extern const char* battery_states[];

void magic_beacon_ui_shared_battery_text(VariableItem* item, uint8_t value);
void magic_beacon_ui_shared_charge_text(VariableItem* item, uint8_t value);
