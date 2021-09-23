//
// Created by vsvood on 9/23/21.
//

#ifndef TEXTHOLDER_UTILS_H
#define TEXTHOLDER_UTILS_H

#include <cstddef>
#include <cstdlib>

#include "custom_status_lib.h"

struct LineDescription {
    const char *begin;
    const char *end;
};

bool IsMeaningful(char chr);

bool IsLetter(char chr);

bool IsLatin(char chr);

bool IsCyrillic(char chr);

bool IsPunctuation(char chr);

bool IsSpecialSymbol(char chr);

char ToLowerCase(char chr);

int CompareLinesForward(const void *line1, const void *line2);

int CompareLinesBackward(const void *line1, const void *line2);

CustomStatus
Partition(LineDescription *index, size_t n_elem, size_t *partition_index, __compar_fn_t cmp);

CustomStatus MyQSort(LineDescription *index, size_t n_elem, __compar_fn_t cmp);

#endif //TEXTHOLDER_UTILS_H
