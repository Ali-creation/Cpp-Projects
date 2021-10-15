#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

int main(){
    string input;
    getline(cin, input);
    replace(input.begin(), input.end(), ',', ' ');
    istringstream inStream (input);
    string output;
    int count = 0;
    while(inStream >> output){
        cout << output << endl;
        count++;
    }
    cout << count;
    return 0;
}