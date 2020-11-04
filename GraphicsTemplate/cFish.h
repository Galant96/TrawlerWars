#pragma once

extern cRenderClass graphics;
using namespace mathLibrary;

class cFish
{
private:
	bool wasCaught = false; // True if the fish was caught
	bool isInNet = false;

public:
	cVector fishPos;
	cVector movementDirection;
	cFish();
	void move();
	void moveCaughtFish(int directionMod, cVector &centralPoint);
	void fishClippingAlgorithm(int xMin, int xMax, int yMin, int yMax);
	bool getWasCaught();
	bool getIsInNet();
	void setIsInNet(bool inNet);
	~cFish();
};

