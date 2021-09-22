//
// Created by vsvood on 9/22/21.
//

#ifndef TEXTHOLDER_TEXT_HOLDER_H
#define TEXTHOLDER_TEXT_HOLDER_H

#include <cstdlib>

#include "custom_lines_lib.h"
#include "custom_status_lib.h"

struct TextHolder {
  LineDescription *index;
  size_t index_size;
  char *text_buffer;
  size_t text_size;
  static CustomStatus Dtor(TextHolder *text_holder);
  static CustomStatus LoadFromFile(TextHolder *text_holder, const char *path);
  static CustomStatus LoadIndex(TextHolder *text_holder);
  static CustomStatus GetTextFromIndex(TextHolder *text_holder, char *buffer);
  static CustomStatus SaveToFile(TextHolder *text_holder, const char *path);
  static CustomStatus SortIndex(TextHolder *text_holder, __compar_fn_t cmp);
};

#endif  // TEXTHOLDER_TEXT_HOLDER_H
