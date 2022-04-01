#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
using namespace std;

unsigned char img[SIZE][SIZE];


void readImage();
void writeImage();
void bwFilter1();
void invertFilter();


int main() {
	string userInput;
	//while(true){
	//	*need to add screen clear here to clean screen after each process*
	readImage();		//gets image from user
	//give user choices
	printf("Please Select a filter:\n1- Black & White Filter\n2- Invert Filter\n3- Merge Filter\n");
	printf("4- Flip Image\n5- Darken and Lighten Image\n6- Rotate Image\n7- Detect Image Edges\n");
	printf("8- Enlarge Image\n9- Shrink Image\na- Mirror Image\nb- Shuffle Image\nc- Blur Image\n");
	cin >> userInput;

	if (userInput == "1") {
		bwFilter1();
		writeImage();
	}
	//use else if conditions here for other processes

	else
		printf("Invalid Input. Please try again");
	//}
}




void readImage() {
    char imageName[100];
    printf("Please enter name of the image to process: ");
    cin >> imageName;
    strcat(imageName, ".bmp");
    readGSBMP(imageName, img);
}


void writeImage() {
    char imageName[100];
    printf("Please enter name of the new image: ");
    cin >> imageName;
    strcat(imageName, ".bmp");
    writeGSBMP(imageName, img);
}


void bwFilter1() {
    //calculate Average grey pixel
    ////////need to check if this calculates Avg correctly
    int avg = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            avg = avg + img[i][j];
        }
    }
    avg = avg / (SIZE * SIZE);

    //Apply B&W Filter
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (img[i][j] > avg)
                img[i][j] = 255;
            else
                img[i][j] = 0;
        }
    }
}

void invertFilter() { // There are some ghost pixels that float black on the image??
                      // Don't know what is the problem.
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            img[i][j] = 256 - img[i][j];
        }
    }
}