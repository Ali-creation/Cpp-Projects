#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;

//Armstrong Power helper
long long ArmstrongNumber_PowerHelper(int i, int num, int &cnum, long long pw){
    if(pow(i,num)<72036854775806)
        pw = pow(i,num);
    else{
        cnum++;
        pw = ArmstrongNumber_PowerHelper(i,num-1,cnum,pw);
    }
    return pw;
}

//Armstrong Number (code 1)
bool ArmstrongNumber(int num){
    int count =0;
    
    for (int i =1; i<num; i++){
        int cnum = 0;
        long long s =0;
        long long pw = 0;
        s = ArmstrongNumber_PowerHelper(i, num, cnum, pw);
        Label1:
        if (cnum != 0){
            s = s%num;
            int a = cnum;
            cnum = 0;
            pw = 0;
            s = s*ArmstrongNumber_PowerHelper(i,a,cnum ,pw);
            goto Label1;
        }
            
        if (s % num == i)
            count ++;
    }
    if( count == (num-1))
        return true;
    else
        return false;
}

//Cyclone Jet (code 2)
bool is_CycloneJet_helper(string st, int first, int last){
    // EFFECTS: returns true if the string
    // starting from its first elements and
    // ending at its last element can be read
    // both ways. i.e, is a Cyclone Jet 
    if( first>= last )
        return true;
    if(st[first] == st[last])
        return is_CycloneJet_helper(st,first+1, last-1);
    else
        return false;
}

bool CycloneJet(int num){
    // Returning the helper to satisfy the condition
    // Checks for same readibility both ways 
    string str = to_string(num);
    return is_CycloneJet_helper(str,0,str.length()-1);
}

//Black Premium Car Number (code 3)
bool BlackPremiumCarNumber(int num){
    double res = (sqrt((24*num)+1)+1)/6;
    if (floor(res) == res)
        return true;
    else
        return false;
}

//Auspicious Number (Code 4)
bool AuspiciousNumber(int num){
    int sum =0;
    for(int i=1; i<num; i++){
        if( num%i == 0)
            sum += i;
    }
    return sum>num;
}


void print_prompt() {
    cout << "Please enter the integer and the test number: ";
}

int main() {
    //TODO: write your code here
    int test, code;
    //Taking Inputs
    PromptLabel: print_prompt();
    cin>> test>> code;
    //Checks for correct code input
    if( code ==1 || code ==2 || code ==3 || code ==4){
        ;
    }
    else
        goto PromptLabel;
    //Checks for correct test number and calling the proper function
    if ( test >0 && test <=10000000){
        switch(code){
            case 1:
                cout<< ArmstrongNumber(test);
                break;
            case 2:
                cout<< CycloneJet(test);
                break;
            case 3:
                cout<< BlackPremiumCarNumber(test);
                break;
            case 4:
                cout<< AuspiciousNumber(test);
                break;
            default:
                return 0;
        }
    }
    else
        goto PromptLabel;
    return 0;
}