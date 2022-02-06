#include <stdio.h>

#define FIELD_WIDTH 80
#define FIELD_HIGHT 25
#define RACKET_WIDTH 3
#define RACKET_SHIFT 3

int check_racket(int x, int y, int shift, int racket);
void draw(int ball_x, int  ball_y,
        int racket1, int racket2,
        int score1, int score2);

int main() {
    int x, y, r1, r2, s1, s2;
    while (1) {
        scanf("%d %d %d %d %d %d", &x, &y, &r1, &r2, &s1, &s2);
        draw(x, y, r1, r2, s1, s2);
        printf("\n\n\n\n\n\n\n\n");
    }
    return 0;
}


void draw(
        int ball_x, int ball_y,
        int racket1, int racket2,
        int score1, int score2) {
    for (int y = 0; y <= FIELD_HIGHT - 1; y++) {
        for (int x = 0; x <= FIELD_WIDTH - 1; x++) {
            // score
            if ( (y == 0) && (x == FIELD_WIDTH / 2 - 3 ) ) {
                    printf(" %02d||%02d ", score1, score2);
                    x += 7;
            // borders
            } else if  ((y == 0 || y == FIELD_HIGHT - 1)
                    && (x == 0 || x == FIELD_WIDTH - 1)) {
                printf("#");
            } else if (y == 0 || y == FIELD_HIGHT - 1) {
                printf("-");
            } else if (x == 0 || x == FIELD_WIDTH - 1) {
                printf("|");
            // rackets
            } else if (check_racket(x, y, RACKET_SHIFT, racket1)) {
                printf("]");
            } else if (check_racket(x, y, FIELD_WIDTH - 1 - RACKET_SHIFT, racket2)) {
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

int check_racket(int x, int y, int shift, int racket) {
    for ( int j = 0; j < RACKET_WIDTH; ++j ) {
        if ( x == shift && y == racket + j )
            return 1;
    }
    return 0;
}

