/*
NAME: Ashish Kumar
ASSIGNMENT: Lab 5
SOURCES: None
*/

#include <iostream>
#include <cmath>
using namespace std;


#define CMPTOL 1E-6  //Floating point comparison tolerance
#define NUM_OF_TERMS 8 //Number of terms to display in the sequence


struct roots
{
    //Defining a struct to hold the roots of the quadratic equation and a bool
    //as a flag to signal if the roots are coincident
    float r1;
    float r2;
    bool coincident;
};


float calc_discriminant(float a, float b, float c);
roots calc_roots(float a, float b, float c);
void display_formula(roots r, float a0, float a1);
void display_sequence(float C, float D, roots r);


int main()
{
    //Main function
    float A, B, a0, a1;
    float dis;
    roots r;

    cout << "Student Name: Ashish Kumar" << endl;
    cout << endl << "a_{k} = A a_{k-1} + B a_{k-2}  with init cond a_0 and a_1";
    cout << endl;

    for ( int i = 0; i < 4; ++i ) {
        cout << endl << endl << "Run " << (i + 1);
        cout << ": Program requiers user to input A, B, a_0, and a_1";
        cout << endl << "Enter value of A: ";
        cin >> A;
        cout << "Enter value of B: ";
        cin >> B;
        cout << "Enter value of a_0: ";
        cin >> a0;
        cout << "Enter value of a_1: ";
        cin >> a1;
        cout << endl;
        if ( B == 0 ) {
            cout << "\tB cannot be zero. Please enter values again." << endl;
            continue;
        }
        dis = calc_discriminant(1, -A, -B);
        if (dis >= -1*CMPTOL) {
            r = calc_roots(1, -A, -B);
            display_formula(r, a0, a1);
        }
        else {
            cout << "\tRoots are complex." << endl;
            cout << "\tThe combination of A and B results in complex roots of ";
            cout << "the characteristic equation t^2 - At - B = 0" << endl;
            cout << "\tProgram is not going to solve for this case." << endl;
        }
    }

    return 0;
}


float calc_discriminant(float a, float b, float c)
{
    /*
    This function calculates discriminant of a quadratic equation
            a x^2 + b x + c = 0
    Discriminant for a quadratic equation is given by b^2 - 4ac.
    Args:
        a: coefficient for x^2
        b: coefficient for x
        c: constant term
    Returns:
        Discriminant D = b^2 - 4ac
    */
    float D;
    D = pow(b, 2) - 4*a*c;
    return D;
}


roots calc_roots(float a, float b, float c)
{
    /*
    Calculates the roots of a quadratic equation a x^2 + b x + c = 0.
    Notes:
        The discriminant D of the quadratic equation is given by b^2 - 4ac.
        D > 0 ==> Distinct roots
        D = 0 ==> Coincident roots
        D < 0 ==> Complex roots.

        Because we are working with floating point numbers, I have implemented a
        tolerance scheme to test for zero.  Anything between [-CMPTOL, CMPTOL]
        defined at the beginning of this program is considered a zero.
    Args:
        a: coefficient for x^2
        b: coefficient for x
        c: constant term
    Returns:
        A struct named "roots" defined earlier that contains the roots of the
        quadratic equation.
    */
    roots r;
    float D;
    D = calc_discriminant(a, b, c);
    if (( D >= -1*CMPTOL ) && ( D <= CMPTOL )) {
        r.coincident = true;
        r.r1 = -b/(2*a);
        r.r2 = -b/(2*a);
    }
    else if ( D > CMPTOL ) {
        r.coincident = false;
        r.r1 = (-b + sqrt(D))/(2*a);
        r.r2 = (-b - sqrt(D))/(2*a);
    }
    else {
        cout << "Roots are complex." << endl;
        cout << "This program doesn't solve for the complex roots case" << endl;
        cout << "Code reached an unexpected code block" << endl;
        cout << "Freaking programmer messed up" << endl;
    }
    return r;
}


void display_formula(roots r, float a0, float a1)
{
    /*
    Figures out the formula for the second order linear homogeneous recurrence
    relation based on the roots of the characteristic equation and the first
    two terms of the sequence.
    Args:
        r: roots of the characteristic equation t^2 - At - B = 0
        a0: User provided first term of the sequence
        a1: User provided second term of the sequence
    Returns:
        Nothing
    */
    float C, D;

    cout << "\tFormula for the sequence: ";
    if (r.coincident) {
        C = a0;
        D = (a1 - a0*r.r1)/r.r1;
        if ( (fabs(C) > CMPTOL) && (fabs(D) > CMPTOL) ) {
            printf("a_n = %.2f (%.2f)^n + %.2f n (%.2f)^n\n", C, r.r1, D, r.r2);
        }
        else if (fabs(C) > CMPTOL) {
            printf("a_n = %.2f (%.2f)^n\n", C, r.r1);
        }
        else {
            printf("a_n = %.2f n (%.2f)^n\n", D, r.r2);
        }
    }
    else {
        C = (a0*r.r2 - a1)/(r.r2 - r.r1);
        D = (a1 - a0*r.r1)/(r.r2 - r.r1);
        if ( (fabs(C) > CMPTOL) && (fabs(D) > CMPTOL) ) {
            printf("a_n = %.2f (%.2f)^n + %.2f (%.2f)^n\n", C, r.r1, D, r.r2);
        }
        else if (fabs(C) > CMPTOL) {
            printf("a_n = %.2f (%.2f)^n\n", C, r.r1);
        }
        else {
            printf("a_n = %.2f (%.2f)^n\n", D, r.r2);
        }
    }
    display_sequence(C, D, r);
}


void display_sequence(float C, float D, roots r)
{
    /*
    Computes and display the terms of a sequence according to the formula
            a_n = C (r)^n  +  D n (r)^n     if the roots are coincident
            a_n = C (r1)^n  +  D n (r2)^n   if the roots are distinct
    Notes:
        Number of terms that are displays are set by the macro NUM_OF_TERMS
    Args:
        C: Coefficient of one of the terms in the above formula
        D: Coefficient of one of the terms in the above formula
        r: Coincident root of the characteristic equation t^2 - At - B = 0
    Returns:
        Nothing
    */
    float nth_term;

    cout << endl << "\tSequence: ";
    for ( int i = 0; i <= NUM_OF_TERMS; ++i ){
        if (r.coincident) {
            nth_term = C*pow(r.r1, i) + D*i*pow(r.r1, i);
        }
        else {
            nth_term = C*pow(r.r1, i) + D*pow(r.r2, i);
        }
        cout << nth_term << ", ";
    }
    cout << "..." << endl;
}
