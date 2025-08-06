#include "./include/raylib.h"
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 450
#define PLAYER_SPEED 200.0f

typedef struct {
  Vector2 position;
  float speed;
} Player;

void updatePlayer(Player *player, float delta) {
  if (IsKeyDown(KEY_LEFT))
    player->position.x -= PLAYER_SPEED * delta;
  if (IsKeyDown(KEY_RIGHT))
    player->position.x += PLAYER_SPEED * delta;
  if (IsKeyDown(KEY_UP))
    player->position.y -= PLAYER_SPEED * delta;
  if (IsKeyDown(KEY_DOWN))
    player->position.y += PLAYER_SPEED * delta;
}

int main(int argv, char **argc) {
  printf("Hello raylib");

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello Raylib");
  SetTargetFPS(60);
  Player player = {0};
  player.position = (Vector2){
      400,
      280,
  };
  player.speed = 0;

  while (!WindowShouldClose()) {
    float delta = GetFrameTime();

    updatePlayer(&player, delta);

    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    Rectangle playrect = {player.position.x, player.position.y, 20.0f, 20.0f};
    // DrawRectangle(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 20, 20, RED);
    DrawRectangleRec(playrect, RED);
    EndDrawing();
  }
  CloseWindow();
}