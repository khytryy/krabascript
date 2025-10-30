/*
  Project:      Krabascript compiler project
  License:      GNU GPL-3.0 License
  Purpose:      Parse the tokens and create a AST
  Copyright:    Copyright 2025 Yehor Khytryy <yehor.khytryy@gmail.com>
*/

#include "tokenizer.h"
#include <parser.h>
#include <stddef.h>

#include <stdlib.h>

void ANVecInit(ASTNodeVector *Vector) {
    Vector->Data = NULL;
    Vector->Size = 0;
    Vector->Capacity = 0;
}

void ANVecFree(ASTNodeVector *Vector) {
    free(Vector->Data);
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

TokenType GetTokenType(TokenVector *Tokens, size_t Index) {
    return Tokens->Data[Index].Type;
}

Token GetToken(TokenVector *Tokens, size_t Index) {
    return Tokens->Data[Index];
}

void IntHandler(ASTParent *Parent, TokenVector *Tokens, size_t *Index) {
    size_t TokensLeft = Tokens->Size - *Index;

    ASTNode Node;

    // Check before we get the token type so we dont read garbage memory
    if (TokensLeft < 2) {

        printf("%skrabascript:%s %sERROR:%s Expected an identifier, got EOF.\n", 
            BWHT, COLOR_RESET, BRED, COLOR_RESET);
        exit(1);
    }

    // Throw an error if the next token isn't an identifier
    if (GetTokenType(Tokens, *Index + 1) != KS_IDENTIFIER) {

        printf("%skrabascript:%s %sERROR:%s Expected an identifier, got '%s'.\n", 
            BWHT, COLOR_RESET, BRED, COLOR_RESET, 
            TokenToKeyword(GetTokenType(Tokens, *Index + 1)));

        exit(1);
    }

    if (TokensLeft < 3) {

        printf("%skrabascript:%s %sERROR:%s Expected ';' or '=', got EOF.\n", 
            BWHT, COLOR_RESET, BRED, COLOR_RESET);
        exit(1);
    }
    
    // Handle int something;
    if (GetTokenType(Tokens, *Index + 2) == KS_SEMI) {

        Token TempToken = GetToken(Tokens, *Index + 1);

        Node.NodeType = INT_DECLARATION;
        Node.Value.HasValue = false;

        Node.Identifier = TempToken.Value.Data.S;

        ANVecPush(&Parent->Children, Node);

        *Index += 3;
        return;
    }

    if (GetTokenType(Tokens, *Index + 2) == KS_EQUALS) {
        if (TokensLeft < 5) {

            printf("%skrabascript:%s %sERROR:%s Expected expression after '=', got EOF.\n", 
                BWHT, COLOR_RESET, BRED, COLOR_RESET);
            exit(1);
        }

        if (GetTokenType(Tokens, *Index + 3) != KS_INT_LIT) {

            printf("%skrabascript:%s %sERROR:%s Expected int literal after '=', got '%s'.\n", 
                BWHT, COLOR_RESET, BRED, COLOR_RESET, 
                TokenToKeyword(GetTokenType(Tokens, *Index + 2)));
            exit(1);
        }

        if (GetTokenType(Tokens, *Index + 4) != KS_SEMI) {

            printf("%skrabascript:%s %sERROR:%s Expected ';' after int literal, got '%s'.\n", 
                BWHT, COLOR_RESET, BRED, COLOR_RESET, 
                TokenToKeyword(GetTokenType(Tokens, *Index + 4)));
            exit(1);
        }

        Token TempToken = GetToken(Tokens, *Index + 3);

        Node.NodeType = INT_DECLARATION;
        Node.Value.HasValue = true;
        Node.Value.Type = TYPE_INT;

        Node.Value.Data.I = TempToken.Value.Data.I;

        ANVecPush(&Parent->Children, Node);

        *Index += 5;
        return;
    }
}

HandlerEntry Handlers[] = {
    { KS_INT, IntHandler },
};

ASTParent CreateAST(TokenVector *Tokens, bool Verbose) {
    ASTParent AST;
    size_t Index = 0;

    // Initialize parent's children
    ANVecInit(&AST.Children);

    while (Index < Tokens->Size) {
        bool Handled = false;

        for (size_t i = 0; i < ARRAY_GET_NUM_EL(Handlers); i++) {
            if (Tokens->Data[Index].Type == Handlers[i].Type) {
                
                Handlers[i].KSHandler(&AST, Tokens, &Index);
                Handled = true;
                break;
            }
        }

        if (!Handled) {
            printf("No handler found...\n");
            Index++;
        }
    }

    return AST;
}