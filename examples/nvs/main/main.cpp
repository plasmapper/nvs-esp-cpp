#include "pl_nvs.h"
#include "nvs_flash.h"

//==============================================================================

extern "C" void app_main(void) {
  esp_err_t error = nvs_flash_init();
  if (error == ESP_ERR_NVS_NO_FREE_PAGES || error == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    error = nvs_flash_init();
  }
  ESP_ERROR_CHECK(error);

  PL::NvsNamespace testNamespace("TestNamespace", PL::NvsAccessMode::readWrite);

  uint16_t bootCount = 0;
  std::string bootCountString;
  char bootCountBlob[5] = {};
  testNamespace.Read("bootCount", bootCount);
  testNamespace.Read("bootCountStr", bootCountString);
  testNamespace.Read("bootCountBlob", bootCountBlob, sizeof(bootCountBlob), NULL);

  printf("Boot count (uint16_t): %u\n", bootCount);
  printf("Boot count (string): \"%s\"\n", bootCountString.c_str());
  printf("Boot count (blob): %c%c%c%c%c\n", bootCountBlob[0], bootCountBlob[1], bootCountBlob[2], bootCountBlob[3], bootCountBlob[4]);

  bootCount++;
  if (bootCount <= sizeof(bootCountBlob)) {
    bootCountBlob[bootCount - 1] = '#';
    testNamespace.Write("bootCount", bootCount);
    testNamespace.Write("bootCountStr", std::string("BOOT COUNT = ") + std::to_string(bootCount));
    testNamespace.Write("bootCountBlob", bootCountBlob, sizeof(bootCountBlob));
  }
  else
    testNamespace.Erase();
  testNamespace.Commit();
}
