/*
 * Buduje ładne drzewko procesów.
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

int spawn(int depth) {
  if (depth == 0) return 0;
  if (fork()) {
    int old = negateexit(-1);
    if (!fork()) {
      return spawn(depth - 1);
    } else {
      negateexit(old);
    }
  } else {
    return spawn(depth - 1);
  }
  return 1;
}

int negate(int a) {
  if (a) return 0;
  return 1;
}

int main() {
  if (spawn(6)) {   // Dla 7 na pewno zapełnisz tablicę PM
    int c1, c2;
    int result = negateexit(0);
    negateexit(result);
    wait(&c1);
    c1 = WEXITSTATUS(c1);
    wait(&c2);
    c2 = WEXITSTATUS(c2);
    // Oba powinny zwrócić 0
    if (c1 || c2) {
      // Błąd
      return negate(result);
    }
    return result;
  } else {
    int r = negateexit(0);
    negateexit(r);
    return r;
  }
}
