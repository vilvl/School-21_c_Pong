#include <stdio.h>

#define FIELD_WIDTH 80
#define FIELD_HIGHT 25
#define RACKET_WIDTH 3
#define RACKET_SHIFT 3

int check_racket(int x, int y, int shift, int racket) {
    for ( int j = 0; j < RACKET_WIDTH; ++j ) {
        if ( x == shift && y == racket + j )
            return 1;
    }
    return 0;
}

void draw(ball_x, ball_y, racket1, racket2, score1, score2) {
    for (int y = 0; y <= FIELD_HIGHT - 1; y++ ) {
        for(int x = 0; x <= FIELD_WIDTH - 1; x++) {
            // score
            if ( (y == 0) && ( x == FIELD_WIDTH / 2 - 3 ) ) {
                    printf("_%2d||%2d_", score1, score2);
                    x +=7;
            // borders
            } else if (y == 0 || y == FIELD_HIGHT - 1) {
                printf("-");
            } else if (x == 0 || x == FIELD_WIDTH - 1) {
                printf("|");
            // rackets
            } else if (check_racket(x ,y, RACKET_SHIFT, racket1)) {
                printf("]");
            } else if (check_racket(x, y, FIELD_WIDTH - RACKET_SHIFT, racket2)) {
                printf("[");
            // ball
            } else if (x == ball_x && y == ball_y) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}



int main()
{
    int x, y, r1, r2, s1, s2;
    while (1) {
        scanf("%d %d %d %d %d %d ", &x, &y, &r1, &r2, &s1, &s2);
        draw(x, y ,r1 , r2, s1, s2);
        printf("\n\n\n\n\n\n\n\n");
    }
    return 0;
  }
