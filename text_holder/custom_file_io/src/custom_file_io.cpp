//
// Created by vsvood on 9/19/21.
//

#include "custom_file_io.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cstdio>

CustomStatus GetFileSize(const char *path, size_t *size) {
  if (CheckInputFile(path) != CustomStatus::kOk) {
    return CustomStatus::kWrongInputParams;
  }

  if (size == nullptr) {
    return CustomStatus::kWrongOutputParams;
  }

  struct stat stats = {};
  if (stat(path, &stats) != 0) {
    return CustomStatus::kRuntimeError;
  }

  *size = (size_t)stats.st_size;
  return CustomStatus::kOk;
}

CustomStatus CheckInputFile(const char *path) {
  if (path == nullptr) {
    return CustomStatus::kWrongInputParams;
  }

  struct stat stats = {};
  if (stat(path, &stats) != 0) {
    printf("\nUnable to access file\n");
    printf("Please check whether file '%s' exists\n", path);
    return CustomStatus::kRuntimeError;
  }
  if ((stats.st_mode & S_IFMT) != S_IFREG) {
    printf("\n'%s' is not a regular file\n", path);
    return CustomStatus::kWrongInputParams;
  }

  return CustomStatus::kOk;
}

CustomStatus CheckOutputFile(const char *path) {
  if (path == nullptr) return CustomStatus::kWrongInputParams;

  struct stat stats = {};
  if (stat(path, &stats) != 0) {
    printf("Unable to access file\n");
    printf("Maybe file '%s' doesnt exists\n", path);
    printf("Do you want to create '%s' [y/n] ", path);
    char ans;
    scanf(" %c", &ans);
    if (ans != 'y') {
      printf("Exiting\n");
      return CustomStatus::kRuntimeError;
    }
    int output_descriptor = open(path, O_CREAT | O_TRUNC, 0666);
    if (output_descriptor > 0) {
      printf("Create success\n");
      close(output_descriptor);
      stat(path, &stats);
    } else {
      printf("Fail creating '%s'\n", path);
      return CustomStatus::kRuntimeError;
    }
  }
  if ((stats.st_mode & S_IFMT) != S_IFREG) {
    printf("Error: '%s' is not a regular file\n", path);
    return CustomStatus::kWrongInputParams;
  }

  return CustomStatus::kOk;
}

CustomStatus ReadFromFile(const char *path, char *buffer, size_t *size) {
  if (CheckInputFile(path) != CustomStatus::kOk) {
    return CustomStatus::kWrongInputParams;
  }
  if (buffer == nullptr) {
    return CustomStatus::kWrongOutputParams;
  }

  int input_descriptor = open(path, O_RDONLY);
  if (input_descriptor < 0) {
    printf("Can`t open file for reading\n");
    return CustomStatus::kRuntimeError;
  }

  long tmp = read(input_descriptor, buffer, *size);
  if (tmp < 0) {
    printf("Failed reading from file\n");
    return CustomStatus::kRuntimeError;
  }
  *size = (size_t)tmp;

  close(input_descriptor);

  return CustomStatus::kOk;
}

CustomStatus WriteToFile(const char *path, const char *buffer, size_t size) {
  if (CheckOutputFile(path) != CustomStatus::kOk) {
    return CustomStatus::kWrongInputParams;
  }
  if (buffer == nullptr) {
    return CustomStatus::kWrongInputParams;
  }

  int input_descriptor = open(path, O_WRONLY | O_TRUNC);
  if (input_descriptor < 0) {
    printf("Can`t open file for writing\n");
    return CustomStatus::kRuntimeError;
  }

  long tmp = write(input_descriptor, (const void *)buffer, (unsigned)size);
  if (tmp < 0) {
    printf("Failed writing to file\n");
    return CustomStatus::kRuntimeError;
  }

  close(input_descriptor);

  return CustomStatus::kOk;
}
