//============================================================================
// Name        : SDLScrolling.cpp
// Author      : Kevin Navero
// Version     :
// Copyright   :
// Description : SDL Scrolling Test
//============================================================================

#include <iostream>
#include <vector>
#include "SDLAbstractionLayer.h"
#include "Objects.h"

#include "Editor/Editor.h"

using namespace std;

const bool EDIT = true;
const bool PLAY = true;

// TODO integrate A* algorithm in here. When Player grabs a GrabbableFigure and arm must
// be drawn from the Player to the GrabbableFigure object along the "shortest" path

/*
 * Description: This client simply tests the API and its capabilities of creating a
 * simple 2d scrolling platform game. This will serve as an example reference for now.
 */
int main(int argc, char* argv[]) {

   // editing the level
   if (EDIT) {
      // Setup
      // ----------------------------------------------------------------------------
      // declare basic event loop variables
      bool quit = false;   // boolean quit to exit out of event loop
      SDL_Event event;     // SLD_Event event to receive inputs
      Timer timer;         // timer to make movement framerate independent

      // set up editor and the file (containing the figures and their positions) to
      // read from. Use Header object to read header information of level.txt
      Editor* editor = new Editor;
      editor->setFile("resources/level.txt", Editor::read);
      Header* info = editor->readHeader();

      // initialize screen, video mode, SDL, ttf, audio, etc.
      SDL_Surface* screen = init(info->screen_w, info->screen_h,
            "SDL Scrolling");

      // instantiate any images needed
      Surface bgnd(info->bg_path.c_str());            // grabbed from level.txt
      Surface dot("images/dot.png", Surface::CYAN); // dot will be our invisible collision circle

      // collision vector - contains all the Figures (pointers to Figures) that
      // must be taken into account in regards to collision detection with the player
      vector<Figure*>* collisions = editor->decode();

      // set up a MouseFigure object which will be your "hand" that places and removes
      // objects on the screen
      printf("Starting mousefig...");
      MouseFigure mouseFig(0, 0, &dot, screen, info->bg_w, info->bg_h, 1);
      mouseFig.setHeader(info);
      mouseFig.setContainer(collisions);
      printf("done!\n");

      // close the file connection
      editor->closeFile();

      // Body
      // ----------------------------------------------------------------------------
      // start the timer and begin the event loop
      timer.start();

      while (!quit) {
         if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
               quit = true;

            // receive input for Player Figure
            mouseFig.handleInput(event);
         }

         //check for container mismatch (due to loading errors)
         if (collisions != mouseFig.container)
            collisions = mouseFig.container; //assume that mouse Fig's copy is right

         // Move player to new position
         mouseFig.move(*collisions, timer.getTicks());

         // restart timer since movement is time-based and independent of framerate
         timer.start();

         // blit background image to screen with respect to the camera following Player Figure
         applySurface(0, 0, bgnd, screen, mouseFig.getCameraClip());

         // draw all figures but temp Figs and player
         for (unsigned int i = 0; i < collisions->size(); i++) {
            (*collisions)[i]->show(mouseFig.getCameraClip());
         }

         // draw the tempMouseFigure if there is one
         if (mouseFig.tempObject != NULL)
            mouseFig.tempObject->show(mouseFig.getCameraClip());

         // update the screen by swapping video buffers
         flip(screen);
      }

      // Teardown
      // ----------------------------------------------------------------------------
      // free allocated memory and teardown with cleanUp()
      for (vector<Figure*>::iterator i = collisions->begin(), end =
            collisions->end(); i != end; i++) {
         delete *i;
      }
      delete collisions;
      delete editor;
      delete info;
      cleanUp();
   }

   // play the level you created!
   if (PLAY) {
      // Setup
      // ----------------------------------------------------------------------------
      // declare variables for the speed, gravity, jump strength affecting the player.
      // Declare variables specifying the number of clips existing on one row on the
      // sprite sheet (assuming only two rows for left and right directions). Declare
      // basic event loop variables - quit, event, timer.
      double FS = 200;     // figure speed
      double G = 4;        // gravity
      double FJS = 3;      // figure jump strength
      int FNC = 4;         // figure number of clips

      bool quit = false;   // boolean quit to exit out of event loop
      SDL_Event event;     // SDL_Event to receive inputs
      Timer timer;         // Timer to make movement framerate independent

      // set up editor and the file (containing the figures and their positions) to
      // read from. Use Header object to read header information of level.txt
      Editor* editor = new Editor;
      editor->setFile("resources/level.txt", Editor::read);
      Header* info = editor->readHeader();

      // initialize screen, video mode, SDL, ttf, audio, etc.
      SDL_Surface* screen = init(info->screen_w, info->screen_h,
            "SDL Scrolling");

      // instantiate any images needed
      Surface bgnd(info->bg_path.c_str());   // grabbed from level.txt
      Surface foo("images/Cyan_Final.png", Surface::BLACK);

      // collision vector - contains all the Figures (pointers to Figures) that
      // must be taken into account in regards to collision detection with the player
      vector<Figure*>* collisions = editor->decode();

      // create a player you want to play as and push it to the collisions container
      PlayerFigure *rf = new PlayerFigure(100,
            info->bg_w - foo.getSDL_Surface()->h / 2, foo, screen, FS, G, FJS,
            FNC, info->bg_w, info->bg_h);
      collisions->push_back(rf);

      // start music and set volume
      Music m("resources/tristam.mp3");
      if (Mix_PlayingMusic() == 0) {
         if (Mix_PlayMusic(m.getMix_Music(), -1) < 0)
            throw SoundException();

         Mix_VolumeMusic(32); //0 to 128
      }

      // close the file connection
      editor->closeFile();

      // Body
      // ----------------------------------------------------------------------------
      // start the timer and begin event loop
      timer.start();

      while (!quit) {
         if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
               quit = true;

            // receive input for Player Figure
            rf->handleInput(event);
         }

         // move Player Figure to new position based on input given
         rf->move(*collisions, timer.getTicks());

         // restart timer since movement is time-based and independent of framerate
         timer.start();

         // blit background image to screen with respect to the camera following Player Figure
         applySurface(0, 0, bgnd, screen, rf->getCameraClip());

         // update and draw all figures within the collisions vector
         for (unsigned int i = 0; i < collisions->size(); i++) {
            // if a coin is found
            if (typeid(*(*collisions)[i]) == typeid(TempFigure)) {
               TempFigure* t = static_cast<TempFigure*>((*collisions)[i]);
               t->move(*collisions, 0);   // the coin needs to disappear/update (hence the
                                          // move method) but not move in the
                                          // x or y direction (hence the 0 as the 2nd arg)
               t->show(rf->getCameraClip());
            }

            // if the figure is not a coin
            else
               (*collisions)[i]->show(rf->getCameraClip());
         }

         // show the Player Figure
         rf->show();

         // update the screen by swapping video buffers
         flip(screen);
      }

      // Teardown
      // ----------------------------------------------------------------------------
      // stop music
      Mix_HaltMusic();

      // free dynamically allocated data and use cleanUp()
      for (vector<Figure*>::iterator i = collisions->begin(), end =
            collisions->end(); i != end; i++) {
         delete *i;
      }
      delete collisions;
      delete editor;
      delete info;
      cleanUp();
   }

   return 0;
}
