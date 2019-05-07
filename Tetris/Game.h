#pragma once
#include <SDL.h>
#include "well.h"

class Game {
public:
   Game();
   ~Game();
   bool tick(); // main game loop
private:
   Game(const Game &);
   //Game &operator=(const Game &);
   SDL_Window *window_;             // object to define window properties
   SDL_Renderer *renderer_;         // object to render to the window
   Tetromino tetromino_;            // the current falling tetromino
   Well well_;
   Uint32 moveTime_;                // timer for tetromino movement
   void check(const Tetromino &);
};