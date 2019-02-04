#pragma once

#include <cstdint>

#define LML_ERRORCODE_FAILED_TO_GET_APPDATA						static_cast<std::uint32_t>(0x00000001)
#define LML_ERRORCODE_FAILED_TO_CREATE_APPDATA					static_cast<std::uint32_t>(0x00000002)

#define LML_ERRORCODE_FAILED_TO_OPEN_OPTION_FILE				static_cast<std::uint32_t>(0x00000010)
#define LML_ERRORCODE_FAILED_TO_CREATE_OPTION_FILE				static_cast<std::uint32_t>(0x00000011)