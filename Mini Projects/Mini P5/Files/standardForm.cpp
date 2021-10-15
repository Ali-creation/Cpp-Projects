//
// Created by Zhuoer Zhu on 10/06/2020.
// Updated by Yanjun Chen on 16/06/2021.
//

#include <cmath>
#include "standardForm.h"

QuadraticFunction::QuadraticFunction(float a_in, float b_in, float c_in):a(a_in),b(b_in),c(c_in){}
// TODO: implement this constructor

float QuadraticFunction::getA() const {
    return a;
}

float QuadraticFunction::getB() const {
    return b;
}

float QuadraticFunction::getC() const {
    return c;
}

float QuadraticFunction::evaluate(float x) {
    // TODO: implement this function
    return a*x*x+b*x+c;
}

Root QuadraticFunction::getRoot() {
    // TODO: implement this function
    Root results;
    int delta = b*b - 4*a*c;
    if(delta > 0){
        results.realRootNum = 2;
        float x1 = (-b + sqrt(delta)) / (2*a);
        float x2 = (-b - sqrt(delta)) / (2*a);
        if(x2>x1){
            results.roots[0].real = x1;
            results.roots[0].imaginary = 0;
            results.roots[1].real = x2;
            results.roots[1].imaginary = 0;
        }
        else{
            results.roots[0].real = x2;
            results.roots[0].imaginary = 0;
            results.roots[1].real = x1;
            results.roots[1].imaginary = 0;
        }
    }
    else if(delta == 0){
        results.realRootNum = 1;
        results.roots[0].real = -b/(2*a);
        results.roots[0].imaginary = 0;
        results.roots[1].real = -b/(2*a);
        results.roots[1].imaginary = 0;
    }
    else{
        results.realRootNum = 0;
        float realPart = -b/(2*a);
        float imaginaryPart =sqrt(-delta)/(2*a);
        results.roots[0].real = realPart;
        results.roots[0].imaginary = - imaginaryPart;
        results.roots[1].real = realPart;
        results.roots[1].imaginary = imaginaryPart;
    }
    return results;
}

bool QuadraticFunction::intersect(QuadraticFunction q){
    // TODO: implement this function 
    QuadraticFunction k(this->a-q.a, this->b-q.b, this->c-q.c);

    if(k.a == 0 && k.b == 0 && k.c != 0)
        return false;
    if(k.a == 0 && k.b == 0 && k.c == 0)
        return true;
    if(k.a == 0 && k.b != 0)
        return true;
    Root rc = k.getRoot();
    if(rc.realRootNum == 2 || rc.realRootNum == 1)
        return true;
    else
        return false;
}