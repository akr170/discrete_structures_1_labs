/*
NAME: Ashish Kumar
ASSIGNMENT: Lab 3
SOURCES: hackerearth.com
*/

#include <string>
#include <iostream>
using namespace std;


int calc_min_num_of_moves(int k);
void move_disk(int num_of_disks, char from, char to, char aux);


int main()
{
    //Main function
    int  num_of_disks = 0;

    cout << "Student Name: Ashish Kumar" << endl;

    while (num_of_disks <= 0){
        cout << "Enter number of disks between 1 and " << INT8_MAX << ": ";
        cin >> num_of_disks;
        if (num_of_disks <= 0){
            cout << "Number of disks cannot be " << num_of_disks << endl;
        }
    }

    cout << endl;

    if (num_of_disks % 2 == 0){
        move_disk(num_of_disks, '1', '2', '3');
    }
    else{
        move_disk(num_of_disks, '1', '3', '2');
    }

    cout << endl;

    return 0;
}


void move_disk(int num_of_disks, char from, char to, char aux)
{
    /*
    Function that is recursively called to move disks

    Args:
        num_of_disks: Number of disks that need to be moved
        from: Tower from which the disks need to be moved
        to: Tower to which the disks need to be moved
        aux: The spare tower
    
    Returns:
        None
    */
    if (num_of_disks == 1){
        cout << "moved disk from " << from << " to " << to << endl;
    }
    else {
        move_disk((num_of_disks-1), from, aux, to);
        cout << "moved disk from " << from << " to " << to << endl;
        move_disk((num_of_disks-1), aux, to, from);
    }
}
