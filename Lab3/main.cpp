/*
NAME: Ashish Kumar
ASSIGNMENT: Lab 3
SOURCES: Course instructor video, https://gmplib.org/manual/
*/

#include <gmp.h>
#include <string>
#include <iostream>
using namespace std;


void division_algorithm(mpz_t n1, mpz_t n2);
void find_gcd(mpz_t n1, mpz_t n2);


int main()
{
    //Main function
    char  num1[100], num2[100];

    cout << "Student Name: Ashish Kumar" << endl;

    cout << "Input big number x: ";
    cin >> num1;
    cout << "Input big number y: ";
    cin >> num2;
    mpz_t n1, n2;
    mpz_init(n1);
    mpz_init(n2);
    mpz_set_str(n1, num1, 10);
    mpz_set_str(n2, num2, 10);

    division_algorithm(n1, n2);
    find_gcd(n1, n2);

    mpz_clear(n1);
    mpz_clear(n2);
    return 0;
}


void division_algorithm(mpz_t n1, mpz_t n2)
{
    // Implements Algorithm 4.10.1 Division Algorithm
    mpz_t q, r, one;
    mpz_init(one);
    mpz_init(q);
    mpz_init(r);
    mpz_set_ui(q, 0);
    mpz_set_ui(one, 1);
    mpz_sub(r, n1, q);
    while(mpz_cmp(r, n2) >= 0)
    {
        mpz_sub(r, r, n2);
        mpz_add(q, q, one);
    }
    cout << endl;
    cout << "Results of division: " << endl;
    cout << "      quotient q: ";
    mpz_out_str(stdout, 10, q);
    cout << endl;
    cout << "      remainder r: ";
    mpz_out_str(stdout, 10, r);
    cout << endl << endl;
    mpz_clear(one);
    mpz_clear(q);
    mpz_clear(r);
    return;
}


void find_gcd(mpz_t n1, mpz_t n2)
{
    //Implements Algorithm 4.10.2 Euclidean Algorithm
    mpz_t r, b, zero;
    mpz_init(r);
    mpz_init(b);
    mpz_init(zero);
    mpz_set_ui(zero, 0);
    mpz_sub(r, n1, zero);
    mpz_sub(b, n2, zero);
    while(mpz_cmp(b, zero) > 0)
    {
        mpz_mod(r, r, b);
        mpz_swap(b, r);
    }
    cout << "GCD: ";
    mpz_out_str(stdout, 10, r);
    cout << endl << endl;
    mpz_clear(r);
    mpz_clear(b);
    mpz_clear(zero);
}
