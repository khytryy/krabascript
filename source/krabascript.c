#include <krabascript.h>

void RunCompiler(char *SourceFile, bool Verbose, bool ShowTime) {
    clock_t Start, End;
    double TokenizerTime;

    Start = clock();

    TokenVector Tokens = Tokenize(SourceFile);
    if (Verbose) {
        PrintTokens(Tokens);
    }

    End = clock();
    TokenizerTime = ((double)(End - Start)) / CLOCKS_PER_SEC;

    if (ShowTime) {
        printf("%skrabascript:%s INFO:%s Tokenizer finished in %s%f%s.\n", BWHT,
           BCYN, COLOR_RESET, BMAG, TokenizerTime, COLOR_RESET);
    }

    double ASTTime;

    Start = clock();
    ASTParent AST = CreateAST(&Tokens, Verbose);

    End = clock();
    ASTTime = ((double)(End - Start)) / CLOCKS_PER_SEC;

    if (ShowTime) {
        printf("%skrabascript:%s INFO:%s Parser finished in %s%f%s.\n", BWHT,
           BCYN, COLOR_RESET, BMAG, ASTTime, COLOR_RESET);
    }
}