#ifndef WHAT_H
#define WHAT_H

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#endif

int __encode_url(char *dest, size_t dest_size, const char *src);
int what_message(const char *number, const char *message);

#endif