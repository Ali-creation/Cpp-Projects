#include <iostream>
#include "node.h"


void Node::addChild(Node *child) {
    if(this->child_num >= n)
        throw tooManyChildren();
    this->children[child_num++] = child;
    child->parent = this;
    if(this-> height < (child->height+1)){
        this->height = (child->height+1);
        int heightNew = this->height+1;
        Node*  nodeNew = this->parent;
        while(nodeNew != nullptr){
            if( nodeNew->height <heightNew)
                nodeNew->height = heightNew;
            heightNew++;
            nodeNew = nodeNew->parent;
        }
    }

}

Node::Node(int _value, int _n) {
    //cout << "Constructor start" << endl;
    this->value = _value;
    //cout <<"Value: "<< value << endl;
    this-> child_num =0;
    this->n = _n;
    this->parent = nullptr;
    this->height =0;
    
    children = (new Node* [this->n]);
    for(int i =0; i< n ; i++){
        children[i] = nullptr;
        //cout << "Children Null" <<endl;
    }
    //cout << "constructor Done" << endl;
}

Node::~Node() {
    for(int i=0; i< this->child_num; i++){
        delete children[i];
    }
    delete[] children;
}

void Node::addChild(int _value) {
    if(child_num >= n)
        throw tooManyChildren();
    Node *child = new Node(_value, this->n);
    //cout << "before going to Child" << endl;
    addChild(child);
}

void Node::traverse(vector<int>& traverseValue) {
    //cout << "We enter traverse here: "<<endl;
    traverseValue.push_back(this->value);
    //cout << "Push back success"<<endl;
    if(this->child_num == 0)
        return;
    for(int i=0; i<this->child_num; i++){
        children[i]->traverse(traverseValue);
    }
}

int Node::getHeight() {
    return this->height;
}

bool Node::equal(Node *sub){
    if(sub == NULL)
        return false;
    if(this->value == sub->value){
        //cout<<"if is done"<<endl;
        if(sub->child_num != 0){
            for (int i=0; i<this->child_num; i++){
                //cout << "loop start" <<endl;
                if (!this->children[i]->equal(sub->children[i]))
                    return false;
                else{
                    continue;
                } 
            }
            return true;
        }
        else{
            //cout << " true " << endl;
            return true;}
    }
    return false;
    
}

bool Node::contain(Node *sub) {
    if(sub == NULL){
        //cout << "NULL reached" <<endl;
        return true;
    }
    if(this->value == sub->value){
        //cout <<"enter if1"<<endl;
        for(int i = 0; i< this->child_num; i++){
            //cout << "loop1"<<endl;
            if(!this->children[i]->contain(sub->children[i])){
                //cout << "yes"<<endl;
                //cnt++;
                return false;}
            else{
                //cout << "No" <<endl;
                continue;
            }
        }
        //cout << "ans_1: "<<ans<<endl;
        return true;
    }
    else{
        //cout <<"enter else"<<endl;
        for(int i = 0; i< this->child_num; i++){
            if(children[i]->contain(sub))
                return true;
            }    
    }
    //cout << "arrived end" <<endl;
    return false;
}

Node& Node::operator[](int i) {
    if (i >= this->child_num)
        throw invalidIndex();
    return *this->children[i];
}