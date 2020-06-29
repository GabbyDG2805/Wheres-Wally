#include <iostream>
#include "Base_Image.h"
#include "Large_Image.h"

using namespace std;

Large_Image::Large_Image() //constructor
{
	Base_Image B; //creates an instance of the Base_Image class so it's functions can be used

	char large_filename[] = "Large_Image.txt"; //specifies the name of the file to read the data from
	
	LargeImage = B.read_text(large_filename, largeRows, largeCols); //calls the function to read the data from the text file and store it in a new double*

	B.createMatrix(lVector, LargeImage, largeRows, largeCols); //calls the function to convert the data into a 2D vector (matrix of size 768x1024) which will be created called lVector

	//unlike in the Ref_Image class, the calculations for the mean and minusMean are not used here because they will be constantly changing depending on the section stored in the vector used for comparison 
}

//This is a function to convert the large image 2D vector to a 1D vector soley for the purpose of writing to the pgm
void Large_Image::twoDconversion(vector<double> &forPGM, vector<vector<double>>&lVector, int largeRows, int largeCols)
{
	for (int i = 0; i < largeRows; i++)
	{
		for (int j = 0; j < largeCols; j++)
		{			
			forPGM.push_back(lVector[i][j]);
		}
	}
}
Large_Image::~Large_Image()
{
	//destructor
}
