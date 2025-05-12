#include "ui_shared.h"

const char* type_states[] = {
    "Air2",
    "Air3",
    "Air4",
    "Air4ANC",
    "AirPro",
    "AirProC",
    "AirPro2",
    "AirMax",
    "AirMaxC",
    "PBPro",
    "PBPro2",
    "BFitPro",
    "BStudB",
    "BStudB+",
};
const char* animation_states[] = {"Hide", "Show"};
const char* le_states[] = {"Off", "On"};
const char* battery_states[] =
    {"0%", "10%", "20%", "30%", "40%", "50%", "60%", "70%", "80%", "90%", "100%", "NaN"};

void magic_beacon_ui_shared_battery_text(VariableItem* item, uint8_t value) {
    if(value == 0x0f) {
        variable_item_set_current_value_index(item, 11);
        variable_item_set_current_value_text(item, battery_states[11]);
    } else if(value <= 0x0a) {
        variable_item_set_current_value_index(item, value);
        variable_item_set_current_value_text(item, battery_states[value]);
    }
}

void magic_beacon_ui_shared_charge_text(VariableItem* item, uint8_t value) {
    variable_item_set_current_value_index(item, value);
    variable_item_set_current_value_text(item, le_states[value]);
}
