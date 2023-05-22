#pragma once

#include <wchar.h>

#define MAX_LENGTH 10000

int processing(wchar_t *text);

int is_palindrome(wchar_t *text, int len);

int split_file(const char *filename);