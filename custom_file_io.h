//
// Created by vsvood on 9/19/21.
//

#ifndef TEXTHOLDER_CUSTOM_FILE_IO_H
#define TEXTHOLDER_CUSTOM_FILE_IO_H

#include <cstddef>

#include "custom_status_lib.h"

/**
 * @brief get size of specified file
 *
 * @param[in] path - path to file
 * @param[out] size - size of file (specified if return kOk)
 *
 * @return member of CustomStatus:\n
 * kOk - Ok func exited normally\n
 * kWrongInputParams - Wrong input params\n
 * kWrongOutputParams - Wrong output params\n
 * kRuntimeError - Something went wrong while running
 */

CustomStatus GetFileSize(const char *path, size_t *size);

/**
 * @brief Check if input file is valid
 *
 * @param[in] path - path to file
 *
 * @return member of CustomStatus:\n
 * kOk - Ok func exited normally\n
 * kWrongInputParams - Wrong input params\n
 * kWrongOutputParams - Wrong output params\n
 * kRuntimeError - Something went wrong while running
 */

CustomStatus CheckInputFile(const char *path);

/**
 * @brief Check if output file is valid
 *
 * If file don`t exists you will be suggested to create it
 *
 * @param[in] path - path to file
 *
 * @return member of CustomStatus:\n
 * kOk - Ok func exited normally\n
 * kWrongInputParams - Wrong input params\n
 * kWrongOutputParams - Wrong output params\n
 * kRuntimeError - Something went wrong while running
 */

CustomStatus CheckOutputFile(const char *path);

/**
 * @brief Proxy for read function
 *
 * Read from file to buffer
 *
 * @param[in] path - path to file
 * @param[out] buffer - data from file (specified if return kOk)
 * @param[in,out] size - max number of bytes to read (input)\n
 * how many bytes was read indeed (output, specified if return kOk)
 *
 * @return member of CustomStatus:\n
 * kOk - Ok func exited normally\n
 * kWrongInputParams - Wrong input params\n
 * kWrongOutputParams - Wrong output params\n
 * kRuntimeError - Something went wrong while running
 */

CustomStatus ReadFromFile(const char *path, char *buffer, size_t *size);

/**
 * @brief Proxy for write function
 *
 * Write from buffer to file
 *
 * @param[in] path - path to file
 * @param[in] buffer - data to write
 * @param[in] size - size of buffer
 *
 * @return member of CustomStatus:\n
 * kOk - Ok func exited normally\n
 * kWrongInputParams - Wrong input params\n
 * kWrongOutputParams - Wrong output params\n
 * kRuntimeError - Something went wrong while running
 */

CustomStatus WriteToFile(const char *path, const char *buffer, size_t size);

#endif  // TEXTHOLDER_CUSTOM_FILE_IO_H
