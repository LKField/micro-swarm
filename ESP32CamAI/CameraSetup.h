// File: CameraSetup.h
#ifndef CAMERA_SETUP_H
#define CAMERA_SETUP_H

#include "esp_camera.h"
#include "soc/soc.h"           // Necessary for disabling brownout detection
#include "soc/rtc_cntl_reg.h"    // Necessary for disabling brownout detection
#include "mbedtls/base64.h"  // Include the mbedTLS header for Base64 encoding

// Define the camera model’s pin assignments for the AI-Thinker module
#define PWDN_GPIO_NUM    32
#define RESET_GPIO_NUM   -1  // Not used
#define XCLK_GPIO_NUM     0
#define SIOD_GPIO_NUM    26
#define SIOC_GPIO_NUM    27

#define Y9_GPIO_NUM      35
#define Y8_GPIO_NUM      34
#define Y7_GPIO_NUM      39
#define Y6_GPIO_NUM      36
#define Y5_GPIO_NUM      21
#define Y4_GPIO_NUM      19
#define Y3_GPIO_NUM      18
#define Y2_GPIO_NUM       5
#define VSYNC_GPIO_NUM   25
#define HREF_GPIO_NUM    23
#define PCLK_GPIO_NUM    22

// This function sets up and initializes the camera.
// It disables brownout detection, sets all the pin and format info,
// then returns the result of esp_camera_init().
esp_err_t initCameraModule() {
  // (Optional) Disable brownout detector (not recommended for production)
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;  // Use JPEG format
  config.grab_mode = CAMERA_GRAB_LATEST; // Always get last available frame

  // Choose resolution based on available PSRAM
  if (psramFound()) {
      config.frame_size = FRAMESIZE_VGA; // High resolution
      config.jpeg_quality = 12;           // Lower quality to save memory
      config.fb_count = 1;
  } else {
      config.frame_size = FRAMESIZE_VGA; // Lower resolution if no PSRAM
      config.jpeg_quality = 12;
      config.fb_count = 1;
  }

  // Initialize the camera
  return esp_camera_init(&config);
}

// Function that converts the frame buffer (JPG image) from esp_camera_fb_get()
// to a Base64 encoded char array with the prefix "data:image/jpeg;base64,".
// Returns NULL on error.
char* fbToBase64(camera_fb_t* fb) {
  if (!fb || !fb->buf || fb->len == 0) {
    return NULL;
  }

  // Calculate the expected size of the Base64 encoded output.
  // Base64 conversion outputs 4 characters for every 3 bytes.
  size_t base64OutSize = 4 * ((fb->len + 2) / 3);

  // Allocate a temporary buffer to hold the Base64 encoded data.
  char *tempBuffer = (char *)malloc(base64OutSize + 1); // +1 for null terminator
  if (!tempBuffer) {
    Serial.println("Memory allocation for temporary Base64 buffer failed");
    return NULL;
  }

  size_t out_len = 0;
  int ret = mbedtls_base64_encode((unsigned char*)tempBuffer, base64OutSize + 1, &out_len,
                                  fb->buf, fb->len);
  if (ret != 0) {
    Serial.printf("Base64 encoding failed with error: %d\n", ret);
    free(tempBuffer);
    return NULL;
  }
  tempBuffer[out_len] = '\0';  // Null-terminate the temporary Base64 string

  // Define the prefix to prepend.
  const char *prefix = "data:image/jpeg;base64,";
  size_t prefixLen = strlen(prefix);

  // Allocate the final buffer to hold the prefix and the Base64 encoded string.
  // +1 for the null terminator.
  size_t finalBufferSize = prefixLen + out_len;
  char *finalBuffer = (char *)malloc(finalBufferSize + 1);
  if (!finalBuffer) {
    Serial.println("Memory allocation for final Base64 buffer failed");
    free(tempBuffer);
    return NULL;
  }

  // Copy the prefix and then the Base64 encoded data into the final buffer.
  memcpy(finalBuffer, prefix, prefixLen);
  memcpy(finalBuffer + prefixLen, tempBuffer, out_len);
  finalBuffer[finalBufferSize] = '\0';  // Null-terminate the final string

  // Free the temporary buffer containing only the Base64 data.
  free(tempBuffer);

  return finalBuffer;
}
#endif  // CAMERA_SETUP_H