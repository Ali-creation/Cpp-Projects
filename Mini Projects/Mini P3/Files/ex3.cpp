/*
 * VE280 Lab 3, SU2021.
 * Written by Yanjun Chen
 */
#include <iostream>
#include <string>
#include<string.h>

using namespace std;

const std::string help_message("Hey, I love Integers.");
const std::string add_message("This is add operation.");
const std::string small_message("This is small operation.");
const std::string no_op_message("No work to do!");

int add(const int *arr, int num){
    int sum = 0;
    for(int i=0; i<num; i++){
        sum += arr[i];
    }
    return sum;
}

int smallest(const int *arr, int num){
    int sm = arr[0];
    for(int i=1; i<num; i++){
        if(arr[i] < sm)
            sm = arr[i];
    }
    return sm;
}

int main(int argc, char *argv[]) {
	//TODO write your code here
	if (argc == 1){
        cout<< no_op_message;
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "--help") == 0){
        cout << help_message;
        return 0;
    }
    if (argc == 3 && (strcmp(argv[1],"--help") == 0 || strcmp(argv[2],"--help") ==0)){
        cout << help_message;
        return 0;
    }

    int num;
    cin >> num;
    int allNum[num];
    for(int i=0; i<num; i++){
        cin >> allNum[i];
    }

    if (argc == 2){
        if(strcmp(argv[1],"--add") == 0){
            cout << add(allNum, num);
        }
    }

    if(argc == 3){
        if(strcmp(argv[1], "--small")==0){
            int value = atoi(argv[2]);
            cout << smallest(allNum, num) + value;
        }
        if((strcmp(argv[1],"--verbose") == 0 || strcmp(argv[2],"--verbose") == 0) && (strcmp(argv[1],"--add") == 0 || strcmp(argv[2],"--add") == 0)){
            cout << add_message << endl;
            cout << add(allNum, num);
        }
    }

    if(argc == 4){
        if((strcmp(argv[1],"--verbose") == 0 || strcmp(argv[3],"--verbose") == 0) && (strcmp(argv[1],"--small") == 0 || strcmp(argv[2],"--small") == 0)){
            cout << small_message << endl;
            int value;
            if (strcmp(argv[1],"--small") == 0){
                value = atoi(argv[2]);
                cout << smallest(allNum, num) + value;
            }
            if (strcmp(argv[2],"--small") == 0){
                value = atoi(argv[3]);
                cout << smallest(allNum, num) + value;
            }
        }

        if((strcmp(argv[1],"--small") == 0 || strcmp(argv[2],"--small") == 0) && (strcmp(argv[1],"--add") == 0 || strcmp(argv[3],"--add") == 0)){
            cout << add(allNum, num) << endl;
            int value;
            if (strcmp(argv[1],"--small") == 0){
                value = atoi(argv[2]);
                cout << smallest(allNum, num) + value <<endl;
            }
            if (strcmp(argv[2],"--small") == 0){
                value = atoi(argv[3]);
                cout << smallest(allNum, num) + value;
            }
        }
    }
	return 0;
}