/*
  Project:      Krabascript compiler project
  License:      GNU GPL-3.0 License
  Purpose:      Parse the tokens and create a AST
  Copyright:    Copyright 2025 Yehor Khytryy <yehor.khytryy@gmail.com>
*/

#pragma once

#include <stdio.h>
#include <tokenizer.h>

#include <stdlib.h>

#define ARRAY_GET_NUM_EL(ARRAY) \
 sizeof(ARRAY) / sizeof(ARRAY[0])

typedef enum {
  INT_DECLARATION,
  STRING_DECLARATION,

} ASTType;


typedef struct ASTNode ASTNode;
typedef struct ASTNodeVector ASTNodeVector;

struct ASTNode {
  ASTType         NodeType;
  char            *Identifier;

  OptionalType    Value;
  ASTNodeVector   *Children;
  ASTNodeVector   *Brothers;
};

struct ASTNodeVector {
  ASTNode         *Data;
  size_t          Size;
  size_t          Capacity;
};

typedef struct {
  ASTType         NodeType;
  ASTNodeVector   Children;

} ASTParent;

typedef void (*Handler)(ASTParent *Parent, TokenVector *Tokens, size_t *Index);

void ANVecInit(ASTNodeVector *Vector);
void ANVecFree(ASTNodeVector *Vector);
void ANVecPush(ASTNodeVector *Vector, ASTNode Node);

typedef struct {
  TokenType       Type;
  Handler         KSHandler;
  
} HandlerEntry;

extern HandlerEntry Handlers[];

TokenType GetTokenType(TokenVector *Tokens, size_t Index);
Token GetToken(TokenVector *Tokens, size_t Index);

void IntHandler(ASTParent *Parent, TokenVector *Tokens, size_t *Index);
void StringHandler(ASTParent *Parent, TokenVector *Tokens, size_t *Index);

ASTParent CreateAST(TokenVector *Tokens, bool Verbose);