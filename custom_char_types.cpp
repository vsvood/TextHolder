//
// Created by vsvood on 9/19/21.
//

#include "custom_char_types.h"

bool IsMeaningful(char chr) {
  return IsCyrillic(chr) || IsLatin(chr) ||
         IsPunctuation(chr) || IsSpecialSymbol(chr);
}

bool IsSpecialSymbol(char chr) {
  const char special_list[] = "\n";
  for (char s_chr : special_list) {
    if (chr == s_chr) return true;
  }
  return false;
}

bool IsPunctuation(char chr) {
  const char punctuation_list[] = ".,!?:;-'`\"";
  for (char p_chr : punctuation_list) {
    if (chr == p_chr) return true;
  }
  return false;
}

bool IsLatin(char chr) {
  return (('a' <= chr) && (chr <= 'z')) || (('A' <= chr) && (chr <= 'Z'));
}

bool IsCyrillic(char chr) {
  return (('à' <= chr) && (chr <= 'ÿ')) || (('À' <= chr) && (chr <= 'ß'));
}

bool IsLetter(char chr) {
  return IsCyrillic(chr) || IsLatin(chr);
}
