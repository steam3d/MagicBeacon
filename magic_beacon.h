#pragma once

#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>
#include <gui/modules/menu.h>
#include <gui/modules/popup.h>
#include <gui/modules/variable_item_list.h>
#include <gui/modules/byte_input.h>
#include <gui/modules/file_browser.h>
#include <gui/modules/text_box.h>
#include <gui/modules/submenu.h>
#include "ble.h"
#include "scenes/scene_template_menu.h"

typedef enum {
    APP_SCENE_MAIN_MENU,
    APP_SCENE_TEMPLATE,
    APP_SCENE_FILE,
    APP_SCENE_FILE_MENU,
    APP_SCENE_INPUT_PAYLOAD,
    APP_SCENE_ADDRESS,
    APP_SCENE_HELP,
    APP_SCENE_COUNT
} AppScene;

typedef enum {
    APP_VIEW_LIST,
    APP_VIEW_BYTE_INPUT,
    APP_VIEW_FILE_BROWSER,
    APP_VIEW_TEXT_BOX,
    APP_VIEW_SUBMENU
} AppView;

typedef enum {
    HELP_MESSAGE_ABOUT,
    HELP_MESSAGE_PAYLOAD,
} HelpMessage;

#define MAX_LINE_LEN 54
typedef struct {
    uint8_t* data;
    size_t length;
} PayloadArray;

typedef struct {
    SceneManager* scene_manager;
    ViewDispatcher* view_dispatcher;
    VariableItemList* list;
    Submenu* submenu;
    ByteInput* byte_input;
    TextBox* text_box;
    LeData le_data;

    PayloadArray* payloads;
    size_t payloads_length;
    uint32_t payloads_selected;

    Template template; //which packet will be used for refference
    FileBrowser* file_browser;
    FuriString* file_path;

    bool data_init;
    bool live_payload;
    HelpMessage message;
} MagicBeaconApp;
