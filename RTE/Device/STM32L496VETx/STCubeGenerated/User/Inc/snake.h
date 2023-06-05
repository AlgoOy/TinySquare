#ifndef __SNAKE_H
#define __SNAKE_H

// struct Point
// {
//     uint8_t x;
//     uint8_t y;
// };

// typedef struct Snake Snake;

// struct Snake {
//     int size;
//     int direction;
//     int speed;
//     struct Point location;
// }

void DrawStartGamePanel(void);
void DrawEndGamePanel(void);
void DrawRunningGamePanel(void);

void CreateBoard(void);
void CreateSnake(void);
void CreateFruit(void);

#endif