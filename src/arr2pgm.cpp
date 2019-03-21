#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void arr2pgm(int img [][256],char const* name){

  string inputfile;

  inputfile= "xdg-open ";
  inputfile+=name;

  try{
      int sys=system(inputfile.c_str());
  }catch(int e){
    cout << "Couldn't open the original image, error: " << e << endl;
  }

	string out, outfile;

	out = "filtered_";
	out += name;
	

	ofstream result(out);

	result << "P2" << endl;
	result << 256 << " " << 256 << " " << 255 << endl;

  // Now print the array to see the result
	int val;
  for(int row = 0; row < 256; ++row) {
    for(int col = 0; col < 256; ++col) {

    	val = img[row][col];
    	result << val << " ";

    }
  }

  cout << "The filtered image is: " << out << endl;

  outfile = "xdg-open ";
  outfile += out;



  try{
  	  int sys=system(outfile.c_str());
  }catch(int e){
  	cout << "Couldn't open the filtered image, error: " << e << endl;
  }


}