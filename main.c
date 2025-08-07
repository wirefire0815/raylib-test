#include "./include/raylib.h"
#include <stdio.h>
#include <string.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 450
#define PLAYER_SPEED 200.0f

typedef enum { LEFT, RIGHT, UP, DOWN } Direction;

typedef struct {
  Rectangle rect;
  Direction direction;
} Player;

typedef struct {
  Rectangle rect;
  Color color;
} Obstacle;

void updatePlayer(Player *player, Obstacle obstacles[], int obstaclesLength,
                  float delta);

int main(int argv, char **argc) {
  printf("Hello raylib");

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello Raylib");
  SetTargetFPS(60);
  Player player = {0};
  player.rect = (Rectangle){0, 0, 20.0f, 20.0f};
  player.direction = 0;

  Obstacle obstacles[] = {
      {{300, 250, 100, 50}, BLACK},  {{300, 250, 90, 40}, YELLOW},
      {{600, 350, 100, 300}, LIME},  {{690, 420, 500, 100}, GOLD},
      {{120, 90, 200, 450}, PURPLE}, {{420, 69, 30, 30}, MAROON},
  };
  int obstaclesLength = sizeof(obstacles) / sizeof(obstacles[0]);

  while (!WindowShouldClose()) {
    float delta = GetFrameTime();

    updatePlayer(&player, obstacles, obstaclesLength, delta);

    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    for (int i = 0; i < obstaclesLength; i++)
      DrawRectangleRec(obstacles[i].rect, obstacles[i].color);

    Rectangle playrect = {player.rect.x, player.rect.y, player.rect.width,
                          player.rect.height};
    // DrawRectangle(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 20, 20, RED);
    DrawRectangleRec(playrect, RED);
    EndDrawing();
  }
  CloseWindow();
}

bool checkCollisionRect(Rectangle r1, Rectangle r2) {
  return r1.x < r2.x + r2.width && r1.x + r1.width > r2.x &&
         r1.y < r2.y + r2.height && r1.y + r1.height > r2.y;
}

void updatePlayer(Player *player, Obstacle obstacles[], int obstaclesLength,
                  float delta) {
  float dx = player->rect.x, dy = player->rect.y;

  if (IsKeyDown(KEY_LEFT)) {
    dx -= PLAYER_SPEED * delta;
    player->direction = LEFT;
  }
  if (IsKeyDown(KEY_RIGHT)) {
    dx += PLAYER_SPEED * delta;
    player->direction = RIGHT;
  }
  if (IsKeyDown(KEY_UP)) {
    dy -= PLAYER_SPEED * delta;
    player->direction = UP;
  }
  if (IsKeyDown(KEY_DOWN)) {
    dy += PLAYER_SPEED * delta;
    player->direction = DOWN;
  }

  bool hitObstacle = false;
  Rectangle *hitter;

  for (int i = 0; i < obstaclesLength; i++) {
    if (player->rect.x < obstacles[i].rect.x + obstacles[i].rect.width) {
      Rectangle *oi = &(obstacles + i)->rect;
      Rectangle *p = &(player->rect);
      if (checkCollisionRect(*p, *oi)) {
        hitObstacle = true;
        memcpy(hitter, oi, sizeof(Rectangle));
        break;
      }
    }
  }

  if (!hitObstacle) {
    player->rect.x = dx;
    player->rect.y = dy;
  } else {

    while (!checkCollisionRect(player->rect, *hitter)) {
      switch (player->direction) {
      case LEFT: {
        player->rect.x -= 10;
      } break;
      case RIGHT: {
        player->rect.x += 10;
      } break;
      case UP: {
        player->rect.y -= 10;
      } break;
      case DOWN: {
        player->rect.y += 10;
      } break;
      }
    }
  }
}