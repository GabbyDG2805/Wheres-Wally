#include <vector>
#pragma once

using namespace std;

class Base_Image
{
public:
	Base_Image(); //Constructor
	~Base_Image(); //Destructor

	double* read_text(char *fileName, int sizeR, int sizeC); //function to read the text file
	double* imageText; //to store the read-in data

	void write_pgm(const char *filename, vector<double> data, int sizeR, int sizeC, int Q); //function to write to a pgm

	vector<double> Vector; //temporary vector used for pushing into other vectors
	void createMatrix(vector<vector<double>> &pVector, double* data, int rows, int cols); //function to put the read-in data in the 1D array to a 2D vector
	void comparisonMatrix(vector<vector<double>> &lVector, int refRows, int refCols, int shiftRow, int shiftCols, vector<vector<double>> &cVector); //function to store a section of the large image matrix (1Vector) into a new Vector (cVector) the same size of the reference image matrix

	double meanCalculation(vector<vector<double>>&pVector, int refRows, int refCols); //function to calculate the mean value inside a vector
	void MinusMean(vector<vector<double>>&pVector, int refRows, int refCols, double mean); //function to subtract the mean from each value inside a vector
	double NCCcalculation(vector<vector<double>>&sVector, vector<vector<double>>&cVector, int refRows, int refCols); //function to calculate the final NCC value
};

