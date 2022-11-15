#pragma once
#include "pl_common.h"
#include "pl_nvs_types.h"
#include "nvs.h"

//==============================================================================

namespace PL {

//==============================================================================

/// @brief NVS namespace class
class NvsNamespace : public Lockable {
public:
  /// @brief Create an NVS namespace
  /// @param partitionName partition name
  /// @param namespaceName namespace name
  /// @param accessMode access mode
  NvsNamespace (const std::string& partitionName, const std::string& namespaceName, NvsAccessMode accessMode);

  /// @brief Create an NVS namespace in the default NVS partition
  /// @param namespaceName namespace name
  /// @param accessMode access mode
  NvsNamespace (const std::string& namespaceName, NvsAccessMode accessMode);
  ~NvsNamespace();
  NvsNamespace (const NvsNamespace&) = delete;
  NvsNamespace& operator= (const NvsNamespace&) = delete;

  esp_err_t Lock (TickType_t timeout = portMAX_DELAY) override;
  esp_err_t Unlock() override;

  /// @brief Read the U8 value 
  /// @param key key
  /// @param value value
  /// @return error code
  esp_err_t Read (const std::string& key, uint8_t& value);

  /// @brief Write the U8 value 
  /// @param key key
  /// @param value value
  /// @return error code
  esp_err_t Write (const std::string& key, uint8_t value);

  /// @brief Read the I8 value 
  esp_err_t Read (const std::string& key, int8_t& value);
  /// @brief Write the I8 value 
  esp_err_t Write (const std::string& key, int8_t value);

  /// @brief Read the U16 value 
  esp_err_t Read (const std::string& key, uint16_t& value);
  /// @brief Write the U16 value 
  esp_err_t Write (const std::string& key, uint16_t value);

  /// @brief Read the I16 value 
  esp_err_t Read (const std::string& key, int16_t& value);
  /// @brief Write the I16 value 
  esp_err_t Write (const std::string& key, int16_t value);

  /// @brief Read the U32 value 
  esp_err_t Read (const std::string& key, uint32_t& value);
  /// @brief Write the U32 value 
  esp_err_t Write (const std::string& key, uint32_t value);

  /// @brief Read the I32 value 
  esp_err_t Read (const std::string& key, int32_t& value);
  /// @brief Write the I32 value 
  esp_err_t Write (const std::string& key, int32_t value);

  /// @brief Read the U64 value 
  esp_err_t Read (const std::string& key, uint64_t& value);
  /// @brief Write the U64 value 
  esp_err_t Write (const std::string& key, uint64_t value);

  /// @brief Read the I64 value 
  esp_err_t Read (const std::string& key, int64_t& value);
  /// @brief Write the I64 value 
  esp_err_t Write (const std::string& key, int64_t value);

  /// @brief Read the string 
  esp_err_t Read (const std::string& key, std::string& value);
  /// @brief Write the string 
  esp_err_t Write (const std::string& key, std::string value);

  /// @brief Read the blob
  /// @param key key
  /// @param data data 
  /// @param maxDataSize maximum data size
  /// @param dataSize data size
  /// @return error code
  esp_err_t Read (const std::string& key, void* data, size_t maxDataSize, size_t* dataSize);

  /// @brief Write the bob
  /// @param key key
  /// @param data data 
  /// @param dataSize data size
  /// @return error code
  esp_err_t Write (const std::string& key, const void* data, size_t dataSize);

  /// @brief Erase the value
  /// @param key key
  /// @return error code
  esp_err_t Erase (const std::string& key);

  /// @brief Erase all values
  /// @return error code
  esp_err_t Erase();

  /// @brief Write any pending changes to the NVS
  /// @return error code
  esp_err_t Commit();

private:
  Mutex mutex;
  std::string partitionName;
  std::string namespaceName;
  NvsAccessMode accessMode;
  nvs_handle handle;
  bool open = false;

  esp_err_t Open();
};

//==============================================================================

}