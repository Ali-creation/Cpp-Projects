#include <iostream>
#include "ex1.h"
using namespace std;

int main(){
    list_t test = list_make();
	test = list_make(7, test);
	test = list_make(6, test);
	test = list_make(5, test);
	test = list_make(4, test);
	test = list_make(3, test);
	test = list_make(2, test);
	test = list_make(1, test);
    cout << "Hello, here: " << endl;    
    list_print(test);
    cout << endl;
	/*test = filter_odd(test);
	list_print(test);
    cout << endl;*/

    list_t test2 = list_make();
	test2 = list_make(1, test2);
	test2 = list_make(2, test2);
	test2 = list_make(3, test2);
	test2 = list_make(4, test2);
    list_print(test2);
    cout << endl;

    cout << "dot product: ";
    cout << dot(test, test2) << endl;


	return 0;
}