#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>
#include <sys/types.h>

/*
 * 5 dzieci ma zanegowany kod
 * 5 nie
 * Każde z nich ma zwrócić i % 2 - każde zwróci 1.
 * Program zwróci 0, jeśli wszystko jest ok.
 */
int main() {
  for (int i = 0; i < 10; ++i) {
    negateexit((i + 1) % 2);
    if (!fork()) {
      return i % 2;
    }
  }
  // Przywracamy normalny kod.
  negateexit(0);
  int result = 0;
  for (int i = 0; i < 10; ++i) {
    int child;
    (void) wait(&child);
    if (!WEXITSTATUS(child)) {
      result = 1;
    }
  }
  return result;  
}
