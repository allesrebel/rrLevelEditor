/*
 * 	Editor v.5
 *
 * 	Encoding and decoding module
 * 	Reads a pretty simple formated txt
 * 	and creates a Vector<Figure*>*
 * 	with all memory it needs allocated
 *
 *  Created on: Sep 7, 2013
 *      Author: Alles Rebel
 */


#ifndef EDITOR_H_
#define EDITOR_H_

#include <string>
#include <vector>
#include "../Figure.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

struct Header{
	int screen_w;
	int screen_h;
	int bg_w;
	int bg_h;
	string bg_path;
	string bgm_path;
};

class Editor {
public:
	enum state{
		read, write
	};

public:
	Editor();
	Editor(string, state);
	~Editor();

	void setFile(string,state);

	void writeHeader(Header);
	Header* readHeader();

	void encode(vector<Figure*>*,Header lvlInfo);
	vector<Figure*>* decode();

	Header* headerInfo;
private:
	void encodeFigure(Figure* fig, int lvlWidth, int lvlHeight);
	Figure* decodeFigure();

	FILE* file;
	void checkFile();
};

#endif /* EDITOR_H_ */
