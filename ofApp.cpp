#include "ofApp.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("Final Project");
	ofSetFrameRate(15);
	ofBackground(255, 255, 255);

	windowWidth = ofGetWidth();
	windowHeight = ofGetHeight();

	//가운데에 오게 설정
	ofSetWindowPosition((ofGetScreenWidth() - windowWidth) / 2, (ofGetScreenHeight() - windowHeight) / 2);

	//폰트 설정
	myFont.loadFont("verdana.ttf", 20, true, true);

	hWnd = WindowFromDC(wglGetCurrentDC());

	// esc 키 누르면 전체화면 종료
	ofSetEscapeQuitsApp(false);

	// A new menu object with a pointer to this class
	menu = new ofxWinMenu(this, hWnd);

	menu->CreateMenuFunction(&ofApp::appMenuFunction);

	//window menu 생성
	HMENU hMenu = menu->CreateWindowMenu();
	HMENU hPopup = menu->AddPopupMenu(hMenu, "View");

	menu->AddPopupSeparator(hPopup);
	menu->AddPopupItem(hPopup, "Exit", false, false);

	menu->AddPopupItem(hPopup, "Full screen", false, false); // Not checked and not auto-check

	hPopup = menu->AddPopupMenu(hMenu, "Help");
	menu->AddPopupItem(hPopup, "About", false, false); // No auto check

	menu->SetWindowMenu();

	//block 설정
	srand((unsigned int)time(NULL));
	drawfall = 0;
	bottom = 0;
	nextblock = color_set();

	score = 0;
}

void ofApp::appMenuFunction(string title, bool bChecked) {
	if (title == "Exit") {
		ofExit(); // Quit the application
	}

	if (title == "Full screen") {
		bFullscreen = !bFullscreen; // Not auto-checked and also used in the keyPressed function
		doFullScreen(bFullscreen); // But also take action immediately
	}

	if (title == "About") {
		ofSystemAlertDialog("Final project\n20201560 BukyeongKim");
	}

} // end appMenuFunction
 
void ofApp::doFullScreen(bool bFull)
{
	// Enter full screen
	if (bFull) {
		// Remove the menu but don't destroy it
		menu->RemoveWindowMenu();
		// hide the cursor
		ofHideCursor();
		// Set full screen
		ofSetFullscreen(true);
	}


} // end doFullScreen


//--------------------------------------------------------------
void ofApp::update(){
	if (drawfall) {
		block.ypos+=5;
		Ynum = (block.ypos - 10) / B_size;
		Xnum = (block.xpos - 10) / B_size;
		if (block.ypos >= 640 || field[Ynum +1][Xnum].exist==1) {
			bottom = 1;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofNoFill();
	ofSetColor(0, 0, 0);
	ofSetLineWidth(5);
	ofDrawRectangle(10, 10, B_size*10, B_size*22);


	ofDrawRectangle(370, 70, 200, 200);
	ofDrawRectangle(370, 350, 200, 100);

	ofSetColor(20, 20, 20);
	myFont.drawString("NEXT BLOCK", 380, 50);
	myFont.drawString("SCORE", 420, 330);

	char fpstr[20];
	sprintf(fpstr, "%d", score);
	myFont.drawString(fpstr, 460, 410);

	if(start_flag)
		myFont.drawString("Press SpaceBar \n\n    to Start!!", 50,320);

	ofSetLineWidth(3);
	ofFill();
	if (drawfall) {
		ofSetColor(block.color);
		ofDrawRectangle(block.xpos, block.ypos, B_size, B_size);
	}
	if (bottom) {
		print_score(10);
		addfield();
		if(!reachTop)
			fall();
	}
	ofSetColor(nextblock);
	ofDrawRectangle(455, 155, B_size, B_size);
	draw_field();
	if (reachTop) {
		ofSetColor(0,0,0);
		bottom = 0;
		myFont.drawString("   GAME OVER!\nPress 'r' to retry.", 60, 320);
		drawfall = 0;
	}
	if (retry) {
		srand((unsigned int)time(NULL));
		drawfall = 0;
		bottom = 0;
		nextblock = color_set();

		score = 0;
		reachTop = 0;
		start_flag = 1;
		for (i = 0;i < 22;i++)
			for (j = 0;j < 10;j++)
				field[i][j] = reset;
		retry = 0;
		
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == VK_ESCAPE) {
		// Disable fullscreen set, otherwise quit the application as usual
		if (bFullscreen) {
			bFullscreen = false;
			doFullScreen(false);
		}
		else {
			ofExit();		//NEVER set pause
		}
	}

	if (key == ' ') {
		if (start_flag) {
			fall();
			start_flag = 0;
		}
	}
	if (key == 'q' || key == 'Q') {
		drawfall = 0;
		reachTop = 1;
	}
	if (key == 'r' || key == 'R') {
		retry = 1;
	}
	if (key == OF_KEY_LEFT) {
		if ((block.ypos - 10) / B_size == 0)
			Ynum = (block.ypos - 10) / B_size;
		else
			Ynum = (block.ypos - 10) / B_size + 1;
		Xnum = (block.xpos - 10) / B_size;
		if (block.xpos > 10 && field[Ynum][Xnum-1].exist==0)
			block.xpos -= B_size;
	}
	if (key == OF_KEY_RIGHT) {
		if ((block.ypos - 10) / B_size == 0)
			Ynum = (block.ypos - 10) / B_size;
		else
			Ynum = (block.ypos - 10) / B_size + 1;
		Xnum = (block.xpos - 10) / B_size;
		if(block.xpos < 280 && field[Ynum][Xnum+1].exist==0)
			block.xpos += B_size;
	}
	if (key == OF_KEY_DOWN) {
		if ((block.ypos - 10) / B_size == 0)
			Ynum = (block.ypos - 10) / B_size;
		else
			Ynum = (block.ypos - 10) / B_size + 1;
		Xnum = (block.xpos - 10) / B_size;
		if (block.ypos < 610 && field[Ynum + 1][Xnum].exist == 0)
				block.ypos += B_size;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::fall() {
	drawfall = 1;
	block.ypos = 10;
	block.xpos = 160;
	bottom = 0;	
	block.color = nextblock;
	nextblock = color_set();
}

ofColor ofApp::color_set() {
	ofColor c;
	switch (rand_color = rand() % 7) {
	case 0:	return (c.crimson);
		break;
	case 1: return (c.mediumBlue);
		break;
	case 2: return (c.lawnGreen);
		break;
	case 3: return (c.gold);
		break;
	case 4: return (c.gray);
		break;
	case 5: return (c.purple);
		break;
	case 6: return (c.pink);
		break;
	}
}

void ofApp::addfield() {
	Xnum = (block.xpos - 10) / B_size;
	Ynum = (block.ypos - 10) / B_size;
	field[(block.ypos - 10) / B_size][(block.xpos - 10) / B_size]=block;
	field[(block.ypos - 10) / B_size][(block.xpos - 10) / B_size].exist = 1;
	
	ofColor block_now = field[Ynum][Xnum].color;
	if (block_now == field[Ynum + 1][Xnum].color)
		delete_block(Xnum, Ynum, 1,0);
	if(block_now == field[Ynum][Xnum - 1].color)
		delete_block(Xnum, Ynum, 0, -1);
	if (block_now == field[Ynum][Xnum + 1].color)
		delete_block(Xnum, Ynum, 0, 1);
	if (field[0][Xnum].exist==1) 
		reachTop = 1;
}

void ofApp::delete_block(int xnum, int ynum, int a, int b) {
	field[ynum][xnum] = reset;
	field[ynum + a][xnum + b] = reset;
	i = 1;

	while (field[ynum - i][xnum + b].exist == 1) {
		field[ynum-i+1][xnum + b] = field[ynum-i][xnum + b];
		field[ynum - i + 1][xnum + b].ypos += 30;
		field[ynum - i][xnum + b]=reset;
		i++;
	}
	draw_field();
	print_score(100);
}

void ofApp::print_score(int plus){
	score += plus;
}

void ofApp::draw_field() {
	for (i = 0;i < 22;i++) {
		for (j = 0;j < 10;j++) {
			if (field[i][j].exist == 1) {
				ofSetColor(field[i][j].color);
				ofDrawRectangle(field[i][j].xpos, field[i][j].ypos, B_size, B_size);
			}
		}
	}
}