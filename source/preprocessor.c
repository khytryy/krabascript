#include <preprocessor.h>

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

char* Preprocess(char* KSSource) {
    Source = KSSource;

    CharVector Buffer;

    CVecInit(&Buffer);

    while (PeekHasValue(0)) {
      char C = Peek(0);

      CVecPush(&Buffer, Consume());

      while (PeekHasValue(0) && (isalnum(Peek(0)) || Peek(0) == '_')) {
        CVecPush(&Buffer, Consume());
      }

      if (Buffer.Data == "define") {

      }
      else if (Buffer.Data == "import") {
        
      }
    }
}