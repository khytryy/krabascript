#pragma once

#include <stdio.h>
#include <stdlib.h> // For free, realloc

#include <ctype.h>   // For isalpha
#include <stdbool.h> // For bool
#include <string.h>

#include "colors.h"

size_t Index = 0;
size_t Line = 0;

char *Source;

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

void TVecInit(TokenVector *Vector) {
  Vector->Data = NULL;
  Vector->Size = 0;
  Vector->Capacity = 0;
}

void TVecFree(TokenVector *Vector) {
  free(Vector->Data);
  Vector->Data = NULL;
  Vector->Size = 0;
  Vector->Capacity = 0;
}

void TVecPush(TokenVector *Vector, Token Value) {
  if (Vector->Size >= Vector->Capacity) {
    size_t NewCapacity = (Vector->Capacity == 0) ? 4 : Vector->Capacity * 2;
    Token *NewData = realloc(Vector->Data, NewCapacity * sizeof(Token));

    Vector->Data = NewData;
    Vector->Capacity = NewCapacity;
  }

  Vector->Data[Vector->Size++] = Value;
}

void CVecInit(CharVector *Vector) {
  Vector->Data = NULL;
  Vector->Size = 0;
  Vector->Capacity = 0;
}

void CVecFree(CharVector *Vector) {
  free(Vector->Data);
  Vector->Data = NULL;
  Vector->Size = 0;
  Vector->Capacity = 0;
}

void CVecPush(CharVector *Vector, char Value) {
  if (Vector->Size >= Vector->Capacity) {
    size_t NewCapacity = (Vector->Capacity == 0) ? 4 : Vector->Capacity * 2;
    char *NewData = realloc(Vector->Data, NewCapacity * sizeof(char));

    Vector->Data = NewData;
    Vector->Capacity = NewCapacity;
  }

  Vector->Data[Vector->Size++] = Value;
}

char Peek(size_t Offset) { return Source[Index + Offset]; }

bool PeekHasValue(size_t Char) {
  char TempChar = Peek(Char);
  return TempChar != '\0';
}

char Consume() {
  if (!PeekHasValue(0))
    return '\0';
  char C = Source[Index];
  Index++;
  return C;
}

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
    {"typedef", ks_typedef},
    {"module", ks_module},
    {"extern", ks_extern},
    {"float", ks_float},
    {"double", ks_double},
    {"signed", ks_signed},
    {"const", ks_const},
    {"static", ks_static},
    {"function", ks_function},
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

    {NULL, 0},

};

const char *TokenToKeyword(TokenType Token) {
  // Check keywords
  for (int i = 0; Keywords[i].Name != NULL; i++) {
    if (Token == Keywords[i].Type)
      return Keywords[i].Name;
  }

  // Check symbols
  for (int i = 0; Symbols[i].Name != NULL; i++) {
    if (Token == Symbols[i].Type)
      return Symbols[i].Name;
  }
  switch (Token) {
  case ks_identifier:
    return "identifier";
  case ks_int_lit:
    return "int_lit";
  case ks_char_lit:
    return "char_lit";
  default:
    return "unknown";
  }

  return "unknown";
}

TokenType KeywordToToken(const char *Keyword) {
  for (int i = 0; Keywords[i].Name != NULL; i++) {
    if (strcmp(Keyword, Keywords[i].Name) == 0)
      return Keywords[i].Type;
  }
  return ks_identifier; // Default on ks_identifier if not a keyword
}

TokenType SymbolToToken(const char *Keyword) {
  for (int i = 0; Symbols[i].Name != NULL; i++) {
    if (strcmp(Symbols[i].Name, Keyword) == 0)
      return Symbols[i].Type;
  }

  return ks_identifier;
}

TokenVector Tokenize(char *SourceF) {
  Source = SourceF;
  Index = 0;
  Line = 0;

  TokenVector Tokens;
  TVecInit(&Tokens);

  CharVector Buffer;
  CVecInit(&Buffer);

  while (PeekHasValue(0)) { // Look at the current index
    char C = Peek(0);

    if (isalpha(C) || C == '_') {
      CVecPush(&Buffer, Consume());

      while (PeekHasValue(0) && (isalnum(Peek(0)) || Peek(0) == '_')) {
        CVecPush(&Buffer, Consume());
      }

      CVecPush(&Buffer, '\0'); // Null-terminate

      TokenType TempTokenT = KeywordToToken(Buffer.Data);

      if (TempTokenT == ks_identifier) {
        TVecPush(&Tokens,
                 (Token){.Type = ks_identifier,
                         .Value = {.HasValue = true,
                                   .Type = type_string,
                                   .Data = {.S = strdup(Buffer.Data)}}});
      } else {
        TVecPush(&Tokens,
                 (Token){.Type = TempTokenT, .Value = {.HasValue = false}});
      }
      Buffer.Size = 0;
    } else if (isspace(C)) {
      Consume();
      continue;
    } else if (C == '\0') {
      Consume();
      break;
    } else if (C == '\n') {
      Consume();
      continue;
    } else if (PeekHasValue(0) && PeekHasValue(1) && Peek(0) == '-' &&
               Peek(1) == '>') {
      Consume();
      Consume();

      TVecPush(&Tokens,
               (Token){.Type = ks_arrow, .Value = {.HasValue = false}});
    } else if (isdigit(C)) {
      CVecPush(&Buffer, Consume());

      // Consume all digits
      while (PeekHasValue(0) && isdigit(Peek(0))) {
        CVecPush(&Buffer, Consume());
      }

      CVecPush(&Buffer, '\0');

      int value = atoi(Buffer.Data);

      TVecPush(&Tokens, (Token){.Type = ks_int_lit,
                                .Value = {.HasValue = true,
                                          .Type = type_int,
                                          .Data = {.I = value}}});

      Buffer.Size = 0;
    } else {
      const char C = Consume();

      char Temp[2] = {C, '\0'};
      TokenType Symbol = SymbolToToken(Temp);

      TVecPush(&Tokens, (Token){.Type = Symbol, .Value = {.HasValue = false}});
    }
  }

  CVecFree(&Buffer);
  return Tokens;
}

void PrintTokens(TokenVector Tokens) {
  printf("%s======== Token dump ========%s\n", BWHT, COLOR_RESET);

  for (size_t i = 0; i < Tokens.Size; i++) {
    Token *t = &Tokens.Data[i];
    const char *Keyword = TokenToKeyword(t->Type);

    printf("    %s%-12s%s", BMAG, Keyword, COLOR_RESET);

    if (t->Value.HasValue) {
      switch (t->Value.Type) {
      case type_int:
        printf(" -> %d", t->Value.Data.I);
        break;
      case type_string:
        printf(" -> \"%s\"", t->Value.Data.S);
        break;
      default:
        break;
      }
    }

    printf("\n");
  }
}
