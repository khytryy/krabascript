/*
  Project:      Krabascript compiler project
  License:      GNU GPL-3.0 License
  Purpose:      Tokenize the source file
  Copyright:    Copyright 2025 Yehor Khytryy <yehor.khytryy@gmail.com>
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <string.h>

#include "colors.h"

typedef enum {
  KS_WHILE,
  KS_FOR,
  KS_VOID,
  KS_BREAK,
  KS_AND,
  KS_OR,
  KS_XOR,
  KS_NOT,
  KS_IF,
  KS_ELSE,
  KS_CONTINUE,
  KS_TEST,
  KS_CASE,
  KS_DEFAULT,
  KS_SHORT,
  KS_LONG,
  KS_UNSIGNED,
  KS_INT,
  KS_CHAR,
  KS_SIZEOF,
  KS_RETURN,
  KS_ENUM,
  KS_STRUCT,
  KS_TYPEDEF,
  KS_MODULE,
  KS_EXTERN,
  KS_FLOAT,
  KS_DOUBLE,
  KS_SIGNED,
  KS_CONST,
  KS_STATIC,
  KS_FUNCTION,
  KS_IMPORT,
  KS_STRING,            // Use this comment if you're lost
  KS_ARROW,
  KS_OPEN_PAREN,
  KS_CLOSED_PAREN,
  KS_SEMI,
  KS_OPEN_BRACKET,
  KS_CLOSED_BRACKET,
  KS_OPEN_CURLY,
  KS_CLOSED_CURLY,
  KS_OPEN_ARROW,
  KS_CLOSED_ARROW,
  KS_HASHTAG,
  KS_DOT,
  KS_COLON,
  KS_QUOTE,
  KS_DQUOTE,
  KS_COMMA,
  KS_QMARK,
  KS_EQUALS,
  KS_AT,
  KS_PLUS,
  KS_MINUS,
  KS_SLASH,
  KS_BACKSLASH,
  KS_SHIFTL,
  KS_SHIFTR,
  KS_INT_LIT,
  KS_STRING_LIT,
  KS_CHAR_LIT,
  KS_IDENTIFIER,

} TokenType;

typedef enum {
  TYPE_NONE,
  TYPE_INT,
  TYPE_UINT,
  TYPE_CHAR,
  TYPE_FLOAT,
  TYPE_DOUBLE,
  TYPE_STRING

} ValueType;

typedef struct {
  bool HasValue;
  ValueType Type;

  union {
    int I;
    unsigned int U;
    char C;
    float F;
    double D;
    char *S;
  } Data;
} OptionalType;

typedef struct {
  TokenType Type;
  OptionalType Value;
} Token;

typedef struct {
  Token *Data;
  size_t Size;
  size_t Capacity;
} TokenVector;

typedef struct {
  char *Data;
  size_t Size;
  size_t Capacity;
} CharVector;

void TVecInit(TokenVector *Vector);
void TVecFree(TokenVector *Vector);
void TVecPush(TokenVector *Vector, Token Value);

void CVecInit(CharVector *Vector);
void CVecFree(CharVector *Vector);
void CVecPush(CharVector *Vector, char Value);

char Peek(size_t Offset);
bool PeekHasValue(size_t Char);
char Consume();

typedef struct {
  const char *Name;
  TokenType Type;
} KeywordEntry;

static const KeywordEntry Keywords[] = {
    {"while", KS_WHILE},
    {"for", KS_FOR},
    {"void", KS_VOID},
    {"break", KS_BREAK},
    {"and", KS_AND},
    {"or", KS_OR},
    {"xor", KS_XOR},
    {"not", KS_NOT},
    {"if", KS_IF},
    {"else", KS_ELSE},
    {"continue", KS_CONTINUE},
    {"test", KS_TEST},
    {"case", KS_CASE},
    {"default", KS_DEFAULT},
    {"short", KS_SHORT},
    {"long", KS_LONG},
    {"unsigned", KS_UNSIGNED},
    {"int", KS_INT},
    {"char", KS_CHAR},
    {"sizeof", KS_SIZEOF},
    {"return", KS_RETURN},
    {"enum", KS_ENUM},
    {"struct", KS_STRUCT},
    {"module", KS_MODULE},
    {"extern", KS_EXTERN},
    {"float", KS_FLOAT},
    {"double", KS_DOUBLE},
    {"signed", KS_SIGNED},
    {"const", KS_CONST},
    {"static", KS_STATIC},
    {"function", KS_FUNCTION},
    {"import", KS_IMPORT},
    {"string", KS_STRING},

    {NULL, 0} // End marker
};

static const KeywordEntry Symbols[] = {
    {"->", KS_ARROW},
    {"(", KS_OPEN_PAREN},
    {")", KS_CLOSED_PAREN},
    {";", KS_SEMI},
    {"[", KS_OPEN_BRACKET},
    {"]", KS_CLOSED_BRACKET},
    {"{", KS_OPEN_CURLY},
    {"}", KS_CLOSED_CURLY},
    {"<<", KS_SHIFTL},
    {">>", KS_SHIFTR},
    {"<", KS_OPEN_ARROW},
    {">", KS_CLOSED_ARROW},
    {"#", KS_HASHTAG},
    {".", KS_DOT},
    {":", KS_COLON},
    {"'", KS_QUOTE},
    {"\"", KS_DQUOTE},
    {",", KS_COMMA},
    {"?", KS_QMARK},
    {"=", KS_EQUALS},
    {"@", KS_AT},
    {"+", KS_PLUS},
    {"-", KS_MINUS},
    {"/", KS_SLASH},
    {"\\", KS_BACKSLASH},

    {NULL, 0},

};

const char *TokenToKeyword(TokenType Token);
TokenType KeywordToToken(const char *Keyword);
TokenType SymbolToToken(const char *Keyword);

TokenVector Tokenize(char *SourceF);

void PrintTokens(TokenVector Tokens);
