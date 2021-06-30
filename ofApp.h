#pragma once

#include "ofMain.h"
#include "ofxWinMenu.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	int windowWidth;
	int windowHeight;

	ofTrueTypeFont myFont;
	HWND hWnd; // Application window
	HWND hWndForeground; // current foreground window

	// Menu
	ofxWinMenu* menu; // Menu object
	void appMenuFunction(string title, bool bChecked); // Menu return function

	//Fullscreen
	bool bFullscreen;
	void doFullScreen(bool bFull);

	//테트리스 블록
	int B_size = 30;
	int rand_color;
	ofColor nextblock;

	void fall();
	int drawfall;
	int bottom;
	int i, j;

	int start_flag = 1;

	void delete_block(int xnum, int ynum, int a, int b);

	void print_score(int plus);
	int score;

	typedef struct _blockstruct {
		int exist = 0;
		int ypos;
		int xpos;
		ofColor color;
	}blockstruct;
	blockstruct block;

	void addfield();
	blockstruct field[22][10];
	blockstruct reset;
	int Xnum;
	int Ynum;
	int reachTop;

	void draw_field();
	ofColor color_set();
	int retry = 0;
};