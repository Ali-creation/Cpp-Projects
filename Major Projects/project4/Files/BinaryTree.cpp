#include "BinaryTree.h"
#include <iostream>
#include <vector>

using namespace std;

/* ================================== Node =================================== */
Node::Node(const int &val, Node *left, Node *right):val(val), left(left), right(right){}
int Node::getVal() const{
    return this->val;
}
void Node::setVal(const int &newVal){
    this->val = newVal;
}
Node *Node::getLeft() const{
    return left;
}
void Node::setLeft(const int &newVal){
    if(this->left == nullptr){Node* Left = new Node(newVal);
    this->left = Left;}
    else this->left->setVal(newVal);
}
Node *Node::getRight() const{
    return right;
}
void Node::setRight(const int &newVal){
    if(this->right == nullptr){Node* Right = new Node(newVal);
    this->right = Right;}
    else this->right->setVal(newVal);
}
/* =============================== Binary Tree =============================== */
BinaryTree::BinaryTree(const int &rootValue){
    Node* Root = new Node(rootValue);
    this->root = Root;
}
BinaryTree::BinaryTree(Node *node):root(node){}

static Node* copy(Node* n){
    if(n == nullptr) return nullptr;
    Node* v = new Node(n->getVal(), copy(n->getLeft()), copy(n->getRight()));
    return v;
}

BinaryTree::BinaryTree(const BinaryTree &tree){
    if(!tree.root){ 
        this->root = nullptr;}
    else {
        this->root = copy(tree.root);}
}
BinaryTree::BinaryTree(std::vector<nodeValue> &source){
    Node* Root = createFromVariant(source, 0);
    this->root = Root;
}

static void deconstructor(Node* n){
    if(n == nullptr) return;
    deconstructor(n->getLeft());
    deconstructor(n->getRight());
    delete n;
}
BinaryTree::~BinaryTree(){
    deconstructor(root);
}
bool BinaryTree::empty() const{
    if(!root) return true;
    return false;
}
static Node* find_helper(const int& key, Node* top){
    if(!top) return nullptr;
    if(top->getVal() == key) return top;
    if(find_helper(key, top->getLeft()) != nullptr)
        return find_helper(key, top->getLeft());
    if(find_helper(key, top->getRight()) != nullptr)
        return find_helper(key, top->getRight());
    return nullptr;
}
Node *BinaryTree::find(const int &key) const{
    return find_helper(key, root);
}

static string findPath_helper(const int& value, const Node* top){
    if(!top) return "-1";
    if(top->getVal() == value) return "";
    string check = findPath_helper(value, top->getLeft());
    if(check != "-1") return "0" + check;
    string check2 = findPath_helper(value, top->getRight());
    if(check2 != "-1") return "1" + check2;
    return "-1";
}
string BinaryTree::findPath(const int &value) const{
    return findPath_helper(value, root);
}

static Node* visitThroughPath_helper(Node* top, const std::string& path){
    if(path.empty()) return top;
    if(path[0] == '0' && top->getLeft() != nullptr){
        return visitThroughPath_helper(top->getLeft(), path.substr(1));
    }
    if(path[0] == '1' && top->getRight() != nullptr){
        return visitThroughPath_helper(top->getRight(), path.substr(1));
    }
    return nullptr;
}
Node *BinaryTree::visitThroughPath(const std::string &path) const{
    return visitThroughPath_helper(root, path);
}
static int sum_helper(const Node* top){
    if(!top) return 0;
    return top->getVal() + sum_helper(top->getLeft()) + sum_helper(top->getRight());
}
int BinaryTree::sum() const{
    return sum_helper(root);
}
static int height_helper(const Node* top){
    if(!top) return 0;
    return 1 + max(height_helper(top->getLeft()), height_helper(top->getRight()));
}
int BinaryTree::height() const{
    return height_helper(root); 
}
static void preOrder_helper(const Node* top){
    if(!top) return;
    cout << top->getVal() << " ";
    preOrder_helper(top->getLeft());
    preOrder_helper(top->getRight());
}
void BinaryTree::preOrder() const{
    preOrder_helper(root);
}
static void inOrder_helper(const Node* top){
    if(!top) return;
    inOrder_helper(top->getLeft());
    cout << top->getVal() << " ";
    inOrder_helper(top->getRight());
}
void BinaryTree::inOrder() const{
    inOrder_helper(root);
}
static void postOrder_helper(const Node* top){
    if(!top) return;
    postOrder_helper(top->getLeft());
    postOrder_helper(top->getRight());
    cout << top->getVal() << " ";
}
void BinaryTree::postOrder() const{
    postOrder_helper(root);
}
static bool allPathSumGreater_helper(int sum, const Node* top){
    if(!top) return true;
    if(!top->getRight() && !top->getLeft()) return top->getVal() > sum;
    return allPathSumGreater_helper(sum-top->getVal(), top->getLeft()) && allPathSumGreater_helper(sum-top->getVal(), top->getRight());
}
bool BinaryTree::allPathSumGreater(const int &sum) const{
    if(!root) return false;
    return allPathSumGreater_helper(sum, root);
}
static bool op1_helper(const Node* target, const Node* main){
    if(!main) 
        return true;
    if(!target) 
        return false;
    return (target->getVal() == main->getVal()) && op1_helper(target->getLeft(), main->getLeft()) && op1_helper(target->getRight(), main->getRight());
}
bool BinaryTree::operator<(const BinaryTree &tree) const{
    return op1_helper(tree.root, root);
}
static bool op2_helper(const Node* target, const Node* main){
    if(op1_helper(target, main)) return true;
    if(!target)
        return false;
    return op2_helper(target->getLeft(), main) || op2_helper(target->getRight(), main);
}
bool BinaryTree::operator<<(const BinaryTree &tree) const{
    return op2_helper(tree.root, root);
}
BinaryTree &BinaryTree::operator=(const BinaryTree &tree){
    if(&tree != this){
        BinaryTree temp(tree);
        swap(temp.root, root);
    }
    return *this;
}

Node *BinaryTree::createFromVariant(const vector<nodeValue> &source, const int &rootIndex) {
    if (rootIndex >= source.size())
        return nullptr;
    auto rootValue = get_if<int>(&source[rootIndex]);
    if (!rootValue)
        return nullptr;
    int rightIndex = 2 * (rootIndex + 1);
    int leftIndex = rightIndex - 1;
    return new Node(*rootValue, createFromVariant(source, leftIndex), createFromVariant(source, rightIndex));
}