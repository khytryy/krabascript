/*
  Project:      Krabascript compiler project
  License:      GNU GPL-3.0 License
  Purpose:      Parse the tokens and create a AST
  Copyright:    Copyright 2025 Yehor Khytryy <yehor.khytryy@gmail.com>
*/

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

void IntHandler(ASTParent *Parent, TokenVector *Tokens, size_t *Index) {

}

HandlerEntry Handlers[] = {
    { KS_INT, IntHandler },
};

ASTParent CreateAST(TokenVector *Tokens) {

    ASTParent AST;
    size_t Index = 0;

    // Init parent's children
    ANVecInit(AST.Children);

    // Init children's children & brothers
    ANVecInit(AST.Children->Data->Children);
    ANVecInit(AST.Children->Data->Brothers);
    
    while (Index < Tokens->Size) {
        for (size_t i = 0; i < ARRAY_GET_NUM_EL(Handlers); i++) {
            Handlers[i].KSHandler(&AST, Tokens, &Index);
        }
    }

    return AST;
}