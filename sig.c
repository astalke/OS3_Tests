/*
 * Nie potrafię znaleźć informacji jaki powinien być kod powrotu przy sygnale.
 * Więc zakładam, że wyniki powinny być takie same niezależnie od ustawienia
 * negateexit.
 * Przy okazji sprawdzamy, czy nie zmieniliśmy przez przypadek numeru sygnału.
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

int test_abort(void) {
  int normal;
  if (fork() == 0) {
    abort();
  } else {
    (void) wait(&normal);
    if (!WIFSIGNALED(normal)) return 0;
    if (WTERMSIG(normal) != SIGABRT) return 0;
  }
  if (fork() == 0) {
    negateexit(1);
    // Kod powrotu powinien być niezerowy.
    abort();
  } else {
    int child;
    (void) wait(&child);
    if (!WIFSIGNALED(child)) return 0;
    if (WTERMSIG(child) != SIGABRT) return 0;
    if (child != normal) return 0;  // Błąd.
  }
  return 1;
}

int test_kill(void) {
  int normal;
  if (fork() == 0) {
    raise(SIGKILL);
  } else {
    (void) wait(&normal);
    if (!WIFSIGNALED(normal)) return 0;
    if (WTERMSIG(normal) != SIGKILL) return 0;
  }
  if (fork() == 0) {
    negateexit(1);
    // Kod powrotu powinien być niezerowy.
    raise(SIGKILL);
  } else {
    int child;
    (void) wait(&child);
    if (!WIFSIGNALED(child)) return 0;
    if (WTERMSIG(child) != SIGKILL) return 0;
    if (child != normal) return 0;  // Błąd.
  }
  return 1;
}

int main() {
  int result;
  if ((result = test_abort())) {
    if ((result = test_kill())) {
      return EXIT_SUCCESS;
    } else {
      fprintf(stderr, "Test kill failed\n");
      return EXIT_FAILURE;
    }
  } else {
    fprintf(stderr, "Test abort failed\n");
    return EXIT_FAILURE;
  }
}
