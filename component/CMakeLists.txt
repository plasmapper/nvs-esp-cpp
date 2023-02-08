cmake_minimum_required(VERSION 3.5)

idf_component_register(SRCS "pl_nvs_namespace.cpp" INCLUDE_DIRS "include" REQUIRES "nvs_flash" "pl_common")