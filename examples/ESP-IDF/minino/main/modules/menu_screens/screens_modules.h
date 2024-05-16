#pragma once

#include <stddef.h>

#define SCROLLING_TEXT "scrollable"

typedef enum {
  MENU_MAIN = 0,
  MENU_APPLICATIONS,
  MENU_SETTINGS,
  MENU_ABOUT,
  /* Applications */
  MENU_WIFI_APPS,
  MENU_BLUETOOTH_APPS,
  MENU_ZIGBEE_APPS,
  MENU_THREAD_APPS,
  MENU_MATTER_APPS,
  MENU_GPS,
  /* WiFi applications */
  MENU_WIFI_ANALIZER,
  MENU_WIFI_DEAUTH,
  /* WiFi analizer items */
  MENU_WIFI_ANALIZER_START,
  MENU_WIFI_ANALIZER_SETTINGS,
  /* Bluetooth applications */
  MENU_BLUETOOTH_AIRTAGS_SCAN,
  /* Zigbee applications */
  MENU_ZIGBEE_SPOOFING,
  MENU_ZIGBEE_SWITCH,
  MENU_ZIGBEE_LIGHT,
  /* Thread applications */
  MENU_THREAD_CLI,
  /* GPS applications */
  MENU_GPS_DATE_TIME,
  MENU_GPS_LOCATION,
  /* About items */
  MENU_ABOUT_VERSION,
  MENU_ABOUT_LICENSE,
  MENU_ABOUT_CREDITS,
  MENU_ABOUT_LEGAL,
  /* Settings items */
  MENU_SETTINGS_DISPLAY,
  MENU_SETTINGS_SOUND,
  MENU_SETTINGS_SYSTEM,
  /* About submenus */
  /* Menu count */
  MENU_COUNT,
} screen_module_menu_t;

static char* menus_list[MENU_COUNT] = {
    "MENU_MAIN", "MENU_APPLICATIONS", "MENU_SETTINGS", "MENU_ABOUT",
    /* Applications */
    "MENU_WIFI_APPS", "MENU_BLUETOOTH_APPS", "MENU_ZIGBEE_APPS",
    "MENU_THREAD_APPS", "MENU_MATTER_APPS", "MENU_GPS",
    /* WiFi applications */
    "MENU_WIFI_ANALIZER", "MENU_WIFI_DEAUTH",
    /* WiFi analizer items */
    "MENU_WIFI_ANALIZER_START", "MENU_WIFI_ANALIZER_SETTINGS",
    /* Bluetooth applications */
    "MENU_BLUETOOTH_AIRTAGS_SCAN",
    /* Zigbee applications */
    "MENU_ZIGBEE_SPOOFING", "MENU_ZIGBEE_SWITCH", "MENU_ZIGBEE_LIGHT",
    /* Thread applications */
    "MENU_THREAD_CLI",
    /* GPS applications */
    "MENU_GPS_DATE_TIME", "MENU_GPS_LOCATION",
    /* About items */
    "MENU_ABOUT_VERSION", "MENU_ABOUT_LICENSE", "MENU_ABOUT_CREDITS",
    "MENU_ABOUT_LEGAL",
    /* Settings items */
    "MENU_SETTINGS_DISPLAY", "MENU_SETTINGS_SOUND", "MENU_SETTINGS_SYSTEM",
    /* About submenus */
};

/**
 * @brief List of menus [current_menu][selected_item]
 * Used to get the next menu to display when the user selects an option
 */
static int menu_next_menu_table[MENU_COUNT][6] = {
    // MENU_MAIN
    {MENU_APPLICATIONS, MENU_SETTINGS, MENU_ABOUT},
    // MENU_APPLICATIONS
    {MENU_WIFI_APPS, MENU_BLUETOOTH_APPS, MENU_ZIGBEE_APPS, MENU_THREAD_APPS,
     MENU_MATTER_APPS, MENU_GPS},
    // MENU_SETTINGS
    {MENU_SETTINGS_DISPLAY, MENU_SETTINGS_SOUND, MENU_SETTINGS_SYSTEM},
    // MENU_ABOUT
    {MENU_ABOUT_VERSION, MENU_ABOUT_LICENSE, MENU_ABOUT_CREDITS,
     MENU_ABOUT_LEGAL},
    // MENU_WIFI_APPS
    {MENU_WIFI_ANALIZER, MENU_WIFI_DEAUTH},
    // MENU_BLUETOOTH_APPS
    {MENU_BLUETOOTH_AIRTAGS_SCAN},
    // MENU_ZIGBEE_APPS
    {MENU_ZIGBEE_SPOOFING},
    // MENU_THREAD_APPS
    {MENU_THREAD_CLI},
    // MENU_MATTER_APPS
    {},
    // MENU_GPS
    {MENU_GPS_DATE_TIME, MENU_GPS_LOCATION},
    // MENU_WIFI_ANALIZER
    {MENU_WIFI_ANALIZER_START, MENU_WIFI_ANALIZER_SETTINGS},
    // MENU_WIFI_DEAUTH
    {},
    // MENU_WIFI_ANALIZER_START
    {},
    // MENU_WIFI_ANALIZER_SETTINGS
    {},
    // MENU_BLUETOOTH_AIRTAGS_SCAN
    {},
    // MENU_ZIGBEE_SPOOFING
    {MENU_ZIGBEE_SWITCH, MENU_ZIGBEE_LIGHT},
    // MENU_ZIGBEE_SWITCH
    {},
    // MENU_ZIGBEE_LIGHT
    {},
    // MENU_THREAD_CLI
    {},
    // MENU_GPS_DATE_TIME
    {},
    // MENU_GPS_LOCATION
    {},
    // MENU_ABOUT_VERSION
    {},
    // MENU_ABOUT_LICENSE
    {},
    // MENU_ABOUT_CREDITS
    {},
    // MENU_ABOUT_LEGAL
    {},
    // MENU_SETTINGS_DISPLAY
    {},
    // MENU_SETTINGS_SOUND
    {},
    // MENU_SETTINGS_SYSTEM
    {},
};

/**
 * @brief List of menus [current_menu]
 * Used to get the previous menu to display when the user returns to the
 * previous menu in `menu_screens_exit_submenu`
 */
static int prev_menu_table[MENU_COUNT] = {
    MENU_MAIN,             // MENU_MAIN
    MENU_MAIN,             // MENU_APPLICATIONS
    MENU_MAIN,             // MENU_SETTINGS
    MENU_MAIN,             // MENU_ABOUT
    MENU_APPLICATIONS,     // MENU_WIFI_APPS
    MENU_APPLICATIONS,     // MENU_BLUETOOTH_APPS
    MENU_APPLICATIONS,     // MENU_ZIGBEE_APPS
    MENU_APPLICATIONS,     // MENU_THREAD_APPS
    MENU_APPLICATIONS,     // MENU_MATTER_APPS
    MENU_APPLICATIONS,     // MENU_GPS
    MENU_WIFI_APPS,        // MENU_WIFI_ANALIZER
    MENU_WIFI_APPS,        // MENU_WIFI_DEAUTH
    MENU_WIFI_ANALIZER,    // MENU_WIFI_ANALIZER_START
    MENU_WIFI_ANALIZER,    // MENU_WIFI_ANALIZER_SETTINGS
    MENU_BLUETOOTH_APPS,   // MENU_BLUETOOTH_AIRTAGS_SCAN
    MENU_ZIGBEE_APPS,      // MENU_ZIGBEE_SPOOFING
    MENU_ZIGBEE_SPOOFING,  // MENU_ZIGBEE_SWITCH
    MENU_ZIGBEE_SPOOFING,  // MENU_ZIGBEE_LIGHT
    MENU_THREAD_APPS,      // MENU_THREAD_CLI
    MENU_GPS,              // MENU_GPS_DATE_TIME
    MENU_GPS,              // MENU_GPS_LOCATION
    MENU_ABOUT,            // MENU_ABOUT_VERSION
    MENU_ABOUT,            // MENU_ABOUT_LICENSE
    MENU_ABOUT,            // MENU_ABOUT_CREDITS
    MENU_ABOUT,            // MENU_ABOUT_LEGAL
    MENU_SETTINGS,         // MENU_SETTINGS_DISPLAY
    MENU_SETTINGS,         // MENU_SETTINGS_SOUND
    MENU_SETTINGS,         // MENU_SETTINGS_SYSTEM
};

static int selected_item_history[MENU_COUNT] = {0};

static char* main_items[] = {
    "Applications",
    "Settings",
    "About",
    NULL,
};

static char* applications_items[] = {
    "WiFi", "Bluetooth", "Zigbee", "Thread", "Matter", "GPS", NULL,
};

static char* settings_items[] = {
    "Display",
    "Sound",
    "System",
    NULL,
};

static char* about_items[] = {
    "Version", "License", "Credits", "Legal", NULL,
};

static char* version_text[] = {
    SCROLLING_TEXT,
    /***************/
    "",
    "",
    "",
    " Minino v1.3.0",
    "     BETA",
    NULL,
};

static char* license_text[] = {
    SCROLLING_TEXT,
    /***************/
    "",
    "",
    "",
    "  GNU GPL 3.0",
    NULL,
};

static char* credits_text[] = {
    SCROLLING_TEXT,
    /***************/
    "Developed by",
    "Electronic Cats",
    "",
    "This product is",
    "in a BETA stage",
    "use at your own",
    NULL,
};

static char* legal_text[] = {
    SCROLLING_TEXT,
    /***************/
    "The user",
    "assumes all",
    "responsibility",
    "for the use of",
    "MININO and",
    "agrees to use",
    "it legally and",
    "ethically,",
    "avoiding any",
    "activities that",
    "may cause harm,",
    "interference,",
    "or unauthorized",
    "access to",
    "systems or data.",
    NULL,
};

static char* wifi_items[] = {
    "Analizer",
    "Deauth",
    NULL,
};

static char* wifi_analizer_items[] = {
    "Start",
    "Settings",
    NULL,
};

static char* wifi_sniffer_settings_items[] = {
    "Channel",
    "Filter",
    NULL,
};

static char* bluetooth_items[] = {
    "Airtags scan",
    NULL,
};

static char* zigbee_items[] = {
    "Spoofing",
    NULL,
};

static char* zigbee_spoofing_items[] = {
    "Switch",
    "Light",
    NULL,
};

static char* thread_items[] = {
    NULL,
};

static char* gps_items[] = {
    "Date & Time",
    "Location",
    NULL,
};

static char* empty_items[] = {
    NULL,
};

// List of menus, it must be in the same order as the enum screen_module_menu_t
static char** menu_items[MENU_COUNT] = {
    main_items, applications_items, settings_items, about_items,
    /* Applications */
    wifi_items, bluetooth_items, zigbee_items, thread_items,
    empty_items,  // Matter
    gps_items,
    /* WiFi applications */
    wifi_analizer_items,
    empty_items,  // WiFi Deauth
    empty_items,  // WiFi Analizer Start
    empty_items,  // WiFi Analizer Settings
    /* Bluetooth applications */
    empty_items,  // Bluetooth Airtags scan
    /* Zigbee applications */
    zigbee_spoofing_items,
    empty_items,  // Zigbee Switch
    empty_items,  // Zigbee Light
    /* Thread applications */
    empty_items,  // Thread CLI
    /* GPS applications */
    empty_items,  // Date & Time
    empty_items,  // Location
    /* About */
    version_text, license_text, credits_text, legal_text,
    /* Settings items */
    empty_items,  // Display
    empty_items,  // Sound
    empty_items,  // System
};
