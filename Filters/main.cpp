#include <iostream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
#include <string>

using namespace std;

unsigned char img[SIZE][SIZE];
unsigned char temp[4][SIZE/2][SIZE/2] = {};
unsigned char quarter[(SIZE/2)*(SIZE/2)] = {};


void readImage();
void writeImage();
void bwFilter1();                 // 1
void invertFilter();              // 2
void mergeFilter();               // 3
void flipFilter();                // 4
int rotateFilter();              // 5
void darkenAndLightenFilter();    // 6
// 7
void enlargeFilter();             // 8
void shrinkFilter();              // 9
void mirrorFilter();              // a
void shuffleFilter();             // b
void blurFilter();                // c

void rotate90();
void extractQuarter(unsigned char* &, int);


int main() {
    string userInput;
    readImage();		//gets image from user
    while (true) {
        //give user choices
        printf("Please Select a filter:\n1- Black & White Filter\n2- Invert Filter\n3- Merge Filter\n4 - Flip Image\n5 - Rotate Image\n");
        printf("6 - Darken and Lighten Image\n7 - Detect Image Edges\n8 - Enlarge Image\n9 - Shrink Image\na - Mirror Image\nb - Shuffle Image\nc - Blur Image\ns - Save changes\n0 - To end\n");

        cin >> userInput;
        if (userInput == "1") {
            bwFilter1();
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
        }
        else if (userInput == "0") {
            printf("Program Finished");
            break;
        }
        else
        {
            printf("Invalid Input. Please try again\n");
            sleep(1);
            return main();      //takes another photo from user
        }
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
    cin >> flip;
    if (flip == "h") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                swap(img[i][j], img[i][SIZE - 1 - j]);
            }
        }
    } else if (flip == "v") {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE; j++) {
                swap(img[i][j], img[SIZE - 1 - i][j]);
            }
        }
    } else {
        printf("Invalid input, Please try again\n");
        return flipFilter();
    }
}

int rotateFilter() {
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

void enlargeFilter() {
    int inputQuarter;
    unsigned char * pQuarter = quarter;
    cout << "Which quarter to enlarge 1, 2, 3 or 4?\n";
    cin >> inputQuarter;
    // Extract a certain quarter to work with
    extractQuarter(pQuarter, inputQuarter);
    // Enlarge that quarter into the whole image
    int k = 0;
    for (int i = 0; i < SIZE; i+=2) {
        for (int j = 0; j < SIZE; j+=2) {
            img[i][j] = pQuarter[k];
            img[i][j+1] = pQuarter[k];
            img[i+1][j] = pQuarter[k];
            img[i+1][j+1] = pQuarter[k];
            k++;
        }
    }
}


void extractQuarter(unsigned char * & ptr, int quarter) {
    int startRow, endRow, startCol, endCol;
    if (quarter == 1) {
        startRow = 0;
        startCol = 0;
        endRow = SIZE / 2;
        endCol = SIZE / 2;
    }
    else if (quarter == 2) {
        startRow = 0;
        startCol = SIZE / 2;
        endRow = SIZE / 2;
        endCol = SIZE;
    }
    else if (quarter == 3) {
        startRow = SIZE / 2;
        startCol = 0;
        endRow = SIZE;
        endCol = SIZE / 2;
    }
    else if (quarter == 4) {
        startRow = SIZE / 2;
        startCol = SIZE / 2;
        endRow = SIZE;
        endCol = SIZE;
    }
    else {
        cout << "Unrecognized quarter!\n";
        startRow = 0;
        startCol = 0;
        endRow = SIZE / 2;
        endCol = SIZE / 2;
    }

    int k = 0;
    for (int i = startRow; i < endRow; i++) {
        for (int j = startCol; j < endCol; j++) {
            ptr[k++] = img[i][j];
        }
    }
}



void shrinkFilter(){
    int shrinkFactor, x = 0, y = 0;
    cout << "By which factor do you want to shrink the image: 2, 3, or 4?" << endl;
    cin >> shrinkFactor;
    unsigned char newImg[SIZE][SIZE] = {{0}};   //creating a new array to store the shrunk image
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
    unsigned char * pQuarter = quarter;
    int arr = 0;
    int k = 0, s = 0;
    cout << "New order of quarters ?\n";
    cin.ignore();
    getline(cin, order);
    for (int i = 0; i < order.length(); i++) {
        if (order[i] == ' ') {
            continue;
        }
        unsigned char * pTemp = &temp[arr++][0][0];
        extractQuarter(pQuarter, (int) (order[i] - '0'));
        for (int j = 0; j < ((SIZE * SIZE) / 4); j++) {
            pTemp[j] = pQuarter[j];
        }
    }
    int q = 0, row = 0, col = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            img[i][j] = temp[q][row][col];
            col++;
            if (j == SIZE / 2 - 1) {
                col = 0;
                q++;
            }
        }
        q--;
        row++;
        if (i == SIZE / 2 - 2) {
            row = 0;
            q += 2;
        }
    }
}


void blurFilter(){
    int avg, sum = 0;
    // Calculates average of each 8 subsequent pixels and assigns this value to each pixel of the 8 horizontally
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 8; ++k) {
                sum += img[i][j + k];
            }
            avg = sum/8;
            img[i][j] = avg;
            sum = 0;
        }

    }
    sum = 0;
    // Calculates average of each 8 subsequent pixels and assigns this value to each pixel of the 8 vertically
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 8; ++k) {
                sum += img[j + k][i];
            }
            avg = sum/8;
            img[j][i] = avg;
            sum = 0;
        }
    }
}