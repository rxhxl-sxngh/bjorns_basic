#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

Pixel** createImage(int width, int height) {
  cout << "Start createImage... " << endl;
  
  // Create a one dimensional array on the heap of pointers to Pixels 
  //    that has width elements (i.e. the number of columns)
  Pixel** image = new Pixel*[width];
  
  bool fail = false;
  
  for (int i=0; i < width; ++i) { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    image[i] = new Pixel[height];
    
    if (image[i] == nullptr) { // failed to allocate
      fail = true;
    }
  }
  
  if (fail) { // if any allocation fails, clean up and avoid memory leak
    // deallocate any arrays created in for loop
    for (int i=0; i < width; ++i) {
      delete [] image[i]; // deleting nullptr is not a problem
    }
    delete [] image; // delete array of pointers
    return nullptr;
  }
  
  // initialize cells
  //cout << "Initializing cells..." << endl;
  for (int row=0; row<height; ++row) {
    for (int col=0; col<width; ++col) {
      //cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = { 0, 0, 0 };
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel** image, int width) {
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i=0; i<width; ++i) {
    delete [] image[i]; // delete each individual array placed on the heap
  }
  delete [] image;
  image = nullptr;
}

// implement for part 1

int* createSeam(int length) {
  int* seam = new int[length];
  for(int i = 0; i < length; i++)
    seam[i] = 0;
  return seam;
}

void deleteSeam(int* seam) {
  delete[] seam;
}

bool loadImage(string filename, Pixel** image, int width, int height) {
  ifstream inFS;
  inFS.open(filename);

  if(!inFS.is_open()) {
    cout << "Error: failed to open input file - " << filename << endl;
    return false;
  }

  string fileType;
  getline(inFS,fileType);
  if(toupper(fileType.at(0)) != 'P' || fileType.at(1) != '3') {
    cout << "Error: type is " << fileType << " instead of P3" << endl;
    return false;
  }

  int x;
  int y;
  int colorRange;

  inFS >> x;
  if (inFS.fail()) {
    cout << "Error: read non-integer value" << endl;
    return false;
  }
  if(width != x) {
    cout << "Error: input width (" << width << ") does not match value in file ("<< x << ")" << endl;
    return false;
  }

  inFS >> y;
  if (inFS.fail()) {
    cout << "Error: read non-integer value" << endl;
    return false;
  }
  if(height != y) {
    cout << "Error: input height (" << height << ") does not match value in file ("<< y << ")" << endl;
    return false;
  }

  inFS >> colorRange;
  if (inFS.fail()) {
    cout << "Error: read non-integer value" << endl;
    return false;
  }
  if(colorRange < 0 || colorRange >255) {
    cout << "Error: invalid color value " << colorRange << endl;
    return false;
  }

  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      int colorVal;
      inFS >> colorVal;
      if (inFS.fail()) {
        if(inFS.eof()) {
          cout << "Error: not enough color values" << endl;
					return false;
        } else {
          cout << "Error: read non-integer value" << endl;
				  return false;
        }       
      }
      if (colorVal < 0 || colorVal > 255) {
          cout << "Error: invalid color value " << colorVal << endl;
          return false;
      }
      image[j][i].r = colorVal;

      inFS >> colorVal;
      if (inFS.fail()) {
        if(inFS.eof()) {
          cout << "Error: not enough color values" << endl;
					return false;
        } else {
          cout << "Error: read non-integer value" << endl;
				  return false;
        }       
      }
      if (colorVal < 0 || colorVal > 255) {
          cout << "Error: invalid color value " << colorVal << endl;
          return false;
      }
      image[j][i].g = colorVal;

      inFS >> colorVal;
      if (inFS.fail()) {
        if(inFS.eof()) {
          cout << "Error: not enough color values" << endl;
					return false;
        } else {
          cout << "Error: read non-integer value" << endl;
				  return false;
        }       
      }
      if (colorVal < 0 || colorVal > 255) {
          cout << "Error: invalid color value " << colorVal << endl;
          return false;
      }
      image[j][i].b = colorVal;

    }
  }

  char tooMany;
  inFS >> tooMany;
  while (!inFS.eof()) {
    if (tooMany != ' ') {
      cout << "Error: too many color values" << endl;
      return false;
    }
    inFS >> tooMany;
  }

  inFS.close();
  return true;
}

bool outputImage(string filename, const Pixel*const* image, int width, int height) {
  ofstream outFS;
  outFS.open(filename);
  if(!outFS.is_open()) {
    cout << "Error: failed to open output file - " << filename << endl;
    return false;
  }
  
  outFS << "P3" << endl;
  outFS << width << " " << height << endl;
  outFS << "255" << endl;

  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      outFS << image[j][i].r << " " << image[j][i].g  << " " << image[j][i].b << endl;
    }
  }
  outFS.close();
  return true;

}

int energy(const Pixel*const* image, int x, int y, int width, int height) { 
  Pixel above;
  Pixel below;
  Pixel right;
  Pixel left;
  int totalEnergy;
  int xEnergy;
  int yEnergy;
  int xr;
  int xg;
  int xb;
  int yr;
  int yg;
  int yb;

  if (width < 3) {
    xEnergy = 0; 
  } else {

    if (x == 0) {
      left = image[width - 1][y];
      right = image[x + 1][y];
    } else if (x == (width - 1)) {
      left = image[x - 1][y];
      right = image[0][y];
    } else {
      left = image[x - 1][y];
      right = image[x + 1][y];
    } 

    xr = abs(right.r - left.r);
    xg = abs(right.g - left.g);
    xb = abs(right.b - left.b);

    xEnergy = pow(xr, 2) + pow(xg, 2) + pow(xb, 2);
  }
  

  if (height < 3) {
    yEnergy = 0;
  } else {

    if (y == 0) {
      above = image[x][height - 1];
      below = image[x][y + 1];
    } else if (y == (height - 1)) {
      above = image[x][y - 1];
      below = image[x][0];
    } else {
      above = image[x][y - 1];
      below = image[x][y + 1];
    }

    yr = abs(below.r - above.r);
    yg = abs(below.g - above.g);
    yb = abs(below.b - above.b);

    yEnergy = pow(yr, 2) + pow(yg, 2) + pow(yb, 2);
  }

  totalEnergy = xEnergy + yEnergy;

  return totalEnergy;
}

// implement for part 2

// uncomment for part 2

int loadVerticalSeam(const Pixel*const* image, int start_col, int width, int height, int* seam) {
  int energyForward = 0;
  int energyLeft = 0;
  int energyRight = 0;
  int seamEnergy = 0;
  int nextPosition = start_col;
  if (width == 1) {
    for (int i = 0; i < height; i++) {
      seamEnergy += energy(image, nextPosition, i, width, height);    
      seam[i] = nextPosition;
    }
  } else {
    for(int i = 0; i < height; i++) {
      if(nextPosition == 0) {
        energyForward = energy(image, 0, i, width, height);
        energyLeft = energy(image, 1, i, width, height);
        if (energyLeft < energyForward) {
          nextPosition = 1;
        } else {
          nextPosition = 0;
        }
      } else if(nextPosition == (width-1)) {

        energyForward = energy(image, width-1, i, width, height);
        energyRight = energy(image, width-2 - 1, i, width, height);
        if (energyRight < energyForward) {
          nextPosition = width - 2;
        } else {
          nextPosition = width - 1;
        }
        
      } else {
        energyForward = energy(image, nextPosition, i, width, height);
        energyRight = energy(image, nextPosition - 1, i, width, height);
        energyLeft = energy(image, nextPosition + 1, i, width, height);
        if(energyRight < energyForward && energyRight < energyLeft) {
          nextPosition -= 1;
        } else if((energyLeft < energyRight || energyLeft == energyRight) && energyLeft < energyForward) {
          nextPosition += 1;
        } else {
          nextPosition = nextPosition;
        }
      }
      if(i == 0) {
        nextPosition = start_col;     
      }
      seamEnergy += energy(image, nextPosition, i, width, height);
      seam[i] = nextPosition;
    }
  }
  return seamEnergy;
  
}
/*
int loadHorizontalSeam(const Pixel*const* image, int start_row, int width, int height, int* seam) {
  return 0;
}
*/
int* findMinVerticalSeam(const Pixel*const* image, int width, int height) {
  int* minVerticalSeam = createSeam(height);
  int minSeamEnergy = loadVerticalSeam(image, 0, width, height, minVerticalSeam);
  int newEnergy;
  for(int i = 1; i < width - 1; i++) {
    int* newSeam = createSeam(height);
    newEnergy = loadVerticalSeam(image, i, width, height, newSeam);
    if (newEnergy < minSeamEnergy) {
      minSeamEnergy = newEnergy;
      deleteSeam(minVerticalSeam);
      minVerticalSeam = newSeam;
      deleteSeam(newSeam);
    } else {
      deleteSeam(newSeam);
    }
  } 
  return minVerticalSeam;
}
/*
int* findMinHorizontalSeam(const Pixel*const* image, int width, int height) {
  return nullptr;
}
*/
void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {
  for (int i = 0; i < height; i++)
  {
	  for (int j = verticalSeam[i]; j < width - 1; j++)
	  {
		  image[j][i] = image[j+1][i];
	  }
  }
}

/*
void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
}
*/
