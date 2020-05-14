#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/types.h>
#include <fcntl.h>

int first_child_pid;

int main() {
  printf("startowy pid: %d\n", getpid());
  printf("liczba kudosow startowego: 0\n");

  switch (fork()) {
    case 0:
      first_child_pid = getpid();
      usleep(30000);

      break;

    default:
      usleep(1000);

      printf("probuje dac kudosy swojemu dziecku: nie powinno sie udać (moj pid: %d)\n", getpid());
      givekudos(first_child_pid);
      printf("nie udalo sie? sprawdz! (moj pid: %d)\n", getpid());

      if (wait(0) == -1)
        syserr("wait");

      break;
  }

  switch (fork()) {
    case 0:
      usleep(10000);

      printf("probuje dac kudosy swojemu kuzynowi: powinno sie udać (moj pid: %d)\n", getpid());
      givekudos(first_child_pid);
      printf("udalo sie? sprawdz! (moj pid: %d)\n", getpid());

      usleep(30000);

      break;

    default:
      usleep(1000);

      if (wait(0) == -1)
        syserr("wait");

      break;
  }

  return 0;
}