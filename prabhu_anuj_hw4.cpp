/*
 * Name: Anuj Prabhu
 * Date: 10 November 2023
 * Description: prabhu_anuj_hw4.cpp file; driver file that contains function prototypes as well as the functions that produce raw and polished landmasses using dirtball dropping.
 * Usage: ./exe
 * ./exe -s <int>
*/

//.h file imports go here
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
#include <string.h>
#include <time.h>
#include <fstream>

//using statements go here
using namespace std;

//function prototypes go here
int** buildLandmass(int, int);
void displayMap(int**, int, int);
void displayPolishedMap(char**, int, int);
bool isInBounds(int, int, int, int, int, int);
void dropDirtBall(int**, int, int, int, int, int, int);
double frand();
int findMax(int**, int, int);
int** normalizeMap(int**, int, int, int);
char** polishMap(int**, int, int, int);
void landmassTxt(int**, int, int);
void normalizedMapTxt(int**, int, int);
void polishedMapTxt(char**, int, int);

//main method that drives my program's logic and interacts with the user
int main(int argc, char** argv) {
	if(argc != 1 && argc != 3) {//if invalid number of arguments, then output error message
		cout << "Usage: ./exe" << endl;
		cout << "./exe -s <int>" << endl;
		return 0;
	}
	else {
		if(argc == 1) {//if 1 argument is passed, then seed srand with current time
			srand(time(0));
			
			int** landmass; //array that will hold raw landmass values; (values gathered after dropping dirtballs)
			int** normalizedMap;//array that will hold normalized values
			char** polishedMap;//array that will hold polished ASCII characters
			
			//initialize variables to store user input
			int width = 0, height = 0;
	
			int waterline = 40;
	
			int radius = 2, power = 2, dirtballs = 0;

			//prompt the user for dimensions
			cout << "Welcome to Anuj Prabhu's CSE240 Terraformer!!" << endl;
	
			cout << "Enter grid width:" << endl;
			cin >> width;
	
	
			cout << "Enter grid height:" << endl;
			cin >> height;


			cout << "Enter value for waterline (40-200):" << endl;
			cin >> waterline;

			cout << "Enter dirtball radius (minimum 2):" << endl;
			cin >> radius;


			cout << "Enter dirtball power rating (minimum = radius):" << endl;
			cin >> power;


			cout << "Enter number of dirtballs to drop:" << endl;
			cin >> dirtballs;
	
			//build landmass of dimensions given by the user
			landmass = buildLandmass(width, height);
	
			//drop dirtballs on the landmass
			int i = 0;
			while(i < dirtballs) {
				int centerX = (int) (frand() * width);
				int centerY = (int) (floor(frand() * height));
		
				dropDirtBall(landmass, width, height, centerX, centerY, radius, power);
				i++;
			}
			displayMap(landmass, width, height);//print the raw landmass to console
			landmassTxt(landmass, width, height);//print the raw landmass to a file
			
			//find the highest value in the raw array
			int maxVal;
			maxVal = findMax(landmass, width, height);
			
			//use that maximum value to normalize the raw array
			normalizedMap = normalizeMap(landmass, width, height, maxVal);
	
			displayMap(normalizedMap, width, height);//output the normalized array to the console
			normalizedMapTxt(normalizedMap, width, height);//output the normalized array to a file
	
			polishedMap = polishMap(normalizedMap, width, height, waterline);//create the polished landmass array using the normalized array
	
			displayPolishedMap(polishedMap, width, height);//print the polished array to the console
			polishedMapTxt(polishedMap, width, height);//print the polished array to a file
	
			//free up landmass memory
			for(int i = 0; i < height; i++) {
				delete[] landmass[i];
			}
			delete[] landmass;
	
	
			//free up normalizedMap memory
			for(int i = 0; i < height; i++) {
				delete[] normalizedMap[i];
			}
			delete[] normalizedMap;
	
	
			//free up polishedMap memory
			for(int i = 0; i < height; i++) {
				delete[] polishedMap[i];
			}
			delete[] polishedMap;
			
			return 0;
		}
		else if(argc == 3 && strcmp(argv[1], "-s") == 0) {//if 3 arguments are passed, check for argument validity and seed srand with <int> given by user; follow same main logic as the if block above
			srand(atoi(argv[2]));
			
			
			int** landmass;
			int** normalizedMap;
			char** polishedMap;
	
			int width = 0, height = 0;
	
			int waterline = 40;
	
			int radius = 2, power = 2, dirtballs = 0;
	
			cout << "Welcome to Anuj Prabhu's CSE240 Terraformer!!" << endl;
	
			cout << "Enter grid width:" << endl;
			cin >> width;
	
	
			cout << "Enter grid height:" << endl;
			cin >> height;


			cout << "Enter value for waterline (40-200):" << endl;
			cin >> waterline;

			cout << "Enter dirtball radius (minimum 2):" << endl;
			cin >> radius;


			cout << "Enter dirtball power rating (minimum = radius):" << endl;
			cin >> power;


			cout << "Enter number of dirtballs to drop:" << endl;
			cin >> dirtballs;
	
			landmass = buildLandmass(width, height);
	
			int i = 0;
			while(i < dirtballs) {
				int centerX = (int) (frand() * width);
				int centerY = (int) (floor(frand() * height));
		
				dropDirtBall(landmass, width, height, centerX, centerY, radius, power);
				i++;
			}
			displayMap(landmass, width, height);
			landmassTxt(landmass, width, height);
	
			int maxVal;
			maxVal = findMax(landmass, width, height);
	
			normalizedMap = normalizeMap(landmass, width, height, maxVal);
	
			displayMap(normalizedMap, width, height);	
			normalizedMapTxt(normalizedMap, width, height);
	
			polishedMap = polishMap(normalizedMap, width, height, waterline);
	
			displayPolishedMap(polishedMap, width, height);
			polishedMapTxt(polishedMap, width, height);
	
			//free up landmass memory
			for(int i = 0; i < height; i++) {
				delete[] landmass[i];
			}
			delete[] landmass;
	
	
			//free up normalizedMap memory
			for(int i = 0; i < height; i++) {
				delete[] normalizedMap[i];
			}
			delete[] normalizedMap;
	
	
			//free up polishedMap memory
			for(int i = 0; i < height; i++) {
				delete[] polishedMap[i];
			}
			delete[] polishedMap;
			
			return 0;
		}
		else {
			cout << "Usage: ./exe" << endl;
			cout << "./exe -s <int>" << endl;
			return 0;
		}
	}
}

//function that builds (allocates memory for) landmass (dynamically allocated 2D array) based on given width and height and initializes the array values to 0.
int** buildLandmass(int width, int height) {
	
	int** landmass;
	landmass = new int*[height];//allocate memory for rows
	
	for(int i = 0; i < height; i++) {//for every row
		landmass[i] = new int[width];//allocate memory for columns
	}

	for(int row = 0; row < height; row++) {
		for(int column = 0; column < width; column++) {
			landmass[row][column] = 0;//initialize 2D array values to 0
		}
	}

	return landmass;//return the 2D array
}

//function that prints the raw landmass and normalized landmass to the console
void displayMap(int** landmass, int width, int height) {
	for(int row = 0; row < height; row++) {
		for(int column = 0; column < width; column++) {
			cout << setw(4) << landmass[row][column];//print every element of the array with a spacing of 4 in between the elements
		}
		cout << endl;//print a new line after every row
	}
	cout << endl;
	cout << endl;
}

//function that print the polished landmass array to the console
void displayPolishedMap(char** map, int width, int height) {
	for(int row = 0; row < height; row++) {
		for(int column = 0; column < width; column++) {
			cout << map[row][column];//print every character of the arry to the console
		}
		cout << endl;//print a newline after a row is printed
	}
}

//functions that returns a bool true if an index is within the bounds of an array and returns false otherwise
bool isInBounds(int x, int y, int minX, int minY, int maxX, int maxY) {
	if(
	(x >= minX && x < maxX) &&//if x is greater than or equal to lowest bound and less than or equal to (highest bound - 1), and
	(y >= minY && y < maxY)//if y is greater than or equal to lowest bound and less than or equal to (highest bound - 1), the index is within bounds of the 2D array
	) {
		return true;//thus, return bool true
	}
	else {
		return false;//else, the index is out of bounds, so return bool false
	}
}


/*
 * dropDirtBall function: drops 1 dirtball of given radius and power at centerX and centerY in the given landmass.
 *
 * Moore Neighborhood and Extended Moore Neighborhood processing:
 *
 * 1. Check if centerX and centerY are in bounds. If yes:
 * 2. Based on radius, create extended moore neighrbood in one go
*/
void dropDirtBall(int** landmass, int width, int height, int centerX, int centerY, int radius, int power) {
	if(
	(centerX >= 0 && centerX < width) &&//if centerX is in bounds
	(centerY >= 0 && centerY < height) &&//and centerY is in bounds
	landmass != NULL
	) {
		for(int y = -radius; y <= radius; y++) {
			for(int x = -radius; x <= radius; x++) {//create EMN (extended moore neighborhood)
				if(isInBounds(centerX + x, centerY + y, 0, 0, width, height)) {//if the index in the EMN is in bounds
					double distance;
					distance = sqrt(pow((centerX + x) - centerX, 2) + pow((centerY + y) - centerY, 2));//find distance from that index to the center
					
					if (distance <= radius) {//if that distance is less than the radius of the drop, that means that indeex is in the drop zone
						int impactVal;
						impactVal = 0;

						impactVal = power - floor(distance);//so, use the power rating to generate an impact for that index based on its proximity to the center.
										//impact lessens with each layer as the drop  extends outwards towards the radius limit
						
						landmass[centerY + y][centerX + x]+=impactVal;//drop the dirtball
					}
					//else {
					//	cout << "distance > radius" << endl;
					//}
				}
				//else {
				//	cout << "array index not in bounds" << endl;
				//}
			}
		}
	}
	else {
		cout << "centerX, centerY, and/or landmass = null issue" << endl;
	}
}

//frand function that generates a floating point number between 0 and 1.
double frand() {
	return (double)rand() / ((double)RAND_MAX + 1);
}

//function that find the maximum value inside a 2D array
int findMax(int** landmass, int width, int height) {
	int max;
	max = landmass[0][0];//initialize max to the first element of the array
	for(int row = 0; row < height; row++) {
		for(int column = 0; column < width; column++) {
			if(landmass[row][column] > max) {//if the current element is higher than max, make it the new max.
				max = landmass[row][column];
			}
		}
	}
	return max;//return max
}

//function that normalizes the raw landmass
int** normalizeMap(int** landmass, int width, int height, int maxVal) {
	int** normalizedMap;
	normalizedMap = new int*[height];

	for(int i = 0; i < height; i++) {
		normalizedMap[i] = new int[width];//allocate memory for the normalizedMap array based on the given width and height, in the same way as raw landmass.
	}

	for(int row = 0; row < height; row++) {
		for(int column = 0; column < width; column++) {
			normalizedMap[row][column] = ((double)landmass[row][column] / maxVal) * 255;//normalize the raw landmass by dividing each raw value by the maximum value of raw landmass and multiplying that by 255.
		}
	}
	return normalizedMap;//return normalizedMap
}

char** polishMap(int** landmass, int width, int height, int waterline) {
	char** polishedMap;
	polishedMap = new char*[height];

	for(int i = 0; i < height; i++) {
		polishedMap[i] = new char[width];//allocate memory for polishedMap array based on the given width and height, in the same way as raw landmass.
	}

	int landzone = 255 - waterline;//calculate landzone as 255 - waterline

	for(int row = 0; row < height; row++) {
		for(int column = 0; column < width; column++) {
			int normalizedVal = landmass[row][column];//get the normalized val as we are going to use that to determine the characters in polishedMap

			if(normalizedVal < floor((0.5 * waterline))) {//floor the result of getting a percentage of waterline. Allocate a different character for each category based on the spec.
				polishedMap[row][column] = '#';//allocate a '#' for deep-water.
			}
			else if(
			(normalizedVal >= floor((0.5 * waterline))) &&
			(normalizedVal <= waterline)//allocate a '~' for shallow-water.
			) {
				polishedMap[row][column] = '~';
			}
			else if(normalizedVal > waterline) {
				if(normalizedVal < (waterline + floor((0.15 * landzone)))) {//allocate a '.' for coast/beach.
					polishedMap[row][column] = '.';
				}
				else if(
				(normalizedVal >= (waterline + floor((0.15 * landzone)))) &&
				(normalizedVal < (waterline + floor((0.4 * landzone))))//allocate a '-' for plains/grass.
				) {
					polishedMap[row][column] = '-';
				}
				else if(
				(normalizedVal >= (waterline + floor((0.4 * landzone)))) &&
				(normalizedVal < (waterline + floor((0.8 * landzone))))//allocate a '*' for forests.
				) {
					polishedMap[row][column] = '*';
				}
				else {
					polishedMap[row][column] = '^';//else, allocate a '^' for mountains.
				}
			}
		}
	}
	return polishedMap;//return the polished map.
}

//function that writes the raw landmass to a text file.
void landmassTxt(int** landmass, int width, int height) {
	ofstream outfile;//create an ofstream object.
	outfile.open("raw_landmass.txt", ios::out);//open the (OFS) output file stream for "raw_landmass.txt" for output operations.
	
	for(int row = 0; row < height; row++) {
		for(int column = 0; column < width; column++) {
			outfile << setw(4) << landmass[row][column];//write each integer to the OFS with a spacing of 4 in between integers.
		}
		outfile << endl;//write a newline after every row.
	}
	outfile.close();//close the file stream.
}

//function that writes the normalized landmass to a text file.
void normalizedMapTxt(int** landmass, int width, int height) {
	ofstream outfile;//create an ofstream object.
	outfile.open("normalized_landmass.txt", ios::out);//open the OFS for "normalized_landmass.txt" for output operations.
	
	for(int row = 0; row < height; row++) {
		for(int column = 0; column < width; column++) {
			outfile << setw(4) << landmass[row][column];//write each integer of the normalized array to the file with a spacing of 4 in between integers.
		}
		outfile << endl;//write a newline after every row.
	}
	outfile.close();//close the file stream.
}

//function that writes the polished map to a text file.
void polishedMapTxt(char** map, int width, int height) {
	ofstream outfile;//create an ofstream object.
	outfile.open("final_landmass.txt", ios::out);//open the OFS for "final_landmass.txt" for output operations.
	
	for(int row = 0; row < height; row++) {
		for(int column = 0; column < width; column++) {
			outfile << map[row][column];//write each character of the polished array to the file.
		}
		outfile << endl;//write a newline after every row.
	}
	outfile.close();//close the file stream.
}
