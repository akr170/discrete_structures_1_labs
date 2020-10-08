/*
NAME: Ashish Kumar
ASSIGNMENT: Lab 2
SOURCES: None
*/

#include <string>
#include <iostream>
using namespace std;


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


int main()
{
    string s = "11001010";
    char c = '0';
    unsigned short int b, a = 255;
    cout << "size of char: " << sizeof(char) << endl;
    cout << "size of bool: " << sizeof(bool) << endl;
    cout << "size of unsigned short int: " << sizeof(unsigned short int) << endl;
    cout << "a: " << a << endl;
    a <<= 1;
    cout << "a: " << a << endl;
    b = a & 0xFF;
    cout << "a: " << b << endl;
    cout << "c: " << c << endl;
    cout << "c: " << (int)c << endl;
    cout << "bits: " << str2bits("101") << endl;
    cout << "strs: " << bits2str(3) << endl;
    return 0;
}