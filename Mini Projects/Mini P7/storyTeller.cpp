#include <iostream>
#include "node.h"
#include "constant.h"

int main(){
    Node root = Node(0, 2);
    root.addChild(1);
    root.addChild(3);
    root[0].addChild(2);
    root[1].addChild(4);
    root[1][0].addChild(5);
    root[1][0].addChild(7);
    root[1][0][0].addChild(6);
    root[1][0][1].addChild(8);
    root[1][0][1].addChild(9);
    root[1][0][1][1].addChild(10);
    
    vector<int> result;
    root.traverse(result);

    for(int x : result)
        cout << storyProcess[x];
    
    return 0;
}