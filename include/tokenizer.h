/*
  Project:      Krabascript compiler project
  License:      GNU GPL-3.0 License
  Purpose:      Tokenize the source file
  Copyright:    Copyright 2025 Yehor Khytryy <yehor.khytryy@gmail.com>
*/

#pragma once

#include <stdio.h>
#include <stdlib.h> // For free, realloc

#include <ctype.h>   // For isalpha
#include <stdbool.h> // For bool
#include <string.h>

#include "colors.h"

typedef enum {
  ks_while,
  ks_for,
  ks_void,
  ks_break,
  ks_and,
  ks_or,
  ks_xor,
  ks_not,
  ks_if,
  ks_else,
  ks_continue,
  ks_test,
  ks_case,
  ks_default,
  ks_short,
  ks_long,
  ks_unsigned,
  ks_int,
  ks_char,
  ks_sizeof,
  ks_return,
  ks_enum,
  ks_struct,
  ks_typedef,
  ks_module,
  ks_extern,
  ks_float,
  ks_double,
  ks_signed,
  ks_const,
  ks_static,
  ks_function,
  ks_import,
  ks_string,            // Use this comment if you're lost
  ks_arrow,
  ks_open_paren,
  ks_closed_paren,
  ks_semi,
  ks_open_bracket,
  ks_closed_bracket,
  ks_open_curly,
  ks_closed_curly,
  ks_open_arrow,
  ks_closed_arrow,
  ks_hashtag,
  ks_dot,
  ks_colon,
  ks_quote,
  ks_dquote,
  ks_comma,
  ks_qmark,
  ks_equals,
  ks_at,
  ks_plus,
  ks_minus,
  ks_slash,
  ks_backslash,
  ks_int_lit,
  ks_char_lit,
  ks_identifier,

} TokenType;

typedef enum {
  type_none,
  type_int,
  type_uint,
  type_char,
  type_float,
  type_double,
  type_string

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
    {"while", ks_while},
    {"for", ks_for},
    {"void", ks_void},
    {"break", ks_break},
    {"and", ks_and},
    {"or", ks_or},
    {"xor", ks_xor},
    {"not", ks_not},
    {"if", ks_if},
    {"else", ks_else},
    {"continue", ks_continue},
    {"test", ks_test},
    {"case", ks_case},
    {"default", ks_default},
    {"short", ks_short},
    {"long", ks_long},
    {"unsigned", ks_unsigned},
    {"int", ks_int},
    {"char", ks_char},
    {"sizeof", ks_sizeof},
    {"return", ks_return},
    {"enum", ks_enum},
    {"struct", ks_struct},
    {"module", ks_module},
    {"extern", ks_extern},
    {"float", ks_float},
    {"double", ks_double},
    {"signed", ks_signed},
    {"const", ks_const},
    {"static", ks_static},
    {"function", ks_function},
    {"import", ks_import},
    {"string", ks_string},

    {NULL, 0} // End marker
};

static const KeywordEntry Symbols[] = {
    {"->", ks_arrow},
    {"(", ks_open_paren},
    {")", ks_closed_paren},
    {";", ks_semi},
    {"[", ks_open_bracket},
    {"]", ks_closed_bracket},
    {"{", ks_open_curly},
    {"}", ks_closed_curly},
    {"<", ks_open_arrow},
    {">", ks_closed_arrow},
    {"#", ks_hashtag},
    {".", ks_dot},
    {":", ks_colon},
    {"'", ks_quote},
    {"\"", ks_dquote},
    {",", ks_comma},
    {"?", ks_qmark},
    {"=", ks_equals},
    {"@", ks_at},
    {"+", ks_plus},
    {"-", ks_minus},
    {"/", ks_slash},
    {"\\", ks_backslash},

    {NULL, 0},

};

const char *TokenToKeyword(TokenType Token);
TokenType KeywordToToken(const char *Keyword);
TokenType SymbolToToken(const char *Keyword);

TokenVector Tokenize(char *SourceF);

void PrintTokens(TokenVector Tokens);