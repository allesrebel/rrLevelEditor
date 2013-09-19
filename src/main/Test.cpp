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
#include "Exception.h"
#include "Figure.h"
#include "RectBoundaryFigure.h"
#include "CircBoundaryFigure.h"
#include "TempFigure.h"
#include "PlayerFigure.h"
#include "MouseFigure.h"
#include "GrabbableFigure.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#include "Editor/Editor.h"

using namespace std;

const int FRAMERATE = 30;

const bool OTHER_LEADER = false;
const double OTHER_SPEED = 0;
const double OTHER_GRAVITY = 0;
const double OTHER_JUMPSTRENGTH = 0;
const int OTHER_NUMCLIPS = 1;

const string TTF_PATH = "fonts/lazy.ttf";
const int FONT_SIZE = 28;
const Surface::Color FONT_COLOR = Surface::BLACK;

const bool EDIT = true;
const bool PLAY = true;


//TODO: there is a bug in where a single (or multiple) GrabbableFigure(s) exists and
//PlayerFigure is incapable of jumping for some reason

/*
 * Description: This client simply tests the API and its capabilities of creating a
 * simple 2d scrolling platform game. This will serve as an example for now.
 */
int main(int argc, char* argv[]) {

   //editor test
   Editor* editor = new Editor;
   editor->setFile("resources/level.txt", Editor::read);
   Header* info = NULL;
   info = editor->readHeader();

   //initialize screen, video mode, SDL, ttf, audio, etc.
   SDL_Surface* screen = init(info->screen_w, info->screen_h, "SDL Scrolling");

   //initialize all images
   Surface bgnd(info->bg_path.c_str());
   Surface dot("images/dot.png", Surface::CYAN);

   //collision vector - contains all the Figures (pointers to Figures) that
   //must be taken into account in regards to collision detection
   vector<Figure*>* collisions = NULL;

   printf("Starting mousefig...");
   MouseFigure mouseFig(0, 0, &dot, screen, info->bg_w, info->bg_h, 1);
   mouseFig.setHeader(info);
   printf("done!\n");

   //Prepare music to be played within level
   Music m("resources/tristam.mp3");

   collisions = editor->decode();
   mouseFig.setContainer(collisions);

   //Prepare bool quit variable, SDL_Event event, and Timer timer. All of these
   //variables will be used in the event loop
   bool quit = false;
   SDL_Event event;
   Timer timer;
   timer.start();

   editor->closeFile();

   //Start event loop

   if (EDIT) {
      while (!quit) {
         if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
               quit = true;

            //receive input for Player Figure
            mouseFig.handleInput(event);
         }

         //check for container mismatch (due to loading errors)
         if (collisions != mouseFig.container) {
            //assume that mouse Fig's copy is right
            collisions = mouseFig.container;
         }

         // Move player to new position
         mouseFig.move(*collisions, timer.getTicks());

         //restart timer since movement is time-based and independent of framerate
         timer.start();

         //blit background image to screen with respect to the camera following Player Figure
         applySurface(0, 0, bgnd, screen, mouseFig.getCameraClip());

         //draw all figures but temp Figs and player
         for (unsigned int i = 0; i < collisions->size(); i++) {
            (*collisions)[i]->show(mouseFig.getCameraClip());
         }

         //draw the tempMouseFigure if there is one
         if (mouseFig.tempObject != NULL)
            mouseFig.tempObject->show(mouseFig.getCameraClip());

         //update the screen by swapping video buffers
         flip(screen);
      }
   }

   if (PLAY) {
      quit = false;
      double FS = 200;
      double G = 4;
      double FJS = 3;
      int FNC = 4;

      //Start music and set volume
      if (Mix_PlayingMusic() == 0)
         if (Mix_PlayMusic(m.getMix_Music(), -1) < 0)
            throw SoundException();

      Mix_VolumeMusic(32); //0 to 128

      Surface foo("images/Cyan_Final.png", Surface::BLACK);

      PlayerFigure rf(100, info->bg_w - foo.getSDL_Surface()->h / 2, foo,
            screen, FS, G, FJS, FNC, info->bg_w, info->bg_h);

      editor = new Editor;
      editor->setFile("resources/level.txt", Editor::read);
      info = editor->readHeader();
      vector<Figure*>* collisions = editor->decode();
      collisions->push_back(&rf);

      while (!quit) {
         if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
               quit = true;

            //receive input for Player Figure
            rf.handleInput(event);
         }

         //move Player Figure to new position based on input given
         rf.move(*collisions, timer.getTicks());

         //restart timer since movement is time-based and independent of framerate
         timer.start();

         //blit background image to screen with respect to the camera following Player Figure
         applySurface(0, 0, bgnd, screen, rf.getCameraClip());

         //draw all figures but temp Figs and player
         for (unsigned int i = 0; i < collisions->size(); i++) {
            if (typeid(*(*collisions)[i]) == typeid(TempFigure)) {
               TempFigure* t = static_cast<TempFigure*>((*collisions)[i]);
               t->move(*collisions, 0);
               t->show(rf.getCameraClip());
            }
            else
               (*collisions)[i]->show(rf.getCameraClip());
         }

         //show the Player Figure
         rf.show();

         //update the screen by swapping video buffers
         flip(screen);
      }

      //stop music
      Mix_HaltMusic();
   }

   //quit out of SDL, close audio, ttf, etc.
   cleanUp();

   return 0;
}
