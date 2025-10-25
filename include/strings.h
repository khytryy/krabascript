#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "colors.h"

void StringAppend(char **Dest, const char *Src) {
    size_t OldLen = (*Dest) ? strlen(*Dest) : 0;
    size_t NewLen = OldLen + strlen(Src);

    char *NewPtr = realloc(*Dest, NewLen + 1); // +1 For null terminator
    if (!NewPtr) {
        fprintf(stderr, "%skrabascript:%s %sERROR:%s Error appending to a string (realloc fault): ",
            BWHT, COLOR_RESET, BRED, COLOR_RESET);
        perror("");
        exit(1);
    }

    *Dest = NewPtr;
    strcpy(*Dest + OldLen, Src); // Append new text at end
}