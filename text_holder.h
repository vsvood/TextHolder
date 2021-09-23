//
// Created by vsvood on 9/22/21.
//

#ifndef TEXTHOLDER_TEXT_HOLDER_H
#define TEXTHOLDER_TEXT_HOLDER_H

#include <cstdlib>

#include "utils.h"
#include "custom_status_lib.h"

struct TextHolder {
  LineDescription *index;
  size_t index_size;
  char *text_buffer;
  size_t text_size;

  /**
   * @brief Initialise member variables
   *
   * @param text_holder - self
   *
   * @return member of CustomStatus:\n
   * kOk - Ok func exited normally\n
   * kWrongInputParams - Wrong input params\n
   * kWrongOutputParams - Wrong output params\n
   * kRuntimeError - Something went wrong while running
   */

  static CustomStatus Ctor(TextHolder *text_holder);

  /**
   * @brief Free allocated memory
   *
   * @param[out] text_holder - self
   *
   * @return member of CustomStatus:\n
   * kOk - Ok func exited normally\n
   * kWrongInputParams - Wrong input params\n
   * kWrongOutputParams - Wrong output params\n
   * kRuntimeError - Something went wrong while running
   */

  static CustomStatus Dtor(TextHolder *text_holder);

  /**
   * @brief Load from file
   *
   * Read text_buffer from file using ReadFromFile and initialise index by calling LoadIndex
   *
   * @param[out] text_holder - self
   * @param[in] path - path to file
   *
   * @return member of CustomStatus:\n
   * kOk - Ok func exited normally\n
   * kWrongInputParams - Wrong input params\n
   * kWrongOutputParams - Wrong output params\n
   * kRuntimeError - Something went wrong while running
   */

  static CustomStatus LoadFromFile(TextHolder *text_holder, const char *path);

  /**
   * @brief Initialise index with text_buffer
   *
   * @param[out] text_holder - self
   *
   * @return member of CustomStatus:\n
   * kOk - Ok func exited normally\n
   * kWrongInputParams - Wrong input params\n
   * kWrongOutputParams - Wrong output params\n
   * kRuntimeError - Something went wrong while running
   */

  static CustomStatus LoadIndex(TextHolder *text_holder);

  /**
   * @brief Extract text from index
   *
   * Write text to buffer in order specified by index
   *
   * @param[in] text_holder - self
   * @param[out] buffer - extracted data (specified if return kOk)
   *
   * @return member of CustomStatus:\n
   * kOk - Ok func exited normally\n
   * kWrongInputParams - Wrong input params\n
   * kWrongOutputParams - Wrong output params\n
   * kRuntimeError - Something went wrong while running
   */

  static CustomStatus GetTextFromIndex(TextHolder *text_holder, char *buffer);

  /**
   * @brief Save current text state to file
   *
   * Extract text with GetTextFromIndex and write it to file using WriteToFile
   *
   * @param[in] text_holder - self
   * @param[in] path - path to file
   *
   * @return member of CustomStatus:\n
   * kOk - Ok func exited normally\n
   * kWrongInputParams - Wrong input params\n
   * kWrongOutputParams - Wrong output params\n
   * kRuntimeError - Something went wrong while running
   */

  static CustomStatus SaveToFile(TextHolder *text_holder, const char *path);

  /**
   * @brief Sort lines in text
   *
   * Sort lines in text using MyQSort with \p cmp comparator
   *
   * @param[out] text_holder - self
   * @param[in] cmp - comparator
   *
   * @return member of CustomStatus:\n
   * kOk - Ok func exited normally\n
   * kWrongInputParams - Wrong input params\n
   * kWrongOutputParams - Wrong output params\n
   * kRuntimeError - Something went wrong while running
   */

  static CustomStatus SortIndex(TextHolder *text_holder, __compar_fn_t cmp);
};

#endif  // TEXTHOLDER_TEXT_HOLDER_H
