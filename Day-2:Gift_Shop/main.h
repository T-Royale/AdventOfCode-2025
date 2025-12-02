#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>

#define MAX_DIGITS 15

bool is_invalid_id(uint64_t id);