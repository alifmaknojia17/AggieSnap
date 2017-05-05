// This file contains all of the definitions to the functions that we will reference
#include "std_lib_facilities_4.h"
#include "Input.h"
#include "Output.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <time.h>
using namespace std;

// Local or URL file
enum { FILE_LOCAL, FILE_URL };

// Get current value of counter
int currentCount();

// Update value of counter
void updateCount();

// Convert a string to lowercase
string strtolower(string);

// Return image object of image based on id
imageOutput getImage(int);

// Return a vector of image IDs that match specified search parameters
vector<int> searchImages(string);

// Default images
vector<int> defaultImages();

// Update tags of an image based on its id
void updateTags(int, vector<string>);