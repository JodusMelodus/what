#ifndef WHAT_H
#define WHAT_H

#include <stdlib.h>

#ifdef _WIN32
#include <Windows.h>
#endif

#include "utils.h"

int what_message(const char *number, const char *message);

#endif