#include <iostream>
#include <fstream> //this is needed in order to read from and write to files
#include <vector> //this is needed to use STL Vector containers
#include "math.h" //this is needed to calculate a square root
#include "Base_Image.h"

using namespace std;

//This class is inherited by the Large_Image and Ref_Image classes so any functions that can be used for either image are created here so the code can be re-used rather than written twice for each image

//This is the provided code to read data from the text files into an array
double* Base_Image::read_text(char *fileName, int sizeR, int sizeC)
{
	double* data = new double[sizeR*sizeC];
	int i = 0;
	ifstream myfile(fileName);
	if (myfile.is_open())
	{

		while (myfile.good())
		{
			if (i > sizeR*sizeC - 1) break;
			myfile >> *(data + i);
			//cout << *(data+i) << ' '; 
			i++;
		}
		cout << "File read successfully"<< endl;
		myfile.close();
	}
	else cout << "Unable to open file";
	//cout << i;
	
	imageText = data;
	return data;
}
//This is the provided code to write data to a pgm. 
//However, the 'double* data has been changed to vector<double> data because the large image matrix has been converted into a 1D vector so it can be written from
void Base_Image::write_pgm(const char *filename, vector<double> data, int sizeR, int sizeC, int Q)
{

	int i, j;
	unsigned char *image;
	ofstream myfile;

	image = (unsigned char *) new unsigned char[sizeR*sizeC];

	for (i = 0; i < sizeR*sizeC; i++)
		image[i] = (unsigned char)data[i];

	myfile.open(filename, ios::out | ios::binary | ios::trunc);

	if (!myfile) {
		cout << "Can't open file: " << filename << endl;
		exit(1);
	}

	myfile << "P5" << endl;
	myfile << sizeC << " " << sizeR << endl;
	myfile << Q << endl;

	myfile.write(reinterpret_cast<char *>(image), (sizeR*sizeC) * sizeof(unsigned char));

	if (myfile.fail()) {
		cout << "Can't write image " << filename << endl;
		exit(0);
	}

	myfile.close();

	delete[] image;

}

//The following function puts the data from the 1D array into a 2D vector
void Base_Image::createMatrix(vector<vector<double>> &pVector, double* imageText, int rows, int cols)
{
	int counter = 0;
	for (int i = 0; i < rows; i++)
	{
		Vector.clear();
		for (int j = 0; j < cols; j++)
		{
			//cout << imageText[counter] << ", ";
			Vector.push_back(imageText[counter++]);
		}
		//cout << endl;
		pVector.push_back(Vector);		
	}
	cout << "Data put into a Matrix" << endl;
}

//This function takes a section of the large image matrix (lVector) and puts it into a new vector (cVector) which is a matrix the same size of the small image matrix (49x36)
void Base_Image::comparisonMatrix(vector<vector<double>> &lVector, int refRows, int refCols, int shiftRow, int shiftCols, vector<vector<double>> &cVector)
{
	for (int i = shiftRow; i < refRows + shiftRow; i++)
	{
		Vector.clear();
		for (int j = shiftCols; j < refCols + shiftCols; j++)
		{			
			Vector.push_back(lVector[i][j]);
		}		
		cVector.push_back(Vector);
	}
}

//The following functions are all steps to carry out a NCC calculation
//The first step is to calculate the mean value inside a matrix/vector
double Base_Image::meanCalculation(vector<vector<double>>&pVector, int refRows, int refCols)
{
	int counter = 0;
	double mean = 0;

	for (int i = 0; i < refRows; i++)
	{
		for (int j = 0; j < refCols; j++)
		{
			mean += pVector[i][j]; //This adds all of the values in the vector together
			counter++;
		}
	}
	mean /= counter; //This the divides the sum by the total number of steps taken which is the number of values in the vector
	return mean;
}
//The next step is to then subtract the mean from each value inside the vector
void Base_Image::MinusMean(vector<vector<double>>&pVector, int refRows, int refCols, double mean)
{
	for (int i = 0; i < refRows; i++)
	{
		for (int j = 0; j < refCols; j++)
		{
			pVector[i][j] = pVector[i][j] - mean;
		}
	}
}
//The final part calculates a number of things in order to calculate a final NCC result
double Base_Image::NCCcalculation(vector<vector<double>>&sVector, vector<vector<double>>&cVector, int refRows, int refCols)
{
	double result = 0;
	long double WallyAndScene = 0;
	long double WallySquared = 0;
	long double SceneSquared = 0;

	for (int i = 0; i < refRows; i++)
	{
		for (int j = 0; j < refCols; j++)
		{
			WallyAndScene += cVector[i][j] * sVector[i][j]; //This multiplies the current position of the section of the scene with the current position of the Wally matrix
			WallySquared += sVector[i][j] * sVector[i][j]; //This squares the current position of the Wally matrix
			SceneSquared += cVector[i][j] * cVector[i][j]; //This squares the current position of the section of the scene matrix
		}
	}
	result = WallyAndScene / sqrt(WallySquared * SceneSquared); //The final result is calculated by dividing the first calculation by the square root of the product of the second and third calculation

	//cout << result << endl; //this prints all of the NCC results on the console
	return result;
}

Base_Image::Base_Image()
{
	//Constructor
}


Base_Image::~Base_Image()
{
	//Destructor
}
