#include <gmp.h>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    char  num1[40];
    char  num2[40] = "789";
    /* get num1 */
    cout << "Input your first big number, please" << endl;
    cin >> num1;
    
    /* declare & initialize the 3 big numbers */
    mpz_t n1, n2, answer;
    mpz_init(n1);
    mpz_init(n2);
    mpz_init(answer);
    /* n1 and n2 assigned values from the strings */

    mpz_set_str(n1,num1, 10);
    cout << "big number1 is  ";
    mpz_out_str(stdout, 10, n1); // this is how to print the number
    cout <<  endl;
    mpz_set_str(n2,num2, 10);
    cout << "big number2 is  ";
    mpz_out_str(stdout, 10,n2);
    cout << endl;
    cout << "comparisons: " << mpz_cmp(n1, n2) << endl;
    cout << "comparisons: " << mpz_cmp(n2, n1) << endl;
    cout << "comparisons: " << mpz_cmp(n1, n1) << endl;
        
    /* subtract the numbers */
    mpz_sub(answer, n1, n2);
    cout << "answer is ";
    mpz_out_str(stdout, 10, answer);
    cout << endl;
    
    /*  clear all the big numbers  */
    mpz_clear(n1);
    mpz_clear(n2);
    mpz_clear(answer);
    return 0;

}