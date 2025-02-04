#pragma once

#include <stddef.h>

#define MAX_NUM_ITEMS 8  // Can be increased if needed

/**
 * @brief Scrolling text flag
 *
 * Used to identify if the text is scrollable
 *
 * Add this flag to the text to make it scrollable
 */
#define VERTICAL_SCROLL_TEXT "vertical_scroll_text"

/**
 * @brief Configuration menu items
 *
 * Used to identify the configuration menu items
 *
 * Add this flag to the menu item to make it a configuration item
 */
#define CONFIGURATION_MENU_ITEMS "configuration"

/**
 * @brief Question menu items
 *
 * Used to identify the question menu items
 *
 * Add this flag to the menu item to make it a question item
 */
#define QUESTION_MENU_ITEMS "question"

/**
 * @brief Enum of menus
 *
 * Used to navigate through the different menus
 *
 * Modify this menu also requires to modify the `menu_list`, `next_menu_table`,
 * `prev_menu_table` and `menu_items` arrays
 */
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
  MENU_GPS,
  /* WiFi applications */
  MENU_WIFI_ANALIZER,
  MENU_WIFI_DEAUTH,
  MENU_WIFI_DOS,
  /* WiFi analizer items */
  MENU_WIFI_ANALYZER_RUN,
  MENU_WIFI_ANALYZER_SETTINGS,
  MENU_WIFI_ANALYZER_HELP,
  /* WiFi analizer start items */
  MENU_WIFI_ANALYZER_ASK_SUMMARY,
  MENU_WIFI_ANALYZER_SUMMARY,
  /* WiFi analizer settings */
  MENU_WIFI_ANALYZER_CHANNEL,
  MENU_WIFI_ANALYZER_DESTINATION,
  MENU_WIFI_ANALYZER_SD_EREASE_WARNING,
  /* Bluetooth applications */
  MENU_BLUETOOTH_TRAKERS_SCAN,
  MENU_BLUETOOTH_SPAM,
  /* Zigbee applications */
  MENU_ZIGBEE_SPOOFING,
  MENU_ZIGBEE_SWITCH,
  MENU_ZIGBEE_LIGHT,
  MENU_ZIGBEE_SNIFFER,
  /* Thread applications */
  MENU_THREAD_BROADCAST,
  MENU_THREAD_SNIFFER,
  /* Thread Sniffer App*/
  MENU_THREAD_SNIFFER_RUN,
  /* GPS applications */
  MENU_GPS_WARDRIVING,
  MENU_GPS_DATE_TIME,
  MENU_GPS_LOCATION,
  MENU_GPS_SPEED,
  MENU_GPS_HELP,
  /* Wardriving submenus */
  MENU_GPS_WARDRIVING_START,
  MENU_GPS_WARDRIVING_HELP,
  /* About submenus */
  MENU_ABOUT_VERSION,
  MENU_ABOUT_LICENSE,
  MENU_ABOUT_CREDITS,
  MENU_ABOUT_LEGAL,
  MENU_ABOUT_UPDATE,
  /* Settings items */
  MENU_SETTINGS_DISPLAY,
  MENU_WEB_SD_BROWSER,
  MENU_SETTINGS_SYSTEM,
  MENU_SETTINGS_TIME_ZONE,
  MENU_SETTINGS_WIFI,
  MENU_SETTINGS_SD_CARD,
  MENU_SETTINGS_SD_CARD_INFO,
  MENU_SETTINGS_SD_CARD_FORMAT,
  /* Menu count */
  MENU_COUNT,  // Keep this at the end
} screen_module_menu_t;

/**
 * @brief List of menus
 *
 * Used to get the menu name from the enum value
 * following the order of the `screen_module_menu_t` enum
 *
 * Usage: menu_list[screen_module_menu_t]
 */
const char* menu_list[] = {
    "MENU_MAIN",
    "MENU_APPLICATIONS",
    "MENU_SETTINGS",
    "MENU_ABOUT",
    "MENU_WIFI_APPS",
    "MENU_BLUETOOTH_APPS",
    "MENU_ZIGBEE_APPS",
    "MENU_THREAD_APPS",
    "MENU_GPS",
    "MENU_WIFI_ANALIZER",
    "MENU_WIFI_DEAUTH",
    "MENU_WIFI_DOS",
    "MENU_WIFI_ANALYZER_RUN",
    "MENU_WIFI_ANALYZER_SETTINGS",
    "MENU_WIFI_ANALYZER_HELP",
    "MENU_WIFI_ANALYZER_ASK_SUMMARY",
    "MENU_WIFI_ANALYZER_SUMMARY",
    "MENU_WIFI_ANALYZER_CHANNEL",
    "MENU_WIFI_ANALYZER_DESTINATION",
    "MENU_WIFI_ANALYZER_SD_EREASE_WARNING",
    "MENU_BLUETOOTH_TRAKERS_SCAN",
    "MENU_BLUETOOTH_SPAM",
    "MENU_ZIGBEE_SPOOFING",
    "MENU_ZIGBEE_SWITCH",
    "MENU_ZIGBEE_LIGHT",
    "MENU_ZIGBEE_SNIFFER",
    "MENU_THREAD_BROADCAST",
    "MENU_THREAD_SNIFFER",
    "MENU_THREAD_SNIFFER_RUN",
    "MENU_GPS_WARDRIVING",
    "MENU_GPS_DATE_TIME",
    "MENU_GPS_LOCATION",
    "MENU_GPS_SPEED",
    "MENU_GPS_HELP",
    "MENU_GPS_WARDRIVING_START",
    "MENU_GPS_WARDRIVING_HELP",
    "MENU_ABOUT_VERSION",
    "MENU_ABOUT_LICENSE",
    "MENU_ABOUT_CREDITS",
    "MENU_ABOUT_LEGAL",
    "MENU_ABOUT_UPDATE",
    "MENU_SETTINGS_DISPLAY",
    "MENU_WEB_SD_BROWSER",
    "MENU_SETTINGS_SYSTEM",
    "MENU_SETTINGS_TIME_ZONE",
    "MENU_SETTINGS_WIFI",
    "MENU_SETTINGS_SD_CARD",
    "MENU_SETTINGS_SD_CARD_INFO",
    "MENU_SETTINGS_SD_CARD_FORMAT",
};

/**
 * @brief List of menus
 *
 * Used to get the next menu to display when the user selects an option
 * following the order of the `screen_module_menu_t` enum
 *
 * Usage: next_menu_table[screen_module_menu_t][selected_item]
 */
const int next_menu_table[][MAX_NUM_ITEMS] = {
    // MENU_MAIN
    {MENU_APPLICATIONS, MENU_SETTINGS, MENU_ABOUT},
    // MENU_APPLICATIONS
    {
        MENU_WIFI_APPS, MENU_BLUETOOTH_APPS, MENU_ZIGBEE_APPS, MENU_THREAD_APPS,
        MENU_GPS  //, MENU_WEB_SD_BROWSER
    },
    // MENU_SETTINGS
    {MENU_SETTINGS_DISPLAY, MENU_SETTINGS_SYSTEM, MENU_WEB_SD_BROWSER},
    // MENU_ABOUT
    {MENU_ABOUT_VERSION, MENU_ABOUT_LICENSE, MENU_ABOUT_CREDITS,
     MENU_ABOUT_LEGAL, MENU_ABOUT_UPDATE},
    // MENU_WIFI_APPS
    {MENU_WIFI_ANALIZER, MENU_WIFI_DEAUTH, MENU_WIFI_DOS},
    // MENU_BLUETOOTH_APPS
    {MENU_BLUETOOTH_TRAKERS_SCAN, MENU_BLUETOOTH_SPAM},
    // MENU_ZIGBEE_APPS
    {MENU_ZIGBEE_SPOOFING, MENU_ZIGBEE_SNIFFER},
    // MENU_THREAD_APPS
    {MENU_THREAD_BROADCAST, MENU_THREAD_SNIFFER},
    // MENU_GPS
    {MENU_GPS_WARDRIVING, MENU_GPS_DATE_TIME, MENU_GPS_LOCATION, MENU_GPS_SPEED,
     MENU_GPS_HELP},
    // MENU_WIFI_ANALIZER
    {MENU_WIFI_ANALYZER_RUN, MENU_WIFI_ANALYZER_SETTINGS,
     MENU_WIFI_ANALYZER_HELP},
    // MENU_WIFI_DEAUTH
    {MENU_WIFI_DEAUTH},
    // MENU_WIFI_DOS
    {MENU_WIFI_DOS},
    // MENU_WIFI_ANALYZER_RUN
    {MENU_WIFI_ANALYZER_RUN},
    // MENU_WIFI_ANALYZER_SETTINGS
    {MENU_WIFI_ANALYZER_CHANNEL, MENU_WIFI_ANALYZER_DESTINATION},
    // MENU_WIFI_ANALYZER_HELP
    {MENU_WIFI_ANALYZER_HELP},
    // MENU_WIFI_ANALYZER_ASK_SUMMARY [0] -> Yes, [1] -> No
    {MENU_WIFI_ANALYZER_SUMMARY, MENU_WIFI_ANALIZER},
    // MENU_WIFI_ANALYZER_SUMMARY
    {MENU_WIFI_ANALYZER_SUMMARY},
    // MENU_WIFI_ANALYZER_CHANNEL
    {MENU_WIFI_ANALYZER_CHANNEL},
    // MENU_WIFI_ANALYZER_DESTINATION
    {MENU_WIFI_ANALYZER_DESTINATION},
    // MENU_WIFI_ANALYZER_SD_EREASE_WARNING
    {MENU_WIFI_ANALYZER_SD_EREASE_WARNING},
    // MENU_BLUETOOTH_TRAKERS_SCAN
    {MENU_BLUETOOTH_TRAKERS_SCAN},
    // MENU_BLUETOOTH_SPAM
    {MENU_BLUETOOTH_SPAM},
    // MENU_ZIGBEE_SPOOFING
    {MENU_ZIGBEE_SWITCH, MENU_ZIGBEE_LIGHT},
    // MENU_ZIGBEE_SWITCH
    {MENU_ZIGBEE_SWITCH},
    // MENU_ZIGBEE_LIGHT
    {MENU_ZIGBEE_LIGHT},
    // MENU_ZIGBEE_SNIFFER
    {MENU_ZIGBEE_SNIFFER},
    // MENU_THREAD_BROADCAST
    {MENU_THREAD_BROADCAST},
    // MENU_THREAD_SNIFFER
    {MENU_THREAD_SNIFFER_RUN},
    // MENU_THREAD_SNIFFER_RUN
    {MENU_THREAD_SNIFFER_RUN},
    // MENU_GPS_WARDRIVING
    {MENU_GPS_WARDRIVING_START, MENU_GPS_WARDRIVING_HELP},
    // MENU_GPS_DATE_TIME
    {MENU_GPS_DATE_TIME},
    // MENU_GPS_LOCATION
    {MENU_GPS_LOCATION},
    // MENU_GPS_SPEED
    {MENU_GPS_SPEED},
    // MENU_GPS_HELP
    {MENU_GPS_HELP},
    // MENU_GPS_WARDRIVING_START
    {MENU_GPS_WARDRIVING_START},
    // MENU_GPS_WARDRIVING_HELP
    {MENU_GPS_WARDRIVING_HELP},
    // MENU_ABOUT_VERSION
    {MENU_ABOUT_VERSION},
    // MENU_ABOUT_LICENSE
    {MENU_ABOUT_LICENSE},
    // MENU_ABOUT_CREDITS
    {MENU_ABOUT_CREDITS},
    // MENU_ABOUT_LEGAL
    {MENU_ABOUT_LEGAL},
    // MENU_ABOUT_UPDATE
    {MENU_ABOUT_UPDATE},
    // MENU_SETTINGS_DISPLAY
    {MENU_SETTINGS_DISPLAY},
    // MENU_WEB_SD_BROWSER
    {MENU_WEB_SD_BROWSER},
    // MENU_SETTINGS_SYSTEM
    {MENU_SETTINGS_TIME_ZONE, MENU_SETTINGS_WIFI, MENU_SETTINGS_SD_CARD},
    // MENU_SETTINGS_TIME_ZONE
    {MENU_SETTINGS_TIME_ZONE},
    // MENU_SETTINGS_WIFI
    {MENU_SETTINGS_WIFI},
    // MENU_SETTINGS_SD_CARD
    {MENU_SETTINGS_SD_CARD_INFO, MENU_SETTINGS_SD_CARD_FORMAT},
    // MENU_SETTINGS_SD_CARD_INFO
    {MENU_SETTINGS_SD_CARD_INFO},
    // MENU_SETTINGS_SD_CARD_FORMAT
    {MENU_SETTINGS_SD_CARD_INFO},
};

/**
 * @brief List of menus
 *
 * Used to get the previous menu to display when the user returns to the
 * previous menu in `menu_screens_exit_submenu`. Add the previous menu
 * following the order of the `screen_module_menu_t` enum
 *
 * Usage: prev_menu_table[screen_module_menu_t]
 */
const int prev_menu_table[] = {
    // PREVIOUS_MENU,                // CURRENT_MENU
    /*****************************************************************/
    MENU_MAIN,                    // MENU_MAIN
    MENU_MAIN,                    // MENU_APPLICATIONS
    MENU_MAIN,                    // MENU_SETTINGS
    MENU_MAIN,                    // MENU_ABOUT
    MENU_APPLICATIONS,            // MENU_WIFI_APPS
    MENU_APPLICATIONS,            // MENU_BLUETOOTH_APPS
    MENU_APPLICATIONS,            // MENU_ZIGBEE_APPS
    MENU_APPLICATIONS,            // MENU_THREAD_APPS
    MENU_APPLICATIONS,            // MENU_GPS
    MENU_WIFI_APPS,               // MENU_WIFI_ANALIZER
    MENU_WIFI_APPS,               // MENU_WIFI_DEAUTH
    MENU_WIFI_APPS,               // MENU_WIFI_DOS
    MENU_WIFI_ANALYZER_SUMMARY,   // MENU_WIFI_ANALYZER_RUN
    MENU_WIFI_ANALIZER,           // MENU_WIFI_ANALYZER_SETTINGS
    MENU_WIFI_ANALIZER,           // MENU_WIFI_ANALYZER_HELP
    MENU_WIFI_ANALYZER_RUN,       // MENU_WIFI_ANALYZER_ASK_SUMMARY
    MENU_WIFI_ANALIZER,           // MENU_WIFI_ANALYZER_SUMMARY
    MENU_WIFI_ANALYZER_SETTINGS,  // MENU_WIFI_ANALYZER_CHANNEL
    MENU_WIFI_ANALYZER_SETTINGS,  // MENU_WIFI_ANALYZER_DESTINATION
    MENU_WIFI_ANALYZER_SETTINGS,  // MENU_WIFI_ANALYZER_SD_EREASE_WARNING
    MENU_BLUETOOTH_APPS,          // MENU_BLUETOOTH_TRAKERS_SCAN
    MENU_BLUETOOTH_APPS,          // MENU_BLUETOOTH_SPAM
    MENU_ZIGBEE_APPS,             // MENU_ZIGBEE_SPOOFING
    MENU_ZIGBEE_SPOOFING,         // MENU_ZIGBEE_SWITCH
    MENU_ZIGBEE_SPOOFING,         // MENU_ZIGBEE_LIGHT
    MENU_ZIGBEE_APPS,             // MENU_ZIGBEE_SNIFFER
    MENU_THREAD_APPS,             // MENU_THREAD_BROADCAST
    MENU_THREAD_APPS,             // MENU_THREAD_SNIFFER
    MENU_THREAD_SNIFFER,          // MENU_THREAD_SNIFFER_RUN
    MENU_GPS,                     // MENU_GPS_WARDRIVING
    MENU_GPS,                     // MENU_GPS_DATE_TIME
    MENU_GPS,                     // MENU_GPS_LOCATION
    MENU_GPS,                     // MENU_GPS_SPEED
    MENU_GPS,                     // MENU_GPS_HELP
    MENU_GPS_WARDRIVING,          // MENU_GPS_WARDRIVING_START
    MENU_GPS_WARDRIVING,          // MENU_GPS_WARDRIVING_HELP
    MENU_ABOUT,                   // MENU_ABOUT_VERSION
    MENU_ABOUT,                   // MENU_ABOUT_LICENSE
    MENU_ABOUT,                   // MENU_ABOUT_CREDITS
    MENU_ABOUT,                   // MENU_ABOUT_LEGAL
    MENU_ABOUT,                   // MENU_ABOUT_UPDATE
    MENU_SETTINGS,                // MENU_SETTINGS_DISPLAY
    MENU_SETTINGS,                // MENU_WEB_SD_BROWSER
    MENU_SETTINGS,                // MENU_SETTINGS_SYSTEM
    MENU_SETTINGS_SYSTEM,         // MENU_SETTINGS_TIME_ZONE
    MENU_SETTINGS_SYSTEM,         // MENU_SETTINGS_WIFI
    MENU_SETTINGS_SYSTEM,         // MENU_SETTINGS_SD_CARD
    MENU_SETTINGS_SD_CARD,        // MENU_SETTINGS_SD_CARD_INFO
    MENU_SETTINGS_SD_CARD,        // MENU_SETTINGS_SD_CARD_FORMAT
};

/**
 * @brief History of selected items in each menu
 *
 * Used to keep track of the selected item in each menu
 *
 * Usage: selected_item_history[screen_module_menu_t]
 */
int selected_item_history[MENU_COUNT] = {0};

char* main_items[] = {
    "Applications",
    "Settings",
    "About",
    NULL,
};

char* applications_items[] = {
    "WiFi", "Bluetooth", "Zigbee", "Thread", "GPS", NULL,
};

char* settings_items[] = {
    "Display",
    "System",
    "File Manager",
    NULL,
};

char* about_items[] = {
    "Version", "License", "Credits", "Legal", "Update", NULL,
};

char* version_text[] = {
    VERTICAL_SCROLL_TEXT,
    /***************/
    "",
    "",
    "",
    " Minino v" CONFIG_PROJECT_VERSION,
    NULL,
};

char* license_text[] = {
    VERTICAL_SCROLL_TEXT,
    /***************/
    "",
    "",
    "",
    "  GNU GPL 3.0",
    NULL,
};

char* credits_text[] = {
    VERTICAL_SCROLL_TEXT,
    /***************/
    "Developed by",
    "Electronic Cats",
    "and PWnLabs",
    "",
    "With love from",
    "Mexico...",
    "",
    "Thanks",
    "- Kevin",
    "  @kevlem97",
    "- Roberto",
    "- Francisco",
    "  @deimoshall",
    "and Electronic",
    "Cats team",
    NULL,
};

char* legal_text[] = {
    VERTICAL_SCROLL_TEXT,
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

char* wifi_items[] = {
    "Analyzer",
    "Deauth",
    "DoS",
    NULL,
};

const char* wifi_analyzer_items[] = {
    "Start",
    "Settings",
    "Help",
    NULL,
};

char* wifi_analizer_summary[120] = {
    VERTICAL_SCROLL_TEXT,
    /***************/
    "Summary",
    NULL,
};

char* wifi_analizer_settings_items[] = {
    "Channel",
    "Destination",
    NULL,
};

char* wifi_analizer_help[] = {
    VERTICAL_SCROLL_TEXT,
    /***************/
    "This tool",
    "allows you to",
    "analyze the",
    "WiFi networks",
    "around you.",
    "",
    "You can select",
    "the channel and",
    "the destination",
    "to save the",
    "results.",
    NULL,
};

char* wifi_analizer_sd_warning[] = {
    VERTICAL_SCROLL_TEXT,
    /***************/
    "Warning",
    "",
    "The SD card",
    "is not",
    "available.",
    "",
    "Please insert",
    "an SD card",
    "to save the",
    "results.",
    NULL,
};

char* wifi_analizer_sd_erease_warning[] = {
    VERTICAL_SCROLL_TEXT,
    /***************/
    "WARNING",
    "Your SD card",
    "data may be",
    "erased if you",
    "start the",
    "WiFi analizer",
    NULL,
};

char* wifi_analizer_summary_question[] = {
    QUESTION_MENU_ITEMS, "Yes", "No", "Show summary?", NULL,
};

char* wifi_analizer_channel_items[] = {
    CONFIGURATION_MENU_ITEMS,
    "[ ] 1",
    "[ ] 2",
    "[ ] 3",
    "[ ] 4",
    "[ ] 5",
    "[ ] 6",
    "[ ] 7",
    "[ ] 8",
    "[ ] 9",
    "[ ] 10",
    "[ ] 11",
    "[ ] 12",
    "[ ] 13",
    "[ ] 14",
    NULL,
};

char* wifi_analizer_destination_items[] = {
    CONFIGURATION_MENU_ITEMS,
    "[ ] SD Card",
    "[ ] Internal",
    NULL,
};

char* bluetooth_items[] = {
    "Trakers scan",
    "Spam",
    NULL,
};

char* zigbee_items[] = {
    "Spoofing",
    "Sniffer",
    NULL,
};

char* zigbee_spoofing_items[] = {
    "Switch",
    "Light",
    NULL,
};

char* thread_items[] = {
    "Broadcast",
    "Sniffer",
    NULL,
};

char* thread_sniffer_items[] = {
    "Run",
    NULL,
};

char* gps_items[] = {
    "Wardrive", "Date & Time", "Location", "Speed", "Help", NULL,
};

char* gps_date_time_items[] = {
    VERTICAL_SCROLL_TEXT,
    /***************/
    "Signal:",
    "",
    "Date:",
    "Time:",
    NULL,
};

char* gps_location_items[] = {
    VERTICAL_SCROLL_TEXT,
    /***************/
    "Signal:",
    "",
    "Latitude:",
    "",
    "Longitude:",
    "",
    "Altitude:",
    "",
    NULL,
};

char* gps_speed_items[] = {
    VERTICAL_SCROLL_TEXT,
    /***************/
    "Signal:",
    "",
    "Speed:",
    NULL,
};

char* gps_help[] = {
    VERTICAL_SCROLL_TEXT,
    /***************/
    "Verify your",
    "time zone if",
    "the time is not",
    "correct, go to",
    "`Settings/",
    "System/Time",
    "zone` and",
    "select the",
    "correct one.",
    NULL,
};

char* wardriving_items[] = {
    "Start",
    "Help",
    NULL,
};

char* wardriving_help[] = {
    VERTICAL_SCROLL_TEXT,
    /***************/
    "This tool",
    "allows you to",
    "scan for WiFi",
    "networks and",
    "save the",
    "results in a",
    "CSV file on",
    "the SD card.",
    "",
    "Before starting",
    "the scan, make",
    "sure your date",
    "and time are",
    "correct.",
    NULL,
};

char* gps_time_zone_options[] = {
    CONFIGURATION_MENU_ITEMS,
    "[ ] UTC-12",
    "[ ] UTC-11",
    "[ ] UTC-10",
    "[ ] UTC-9:30",
    "[ ] UTC-9",
    "[ ] UTC-8",
    "[ ] UTC-7",
    "[ ] UTC-6",
    "[ ] UTC-5",
    "[ ] UTC-4",
    "[ ] UTC-3:30",
    "[ ] UTC-3",
    "[ ] UTC-2",
    "[ ] UTC-1",
    "[ ] UTC+0",
    "[ ] UTC+1",
    "[ ] UTC+2",
    "[ ] UTC+3",
    "[ ] UTC+3:30",
    "[ ] UTC+4",
    "[ ] UTC+4:30",
    "[ ] UTC+5",
    "[ ] UTC+5:30",
    "[ ] UTC+5:45",
    "[ ] UTC+6",
    "[ ] UTC+6:30",
    "[ ] UTC+7",
    "[ ] UTC+8",
    "[ ] UTC+8:45",
    "[ ] UTC+9",
    "[ ] UTC+9:30",
    "[ ] UTC+10",
    "[ ] UTC+10:30",
    "[ ] UTC+11",
    "[ ] UTC+12",
    "[ ] UTC+12:45",
    "[ ] UTC+13",
    "[ ] UTC+14",
    NULL,
};

char* system_settings_items[] = {
    "Time zone",
    "WiFi",
    "SD card",
    NULL,
};

char* sd_card_settings_items[] = {
    "Info",
    "Check Format",
    NULL,
};

char* sd_card_info[] = {
    VERTICAL_SCROLL_TEXT,
    /***************/
    "SD Card Info",
    "",
    "Name:",
    "Space:",
    "Speed:",
    "Type:",
    NULL,
};

char* sd_card_format_array[] = {
    "This array is not used",
    NULL,
};

char* empty_items[] = {
    NULL,
};

/**
 * @brief List of menu items
 *
 * Used to get the menu items from the menu enum value
 * following the order of the `screen_module_menu_t` enum
 *
 * Usage: menu_items[screen_module_menu_t]
 */
char** menu_items[] = {
    main_items,                       // MENU_MAIN
    applications_items,               // MENU_APPLICATIONS
    settings_items,                   // MENU_SETTINGS
    about_items,                      // MENU_ABOUT
    wifi_items,                       // MENU_WIFI_APPS
    bluetooth_items,                  // MENU_BLUETOOTH_APPS
    zigbee_items,                     // MENU_ZIGBEE_APPS
    thread_items,                     // MENU_THREAD_APPS
    gps_items,                        // MENU_GPS
    wifi_analyzer_items,              // MENU_WIFI_ANALIZER
    empty_items,                      // MENU_WIFI_DEAUTH
    empty_items,                      // MENU_WIFI_DOS
    empty_items,                      // MENU_WIFI_ANALYZER_RUN
    wifi_analizer_settings_items,     // MENU_WIFI_ANALYZER_SETTINGS
    wifi_analizer_help,               // MENU_WIFI_ANALYZER_HELP
    wifi_analizer_summary_question,   // MENU_WIFI_ANALYZER_ASK_SUMMARY
    wifi_analizer_summary,            // MENU_WIFI_ANALYZER_SUMMARY
    wifi_analizer_channel_items,      // MENU_WIFI_ANALYZER_CHANNEL
    wifi_analizer_destination_items,  // MENU_WIFI_ANALYZER_DESTINATION
    wifi_analizer_sd_erease_warning,  // MENU_WIFI_ANALYZER_SD_EREASE_WARNING
    empty_items,                      // MENU_BLUETOOTH_TRAKERS_SCAN
    empty_items,                      // MENU_BLUETOOTH_SPAM
    zigbee_spoofing_items,            // MENU_ZIGBEE_SPOOFING
    empty_items,                      // MENU_ZIGBEE_SWITCH
    empty_items,                      // MENU_ZIGBEE_LIGHT
    empty_items,                      // MENU_ZIGBEE_SNIFFER
    empty_items,                      // MENU_THREAD_BROADCAST
    thread_sniffer_items,             // MENU_THREAD_SNIFFER
    empty_items,                      // MENU_THREAD_SNIFFER_RUN
    wardriving_items,                 // MENU_GPS_WARDRIVING
    gps_date_time_items,              // MENU_GPS_DATE_TIME
    gps_location_items,               // MENU_GPS_LOCATION
    gps_speed_items,                  // MENU_GPS_SPEED
    gps_help,                         // MENU_GPS_HELP
    empty_items,                      // MENU_GPS_WARDRIVING_START
    wardriving_help,                  // MENU_GPS_WARDRIVING_HELP
    version_text,                     // MENU_ABOUT_VERSION
    license_text,                     // MENU_ABOUT_LICENSE
    credits_text,                     // MENU_ABOUT_CREDITS
    legal_text,                       // MENU_ABOUT_LEGAL
    empty_items,                      // MENU_ABOUT_UPDATE
    empty_items,                      // MENU_SETTINGS_DISPLAY
    empty_items,                      // MENU_WEB_SD_BROWSER
    system_settings_items,            // MENU_SETTINGS_SYSTEM
    gps_time_zone_options,            // MENU_SETTINGS_TIME_ZONE
    empty_items,                      // MENU_SETTINGS_WIFI
    sd_card_settings_items,           // MENU_SETTINGS_SD_CARD
    sd_card_info,                     // MENU_SETTINGS_SD_CARD_INFO
    sd_card_format_array,             // MENU_SETTINGS_SD_CARD_FORMAT
};
