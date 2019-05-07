#pragma once
#include<SDL.h>

class Tetromino {
public:

   enum Type {I , J, L, S, T, O, Z}; //type of block
   Tetromino(Type);
   void draw(SDL_Renderer *);             // draws and fills blocks
   bool block(int, int) const;            // block collission information
   void move(int, int);                   // movement controlled with asd
   void rotate();                         // rotate with w
   void initialXCorrection(int);
   void initialYCorrection(int);
   static const int initialPos[7][2];
   int getType();
   int getX() const;
   int getY() const;
private:
   Type type_;
   int x_;
   int y_;
   int angle_; // 0 - 0deg, 1 - 90deg, 2 - 180deg, 3 - 270deg
};