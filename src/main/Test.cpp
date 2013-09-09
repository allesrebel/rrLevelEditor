//============================================================================
// Name        : SDLScrolling.cpp
// Author      : Kevin Navero
// Version     :
// Copyright   : 
// Description : SDL Scrolling Test
//============================================================================
#include <iostream>
#include "SDLAbstractionLayer.h"
#include "Exception.h"
#include "Figure.h"
#include "MouseFigure.h"
#include "Editor/Editor.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

using namespace std;

const string TTF_PATH = "fonts/lazy.ttf";
const int FONT_SIZE = 28;
const Surface::Color FONT_COLOR = Surface::BLACK;

const bool FOO = true; //change this from true or false to choose between a stick figure
//or dot ("FOO = true" is the stick figure)

const Figure::Gravity gravEnDis = Figure::GRAVITY_ENABLED;
//const Figure::Gravity gravEnDis = Figure::GRAVITY_DISABLED;

const bool TEST_GRAPHICS = true;
const bool TEST_STRING_INPUT = false;

/*Description: This tests the scrolling, collision detection, static figures within the level,
 *and animation. User can switch const bool FOO to true/false and comment/uncomment const
 *Figure::Gravity gravEnDis for Enabling and Disabling gravity
 */
int main(int argc, char* argv[]) {
	if (TEST_GRAPHICS) {

		//Just for testing
		//Load background and level defaults
		Editor edit;

		edit.setFile("resources/default", Editor::read);
		edit.readHeader();

		Header windowProperties = *edit.headerInfo;

		const int LEVEL_WIDTH = edit.headerInfo->bg_w;
		const int LEVEL_HEIGHT = edit.headerInfo->bg_h;
		const int SCREEN_WIDTH = edit.headerInfo->screen_w;
		const int SCREEN_HEIGHT = edit.headerInfo->screen_h;

		SDL_Surface* screen = init(SCREEN_WIDTH, SCREEN_HEIGHT, "SDL Scrolling");

		Surface bgnd(edit.headerInfo->bg_path.c_str());
		Surface dot("images/dot.png", Surface::CYAN);
		Surface foo("images/Cyan_Final.png", Surface::BLACK);
		Surface rect("images/rectangle.png");
		Surface coin("images/coin.png", Surface::CYAN);

		Surface red("images/red.bmp", Surface::CYAN);
		Surface blue("images/blue.bmp", Surface::CYAN);
		Surface green("images/green.bmp", Surface::CYAN);
		Surface shimmer("images/shimmer.bmp", Surface::CYAN);

		RectFigure rf1(300, 525, rect, screen, Figure::GRAVITY_DISABLED, false, 0, 0, 0, 1, LEVEL_WIDTH, LEVEL_HEIGHT,
				Figure::BOUNDARY, &red, &shimmer);
		RectFigure rf2(500, 125, rect, screen, Figure::GRAVITY_ENABLED, false, 0, 0, 0, 1, LEVEL_WIDTH, LEVEL_HEIGHT);
		CircFigure cf1(700, 525, dot, screen, Figure::GRAVITY_DISABLED, false, 0, 0, 0, 1, LEVEL_WIDTH, LEVEL_HEIGHT);
		CircFigure cf2(900, 350, dot, screen, Figure::GRAVITY_ENABLED, false, 0, 0, 0, 1, LEVEL_WIDTH, LEVEL_HEIGHT,
				Figure::BOUNDARY, &red, &green, &blue, &shimmer);
		RectFigure coin1(600, 325, coin, screen, Figure::GRAVITY_DISABLED, false, 0, 0, 0, 1, LEVEL_WIDTH, LEVEL_HEIGHT,
				Figure::POINT);

		MouseFigure mouseFig(1, 1, rect, screen, Figure::GRAVITY_DISABLED, true, 0, 0, 0, 1, LEVEL_WIDTH, LEVEL_HEIGHT,
				Figure::BOUNDARY);

		bool quit = false;
		SDL_Event event;
		Timer timer;

		//container for level Figures
		vector<Figure*>* collisions = NULL;

		//load level
		Editor loadLevel("resources/level.txt",Editor::read);

		//for reading level
		collisions = loadLevel.decode();

		mouseFig.setHeightWidth(LEVEL_HEIGHT, LEVEL_WIDTH);
		mouseFig.setContainer(collisions);
		mouseFig.setHeader(edit.headerInfo);

		Music m(edit.headerInfo->bgm_path);

		timer.start();

		if (Mix_PlayingMusic() == 0) if (Mix_PlayMusic(m.getMix_Music(), -1) < 0) throw SoundException();

		Mix_VolumeMusic(32); //0 to 128

		while (!quit) {
			if (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					quit = true;
					exit(0);
				}

				mouseFig.handleInput(event);
			}

			mouseFig.move(*collisions, timer.getTicks());
			timer.start();

			applySurface(0, 0, bgnd, screen, mouseFig.getCameraClip());

			for (int i = 0; i < (int) (*collisions).size(); i++) {
				(*collisions)[i]->show(mouseFig.getCameraClip());
				if (mouseFig.tempObject != NULL) mouseFig.tempObject->show(mouseFig.getCameraClip());
			}

			flip(screen);
		}

		Mix_HaltMusic();

		if (TEST_STRING_INPUT) {
			quit = false;
			bool nameEntered = false;

			StringInput name(TTF_PATH, FONT_SIZE, FONT_COLOR, screen);
			Surface msg(TTF_PATH, FONT_SIZE, FONT_COLOR, "New High Score! Enter Name: ");

			fillScreen(screen, Surface::WHITE);
			applySurface(getHorizontalMiddlePosition(msg, screen), 100, msg, screen);
			flip(screen);

			while (!quit) {
				if (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						quit = true;
						break;
					}

					if (!nameEntered) {
						name.handleInput(event);

						if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
							nameEntered = true;
							msg.setSDL_Surface(TTF_PATH, FONT_SIZE, FONT_COLOR, "Rank 1st: ");
							quit = true;
						}
					}

					fillScreen(screen, Surface::WHITE);
					applySurface(getHorizontalMiddlePosition(msg, screen), 100, msg, screen);
					name.showCentered();

					flip(screen);

					if (nameEntered) SDL_Delay(500);
				}
			}
		}
	}

	cleanUp();

	return 0;
}
