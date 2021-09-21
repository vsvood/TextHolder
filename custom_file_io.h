//
// Created by vsvood on 9/19/21.
//

#ifndef TEXTHOLDER_CUSTOM_FILE_IO_H
#define TEXTHOLDER_CUSTOM_FILE_IO_H

#include <X11/Xlib.h>
#include "custom_status_lib.h"

CustomStatus CheckInputFile(const char *path);

CustomStatus CheckOutputFile(const char *path);

CustomStatus ReadFromFile(const char *path, char **buffer, long *size);

CustomStatus WriteToFile(const char *path, const char *buffer, long size);

#endif //TEXTHOLDER_CUSTOM_FILE_IO_H