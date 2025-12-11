#include "bootloader_random.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_log_level.h"
#include "esp_random.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/projdefs.h"
#include "freertos/task.h"

#include "audio_driver.h"
#include "bsp_board.h"
#include "rgb_led_driver.h"
#include "tca9555_driver.h"
#include <stdint.h>
#include <stdio.h>

static char* TAG = "app main";

#define MAX_MP3_FILE 50
static char SD_Name[MAX_MP3_FILE][100];
static uint16_t Search_mp3_file_count = 0;
static char music_buf[120] = {0};

static void Search_mp3_Music(const char* dir) {
	Search_mp3_file_count =
		Folder_retrieval(dir, ".mp3", SD_Name, MAX_MP3_FILE);
	printf("file_count=%d\r\n", Search_mp3_file_count);
	if (Search_mp3_file_count) {
		for (int i = 0; i < Search_mp3_file_count; i++) {
			ESP_LOGI("SAFASF", "%s", SD_Name[i]);
		}
	}
}

void load_music(const char* dir) {
	Search_mp3_Music(dir);
	uint16_t choice = esp_random() % Search_mp3_file_count;
	memset(music_buf, 0, sizeof(music_buf));
	sprintf(music_buf, "file://%s/%s", dir, SD_Name[choice]);
}

void play_music() {
	ESP_LOGI(TAG, "Playing %s", music_buf);
	vTaskDelay(pdMS_TO_TICKS(1000));
	Audio_Play_Music(music_buf);
	set_rgb_mode(RGB_MODE_PLAYING);
	fflush(stdout);
	while (Audio_Get_Current_State() != ESP_ASP_STATE_FINISHED)
		vTaskDelay(pdMS_TO_TICKS(1));
	Audio_Stop_Play();
	set_rgb_mode(RGB_MODE_PLAYING);
	set_rgb_color(RGB_COLOR_OFF);
}

void app_main() {
	ESP_ERROR_CHECK(esp_board_init(16000, 2, 16));
	tca9555_driver_init();
	esp_sdcard_init("/sdcard", 10);
	Audio_Play_Init();
	Volume_Adjustment(70);
	bootloader_random_enable();
	esp_log_level_set("*", ESP_LOG_INFO);
	RGB_Example();
	set_rgb_color(RGB_COLOR_BLUE);

	// 10% chance to use alternative sounds
	bool violence = !(esp_random() % 9);
	char* dir;
	if (violence) {
		dir = "/sdcard/alt";
	} else {
		dir = "/sdcard";
	}
	ESP_LOGI(TAG, "Chosen dir: %s", dir);

	load_music(dir);
	play_music();

	// Wait 5 min
	vTaskDelay(pdMS_TO_TICKS(5 * 60 * 1000));

	// 1/10000 chance every second for sound effect
	while (true) {
		if (!(esp_random() % 9999)) {
			load_music("/sdcard/reg");
			play_music();
		}
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}
