//
// Created by vsvood on 9/19/21.
//

#include "custom_lines_lib.h"
#include "custom_char_types.h"

LineDescription::LineDescription() : begin(nullptr), end(nullptr) {}

int CompareLinesForward(const LineDescription *line_1,
                        const LineDescription *line_2) {
  const char* pointer_1 = line_1->begin;
  const char* pointer_2 = line_2->begin;
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

    if ('à' <= letter_1 && letter_1 <= 'ÿ')
      letter_1 -= 'à' - 'À';
    if ('à' <= letter_2 && letter_2 <= 'ÿ')
      letter_2 -= 'à' - 'À';
    if ('a' <= letter_1 && letter_1 <= 'z')
      letter_1 -= 'a' - 'A';
    if ('a' <= letter_2 && letter_2 <= 'z')
      letter_2 -= 'a' - 'A';

    if (letter_1 < letter_2)
      return -1;
    if (letter_1 > letter_2)
      return 1;
    ++pointer_1;
    ++pointer_2;
  }
  return 0;
}

int CompareLinesBackward(const LineDescription *line_1,
                         const LineDescription *line_2) {
  const char* pointer_1 = line_1->end-1;
  const char* pointer_2 = line_2->end-1;
  while (pointer_1 >= line_1->begin && pointer_2>= line_2->begin) {
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

    if ('à' <= letter_1 && letter_1 <= 'ÿ')
      letter_1 -= 'à' - 'À';
    if ('à' <= letter_2 && letter_2 <= 'ÿ')
      letter_2 -= 'à' - 'À';
    if ('a' <= letter_1 && letter_1 <= 'z')
      letter_1 -= 'a' - 'A';
    if ('a' <= letter_2 && letter_2 <= 'z')
      letter_2 -= 'a' - 'A';

    if (letter_1 < letter_2)
      return -1;
    if (letter_1 > letter_2)
      return 1;
    --pointer_1;
    --pointer_2;
  }
  return (int)((pointer_1 - line_1->begin) - (pointer_2 - line_2->begin));
}

CustomStatus MyQSort(const LineDescription *index, const long index_size,
                     int (*const cmp)(const LineDescription *, const LineDescription *)) {
  if (index == nullptr)
    return CustomStatus::kWrongInputParams;
  if (cmp == nullptr)
    return CustomStatus::kWrongInputParams;
  if (index_size < 0)
    return CustomStatus::kWrongInputParams;
  return CustomStatus::kOk;
}
