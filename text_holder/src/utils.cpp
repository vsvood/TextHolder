//
// Created by vsvood on 9/23/21.
//

#include "utils.h"

bool IsCyrillic(char chr) {
  return (('à' <= chr) && (chr <= 'ÿ')) || (('À' <= chr) && (chr <= 'ß'));
}

bool IsLatin(char chr) {
  return (('a' <= chr) && (chr <= 'z')) || (('A' <= chr) && (chr <= 'Z'));
}

bool IsLetter(char chr) { return IsCyrillic(chr) || IsLatin(chr); }

bool IsMeaningful(char chr) {
  return IsCyrillic(chr) || IsLatin(chr) || IsPunctuation(chr) ||
         IsSpecialSymbol(chr);
}

bool IsPunctuation(char chr) {
  const int kListSize = 10;
  const char kList[kListSize] = {'.', ',', '?',  '!', ':',
                                 ';', '-', '\'', '`', '\"'};
  for (int i = 0; i < kListSize; ++i) {
    if (chr == kList[i]) return true;
  }
  return false;
}

bool IsSpecialSymbol(char chr) {
  const int kListSize = 1;
  const char kList[kListSize] = {'\n'};
  for (int i = 0; i < kListSize; ++i) {
    if (chr == kList[i]) return true;
  }
  return false;
}

char ToLowerCase(char chr) {
  if ('À' <= chr && chr <= 'ß') chr = chr - 'À' + 'à';
  if ('A' <= chr && chr <= 'Z') chr = (char)((int)chr - 'A' + 'a');
  return chr;
}

int CompareLinesForward(const void *line1, const void *line2) {
  const LineDescription *line_1 = (const LineDescription *)line1;
  const LineDescription *line_2 = (const LineDescription *)line2;
  const char *pointer_1 = line_1->begin;
  const char *pointer_2 = line_2->begin;

  while (pointer_1 <= line_1->end && pointer_2 <= line_2->end) {
    char letter_1 = *pointer_1;
    char letter_2 = *pointer_2;
    if (!(IsLetter(letter_1) || IsSpecialSymbol(letter_1))) {
      ++pointer_1;
      continue;
    }
    if (!(IsLetter(letter_2) || IsSpecialSymbol(letter_2))) {
      ++pointer_2;
      continue;
    }

    letter_1 = ToLowerCase(letter_1);
    letter_2 = ToLowerCase(letter_2);

    if (letter_1 < letter_2) {
      return -1;
    }
    if (letter_1 > letter_2) {
      return 1;
    }

    ++pointer_1, ++pointer_2;
  }
  return 0;
}

int CompareLinesBackward(const void *line1, const void *line2) {
  const LineDescription *line_1 = (const LineDescription *)line1;
  const LineDescription *line_2 = (const LineDescription *)line2;
  const char *pointer_1 = line_1->end - 1;
  const char *pointer_2 = line_2->end - 1;

  while (pointer_1 >= line_1->begin && pointer_2 >= line_2->begin) {
    char letter_1 = *pointer_1;
    char letter_2 = *pointer_2;
    if (!(IsLetter(letter_1) || IsSpecialSymbol(letter_1))) {
      --pointer_1;
      continue;
    }
    if (!(IsLetter(letter_2) || IsSpecialSymbol(letter_2))) {
      --pointer_2;
      continue;
    }

    letter_1 = ToLowerCase(letter_1);
    letter_2 = ToLowerCase(letter_2);

    if (letter_1 < letter_2) {
      return -1;
    }
    if (letter_1 > letter_2) {
      return 1;
    }

    --pointer_1, --pointer_2;
  }
  return (int)((pointer_1 - line_1->begin) - (pointer_2 - line_2->begin));
}
