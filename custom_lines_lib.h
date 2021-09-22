//
// Created by vsvood on 9/19/21.
//

#ifndef TEXTHOLDER_CUSTOM_LINES_LIB_H
#define TEXTHOLDER_CUSTOM_LINES_LIB_H

#include <cstdlib>

#include "custom_status_lib.h"

struct LineDescription {
  const char *begin;
  const char *end;
};

char ToLowerCase(char chr);

int CompareLinesForward(const void *line1, const void *line2);

int CompareLinesBackward(const void *line1, const void *line2);

CustomStatus MyQSort(const LineDescription *index, long index_size,
                     int (*cmp)(const void *, const void *));

#endif  // TEXTHOLDER_CUSTOM_LINES_LIB_H
