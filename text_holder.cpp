#include <cstdio>
#include <cstdlib>

#include "custom_file_io.h"
#include "custom_lines_lib.h"
#include "custom_status_lib.h"

const int kMaxPathLength = 100;

CustomStatus CreateIndex(const char *buffer,
                         long size,
                         LineDescription *index[],
                         long *index_size);

CustomStatus GetTextFromIndex(const LineDescription *index,
                              long index_size,
                              long source_size,
                              char **buffer,
                              long *buffer_size);

int main() {
  char input_path[kMaxPathLength];

  printf("Enter input path (%d chars max):\n", kMaxPathLength);
  scanf("%s", input_path);

  char *input_buffer = nullptr;
  long input_size = 0;
  CustomStatus status = ReadFromFile(input_path, &input_buffer, &input_size);
  if (status != CustomStatus::kOk) {
    printf("Failed reading with '%s' error\n",
           kCustomStatusDescription[(int)status]);
    return 0;
  }

  LineDescription *index = nullptr;
  long index_size = 0;
  status = CreateIndex(input_buffer, input_size, &index, &index_size);
  if (status != CustomStatus::kOk) {
    printf("Failed creating index with '%s' error\n",
           kCustomStatusDescription[(int)status]);
    return 0;
  }

  printf("Sorting forward...");
  qsort(index, (size_t) index_size, sizeof(LineDescription),
        (__compar_fn_t) CompareLinesForward);
  printf("OK\n");

  char output_path[kMaxPathLength];
  printf("Enter output path for forward sorting (%d chars max):\n",
         kMaxPathLength);
  scanf("%s", output_path);

  char *output_buffer = nullptr;
  long output_size = 0;
  status = GetTextFromIndex(index, index_size, input_size,
                            &output_buffer,&output_size);
  if (status != CustomStatus::kOk) {
    printf("Failed getting text from index with '%s' error\n",
           kCustomStatusDescription[(int)status]);
    return 0;
  }

  status = WriteToFile(output_path, output_buffer, output_size);
  if (status != CustomStatus::kOk) {
    printf("Failed writing with '%s' error\n",
           kCustomStatusDescription[(int)status]);
    return 0;
  }

  printf("Backward sorting...");
  qsort(index, (size_t) index_size, sizeof(LineDescription),
        (__compar_fn_t) CompareLinesBackward);
  printf("OK\n");

  printf("Enter output path for backward sorting (%d chars max):\n",
         kMaxPathLength);
  scanf("%s", output_path);

  status = GetTextFromIndex(index, index_size, input_size,
                            &output_buffer, &output_size);
  if (status != CustomStatus::kOk) {
    printf("Failed getting text from index with '%s' error\n",
           kCustomStatusDescription[(int)status]);
    return 0;
  }

  status = WriteToFile(output_path, output_buffer, output_size);
  if (status != CustomStatus::kOk) {
    printf("Failed writing with '%s' error\n",
           kCustomStatusDescription[(int)status]);
    return 0;
  }

  printf("Enter output path for original text (%d chars max):\n",
         kMaxPathLength);
  scanf("%s", output_path);

  status = WriteToFile(output_path, input_buffer, input_size);
  if (status != CustomStatus::kOk) {
    printf("Failed writing with '%s' error\n",
           kCustomStatusDescription[(int)status]);
    return 0;
  }

  if (output_buffer != nullptr)
    free(output_buffer);
  if (index != nullptr)
    free(index);
  if (input_buffer != nullptr)
    free(input_buffer);

  return 0;
}

CustomStatus GetTextFromIndex(const LineDescription *index,
                              const long index_size,
                              const long source_size,
                              char **buffer,
                              long *buffer_size) {
  if (index == nullptr)
    return CustomStatus::kWrongInputParams;
  if (buffer == nullptr)
    return CustomStatus::kWrongOutputParams;
  if (buffer_size == nullptr)
    return CustomStatus::kWrongOutputParams;

  *buffer_size = source_size;
  if (*buffer != nullptr)
    free(*buffer);
  *buffer = (char *)(calloc((size_t)*buffer_size, sizeof(char)));

  char *buff_ptr = *buffer;
  for (int i = 0; i < index_size; ++i) {
    for (const char *src_ptr = index[i].begin; src_ptr <= index[i].end; ++src_ptr) {
      *buff_ptr = *src_ptr;
      ++buff_ptr;
    }
  }

  return CustomStatus::kOk;
}

CustomStatus CreateIndex(const char *buffer,
                         const long size, LineDescription *index[],
                         long *index_size) {
  if (buffer == nullptr)
    return CustomStatus::kWrongInputParams;
  if (index == nullptr)
    return CustomStatus::kWrongOutputParams;
  if (index_size == nullptr)
    return CustomStatus::kWrongOutputParams;
  printf("Indexing...");

  int lines_count = 1;

  for (int i = 0; i < size-1; ++i) {
    if (buffer[i] == '\n') lines_count++;
  }

  if (*index != nullptr)
    free(*index);
  *index = (LineDescription*)calloc((size_t)lines_count,
                                    sizeof(LineDescription));
  (*index)[0].begin = buffer;

  *index_size = 1;

  for (int i = 0; i < size-1; ++i) {
    if (buffer[i] == '\n') {
      (*index)[*index_size].begin = &buffer[i+1];
      (*index)[*index_size-1].end = &buffer[i];
      (*index_size)++;
    }
  }
  (*index)[lines_count-1].end = &buffer[size-1];

  printf("OK\n");

  return CustomStatus::kOk;
}
