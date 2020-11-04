===============================================================================================
    "Trawler Wars"
===============================================================================================
This project is a software visualisation tool to be used in a 2D fishing game called "Trawler Wars".
However, the main aim is to develop a simple prototype of the fishing net mechanics.
The prototype is based on the rendering of simple 2D elements by implementing its own created math library and using 2D graphics techniques.
The software renders the simulated environment of the sea with swimming fish.
A fish is represented by a single yellow point in the sea.
The net has the triangle start form, but the shape can be turned into to the smallest convex hull that surrounds the captured fish.
The score is calculated by the amount of fish inside the net.
The final result of the captured fish is displayed to the user when the net is above the sea level.
Namely, this is the event of the end of the game.

The number of fish in the sea is determined by setting:
#define FISH_AMOUNT 25 - will be rendered
This amount might need to be change

===============================================================================================
HOW TO USE THE PROGRAM
===============================================================================================
The application is opened in the console window, and after that, the main menu is displayed.
2. User may input 1 to start the simulation.
   User may input 2 to end the program.
3. If the input was 1, then the simulation is run.
4. Capturing fish begun.
5  The net is moving down until the sea bed is reached.
6. If the sea bed was reached move the net up until it is above the sea level.
7. While the net is above the sea level, display the result of the captured fish to the user. 
7. Ask the user for exiting the application.

===============================================================================================
Math Library namespace
===============================================================================================

nMathLibrary.h
nMathLibrary.cpp

This is the main mathematical library. It contains vector and matrix classes and relevant mathematical functions.
It is used to solve computations in computer graphics.

cVector class:

void setVector(double xX, double yY, double zZ = 1) - Setting the values for vector

void displayVector() - Display vector to console window

int returnDistanceToPoint(cVector &p2) - Return the distance between points

void multiplicationMatrixVector(cMatrix3D & m1) - Matrix * Vertex - return product of matrix and vector multiplication

void translatePoint2D(float translateX, float translateY) - Translate point using coordinates

void translatePoint2D(cVector &v) - Translate point using vector
	
void scalePoint2D(float scaleX, float scaleY) - Scale point using coordinates (Non-uniform scaling)

void scalePoint2D(cVector &v) - Scale point using vector (Non-uniform scaling)

void scaleUniformPoint2D(float factor) -  Scale point using factor (Uniform scaling)

void rotatePoint2DAboutZ(double degrees) - Rotate point about z axis

void rotatePoint2DAboutX(double degrees) - Rotate point about x axis
	
void rotatePoint2DAboutY(double degrees) - Rotate point about y axis


cMatrix class:

void setMatrixEntry(size_t row, size_t column, double value) - Setting the specific entry for the given matrix

void createIdentityMatrix() - Identity matrix - return identity matrix

void multiplicationMatrixMatrix(cMatrix3D & m2) - Matrix * matrix - return product of matrix and matrix multiplication

void displayMatrix() - Display matrix in the console window


Lookup Tables functions:

void fillLookupTables() - Filling lookup tables - the function is called at the beginning of the program in GraphicsTemplate.cpp file

double getSin(double degrees) - Return sinus of x degrees

double getCos(double degrees) - Return cosinus of x degrees
	
double getTan(double degrees) - Return tangent of x degrees

void displayLookupTable() - Draft function using to display the lookup tables


Conversion functions:

double toRadians(double degrees) - Convert degrees to radians

double toDegrees(double radians) - Convert radians to degrees

===============================================================================================
cFish class
===============================================================================================

cFish.cpp
cFish.h

This class is a blueprint for the fish objects. It is responsible for setting the fish in random positions and providing
movement strategies for them. Also, the class stores information about the "catch" status.

void cFish::move() - Fish movement strategy

void moveCaughtFish(int directionMod, cVector &centralPoint) - Caught fish movement strategy

void fishClippingAlgorithm(int xMin, int xMax, int yMin, int yMax) - Determine if a fish has moved beyond the screen extents

bool getWasCaught() - Return the true if fish was caught

bool getIsInNet() - Return the true if fish is in the net

void setIsInNet(bool inNet) - Set fish isInNet status

===============================================================================================
GraphicsTemplate
===============================================================================================

This is the main application source file. It is responsible for performing the simulation of the prototype mechanics.
Some new functions are described below.

void displayMenu() - Display menu

void choseMenuOptions(int userChoice) - Chose menu options

void displayEndGame() - Display the end of the game

void drawLine(cVector &point1, cVector &point2) - Bresenham's line drawing algorithm

void pointClipping(cVector &point) - Point clipping algorithm

void drawPixel(cVector &point) - Check if point is not clipped and draw a pixel

void drawTraingle(cVector &v1, cVector&v2, cVector &v3) - Draft method for drawing simple triangle

void drawSeaLevel() - Draw the level of the sea

void initialiseNetPosition() - Initialise the start position of the net

cVector returnCentralNetPoint() // Return the central point of the net

void moveNet() - Move the net

void trackPointsPosition() - Track the position of the points

int orientation(cVector p1, cVector p2, cVector p3) - Get the point orientation

void findConvexHullPoints(vector <cVector> pointsList) - Find convex hull points

void moveFish() - Conditions for fish movement mechanics

bool chekIfFishInRadius(cVector point) - Check if the fish was caught
