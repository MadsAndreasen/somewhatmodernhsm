
#include "door.h"

int main() {
  Door watch;
  watch.onStart();
  for (;;)  {
    int i;
    printf("\nEvent<-");
    scanf("%d", &i);
    watch.onEvent(static_cast<Events>(i));
  }
  return 0;
}
