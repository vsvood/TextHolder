//
// Created by vsvood on 9/22/21.
//

#include "text_holder.h"

#include <cstdio>
#include <cstdlib>

#include "custom_file_io.h"
#include "custom_lines_lib.h"
#include "custom_status_lib.h"

CustomStatus TextHolder::LoadFromFile(TextHolder *text_holder,
                                      const char *path) {
  if (path == nullptr) {
    return CustomStatus::kWrongInputParams;
  }
  if (text_holder == nullptr) {
    return CustomStatus::kWrongOutputParams;
  }

  CustomStatus status = GetFileSize(path, &(text_holder->text_size));
  if (status != CustomStatus::kOk) {
    printf("Failed getting file size with '%s' error\n",
           kCustomStatusDescription[(int)status]);
    return status;
  }

  char *tmp = (char *)calloc(text_holder->text_size, sizeof(char));
  if (tmp == nullptr) {
    return CustomStatus::kRuntimeError;
  }
  text_holder->text_buffer = tmp;

  status =
      ReadFromFile(path, text_holder->text_buffer, &(text_holder->text_size));
  if (status != CustomStatus::kOk) {
    printf("Failed reading with '%s' error\n",
           kCustomStatusDescription[(int)status]);
    return status;
  }

  status = TextHolder::LoadIndex(text_holder);
  if (status != CustomStatus::kOk) {
    printf("Failed loading index with '%s' error\n",
           kCustomStatusDescription[(int)status]);
    return status;
  }

  return CustomStatus::kOk;
}

CustomStatus TextHolder::LoadIndex(TextHolder *text_holder) {
  if ((text_holder == nullptr) || (text_holder->text_buffer == nullptr)) {
    return CustomStatus::kWrongInputParams;
  }

  size_t lines_count = 1;
  for (size_t i = 0; i < text_holder->text_size - 1; ++i) {
    if (text_holder->text_buffer[i] == '\n') {
      lines_count++;
    }
  }

  if (text_holder->index != nullptr) {
    free(text_holder->index);
  }
  LineDescription *tmp =
      (LineDescription *)calloc(lines_count, sizeof(LineDescription));
  if (tmp == nullptr) {
    return CustomStatus::kRuntimeError;
  }
  text_holder->index = tmp;
  text_holder->index[0].begin = text_holder->text_buffer;
  text_holder->index_size = 1;

  for (size_t i = 0; i < text_holder->text_size - 1; ++i) {
    if (text_holder->text_buffer[i] == '\n') {
      text_holder->index[text_holder->index_size].begin =
          &text_holder->text_buffer[i + 1];
      text_holder->index[text_holder->index_size - 1].end =
          &text_holder->text_buffer[i];
      text_holder->index_size++;
    }
  }
  text_holder->index[text_holder->index_size - 1].end =
      &text_holder->text_buffer[text_holder->text_size - 1];

  return CustomStatus::kOk;
}

CustomStatus TextHolder::SortIndex(TextHolder *text_holder, __compar_fn_t cmp) {
  if ((text_holder == nullptr) || (cmp == nullptr)) {
    return CustomStatus::kWrongInputParams;
  }

  qsort(text_holder->index, text_holder->index_size, sizeof(LineDescription),
        cmp);

  return CustomStatus::kOk;
}

CustomStatus TextHolder::SaveToFile(TextHolder *text_holder, const char *path) {
  if ((text_holder == nullptr) || (path == nullptr)) {
    return CustomStatus::kWrongInputParams;
  }

  char *tmp = (char *)calloc(text_holder->text_size, sizeof(char));
  if (tmp == nullptr) {
    return CustomStatus::kRuntimeError;
  }
  char *output_buffer = tmp;
  CustomStatus status =
      TextHolder::GetTextFromIndex(text_holder, output_buffer);
  if (status != CustomStatus::kOk) {
    printf("Failed getting text from index with '%s' error\n",
           kCustomStatusDescription[(int)status]);
    return status;
  }

  status = WriteToFile(path, output_buffer, text_holder->text_size);
  if (status != CustomStatus::kOk) {
    printf("Failed writing with '%s' error\n",
           kCustomStatusDescription[(int)status]);
    return status;
  }

  free(output_buffer);

  return CustomStatus::kOk;
}

CustomStatus TextHolder::GetTextFromIndex(TextHolder *text_holder,
                                          char *buffer) {
  if ((text_holder == nullptr) || (text_holder->index == nullptr) ||
      (buffer == nullptr)) {
    return CustomStatus::kWrongInputParams;
  }

  char *buff_ptr = buffer;
  for (size_t i = 0; i < text_holder->index_size; ++i) {
    for (const char *src_ptr = text_holder->index[i].begin;
         src_ptr <= text_holder->index[i].end; ++src_ptr) {
      *buff_ptr = *src_ptr;
      ++buff_ptr;
    }
  }

  return CustomStatus::kOk;
}

CustomStatus TextHolder::Dtor(TextHolder *text_holder) {
  if (text_holder == nullptr) {
    return CustomStatus::kWrongInputParams;
  }

  free(text_holder->index);
  free(text_holder->text_buffer);

  return CustomStatus::kOk;
}
