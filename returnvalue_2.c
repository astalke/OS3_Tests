#include <unistd.h>
#include <assert.h>

int main() {
  negateexit(1);
  if (!fork()) {
    assert(negateexit(1) == 1);
    assert(negateexit(0) == 1);
    assert(negateexit(1) == 0);
  }
  int child;
  wait(&child);
  negateexit(0);
  return child;
}
