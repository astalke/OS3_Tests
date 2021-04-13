#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>
#include <sys/types.h>

// Negujemy, dziecko zwraca 21, co jest negowane do 0
// Rodzic odibera 0 i zwraca to samo, co jest negowane do 1.
int main() {
  negateexit(1);
  if (fork()) {
    int child;
    (void) wait(&child);
    return WEXITSTATUS(child);
  } else {
    return 21;
  }
}
