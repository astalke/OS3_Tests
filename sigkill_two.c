#include <unistd.h>
#include <signal.h>

// Proces wysyła wysgnał sam do siebie.
int main() {
  negateexit(1);
  // Kod powrotu powinien być niezerowy.
  raise(SIGKILL);
}
