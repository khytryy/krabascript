/*
  Project:      Krabascript compiler project
  License:      GNU GPL-3.0 License
  Purpose:      Replace definitions with other text
  Copyright:    Copyright 2025 Yehor Khytryy <yehor.khytryy@gmail.com>
*/

#pragma once

#include <stdio.h>
#include <stdbool.h>

typedef struct {
  char *Data;
  size_t Size;
  size_t Capacity;
} CharVector;

void CVecInit(CharVector *Vector);
void CVecFree(CharVector *Vector);
void CVecPush(CharVector *Vector, char Value);

char*     Source;
size_t    Index = 0;



char Peek(size_t Offset);
bool PeekHasValue(size_t Char);
char Consume();

char* Preprocess(char* Source);