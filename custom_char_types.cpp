//
// Created by vsvood on 9/19/21.
//

#include "custom_char_types.h"

bool IsMeaningful(char chr) {
  return IsCyrillic(chr) || IsLatin(chr) || IsPunctuation(chr) ||
         IsSpecialSymbol(chr);
}

bool IsSpecialSymbol(char chr) {
  const int kListSize = 1;
  const char kList[kListSize] = {'\n'};
  for (int i = 0; i < kListSize; ++i) {
    if (chr == kList[i]) return true;
  }
  return false;
}

bool IsPunctuation(char chr) {
  const int kListSize = 10;
  const char kList[kListSize] = {
    '.', ',', '?', '!', ':',
    ';', '-', '\'', '`', '\"'
  };
  for (int i = 0; i < kListSize; ++i) {
    if (chr == kList[i]) return true;
  }
  return false;
}

bool IsLatin(char chr) {
  return (('a' <= chr) && (chr <= 'z')) || (('A' <= chr) && (chr <= 'Z'));
}

bool IsCyrillic(char chr) {
  return (('à' <= chr) && (chr <= 'ÿ')) || (('À' <= chr) && (chr <= 'ß'));
}

bool IsLetter(char chr) { return IsCyrillic(chr) || IsLatin(chr); }
