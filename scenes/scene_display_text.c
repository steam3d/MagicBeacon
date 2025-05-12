#include "scene_display_text.h"
#include "magic_beacon.h"
#define TAG "magic_beacon"

static const char* get_payload_help_text() {
    return "Payload bytes:\n"
           "04, 05 - model\n"
           "07 - left and right battery\n"
           "08 - bits 0-3: charge level; bits 4-7: case battery\n"
           "10 - color\n"
           "Models:\n"
           "0220 AirPods1\n"
           "0F20 AirPods2\n"
           "1320 AirPods3\n"
           "1920 AirPods4\n"
           "1B20 AirPods4anc\n"
           "0E20 AirPodsPro\n"
           "2420 AirPodsProusbc\n"
           "1420 AirPodsPro2\n"
           "0A20 AirPodsMax\n"
           "1F20 AirPodsMax2024\n"
           "0B20 PowerbeatsPro\n"
           "1D20 PowerbeatsPro2\n"
           "0320 Powerbeats3\n"
           "0D20 Powerbeats4\n"
           "0620 BeatsSolo3\n"
           "2620 BeatsSoloBuds\n"
           "0C20 BeatsSoloPro\n"
           "0920 BeatsStudio3\n"
           "1720 BeatsStudioPro\n"
           "1120 BeatsStudioBuds\n"
           "1620 BeatsStudioBuds+\n"
           "0520 BeatsX\n"
           "1020 BeatsFlex\n"
           "1220 BeatsFitPro";
}

static const char* get_main_menu_help_text() {
    return "MagicBeacon - an emulator of AirPods packets (payloads) transmitted over Bluetooth LE.\n"
           "\n"
           "Modes:\n"
           "Payload from template - create payloads based on predefined templates.\n"
           "Payload from file - load payloads from a text file.\n"
           "\n"
           "File format:\n"
           "The first line - MAC address (e.g., XX:XX:XX:XX:XX:XX)\n"
           "The remaining lines - payload packets, one per line.\n"
           "Maximum payload length: up to 27 bytes (54 characters), no separators.\n"
           "\n"
           "Example:\n"
           "0c:2d:0a:21:42:1d\n"
           "0719011B2075AAB83100...\n"
           "0719011B2075AAB83100...\n"
           "0719011B2075AAB83100...\n"
           "\n"
           "How to use:\n"
           "Set the desired parameters in the settings. Enable \"Advertising\" to start broadcasting.  \n"
           "When parameters are changed, the payload is updated automatically.  \n"
           "To enable automatic updating in \"Edit payload\" mode without saving, turn on \"Live payload\".  \n"
           "To change the MAC address: disable \"Advertising\", change the address, and then enable it again.\n"
           "\n"
           "Developer:\n"
           "Aleksander Maslov\n"
           "Website:\n"
           "magicpods.app";
}

void magic_beacon_scene_display_text_on_enter(void* context) {
    FURI_LOG_T(TAG, "magic_beacon_scene_display_text_on_enter");
    MagicBeaconApp* app = context;
    if(app->message == HELP_MESSAGE_ABOUT) {
        text_box_set_text(app->text_box, get_main_menu_help_text());
    } else {
        text_box_set_text(app->text_box, get_payload_help_text());
    }
    view_dispatcher_switch_to_view(app->view_dispatcher, APP_VIEW_TEXT_BOX);
}

bool magic_beacon_scene_display_text_on_event(void* context, SceneManagerEvent event) {
    FURI_LOG_T(TAG, "magic_beacon_scene_display_text_on_event");
    UNUSED(context);
    UNUSED(event);
    return false;
}

void magic_beacon_scene_display_text_on_exit(void* context) {
    FURI_LOG_T(TAG, "magic_beacon_scene_display_text_on_exit");
    UNUSED(context);
}
