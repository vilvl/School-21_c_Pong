//I WANT TO PLAY WITH YOU
//        YOUR FRIEND, AI

#include <stdio.h>
#include <conio.h>
int main() {
  while ((score_left != 21) || (score_right !=21)) {
    input();
    logic();
    ball_movement_and_update_score(5, 1)
  }
}
void input()
{
  if (kbhit()) {
    switch (getch()) {
    case 'a':
      flag = 1;
      break;
    case 'z':
      flag = 2;
      break;
    case 'k':
      flag = 3;
      break;
    case 'm':
      flag = 4;
      break;
    }
  }
}
void logic()
{
  sleep(0.01);
  switch (flag) {
  case 1:
    change_position(height_left, 2);
    break;
  case 2:
     change_position(height_left, -2);
    break;
  case 3:
     change_position(height_right, 2);
    break;
  case 4:
      change_position(height_right, -2);
    break;
  default:
    break;
  }
void change_position (int &height, int &change){
  int max_height= 25;//сюда пишем максимальную высоту положения ракетки
  int min_height= 3; //сюда пишем минимальную высоту
  if ((height + change < 25) && (height + change > 3)) {
    height += change;
  }
}
// dir отвечает за то, в какой плоскости мы меняем направление, если ударились о горизонтальную поверхность - 1 , в ином случае - 0
void change_direction (int &Vx, int &Vy, int &hor_or_vert) {
  if (hor_or_vert == 1) {
    Vy *= -1;
  }
  if (hor_or_vert == 0) {
    Vx *= -1;
  }
}
void change_score (int &Vx, int &score_left, int &score_right) {
  if (Vx > 0) {
    score_left += 1;
  } else {
    score_right += 1;
  }
}
void ball_movement_and_update_score (int &Vx, int &Vy, int &X, int &Y, int &height_right, int &height_left, int &score_left, int &score_right) {
  if ((Y + Vy >= 25) || (Y + Vy <= 0)) {
    if (Y + Vy >= 25){
      Y = 25;
    } else {
      Y = 0;
    }
    change_direction(Vx, Vy, 1);
  }
  if ((X + Vx <= 10) || (X + Vx >= 70) {
    int dy;
    if (X + Vx <= 10) {
      dy = (X - 10) * Vy / Vx;
    } else {
      dy = (70 - x) * Vy / Vx;
    }
    if (Vx < 0){
    if ((height_left >= Y) && (height_left - Y < 3)) {
      change_direction(Vx, Vy, 0);
    }
    } else {
      if ((height_right >= Y) && (height_right - Y < 3)) {
            change_direction(Vx, Vy, 0);
          }
    }
    if ((X + Vx <= 0) || (X + Vx >= 80)) {
   // вызываем функцию изменения счета и спавним шарик на начальную позицию
    change_score(Vx, score_left, score_right);
    X = 40;
    Y = 12;
  }
  }
  X += Vx;
  Y += Vy;
}
