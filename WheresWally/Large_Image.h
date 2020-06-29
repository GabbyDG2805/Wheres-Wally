#pragma once
#include "Base_Image.h"

using namespace std; 

class Large_Image :
	public Base_Image //inherits the Base_Image class
{
public:
	Large_Image(); //constructor
	~Large_Image(); //destructor

	//stores the size of the large image matrix (rows x columns)
	int largeRows = 768;
	int largeCols = 1024;

	vector<vector<double>> lVector; //creates a new 2D vector for the large image matrix to be stored in
	vector<double> forPGM; //creates a 1D vector converted from the 2D a vector above so it can be written to a pgm
	void twoDconversion(vector<double> &forPGM, vector<vector<double>>&lVector, int largeRows, int largeCols); //function to do the conversion mentioned above

	double* LargeImage; //stores the data read from large_image.txt
	
	char large_filename[];	//to store the name of the large text file to read from
		
};

