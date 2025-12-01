#pragma once

#include <stdio.h>
#include <stddef.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_PATH_LEN 64
#define LINE_LEN 8

bool parse_file(char *path, int *dial, int *result);