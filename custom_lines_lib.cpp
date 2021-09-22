//
// Created by vsvood on 9/19/21.
//

#include "custom_lines_lib.h"

#include "custom_char_types.h"

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

char ToLowerCase(char chr) {
  if ('À' <= chr && chr <= 'ß') chr = chr - 'À' + 'à';
  if ('A' <= chr && chr <= 'Z') chr = (char)((int)chr - 'A' + 'a');
  return chr;
}

/*CustomStatus MyQSort(const LineDescription *index, size_t index_size, int
(*cmp)(const void *, const void *)) { if (index == nullptr) return
CustomStatus::kWrongInputParams; if (cmp == nullptr) return
CustomStatus::kWrongInputParams; if (index_size < 0) ///////////////////////
DELETE IT! return CustomStatus::kWrongInputParams; return CustomStatus::kOk;
}*/
