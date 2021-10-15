#include <iostream>
#include "Dlist.h"
using namespace std;

int main(int argc, char *argv[])
{
    int result = 0;
    cout << "done1" <<endl;
    Dlist<int> ilist;
    int *ip = new int(1);
    cout << "done2" <<endl;
    ilist.insertBack(ip);
    cout << "done3" <<endl;
    int *ip1 = new int(2);
    ilist.insertBack(ip1);
    int *ip2 = new int(3);
    ilist.insertBack(ip2);
    int *ip3 = new int(4);
    ilist.insertBack(ip3);
    int *ip4 = new int(5);
    ilist.insertBack(ip4);

    /*while(!ilist.isEmpty()){
        cout << *ilist.removeBack() << endl;
    }*/

    ip = ilist.removeFront();
    cout << "done4" <<endl;
    if(*ip != 1)
        result = -1;
    cout << "done5" <<endl;
    //delete ip;
    cout << "done6" <<endl;
    if(!ilist.isEmpty())
        result = -1;
    cout << "done7" <<endl;
    cout << "result: " << result;
    return result;
}
