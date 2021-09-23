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

/**
 * @brief Check if character has meaning
 *
 * Check if character is letter or punctuation or special symbol
 *
 * @param[in] chr - character to check
 *
 * @return true - character has meaning, false - otherwise
 */

bool IsMeaningful(char chr);

/**
 * @brief Check if character is letter
 *
 * @param[in] chr - character to check
 *
 * @return true - character is letter, false - otherwise
 */

bool IsLetter(char chr);

/**
 * @brief Check if character is latin letter
 *
 * @param[in] chr - character to check
 *
 * @return true - character is latin letter, false - otherwise
 */

bool IsLatin(char chr);

/**
 * @brief Check if character is cyrillic letter
 *
 * @param[in] chr - character to check
 *
 * @return true - character is cyrillic letter, false - otherwise
 */

bool IsCyrillic(char chr);

/**
 * @brief Check if character is punctuation
 *
 * @param[in] chr - character to check
 *
 * @return true - character is punctuation, false - otherwise
 */

bool IsPunctuation(char chr);

/**
 * @brief Check if character is special symbol
 *
 * @param[in] chr - character to check
 *
 * @return true - character is special symbol, false - otherwise
 */

bool IsSpecialSymbol(char chr);

/**
 * @brief Convert character to lowercase
 *
 * If character is letter convert it to lowercase. Otherwise return without
 * changes
 *
 * @param[in] chr - character to convert
 *
 * @return converted character
 */

char ToLowerCase(char chr);

/**
 * @brief Compare lines in lexicographic order
 *
 * @param[in] line1 - 1st line
 * @param[in] line2 - 2nd line
 *
 * @return -1 - 1st line is lexicographically smaller then 2nd line\n
 * 0 - lines are equal\n
 * 1 - 1st line is lexicographically bigger then 2nd line
 */

int CompareLinesForward(const void *line1, const void *line2);

/**
 * @brief Compare lines in lexicographic order starting from line end
 *
 * @param[in] line1 - 1st line
 * @param[in] line2 - 2nd line
 *
 * @return -1 - 1st line is lexicographically smaller then 2nd line\n
 * 0 - lines are equal\n
 * 1 - 1st line is lexicographically bigger then 2nd line
 */

int CompareLinesBackward(const void *line1, const void *line2);

/**
 * @brief Partition func for MyQsort
 *
 * @param[in,out] index - pointer for beginning of partition area
 * @param[in] n_elem - length of partition area
 * @param[out] partition_index - splitting index for next iteration
 * @param cmp - comparator
 *
 * @return member of CustomStatus:\n
 * kOk - Ok func exited normally\n
 * kWrongInputParams - Wrong input params\n
 * kWrongOutputParams - Wrong output params\n
 * kRuntimeError - Something went wrong while running
 */

CustomStatus Partition(LineDescription *index, size_t n_elem,
                       size_t *partition_index, __compar_fn_t cmp);

/**
 * @brief Custom qsort function
 *
 * Custom qsort function working with standard comparators
 *
 * @param[in, out] index - pointer for beginning of sorting area
 * @param n_elem - length of sorting area
 * @param cmp - comparator
 *
 * @return member of CustomStatus:\n
 * kOk - Ok func exited normally\n
 * kWrongInputParams - Wrong input params\n
 * kWrongOutputParams - Wrong output params\n
 * kRuntimeError - Something went wrong while running
 */

CustomStatus MyQSort(LineDescription *index, size_t n_elem, __compar_fn_t cmp);

#endif  // TEXTHOLDER_UTILS_H
