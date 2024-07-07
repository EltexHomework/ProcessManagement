#include "headers/interpretor.h"

int main(void) {
  struct interpretor* interpretor = create_interpretor();
  run_interpretor(interpretor);
  return 0;
}
