#include <string.h>
#include <furi.h>
#include "ui/ui_item_advertising.h"
#include "ui/ui_item_animation.h"
#include "ui/ui_item_battery_left.h"
#include "ui/ui_item_battery_right.h"
#include "ui/ui_item_battery_case.h"
#include "ui/ui_item_charge_left.h"
#include "ui/ui_item_charge_right.h"
#include "ui/ui_item_charge_case.h"
#include "ui/ui_item_address.h"
#include "ui/ui_item_payload.h"
#include "ui/ui_item_template.h"
#include "ui/ui_item_live_payload.h"
#include "ui/ui_item_help.h"
#include "../magic_beacon.h"
#define TAG "magic_beacon"

const Template template_order[14] = {
    TEMPLATE_AIRPODS_2,
    TEMPLATE_AIRPODS_3,
    TEMPLATE_AIRPODS_4,
    TEMPLATE_AIRPODS_4_ANC,
    TEMPLATE_AIRPODS_PRO,
    TEMPLATE_AIRPODS_PRO_C,
    TEMPLATE_AIRPODS_PRO_2,
    TEMPLATE_AIRPODS_MAX,
    TEMPLATE_AIRPODS_MAX_2024,
    TEMPLATE_POWER_BEATS_PRO,
    TEMPLATE_POWER_BEATS_PRO_2,
    TEMPLATE_BEATS_FITS_PRO,
    TEMPLATE_BEATS_STUDIO_BUDS,
    TEMPLATE_BEATS_STUDIO_BUDS_PLUS};

static void magic_beacon_template_address_init(LeData* data) {
    uint8_t mac_init[] = {0x0a, 0xe1, 0x61, 0x02, 0xa1, 0xf8};
    memcpy(data->address, mac_init, sizeof(mac_init));
}

void magic_beacon_template_payload_init(LeData* data, Template* type, Template new_type) {
    *type = new_type;

    if(*type == TEMPLATE_AIRPODS_MAX || *type == TEMPLATE_AIRPODS_MAX_2024) {
        uint8_t payload_init[] = {0x07, 0x19, 0x01, 0x0A, 0x20, 0x02, 0x03, 0x80, 0x84,
                                  0x0F, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        data->payload_length = sizeof(payload_init);
        memcpy(data->payload, payload_init, data->payload_length);
    } else {
        uint8_t payload_init[] = {0x07, 0x19, 0x01, 0x1B, 0x20, 0x55, 0xAA, 0xB8, 0x11,
                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        data->payload_length = sizeof(payload_init);
        memcpy(data->payload, payload_init, data->payload_length);
    }

    unsigned char high_byte = (*type >> 8) & 0xFF; //0x20
    unsigned char low_byte = *type & 0xFF; //0x1f
    data->payload[3] = low_byte;
    data->payload[4] = high_byte;
}

static void my_item_list_enter_callback(void* context, uint32_t index) {
    FURI_LOG_T(TAG, "my_item_list_enter_callback %ld", index);
    MagicBeaconApp* app = context;
    if(index == 10) {
        app->message = HELP_MESSAGE_PAYLOAD;
        scene_manager_next_scene(app->scene_manager, APP_SCENE_HELP);
    } else if(index == 11) {
        scene_manager_next_scene(app->scene_manager, APP_SCENE_ADDRESS);
    } else if(index == 12) {
        scene_manager_next_scene(app->scene_manager, APP_SCENE_INPUT_PAYLOAD);
    }
}

void magic_beacon_scene_template_menu_on_enter(void* context) {
    FURI_LOG_T(TAG, "magic_beacon_scene_template_menu_on_enter");
    MagicBeaconApp* app = (MagicBeaconApp*)context;

    if(!app->data_init) {
        magic_beacon_template_address_init(&app->le_data);
        magic_beacon_template_payload_init(&app->le_data, &app->template, TEMPLATE_AIRPODS_2);
        app->data_init = true;
    }

    variable_item_list_reset(app->list);
    variable_item_list_set_enter_callback(app->list, my_item_list_enter_callback, app);

    magic_beacon_ui_item_advertising(context);
    magic_beacon_ui_item_animation(context);
    magic_beacon_ui_item_battery_left(context);
    magic_beacon_ui_item_battery_right(context);
    magic_beacon_ui_item_battery_case(context);
    magic_beacon_ui_item_charge_left(context);
    magic_beacon_ui_item_charge_right(context);
    magic_beacon_ui_item_charge_case(context);
    magic_beacon_ui_item_template(context);
    magic_beacon_ui_item_live_payload(context);
    magic_beacon_ui_item_help(context);
    magic_beacon_ui_item_address(context);
    magic_beacon_ui_item_payload(context);

    view_dispatcher_switch_to_view(app->view_dispatcher, APP_VIEW_LIST);
}

bool magic_beacon_scene_template_menu_on_event(void* context, SceneManagerEvent event) {
    FURI_LOG_T(TAG, "magic_beacon_scene_template_menu_on_event");
    if(event.type == SceneManagerEventTypeBack) {
        FURI_LOG_T(TAG, "SceneManagerEventTypeBack");
        MagicBeaconApp* app = (MagicBeaconApp*)context;
        app->data_init = false;
        variable_item_list_set_selected_item(app->list, 0);
    }
    return false;
}

void magic_beacon_scene_template_menu_on_exit(void* context) {
    FURI_LOG_T(TAG, "magic_beacon_scene_template_menu_on_exit");
    MagicBeaconApp* app = context;
    variable_item_list_reset(app->list);
}
