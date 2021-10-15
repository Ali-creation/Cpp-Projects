/*
 * This is an exercise of VE280 Lab 1, SU2020.
 * Written by Martin Ma.
 * Latest Update: 5/10/2020.
 * Copyright © 2020 Mars-tin. All rights reserved.
 */

#include <iostream>
using namespace std;


// EFFECTS: return true if the password is a valid one
bool isValidPassword(char password[]){
    bool alphabet = 0, numeric = 0, non_alphabet = 0;
    for (int i=0; i<50; i++){
        if ((password[i]>=65 && password[i]<=90) || (password[i]>=97 && password[i]<=122)){
            alphabet = 1;}
        else if ((password[i]>=32 && password[i]<=47) || (password[i]>=58 && password[i]<=64) || (password[i]>=91 && password[i]<=96) || (password[i]>=123 && password[i]<=126)){
            non_alphabet = 1;}
        else if  (password[i]>=48 && password[i]<=57){
            numeric = 1;}
    }
    if (alphabet && non_alphabet && numeric){
        return 1;
    }
    else
        return 0;
}


int main(){
    char password[50] = {};
    cin >> password;
    cout << isValidPassword(password) << endl;
}
