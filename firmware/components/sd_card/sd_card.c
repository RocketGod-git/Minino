#include "sd_card.h"

#include <dirent.h>
#include <string.h>
#include "argtable3/argtable3.h"
#include "driver/sdmmc_host.h"
#include "driver/sdspi_host.h"
#include "driver/spi_common.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"

#define MOUNT_POINT   "/sdcard"
#define MAX_CHAR_SIZE 1024
#define PIN_NUM_MISO  20
#define PIN_NUM_MOSI  19
#define PIN_NUM_CLK   21
#define PIN_NUM_CS    18

const char* f_result_to_name[] = {"FR_OK",
                                  "FR_DISK_ERR",
                                  "FR_INT_ERR",
                                  "FR_NOT_READY",
                                  "FR_NO_FILE",
                                  "FR_NO_PATH",
                                  "FR_INVALID_NAME",
                                  "FR_DENIED",
                                  "FR_EXIST",
                                  "FR_INVALID_OBJECT",
                                  "FR_WRITE_PROTECTED",
                                  "FR_INVALID_DRIVE",
                                  "FR_NOT_ENABLED",
                                  "FR_NO_FILESYSTEM",
                                  "FR_MKFS_ABORTED",
                                  "FR_TIMEOUT",
                                  "FR_LOCKED",
                                  "FR_NOT_ENOUGH_CORE",
                                  "FR_TOO_MANY_OPEN_FILES",
                                  "FR_INVALID_PARAMETER"};

static const char* TAG = "sd_card";
bool _sd_card_mounted = false;
bool _format_if_mount_failed = false;
sd_card_info_t _sd_card_info;

static struct {
  struct arg_str* device;
  struct arg_end* end;
} mount_args;

esp_err_t sd_card_fill_info(const sdmmc_card_t* card);

void print_files_in_sd() {
  if (!_sd_card_mounted) {
    ESP_LOGE(TAG, "SD card not mounted");
    return;
  }

  DIR* dir;
  struct dirent* ent;
  if ((dir = opendir(MOUNT_POINT)) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      ESP_LOGI(TAG, "%s", ent->d_name);
    }
    closedir(dir);
  } else {
    ESP_LOGE(TAG, "Could not open directory");
    return;
  }
}

/** 'mount' command */
int mount(int argc, char** argv) {
  esp_err_t ret;

  int nerrors = arg_parse(argc, argv, (void**) &mount_args);
  if (nerrors != 0) {
    arg_print_errors(stderr, mount_args.end, argv[0]);
    return ESP_ERR_INVALID_ARG;
  }
  /* mount sd card */
  if (!strncmp(mount_args.device->sval[0], "sd", 2)) {
    ESP_LOGI(TAG, "Initializing SD card, format: %s",
             _format_if_mount_failed ? "true" : "false");
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = _format_if_mount_failed,
        .max_files = 4,
        .allocation_unit_size = 16 * 1024};

    // initialize SD card and mount FAT filesystem.
    sdmmc_card_t* card;

    ESP_LOGI(TAG, "Using SPI peripheral");
    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    spi_bus_config_t bus_cfg = {
        .mosi_io_num = PIN_NUM_MOSI,
        .miso_io_num = PIN_NUM_MISO,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000,
    };
    ret = spi_bus_initialize(host.slot, &bus_cfg, SPI_DMA_CH_AUTO);
    if (ret != ESP_OK) {
      ESP_LOGE(TAG, "Failed to initialize bus.");
      return ESP_ERR_NO_MEM;
    }

    // This initializes the slot without card detect (CD) and write protect (WP)
    // signals. Modify slot_config.gpio_cd and slot_config.gpio_wp if your board
    // has these signals.
    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = PIN_NUM_CS;
    slot_config.host_id = host.slot;

    ret = esp_vfs_fat_sdspi_mount(MOUNT_POINT, &host, &slot_config,
                                  &mount_config, &card);

    if (ret != ESP_OK) {
      if (ret == ESP_FAIL) {
        ESP_LOGE(TAG,
                 "Failed to mount filesystem. "
                 "If you want the card to be formatted, set "
                 "format_if_mount_failed = true.");
        spi_bus_free(host.slot);
        return ESP_ERR_NOT_SUPPORTED;
      } else {
        ESP_LOGE(TAG,
                 "Failed to initialize the card (%s). "
                 "Make sure SD card lines have pull-up resistors in place.",
                 esp_err_to_name(ret));
        // Free the bus after mounting failed
        spi_bus_free(host.slot);
        return ESP_ERR_NOT_MOUNTED;
      }
    }
    /* print card info if mount successfully */
    sdmmc_card_print_info(stdout, card);
    sd_card_fill_info(card);
  }
  return ESP_OK;
}

void register_mount(void) {
  mount_args.device =
      arg_str1(NULL, NULL, "<sd>", "choose a proper device to mount/unmount");
  mount_args.end = arg_end(1);
}

esp_err_t unmount(int argc, char** argv) {
  esp_err_t ret;

  if (!_sd_card_mounted) {
    ESP_LOGE(TAG, "SD card not mounted");
    return ESP_ERR_NOT_ALLOWED;
  }

  sdmmc_host_t host = SDSPI_HOST_DEFAULT();
  int nerrors = arg_parse(argc, argv, (void**) &mount_args);
  if (nerrors != 0) {
    arg_print_errors(stderr, mount_args.end, argv[0]);
    return ESP_ERR_INVALID_ARG;
  }
  /* unmount sd card */
  if (!strncmp(mount_args.device->sval[0], "sd", 2)) {
    if (esp_vfs_fat_sdmmc_unmount() != ESP_OK) {
      ESP_LOGE(TAG, "Card unmount failed");
      return ESP_FAIL;
    }
    ret = spi_bus_free(host.slot);
    if (ret != ESP_OK) {
      ESP_LOGE(TAG, "Failed to deinitialize bus.");
      return ESP_FAIL;
    }
  }

  ESP_LOGI(TAG, "Card unmounted");
  return ESP_OK;
}

void register_unmount(void) {
  mount_args.device =
      arg_str1(NULL, NULL, "<sd>", "choose a proper device to mount/unmount");
  mount_args.end = arg_end(1);
}

void sd_card_begin() {
#if !defined(CONFIG_SD_CARD_DEBUG)
  esp_log_level_set(TAG, ESP_LOG_NONE);
#endif
  register_mount();
  register_unmount();
}

esp_err_t sd_card_mount() {
  esp_err_t err = ESP_OK;
  if (_sd_card_mounted) {
    ESP_LOGW(TAG, "SD card already mounted");
    return err;
  }

  const char** mount_argv[] = {"mount", "sd"};
  uint8_t mount_argc = 2;

  err = mount(mount_argc, (char**) mount_argv);
  if (err == ESP_OK) {
    _sd_card_mounted = true;
    return err;
  } else {
    ESP_LOGE(TAG, "Failed to mount SD card");
  }
  return err;
}

esp_err_t sd_card_unmount() {
  const char** unmount_argv2[] = {"unmount", "sd"};
  uint8_t unmount_argc2 = 2;

  esp_err_t err = unmount(unmount_argc2, (char**) unmount_argv2);
  if (err == ESP_OK) {
    _sd_card_mounted = false;
  }
  return err;
}

esp_err_t sd_card_format() {
  ESP_LOGI(TAG, "Formatting SD Card...");
  _format_if_mount_failed = true;
  esp_err_t err = sd_card_mount();
  _format_if_mount_failed = false;
  return err;
}

bool sd_card_is_mounted() {
  return _sd_card_mounted;
}

esp_err_t sd_card_create_dir(const char* dir_name) {
  if (!_sd_card_mounted) {
    ESP_LOGE(TAG, "SD card not mounted");
    return ESP_ERR_NOT_MOUNTED;
  }

  FRESULT res = f_mkdir(dir_name);
  if (res == FR_OK) {
    ESP_LOGI(TAG, "Directory created");
    return ESP_OK;
  } else if (res == FR_EXIST) {
    ESP_LOGW(TAG, "Directory already exists");
    return ESP_OK;
  } else {
    ESP_LOGE(TAG, "Failed to create directory, reason: %s",
             f_result_to_name[res]);
    return ESP_FAIL;
  }
}

esp_err_t sd_card_create_file(const char* path) {
  if (!_sd_card_mounted) {
    ESP_LOGE(TAG, "SD card not mounted");
    return ESP_FAIL;
  }

  uint8_t path_len = strlen(path);
  char full_path[path_len + 1 + strlen(MOUNT_POINT)];
  sprintf(full_path, "%s/%s", MOUNT_POINT, path);

  // Try to read it to check if it exists
  FILE* file = fopen(full_path, "r");
  if (file != NULL) {
    ESP_LOGE(TAG, "File already exists");
    fclose(file);
    return ESP_ERR_FILE_EXISTS;
  }

  fclose(file);
  file = fopen(full_path, "w");
  if (file == NULL) {
    ESP_LOGE(TAG, "Failed to open file for writing");
    return ESP_FAIL;
  }

  fclose(file);
  return ESP_OK;
}

esp_err_t sd_card_read_file(const char* path) {
  if (!_sd_card_mounted) {
    ESP_LOGE(TAG, "SD card not mounted");
    return ESP_FAIL;
  }

  uint8_t path_len = strlen(path);
  char full_path[path_len + 1 + strlen(MOUNT_POINT)];
  sprintf(full_path, "%s/%s", MOUNT_POINT, path);

  ESP_LOGI(TAG, "Reading file %s", full_path);
  FILE* file = fopen(full_path, "r");
  if (file == NULL) {
    ESP_LOGE(TAG, "Failed to open file for reading");
    return ESP_FAIL;
  }

  char line[MAX_CHAR_SIZE];
  ESP_LOGI(TAG, "Read from file:");
  while (fgets(line, sizeof(line), file) != NULL) {
    // strip newline
    char* pos = strchr(line, '\n');
    if (pos) {
      *pos = '\0';
    }
    ESP_LOGI(TAG, "'%s'", line);
  }
  fclose(file);

  return ESP_OK;
}

esp_err_t sd_card_write_file(const char* path, char* data) {
  if (!_sd_card_mounted) {
    ESP_LOGE(TAG, "SD card not mounted");
    return ESP_FAIL;
  }

  uint8_t path_len = strlen(path);
  char full_path[path_len + 1 + strlen(MOUNT_POINT)];
  sprintf(full_path, "%s/%s", MOUNT_POINT, path);

  ESP_LOGI(TAG, "Opening file %s", full_path);
  FILE* file = fopen(full_path, "w");
  if (file == NULL) {
    ESP_LOGE(TAG, "Failed to open file for writing");
    return ESP_FAIL;
  }
  fprintf(file, data);
  fclose(file);
  ESP_LOGI(TAG, "File written");

  return ESP_OK;
}

size_t sd_card_get_file_size(FILE* file) {
  if (file == NULL) {
    return 0;
  }
  long current_ptr = ftell(file);
  fseek(file, 0, SEEK_END);
  size_t file_size = ftell(file);
  fseek(file, 0, current_ptr);
  return file_size;
}

esp_err_t sd_card_fill_info(const sdmmc_card_t* card) {
  if (card == NULL) {
    ESP_LOGE(TAG, "Card is NULL");
    return ESP_FAIL;
  }

  _sd_card_info.name = card->cid.name;
  _sd_card_info.total_space =
      ((uint64_t) card->csd.capacity) * card->csd.sector_size / (1024 * 1024);
  _sd_card_info.speed = card->real_freq_khz < 1000
                            ? card->real_freq_khz
                            : card->real_freq_khz / 1000.0;
  if (card->is_sdio) {
    _sd_card_info.type = "SDIO";
  } else if (card->is_mmc) {
    _sd_card_info.type = "MMC";
  } else {
    int SD_OCR_SDHC_CAP = 1 << 30;
    _sd_card_info.type = (card->ocr & SD_OCR_SDHC_CAP) ? "SDHC/SDXC" : "SDSC";
  }
  return ESP_OK;
}

sd_card_info_t sd_card_get_info() {
  if (!_sd_card_mounted) {
    ESP_LOGE(TAG, "SD card not mounted");
  }

  return _sd_card_info;
}
