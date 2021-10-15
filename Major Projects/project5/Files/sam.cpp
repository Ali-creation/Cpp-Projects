#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cassert>
#include "Dlist.h"
#include "Instr.h"

using namespace std;

template<class T>
class Stack{
    Dlist<T> stDlist;
    public:
        bool isEmpty() const;
        void push(T* item);
        T* pop(); 

        void Print_Stack();
};

template<class T>
bool Stack<T>::isEmpty() const{
    return stDlist.isEmpty();
}

template<class T>
void Stack<T>::push(T* item){
    stDlist.insertFront(item);
}

template<class T>
T* Stack<T>::pop(){
    return stDlist.removeFront();
}

template<class T>
void Stack<T>::Print_Stack(){
    if (stDlist.isEmpty())
        return;
    int* x = stDlist.removeFront();
    this->Print_Stack();
    cout << *x << " ";
    stDlist.insertFront(x);
}


template<class T>
class Queue{
    Dlist<T> qDlist;
    public:
        bool isEmpty() const;
        void pushF(T* item);
        void pushB(T* item);
        T* pop();

        //void Load_Queue(int i);
        void Print_Queue();
};

template<class T>
bool Queue<T>::isEmpty() const{
    return qDlist.isEmpty();
}

template<class T>
void Queue<T>::pushF(T* item){
    qDlist.insertFront(item);
}

template<class T>
void Queue<T>::pushB(T* item){
    qDlist.insertBack(item);
}

template<class T>
T* Queue<T>::pop(){
    return qDlist.removeFront();
}

template<class T>
void Queue<T>::Print_Queue(){
    if (qDlist.isEmpty())
        return;
    Instr* x = qDlist.removeFront();
    cout << *x << " ";
    this->Print_Queue();
    //Instr* iX = new Instr(*x);
    qDlist.insertFront(x);
}

/*template<class T>
void Queue<T>::Load_Queue(int i){
    if (i == 0) return;
    Instr ins;
    cin >> ins;
    i--;
    this->Load_Queue(i);
    Instr* insrr = &ins;
    qDlist.insertFront(insrr);
}*/


template <class T>
constexpr T NOR(T lhs, T rhs) noexcept { 
    return ~(lhs | rhs); 
}


int main(int argc, char *argv[])
{
    //TODO:write your code here.
    enum class Action{
        InsOutput, NoInsOutput
    };
    Action choice;
    if(argc == 2 && string(argv[1]) == "-s"){
        choice = Action::NoInsOutput;
    }
    else{
        choice = Action::InsOutput;
    }

    int stackNum, queueNum;
    string line;
    getline(cin, line);
    istringstream inStream (line);
    inStream >> stackNum >> queueNum;

    getline(cin, line);
    istringstream inStream2(line);
    Stack<int> stack;
    for(int i = 0; i<stackNum; i++){
        int pushNum;
        inStream2 >> pushNum;
        int *ic = new int(pushNum);
        stack.push(ic);
    }
    Queue<Instr> queue;
    for(int i=0; i<queueNum; i++){
        Instr ins;
        cin >> ins;
        Instr *ip = new Instr(ins);
        queue.pushB(ip);
    }
    
    int mem[16];
    for(int i=0; i<16; i++){
        cin >> mem[i];
    }

    while(!queue.isEmpty()){
        Instr* ins = queue.pop();
        switch(ins->name) {
            case InstrName::ADD:
                {int* num1 = stack.pop();
                int* num2 = stack.pop();
                int sum = *num1 + *num2;
                int *is = new int(sum);
                stack.push(is);
                delete num1;
                delete num2;
                break;}
            case InstrName::NOR:
                {int* num1 = stack.pop();
                int* num2 = stack.pop();
                int res = NOR(*num1, *num2);
                int *ir = new int(res);
                stack.push(ir);
                delete num1;
                delete num2;
                break;}
            case InstrName::IFZ:
                {int* num1 = stack.pop();
                int n = 0;
                if(*num1 == 0) n = ins->parameter;
                for(int i=0; i<n; i++){
                    Instr* ig = queue.pop();
                    delete ig;
                }
                delete num1;
                break;}
            case InstrName::HALT:
                {
                if(choice == Action::InsOutput){
                    cout << *ins << endl;
                    stack.Print_Stack();
                    cout << endl;
                    queue.Print_Queue();
                    cout << endl;
                    for(int i=0; i<16; i++){
                        cout << mem[i] << " ";
                    }
                    cout << endl;
                }
                else{
                    stack.Print_Stack();
                    cout << endl;
                    for(int i=0; i<16; i++){
                        cout << mem[i] << " ";
                    }
                    cout << endl;
                }
                delete ins;
                return 0;
                break;}
            case InstrName::LOAD:
                {int* num1 = stack.pop();
                int* il = new int(mem[*num1]);
                stack.push(il);
                delete num1;
                
                break;}
            case InstrName::STORE:
                {int* num1 = stack.pop();
                int* num2 = stack.pop();
                mem[*num1] = *num2;
                delete num1;
                delete num2;
                break;}
            case InstrName::POP:
                {int* num1 = stack.pop();
                delete num1;
                
                break;}
            case InstrName::PUSHI:
                {int* iP = new int(ins->parameter);
                stack.push(iP);
                break;}
            case InstrName::NOOP:
                {break;}
            }
        if(choice == Action::InsOutput){
            cout << *ins << endl;
            stack.Print_Stack();
            cout << endl;
            queue.Print_Queue();
            cout << endl;
            for(int i=0; i<16; i++){
                cout << mem[i] << " ";
            }
            cout << endl;
        }
        delete ins;
    }
    return 0;
}