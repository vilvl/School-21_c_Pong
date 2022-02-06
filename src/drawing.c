#include <stdio.h>

#define
#define
int x = 80;
int y = 0;
void draw(ball_x, ball_y, racket1, racket2)
    {
while (y != 26 ) {
    y = y + 1;
    for(int i = 0; x >= i; i++) {
        if((y == 1) || (y == 26)) {
            printf("-");
        } else {
            if(((i == 0) || (i == 80)) && ((y != 1) || (y != 26))) {
                printf("|");
            } else {
                if ((y == 2) && (i == 40)) {
                    printf("%d||%d", 0, 0);
                    i+=4;
                }
                for(int j = 0; j < 3; j++) {
                if((i == 3) && (y == racket1+j)) {
                    printf("]");
                    i+=1;
                    }
                }
                for(int b = 0; b < 3; b++) {
                if((i == 76) && (y == racket2+b)) {
                    printf("[");
                    i+=1;
                    }
                }
                if((i == ball_x) && (y == ball_y)) {
                    printf("*");
                    i+=1;
                }
            }
            printf(" ");
        }
    }
    printf("\n");
    }
}

  int main()
  {
      
      draw();
    
      return 0;
  }
