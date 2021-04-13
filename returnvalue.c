#include <unistd.h>
#include <assert.h>

int main() {
  assert(negateexit(1) == 0);
  assert(negateexit(1) == 1);
  assert(negateexit(1) == 1);
  assert(negateexit(0) == 1);
  return 0;
}
