#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
printf("Now start cooking ra-men\n");
sleep(5);
printf("ra-men is ready\n");
system("mplayer ra-men.mp3");

return 0;
}
