#pragma once

#include <cstdint>

#define LML_ERRORCODE_FAILED_TO_CREATE_APPDATA					static_cast<std::uint32_t>(0x00000001)

#define LML_ERRORCODE_FAILED_TO_OPEN_OPTION_FILE				static_cast<std::uint32_t>(0x00000010)
#define LML_ERRORCODE_FAILED_TO_CREATE_OPTION_FILE				static_cast<std::uint32_t>(0x00000011)
#define LML_ERRORCODE_FAILED_TO_OPEN_LANGUAGE_FILE				static_cast<std::uint32_t>(0x00000012)
#define LML_ERRORCODE_FAILED_TO_CREATE_LANGUAGE_FILE			static_cast<std::uint32_t>(0x00000013)

#define LML_ERRORCODE_FAILED_TO_OPEN_EXTENSION					static_cast<std::uint32_t>(0x00000020)
#define LML_ERRORCODE_ALREADY_LOADED_EXTENSION					static_cast<std::uint32_t>(0x00000021)
#define LML_ERRORCODE_FAILED_TO_LOAD_EXTENSION_ENTRYPOINT		static_cast<std::uint32_t>(0x00000022)
#define LML_ERRORCODE_FAILED_TO_CREATE_EXTENSION_INSTANCE		static_cast<std::uint32_t>(0x00000023)