#pragma once
#include<iostream>
#define PI 3.14159265359
#define ROWS_MATRIX 3
#define COLUMNS_MATRIX 3
#define ROWS_VECTOR 3
#define COLUMNS_VECTOR 1

#define LOOKUP_TABLE_SIZE 1024
#define COMPLETE_ANGLE 360.0


namespace mathLibrary
{

	// Forward declaration of classes
	class cVector;
	class cMatrix3D;

	class cVector
	{
	private:

	public:
		double x;
		double y;
		double z;
		double vector[ROWS_VECTOR][COLUMNS_VECTOR] = { x, y, z };
		cVector(double x, double y);
		cVector::cVector();
		~cVector();
		void setVector(double x, double y, double z);
		void displayVector();

		int returnDistanceToPoint(cVector & p1);

		void multiplicationMatrixVector(cMatrix3D & m1);

		void translatePoint2D(float translateX, float translateY);

		void translatePoint2D(cVector & v);

		void scalePoint2D(float scaleX, float scaleY);

		void scalePoint2D(cVector & v);

		void scaleUniformPoint2D(float factor);

		void rotatePoint2DAboutZ(double degrees);

		void rotatePoint2DAboutX(double degrees);

		void rotatePoint2DAboutY(double degrees);


	};

	class cMatrix3D
	{
	private:
	public:
		float matrix[ROWS_MATRIX][COLUMNS_MATRIX] = { 0 };

		cMatrix3D(cVector &a, cVector &b, cVector &c);
		cMatrix3D();
		~cMatrix3D();

		void setMatrixEntry(size_t row, size_t column, double value);

		void displayMatrix();
		void createIdentityMatrix();
		void multiplicationMatrixMatrix(cMatrix3D & m2);
	};



	// Convert degrees to radians
	double toRadians(double degrees);

	// Convert radians to degrees
	double toDegrees(double radians);

	void displayLookupTable();

	void fillLookupTables();

	double getSin(double degrees);

	double getCos(double degrees);

	double getTan(double degrees);
 
}


