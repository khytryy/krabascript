/*
  Project:      Krabascript compiler project
  License:      GNU GPL-3.0 License
  Purpose:      Parse the tokens and create a AST
  Copyright:    Copyright 2025 Yehor Khytryy <yehor.khytryy@gmail.com>
*/

#pragma once

#include <stdio.h>
#include "tokenizer.h"

#include <stdlib.h>

#define ARRAY_GET_NUM_EL(ARRAY) \
 sizeof(ARRAY) / sizeof(ARRAY[0])

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

void ANVecPush(ASTNodeVector *Vector, ASTNode Value) {
  if (Vector->Size >= Vector->Capacity) {
    size_t NewCapacity = (Vector->Capacity == 0) ? 4 : Vector->Capacity * 2;
    ASTNode *NewData = realloc(Vector->Data, NewCapacity * sizeof(ASTNode));

    Vector->Data = NewData;
    Vector->Capacity = NewCapacity;
  }

  Vector->Data[Vector->Size++] = Value;
}

Token GetToken(TokenVector Tokens, size_t Index, size_t Add) {
  return Tokens.Data[Index + Add];
}

TokenType GetTokenType(TokenVector *Tokens, size_t Index, size_t Add) {
  return Tokens->Data[Index + Add].Type;
}

typedef void (*ASTHandler)(ASTParent *AST, TokenVector *Tokens, size_t *Index);

void IntHandler(ASTParent *AST, TokenVector *Tokens, size_t *Index) {

  ASTNode Node;

  if (GetTokenType(Tokens, *Index, 1) == ks_identifier) {
    if (GetTokenType(Tokens, *Index, 2) == ks_semi) {

      Node.NodeType = int_declaration;
      Node.Value.HasValue = false;

      ANVecPush(&AST->Children, Node);
    }
    else if (GetTokenType(Tokens, *Index, 2) == ks_equals) {
      Node.NodeType = int_assigment;
      
      Token KSToken = GetToken(*Tokens, *Index, 3);

      if (KSToken.Value.HasValue == true) {

      }
      else {

        printf("%skrabascript:%s %sERROR:%s Expected an assigment, found '%s'\n", BWHT, BRED, COLOR_RESET, TokenToKeyword(GetToken(*Tokens, *Index, 3)));
        return;
      }
    }
  }
}

void FloatHandler(ASTParent *AST, TokenVector *Tokens, size_t *Index) {

}

typedef struct {
  TokenType   Type;
  ASTHandler  Handler;

} HandlerEntry;

static const HandlerEntry Handlers[] = {
  { ks_int,  IntHandler },
  { ks_float, FloatHandler },
};

ASTParent CreateAST(TokenVector Tokens, bool Verbose) {
  ASTParent AST;
  size_t Index = 0;

  // Init vectors children
  ANVecInit(&AST.Children);

  while (Index < Tokens.Size) {
    for (size_t i = 0; i < ARRAY_GET_NUM_EL(Handlers); i++) {
      if (GetTokenType(&Tokens, Index, 0) == Handlers[Index].Type) {
        Handlers[i].Handler(&AST, &Tokens, &Index);
      }
      else {
        Index++;      // Skip over tokens with no handlers
      }
    }
  }
}