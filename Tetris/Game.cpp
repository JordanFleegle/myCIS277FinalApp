#include "Game.h"
#include "tetrominos.h"
#include <stdexcept>

Game::Game(): /*initialization list*/tetromino_{static_cast<Tetromino::Type>(rand() % 7)}, moveTime_(SDL_GetTicks()) {
   if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      throw std::runtime_error("SDL_Init(SDL_INIT_)VIDEO)\n");
   }

   SDL_CreateWindowAndRenderer(720 / 2, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS, &window_, &renderer_);    //initializes the game window and renderer objects
   SDL_SetWindowPosition(window_, 65, 126);
}

Game::~Game() {
   SDL_DestroyRenderer(renderer_);
   SDL_DestroyWindow(window_);
   SDL_Quit();                   // these handle garbage collection
}

// handles game clock, collisions, and player input
bool Game::tick() {
   SDL_Event event;
   if (SDL_WaitEventTimeout(&event, 250)){
      switch (event.type){
         case SDL_KEYDOWN: // TODO: might refactor controls to add drop functionality, but this wasn't in the first version of tetris 
            switch(event.key.keysym.sym){
               case SDLK_s: { // down move
               Tetromino t = tetromino_;
               t.move(0, 1);
               if (!well_.isCollision(t))
                  tetromino_ = t;
               }
               break;
               case SDLK_w: { // rotate
                  Tetromino t = tetromino_;
                  t.rotate();
                  if (!well_.isCollision(t))
                     tetromino_ = t;
               }
               break;
               case SDLK_d: { //right move
                  Tetromino t = tetromino_;
                  t.move(1, 0);
                  if (!well_.isCollision(t))
                     tetromino_ = t;
               }
               break;
               case SDLK_a: { // left move
                  Tetromino t = tetromino_;
                  t.move(-1, 0);
                  if (!well_.isCollision(t))
                     tetromino_ = t;
               }
               break;
            }
         break;
      case SDL_QUIT:
         return false;
      }   
   }

   SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0xff);
   SDL_RenderClear(renderer_);
   well_.draw(renderer_);                 // draw the well
   tetromino_.draw(renderer_);            // draw current piece
   if (SDL_GetTicks() > moveTime_) {      // drop one block every second
      moveTime_ += 1000;
      Tetromino t = tetromino_;
      t.move(0, 1);
      check(t);
   }
   SDL_RenderPresent(renderer_);
   return true;
};

// checks for collisions and calls appropriate responses
void Game::check(const Tetromino &t){
	if (well_.isCollision(t)){                                           //if a collision occurs...
		well_.plant(tetromino_);                                          // merge the tetromino into the bottom
		tetromino_ = Tetromino{static_cast<Tetromino::Type>(rand() % 7)}; //spawn new tetromino
      tetromino_.initialXCorrection(tetromino_.getType());              //adjust tetromino array to spawn piece in appropriate location
      tetromino_.initialYCorrection(tetromino_.getType());
      if(well_.isCollision(tetromino_)){                                // if the new tetromino collides...    TODO: refactor, this version doesn't catch a clutch line clear.
			well_ = Well();                                                // reset the well                      TODO: maybe just stop the game for a gmae over screen and score display
		}
	} else {
		tetromino_ = t;
	}
}
