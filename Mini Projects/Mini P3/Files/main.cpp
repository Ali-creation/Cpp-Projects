#include <iostream>
#include <limits.h>
#include "ex1.h"

using namespace std;

int main(){
    int arr[] = {1,2,3,4,5,6,7,8,9,10};
    cout<<"add result: " <<fold(10,arr,fn_add,0)<<endl;
    cout<<"count odd: " <<fold(10,arr,fn_count_odd,0)<<endl;
    return 0;
}