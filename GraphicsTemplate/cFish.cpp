#include "stdafx.h"
#include "cFish.h"


cFish::cFish()
{
	static int seaLevelOffset = 105;
	// Randomise the start position of the fish
	fishPos.x = rand() % SCREEN_WIDTH + 1;
	fishPos.y = rand() % (SCREEN_HEIGHT - seaLevelOffset) + 1;
	
	// Avoid non-movement when dirX and dirY are equal to 0
	do
	{
		movementDirection.x = rand() % 3;
		movementDirection.y = 0;

	} while (movementDirection.x == 0 && movementDirection.y == 0);

	// Because rand does not return 0 the program uses 2 as trigger mark to set  direction to -1
	if (movementDirection.x == 2)
	{
		movementDirection.x = -1;
	}

	// Set the position and direction vertices
	fishPos = cVector(fishPos.x, fishPos.y);
	movementDirection = cVector(movementDirection.x, movementDirection.y);
}

// Fish movement strategy
void cFish::move()
{
	// Check if the fish was caught
	if (wasCaught == false)
	{
		// Move by translation
		fishPos.translatePoint2D(movementDirection.x, movementDirection.y);

		// Change direction of the movement if a fish has moved beyond the screen
		fishClippingAlgorithm((SCREEN_WIDTH - SCREEN_WIDTH), SCREEN_WIDTH, (SCREEN_HEIGHT - SCREEN_HEIGHT), SCREEN_HEIGHT);
	}
	
}

// Caught fish movement strategy
void cFish::moveCaughtFish(int directionMod, cVector &centralPoint)
{
	// The Fish has been caught in the net
	wasCaught = true;
	if (wasCaught == true)
	{
		movementDirection.y = directionMod;

		// Change direction of the movement if a fish has moved beyond the net
		fishClippingAlgorithm(centralPoint.x - 50, centralPoint.x + 50, centralPoint.y - 60, centralPoint.y + 60);

		if (directionMod >= 1)
		{
			// Move by translation
			fishPos.translatePoint2D(movementDirection.x, 1);
		}
		else
		{
			// Move by translation
			fishPos.translatePoint2D(movementDirection.x, movementDirection.y);
		}
		
	}
	else
	{

		return;
	}

}

// Determine if a fish has moved beyond the screen extents
void cFish::fishClippingAlgorithm(int xMin, int xMax, int yMin, int yMax)
{
	if ((fishPos.x > xMin && fishPos.x < xMax) && (fishPos.y > yMin && fishPos.y < yMax))
	{
		return;
	}
	else
	{
		// Change direction
		movementDirection.scaleUniformPoint2D(-1.0);
	}
}

// Return the true if fish was caught
bool cFish::getWasCaught()
{
	return wasCaught;
}

// Return the true if fish is in the net
bool cFish::getIsInNet()
{
	return isInNet;
}

// Set fish isInNet status
void cFish::setIsInNet(bool inNet)
{
	isInNet = inNet;
}


cFish::~cFish()
{
}
