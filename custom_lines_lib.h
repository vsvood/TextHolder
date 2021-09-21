//
// Created by vsvood on 9/19/21.
//

#ifndef TEXTHOLDER_CUSTOM_LINES_LIB_H
#define TEXTHOLDER_CUSTOM_LINES_LIB_H

#include "custom_status_lib.h"

struct LineDescription {
    LineDescription();
    const char* begin;
    const char* end;
};

int CompareLinesForward(const LineDescription* line_1,
                        const LineDescription* line_2);

int CompareLinesBackward(const LineDescription* line_1,
                         const LineDescription* line_2);

CustomStatus MyQSort(const LineDescription *index, long index_size,
                     int(* cmp)(const LineDescription*,
                                     const LineDescription*));

#endif //TEXTHOLDER_CUSTOM_LINES_LIB_H
