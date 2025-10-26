#pragma once

#include <cstddef>
#include <stdio.h>
#include "tokenizer.h"

#include <stdlib.h>

typedef enum {
  int_assigment,
  int_declaration,
  function_dec,
  float_assigment,
  double_assigment,
  string_assigment,
  char_assigment,
  for_loop,
  while_loop,
  if_statement,
  else_statement,

} ASTType;

#define HANDLE(ASTTYPE, AST, TOKENS, INDEX) \
  ASTTYPE##_handler(AST, TOKENS, INDEX)

typedef struct {
  ASTType NodeType;
  OptionalType Value;

} ASTNode;

typedef struct {
  ASTNode *Data;
  size_t Size;
  size_t Capacity;

} ASTNodeVector;

typedef struct {
  ASTType NodeType;
  ASTNodeVector Children;

} ASTParent;

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

Token GetToken(TokenVector Tokens, size_t Index, size_t Add) {
  return Tokens.Data[Index + Add];
}

TokenType GetTokenType(TokenVector Tokens, size_t Index, size_t Add) {
  return Tokens.Data[Index + Add].Type;
}


void IntDeclarationHandler(TokenVector *Tokens, ASTParent *AST, size_t *Index) {

  if (GetTokenType(Tokens, Index, 0)) {

  }
}

ASTParent CreateAST(TokenVector Tokens) {

  ASTParent AST;
  ASTParent TempNode;

  for (size_t i = 0; i < Tokens.Size; i++) {
    Token Current = Tokens.Data[i];

    // Int variable declaration
    switch (Current.Type) {
      // TODO: Add handlers
    }
  }
}