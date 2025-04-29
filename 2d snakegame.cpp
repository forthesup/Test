#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 20
#define HEIGHT 20
#define MAX_SNAKE_LENGTH 100

typedef struct {
    int x, y;
} Point;

Point snake[MAX_SNAKE_LENGTH];
int snakeLength;
Point food;
int score;
char direction;
int gameOver;

void initializeGame() {
    snakeLength = 2;
    snake[0].x = WIDTH / 2;
    snake[0].y = HEIGHT / 2;
    direction = 'w';
    score = 0;
    gameOver = 0;

    food.x = rand() % WIDTH;
    food.y = rand() % HEIGHT;
}

void draw() {
    system("cls");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1) {
                printf("#");
            } else if (x == food.x && y == food.y) {
                printf("F");
            } else {
                int isSnake = 0;
                for (int i = 0; i < snakeLength; i++) {
                    if (snake[i].x == x && snake[i].y == y) {
                        printf("O");
                        isSnake = 1;
                        break;
                    }
                }
                if (!isSnake) {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}

void input() {
    if (_kbhit()) {
        char newDirection = _getch();
        if ((newDirection == 'w' || newDirection == 'a' || newDirection == 's' || newDirection == 'd') &&
            abs(direction - newDirection) != 2) {
            direction = newDirection;
        }
    }
}

void logic() {
    // Move the snake body
    for (int i = snakeLength - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    // Move the snake head
    if (direction == 'w') snake[0].y--;
    if (direction == 'a') snake[0].x--;
    if (direction == 's') snake[0].y++;
    if (direction == 'd') snake[0].x++;

    // Check for collisions with walls
    if (snake[0].x <= 0 || snake[0].x >= WIDTH - 1 || snake[0].y <= 0 || snake[0].y >= HEIGHT - 1) {
        gameOver = 1;
    }

    // Check for collisions with itself
    for (int i = 1; i < snakeLength; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            gameOver = 1;
        }
    }

    // Check if the snake eats the food
    if (snake[0].x == food.x && snake[0].y == food.y) {
        score++;
        snakeLength++;
        food.x = rand() % (WIDTH - 2) + 1;
        food.y = rand() % (HEIGHT - 2) + 1;
    }
}

int main() {
    initializeGame();
    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(100);
    }
    printf("Game Over! Final Score: %d\n", score);
    return 0;
}

