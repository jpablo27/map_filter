
#include <iostream>
#include <fstream>

using namespace std;

void pgm2array(int img[][256],ifstream & pgm){
  int row = 0, col = 0, numrows = 0, numcols = 0, maxwhite=0;
  stringstream ss;
  string inputLine = "";

  // First line : version
  getline(pgm,inputLine);
  if(inputLine.compare("P2") != 0) cerr << "Version error" << endl;
  //else cout << "Version : " << inputLine << endl;



  // Continue with a stringstream
  ss << pgm.rdbuf();
  // Third line : size
  ss >> numcols >> numrows >> maxwhite;
  //cout << numcols << " columns and " << numrows << " rows and " << maxwhite << endl;


  // Following lines : data
  for(row = 0; row < numrows; ++row)
    for (col = 0; col < numcols; ++col) ss >> img[row][col];


  // Now print the array to see the result

/*  for(row = 0; row < numrows; ++row) {
    for(col = 0; col < numcols; ++col) {
      cout << img[row][col] << " ";
    }
    cout << endl;
  }*/
  pgm.close();
}