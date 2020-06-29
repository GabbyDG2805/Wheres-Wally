//CMP2090M - Object Oriented Programming - Assessment Item 1
//By Gabriella Di Gregorio, DIG15624188

#include <iostream> //this is needed for basic input/output such as cout and cin
#include <algorithm> //this is needed in order to sort a vector
#include "Base_Image.h"
#include "Large_Image.h"
#include "Ref_Image.h"

using namespace std;

int main()
{
	cout << "Lets find Wally!\n" << endl;

	//Creates an object of the Large_Image class to read the Large_Image.txt then put the data into a matrix
	cout << "Reading the Large Image..." << endl;
	Large_Image L;	

	//Creates an object of the Ref_Image class to read the Ref_Image.txt then put the data into a matrix
	cout << "\nReading the Small Image..." << endl;
	Ref_Image R;
	
	cout << "\nComparing Matrices..." << endl;
		
	Base_Image B; //Creates an object of the Base_Image class outside the loop
	double mean; //a double to store the mean that gets calculated inside the loop
	vector<vector<double>> results; //a 2D Vector to store the results of the NCC calculation which includes the position of both the rows and columns and the NCC value
	vector<double> resultPush; //a 1D Vector simply used to push the data into the 2D vector above

	//This is a nested for loop to scan through the large image. To make this search more efficient, it jumps across 18 rows and 24 columns at a time rather than moving one at a time.
	for (int shiftRow = 0; shiftRow <= L.largeRows - R.refRows; shiftRow += R.refRows/2)
	{
		for (int shiftCols = 0; shiftCols <= L.largeCols - R.refCols; shiftCols += R.refCols/2) 
		{			
			vector<vector<double>> cVector;	//This is a 2D vector to store a section of the large image matrix the same size of the small image matrix				

			//The following lines are all about calling functions from the Base_Image class in order to do the NCC calculation...
			B.comparisonMatrix(L.lVector, R.refRows, R.refCols, shiftRow, shiftCols, cVector); //This stores a section of the large image matrix of size 49x36 in cVector to use to compare to the small image matrix (sVector)
			mean = B.meanCalculation(cVector, R.refRows, R.refCols); //This calculates the mean value of the current section of the scene inside cVector
			B.MinusMean(cVector, R.refRows, R.refCols, mean); //This subtracts the mean from each value currently in cVector
			double result = B.NCCcalculation(R.sVector, cVector, R.refRows, R.refCols); //This calls the final step of the NCC calculation which produces a similarity result
			//The calculations above are explained in more detail in their relevant functions inside the Base_Image Class.

			/*This if statement saves time by only storing the NCC result if it is greater than 0. 
			Since the results range between 1 (identical to Wally) and -1 (opposite of Wally), anything scoring lower than 0 is nothing like Wally so does not need to be kept.
			If the NCC result is greater than 0, the position (row and column) and the similarity (NCC) result is stored inside the results Vector using the resultPush Vector.*/
			if (result > 0)
			{
				resultPush.push_back(shiftRow);
				resultPush.push_back(shiftCols);
				resultPush.push_back(result);
				results.push_back(resultPush);
				resultPush.clear();
			}
		}
	}
	//By including the STL Alogrithm Library, the sort function can be used to sort the results vector from largest to smallest
	sort(results.begin(), results.end(), [](const vector<double> &largerValue, const vector<double> &smallerValue)
	{
		return largerValue[2] > smallerValue[2];
	});

	cout << "Best Matches found!" << endl;
	int requestedResults;
	cout << "\nHow many results would you like to see?: "; 
	cin >> requestedResults; //The user can choose how many N-best results they would like to see by entering a number in the console
	cout << "\n OK! These are the " << requestedResults << " best results found..." << endl;
	
	/*This displays a ranked list of N-best values depending on how many results the user has asked to see.
	The best results are at the start of the results vector because the highest scores are most similar to Wally*/
	for (int i = 0; i < requestedResults; i++)
	{
		cout << i + 1 << ". " << "Row: " << results[i][0] << ", Column: " << results[i][1] << ", NCC Result: " << results[i][2] << endl;
		
		//These store the positions of the best results so they can be used to indicate the positions on the picture
		int alterRow = results[i][0];
		int alterColumn = results[i][1];		
		
		int row;
		int col;

		if (i == 0) //if i is 0 then this is the highest score in the Vector which is the closest match Wally. I wanted to indicate Wally with a thicker border than the other N-best results.
		{
			//Creating the top border around Wally
			for (row = alterRow - 4; row < alterRow; row++) // +/- 4 is used to make a thick border, 4 pixels wide
			{
				for (col = alterColumn - 4; col < alterColumn + R.refCols + 4; col++) 
				{
					L.lVector[row][col] = 0; //This sets the greyscale values in the vector storing the large image matrix to 0 so the pixels are made completely black
				}
			}
			//Creating the left and right borders around Wally
			for (row = alterRow; row < alterRow + R.refRows; row++)
			{
				for (col = alterColumn - 4; col < alterColumn - 1; col++)
				{
					L.lVector[row][col] = 0;
				}
				for (col = alterColumn + R.refCols + 1; col < alterColumn + R.refCols + 4; col++)
				{
					L.lVector[row][col] = 0;
				}
			}
			//Creating the bottom border around Wally
			for (row = alterRow + R.refRows; row < alterRow + R.refRows + 4; row++)
			{
				for (col = alterColumn - 4; col < alterColumn + R.refCols + 4; col++)
				{
					L.lVector[row][col] = 0;
				}
			}
		}
		else //These are the other N-best values which are indicated by a thinner border
		{
			//Creating the top border around the other similar results
			for (row = alterRow - 2; row < alterRow; row++) // +/- 2 is used to create a thinner border 2 pixels wide so the border around Wally appears significantly thicker
			{
				for (col = alterColumn - 2; col < alterColumn + R.refCols + 2; col++)
				{
					L.lVector[row][col] = 0;
				}
			}
			//Creating the left and right borders around the other similar results
			for (row = alterRow; row < alterRow + R.refRows; row++)
			{
				for (col = alterColumn - 2; col < alterColumn - 1; col++)
				{
					L.lVector[row][col] = 0;
				}
				for (col = alterColumn + R.refCols + 1; col < alterColumn + R.refCols + 2; col++)
				{
					L.lVector[row][col] = 0;
				}
			}
			//Creating the bottom border around the other similar results
			for (row = alterRow + R.refRows; row < alterRow + R.refRows + 2; row++)
			{
				for (col = alterColumn - 2; col < alterColumn + R.refCols + 2; col++)
				{
					L.lVector[row][col] = 0;
				}
			}
		}
	}
	cout << "\nWally is most likely to be at row " << results[0][0] << ", column " << results[0][1] << " because this scored the highest NCC value of " << results[0][2] << endl;
	//This explains to the user that the best result at rank 1 is most likely to be Wally since that position scored the highest NCC result meaning it is most similar to Wally.
	
	const char* scenePGM = "Large_Image.pgm"; //This creates a file to write the large image to which will show boxes around Wally and the other N-best values
	L.twoDconversion(L.forPGM, L.lVector, L.largeRows, L.largeCols); //This calls a function which converts the large image matrix (lVector) to a 1D vector so that it can be written to the pgm
	B.write_pgm(scenePGM, L.forPGM, L.largeRows, L.largeCols, 255); //This calls the function to write the pgm image
	
	cout << "\nYou can now see the possible positions of Wally outlined in the .pgm file. The most likely position, which should be Wally, is indicated by a thick border. The other N best values are shown with a thinner border." << endl;

	cin.get();

	return 0;
}
