//
// Created by cyx on 20-6-12.
//

#include <iostream>
#include "mylist.h"

int main() {

    try{
        List<int> la, lb;
        la.insertBack(5);
        la.insertBack(4);
        la.insertBack(1);
        la.insertBack(3); // a = 3145

        lb.insertBack(2);
        lb.insertBack(4);
        lb.insertBack(1);
        lb.insertBack(3);
        lb.removeFront(); // b = 314

        std::cout << isLarger(la, lb) << '\n';

        List<int> ab_sum(la);
        std::cout << "done1"<<std::endl;
        ab_sum.print();
        std::cout << "done2"<<std::endl;
        ab_sum = add(la, lb);
        std::cout << "done3"<<std::endl;
        ab_sum.print();
        std::cout << "done4"<<std::endl;

        List<bool> lc;
        std::cout << "done5"<<std::endl;
        lc.insertBack(true);
        std::cout << "done6"<<std::endl;
        lc.insertBack(false);
        std::cout << "done7"<<std::endl;
        lc.insertBack(true);

        List<bool> ld(lc);
        std::cout << "done8"<<std::endl;
        ld.removeFront();
        std::cout << "done9"<<std::endl;
        ld.print();
        std::cout << "done10"<<std::endl;
    }
    catch(EmptyList){
        std::cout << "Remove from empty list!\n";
    }

    return 0;
}

