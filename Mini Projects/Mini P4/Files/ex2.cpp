#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

const int MAXELTS = 10000;

int main(int argc, char* argv[]){
    struct BULLETS{
        string name;
        double price;
        int num;
        double perform;
    };
    
    ifstream iFile;
    iFile.open(argv[1]);
    
    BULLETS b[MAXELTS];
    iFile >> b[0].name;
    iFile >> b[0].price;
    iFile >> b[0].num;
    b[0].perform = b[0].price / b[0].num;
    double best = b[0].perform;
    int i = 1;
    while(iFile){
        iFile >> b[i].name;
        iFile >> b[i].price;
        iFile >> b[i].num;
        b[i].perform = b[i].price / b[i].num;
        if( b[i].perform < best )
            best = b[i].perform;
        ++i;
    }
    for (int j =0; j<i; j++){
        if(b[j].perform == best){
            cout << b[j].name << " " << fixed << setprecision(2) << b[j].price << " " << b[j].num << endl;
        }
    }
    iFile.close();
}