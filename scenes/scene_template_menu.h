#pragma once
#include <gui/scene_manager.h>

typedef enum {
    TEMPLATE_AIRPODS_2 = 0x200f,
    TEMPLATE_AIRPODS_3 = 0x2013,
    TEMPLATE_AIRPODS_4 = 0x2019,
    TEMPLATE_AIRPODS_4_ANC = 0x201b,
    TEMPLATE_AIRPODS_PRO = 0x200e,
    TEMPLATE_AIRPODS_PRO_C = 0x2024,
    TEMPLATE_AIRPODS_PRO_2 = 0x2014,
    TEMPLATE_AIRPODS_MAX = 0x200a,
    TEMPLATE_AIRPODS_MAX_2024 = 0x201f,
    TEMPLATE_POWER_BEATS_PRO = 0x2017,
    TEMPLATE_POWER_BEATS_PRO_2 = 0x201d,
    TEMPLATE_BEATS_FITS_PRO = 0x2012,
    TEMPLATE_BEATS_STUDIO_BUDS = 0x2011,
    TEMPLATE_BEATS_STUDIO_BUDS_PLUS = 0x2016
} Template;
extern const Template template_order[14];

void magic_beacon_template_payload_init(LeData* data, Template* type, Template new_type);
void magic_beacon_scene_template_menu_on_enter(void* context);
bool magic_beacon_scene_template_menu_on_event(void* context, SceneManagerEvent event);
void magic_beacon_scene_template_menu_on_exit(void* context);
