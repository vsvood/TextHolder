//
// Created by vsvood on 9/19/21.
//

#ifndef TEXTHOLDER_CUSTOM_FILE_IO_H
#define TEXTHOLDER_CUSTOM_FILE_IO_H

#include <cstddef>

#include "custom_status.h"

CustomStatus GetFileSize(const char *path, size_t *size);

CustomStatus CheckInputFile(const char *path);

CustomStatus CheckOutputFile(const char *path);

CustomStatus ReadFromFile(const char *path, char *buffer, size_t *size);

CustomStatus WriteToFile(const char *path, const char *buffer, size_t size);

#endif  // TEXTHOLDER_CUSTOM_FILE_IO_H
