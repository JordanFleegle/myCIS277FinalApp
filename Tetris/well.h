#pragma once
#include "tetrominos.h"
#include <SDL.h>

class Well {
public:
   enum { WIDTH = 10, HEIGHT = 20 };
   Well();
   void draw(SDL_Renderer *);
   bool isCollision(const Tetromino &t) const;
   void plant(const Tetromino &);
private:
   bool data[WIDTH][HEIGHT];
};