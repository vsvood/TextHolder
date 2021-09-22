//
// Created by vsvood on 9/23/21.
//

#ifndef TEXTHOLDER_UTILS_H
#define TEXTHOLDER_UTILS_H

bool IsMeaningful(char chr);

bool IsLetter(char chr);

bool IsLatin(char chr);

bool IsCyrillic(char chr);

bool IsPunctuation(char chr);

bool IsSpecialSymbol(char chr);

struct LineDescription {
    const char *begin;
    const char *end;
};

char ToLowerCase(char chr);

int CompareLinesForward(const void *line1, const void *line2);

int CompareLinesBackward(const void *line1, const void *line2);

#endif //TEXTHOLDER_UTILS_H
