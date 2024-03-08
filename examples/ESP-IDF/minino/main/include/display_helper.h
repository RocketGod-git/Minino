#ifndef DISPLAY_HELPER_H
#define DISPLAY_HELPER_H

enum MenuLayer {
    LAYER_MAIN_MENU = 0,
    LAYER_APPLICATIONS,
    LAYER_SETTINGS,
    LAYER_ABOUT,
};

enum MainMenuItem {
    MAIN_MENU_APPLICATIONS = 0,
    MAIN_MENU_SETTINGS,
    MAIN_MENU_ABOUT,
};

enum ApplicationsMenuItem {
    APPLICATIONS_MENU_WIFI = 0,
    APPLICATIONS_MENU_BLUETOOTH,
    APPLICATIONS_MENU_ZIGBEE,
    APPLICATIONS_MENU_THREAD,
    APPLICATIONS_MENU_MATTER,
};

typedef enum MenuLayer Layer;

static char* main_options[] = {
    "Applications",
    "Settings",
    "About",
};

static char* applications_options[] = {
    "WiFi",
    "Bluetooth",
    "Zigbee",
    "Thread",
    "Matter",
    "GPS",
};

static char* settings_options[] = {
    "Display",
    "Sound",
    "Network",
    "System",
};

static char* about_options[] = {
    "Version",
    "License",
    "Credits",
    "Legal",
};

static char* wifi_options[] = {
    "Analizer",
    "Help",
};

#endif  // DISPLAY_HELPER_H