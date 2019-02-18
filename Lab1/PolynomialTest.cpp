// Lab 1
// Chris Staykov 20717876
// Robyn Ching 20719829

#ifndef __POLYNOMIALTEST_H__
#define __POLYNOMIALTEST_H__
#endif

void PolynomialTest::testConstructor1() {

    int a1[3] = {1,2,3};
    Polynomial polynomial(a1, 3);
    assert(polynomial.coefficients.size() == 3);
    assert(polynomial.coefficients[0] == 1);
    assert(polynomial.coefficients[1] == 2);
    assert(polynomial.coefficients[2] == 3);
    cout<< "Test1A PASS: Typical array input for constructor" << endl;
    
    int a2[0] = {};
    polynomial = Polynomial(a2, 0);
    assert(polynomial.coefficients.size() == 1);
    assert(polynomial.coefficients[0] == 0);
    cout<< "Test1B PASS: Empty array as input for constructor" << endl;
    
    int a3[1005] = {0};
    try {
        polynomial = Polynomial(a3, 1005);
    } catch (invalid_argument) {
        cout<< "Test1C PASS: Polynomial degree cannot exceed 1000" << endl;
    }
    
    int a4[5] = {4,0,2,0,0};
    polynomial = Polynomial(a4, 5);
    assert(polynomial.coefficients.size() == 3);
    assert(polynomial.coefficients[0] == 4);
    assert(polynomial.coefficients[1] == 0);
    assert(polynomial.coefficients[2] == 2);
    cout<< "Test1D PASS: Removes zeros at end of array" << endl;
    
    int a5[5] = {0,0,0,0,0};
    polynomial = Polynomial(a5, 5);
    assert(polynomial.coefficients.size() == 1);
    assert(polynomial.coefficients[0] == 0);
    cout<< "Test1E PASS: If all zeros writes only one" << endl;
}

void PolynomialTest::testConstructor2() {
    
    Polynomial polynomial = Polynomial();
    int size = polynomial.coefficients.size();
    
    assert(polynomial.coefficients.size() >= 0);
    assert(polynomial.coefficients.size() <= 1000);
    cout<< "Test2A PASS: Empty constructor has proper size" << endl;
    
    for (int i = 0; i < size ; i++) {
        assert(polynomial.coefficients[i] >= -1000);
        assert(polynomial.coefficients[i] <= 1000);
    }
    
    cout<< "Test2B PASS: Empty constructor has proper elements" << endl;
    
}

void PolynomialTest::testConstructor3() {
    
    Polynomial polynomial = Polynomial("input.txt");
    assert(polynomial.coefficients.size() == 5);
    assert(polynomial.coefficients[0] == 1);
    assert(polynomial.coefficients[1] == 2);
    assert(polynomial.coefficients[2] == 3);
    assert(polynomial.coefficients[3] == 4);
    assert(polynomial.coefficients[4] == 5);
    cout<< "Test3A PASS: Typical array input file" << endl;
    
}
