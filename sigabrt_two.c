#include <unistd.h>
#include <stdlib.h>

// Proces wysyła wysgnał sam do siebie.
int main() {
  negateexit(1);
  // Kod powrotu powinien być niezerowy.
  abort();
}
