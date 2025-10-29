/*
  Project:      Krabascript compiler project
  License:      GNU GPL-3.0 License
  Purpose:      Tokenize the source file
  Copyright:    Copyright 2025 Yehor Khytryy <yehor.khytryy@gmail.com>
*/

#include <tokenizer.h>

size_t Index = 0;
size_t Line = 0;

char *Source;

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
    case KS_IDENTIFIER:
      return "identifier";
    case KS_INT_LIT:
      return "int_lit";
    case KS_CHAR_LIT:
      return "char_lit";
    case KS_STRING_LIT:
      return "string_lit";
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
  return KS_IDENTIFIER; // Default on KS_IDENTIFIER if not a keyword
}

TokenType SymbolToToken(const char *Keyword) {
  for (int i = 0; Symbols[i].Name != NULL; i++) {
    if (strcmp(Symbols[i].Name, Keyword) == 0)
      return Symbols[i].Type;
  }

  return KS_IDENTIFIER;
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

      if (TempTokenT == KS_IDENTIFIER) {
        TVecPush(&Tokens,
                 (Token){.Type = KS_IDENTIFIER,
                         .Value = {.HasValue = true,
                                   .Type = TYPE_STRING,
                                   .Data = {.S = strdup(Buffer.Data)}}});
      } else {
        TVecPush(&Tokens,
                 (Token){.Type = TempTokenT, .Value = {.HasValue = false}});
      }

      Buffer.Size = 0;
      
    } else if (isspace(C)) {
      Consume();
      continue;

    } else if (C == '"') {

      Consume();
      Buffer.Size = 0;

      // Copy everything into a buffer until we find a dquote
      while (PeekHasValue(0) && Peek(0) != '"') {
        CVecPush(&Buffer, Consume());
      }

      if (PeekHasValue(0) && Peek(0) == '"') Consume();

      // Push a string
      TVecPush(&Tokens, (Token){
        .Type = KS_STRING_LIT,
        .Value = {.HasValue = true, .Type = TYPE_STRING, .Data = {.S = strdup(Buffer.Data)}}
      });

      Buffer.Size = 0;

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
               (Token){.Type = KS_ARROW, .Value = {.HasValue = false}});
    } else if (isdigit(C)) {
      CVecPush(&Buffer, Consume());

      // Consume all digits
      while (PeekHasValue(0) && isdigit(Peek(0))) {
        CVecPush(&Buffer, Consume());
      }

      CVecPush(&Buffer, '\0');

      int value = atoi(Buffer.Data);

      TVecPush(&Tokens, (Token){.Type = KS_INT_LIT,
                                .Value = {.HasValue = true,
                                          .Type = TYPE_INT,
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
      case TYPE_INT:
        printf(" -> %d", t->Value.Data.I);
        break;
      case TYPE_STRING:
        printf(" -> \"%s\"", t->Value.Data.S);
        break;
      default:
        break;
      }
    }

    printf("\n");
  }
}