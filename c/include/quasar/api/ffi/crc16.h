#pragma once

#include <quasar/api/ffi/detail/definitions.h>

QUASAR_C_API_BEGIN

/**
 * @brief Calculates the CRC16 checksum of the given data.
 * @details Uses Modbus CRC16 algorithm (CRC-16-ANSI), polynomial `0xA001`.
 * @param data Pointer to the data buffer.
 * @param len Length of the data buffer.
 * @return The calculated CRC16 checksum as a 16-bit unsigned integer.
 * @note If `data` is `NULL` or `len` is `0`, the function returns `0`.
 */
QUASAR_C_API uint16_t quasar_crc16(uint8_t const* data, size_t len);

/**
 * @brief Calculates the CRC16-CCITT checksum of the given data.
 * @details Uses CRC-16-CCITT algorithm, polynomial `0x1021`.
 * @param data Pointer to the data buffer.
 * @param len Length of the data buffer.
 * @return The calculated CRC16-CCITT checksum as a 16-bit unsigned integer.
 * @note If `data` is `NULL` or `len` is `0`, the function returns `0`.
 */
QUASAR_C_API uint16_t quasar_crc16_ccitt(uint8_t const* data, size_t len);

QUASAR_C_API uint16_t quasar_byteswap16(uint16_t value);

QUASAR_C_API_END