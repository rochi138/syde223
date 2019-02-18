// Lab 1
// Chris Staykov 20717876
// Robyn Ching 20719829

#include <vector>
using namespace std;

class Polynomial {
    
    friend class PolynomialTest;
    
    // Sequential list containing the coefficients of the polynomial, stored
    // in increasing order of exponents
    vector<int> coefficients;
    
    public:
    
    // Input is array of int to be stored in coefficients vector
    Polynomial( int array[], int size);
    
    // Generates instance of polynomials with degree from 0 to 1000
    // and coefficients from -1000 to 1000
    Polynomial();
    
    // Input is filename of txt file that contains polynomial size and coefficients
    Polynomial( string fileName );
    
};
