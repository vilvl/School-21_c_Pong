// #include <stdio.h>
// #include <termios.h>

// int main() {
//
//    struct termios info;
//    /* get current terminal attirbutes; 0 is the file descriptor for stdin */
//    tcgetattr(0, &info);
//    /* disable canonical mode */
//    info.c_lflag &= ~ICANON;
//    /* wait until at least one keystroke available */
//    info.c_cc[VMIN] = 1;
//    /* no timeout */
//    info.c_cc[VTIME] = 0;
//    /* set immediately */
//    tcsetattr(0, TCSANOW, &info);
//
//    // c_cc[VMIN] = 0;
//    char a = n;
//    while (1) {
//        a = getchar();
//        printf("%c\n", a);
//        if (a=='t') break;
//    }
//
//    tcgetattr(0, &info);
//    info.c_lflag |= ICANON;
//    tcsetattr(0, TCSANOW, &info);
//    return 0;
// }
//

#include <stdio.h>

#define LEFT 0
#define RIGHT 1

#define L_UP 'a'
#define L_DOWN 'z'
#define L_NO ' '
#define R_UP 'k'
#define R_DOWN 'm'
#define R_NO ' '
#define GAMEOVER_KEY 't'

#define EXIT -2

int main() {

    int gameover = 0;
    int inp = 0;
    int ball_x, ball_y, ball_VX, ball_VY;

    init_ball();
    init_pong();

    // base game
    while (1) {
        // first player
        racket_move = handle_input(L_UP, L_DOWN, L_NO);
        if (racket_move == EXIT) {
            break;
        }
        mv_racket(LEFT, racket_move);
        // second player
        racket_move = handle_input(L_UP, L_DOWN, L_NO);
       if (racket_move == EXIT) {
            break;
        }
        mv_racket(RIGHT, handle_input);
        
        update_score(mv_ball() 
    }

    if (racket_move == EXIT) {
        return 1;
    }

}

int handle_input(char up, char down, char no_event) {
    char key;
    while (scanf("%c", &key) == 1) {
        switch(key) {
            case up:
                return 1;
            case down:
                return -1;
            case no_event:
                return 0;
            case GAMEOVER_KEY:
                return -2;
        }
        printf("\r                \rwrong input");
    }
    printf("\r                \rwrong input");
    return 0;
}

void init_pong() {
    draw(
            FIELD_WITH / 2, FIELD_HEIGHT / 2,
            FIELD_HEIGHT / 2, FIELD_HEIGHT / 2, 
            0, 0);
}
