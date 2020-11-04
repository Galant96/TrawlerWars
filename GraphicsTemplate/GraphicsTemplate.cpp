// GraphicsTemplate.cpp
// 
//////////////////////////////////////////////////////////////////////////////////////////
// includes 
//////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "cFish.h"
#include <chrono>
#include <thread>

//////////////////////////////////////////////////////////////////////////////////////////
// definitions 
//////////////////////////////////////////////////////////////////////////////////////////

#define SEA_LEVEL 400
#define TRIANGLE_VERTICES 3
#define FISH_AMOUNT 25 // This amount might need to be change
#define NET_RADIUS 50

//////////////////////////////////////////////////////////////////////////////////////////
// externals 
//////////////////////////////////////////////////////////////////////////////////////////
extern cRenderClass graphics;
using namespace mathLibrary; // Include created math library
using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

// Display menu
void displayMenu();
void choseMenuOptions(int userChoice);

// Display the end of the game
void displayEndGame();

// Bresenham's line drawing algorithm
void drawLine(cVector &point1, cVector &point2);

// Point clipping algorithm
void pointClipping(cVector &point);

// Check if point is not clipped and draw a pixel
void drawPixel(cVector &point);

// Draft method for drawing simple triangle
void drawTraingle(cVector &v1, cVector&v2, cVector &v3);

// Draw the level of the sea
void drawSeaLevel();

// Initialise the start position of the net
void initialiseNetPosition();
// Return the central point of the net
cVector returnCentralNetPoint();
// Move the net
void moveNet();

// Track the position of the points
void trackPointsPosition();

// Get the point orientation
int orientation(cVector p1, cVector p2, cVector p3);

// Find convex hull points
void findConvexHullPoints(vector <cVector> pointsList);

// Conditions for fish movement mechanics
void moveFish();

// Check if the fish was caught
bool chekIfFishInRadius(cVector point);

cFish *fish = NULL; // Stores fish objects
cVector *triangleNet = NULL; // Stores the starting net
bool wasSeaBedReached = false; // True if the sea bed was reached

vector <cVector> pointsList; // Keeps the list of all points 

vector <cVector> convexHullPoints; // Keeps the list of convex hull points

const milliseconds frameRate((int)((1.0f / 60.0f) * 600.0f)); // Get constant frame rate

int score = 0;
bool isGameEnd = false;


//////////////////////////////////////////////////////////////////////////////////////////
// _tmain() - program entry point
//////////////////////////////////////////////////////////////////////////////////////////
int _tmain(int argc, _TCHAR* argv[])
{	
	// init glut stuff..
	graphics.create(argc, argv);


	// good place for one-off initialisations and objects creation..
	displayMenu();

	// Initialise random seed
	srand(time(NULL));

	// Initialise the fish objects
	fish = new cFish[FISH_AMOUNT];
	// Initialise the net object
	triangleNet = new cVector[TRIANGLE_VERTICES];
	initialiseNetPosition();

	// Fill the lookup tables
	fillLookupTables();

	// enter game loop..
	graphics.loop();	
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
// update() - update function
//////////////////////////////////////////////////////////////////////////////////////////
void update()
{
	// Draw the level of the sea
	drawSeaLevel();
	// add any update code here...

	moveFish();
	trackPointsPosition();
	moveNet();

	// Wait before render and the next update
	sleep_for(nanoseconds(frameRate));

	// always re-render the scene..
	renderScene();
}

//////////////////////////////////////////////////////////////////////////////////////////
// renderScene() - render the scene
//////////////////////////////////////////////////////////////////////////////////////////
void renderScene()
{
	// set a colour
	// graphics.setColour(0, 0, 0);
	// set pixel size..
	graphics.setPointSize(4);
	
	// draw to an off screen buffer

	// render the scene
	graphics.render();
}

void displayMenu()
{
	// Store user choice
	int userChoice = 0;
	isGameEnd = false;

	// Display the menu of the program in the console windows
	do
	{
		cout << "\n" << "************************************************" << "\n" << "************************************************" << endl;
		cout << "Welcome in the Trawler Wars menu!" << endl;
		cout << "The game is the prototype of the product.It shows the mechanics which can be used in the final version." << endl;
		cout << "After entering the game, the net is starting slowly falling to the sea bed the hunt is begun!"<< endl;
		cout << "The fish can be trapped in the net!"<< endl;
		cout <<"However, some of them are combative and might accidentally breakaway... "<< endl;
		cout << "Ah... fisherman's babble... The more fish you are lucky to catch, the better!"<< endl;

		cout << "MENU:" << endl;
		cout << "1. Enter the game." << endl;
		cout << "2. Exit the application." << endl;

		// Get user input
		cin >> userChoice;		// Proceed with a choosen operation
		choseMenuOptions(userChoice);

	} while (userChoice != 1);

}

// Proceed the menu options
void choseMenuOptions(int userChoice)
{

	switch (userChoice)
	{
	case 1:
	{
		cout << "Good luck!!!" << endl;
		break;
	}
	// Exit the application
	case 2:
		cout << endl;
		cout << "Exitting the application...";
		exit(0);
		break;
	default:
		cout << "Error: Invalid input!" << endl;
		exit(0);
	}
}

// Bresenham's line drawing algorithm
void drawLine(cVector &point1, cVector &point2)
{
	double x1 = point1.x;
	double x2 = point2.x;
	double y1 = point1.y;
	double y2 = point2.y;

	// Determine steps for X and Y axis
	int stepX, stepY = 0;
	if (x1 <= x2)
	{
		stepX = 1;
	}
	else
	{
		stepX = -1;
	}

	if (y1 <= y2)
	{
		stepY = 1;
	}
	else
	{
		stepY = -1;
	}

	// Calculate dx and dy
	int dx, dy = 0;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);

	if (dx < 0)
	{
		dx = dx * -1;
	}

	if (dy < 0)
	{
		dy = dy * -1;
	}

	// Draw start pixel
	graphics.drawPixel(x1, y1);

	// Initialise error variable
	int e = 0;

	// Pick a Bresenham's algorithm version

	if (dx >= dy)
	{
		// Basic version

		e = dx / 2;   // Calculating error

		for (int i = 0; i < dx; i++)
		{
			x1 += stepX;
			// Updating error value
			e -= dy;    
			if (e < 0)
			{
				y1 += stepY;
				e += dx;
			}

			// Draw a pixel
			graphics.drawPixel(x1, y1); // Using drawPixel function with clipping method is to slow for drawing a line

		}
	}
	else
	{
		// Version with changed coordinates

		e = dy / 2;   // Calculating error

		for (int i = 0; i < dy; i++)
		{
			y1 += stepY;
			e -= dx;
			if (e < 0)
			{
				x1 += stepX;
				e += dy;
			}

			graphics.drawPixel(x1, y1);
		}
	}

}

// Point clipping algorithm
void pointClipping(cVector &point)
{
	int xMin = SCREEN_WIDTH - SCREEN_WIDTH;
	int xMax = SCREEN_WIDTH;
	int yMin = SCREEN_HEIGHT - SCREEN_HEIGHT;
	int yMax = SCREEN_HEIGHT;

	if ((point.x >= xMin && point.x <= xMax) && (point.y >= yMin && point.y <= yMax))
	{
		// Render a point
		//std::cout << "The point is rendered!" << endl;
		graphics.drawPixel(point.x, point.y);
	}
	else
	{
		//std::cout << "The point is clipped!" << endl;
	}
}

// Utility function to draw a point
void drawPixel(cVector &point)
{
	pointClipping(point);
}

// Draft for drawng a triangle
void drawTraingle(cVector &v1, cVector&v2, cVector &v3)
{
	drawLine(v1, v2);
	drawLine(v2, v3);
	drawLine(v3, v1);
}

// Net's position initialisation
void initialiseNetPosition()
{
	triangleNet[0] = cVector(200, 400); // Left vertex of the net
	triangleNet[1] = cVector(300, 400); // Right vertex of the net
	triangleNet[2] = cVector(250, 500); // Top vertex of the net
}

// Move net mechanics
void moveNet()
{
	// Strat falling the net to the sea bed
	if (triangleNet[1].y > 0 && wasSeaBedReached == false)
	{
		for (size_t i = 0; i < TRIANGLE_VERTICES; i++)
		{
			triangleNet[i].translatePoint2D(0, -1);
		}
	}
	else 	// If sea bed is reached start to pull the net up
	{
		wasSeaBedReached = true;

		// The condition to stop pulling and finalise the fishing result
		if (triangleNet[2].y >= 500 && wasSeaBedReached == true)
		{
			for (size_t i = 0; i < 3; i++)
			{
				triangleNet[i].translatePoint2D(0, 0);
			}

			// Display the final score and go to menu
			displayEndGame();
		}
		else // Continue pulling the net
		{
			for (size_t i = 0; i < 3; i++)
			{
				triangleNet[i].translatePoint2D(0, 1);
			}
		}
	}
}

// Moving fish conditions
void moveFish()
{
	for (size_t i = 0; i < FISH_AMOUNT; i++)
	{
		// Check if fish is outside the sea
		if (fish[i].fishPos.y > SEA_LEVEL)
		{
			// SCORE
			graphics.setColour(255, 0, 0);
			drawPixel(fish[i].fishPos);
		}
		// Keep fish in the net if it is inside
		else if(chekIfFishInRadius(fish[i].fishPos))
		{
			// Find the central point of the net for referencing the position of a fish in the net			
			cVector centralPoint = returnCentralNetPoint();

			// Find out the y-direction for the fish in the net according to the y position of the net
			int directionMod = 0;
			if (wasSeaBedReached == true)
			{
				directionMod = 1;
			}
			else
			{
				directionMod = -1;
			}

			// Implement movement in the net
			fish[i].moveCaughtFish(directionMod, centralPoint);

			// Calculating the current score
			if (fish[i].getIsInNet() == false)
			{
				fish[i].setIsInNet(true);
				score += 1;
				cout << "Score : " << score << endl;
			}

			// Set the colour of a fish in the net to red
			graphics.setColour(255, 0, 0);
			drawPixel(fish[i].fishPos);
			
		}
		// Move fish in the sea
		else
		{
			// Updating the current score if fish run away
			if (fish[i].getIsInNet() == true)
			{
				fish[i].setIsInNet(false);
				score -= 1;
				cout << "Score : " << score << endl;
			}

			// Set the colour of a fish in the sea to yellow
			graphics.setColour(255, 255, 0);

			// Implement movement in the sea
			fish[i].move();
			drawPixel(fish[i].fishPos);

		}

	}
}

// Track the position of the points to collect by the net
void trackPointsPosition()
{
	// Clear the array list of the points each time when they are recalculated
	pointsList.clear();

	for (size_t i = 0; i < TRIANGLE_VERTICES; i++)
	{
		pointsList.push_back(triangleNet[i]);
	}

	for (size_t i = 0; i < FISH_AMOUNT; i++)
	{
		if (chekIfFishInRadius(fish[i].fishPos))
		{
			pointsList.push_back(fish[i].fishPos);
		}
	}

	// Find convex hull of the list of points
	findConvexHullPoints(pointsList);
}

// Find convex hull of the list of points
void findConvexHullPoints(vector <cVector> points)
{
	// Clear the array list of the convex hull points each time when they are recalculated
	convexHullPoints.clear();

	int pointsNumber = points.size();

	// There must be at least 3 points
	if (pointsNumber < 3)
	{
		return;
	}

	// Find the leftmost point index
	int l = 1;
	for (size_t i = 0; i < pointsNumber; i++)
	{
		if (((points[i].y < points[l].y) || (points[i].y < points[l].y)) && (points[i].x < points[l].x))
		{
			l = i;
		}
	}

	// Start from leftmost point and keep moving counterclockwise
	int p = l, q;

	do
	{
		// Add current point to convex hull points list 
		convexHullPoints.push_back(points[p]);

		// Initialise the variable for keeping track the index of last visited most couterclockwise point 
		q = (p + 1) % pointsNumber;

		// Check if any other point is more counterclockwise
		for (size_t i = 0; i < pointsNumber; i++)
		{
			// If any other point is more counterclockwise than current q, update q
			if (orientation(points[p], points[i], points[q]) == 2)
			{
				q = i;
			}
		}

		// Now q is the most counterclockwise in comparision to p
		// Set p as q for next iteration
		// point[q] is added to convexHullPoints
		p = q;

	} while (p != l); // While p is not equal to the first point

	//cout << "_______________________________________________________________________\n";

	// Set the colour of the net to white
	graphics.setColour(250, 250, 250);

	// Draw lines between points
	for (size_t i = 0; i < convexHullPoints.size(); i++)
	{
		if (i == convexHullPoints.size() - 1)
		{
			drawLine(convexHullPoints[i], convexHullPoints[0]);
		}
		else
		{
			drawLine(convexHullPoints[i], convexHullPoints[i+1]);
		}

		//cout << "(" << convexHullPoints[i].x << ", " << convexHullPoints[i].y << ")\n";
	}
	//cout << "_______________________________________________________________________\n";
 
}


// To find orientation of ordered triplet (p, q, r), the function returns following values:
// 0 - p1, p2 and p3 are colinear
// 1 - Clockwise
// 2 - Counterclockwise
int orientation(cVector p1, cVector p2, cVector p3)
{
	int val = (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y);

	if (val == 0)
	{
		return 0;  // Colinear
	}

	return (val > 0) ? 1 : 2; // Clock or counterclock wise
}

// Return true if the fish is in the radius of the net
bool chekIfFishInRadius(cVector point)
{
	cVector centralPoint = returnCentralNetPoint();
	int radius = NET_RADIUS;

	//cout <<"d "<< point.returnDistanceToPoint(centralPoint)<<endl;
	//cout << "p " << centralPoint.x << "," << centralPoint.y << endl;

	if (int(point.returnDistanceToPoint(centralPoint)) <= radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Calculate and return the central point of the net
cVector returnCentralNetPoint()
{
	cVector centralPoint = cVector(int((triangleNet[0].x + triangleNet[1].x + triangleNet[2].x)/TRIANGLE_VERTICES),
		int((triangleNet[0].y + triangleNet[1].y + triangleNet[2].y) / TRIANGLE_VERTICES));
	return centralPoint;
}

// Draw the level of the sea
void drawSeaLevel()
{
	// Set the colour of the sea level to blue
	graphics.setColour(0, 0, 255);
	drawLine(cVector((SCREEN_WIDTH-SCREEN_WIDTH), SEA_LEVEL), cVector(SCREEN_WIDTH, SEA_LEVEL));
}

// Display the result of the game
void displayEndGame()
{
	if(isGameEnd == false)
	{
		isGameEnd = true;

		cout << "===========================================================" << endl;
		cout << "========================= GAME END ========================" << endl;
		cout << "===========================================================" << endl;
		cout << "======================== CAUGHT FISH ========================" << endl;
		cout << "=========================== " << score << " ==========================" << endl;
		cout << "===========================================================" << endl;

		// Free the memory
		delete[] fish;
		delete[] triangleNet;

		// To exit the application, enter 2
		int decision = 0;
		do
		{
			cout << "To exit the application, enter 2 >>>>> ";
			cin >> decision;
		} while (decision != 2);

		choseMenuOptions(decision);
	}

}


