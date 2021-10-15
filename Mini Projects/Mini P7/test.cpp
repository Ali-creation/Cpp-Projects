#include <iostream>
#include "node.h"


///using namespace std;

int main(){
    cout << "Initialization:" << endl; 
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
    cout << "Traverse:" << endl;
    root.traverse(result);

    cout << "Printing: " << endl;
    for(int x : result)
        cout << x << " ";
    cout << endl;

    cout << "Height: " << root.getHeight() << endl;

    Node A = Node(4,2);
    A.addChild(5);
    A.addChild(7);
    A[0].addChild(6);
    A[1].addChild(8);
    vector<int> result2;
    cout << "Traverse A:" << endl;
    A.traverse(result2);
    cout << "Printing A: " << endl;
    for(int x : result2)
        cout << x << " ";
    cout << endl;

    Node B = Node(1,2);
    B.addChild(2);

    Node C = Node(4,2);
    C.addChild(5);
    C.addChild(7);

    Node D = Node(5,2);
    D.addChild(6);

    Node E = Node(13,2);
    E.addChild(9);

    Node F = Node(4,2);
    F.addChild(5);
    F.addChild(7);
    F[0].addChild(6);
    F[1].addChild(13);

    cout << "root contains A: " << root.contain(&A) << endl;
    cout << "root contains B: " << root.contain(&B) << endl;
    cout << "root contains C: " << root.contain(&C) << endl;
    cout << "root contains D: " << root.contain(&D) << endl;
    cout << "root contains E: " << root.contain(&E) << endl;
    cout << "root contains F: " << root.contain(&F) << endl;
    
    return 0;
}