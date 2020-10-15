/*
NAME: Ashish Kumar
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


void str2bin(string num, bool * bin)
{
    /*
    Takes in a user provided string representing an 8 bit binary number and
    stores individual characters of that string in a boolean array.
    
    Notes:
        The bits are stored in the boolean array in such as way that the 0th
        element represents the least significant bit.
    
    Args:
        num: a user provided string representing an 8-bit binary number
        bin: an boolean array that is used for storing the 8-bits from num
    
    Returns:
        None
    */
    int ptr = 0;

    for ( int i = ((int)num.size() - 1); i >= 0; --i ){
        if ((int)num[i] == 48){
            *(bin + ptr) = 0;
        } else {
            *(bin + ptr) = 1;
        }
        ++ptr;
    }
}


string reverse_string(string num)
{
    /*
    Takes in a string and returns the reversed string.

    Notes:
        1010 1000 will become 0001 0101
    
    Args:
        num: a string
    
    Returns:
        The reversed string
    */
    string ret = "";
    for ( int i = ((int)num.size() - 1); i >= 0; --i ){
        ret.push_back(num[i]);
    }
    return ret;
}


string formatbinstring(string num)
{
    /*
    Takes in a string and adds spaces after every 4th character starting from
    the right most character going towards the left most character.

    Notes:
        if input is 00101111, the return will be 0010 1111

    Args:
        num: a string
    
    Returns:
        string with a space added after every 4th character starting from left.
    */
    string temp = "";
    string ret;
    int counter = 0;
    for ( int i = ((int)num.size() - 1); i >= 0; --i ){
        if ((counter % 4 == 0) && (counter != 0)) {
            temp.append(" ");
        }
        temp.push_back(num[i]);
        ++counter;
    }
    ret = reverse_string(temp);
    return ret;
}


string bin2str(bool * num, int arr_size=9)
{
    /*
    Takes in a boolean array representing a binary number and converts it to a
    string.

    Notes:
        If the input is { 1, 0, 1, 1, 0, 1, 0, 0, 0 }, the return string will be
        "0010 1101"
        If the input is { 1, 0, 1, 1, 0, 1, 0, 0, 1 }, the return string will be
        "1 0010 1101"
    
    Args:
        num: a boolean array with elements representing bits of a binary number
        arr_size: size of the 'num' array
    
    Returns:
        binary number converted to string and formatted according to the
        CS250 guidelines
    */
    bool significant_flag = false;
    string ret = "";

    for ( int i = (arr_size - 1); i >= 0; --i ){
        if (significant_flag || num[i]){
            if (num[i]) {
                ret.push_back('1');
            } else {
                ret.push_back('0');
            }
        }
        significant_flag = true;
    }
    ret = formatbinstring(ret);
    return ret;
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
    bool bin1[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    bool bin2[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    bool result[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    bool carry_in = 0;
    adret adder_ret;

    str2bin(str_bin1, bin1); //store str_bin1 characters into boolean array bin1
    str2bin(str_bin2, bin2); //store str_bin1 characters into boolean array bin2
    cout << "The numbers to be added are " << bin2str(bin1) << " and "
        << bin2str(bin2) << endl;

    for ( int i = 0; i < 8; ++i ){
        // add binary numbers bit by bit
        adder_ret = full_adder(*(bin1 + i), *(bin2 + i), carry_in);
        carry_in = adder_ret.carry;
        result[i] = adder_ret.sum; //store the sum bit in the results
    }
    result[8] = adder_ret.carry; //append the last carry to the 9th position

    str_ret = bin2str(result); //covert the result to properly formatted string
    return str_ret;
}


int main()
{
    /*
    Main function
    */
    string bin1, bin2, sum;
    bool check1, check2;
    
    cout << "Student Name: Ashish Kumar" << endl;

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
