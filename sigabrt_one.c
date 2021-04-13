#include <unistd.h>
#include <stdlib.h>

// Proces wysyła wysgnał sam do siebie.
int main() {
  // Kod powrotu powinien być niezerowy.
  abort();
}
