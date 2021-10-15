#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "BinaryTree.h"
#include "NodeInfo.h"
using namespace std;

void compress(istream& input){
    BinaryTree compress = BinaryTree(0);
    string w2;
    string w = "";
    char c;
    int node_index = 0;
    while(input >> c){
        w2 = w;
        w2.push_back(c);
        if(compress.visitThroughPath(w2) != nullptr){
            w = w2;
        }
        else {
            Node* n = compress.visitThroughPath(w);
            if(c == '0'){ n->setLeft(++node_index);
            NodeInfo child(n->getVal(), '0');
            cout << child;}
            if(c == '1'){ n->setRight(++node_index);
            NodeInfo child(n->getVal(), '1');
            cout << child;}
            w = "";
        }
    }
    Node* n = compress.visitThroughPath(w);
    NodeInfo child(n->getVal(), '@');
    cout << child;

}

void decompress(istream& input){
    BinaryTree decompress = BinaryTree(0);
    int latest_node = 0;
    NodeInfo pair;
    while(input >> pair){
        Node* n = decompress.find(pair.node_index);
        if(pair.c == '0'){n->setLeft(++latest_node);
        cout << decompress.findPath(latest_node);}
        else if(pair.c == '1'){n->setRight(++latest_node);
        cout << decompress.findPath(latest_node);}
        else {cout << decompress.findPath(pair.node_index);}
    }
}

int main(int argc, char *argv[]){
    // TODO: implement your dbc program here!
    enum class Action{
        Compress, Decompress
    };
    Action choice;
    if(string(argv[1]) == "-x"){
        choice = Action::Compress;
    }
    if(string(argv[1]) == "-d"){
        //cout << "-d recognized" << endl;
        choice = Action::Decompress;
    }
    ifstream input_file(argv[2]);
    if(choice == Action::Compress){
        //cout << "compress function check" << endl;
        compress(input_file);
    }
    if(choice == Action::Decompress){
        //cout << "decompress function check" << endl;
        decompress(input_file);
    }
    return 0;
}