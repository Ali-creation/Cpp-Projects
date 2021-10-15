//
// Created by Zhuoer Zhu on 10/06/2020.
// Updated by Yanjun Chen on 16/06/2021.
//

#include "factoredForm.h"

QuadraticFunction::QuadraticFunction(float a_in, float b_in, float c_in):a(a_in){
    int delta = (b_in/a_in)*(b_in/a_in) - 4*(c_in/a_in);
    if(delta > 0){
        float x1 = (-(b_in/a_in) + sqrt(delta)) /2;
        r1.imaginary = 0;
        float x2 = (-(b_in/a_in) - sqrt(delta)) /2;
        r2.imaginary = 0;
        if(x2>x1){
            r1.real = x1;
            r2.real = x2;
        }
        else{
            r1.real = x2;
            r2.real = x1;
        }
    }
    else if(delta == 0){
        r1.real = -(b_in/a_in)/2;
        r1.imaginary = 0;
        r2.real = -(b_in/a_in)/2;
        r2.imaginary = 0;
    }
    else{
        float realPart = -(b_in/a_in)/2;
        float imaginaryPart =sqrt(-delta)/2;
        r1.real = realPart;
        r1.imaginary = - imaginaryPart;
        r2.real = realPart;
        r2.imaginary = imaginaryPart;
    }
}
// TODO: implement this constructor

float QuadraticFunction::getA() const {
    return a;
}

float QuadraticFunction::getB() const {
    // TODO: implement this function
    return a*(-1)*(r1.real + r2.real);
}

float QuadraticFunction::getC() const {
    // TODO: implement this function
    return a*(r1.real*r2.real-r1.imaginary*r2.imaginary);
}

float QuadraticFunction::evaluate(float x) {
    // TODO: implement this function
    return getA()*x*x+getB()*x+getC();//f(x) = ax^2 + bx + c
}

Root QuadraticFunction::getRoot() {
    // TODO: implement this function
    Root result;
    if(r1.imaginary == 0 && r1.real != r2.real)
        result.realRootNum = 2;
    else if(r2.imaginary == 0 && r1.real == r2.real)
        result.realRootNum = 1;
    else
        result.realRootNum = 0;
    result.roots[0] = r1;
    result.roots[1] = r2;
    return result;
}

bool QuadraticFunction::intersect(QuadraticFunction q) {
    // TODO: implement this function
    QuadraticFunction k(this->getA()-q.getA(), this->getB()-q.getB(), this->getC()-q.getC());

    if(k.getA() == 0 && k.getB() == 0 && k.getC() != 0)
        return false;
    if(k.getA() == 0 && k.getB() == 0 && k.getC() == 0)
        return true;
    if(k.getA() == 0 && k.getB() != 0)
        return true;
    Root rc = k.getRoot();
    if(rc.realRootNum == 2 || rc.realRootNum == 1)
        return true;
    else
        return false;
}