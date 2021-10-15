#include <iostream>
#include <string>
#include "binaryTree.h"
using namespace std;

void nodePrint(Node *x) {
    if (x == nullptr)
        cout << "nullptr" << endl;
    else
        cout << x->getVal() << endl;
}

int main() {
    Node* n1 = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    Node* n4 = new Node(4);
    Node* n5 = new Node(5);
    Node* n6 = new Node(6);
    Node* n7 = new Node(7);
    cout<<"done1" <<endl;
    n1->setLeft(2);
    cout<<"done2" <<endl;
    n1->setRight(3);
    cout<<"done3" <<endl;
    n2->setRight(4);
    n4->setLeft(6);
    cout<<"done5" <<endl;
    n4->setRight(7);
    n3->setRight(5);
    n1->getRight()->setRight(6);
    n1->getRight()->getRight()->setLeft(8);
    cout<<"done7" <<endl;
    BinaryTree b1(n1);
    cout<<"done8" <<endl;
    BinaryTree b2;
    cout<<"done9" <<endl;
    Node* n8 = new Node(1);
    Node* n9 = new Node(3);
    Node* n10 = new Node(5);
    Node* n11 = new Node(9);
    n8->setRight(9);
    n9->setRight(10);
    n10->setLeft(11);
    cout<<"done10" <<endl;
    BinaryTree b3(n8);
    cout<<"done11" <<endl;
    Node* n12 = new Node(1);
    Node* n13 = new Node(3);
    Node* n14 = new Node(5);
    n12->setRight(13);
    n13->setRight(14);
    cout<<"done12" <<endl;
    BinaryTree b4(n12);
    cout<<"done13" <<endl;
    Node* n15 = new Node(4);
    Node* n16 = new Node(6);
    Node* n17 = new Node(7);
    n15->setLeft(16);
    n15->setRight(17);
    BinaryTree b5(n15);
    cout<<"done14" <<endl;
    Node* n18 = new Node(4);
    Node* n19 = new Node(6);
    Node* n20 = new Node(8);
    n18->setLeft(19);
    n18->setRight(20);
    BinaryTree b6(n18);
    cout<<"done15" <<endl;
    cout<<b1.findPath(11)<<endl;
    cout<<"done16" <<endl;
    cout<<b1.findPath(3)<<endl;
    cout<<b1.findPath(10)<<endl;
    cout<<"done17" <<endl;
    cout<<b1.findPath(01)<<endl;
    cout<<b1.findPath(8)<<endl;
    cout<<b1.findPath(101)<<endl;
    cout<<b1.sum()<<endl;
    cout<<"done18" <<endl;
    cout<<b2.sum()<<endl;
    cout<<"done19" <<endl;
    cout<<b1.height()<<endl;
    cout<<b2.height()<<endl;
    cout<<"done20" <<endl;
    b1.preOrder();
    cout<<endl;
    cout<<"done21" <<endl;
    b1.inOrder();
    cout<<endl;
    cout<<"done22" <<endl;
    b1.postOrder();
    cout<<endl;
    b2.preOrder();
    b2.inOrder();
    b2.postOrder();
    cout<<endl;
    cout<<b1.allPathSumGreater(9)<<endl;
    cout<<b2.allPathSumGreater(1)<<endl;
    cout<<b1.allPathSumGreater(8)<<endl;
    cout<<b1.allPathSumGreater(1)<<endl;
    cout<<(b2<b1)<<endl;
    cout<<(b3<b1)<<endl;
    cout<<(b4<b1)<<endl;
    cout<<(b5<b1)<<endl;
    cout<<(b6<b1)<<endl;
    cout<<(b2<<b1)<<endl;
    cout<<(b3<<b1)<<endl;
    cout<<(b4<<b1)<<endl;
    cout<<(b5<<b1)<<endl;//diff 0->1(hygg)
    cout<<(b6<<b1)<<endl;
    cout<<(b2<<b2)<<endl;
    cout<<(b2<b2)<<endl;
    cout<<"find"<<endl;
    Node* x = b1.find(6);
    cout<<"Done"<<endl;
    //cout<<&x<<endl;
    nodePrint(x);
    cout << x->getVal() <<endl;
    cout<<"check"<<endl;
    cout<< x->getLeft()->getVal()<<endl;

    Node* ch = b1.visitThroughPath("01");
    //cout << ch->getVal() <<endl;
    nodePrint(ch);
    cout<<endl;
    /*cout<<b2.contained_by(b1.copy())<<endl;
    cout<<b3.contained_by(b1.copy())<<endl;
    cout<<b4.contained_by(b1.copy())<<endl;
    cout<<b5.contained_by(b1.copy())<<endl;//diff 0->1(hygg)
    cout<<b6.contained_by(b1.copy())<<endl;*/
    return 0;
}