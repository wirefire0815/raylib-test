#include "./include/raylib.h"
#include <stdio.h>

int main(int argv, char **argc) {
  printf("Hello raylib");

  InitWindow(800, 450, "Hello Raylib");
  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    DrawText("Hallo", 10, 0, 20, BLACK);
    EndDrawing();
  }
  CloseWindow();
}