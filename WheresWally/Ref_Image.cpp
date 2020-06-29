#include <iostream>
#include "Ref_Image.h"

using namespace std;

Ref_Image::Ref_Image() //constructor
{
	Base_Image B; //creates instance of the Base_Image class so it's functions can be called

	char small_filename[] = "Ref_Image.txt"; //specifies the name of the txt file to read from
	
	SmallImage = B.read_text(small_filename, refRows, refCols); //calls the function to read the data from the text file and store it in a new double*

	B.createMatrix(sVector, SmallImage, refRows, refCols); //calls the function to convert the data into a 2D vector (matrix of size 49x36) which will be created called sVector

	//The following two calculations can be called here since they will remain constant
	WallyMean = B.meanCalculation(sVector, refRows, refCols); //calls the function to calculate the mean value inside the Wally matrix (sVector)
	B.MinusMean(sVector, refRows, refCols, WallyMean); //calls the function to subtract the mean from each value inside the small matrix
}

Ref_Image::~Ref_Image()
{
	//destructor
}
