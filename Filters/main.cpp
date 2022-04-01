#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
using namespace std;

unsigned char img[SIZE][SIZE];


void readImage();
void writeImage();
void bwFilter1();       // 1
void invertFilter();    // 2
                        // 3
                        // 4
                        // 5
void rotateFilter();    // 6
                        // 7
                        // 8
                        // 9
                        // a
                        // b
                        // c

int main() {
	string userInput;
	//while(true){
	//	*need to add screen clear here to clean screen after each process*
	readImage();		//gets image from user
	//give user choices
	printf("Please Select a filter:\n1- Black & White Filter\n2- Invert Filter\n3- Merge Filter\n");
	printf("4- Flip Image\n5- Rotate Image\n6- Darken and Lighten Image\n7- Detect Image Edges\n");
	printf("8- Enlarge Image\n9- Shrink Image\na- Mirror Image\nb- Shuffle Image\nc- Blur Image\n");
	cin >> userInput;

	if (userInput == "1") {
		bwFilter1();
		writeImage();
	}
    else if (userInput == "2") {
        invertFilter();
        writeImage();
    }
    else if (userInput == "5") {
        rotateFilter();
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

void invertFilter() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            img[i][j] = 255 - img[i][j];
        }
    }
}

void rotateFilter() {
    int angle;
    cout << "Rotate (90), (180), (270) or (360) degrees?\n";
    cin >> angle;
    if (angle == 270) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = i; j < SIZE; j++) {
                swap(img[i][j], img[j][i]);
            }
        }
    }
    if (angle == 180) {
        // First flip vertically
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE; j++) {
                swap(img[i][j], img[SIZE-1-i][j]);
            }
        }
        // Then flip horizontally
        for (int i = 0; i < SIZE;i++) {
            for (int j = 0;j < SIZE/2;j++) {
                swap(img[i][j], img[i][SIZE - 1 - j]);
            }
        }
    }
    if (angle == 90) {
        // First flip the image
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE; j++) {
                swap(img[i][j], img[SIZE-1-i][j]);
            }
        }
        // Then get transpose
        for (int i = 0; i < SIZE; i++) {
            for (int j = i; j < SIZE; j++) {
                swap(img[i][j], img[j][i]);
            }
        }
    }
    if (angle == 360) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = i; j < SIZE; j++) {
                swap(img[i][j], img[i][j]);
            }
        }
    }
}