#include <cstdio>
#include <cstdlib>
#include <unistd.h>

#include "custom_char_types.h"
#include "custom_file_io.h"
#include "custom_status_lib.h"

const int kMaxPathLength = 100;

CustomStatus Normalise(const char *input_buffer, long input_size, char **output_buffer, long *output_size);

int main() {
  char input_path[kMaxPathLength];
  char output_path[kMaxPathLength];

  printf("Enter input path (%d chars max):\n", kMaxPathLength);
  scanf("%s", input_path);

  char* input_buffer = nullptr;
  long input_size = 0;

  CustomStatus status;
  status = ReadFromFile(input_path, &input_buffer, &input_size);
  if (status != CustomStatus::kOk) {
    printf("Failed reading with '%s' error\n", kCustomStatusDescription[(int)status]);
    return 0;
  }

  char *output_buffer = nullptr;
  long output_size = 0;

  status = Normalise(input_buffer, input_size, &output_buffer, &output_size);
  if (status != CustomStatus::kOk) {
    printf("Failed Normalising with '%s' error\n", kCustomStatusDescription[(int)status]);
    return 0;
  }

  free(input_buffer);

  printf("Enter output path (%d chars max):\n", kMaxPathLength);
  scanf("%s", output_path);

  status = WriteToFile(output_path, output_buffer, output_size);
  if (status != CustomStatus::kOk) {
    printf("Failed writing with '%s' error\n", kCustomStatusDescription[(int)status]);
    return 0;
  }

  free(output_buffer);

  return 0;
}

CustomStatus Normalise(const char *input_buffer, const long input_size, char **output_buffer, long *output_size) {
  if (input_buffer == nullptr)
    return CustomStatus::kWrongInputParams;
  if (output_buffer == nullptr)
    return CustomStatus::kWrongOutputParams;
  if (output_size == nullptr)
    return CustomStatus::kWrongOutputParams;
  printf("Normalising...");

  *output_buffer = (char*)calloc((size_t)input_size, sizeof(char));

  int output_index = 0;

  bool possible_gap = false;
  bool line_begin = true;

  for (int input_index = 0; input_index < input_size; ++input_index) {
    char cur_chr = input_buffer[input_index];

    if (IsMeaningful(cur_chr)) {
      if (line_begin) {
        (*output_buffer)[output_index] = cur_chr;
        output_index++;
        line_begin = false;
        possible_gap = false;
      } else if (!possible_gap || cur_chr == '\n') {
        (*output_buffer)[output_index] = cur_chr;
        output_index++;
      } else {
        (*output_buffer)[output_index] = ' ';
        output_index++;
        (*output_buffer)[output_index] = cur_chr;
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
