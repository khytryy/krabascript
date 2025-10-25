#pragma once

#include <stdio.h>
#include <tokenizer.h>

#include <stdlib.h>

typedef enum {
  int_assigment,

} ASTType;

typedef struct {
  ASTType NodeType;
  OptionalType Value;

} ASTNode;

typedef struct {
  ASTNode *Data;
  size_t Size;
  size_t Capacity;

} ASTNodeVector;

void ANVecInit(ASTNodeVector *Vector) {
  Vector->Data = NULL;
  Vector->Size = 0;
  Vector->Capacity = 0;
}

void ANVecFree(ASTNodeVector *Vector) {
  free(Vector->Data);

  Vector->Data = NULL;
  Vector->Size = 0;
  Vector->Capacity = 0;
}
