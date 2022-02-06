#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#define FIELD_WIDTH 80
#define FIELD_HIGHT 25
#define RACKET_SHIFT 3
#define RACKET_WIDTH 3

#define BALL_MIN_X_SPEED 2
// BALL_MAX_X_SPEED is diff between
// true max speed and min speed
#define BALL_MAX_X_SPEED 5
#define BALL_MAX_Y_SPEED 3

#define L_UP 'a'
#define L_DOWN 'z'
#define R_UP 'k'
#define R_DOWN 'm'
#define GAMEOVER 't'

#define WIN_SCORE 21

int game_loop();
void init_ng(int *l_score, int *r_score);
void init(int *l_racket, int *r_racket,
        double *ball_x, double *ball_y,
        double *ball_VX, double *ball_VY);

int get_direction();
int get_rand_x_speed();
int get_rand_y_speed();

int get_input(int player);

int check_racket(int x, int y, int shift, int racket);
void draw(int ball_x, int  ball_y,
        int racket1, int racket2,
        int score1, int score2, int graz);

void clear_screen(int x);

void mv_racket(int *racket, int mv);

void change_score(int score, int *score_l, int *score_r);

double check_hit(double ball_x, double ball_y,
            double ball_VX, double ball_VY,
            int racket_x);

int mv_ball(double *ball_x, double *ball_y,
            double* ball_VX, double *ball_VY,
            int racket_l, int racket_r);

int main() {
    int l_score, r_score;
    int l_racket, r_racket;
    double ball_x, ball_y;
    double ball_VX, ball_VY;

    int gameover = 0;

    srand(time(NULL));

    init_ng(&l_score, &r_score);
    while (l_score < WIN_SCORE && r_score < WIN_SCORE && !gameover) {
        init(
            &l_racket, &r_racket,
            &ball_x, &ball_y,

            &ball_VX, &ball_VY);
        draw(ball_x, ball_y,
                l_racket, r_racket,
                l_score, r_score, 0);
        gameover = game_loop(
                &ball_x, &ball_y,
                &ball_VX, &ball_VY,
                &l_racket, &r_racket,
                &l_score, &r_score);
    }
    if (!gameover) {
        draw(ball_x, ball_y,
                l_racket, r_racket,
                l_score, r_score, (l_score == WIN_SCORE) ? 1 : 2);
    }
    // printf("\033[20A\033[K|   GRAZ |");
}


int game_loop(double *ball_x, double *ball_y,
            double *ball_VX, double *ball_VY,
            int *racket_l, int *racket_r,
            int *score_l, int *score_r) {
    while (1) {
        int inp1 = get_input(0);
        if (inp1 == 2)
            return 1;
        if (inp1 != 3) {
            mv_racket(racket_l, inp1);
            int inp2 = get_input(1);
            if (inp2 == 2)
                return 1;
            if (inp2 != 3)
                mv_racket(racket_r, inp2);
        }
        fseek(stdin, 0, SEEK_END);

        int score = mv_ball(ball_x, ball_y, ball_VX, ball_VY,
                *racket_l, *racket_r);

        if (score) {
            change_score(score, score_l, score_r);
        }

        draw((int)*ball_x, (int)*ball_y,
                *racket_l, *racket_r,
                *score_l, *score_r, 0);

        if (score) {
            return 0;
        }
    }
}

void change_score(int score, int *score_l, int *score_r) {
    if (score == -1)
        ++*score_r;
    else if (score == 1)
        ++*score_l;
}

int mv_ball(double *ball_x, double *ball_y,
            double *ball_VX, double *ball_VY,
            int racket_l, int racket_r) {
    double hit_y;
    // if hit l_racket x coord
    if (*ball_x + *ball_VX <= RACKET_SHIFT) {
        hit_y = check_hit(*ball_x, *ball_y, *ball_VX, *ball_VY,
                RACKET_SHIFT);
        if (hit_y >= racket_l && hit_y <= racket_l + RACKET_WIDTH) {
            *ball_x = RACKET_SHIFT + 1;
            *ball_y = hit_y;
            *ball_VX = get_rand_x_speed();
            *ball_VY = get_rand_y_speed();
            return 0;
        } else {
            *ball_x = 2;
            *ball_y = hit_y;
            return -1;
        }
    // if hit r_racket x coord
    } else if (*ball_x + *ball_VX >= FIELD_WIDTH - 1 - RACKET_SHIFT) {
        hit_y = check_hit(*ball_x, *ball_y, *ball_VX, *ball_VY,
                FIELD_WIDTH - 1 - RACKET_SHIFT);
        if (hit_y >= racket_r && hit_y <= racket_r + RACKET_WIDTH) {
            *ball_x = FIELD_WIDTH - 1 - RACKET_SHIFT - 1;
            *ball_y = hit_y;
            *ball_VX = -1 * get_rand_x_speed();
            *ball_VY = get_rand_y_speed();
            return 0;
        } else {
            *ball_x = FIELD_WIDTH - 2;
            *ball_y = hit_y;
            return 1;
        }
    }

    *ball_x += *ball_VX;
    *ball_y += *ball_VY;

    if (*ball_y < 1) {
        *ball_y = 1 + 1 - *ball_y;
        *ball_VY = -*ball_VY;
    } else if (*ball_y > FIELD_HIGHT - 1) {
        *ball_y = FIELD_HIGHT - 1 - (*ball_y - FIELD_HIGHT - 1);
        *ball_VY = -*ball_VY;
        if ((int)*ball_y >= FIELD_HIGHT - 1)
            *ball_y = FIELD_HIGHT - 2;
    }
    return 0;
}

double check_hit(double ball_x, double ball_y,
            double ball_VX, double ball_VY,
            int racket_x) {
    double hit_y = ball_y + (racket_x - ball_x) / ball_VX * ball_VY;
    if (hit_y > FIELD_HIGHT - 1) {
        hit_y = FIELD_HIGHT - 1 - (hit_y - FIELD_HIGHT - 1);
    }
    if (hit_y < 1) {
        hit_y = 1 + (1 - hit_y);
    }
    return hit_y;
}

void mv_racket(int *racket, int mv) {
    if (!mv)
        return;
    if (mv > 0 && *racket >= (FIELD_HIGHT - 1 - RACKET_WIDTH))
        return;
    if (mv < 0 && *racket <= 1)
        return;
    *racket += mv;
}

// 0 for L player, 1 for right one
int get_input(int player) {
    char inp;
    scanf("%c", &inp);
    if (!player) {
        switch (inp) {
            case L_UP: return -1;
            case L_DOWN: return 1;
            case GAMEOVER: return 2;
            case '\n': return 3;
        }
    } else {
        switch (inp) {
            case R_UP: return -1;
            case R_DOWN: return 1;
            case GAMEOVER: return 2;
            case '\n': return 3;
        }
    }
    return 0;
}

// INIT GAME /////////////////
void init_ng(
        int *l_score, int *r_score) {
    *l_score = 0;
    *r_score = 0;
    // printf("HELLO_HELLO_HELLO_HELLO\n");
}

void init(int *l_racket, int *r_racket,
        double *ball_x, double *ball_y,
        double *ball_VX, double *ball_VY) {
    *l_racket = FIELD_HIGHT / 2 - RACKET_WIDTH / 2;
    *r_racket = *l_racket;

    *ball_x = FIELD_WIDTH / 2.0;
    *ball_y = FIELD_HIGHT / 2.0;


    *ball_VX = get_direction() * get_rand_x_speed();
    *ball_VY = get_direction() * get_rand_y_speed();
}


// BALL SPEED GENERATION ////////////////////////

// 1 or -1
int get_direction() {
    return (rand() % 2) * 2 - 1;
}

int get_rand_x_speed() {
    return BALL_MIN_X_SPEED + rand() % BALL_MAX_X_SPEED;
}

int get_rand_y_speed() {
    return rand() % BALL_MAX_Y_SPEED;
}

// DRAWINGS ///////////////////////////////////

void draw(
        int ball_x, int ball_y,
        int racket1, int racket2,
        int score1, int score2, int graz) {
    clear_screen(20);
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
            // graz
            } else if (graz && y == 7 && x == FIELD_WIDTH/2 - 14) {
                printf("CONGRATULATIONS PLAYER %d WIN", graz);
                x += 27;
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

void clear_screen(int counter) {
    while (counter > 0) {
        --counter;
        printf("\n");
    }
}

