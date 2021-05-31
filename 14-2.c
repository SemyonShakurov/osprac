#include <signal.h>
#include <stdio.h>

// Хендлер по примеру
void myHandler(int nsig) {
  if(nsig == SIGINT) {
    printf("CTRL + С нажат");
  }
  else if(nsig == SIGQUIT) {
    printf("CTRL + 4 нажат");
  }
}

int main(void) {
  // Код из 14-1
  (void)signal(SIGINT, myHandler);
  (void)signal(SIGQUIT, myHandler);

  while(1);
  return 0;
}
