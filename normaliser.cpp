#include <cstdio>
#include <cstdlib>

#include "text_holder/src/utils.h"
#include "text_holder/custom_file_io/include/custom_file_io.h"
#include "text_holder/include/custom_status.h"

const int kMaxPathLength = 100;

CustomStatus Normalise(const char *input_buffer, size_t input_size,
                       char *output_buffer, size_t *output_size);

int main() {
  char input_path[kMaxPathLength];
  char output_path[kMaxPathLength];

  printf("Enter input path (%d chars max):\n", kMaxPathLength);
  scanf("%s", input_path);

  size_t input_size = 0;
  CustomStatus status = GetFileSize(input_path, &input_size);
  if (status != CustomStatus::kOk) {
    printf("\nFailed getting file size with '%s' error\n",
           kCustomStatusDescription[(int)status]);
    return 1;
  }

  char *tmp = (char *)calloc(input_size, sizeof(char));
  if (tmp == nullptr) {
    printf("\nFailed allocating memory for input buffer\n");
    return 2;
  }
  char *input_buffer = tmp;

  status = ReadFromFile(input_path, input_buffer, &input_size);
  if (status != CustomStatus::kOk) {
    printf("Failed reading with '%s' error\n",
           kCustomStatusDescription[(int)status]);
    return 3;
  }

  tmp = (char *)calloc(input_size, sizeof(char));
  if (tmp == nullptr) {
    printf("\nFailed allocating memory for output buffer\n");
    return 4;
  }
  char *output_buffer = tmp;
  size_t output_size = 0;

  status = Normalise(input_buffer, input_size, output_buffer, &output_size);
  if (status != CustomStatus::kOk) {
    printf("Failed Normalising with '%s' error\n",
           kCustomStatusDescription[(int)status]);
    return 5;
  }

  free(input_buffer);

  printf("Enter output path (%d chars max):\n", kMaxPathLength);
  scanf("%s", output_path);

  status = WriteToFile(output_path, output_buffer, output_size);
  if (status != CustomStatus::kOk) {
    printf("Failed writing with '%s' error\n",
           kCustomStatusDescription[(int)status]);
    return 0;
  }

  free(output_buffer);

  return 0;
}

CustomStatus Normalise(const char *input_buffer, const size_t input_size,
                       char *output_buffer, size_t *output_size) {
  if (input_buffer == nullptr) return CustomStatus::kWrongInputParams;
  if (output_buffer == nullptr) return CustomStatus::kWrongOutputParams;
  if (output_size == nullptr) return CustomStatus::kWrongOutputParams;

  size_t output_index = 0;
  bool possible_gap = false;
  bool line_begin = true;

  for (size_t input_index = 0; input_index < input_size; ++input_index) {
    char cur_chr = input_buffer[input_index];

    if (IsMeaningful(cur_chr)) {
      if (line_begin) {
        output_buffer[output_index] = cur_chr;
        output_index++;
        line_begin = false;
        possible_gap = false;
      } else if (!possible_gap || cur_chr == '\n') {
        output_buffer[output_index] = cur_chr;
        output_index++;
      } else {
        output_buffer[output_index] = ' ';
        output_index++;
        output_buffer[output_index] = cur_chr;
        output_index++;
        possible_gap = false;
      }
      if (cur_chr == '\n') line_begin = true;
    } else {
      possible_gap = true;
    }
  }
  *output_size = output_index;
  printf("OK\n");
  return CustomStatus::kOk;
}
