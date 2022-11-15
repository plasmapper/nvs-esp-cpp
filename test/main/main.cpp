#include "unity.h"
#include "nvs_flash.h"
#include "pl_nvs.h"

//==============================================================================

uint8_t u8W = 0xAA, u8R;
int8_t i8W = 0xAA, i8R;
uint16_t u16W = 0xAAAA, u16R;
int16_t i16W = 0xAAAA, i16R;
uint32_t u32W = 0xAAAAAAAA, u32R;
int32_t i32W = 0xAAAAAAAA, i32R;
uint64_t u64W = 0xAAAAAAAAAAAAAAAA, u64R;
int64_t i64W = 0xAAAAAAAAAAAAAAAA, i64R;
std::string stringW = "string", stringR;
char blobW[] = "blob";
char blobR[sizeof(blobW)];

void TestNvs();

//==============================================================================

extern "C" void app_main(void) {
  esp_err_t err = nvs_flash_init();
  if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK (nvs_flash_erase());
      err = nvs_flash_init();
  }
  ESP_ERROR_CHECK (err);

  UNITY_BEGIN();
  RUN_TEST (TestNvs);
  UNITY_END();
}

//==============================================================================

void TestNvs() {
  PL::NvsNamespace nvsW ("Test", PL::NvsAccessMode::readWrite);
  PL::NvsNamespace nvsR ("Test", PL::NvsAccessMode::readOnly);

  TEST_ASSERT (nvsW.Write ("u8", u8W) == ESP_OK);
  TEST_ASSERT (nvsW.Write ("i8", i8W) == ESP_OK);
  TEST_ASSERT (nvsW.Write ("u16", u16W) == ESP_OK);
  TEST_ASSERT (nvsW.Write ("i16", i16W) == ESP_OK);
  TEST_ASSERT (nvsW.Write ("u32", u32W) == ESP_OK);
  TEST_ASSERT (nvsW.Write ("i32", i32W) == ESP_OK);
  TEST_ASSERT (nvsW.Write ("u64", u64W) == ESP_OK);
  TEST_ASSERT (nvsW.Write ("i64", i64W) == ESP_OK);
  TEST_ASSERT (nvsW.Write ("string", stringW) == ESP_OK);
  TEST_ASSERT (nvsW.Write ("blob", blobW, sizeof (blobW)) == ESP_OK);
  TEST_ASSERT (nvsW.Commit() == ESP_OK);

  TEST_ASSERT (nvsR.Read ("u8", u8R) == ESP_OK);
  TEST_ASSERT (nvsR.Read ("i8", i8R) == ESP_OK);
  TEST_ASSERT (nvsR.Read ("u16", u16R) == ESP_OK);
  TEST_ASSERT (nvsR.Read ("i16", i16R) == ESP_OK);
  TEST_ASSERT (nvsR.Read ("u32", u32R) == ESP_OK);
  TEST_ASSERT (nvsR.Read ("i32", i32R) == ESP_OK);
  TEST_ASSERT (nvsR.Read ("u64", u64R) == ESP_OK);
  TEST_ASSERT (nvsR.Read ("i64", i64R) == ESP_OK);
  TEST_ASSERT (nvsR.Read ("string", stringR) == ESP_OK);
  size_t blobRSize;
  TEST_ASSERT (nvsR.Read ("blob", blobR, sizeof (blobR), &blobRSize) == ESP_OK);

  TEST_ASSERT_EQUAL (u8W, u8R);
  TEST_ASSERT_EQUAL (i8W, i8R);
  TEST_ASSERT_EQUAL (u16W, u16R);
  TEST_ASSERT_EQUAL (i16W, i16R);
  TEST_ASSERT_EQUAL (u32W, u32R);
  TEST_ASSERT_EQUAL (i32W, i32R);
  TEST_ASSERT_EQUAL (u64W, u64R);
  TEST_ASSERT_EQUAL (i64W, i64R);
  TEST_ASSERT (stringW == stringR);
  TEST_ASSERT_EQUAL (sizeof(blobW), blobRSize);
  for (int i = 0; i < sizeof (blobW); i++) {
    TEST_ASSERT_EQUAL (blobW[i], blobR[i]);
  }

  TEST_ASSERT (nvsW.Erase ("u8") == ESP_OK);
  TEST_ASSERT (nvsR.Read ("u8", u8R) == ESP_ERR_NVS_NOT_FOUND);
  TEST_ASSERT (nvsW.Erase () == ESP_OK);
  TEST_ASSERT (nvsR.Read ("i64", i64R) == ESP_ERR_NVS_NOT_FOUND);
}