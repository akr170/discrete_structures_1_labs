/*
NAME: Ashish Kumar
ASSIGNMENT: Lab 1
SOURCES: None
*/

#include <iostream>
using namespace std;


bool evl_cond(bool a, bool b)
{
    /*
    This function helps evaluate the conditional A --> B.

    Args:
        a: a boolean T/F value denoting A
        b: a boolean T/F value denoting B

    Returns:
        A --> B 
    */
    bool ret;
    ret = !a || b;
    return ret;
}


bool evl_bidir(bool a, bool b)
{
    /*
    This function helps evaluate the bidirectional conditional A <--> B.

    Args:
        a: a boolean T/F value denoting A
        b: a boolean T/F value denoting B

    Returns:
        A <--> B 
    */
    bool ret;
    ret = evl_cond(a, b) && evl_cond(b, a);
    return ret;
}


bool evl_prems(bool p, bool q, bool r)
{
    /*
    This function helps evaluate the following premise given in Lab 1
    (P v Q -> R) ^ (~Q <=> P) ^ ((~R v Q) XOR P)

    Args:
        p: a boolean T/F value denoting a P value
        q: a boolean T/F value denoting a Q value
        r: a boolean T/F value denoting an R value

    Returns:
        The T/F boolean result of the premise.
    */
    bool premise;
    // PREMISE EVALUATED HERE.
    // Please change the line below to change premise.
    premise = evl_cond(p || q, r) && evl_bidir(!q, p) && ((!r || q) ^ p);
    // End of premise evaluation
    return premise;
}


bool evl_concl(bool p, bool q, bool r)
{
    /*
    This function helps evaluate the conclusion given in Lab 1: (~Q ^ R)

    Args:
        p: a boolean T/F value denoting a P value (unused)
        q: a boolean T/F value denoting a Q value
        r: a boolean T/F value denoting an R value

    Returns:
        The T/F boolean result of the conclusion.
    */
    bool concl;
    // CONCLUSION EVALUATED HERE.
    // Please change the line below to change conclusion.
    concl = !q && r;
    // End of conclusion evaluation
    return concl;
}


char b2c(bool a)
{
    /*
    Converts the C++ boolean true/false result in the 'T' or 'F' character to be
    so that it could be displayed in expected format on the screen.

    Args:
        a: a boolean T/F
    
    Returns:
        'T' if a == true, returns 'F' otherwise.
    */
    char ret = 'F';
    if (a) ret = 'T';
    return ret;
}


void disp_truth_table(bool * p, bool * q, bool * r, bool * prem, bool * conc)
{
    /*
    Formats the result into a table and displays it on the screen.

    Args:
        p: an array of boolean T/F values denoting entries of P in truth table
        q: an array of boolean T/F values denoting entries of Q in truth table
        r: an array of boolean T/F values denoting entries of R in truth table
        prem: an array of evaluated T/F premise values in truth table  
        conc: an array of evaluated T/F conclusion values in truth table
    
    Returns:
        None
    */
    cout << "Row\tP\tQ\tR\tPrem\tConcl" << endl;
    for ( int i = 0; i < 8; ++i ){
        printf("%d\t%c\t%c\t%c\t%c\t%c\n", i, b2c(p[i]), b2c(q[i]),
            b2c(r[i]), b2c(prem[i]), b2c(conc[i]));
    }
}


void test_validity(bool * prem, bool * conc)
{
    /*
    Tests validity of overall argument by comparing premise & conclusion values.
    If the argument is invalid, displays the row in which the argument is
    invalid.  If the argument is valid, displays the string "The argument is 
    valid."

    Args:
        prem: an array of evaluated T/F premise values in truth table  
        conc: an array of evaluated T/F conclusion values in truth table
    
    Returns:
        None
    */
    bool valid_flag = true;
    for ( int i = 0; i < 8; ++i ){
        if ((prem[i]) && (!conc[i])){
            printf("The argument is invalid in row %d\n", i);
            valid_flag = false;
        }
    }
    if (valid_flag) cout << "The argument is valid." << endl;
}


int main() {
    /*
    Main function
    */
    bool value[] = { true, false };
    bool p[8], q[8], r[8];
    bool prem[8], conc[8];
    int row = 0;
    
    cout << "Student Name: Ashish Kumar" << endl;
    
    for( int i = 0; i < 2; ++i ){
        for ( int j = 0; j < 2; ++j ){
            for ( int k = 0; k < 2; ++k ){
                p[row] = value[i];
                q[row] = value[j];
                r[row] = value[k];
                prem[row] = evl_prems(p[row], q[row], r[row]);
                conc[row] = evl_concl(p[row], q[row], r[row]);
                ++row;
            }
        }
    }
    test_validity(prem, conc);
    disp_truth_table(p, q, r, prem, conc);
    return 0;
}
