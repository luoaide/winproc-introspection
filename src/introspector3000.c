#include <stdio.h>
#include <


int main(int argc, char *argv[]) {
  //arg 1: path of the target executable (String)
  //arg 2: time interval of updates (ms)

  if(3 != argc) {
    return -1;
  }

  BOOL running = CreateProcessA(NULL, path, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

}
