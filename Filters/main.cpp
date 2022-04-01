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
void flipFilter();      // 4
void rotateFilter();    // 5
                        // 6
                        // 7
                        // 8
                        // 9
void mirrorFilter();    // a
                        // b
                        // c

void rotate90();


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
    
    else if (userInput == "4") {
        flipFilter();
        writeImage();
    }
    
    else if (userInput == "5") {
        rotateFilter();
        writeImage();
    }

    else if (userInput == "a") {
        mirrorFilter();
        writeImage();
    }
    
    //use else if conditions here for other processes


    //else if(userInput == "0"){
    //  printf("Program Finished");
    //  break;
    //}
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
            img[i][j] = 255 - img[i][j]; // Invert each pixel
        }
    }
}

void flipFilter() {
    string flip;
    printf("h to flip horizontally, v to flip vertically: ");
    cin >> flip;
    if (flip == "h") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0;j < SIZE / 2; j++) {
                swap(img[i][j], img[i][SIZE - 1 - j]);
            }
        }
    }
    else if (flip == "v") {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE; j++) {
                swap(img[i][j], img[SIZE-1-i][j]);
            }
        }
    }
    else {
        printf("Invalid input, Please try again\n");
        return flipFilter();
    }
}

void rotateFilter() {
    int angle;
    cout << "Rotate (90), (180), (270) or (360) degrees?\n";
    cin >> angle;
    if (angle == 360) {
        rotate90();
        rotate90();
        rotate90();
        rotate90();
    }
    else if (angle == 270) {
        rotate90();
        rotate90();
        rotate90();
    }
    else if (angle == 180) {
        rotate90();
        rotate90();
    }
    else if (angle == 90) {
        rotate90();
    }
    else {
        cout << "Not a recognized angle! Please try again\n";
        return rotateFilter();
    }
}

void rotate90() {
    unsigned char temp[SIZE][SIZE];
    // Store img into a temporary array
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            temp[i][j] = img[i][j];
        }
    }
    // Store into img rotated 90 Deg.
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            img[j][SIZE-1-i] = temp[i][j];
        }
    }
}

void mirrorFilter() {
    string mirrorInput;
    printf("1- to Mirror Left half, 2- to Mirror Right half\n3- to Mirror Upper half, 4- to Mirror Lower half\n");
    cin >> mirrorInput;
    if (mirrorInput == "1") {                           //left half mirror
        for (int i = 0; i < SIZE; i++) {
            for (int j = SIZE / 2; j < SIZE; j++) {     //loop over right half
                img[i][j] = img[i][SIZE - 1 -j];            //change every pixel of right half to the opposite half
            }
        }
    }
    else if (mirrorInput == "2") {                  //right half mirror
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < (SIZE / 2); j++) {    //loop over left half
                img[i][j] = img[i][SIZE - 1 -j];          //change every pixel to its opposite half
            }
        }
    }
    else if (mirrorInput == "3") {                  //upper half mirror
        for (int i = SIZE / 2; i < SIZE; i++) {     
            for (int j = 0; j < SIZE; j++) {        //loop over lower half
                img[i][j] = img[SIZE - 1 - i][j];        //change every pixel to its opposite half
            }
        }
    }
    else if (mirrorInput == "4") {                  //lower half mirror
        for (int i = 0;i < (SIZE / 2);i++) {
            for (int j = 0;j < SIZE;j++) {          //loop over upper half
                img[i][j] = img[SIZE -1 - i][j];    //change every pixel to its opposite half
            }
        }
    }
    else {
        printf("Invalid input. Please try again\n");
        return mirrorFilter();
    }
}