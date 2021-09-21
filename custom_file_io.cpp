//
// Created by vsvood on 9/19/21.
//

#include "custom_file_io.h"

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "custom_status_lib.h"

CustomStatus CheckInputFile(const char *path) {
  if (path == nullptr)
    return CustomStatus::kWrongInputParams;

  printf("Checking input file '%s'...", path);
  if (access(path, F_OK) != 0) {
    printf("\nUnable to access file\n");
    printf("Please check whether file '%s' exists\n", path);
    return CustomStatus::kRuntimeError;
  }
  printf("OK\n");
  return CustomStatus::kOk;
}

CustomStatus CheckOutputFile(const char *path) {
  if (path == nullptr)
    return CustomStatus::kWrongInputParams;

  printf("Checking output file '%s'...", path);
  if (access(path, F_OK) != 0) {
    printf("\nUnable to access file\n");
    printf("Maybe file '%s' doesnt exists\n", path);
    printf("Do you want to create '%s' [y/n] ", path);
    char ans;
    scanf(" %c", &ans);
    if (ans != 'y') {
      printf("Exiting\n");
      return CustomStatus::kRuntimeError;
    }
    int output_descriptor = open(path, O_CREAT|O_TRUNC, 0666);
    if (output_descriptor > 0) {
      printf("Create success\n");
      close(output_descriptor);
    } else {
      printf("Fail creating '%s'\n", path);
      return CustomStatus::kRuntimeError;
    }
  }

  printf("OK\n");

  return CustomStatus::kOk;
}

CustomStatus ReadFromFile(const char *path, char **buffer, long *size) {
  if (CheckInputFile(path) != CustomStatus::kOk)
    return CustomStatus::kWrongInputParams;
  if (buffer == nullptr)
    return CustomStatus::kWrongOutputParams;
  if (size == nullptr)
    return CustomStatus::kWrongOutputParams;

  printf("Reading from '%s'...", path);

  struct stat file_stats = {};
  stat(path, &file_stats);

  int input_descriptor = open(path, O_RDONLY);
  if (input_descriptor < 0)
    return CustomStatus::kRuntimeError;
  *buffer = (char*)calloc((size_t)file_stats.st_size, sizeof(char));
  *size = read(input_descriptor, *buffer, (size_t)file_stats.st_size);
  close(input_descriptor);

  printf("OK\n");

  return CustomStatus::kOk;
}

CustomStatus WriteToFile(const char *path, const char *buffer, const long size) {
  if(CheckOutputFile(path) != CustomStatus::kOk) {
    return CustomStatus::kWrongInputParams;
  }
  if (buffer == nullptr) {
    return CustomStatus::kWrongInputParams;
  }

  printf("Writing to '%s'...", path);

  int input_descriptor = open(path, O_WRONLY|O_TRUNC);
  if (input_descriptor < 0)
    return CustomStatus::kRuntimeError;
  write(input_descriptor, (const void *)buffer, (unsigned)size);
  close(input_descriptor);

  printf("OK\n");

  return CustomStatus::kOk;
}
