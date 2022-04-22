// FCAI - Programming 1 - 2022 - Assignment 3
// Program Name: Gray-Scale-Image-Processor.cpp
// Last Modification Date: Apr 21, 2022
// Author1 and ID and Group: Mahmoud Adel  | 20210563 | S25
// Author2 and ID and Group: Maya Ayman    | 20210508 | S25
// Author3 and ID and Group: Yousef Kilany | 20210544 | S25
// Teaching Assistant: Eng. Mahmoud Fateaha 
// Purpose: This program processes images taken from the user in many different ways.

#include <iostream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
#include<algorithm>
#include <string>

using namespace std;

unsigned char img[SIZE][SIZE];
unsigned char temp[4][SIZE/2][SIZE/2] = {};    // The use of 3D array here is for organizing        q1
unsigned char quarter[(SIZE/2)*(SIZE/2)] = {}; // memory, so quarters get stored squentially:       q2
                                               // this makes appending elements in the memory       q3
                                               // is surely going to finish a quarter entirely      q4
void readImage();                              // before moving to the next quarter.
void writeImage();
void bwFilter();                  // 1
void invertFilter();              // 2
void mergeFilter();               // 3
void flipFilter();                // 4
void rotateFilter();              // 5
void darkenAndLightenFilter();    // 6
void edgeFilter();                // 7
void enlargeFilter();             // 8
void shrinkFilter();              // 9
void mirrorFilter();              // a
void shuffleFilter();             // b
void blurFilter();                // c

void rotate90();
void extractQuarter(unsigned char* &, int);


int main() {
    // NOTE: The program loops on the same picture until saved, The user can apply multiple filters on the same picture.
    // The program asks for a new picture only after the user save the previous picture.
    string userInput;
    readImage();		//gets image from user
    while (true) {
        //give user choices
        printf("Please Select a filter:\n1- Black & White Filter\n2- Invert Filter\n3- Merge Filter\n4 - Flip Image\n5 - Rotate Image\n");
        printf("6 - Darken and Lighten Image\n7 - Detect Image Edges\n8 - Enlarge Image\n9 - Shrink Image\na - Mirror Image\nb - Shuffle Image\nc - Blur Image\ns - Save changes\n0 - To end\n");

        cin >> userInput;
        if (userInput == "1") {
            bwFilter();
            printf("Black and white complete\n");
        }
        else if (userInput == "2") {
            invertFilter();
            printf("Image Inverted\n");
        }
        else if (userInput == "3"){
            mergeFilter();
            printf("2 images merged\n");
        }
        else if (userInput == "4") {
            flipFilter();
            printf("Image flipped\n");
        }
        else if (userInput == "5") {
            rotateFilter();
            printf("Image rotated\n");
        }
        else if (userInput == "6") {
            darkenAndLightenFilter();
            printf("Image lightened/darkened\n");
        }
        else if (userInput == "7") {
            edgeFilter();
            printf("Edges detected\n");
        }
        else if (userInput == "8") {
            enlargeFilter();
            printf("Image enlarged\n");
        }
        else if (userInput == "9") {
            shrinkFilter();
            printf("Image shrunk\n");
        }
        else if (userInput == "a") {
            mirrorFilter();
            printf("Image mirrored\n");
        }
        else if (userInput == "b") {
            shuffleFilter();
            printf("Image Shuffled\n");
        }
        else if (userInput == "c"){
            blurFilter();
            printf("Image blurred\n");
        }
        else if (userInput == "s") {
            writeImage();
            printf("Save completed\n");
            sleep(1);
            return main();      //takes another photo from user

        }
        else if (userInput == "0") {
            printf("Program Finished");
            break;
        }
        else
            printf("Invalid Input. Please try again\n");
        sleep(1);
    }
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

void bwFilter() {
    //calculate Average gray pixel
    int avg = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            avg = avg + img[i][j];
        }
    }
    avg = avg / (SIZE * SIZE);              // sum of all pixels values / size of the picture

    //Apply B&W Filter
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (img[i][j] > avg)            // if pixel value is higher than average
                img[i][j] = 255;            // turn it white
            else
                img[i][j] = 0;              // else turn it black
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

void mergeFilter(){
    // Takes the name of the image to be merged with the current one
    char imageName2[100];
    unsigned char img2[SIZE][SIZE];
    cout << "Please enter name of the image to merge: " << endl;
    cin >> imageName2;
    strcat(imageName2, ".bmp");
    readGSBMP(imageName2, img2);

    // Merges the 2 images
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            img[i][j] = (img[i][j] + img2[i][j]) / 2;
        }
    }
}

void flipFilter() {
    string flip;
    printf("h to flip horizontally, v to flip vertically: ");
    cin >> flip;                        // take user input for flip direction
    if (flip == "h") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                swap(img[i][j], img[i][SIZE - 1 - j]);      // swap pixel with it's corresponding horizontal pixel
            }
        }
    } else if (flip == "v") {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE; j++) {
                swap(img[i][j], img[SIZE - 1 - i][j]);      // swap pixel with it's corresponding vertical pixel
            }
        }
    } else {
        printf("Invalid input, Please try again\n");
        return flipFilter();                                // recursion in case of invalid input
    }
}

void rotateFilter() {
    int angle;
    cout << "Rotate (90), (180), (270) or (360) degrees?\n";
    cin >> angle;
    if (angle == 360 || angle == 270 || angle == 180 || angle == 90) {
        for (int i = 0; i < angle / 90; i++) {
            rotate90();
        }
    }
    else {
        cout << "Unrecognized angle! Please try again\n";
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

void darkenAndLightenFilter() {
    string rspns;
    cout << "Do you want to lighten or darken the image? " << endl;
    cin >> rspns;
    transform(rspns.begin(), rspns.end(), rspns.begin(), ::tolower);
    // Lightens an image
    if (rspns == "lighten")
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                (img[i][j] * 1.5 > 255) ? img[i][j] = 255 : img[i][j] += 0.5 * img[i][j];
            }
        }
    // Darkens an image
    else if (rspns == "darken")
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                img[i][j] /= 2;
            }
        }
}

void edgeFilter() {
    bwFilter();
    for (int i = 0;i < SIZE;i++) {
        for (int j = 0;j < SIZE;j++) {
            if (img[i][j] != img[i][j + 1] || img[i][j] != img[i + 1][j])    // if pixel is not the same value as the next horizontal or vetrical pixel
                img[i][j] = 0;                                               // make it black
            else
                img[i][j] = 255;                                             // make it white
        }
    }
}

void enlargeFilter() {
    int inputQuarter;
    unsigned char * pQuarter = quarter; // Point at a quarter-sized array to store a quarter into.
    cout << "Which quarter to enlarge 1, 2, 3 or 4?\n";
    cin >> inputQuarter;
    // Extract a certain quarter to work with
    extractQuarter(pQuarter, inputQuarter);
    // Enlarge that quarter into the whole image
    int k = 0;
    for (int i = 0; i < SIZE; i+=2) {
        for (int j = 0; j < SIZE; j+=2) { // by putting each single pixel from quarter
            img[i][j] = pQuarter[k];      // into 4 pixels of the original image.
            img[i][j+1] = pQuarter[k];
            img[i+1][j] = pQuarter[k];
            img[i+1][j+1] = pQuarter[k];
            k++;
        }
    }
}


void extractQuarter(unsigned char * & ptr, int quarter) {
    int startRow = 0, endRow = SIZE/2, startCol = 0, endCol = SIZE/2;
    // Determine boundries according to quarter
    if (quarter == 2) {
        startCol = SIZE / 2;
        endCol = SIZE;
    }
    else if (quarter == 3) {
        startRow = SIZE / 2;
        endRow = SIZE;
    }
    else if (quarter == 4) {
        startRow = SIZE / 2;
        startCol = SIZE / 2;
        endRow = SIZE;
        endCol = SIZE;
    }
    if (quarter < 1 or quarter > 4)
        cout << "Unrecognized quarter!\n";
    
    int k = 0;
    for (int i = startRow; i < endRow; i++) {
        for (int j = startCol; j < endCol; j++) {
            ptr[k++] = img[i][j];
        }   // Due to the squential organization of memory we can               
    }       // store the image row-by-row with a single iterator(k)
}



void shrinkFilter(){
    int shrinkFactor, x = 0, y = 0;
    cout << "By which factor do you want to shrink the image: 2, 3, or 4?" << endl;
    cin >> shrinkFactor;
    unsigned char newImg[SIZE][SIZE];      //creating a new array to store the shrunk image

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            newImg[i][j] = 255;
        }
    }
    // Shrinking the image by removing some pixels
    for (int i = 0; i < SIZE; i += shrinkFactor) {
        for (int j = 0; j < SIZE; j += shrinkFactor) {
            newImg[x][y++] = img[i][j];
        }
        x++;
        y = 0;
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            img[i][j] = newImg[i][j];
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


void shuffleFilter() {
    string order;
    unsigned char * pQuarter = quarter; // Point at a quarter-sized array to store a quarter into.
    unsigned char * pTemp = &temp[0][0][0]; // Point at temp 3D array (divided into 4 quarters)
    int k = 0;
    cout << "New order of quarters ?\n";
    cin.ignore(); // For getline() to work properly
    getline(cin, order);                       
    for (int i = 0; i < order.length(); i++) { // Fill a temp. array with the shuffled image
        if (order[i] == ' ') {                 // a quarter per iteration
            continue; 
        } 
        extractQuarter(pQuarter, (int) (order[i] - '0'));
        for (int j = 0; j < ((SIZE * SIZE) / 4); j++) {
            pTemp[k] = pQuarter[j]; // Store extracted-quarter[original] inside current quarter[temp]
            k++;
        }
    }
    // Transfer temp. array into original image.
    int qrtr = 0, row = 0, col = 0;
    for (int i = 0; i < SIZE; i++) { // Store a 3D array into a 2D array
        if (i == SIZE / 2) {
            qrtr += 2; // Go to next half (Vertically)
            row = 0;
        }
        col = 0;
        for (int j = 0; j < SIZE; j++) {
            if (j == SIZE / 2) {
                qrtr++; // Go to next quarter(Horizontally), same row
                col = 0;
            }
            img[i][j] = temp[qrtr][row][col];
            col++;
        }
        qrtr--; // Go back to previous quarter(Horizontally), new row
        row++;
    }
}


void blurFilter() {
    int avg, sum = 0;
    // Calculates average of each 8 subsequent pixels and assigns this value to each pixel of the 8 horizontally
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; j++) {
            if (j <= 247) {                              // makes sure the index doesn't go beyond 256
                for (int k = 0; k < 8; ++k) {
                    sum += img[i][j + k];
                }
                avg = sum / 8;
                img[i][j] = avg;
                sum = 0;
            }
            else {
                img[i][j] = avg;
            }
        }
    }
    sum = 0;
    // Calculates average of each 8 subsequent pixels and assigns this value to each pixel of the 8 vertically
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; j++) {
            if (j <= 247) {                             // makes sure the index doesn't go beyond 256
                for (int k = 0; k < 8; ++k) {
                    sum += img[j + k][i];
                }
                avg = sum / 8;
                img[j][i] = avg;
                sum = 0;
            }
            else {
                img[j][i] = avg;
            }
        }
    }
}
