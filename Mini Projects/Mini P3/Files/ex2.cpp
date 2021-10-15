/*
 * VE280 Lab 3, SU2021.
 * Written by Guoxin Yin
 */

#include <iostream>

using namespace std;

const int MAXSIZE = 10;

bool p_check(int i, int p_keep[], int Nposition){
    for (int j=0; j<i; j++){
        if (p_keep[j] == Nposition)
            return false;
    }
    return true;
}

bool canWin_helper(int count, int arr[], int position, int i, int p_keep[]){
    if( arr[position] == 280 )
        return true;
    p_keep[i] = position;
    i++;
    if( position + arr[position] <count && p_check(i, p_keep, position + arr[position])){
        return canWin_helper(count, arr, position + arr[position], i, p_keep);
    }
    else if( position - arr[position]>0 && position - arr[position] <count && p_check(i, p_keep, position - arr[position])){
        return canWin_helper(count, arr, position - arr[position], i, p_keep);
    }
    return false;
}

bool canWin(int count, int arr[], int position) {
    // EFFECTS: return whether the player can win given the start position
    // and the card sequence
    // TODO: implement this function
    int i=0;
    int p_keep[count];
    return canWin_helper(count, arr, position, i, p_keep); 
}

int main() {
    int count;
    cin >> count;
    int arr[MAXSIZE];
    for (int i = 0; i < count; ++i) {
        cin >> arr[i];
    }
    int position;
    cin >> position;
    cout << canWin(count, arr, position);
}