#include <colors.h>
#include <stdbool.h>
#include <stdio.h>

#include <krabascript.h>
#include <strings.h>

#include <time.h>

#define REQUIRED_ARGS REQUIRED_STRING_ARG(input_file, "input", "Input file")

#define OPTIONAL_ARGS                                                          \
  OPTIONAL_STRING_ARG(output_file, "a.out", "-o", "Output file",               \
                      "Output file name")                                      \
  OPTIONAL_UINT_ARG(optimization_lvl, 1, "-O", "Optimization",                 \
                    "Optimization level")                                      \
  OPTIONAL_STRING_ARG(include_folder, NULL, "-I", "Include", "Include path")

#define BOOLEAN_ARGS                                                           \
  BOOLEAN_ARG(help, "-h", "Show help")                                         \
  BOOLEAN_ARG(comtime, "-t", "Show compile time")                              \
  BOOLEAN_ARG(verbose, "-v", "Verbose output")

#include <easyargs.h>

int main(int argc, char *argv[]) {

  args_t Args = make_default_args();

  if (!parse_args(argc, argv, &Args)) {
    print_help(argv[0]);
    return 1;
  }

  FILE *Source = fopen(Args.input_file, "r");

  if (Source == NULL) {
    fprintf(stderr, "%skrabascript:%s %sERROR:%s Error opening %s: ", BWHT,
            COLOR_RESET, BRED, COLOR_RESET, Args.input_file);
    perror("");

    return 1;
  }

  char SourceTemp[MAX_TEMP_SRC_SIZE];
  char *StringSource = NULL;

  while (fgets(SourceTemp, sizeof(SourceTemp), Source) != NULL) {
    StringAppend(&StringSource, SourceTemp);
  }

  clock_t Start, End;
  double TokenizerTime;

  Start = clock();

  TokenVector Tokens = Tokenize(StringSource);
  if (Args.verbose == true) {
    PrintTokens(Tokens);
  }

  End = clock();
  TokenizerTime = ((double)(End - Start)) / CLOCKS_PER_SEC;

  if (Args.comtime == true) {
    printf("%skrabascript:%s SUCCESS:%s Tokenizer finished in %s%f%s.\n", BWHT,
           BGRN, COLOR_RESET, BMAG, TokenizerTime, COLOR_RESET);
  }

  return 0;
}
