#include <iostream>
#include <fstream>
#include <sstream> // stringstream

#include "pgm2arr.cpp"
#include "filter.cpp"
#include "arr2pgm.cpp"

using namespace std;

const int width = 256, height = 256;

int main(int argc, char const *argv[])
{
	if( argc != 2 ) {
		cout << "Please provide only one argument (e.g $./filter test1.pgm)"<<endl;
		return -1;
   	}

   	ifstream infile(argv[1]);
   	if(infile.fail()){
   		cout << "Failed to load image! Try again!" << endl;
   		return -1;
   	}
   	cout << "The testing image is: " << argv [1] << endl;
   
   	int img[height][width]; //THIS IS THE INITIALIZATION OF THE INPUT, A 2D ARRAY

   	pgm2array(img,infile); // THIS FUNCTION PREPARES THE 2D ARRAY FOR TESTING PURPOSES

      map_filter ob;

   	//THIS IS THE FILTER
   	//THE INPUT ARG IS THE 2D ARRAY CALLED "img" AND THE RESULT IS THE SAME ARRAY FILTERED.
   	ob.filter(img);

   	arr2pgm(img, argv[1]);//THIS FUNCTION WAS WRITTEN TO VISUALIZE THE FILTERED MAP.

	return 0;
}

