#include "nMathLibrary.h"

namespace mathLibrary
{
	//////////////////////////////////////////////////////////////
	// Vector class
	//////////////////////////////////////////////////////////////

	// cVecot's constructors
	cVector::cVector(double xX = 0, double yY = 0)
	{
		// Set the vector's position
		x = xX;
		y = yY;
		z = 1;
		vector[0][0] = x;
		vector[1][0] = y;
		vector[2][0] = z;
	}

	cVector::cVector()
	{
		// Set the vector's position
		x = 0;
		y = 0;
		z = 1;
		vector[0][0] = x;
		vector[1][0] = y;
		vector[2][0] = z;
	}

	cVector::~cVector()
	{
	}

	// Setting the values for vector
	void cVector::setVector(double xX, double yY, double zZ = 1)
	{
		x = xX;
		y = yY;
		z = 1;
		vector[0][0] = x;
		vector[1][0] = y;
		vector[2][0] = z;
	}

	// Display vector to console window
	void cVector::displayVector()
	{
		for (int i = 0; i < ROWS_VECTOR; i++)
		{
			for (int j = 0; j < COLUMNS_VECTOR; j++)
			{
				std::cout << vector[i][j] << std::endl;;
			}
		}
		std::cout << std::endl;
	}

	// Return the distance between points
	int cVector::returnDistanceToPoint(cVector &p2)
	{
		return abs(sqrt(((x - p2.x)*(x - p2.x)) + ((y - p2.y)*(y - p2.y))));
	}

	// Matrix * Vertex - return product of matrix and vector multiplication
	void cVector::multiplicationMatrixVector(cMatrix3D & m1)
	{
		cVector productVector = cVector(0, 0);

		// Multiplying vector and matrix
		for (int i{ 0 }; i < ROWS_MATRIX; i++)
		{
			for (int j{ 0 }; j < COLUMNS_VECTOR; j++)
			{
				for (int k{ 0 }; k < ROWS_VECTOR; k++)
				{
					productVector.vector[i][j] += (m1.matrix[i][k] * vector[k][j]);
				}
			}
		}

		setVector(productVector.vector[0][0], productVector.vector[1][0], productVector.vector[2][0]);
		//displayVector();
	}


	// Translate point using coordinates
	void cVector::translatePoint2D(float translateX, float translateY)
	{
		// Initialise the translation matrix
		cMatrix3D translateMatrix = cMatrix3D();
		translateMatrix.createIdentityMatrix();
		//translateMatrix.displayMatrix();

		// Setting the entries of the matrix
		translateMatrix.setMatrixEntry(0, 2, translateX);
		translateMatrix.setMatrixEntry(1, 2, translateY);
		//translateMatrix.displayMatrix();

		// Get the result as a vector matrix 
		multiplicationMatrixVector(translateMatrix);

	}
	
	// Translate point using vector
	void cVector::translatePoint2D(cVector &v)
	{
		// Initialise the translation matrix
		cMatrix3D translateMatrix = cMatrix3D();
		translateMatrix.createIdentityMatrix();
		// scalingMatrix.displayMatrix();

		// Setting the entries of the matrix
		translateMatrix.setMatrixEntry(0, 2, v.x);
		translateMatrix.setMatrixEntry(1, 2, v.y);
		// scalingMatrix.displayMatrix();

		// Get the result as a vector matrix 
		multiplicationMatrixVector(translateMatrix);
	}

	/////////////////////////////////////////////////
	// Non-uniform scaling
	////////////////////////////////////////////////

	// Scale point using coordinates
	void cVector::scalePoint2D(float scaleX, float scaleY)
	{
		// Initialise the scaling matrix
		cMatrix3D scalingMatrix = cMatrix3D();
		scalingMatrix.createIdentityMatrix();
		// scalingMatrix.displayMatrix();

		// Setting the entries of the matrix
		scalingMatrix.setMatrixEntry(0, 0, scaleX);
		scalingMatrix.setMatrixEntry(1, 1, scaleY);
		// scalingMatrix.displayMatrix();

		// Get the result as a vector matrix 
		multiplicationMatrixVector(scalingMatrix);
	}

	// Scale point using vector
	void cVector::scalePoint2D(cVector &v)
	{
		// Initialise the scaling matrix
		cMatrix3D scalingMatrix = cMatrix3D();
		scalingMatrix.createIdentityMatrix();
		// scalingMatrix.displayMatrix();

		// Setting the entries of the matrix
		scalingMatrix.setMatrixEntry(0, 0, v.x);
		scalingMatrix.setMatrixEntry(1, 1, v.y);
		// scalingMatrix.displayMatrix();

		// Get the result as a vector matrix 
		multiplicationMatrixVector(scalingMatrix);
	}

	/////////////////////////////////////////////////
	// Uniform scaling
	////////////////////////////////////////////////
	void cVector::scaleUniformPoint2D(float factor)
	{
		// Initialise the scaling matrix
		cMatrix3D scalingMatrix = cMatrix3D();
		scalingMatrix.createIdentityMatrix();
		// scalingMatrix.displayMatrix();

		// Setting the entries of the matrix
		scalingMatrix.setMatrixEntry(0, 0, factor);
		scalingMatrix.setMatrixEntry(1, 1, factor);
		// scalingMatrix.displayMatrix();

		// Get the result as a vector matrix 
		multiplicationMatrixVector(scalingMatrix);
	}

	// Rotate point about z axis
	void cVector::rotatePoint2DAboutZ(double degrees)
	{
		// Initialise the rotation matrix
		cMatrix3D rotatingMatrix = cMatrix3D();
		rotatingMatrix.createIdentityMatrix();
		// rotatingMatrix.displayMatrix();

		// Setting the entries of the rotation matrix
		// Using precalculated trigonometric functions
		rotatingMatrix.setMatrixEntry(0, 0, getCos(degrees));
		rotatingMatrix.setMatrixEntry(0, 1, getSin(degrees) * -1);
		rotatingMatrix.setMatrixEntry(1, 0, getSin(degrees));
		rotatingMatrix.setMatrixEntry(1, 1, getCos(degrees));
		rotatingMatrix.displayMatrix();

		// Get the result as a vector matrix 
		multiplicationMatrixVector(rotatingMatrix);
	}

	// Rotate point about x axis
	void cVector::rotatePoint2DAboutX(double degrees)
	{
		// Initialise the rotation matrix
		cMatrix3D rotatingMatrix = cMatrix3D();
		rotatingMatrix.createIdentityMatrix();
		// rotatingMatrix.displayMatrix();

		// Setting the entries of the rotation matrix
		// Using precalculated trigonometric functions
		rotatingMatrix.setMatrixEntry(1, 1, getCos(degrees));
		rotatingMatrix.setMatrixEntry(1, 2, getSin(degrees) * -1);
		rotatingMatrix.setMatrixEntry(2, 1, getSin(degrees));
		rotatingMatrix.setMatrixEntry(2, 2, getCos(degrees));
		rotatingMatrix.displayMatrix();

		// Get the result as a vector matrix 
		multiplicationMatrixVector(rotatingMatrix);
	}

	// Rotate point about y axis
	void cVector::rotatePoint2DAboutY(double degrees)
	{
		// Initialise the rotation matrix
		cMatrix3D rotatingMatrix = cMatrix3D();
		rotatingMatrix.createIdentityMatrix();
		// rotatingMatrix.displayMatrix();

		// Setting the entries of the rotation matrix
		// Using precalculated trigonometric functions
		rotatingMatrix.setMatrixEntry(0, 0, getCos(degrees));
		rotatingMatrix.setMatrixEntry(0, 2, getSin(degrees));
		rotatingMatrix.setMatrixEntry(2, 0, getSin(degrees) * -1);
		rotatingMatrix.setMatrixEntry(2, 2, getCos(degrees));
		rotatingMatrix.displayMatrix();

		// Get the result as a vector matrix 
		multiplicationMatrixVector(rotatingMatrix);
	}

	//////////////////////////////////////////////////////////////
	// Matrix class
	//////////////////////////////////////////////////////////////

	// Constructors
	// Using column major format
	cMatrix3D::cMatrix3D(cVector &a, cVector &b, cVector &c)
	{
		matrix[0][0] = a.x; matrix[0][1] = b.x; matrix[0][2] = c.x;
		matrix[1][0] = a.y; matrix[1][1] = b.y; matrix[1][2] = c.y;
		matrix[2][0] = a.z; matrix[2][1] = b.z; matrix[2][2] = c.z;
	}

	cMatrix3D::cMatrix3D()
	{
	}

	cMatrix3D::~cMatrix3D()
	{
	}

	// Setting the specific entry for the given matrix
	void cMatrix3D::setMatrixEntry(size_t row, size_t column, double value)
	{
		matrix[row][column] = value;
	}

	// Identity matrix - return identity matrix
	void cMatrix3D::createIdentityMatrix()
	{
		// Initialise and prepare the identity matrix
		matrix[0][0] = 1; matrix[0][1] = 0; matrix[0][2] = 0;
		matrix[1][0] = 0; matrix[1][1] = 1; matrix[1][2] = 0;
		matrix[2][0] = 0; matrix[2][1] = 0; matrix[2][2] = 1;
	}

	// Matrix * matrix - return product of matrix and matrix multiplication
	void cMatrix3D::multiplicationMatrixMatrix(cMatrix3D & m2)
	{
		// Initialise and prepare the product matrix

		// Multiplying matrices
		for (int i{ 0 }; i < ROWS_MATRIX; i++)
		{
			for (int j{ 0 }; j < COLUMNS_MATRIX; j++)
			{
				for (int k{ 0 }; k < ROWS_MATRIX; k++)
				{
					matrix[i][j] += (matrix[i][k] * m2.matrix[k][j]);
				}
			}
		}
	}

	// Display matrix in the console window
	void cMatrix3D::displayMatrix()
	{
		for (int i = 0; i < ROWS_MATRIX; i++)
		{
			for (int j = 0; j < COLUMNS_MATRIX; j++)
			{
				std::cout << matrix[i][j] << " ";
				if (j == 2)
				{
					std::cout << std::endl;
				}
			}
		}
		std::cout << std::endl;
	}

	//////////////////////////////////////////////////////////////
	// Lookup Tables
	//////////////////////////////////////////////////////////////

	// Initialise lookup tables for storing sin, cos and tan values
	extern double sinTable[LOOKUP_TABLE_SIZE] = { 0 };
	double cosTable[LOOKUP_TABLE_SIZE] = { 0 };
	double tanTable[LOOKUP_TABLE_SIZE] = { 0 };

	// Offset required to find an index is set to value of sin(1);
	double indexOffset = 0.0175;

	// Filling lookup tables - the function is called at the beginning of the program in GraphicsTemplate.cpp file
	void fillLookupTables()
	{
		// Initialise degrees
		double degrees = 0;
		// Calculating the scalling factor
		double scalingFactor = (COMPLETE_ANGLE / LOOKUP_TABLE_SIZE);

		for (int i = 0; i < LOOKUP_TABLE_SIZE; i++)
		{
			// Scalling i
			degrees = (double(i)  * scalingFactor);
			//Converting degrees to radians
			float radians = toRadians(degrees);
			// Storing the results of trigonometric calculations
			sinTable[i] = sin(radians);
			cosTable[i] = cos(radians);
			tanTable[i] = tan(radians);
		}
	}

	// Return sinus of x degrees
	double getSin(double degrees)
	{
		int index = int(((LOOKUP_TABLE_SIZE / COMPLETE_ANGLE) * degrees) - indexOffset);

		return sinTable[index];
	}

	// Return cosinus of x degrees
	double getCos(double degrees)
	{
		int index = int(((LOOKUP_TABLE_SIZE / COMPLETE_ANGLE) * degrees) - indexOffset);

		return cosTable[index];
	}

	// Return tangent of x degrees
	double getTan(double degrees)
	{
		int index = int(((LOOKUP_TABLE_SIZE / COMPLETE_ANGLE) * degrees) - indexOffset);

		return tanTable[index];
	}

	// Draft function using to display the lookup tables
	void displayLookupTable()
	{
		std::cout << " SIN " << std::endl;
		for (int i = 0; i < LOOKUP_TABLE_SIZE; i++)
		{
			std::cout << i << " " << sinTable[i] << " " << std::endl;
		}

		std::cout << " COS " << std::endl;

		for (int i = 0; i < LOOKUP_TABLE_SIZE; i++)
		{
			std::cout << i << " " << cosTable[i] << " " << std::endl;
		}

		std::cout << " TAN " << std::endl;

		for (int i = 0; i < LOOKUP_TABLE_SIZE; i++)
		{
			std::cout << i << " " << tanTable[i] << " " << std::endl;
		}
	}

	//////////////////////////////////////////////////////////////
	// Conversion functions
	//////////////////////////////////////////////////////////////

	// Convert degrees to radians
	double toRadians(double degrees)
	{
		return degrees * ((2*PI) / COMPLETE_ANGLE);
	}

	// Convert radians to degrees
	double toDegrees(double radians)
	{
		return radians * (COMPLETE_ANGLE / (2*PI));
	}

}

