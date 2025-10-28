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

void ANVecInit(ASTNodeVector *Vector);
void ANVecFree(ASTNodeVector *Vector);
void ANVecPush(ASTNodeVector *Vector, ASTNode Value);

Token GetToken(TokenVector Tokens, size_t Index, size_t Add);
TokenType GetTokenType(TokenVector *Tokens, size_t Index, size_t Add);

typedef void (*ASTHandler)(ASTParent *AST, TokenVector *Tokens, size_t *Index);

void IntHandler(ASTParent *AST, TokenVector *Tokens, size_t *Index);
void FloatHandler(ASTParent *AST, TokenVector *Tokens, size_t *Index);

typedef struct {
  TokenType   Type;
  ASTHandler  Handler;

} HandlerEntry;

static const HandlerEntry Handlers[] = {
  { ks_int,  IntHandler },
  { ks_float, FloatHandler },
};

ASTParent CreateAST(TokenVector Tokens, bool Verbose);