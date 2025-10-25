module stdlib {
  
  unsigned int Seed = 1;

  function Srand(int seed) {
    Seed = seed;
  }
  function Rand() -> int {
    Seed = Seed * 1103515245 + 12345;

    return (unsigned int)(Seed / 65536) % 32768;
  }
};
