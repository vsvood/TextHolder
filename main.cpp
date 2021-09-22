//
// Created by vsvood on 9/22/21.
//
#include <cstdio>

#include "custom_file_io.h"
#include "custom_status_lib.h"
#include "text_holder.h"
#include "utils.h"

const int kMaxPathLength = 101;

int main() {
  char input_path[kMaxPathLength] = {};
  printf("Enter input path (%d chars max):\n", kMaxPathLength - 1);
  scanf("%100s", input_path);

  TextHolder text_holder = {};
  CustomStatus status = TextHolder::LoadFromFile(&text_holder, input_path);
  if (status != CustomStatus::kOk) {
    printf("Can't load from '%s' with '%s' error\n", input_path,
           kCustomStatusDescription[(int)status]);
    TextHolder::Dtor(&text_holder);
    return 1;
  }

  status = TextHolder::SortIndex(&text_holder, CompareLinesForward);
  if (status != CustomStatus::kOk) {
    printf("Failed forward sorting with '%s' error\n",
           kCustomStatusDescription[(int)status]);
    TextHolder::Dtor(&text_holder);
    return 2;
  }

  char output_path[kMaxPathLength];
  printf("Enter output path for forward sorting (%d chars max):\n",
         kMaxPathLength - 1);
  scanf("%100s", output_path);
  status = TextHolder::SaveToFile(&text_holder, output_path);
  if (status != CustomStatus::kOk) {
    printf("Failed writing to '%s' with '%s' error\n", output_path,
           kCustomStatusDescription[(int)status]);
    TextHolder::Dtor(&text_holder);
    return 3;
  }

  status = TextHolder::SortIndex(&text_holder, CompareLinesBackward);
  if (status != CustomStatus::kOk) {
    printf("Failed backward sorting with '%s' error\n",
           kCustomStatusDescription[(int)status]);
    TextHolder::Dtor(&text_holder);
    return 4;
  }

  printf("Enter output path for backward sorting (%d chars max):\n",
         kMaxPathLength - 1);
  scanf("%100s", output_path);
  status = TextHolder::SaveToFile(&text_holder, output_path);
  if (status != CustomStatus::kOk) {
    printf("Failed writing to '%s' with '%s' error\n", output_path,
           kCustomStatusDescription[(int)status]);
    TextHolder::Dtor(&text_holder);
    return 5;
  }

  printf("Enter output path for original text (%d chars max):\n",
         kMaxPathLength - 1);
  scanf("%100s", output_path);
  status =
      WriteToFile(output_path, text_holder.text_buffer, text_holder.text_size);
  if (status != CustomStatus::kOk) {
    printf("Failed writing to '%s' with '%s' error\n", output_path,
           kCustomStatusDescription[(int)status]);
    TextHolder::Dtor(&text_holder);
    return 6;
  }

  TextHolder::Dtor(&text_holder);
  return 0;
}
