#pragma once
#include "Base_Image.h"
class Ref_Image :
	public Base_Image //inherits the Base_Image class
{
public:
	Ref_Image(); //constructor
	~Ref_Image(); //destructor

	//stores the size of the small matrix (rows x columns)
	int refRows = 49;
	int refCols = 36;
	
	vector<vector<double>> sVector; //a new 2D vector is created to store the small matrix
	
	double* SmallImage; //to store the data read from Ref_Image.txt
	double WallyMean; //to store the calculated mean of the values inside sVector
	
	char small_filename[]; //to store the name of the file to read the data from	
};

