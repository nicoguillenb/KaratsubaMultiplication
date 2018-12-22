#include <iostream>
#include <string>
#include "console.h"
#include "strlib.h"
#include "math.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
using namespace std;


string zero(int x);
string multiply(string x, string y);
string addition(string x, string y);
string substraction(string x, string y);
void addZeros(string &x, string &y);
void orderNumbers(string &x, string &y);

int main() {
    cout << "This program uses the Karatsuba Algorithm to multiply long integers." << endl;
//    string x = "3141592653589793238462643383279502884197169399375105820974944592";
//    string y = "2718281828459045235360287471352662497757247093699959574966967627";
    string x = "92";
    string y = "27";
    cout << "We're going to multiply the following numbers:" << endl;
    cout << "x: " + x << endl;
    cout << "y: " + y << endl;
    string result = multiply(x,y);
    cout << endl;
    cout << "The Result is: " + result << endl;
    return 0;
}

string multiply(string x, string y){
    if (x.length() != y.length()){
        addZeros(x,y);
    }
    if (x.length() == 1) {
        int result = (stringToInteger(x) * stringToInteger(y));
        return integerToString(result);
    } else {
        int n = x.length();
        string a = x.substr(0, n/2);
        string b = x.substr(n/2);
        string c = y.substr(0, n/2);
        string d = y.substr(n/2);
        string ac = multiply(a,c);
        string bd = multiply(d,b);
        string pq = multiply(addition(a,b), addition(c,d));
        string abdc = substraction(pq,addition(ac,bd));
        return addition(ac + zero(n), addition(abdc+ zero(n/2), bd));
    }
}

string zero(int x){
    string result;
    while (x > 0){
        result += "0";
        x--;
    }
    return result;
}

string addition(string x, string y){
    string result;
    string tempResult;
    int tempX;
    int tempY;
    int reminder = 0;
    if (x.length() != y.length()) addZeros(x,y);
    int xlength = x.length();
    for (int i = 0; i < xlength; i++){
        int length = x.length();
        if (stringIsInteger(x)) tempX = charToInteger(x[length-1]);
        x = x.substr(0,length-1);
        if (stringIsInteger(y)) tempY = charToInteger(y[length-1]);
        y = y.substr(0,length-1);
        tempResult = integerToString(tempX + tempY + reminder);
        result = tempResult[tempResult.length()-1] + result;
        if (tempResult.length() > 1){
            tempResult = tempResult.substr(0,tempResult.length()-1);
        } else {
            tempResult = "";
        }
        if (stringIsInteger(tempResult)){
            reminder = stringToInteger(tempResult);
        }
    }
    if (stringIsInteger(tempResult)){
        result = integerToString(reminder) + result;
    }
    return result;
}


string substraction(string x, string y){
    string result;
    string tempResult;
    addZeros(x,y);
    orderNumbers(x,y);
    int xlength = x.length();
    bool substraction = false;
    int helper = 0;
    int tempX;
    int tempY;
    for (int i = 0; i < xlength; i++){
        if (substraction) {
            helper = -1;
         } else {
            helper = 0;
         }
        int length = x.length();
        if (stringIsInteger(x)) tempX = charToInteger(x[length-1]);
        x = x.substr(0,length-1);
        if (stringIsInteger(y)) tempY = charToInteger(y[length-1]);
        y = y.substr(0,length-1);
        tempX += helper;
        if (tempX < tempY && stringIsInteger(x)){
            tempResult = integerToString((tempX + 10) - tempY);
            substraction = true;
        } else {
            tempResult = integerToString(tempX - tempY);
            substraction = false;
        }
        result = tempResult[tempResult.length()-1] + result;
        tempResult = "";
    }
    return result;
}

void addZeros(string &x, string &y){
    int xlength = x.length();
    if (x[0] == '-') xlength--;
    int ylength = y.length();
    if (y[0] == '-') ylength--;
    if (xlength > ylength){
        y = zero(xlength-ylength) + y;
    } else if (xlength < ylength){
        x = zero(ylength-xlength) + x;
    }
}

void orderNumbers(string &x, string &y){
    int counter = x.length();
    for (int i = 0; i < counter; i++){
        if(charToInteger(x[i]) != charToInteger(y[i])){
            if(charToInteger(x[i]) < charToInteger(y[i])){
                   string temp = x;
                   x = y;
                   y = temp;
            }
            return;
        }
    }
}

