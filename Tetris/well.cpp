#include "well.h"

Well::Well():
   data{ {false} } {
   
}
// draws planted blocks
void Well::draw(SDL_Renderer *renderer){
   SDL_SetRenderDrawColor(renderer, 0xbe, 0xfa, 0xaa, 0xff);
   for (int x = 0; x < WIDTH; ++x)
      for (int y = 0; y < HEIGHT; ++y) {
         if (data[x][y]) {
            SDL_Rect Lrect{ x * 720 / 2 / 10 + 1, y * 720 / 2 / 10 + 1, 720 / 2 / 10 / 2 - 2, 720 / 2 / 10 - 2 }; //left half of block
            SDL_Rect Rrect{ x * 720 / 2 / 10 + 1 + (18), y * 720 / 2 / 10 + 1, 720 / 2 / 10 / 2 - 2, 720 / 2 / 10 - 2 }; //right half of block
            SDL_RenderFillRect(renderer, &Lrect);
            SDL_RenderFillRect(renderer, &Rrect);
            //SDL_Rect rect{ x * 720 / 2 / 10/*x corner*/, y * 720 / 2 / 10/*y corner*/, 720 / 2 / 10/*width*/, 720 / 2 / 10/*height*/ };
            //SDL_RenderFillRect(renderer, &rect);
         }
         else {
            SDL_RenderDrawPoint(renderer, x * 720 / 2 / 10 + 720 / 2 / 10 / 2,
               y * 720 / 2 / 10 + 720 / 2 / 10 / 2);

         }
      }
}
// checks the well collision data
bool Well::isCollision(const Tetromino &t) const {
   for (int x = 0; x < 5; ++x)
      for (int y = 0; y < 5; ++y)
         if (t.block(x, y))
         {
            int wx = t.getX() + x; 
             int wy = t.getY() + y;
            if (wx < 0 || wx >= WIDTH || wy < 0 || wy >= HEIGHT)
               return true;
            if (data[wx][wy])
               return true;
         }
   return false;
}


/*TODO: this method only allows one row to be removed per clear, but will allow clears to stack,
   so additional rows will remove at the same time as other rows in a successive clear, gonna have to figure that mess out*/
void Well::plant(const Tetromino &t){                //adds the cuurent tetromino to the bottom of the well
   for (int x = 0; x < 5; ++x)
      for (int y = 0; y < 5; ++y)
         if (t.block(x, y))
            data[t.getX() + x][t.getY() + y] = true; // add block and collision data to well

   for (int y = HEIGHT - 1; y >= 0; --y) {           //check every row from the bottom up
      bool solid = true;
      for (int x = 0; x < WIDTH; ++x)
         if (!data[x][y]) {
            solid = false;
            break;
         }
      //TODO: this should probably be its own method
      if (solid) {                                   // if an entire row is occupied
         for (int dropY = y - 1; dropY >= 0; --dropY)
            for (int x = 0; x < WIDTH; ++x)
               data[x][dropY + 1] = data[x][dropY];  //drop all rows down one 
         for (int x = 0; x < WIDTH; ++x)
            data[x][0] = false;                      //new clear row for the top of the well
      }
   }
}
