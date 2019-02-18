// Lab 1
// Chris Staykov 20717876
// Robyn Ching 20719829


#ifndef __LAB1_POLYNOMIAL_H__
#define __LAB1_POLYNOMIAL_H__
	#include "lab1_polynomial.h"
#endif
#include <fstream>
#include <iostream>
#include <cstdlib>

Polynomial::Polynomial( int array[], int size) {
    if (size > 1001) {
        //throw invalid_argument("Degree of polynomial cannot exceed 1000");
    }
    
    if (size <= 0) {
        coefficients.push_back(0);
        return;
    }

    int highestDegree = size;
    while (array[highestDegree - 1] == 0) {
        highestDegree--;
        
        if (highestDegree == 1) {
            coefficients.push_back(0);
            return;
        }
    }
    
    
    for (int i = 0; i < highestDegree; i++) {
        coefficients.push_back(array[i]);
    }
}

Polynomial::Polynomial() {
    //srand(time(0));
    
    int size = rand() % 1000 + 1;
    //srand(time(0));
    
    for (int i = 0; i < size; i++) {
        coefficients.push_back(rand()%2001 - 1000);
    }
    
}

Polynomial::Polynomial( string fileName ) {

    int fileNameLength = fileName.length();

    if (fileNameLength <= 4 ||
        fileName[fileNameLength-1] != 't' ||
        fileName[fileNameLength-2] != 'x' ||
        fileName[fileNameLength-3] != 't' ||
        fileName[fileNameLength-4] != '.'
        ) {
        throw invalid_argument("Filename invalid");
    }


    ifstream coefficientFile;
    coefficientFile.open( fileName.c_str() );

    //Error check
    if (coefficientFile.fail()){
        cout<<"A file does not exist with that name. The program will now exit."<<endl<<endl;
        exit(1);
    }

    int num;
    int size;

    if(coefficientFile >> num){
        size = num;
        if (size > 1000)
            throw invalid_argument("Degree of polynomial cannot exceed 1000");
        if (size <= 0) {
            coefficients.push_back(0);
            return;
        }
    }

    while (coefficientFile >> num) {
        coefficients.push_back(num);
    }

    for (int i = size-1; i >= 0; i++){
        if (coefficients[i] == 0)
            coefficients.pop_back();
        else
            break;
    }

    coefficientFile.close();
}

