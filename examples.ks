// Variables
int a = 5000;
int b;

// Functions
function add(a: int, b: int) -> int {
  return a + b;
}

// structs

typedef struct {
  int a;
  int b;
} AwesomeStruct;

// Modules

module MyModule {
  function Pi() -> double {
    return 3.14159265359;
  }
};

// Enums

typedef enum {
  OK,
  ERROR
} Status;

// Imports

@import <Module.kh>