#include "pl_nvs_namespace.h"
#include "esp_check.h"

//==============================================================================

static const char* TAG = "pl_nvs_namespace";

//==============================================================================

namespace PL {

//==============================================================================

NvsNamespace::NvsNamespace (const std::string& partitionName, const std::string& namespaceName, NvsAccessMode accessMode) :
    partitionName (partitionName), namespaceName (namespaceName), accessMode (accessMode) {
  if (accessMode != NvsAccessMode::readOnly && accessMode != NvsAccessMode::readWrite)
    this->accessMode = NvsAccessMode::readOnly;
}

//==============================================================================

NvsNamespace::NvsNamespace (const std::string& namespaceName, NvsAccessMode accessMode) :
  partitionName (NVS_DEFAULT_PART_NAME), namespaceName (namespaceName), accessMode (accessMode) {}

//==============================================================================

NvsNamespace::~NvsNamespace() {
  if (open) {
    nvs_commit (handle);
    nvs_close(handle);
  }
}

//==============================================================================

esp_err_t NvsNamespace::Lock (TickType_t timeout) {
  esp_err_t error = mutex.Lock (timeout);
  if (error == ESP_OK)
    return ESP_OK;
  if (error == ESP_ERR_TIMEOUT && timeout == 0)
    return ESP_ERR_TIMEOUT;
  ESP_RETURN_ON_ERROR (error, TAG, "mutex lock failed");
  return ESP_OK;
}

//==============================================================================

esp_err_t NvsNamespace::Unlock() {
  ESP_RETURN_ON_ERROR (mutex.Unlock(), TAG, "mutex unlock failed");
  return ESP_OK;
}

//==============================================================================

esp_err_t NvsNamespace::Read (const std::string& key, uint8_t& value) {
  LockGuard lg (*this);
  ESP_RETURN_ON_ERROR (Open(), TAG, "open failed");
  ESP_RETURN_ON_ERROR (nvs_get_u8 (handle, key.c_str(), &value), TAG, "read '%s' failed", key.c_str());
  return ESP_OK;
}

//==============================================================================

esp_err_t NvsNamespace::Write (const std::string& key, uint8_t value) {
  LockGuard lg (*this);
  ESP_RETURN_ON_ERROR (Open(), TAG, "open failed");
  ESP_RETURN_ON_ERROR (nvs_set_u8 (handle, key.c_str(), value), TAG, "write '%s' failed", key.c_str());
  return ESP_OK;
}

//==============================================================================

esp_err_t NvsNamespace::Read (const std::string& key, int8_t& value) {
  LockGuard lg (*this);
  ESP_RETURN_ON_ERROR (Open(), TAG, "open failed");
  ESP_RETURN_ON_ERROR (nvs_get_i8 (handle, key.c_str(), &value), TAG, "read '%s' failed", key.c_str());
  return ESP_OK;
}

//==============================================================================

esp_err_t NvsNamespace::Write (const std::string& key, int8_t value) {
  LockGuard lg (*this);
  ESP_RETURN_ON_ERROR (Open(), TAG, "open failed");
  ESP_RETURN_ON_ERROR (nvs_set_i8 (handle, key.c_str(), value), TAG, "write '%s' failed", key.c_str());
  return ESP_OK;
}

//==============================================================================

esp_err_t NvsNamespace::Read (const std::string& key, uint16_t& value) {
  LockGuard lg (*this);
  ESP_RETURN_ON_ERROR (Open(), TAG, "open failed");
  ESP_RETURN_ON_ERROR (nvs_get_u16 (handle, key.c_str(), &value), TAG, "read '%s' failed", key.c_str());
  return ESP_OK;
}

//==============================================================================

esp_err_t NvsNamespace::Write (const std::string& key, uint16_t value) {
  LockGuard lg (*this);
  ESP_RETURN_ON_ERROR (Open(), TAG, "open failed");
  ESP_RETURN_ON_ERROR (nvs_set_u16 (handle, key.c_str(), value), TAG, "write '%s' failed", key.c_str());
  return ESP_OK;
}

//==============================================================================

esp_err_t NvsNamespace::Read (const std::string& key, int16_t& value) {
  LockGuard lg (*this);
  ESP_RETURN_ON_ERROR (Open(), TAG, "open failed");
  ESP_RETURN_ON_ERROR (nvs_get_i16 (handle, key.c_str(), &value), TAG, "read '%s' failed", key.c_str());
  return ESP_OK;
}

//==============================================================================

esp_err_t NvsNamespace::Write (const std::string& key, int16_t value) {
  LockGuard lg (*this);
  ESP_RETURN_ON_ERROR (Open(), TAG, "open failed");
  ESP_RETURN_ON_ERROR (nvs_set_i16 (handle, key.c_str(), value), TAG, "write '%s' failed", key.c_str());
  return ESP_OK;
}

//==============================================================================

esp_err_t NvsNamespace::Read (const std::string& key, uint32_t& value) {
  LockGuard lg (*this);
  ESP_RETURN_ON_ERROR (Open(), TAG, "open failed");
  ESP_RETURN_ON_ERROR (nvs_get_u32 (handle, key.c_str(), &value), TAG, "read '%s' failed", key.c_str());
  return ESP_OK;
}

//==============================================================================

esp_err_t NvsNamespace::Write (const std::string& key, uint32_t value) {
  LockGuard lg (*this);
  ESP_RETURN_ON_ERROR (Open(), TAG, "open failed");
  ESP_RETURN_ON_ERROR (nvs_set_u32 (handle, key.c_str(), value), TAG, "write '%s' failed", key.c_str());
  return ESP_OK;
}

//==============================================================================

esp_err_t NvsNamespace::Read (const std::string& key, int32_t& value) {
  LockGuard lg (*this);
  ESP_RETURN_ON_ERROR (Open(), TAG, "open failed");
  ESP_RETURN_ON_ERROR (nvs_get_i32 (handle, key.c_str(), &value), TAG, "read '%s' failed", key.c_str());
  return ESP_OK;
}

//==============================================================================

esp_err_t NvsNamespace::Write (const std::string& key, int32_t value) {
  LockGuard lg (*this);
  ESP_RETURN_ON_ERROR (Open(), TAG, "open failed");
  ESP_RETURN_ON_ERROR (nvs_set_i32 (handle, key.c_str(), value), TAG, "write '%s' failed", key.c_str());
  return ESP_OK;
}

//==============================================================================

esp_err_t NvsNamespace::Read (const std::string& key, uint64_t& value) {
  LockGuard lg (*this);
  ESP_RETURN_ON_ERROR (Open(), TAG, "open failed");
  ESP_RETURN_ON_ERROR (nvs_get_u64 (handle, key.c_str(), &value), TAG, "read '%s' failed", key.c_str());
  return ESP_OK;
}

//==============================================================================

esp_err_t NvsNamespace::Write (const std::string& key, uint64_t value) {
  LockGuard lg (*this);
  ESP_RETURN_ON_ERROR (Open(), TAG, "open failed");
  ESP_RETURN_ON_ERROR (nvs_set_u64 (handle, key.c_str(), value), TAG, "write '%s' failed", key.c_str());
  return ESP_OK;
}

//==============================================================================

esp_err_t NvsNamespace::Read (const std::string& key, int64_t& value) {
  LockGuard lg (*this);
  ESP_RETURN_ON_ERROR (Open(), TAG, "open failed");
  ESP_RETURN_ON_ERROR (nvs_get_i64 (handle, key.c_str(), &value), TAG, "read '%s' failed", key.c_str());
  return ESP_OK;
}

//==============================================================================

esp_err_t NvsNamespace::Write (const std::string& key, int64_t value) {
  LockGuard lg (*this);
  ESP_RETURN_ON_ERROR (Open(), TAG, "open failed");
  ESP_RETURN_ON_ERROR (nvs_set_i64 (handle, key.c_str(), value), TAG, "write '%s' failed", key.c_str());
  return ESP_OK;
}

//==============================================================================

esp_err_t NvsNamespace::Read (const std::string& key, std::string& value) {
  LockGuard lg (*this);
  ESP_RETURN_ON_ERROR (Open(), TAG, "open failed");
  size_t valueSize;
  ESP_RETURN_ON_ERROR (nvs_get_str (handle, key.c_str(), NULL, &valueSize), TAG, "read '%s' failed", key.c_str());
  std::unique_ptr<char[]> tempValue (new char[valueSize]);
  ESP_RETURN_ON_ERROR (nvs_get_str (handle, key.c_str(), tempValue.get(), &valueSize), TAG, "read '%s' failed", key.c_str());
  value = tempValue.get();
  return ESP_OK;
}

//==============================================================================

esp_err_t NvsNamespace::Write (const std::string& key, std::string value) {
  LockGuard lg (*this);
  ESP_RETURN_ON_ERROR (Open(), TAG, "open failed");
  ESP_RETURN_ON_ERROR (nvs_set_str (handle, key.c_str(), value.c_str()), TAG, "write '%s' failed", key.c_str());
  return ESP_OK;
}

//==============================================================================

esp_err_t NvsNamespace::Read (const std::string& key, void* data, size_t maxDataSize, size_t* dataSize) {
  LockGuard lg (*this);
  ESP_RETURN_ON_ERROR (Open(), TAG, "open failed");
  esp_err_t error = nvs_get_blob (handle, key.c_str(), data, &maxDataSize);
  if (dataSize)
    *dataSize = maxDataSize;
  ESP_RETURN_ON_ERROR (error, TAG, "read '%s' failed", key.c_str());
  return ESP_OK;
}

//==============================================================================

esp_err_t NvsNamespace::Write (const std::string& key, const void* data, size_t dataSize) {
  LockGuard lg (*this);
  ESP_RETURN_ON_ERROR (Open(), TAG, "open failed");
  ESP_RETURN_ON_ERROR (nvs_set_blob (handle, key.c_str(), (const char*)data, dataSize), TAG, "write '%s' failed", key.c_str());
  return ESP_OK;
}

//==============================================================================

esp_err_t NvsNamespace::Erase (const std::string& key) {
  LockGuard lg (*this);
  ESP_RETURN_ON_ERROR (Open(), TAG, "open failed");
  ESP_RETURN_ON_ERROR (nvs_erase_key (handle, key.c_str()), TAG, "erase '%s' failed", key.c_str());
  return ESP_OK;
}

//==============================================================================

esp_err_t NvsNamespace::Erase() {
  LockGuard lg (*this);
  ESP_RETURN_ON_ERROR (Open(), TAG, "open failed");
  ESP_RETURN_ON_ERROR (nvs_erase_all (handle), TAG, "erase all failed");
  return ESP_OK;
}

//==============================================================================

esp_err_t NvsNamespace::Commit() {
  LockGuard lg (*this);
  if (!open)
    return ESP_OK;
  ESP_RETURN_ON_ERROR (nvs_commit (handle), TAG, "commit failed");
  return ESP_OK;
}

//==============================================================================

esp_err_t NvsNamespace::Open() {
  if (open)
    return ESP_OK;
  ESP_RETURN_ON_ERROR (nvs_open_from_partition (partitionName.c_str(), namespaceName.c_str(), accessMode == NvsAccessMode::readOnly ? NVS_READONLY : NVS_READWRITE, &handle),\
                       TAG, "open '%s/%s' failed", partitionName.c_str(), namespaceName.c_str());
  open = true;
  return ESP_OK;
}

//==============================================================================

}