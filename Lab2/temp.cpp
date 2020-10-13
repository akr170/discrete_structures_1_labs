/*
NAME: Dakota Bloom
ASSIGNMENT: Lab 2
SOURCES: None
*/

#include <string>
#include <iostream>
using namespace std;


struct adret
{
    /*
    Defining a struct to hold the results of half adder and full adder functions
    */
    bool sum;
    bool carry;
};


bool and_gate(bool p, bool q)
{
    /*
    Takes in two booleans that represent individual bits and returs their AND

    Args:
        p: a boolean representing a bit
        q: a boolean representing a bit
    
    Returns:
        p AND q
    */
    bool ret;
    ret = p & q;
    return ret;
}


bool or_gate(bool p, bool q)
{
    /*
    Takes in two booleans that represent individual bits and returs their OR

    Args:
        p: a boolean representing a bit
        q: a boolean representing a bit
    
    Returns:
        p OR q
    */
    bool ret;
    ret = p | q;
    return ret;
}


bool not_gate(bool p)
{
    /*
    Takes in a boolean that represents a bit and returs its NOT

    Args:
        p: a boolean representing a bit
    
    Returns:
        NOT p
    */
    bool ret;
    ret = !p;
    return ret;
}


adret half_adder(bool p, bool q)
{
    /*
    Implements the half adder circuitry.

    Notes:
        Takes in two booleans p and q representing bits and performs half adder
        addition ot those bits. Returns the sum and carry of p + q.

    Args:
        p: a boolean representing a bit
        q: a boolean representing a bit
    
    Returns:
        sum and carry after performing p + q
    */
    adret ret_val;
    bool p_or_q, p_and_q;
    p_and_q = and_gate(p, q);
    p_or_q = or_gate(p, q);
    ret_val.sum = and_gate(not_gate(p_and_q), p_or_q);
    ret_val.carry = p_and_q;
    return ret_val;
}


adret full_adder(bool p, bool q, bool carry_in)
{
    /*
    Implements the full adder circuitry.

    Notes:
        Takes in three booleans p, q, and a carry-in representing bits and
        performs a full adder addition ot those bits. Returns the sum and carry
        of p + q + carry-in.

    Args:
        p: a boolean representing a bit
        q: a boolean representing a bit
        carry_in: a boolean representing a bit
    
    Returns:
        sum and carry after performing p + q + carry_in
    */
    adret ret_val, result1, result2;
    bool sum1, carry1;
    result1 = half_adder(p, q);
    sum1 = result1.sum;
    carry1 = result1.carry;
    result2 = half_adder(sum1, carry_in);
    ret_val.sum = result2.sum;
    ret_val.carry = or_gate(carry1, result2.carry);
    printf("The bits are %d and %d.  ", p, q);
    printf("The carry in is %d.  ", carry_in);
    printf("The sum is %d.  ", ret_val.sum);
    printf("The carry out is %d.\n", ret_val.carry);
    return ret_val;
}


string bits2str(unsigned short int num_copy)
{
    unsigned short int num, counter = 0;
    string temp, str = "";

    num = num_copy;
    for ( int i = 0; i < 8; ++i ){
        if (counter == 4){
            temp = " ";
            str = temp.append(str);
        }
        if ((num & 0x01) == 0){
            temp = "0";
        } else {
            temp = "1";
        }
        str = temp.append(str);
        num >>= 1;
        ++counter;
    }
    if ((num & 0x01) == 1) {
        temp = "1 ";
        str = temp.append(str);
    }
    return str;
}


unsigned short int str2bits(string s)
{
    unsigned short int num = 0;
    for ( int i = 0; i < s.size(); i++ ){
        num <<= 1;
        if ((int)s[i] == 49) {
            num = num | 0x01;
        }
    }
    return num;
}


bool check_if_binary_number(string num)
{
    /*
    Checks to make sure that the user input received is an 8-bit binary number.

    Notes:
        Following are the checks performed:
        1. The length of the user provided string is less than or equal to 8.
        2. The individual characters in the string are none other than 0 or 1.
    
    Args:
        num: a string representing the binary number

    Returns:
        true if the input string passes all checks, false otherwise.
    */
    bool check = true;
    if (num.size() > 8){
        check = false;
    }
    for ( int i = 0; i < (int)num.size(); ++i ){
        if (!(((int)num[i] == 48) || ((int)num[i] == 49))) {
            check = false;
        };
    }
    if (!check) {
        cout << num << " is not an 8-bit binary number." << endl;
    }
    return check;
}


string add_binary_nums(string str_bin1, string str_bin2)
{
    /*
    Takes in two user provided strings representing 8-bit binary numbers and
    performs their bit by bit addition using full adder.

    Args:
        str_bin1: a user provided string representing an 8-bin binary number
        str_bin2: a user provided string representing an 8-bin binary number
    
    Returns:
        A string representing the sum of two user provided binary numbers
    */
    string str_ret;
    int bin1, bin2, result = 0;
    bool carry_in = 0;
    adret adder_ret;

    bin1 = str2bits(str_bin1);
    bin2 = str2bits(str_bin2);
    cout << "The numbers to be added are " << bits2str(bin1) << " and "
        << bits2str(bin2) << endl;

    for ( int i = 0; i < 8; ++i ){
        // add binary numbers bit by bit
        adder_ret = full_adder(bin1 & 0x01, bin2 & 0x01, carry_in);
        carry_in = adder_ret.carry;
        result = result | (adder_ret.sum << i); //store the sum in the results
        bin1 >>= 1;
        bin2 >>= 1;
    }
    result = result | (adder_ret.carry << 8);
    str_ret = bits2str(result); //covert the result to properly formatted string
    return str_ret;
}


int main()
{
    /*
    Main function
    */
    string bin1, bin2, sum;
    bool check1, check2;
    
    cout << "Student Name: Dakota Bloom" << endl;

    for ( int i = 0; i < 4; ++i){
        cout << endl;
        cout << "Enter 1st 8-bit binary number: ";
        cin >> bin1;
        cout << "Enter 2nd 8-bit binary number: ";
        cin >> bin2;
        cout << endl;
        check1 = check_if_binary_number(bin1);
        check2 = check_if_binary_number(bin2);
        if (check1 && check2){
            sum = add_binary_nums(bin1, bin2);
            cout << "The answer is " << sum << endl;
        }
    }
    return 0;
}
