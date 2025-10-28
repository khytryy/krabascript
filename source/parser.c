/*
  Project:      Krabascript compiler project
  License:      GNU GPL-3.0 License
  Purpose:      Parse the tokens and create a AST
  Copyright:    Copyright 2025 Yehor Khytryy <yehor.khytryy@gmail.com>
*/

#include <parser.h>

unsigned int TokenNumber;

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

void IntHandler(ASTParent *AST, TokenVector *Tokens, size_t *Index) {
    ASTNode Node;

    // Expect identifier
    if (GetTokenType(Tokens, *Index, 1) != ks_identifier) {
        printf("%skrabascript:%s %sERROR:%s Expected an identifier, got '%s'\n",
               BWHT, COLOR_RESET, BRED, COLOR_RESET,
               TokenToKeyword(GetTokenType(Tokens, *Index, 1)));
        exit(1);
    }

    TokenType second = GetTokenType(Tokens, *Index, 2);

    // Handle int something;
    if (second == ks_semi) {
        Node.Value.HasValue = false;
        Node.NodeType = int_declaration;
        ANVecPush(&AST->Children, Node);
        *Index += 3;
        return;
    }

    // Handle int something = ...;
    if (second == ks_equals) {
        if (GetTokenType(Tokens, *Index, 3) != ks_int_lit) {
            printf("%skrabascript:%s %sERROR:%s Expected int literal, got '%s'\n",
                   BWHT, COLOR_RESET, BRED, COLOR_RESET,
                   TokenToKeyword(GetTokenType(Tokens, *Index, 3)));
            exit(1);
        }

        if (GetTokenType(Tokens, *Index, 4) != ks_semi) {
            printf("%skrabascript:%s %sERROR:%s Expected ';', got '%s'\n",
                   BWHT, COLOR_RESET, BRED, COLOR_RESET,
                   TokenToKeyword(GetTokenType(Tokens, *Index, 4)));
            exit(1);
        }

        Token TempToken = GetToken(*Tokens, *Index, 3);
        Node.Value.HasValue = true;
        Node.Value.Data.I = TempToken.Value.Data.I;
        Node.NodeType = int_declaration;
        ANVecPush(&AST->Children, Node);
        *Index += 5;
        return;
    }

    // Unexpected stuff
    printf("%skrabascript:%s %sERROR:%s Expected ';' or '=', got '%s'\n",
           BWHT, COLOR_RESET, BRED, COLOR_RESET,
           TokenToKeyword(second));
    exit(1);
}

void FloatHandler(ASTParent *AST, TokenVector *Tokens, size_t *Index) {
  
}

ASTParent CreateAST(TokenVector Tokens, bool Verbose) {
  ASTParent AST;
  size_t Index = 0;

  TokenNumber = 0;

  // Init vectors children
  ANVecInit(&AST.Children);

  while (Index < Tokens.Size - 1) {
    for (size_t i = 0; i < ARRAY_GET_NUM_EL(Handlers); i++) {
      if (GetTokenType(&Tokens, Index, 0) == Handlers[Index].Type) {
        Handlers[i].Handler(&AST, &Tokens, &Index);
      } else {
        Index++; // Skip over tokens with no handlers
        TokenNumber++;
      }
    }
  }

  return AST;
}
