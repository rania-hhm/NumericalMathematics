#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include "windows.h"
#include "mmsystem.h"
#include<stdlib.h>
using namespace std;
const double E = 2.71828182845904523536;
HWND consoleWindow = GetConsoleWindow();    // Get a console handle
vector<int> valuesBiggerThan9;
vector<int> negationValues;
vector<int> negationDifferentiationValues;
vector<double> fractionValues;
int vI = 0, nI = 0, nDI = 0, fV = 0;
double inter1, inter2;
bool endorNo = true;
class CommonFunctions {
public:
    int Precedence(char op) // precedence of operators
    {
        if (op == '+' || op == '-')
            return 1;
        else if (op == '*' || op == '/')
            return 2;
        else if (op == '^' || op == 's' || op == 'c' || op == 't' || op == 'l' ||
            op == 'n' || op == 'r' || op == 'e' || op == 'f' ||
            op == 'g' || op == 'h' || op == 'i' || op == 'j' || op == 'k')
            return 3;
        else
            return 0;
    }
    int ConvertString(string& eq, int i) {
        int j = i + 1;
        int r = 1;
        string ins = eq;
        bool brk = true;
        for (int del = j; j < ins.size(), brk; j++, del++) {
            if (ins[j] >= '0' && ins[j] <= '9') {
                eq.erase(eq.begin() + del);
                del--;
                r++;
            }
            else
                brk = false;;
        }
        string in = ins.substr(i, r);
        int x = stoi(in);
        return x;
    }
    string OperatorAfterChange(string op) {
        if (op == "sin")
            return "s";
        else if (op == "tan")
            return "t";
        else if (op == "cos")
            return "c";
        else if (op == "ln")
            return "n";
        else if (op == "log")
            return "l";
        else if (op == "exp")
            return "e";
        else if (op == "root")
            return "r";
        else if (op == "sec")
            return "f";
        else if (op == "csc")
            return "g";
        else if (op == "cot")
            return "h";
        else if (op == "arcsin")
            return "i";
        else if (op == "arccos")
            return "j";
        else if (op == "arctan")
            return "k";
    }
    string EditEquation(string eq) {
        string res, op;
        for (int i = 0; i < eq.length(); i++) {
            if (eq[i] >= 48 && eq[i] <= 57) {
                op == "" ? res += eq[i] : res += OperatorAfterChange(op) + eq[i];
                op = "";
            }
            else
                if (eq[i] == '+' || eq[i] == '-' || eq[i] == '*' || eq[i] == '/' || eq[i] == '(' || eq[i] == ')'
                    || eq[i] == '^') {
                    op == "" ? res += eq[i] : res += OperatorAfterChange(op) + eq[i];
                    op = "";
                }
                else
                    if ((eq[i] == 'x' || eq[i] == 'y') && (i == 0 || eq[i - 1] != 'e')) {
                        op == "" ? res += eq[i] : res += OperatorAfterChange(op) + eq[i];
                        op = "";
                    }
                    else
                        op += eq[i];
        }
        return res;
    }
    string ConvertPostfix(string eq) //convert infix -> postfix
    {
        eq = EditEquation(eq);
        string res; //result of the string
        vector<char> op; //vector to hold operators
        for (int i = 0; i < eq.size(); i++) //loop to edit the orignal string
        {
            if ((eq[i] >= 48 && eq[i] <= 57)) //if it is a number
            {
                //check if the number more than 1 digit
                int x = ConvertString(eq, i);
                //and replace the number with character 'a'
                if (x > 9) {
                    res += 'a';
                    valuesBiggerThan9.push_back(x);
                }
                else //if the number is 1 digit type it
                    res += x + '0';

            }
            else if (eq[i] == 'x' || eq[i] == 'y')// if it's a variable type it
                res += eq[i];
            else if (eq[i] == '-') {
                if (i == 0 ||
                    eq[i - 1] == '+' || eq[i - 1] == '-' || eq[i - 1] == '*' || eq[i - 1] == '/' ||
                    eq[i - 1] == 'l' || eq[i - 1] == '^' || eq[i - 1] == 'r' || eq[i - 1] == 'e' ||
                    eq[i - 1] == 's' || eq[i - 1] == 'c' || eq[i - 1] == 't' || eq[i - 1] == 'n' ||
                    eq[i - 1] == 'f' || eq[i - 1] == 'g' || eq[i - 1] == 'h' || eq[i - 1] == 'i' ||
                    eq[i - 1] == 'j' || eq[i - 1] == 'k' || eq[i - 1] == '(')
                {
                    if (eq[i + 1] == 'x')
                        res += 'X';
                    else if (eq[i + 1] == 'y')
                        res += 'Y';
                    else {
                        int x = ConvertString(eq, i + 1);
                        res += 'b';
                        negationValues.push_back(x);
                    }
                    i++;
                }
                else {
                    if (op.size() == 0 || op[op.size() - 1] == '(') //if vector is empty or last element in vector is open brackets '(' push the operator
                        op.push_back(eq[i]);
                    else {
                        while (op.size() != 0 && Precedence(op[op.size() - 1]) >= Precedence(eq[i])) {
                            res += op[op.size() - 1];
                            op.pop_back();
                        }
                        op.push_back(eq[i]);
                    }
                }
            }
            else //else push it in vector
            {
                if ((op.size() == 0 || op[op.size() - 1] == '(' || eq[i] == '(') && eq[i] != ')') //if vector is empty or last element in vector is open brackets '(' push the operator
                    op.push_back(eq[i]);
                else if (eq[i] == ')') {
                    while (op[op.size() - 1] != '(') //if last element of vector is close bracket pop every operator untill open bracket and type it
                    {
                        res += op[op.size() - 1];
                        op.pop_back();
                    }
                    op.pop_back(); // pop open brackets
                }
                else //for operators
                {
                    if (Precedence(eq[i]) > Precedence(op[op.size() - 1]))//check the precedence if it greater push it
                        op.push_back(eq[i]);
                    else //else pop untill the last element is smaller in precedence and then push it
                    {
                        while (op.size() != 0 && Precedence(op[op.size() - 1]) >= Precedence(eq[i])) {
                            res += op[op.size() - 1];
                            op.pop_back();
                        }
                        op.push_back(eq[i]);
                    }
                }
            }
        }
        while (op.size() != 0) //type all the elements in vector
        {
            res += op[op.size() - 1];
            op.pop_back();
        }
        return res; // return the result after converison
    }
    double EvalRes(char eq, double a, double b) //solve equations of two operands or one operand
    {
        double res;
        switch (eq)
        {
        case '+':res = b + a;
            break;
        case '-':res = b - a;
            break;
        case '*':res = b * a;
            break;
        case '/':res = b / a;
            break;
        case '^':res = pow(b, a);
            break;
        case 's':res = sin(a);
            break;
        case 'c':res = cos(a);
            break;
        case 't':res = tan(a);
            break;
        case 'n':res = log(a);
            break;
        case 'l':res = log(a) / log(b);
            break;
        case 'r':res = pow(a, 1 / b); // nthRoot
            break;
        case 'e':res = exp(a);
            break;
        case 'f':res = 1 / cos(a);
            break;
        case 'g':res = 1 / sin(a);
            break;
        case 'h':res = cos(a) / sin(a);
            break;
        case 'i':res = asin(a);
            break;
        case 'j':res = acos(a);
            break;
        case 'k':res = atan(a);
            break;
        }
        return res;
    }
    double evalPostfix(string eq, double x, double y = 0) //calculate of the equation
    {
        vector<double> eval;//vector to hold numbers
        for (int i = 0, vI = 0, nI = 0, nDI = 0, fV = 0; i < eq.size(); i++)
        {
            if (eq[i] >= 48 && eq[i] < 57)
                eval.push_back(eq[i] - 48);
            else if (eq[i] == 'x') // if it is a number or variable push it
                eval.push_back(x);
            else if (eq[i] == 'y')
                eval.push_back(y);
            else if (eq[i] == 'a') // if the number more than 1 digit replace push the full number in the vector
            {
                eval.push_back(valuesBiggerThan9[vI]);
                vI++;
            }
            else if (eq[i] == 'X')
                eval.push_back(-x);
            else if (eq[i] == 'Y')
                eval.push_back(-y);
            else if (eq[i] == 'b') {
                eval.push_back(-negationValues[nI]);
                nI++;
            }
            else if (eq[i] == 'd') {
                eval.push_back(-negationDifferentiationValues[nDI]);
                nDI++;
            }
            else //else (operator), pop and calculate and push the result back
            {
                double a = eval[eval.size() - 1];//pop first number
                eval.pop_back();
                double b = 1;
                // some operator take only one operand ex. sin()
                // if it take two operand pop the second number
                if (eq[i] == '+' || eq[i] == '-' || eq[i] == '*' || eq[i] == '/' || eq[i] == 'l' || eq[i] == '^' || eq[i] == 'r')
                {
                    b = eval[eval.size() - 1];
                    eval.pop_back();
                }
                eval.push_back(EvalRes(eq[i], a, b));//calculate
            }
        }
        return eval[eval.size() - 1];//return the result of equation
    }
    void Draw(string s) {
        system("color 70 ");
        HDC consoleDC = GetDC(consoleWindow);
        for (int i = 600, x = 0; i <= 900; i++, x++) {
            SetPixel(consoleDC, i, 250, RGB(0, 0, 0));
            if (x % 100 == 0) {
                for (int j = 1; j < 10; j++) {
                    SetPixel(consoleDC, i, 245 + j, RGB(0, 0, 0));
                }
            }
        }
        for (int i = 100, x = 0; i <= 400; i++, x++) {
            SetPixel(consoleDC, 750, i, RGB(0, 0, 0));
            if (x % 100 == 0)
                for (int j = 1; j < 10; j++)
                    SetPixel(consoleDC, 745 + j, i, RGB(0, 0, 0));
        }
        for (double x = -100; x <= 100; x += 0.01) {
            int y = evalPostfix(s, x / 10) * 10;
            double xA, yA;
            if (y > 0) {
                yA = 200 - y;
            }
            else {
                yA = 200 + abs(y);
            }
            if (yA > 50 && yA < 350)
                SetPixel(consoleDC, x + 750, yA - 50 + 100, RGB(0, 0, 0));
        }
    }
};
class Differentiation : public CommonFunctions {
public:
    vector<string> eval;
    vector<pair<string, string>> fxfxD; // cos(cosx) -> -sin(cosx)*-sin(x) -> css -> dcxs*dxc** -> xc
    bool checkNumber(string& a) {
        if ((a.length() == 1 && a >= "0" && a <= "9") || a == "a" || a == "b" || a == "d" || a == "z")
            return true;
    }
    bool checkX(string a) { return a == "x" || a == "X"; }
    string findFxD(string a, bool num, bool isX) {
        if (num)
            return "0";
        else if (isX)
            return "1";
        else
            for (int i = 0; i < fxfxD.size(); i++)
                if (a == fxfxD[i].first)
                    return fxfxD[i].second;
        return "";
    }
    pair<string, bool> powerDecrement(string a) {
        double x;
        string afterDec;
        bool isZero = false;
        if (a == "a") {
            x = valuesBiggerThan9[vI];
            x--;
            vI++;
            valuesBiggerThan9.push_back(x);
            afterDec = "a";
        }
        else if (a == "b") {
            x = negationValues[nI];
            x++;
            nI++;
            negationDifferentiationValues.push_back(x);
            afterDec = "d";
        }
        else if (a == "d") {
            x = negationDifferentiationValues[nDI];
            x++;
            nDI++;
            negationDifferentiationValues.push_back(x);
            afterDec = "d";
        }
        else {
            int x = stoi(a);
            if (x == 0)
                isZero = true;
            x--;
            if (x < 0) {
                negationDifferentiationValues.push_back(x);
                afterDec = "d";
            }
            else {
                afterDec = to_string(x);
            }
        }
        return make_pair(afterDec, isZero);
    }
    string oneOperandOperator(string a, char op) {
        string fxD = "1";
        if (op == '*' || op == '/' || op == '-' || op == '+' || op == '^' || op == 'l' || op == 'r')
            return "";
        bool aX = checkX(a), aNUM = checkNumber(a);
        fxD = findFxD(a, aNUM, aX);
        switch (op)
        {
        case 's':  return a + "c" + fxD + "*";
        case 'c': {
            negationDifferentiationValues.push_back(1);
            return "d" + a + "s" + "*" + fxD + "*";
        }
        case 't':  return a + "f" + "2" + "^" + fxD + "*";
        case 'h': {
            negationDifferentiationValues.push_back(1);
            return "d" + a + "g" + "^" + "*" + fxD + "*";
        }
        case 'i':  return "1" + ("2" + ("1" + a + "2" + "^" + "-" + "r" + "/")) + fxD + "*";
        case 'j': {
            negationDifferentiationValues.push_back(1);
            return "d" + ("1" + ("2" + ("1" + a + "2" + "^" + "-" + "r" + "/"))) + "*" + fxD + "*";
        }
        case 'k':  return "1" + ("1" + a + "2" + "^" + "+") + "/" + fxD + "*";
        case 'n':  return "1" + a + "/" + fxD + "*";
        case 'e':  return a + "e" + fxD + "*";
        }
        return "";
    }
    string findDerivative(string a, string b, char op) {
        string fxD = oneOperandOperator(a, op);
        if (fxD != "")
            return fxD;
        bool aNUM = checkNumber(a), bNUM = checkNumber(b), aX = checkX(a), bX = checkX(b);
        string fxAD = findFxD(a, aNUM, aX), fxBD = findFxD(b, bNUM, bX);
        if (aNUM && bNUM)
            return "0";
        switch (op)
        {
        case '+':case '-': {
            return fxBD + fxAD + op;
        }
        case '^': {
            double valueOfD;
            bool negativeValue = false;
            if (bNUM && (b == "d" || b == "b")) {
                if (b == "d")
                    valueOfD = negationDifferentiationValues[negationDifferentiationValues.size() - 1];
                else if (b == "b") {
                    valueOfD = negationValues[negationValues.size() - 1];
                }
                b = to_string(valueOfD);
                negativeValue = true;
            }
            if (aNUM && bX) {
                pair<string, bool> powerDec = powerDecrement(a);
                if (powerDec.second)
                    return "0";
                return a + b + powerDec.first + '^' + '*';
            }
            else if (bNUM && aX) {
                if (negativeValue) {
                    negationDifferentiationValues.push_back(1);
                    return 'd' + b + 'n' + b + a + '^' + '*' + '*';
                }
                return b + 'n' + b + a + '^' + '*';
            }
            else if (bNUM) {
                if (negativeValue) {
                    negationDifferentiationValues.push_back(1);
                    return 'd' + b + 'n' + b + a + '^' + '*' + fxAD + '*' + '*';
                }
                return b + 'n' + b + a + '^' + '*' + fxAD + '*';
            }
            else if (aNUM) {
                pair<string, bool> powerDec = powerDecrement(a);
                if (powerDec.second)
                    return "0";
                return a + b + "*" + powerDec.first + "^" + fxBD + "*";
            }
            else {
                string fx = b + "n";
                string fxD = findDerivative(b, "", 'n');
                fxfxD.push_back(make_pair(fx, fxD));
                fx = a + fx + "*";
                fxD = findDerivative(b + "n", a, '*');
                fxfxD.push_back(make_pair(fx, fxD));
                return b + a + "^" + fxD + "*";
            }
        }
        case '*': {
            if ((aNUM && a == "d") || (bNUM && b == "d")) {
                int valueOfD = negationDifferentiationValues[negationDifferentiationValues.size() - 1];
                negationDifferentiationValues.push_back(valueOfD);
            }
            if (aNUM && bX)
                if (b == "X") {
                    negationDifferentiationValues.push_back(1);
                    return a + "d" + "*";
                }
                else
                    return a;
            else if (bNUM && aX)
                if (a == "X") {
                    negationDifferentiationValues.push_back(-1);
                    return b + "d" + "*";
                }
                else
                    return b;
            else if (bNUM)
                return b + fxAD + '*';
            else if (aNUM)
                return a + fxBD + '*';
            else
                return a + fxBD + "*" + b + fxAD + "*" + "+";
        }
        case '/': {
            if (aNUM && bX)
                return "1" + a + op;
            else if (bNUM && aX) {
                negationDifferentiationValues.push_back(1);
                return "d" + b + "x" + "2" + "^" + "/" + "*";
            }
            else if (bNUM) {
                negationDifferentiationValues.push_back(1);
                return "d" + b + fxAD + "*" + a + "2" + "^" + "/" + "*";
            }
            else if (aNUM)
                return "1" + a + "/" + fxBD + "*";
            else
                return fxBD + a + "*" + b + fxAD + "*" + "-" + a + "2" + "^" + "/";
        }
        case 'l': {
            if (bNUM && aX)
                return "1" + b + "n" + "/" + "1" + a + "/" + "*";
            else if (bNUM) {
                string fx = a + "n";
                fxD = findDerivative(a, "", 'n');
                fxfxD.push_back(make_pair(fx, fxD));
                return "1" + b + "n" + "/" + fxD + "*";
            }
        }
        case 'r': {
            if (bNUM && b == "2") {
                return fxAD + "1" + "*" + "2" + a + "*" + "/";
            }
        }
        }
        return "0";
    }
    string convertDerivative(string eq) {
        string insEq = eq;
        for (int i = 0; i < eq.length(); i++) {
            string ins;
            ins += eq[i];
            if ((eq[i] >= 48 && eq[i] < 57) || eq[i] == 'x' || eq[i] == 'X' || eq[i] == 'a' || eq[i] == 'b' || eq[i] == 'd' || eq[i] == 'z') {
                eval.push_back(ins);
            }
            else {
                string a = eval[eval.size() - 1];
                eval.pop_back();
                string b = "";
                if (eq[i] == '-' || eq[i] == '+' || eq[i] == '*' || eq[i] == '/' || eq[i] == '^' ||
                    eq[i] == 'r' || eq[i] == 'l')
                {
                    b = eval[eval.size() - 1];
                    eval.pop_back();
                }
                string fx, fxD;
                fx = b + a + eq[i];
                eval.push_back(fx);
                fxD = findDerivative(a, b, eq[i]);
                fxfxD.push_back(make_pair(fx, fxD));
            }
        }
        for (int i = 0; i < fxfxD.size(); i++)
            if (insEq == fxfxD[i].first)
                return fxfxD[i].second;
        if (eq == "x" || eq == "X")
            return "1";
        else
            return "0";
    }
};
class BisectionMethod : public CommonFunctions {
public:
    bool BiSectionConditionCal(string s, double& a, double& b) ///some equations leads to wrong values
    {
        double resB = evalPostfix(s, b);
        for (int i = -1, j = 1;; i--, j++) {
            double resBI = evalPostfix(s, j);
            double resBD = evalPostfix(s, i);
            if (resB == 0)
                return true;
            else if (resBI == 0) {
                b = j;
                return true;
            }
            else if (resBD == 0) {
                b = i;
                return true;
            }
            bool bI = false, bD = false;
            if (resB == resBI && resBD == resB) {
                if (j > 3)
                    return true;
                continue;
            }
            else if ((resB < 0 && resBI > resB) || (resBI < resB && resBI > 0)) {
                resB = resBI;
                b = j;
            }
            else
                bI = true;
            if ((resB < 0 && resBD > resB) || (resBD < resB && resBD > 0)) {
                resB = resBD;
                b = i;
            }
            else
                bD = true;
            if (bI && bD)
                break;
        }
        double resA = evalPostfix(s, a);
        for (int i = -1, j = 1;; i--, j++) {
            double resAI = evalPostfix(s, j);
            double resAD = evalPostfix(s, i);
            if (resA == 0)
                return true;
            else if (resAI == 0) {
                a = j;
                return true;
            }
            else if (resAD == 0) {
                a = i;
                return true;
            }
            bool aI = false, aD = false;
            if (resA == resAI && resAD == resA) {
                if (j > 3)
                    return true;
                continue;
            }
            else if ((resA > 0 && resAI < resA) || (resAI > resA && resAI < 0)) {
                resA = resAI;
                a = j;
            }
            else
                aI = true;
            if ((resA > 0 && resAI < resA) || (resAD > resA && resAD < 0)) {
                resA = resAD;
                a = i;
            }
            else
                aD = true;
            if (aI && aD)
                break;
        }
        return false;
    }
    void BiSection(string s, bool val) //bisection method
    {
        double a = 0, b = 0, c;//a for negative sign, b for positive sign
        //r to hold the result when a = 0
        bool bise = false;
        if (val) {
            cout << "Enter A\n";
            cin >> inter1;
            cout << "Enter B\n";
            cin >> inter2;
            a = inter1;
            b = inter2;
            bise = BiSectionConditionCal(s, a, b);
            if (evalPostfix(s, a) > 0 || evalPostfix(s, b) < 0) {
                cout << "error in interval \n";
                BiSection(s, val);
            }
        }
        else {
            bise = BiSectionConditionCal(s, a, b);
        }
        if (!bise) {
            c = (a + b) / 2;
            double re = evalPostfix(s, c);
            string table;
            cout << "Do you want the solution steps?\n";
            cout << "Enter yes or no\n";
            cin >> table;
            if (table[0] == 'y' || table[0] == 'Y') {
                cout << "\n f < 0 at x = a | f > 0 at x = b | midpoint c     | f(c)         \n";
                cout << "________________|________________|________________|_________________\n";
                cout << fixed << setprecision(6) << a << "\t|" << fixed << setprecision(6) << b << "\t |" << fixed << setprecision(6) << c << "\t  |" << fixed << setprecision(6) << re << endl;
            }
            while (abs(re) > 0.0000001)//if the absolute value smaller than 0.000000001 (tolerance) stop the loop
            {
                if (re < 0)//negative value store it in a
                    a = c;
                else //positive value store it in b
                    b = c;
                c = (a + b) / 2;
                re = evalPostfix(s, c); //value of f(c)
                if (table[0] == 'y' || table[0] == 'Y') {
                    cout << fixed << setprecision(6) << a << "\t|" << fixed << setprecision(6) << b << "\t |" << fixed << setprecision(6) << c << "\t  |" << fixed << setprecision(6) << re << endl;
                }
            }
            cout << "x = " << fixed << setprecision(10) << c << endl;//value of x
            cout << "f(x) = " << fixed << setprecision(10) << evalPostfix(s, c) << endl;
        }
        else {
            // bisection won't work
            // use another method
            if (evalPostfix(s, a) == 0)
                cout << "x = " << a << " f(x) = 0" << endl;
            else if (evalPostfix(s, b) == 0)
                cout << "x = " << b << " f(x) = 0" << endl;
        }
    }
    void callBisection() {
        system(" cls ");
        system("color 70 ");
        string s;
        cout << "Operators:\n";
        cout << "arithmetic operators: +, -, *, /, ^, ln(x) or lnx, 2log(x) or 2logx, 2root3, exp(x)\n";
        cout << "Trigonometric functions: sin(x), cos(x), tan(x), sec(x), csc(x), cot(x), arcsin(x), arccot(x), arctan(x)\n";
        cout << "x -> variable or number\n";
        cout << "ex. x-cos(x)+3*sinx\n";
        cout << "enter full equation without any spaces\n";
        cout << "equation: ";
        cin >> s;
        s = ConvertPostfix(s);
        cout << "Do you have a specific interval?\n";
        cout << "Enter yes or no\n";
        string interval;
        bool val;
        cin >> interval;
        system(" cls ");
        if (interval[0] == 'y' || interval[0] == 'Y')
        {
            val = true;
            BiSection(s, val);
        }
        else {
            val = false;
            BiSection(s, val);
        }
        string drawBisection;
        cout << "Do you want to sketch the graph of the function?\n";
        cout << "Enter yes or no\n";
        cin >> drawBisection;
        while (drawBisection[0] == 'y' || drawBisection[0] == 'Y') {
            Draw(s);
            cout << "draw again?\n";
            cout << "Enter yes or no\n";
            cin >> drawBisection;
        }
    }
};
class newtonthodMethod : public Differentiation {
public:
    bool FindNewtonRoot(string fx, string fxD1, string fxD2, double root) {
        double res = abs(evalPostfix(fx, root) * evalPostfix(fxD2, root) / pow(evalPostfix(fxD1, root), 2));
        return res < 1 && res != 0;
    }
    bool NewtonSolve(string fx, string fxD1, double root) {  /// x of (n+1) = x of (n) * ( ss1 / ss2 );
        double xi, xiA, valueOfFx, valueOfFxD, fxI;
        xi = root;
        valueOfFx = evalPostfix(fx, xi);
        valueOfFxD = evalPostfix(fxD1, xi);
        if (valueOfFxD == 0) {
            cout << "f'x = 0" << endl;
            system(" cls ");
            return false;
        }
        xiA = xi - valueOfFx / valueOfFxD;
        fxI = evalPostfix(fx, xiA);
        string table;
        cout << "Do you want the solution steps?\n";
        cout << "Enter yes or no\n";
        cin >> table;
        if (table[0] == 'y' || table[0] == 'Y') {
            cout << "\n x of i         | f(x)           | f'(x)          | x of i+1        \n";
            cout << "________________|________________|________________|_________________\n";
            cout << fixed << setprecision(9) << xi << " \t|" << valueOfFx << "\t |" << valueOfFxD << "\t  |" << xiA << endl;
        }
        int count = 0;
        double insFx = valueOfFx;
        bool notWrong = true;
        while (abs(fxI) > 0.0000001)//if the absolute value smaller than 0.000000001 (tolerance) stop the loop
        {
            int i = 0;
            xi = xiA;
            valueOfFx = evalPostfix(fx, xi);
            if (abs(valueOfFx) > 0 && valueOfFx > insFx) {
                count++;
                insFx = valueOfFx;
            }
            if (count > 20) {
                notWrong = false;
                system(" cls ");
                break;
            }
            valueOfFxD = evalPostfix(fxD1, xi);
            xiA = xi - valueOfFx / valueOfFxD;
            fxI = evalPostfix(fx, xiA);
            if (table[0] == 'y' || table[0] == 'Y') {
                cout << fixed << setprecision(9) << xi << "\t|" << valueOfFx << "\t |" << valueOfFxD << "\t  |" << xiA << endl;
            }
        }
        if (table[0] != 'y' && table[0] != 'Y')
            cout << fixed << setprecision(9) << "x = " << xiA << endl << "fx = " << valueOfFx << endl;
        return notWrong;
    }
    void Newton(string fx, bool val) {
        string fxD1 = convertDerivative(fx), fxD2 = convertDerivative(fxD1);
        double root = 0;
        if (val)
        {
        pointNewton:
            cout << "Enter the value of the root : ";
            cin >> root;
            if (FindNewtonRoot(fx, fxD1, fxD2, root)) {
                NewtonSolve(fx, fxD1, root);
            }
            else {
                cout << "Wrong .. , please try again\n";
                goto pointNewton;
            }

        }
        else {
            for (double i = 1, j = -1; i <= 100; i++, j--) {
                if (FindNewtonRoot(fx, fxD1, fxD2, i)) {
                    if (NewtonSolve(fx, fxD1, i))
                        break;
                }
                else if (FindNewtonRoot(fx, fxD1, fxD2, j)) {
                    if (NewtonSolve(fx, fxD1, i))
                        break;
                }
            }
        }
    }
    void callNewton() {
        system(" cls ");
        system("color 70 ");
        string fx;
        cout << "Operators:\n";
        cout << "arithmetic operators: +, -, *, /, ^, ln(x) or lnx, 2log(x) or 2logx, 2root3, exp(x)\n";
        cout << "Trigonometric functions: sin(x), cos(x), tan(x), sec(x), csc(x), cot(x), arcsin(x), arccot(x), arctan(x)\n";
        cout << "x -> variable or number\n";
        cout << "ex. x-cos(x)+3*sinx\n";
        cout << "enter full equation without any spaces\n";
        cout << "equation: ";
        cin >> fx;
        fx = ConvertPostfix(fx);
        cout << "Do you have a specific Root?\n";
        cout << "Enter yes or no\n";
        string YorN;
        cin >> YorN;
        bool val;
        if (YorN[0] == 'y' || YorN[0] == 'Y') {
            val = true;
            Newton(fx, val);
        }
        else {
            val = false;
            Newton(fx, val);
        }
        string drawNewton;
        cout << "Do you want to sketch the graph of the function?\n";
        cout << "Enter yes or no\n";
        cin >> drawNewton;
        while (drawNewton[0] == 'y' || drawNewton[0] == 'Y') {
            Draw(fx);
            cout << "draw again?\n";
            cout << "Enter yes or no\n";
            cin >> drawNewton;
        }
    }
};
class jacobianMethod : public CommonFunctions {
public:
    /*
    Update
        1.added new variable 'y' to func(ConvertPostfix() line (765,774) , evalPostfix() line (861,870,879) )
        2.ask user for extra derivative (fyD,gyD) cause it's partial fraction
        3.using func(evalPostfix) instead of func(solveAtPoint) also edited line(944,945)
        4.using func(evalPostfix) instead of func(findJacobianMatrix) and deleted extra bool variables
        5.vI,nI global instead of local variables because there are multiple equations
        6.line 953 multiply by 1/det not det
    */

    double evalPostfix(string eq, double x, double y = 0) //calculate of the equation
    {
        vector<double> eval;//vector to hold numbers
        for (int i = 0; i < eq.size(); i++)
        {
            if (eq[i] >= 48 && eq[i] < 57)
                eval.push_back(eq[i] - 48);
            else if (eq[i] == 'x') // if it is a number or variable push it
                eval.push_back(x);
            else if (eq[i] == 'y')
                eval.push_back(y);
            else if (eq[i] == 'a') // if the number more than 1 digit replace push the full number in the vector
            {
                eval.push_back(valuesBiggerThan9[vI]);
                vI++;
            }
            else if (eq[i] == 'X')
                eval.push_back(-x);
            else if (eq[i] == 'Y')
                eval.push_back(-y);
            else if (eq[i] == 'b') {
                eval.push_back(-negationValues[nI]);
                nI++;
            }
            else if (eq[i] == 'd') {
                eval.push_back(-negationDifferentiationValues[nDI]);
                nDI++;
            }
            else //else (operator), pop and calculate and push the result back
            {
                double a = eval[eval.size() - 1];//pop first number
                eval.pop_back();
                double b = 1;
                // some operator take only one operand ex. sin()
                // if it take two operand pop the second number
                if (eq[i] == '+' || eq[i] == '-' || eq[i] == '*' || eq[i] == '/' || eq[i] == 'l' || eq[i] == '^' || eq[i] == 'r')
                {
                    b = eval[eval.size() - 1];
                    eval.pop_back();
                }
                eval.push_back(EvalRes(eq[i], a, b));//calculate
            }
        }
        return eval[eval.size() - 1];//return the result of equation
    }
    void findX1andY1(string fxy, string fxD, string fyD, string gxy, string gxD, string gyD, pair <double, double> point) {
        pair <double, double> fgx0y0;
        fgx0y0.first = evalPostfix(fxy, point.first, point.second);
        fgx0y0.second = evalPostfix(gxy, point.first, point.second);
        vector <double> vJaco;
        vJaco.push_back(evalPostfix(fxD, point.first, point.second));
        vJaco.push_back(evalPostfix(fyD, point.first, point.second));
        vJaco.push_back(evalPostfix(gxD, point.first, point.second));
        vJaco.push_back(evalPostfix(gyD, point.first, point.second));
        // find det of vJaco
        double detv = vJaco[0] * vJaco[3] - vJaco[1] * vJaco[2];
        //del * vJaco
        for (int i = 0; i < vJaco.size(); i++)
            vJaco[i] = vJaco[i] * (1 / detv);
        //inverse vJaco
        swap(vJaco[3], vJaco[0]);
        vJaco[1] = vJaco[1] * -1;
        vJaco[2] = vJaco[2] * -1;
        // i have x0 || y0 = point 
        // i have fx0y0 || gx0y0 = fgx0y0 
        // i have inverse of jacobian matrix * del = vJaco
        // start solve to find x1 and y1
    /*
    to find x1 and y1
     1- solve newMatrix = vJaco * fgx0y0
     2- X1 || y1 = result = point - newMatrix
    */
        pair <double, double> newMatrix;
        newMatrix.first = vJaco[0] * fgx0y0.first + vJaco[1] * fgx0y0.second;
        newMatrix.second = vJaco[2] * fgx0y0.first + vJaco[3] * fgx0y0.second;

        pair <double, double> result;
        result.first = point.first - newMatrix.first;
        result.second = point.second - newMatrix.second;

        cout << "x1 = " << result.first << "\ny1 = " << result.second << endl;
    }
    void callJacobian() {
        system(" cls ");
        system("color 70 ");
        string s1, s2, s3, s4, s5, s6, fxy, fxD, fyD, gxy, gxD, gyD;
        cout << "Operators:\n";
        cout << "arithmetic operators: +, -, *, /, ^, ln(x) or lnx, 2log(x) or 2logx, 2root3, exp(x)\n";
        cout << "Trigonometric functions: sin(x), cos(x), tan(x), sec(x), csc(x), cot(x), arcsin(x), arccot(x), arctan(x)\n";
        cout << "x -> variable or number\n";
        cout << "ex. x-cos(x)+3*sinx\n";
        cout << "enter full equation without any spaces\n";
        cout << "first Equation: ";
        cin >> s1;
        cout << "\nAnd It is First Order ODEs for x: ";
        cin >> s2;
        cout << "\nAnd It is First Order ODEs for y: ";
        cin >> s3;
        cout << "\nsecond Equation: ";
        cin >> s4;
        cout << "\nAnd It is First Order ODEs for x : ";
        cin >> s5;
        cout << "\nAnd It is First Order ODEs for y : ";
        cin >> s6;
        fxy = ConvertPostfix(s1);
        fxD = ConvertPostfix(s2);
        fyD = ConvertPostfix(s3);
        gxy = ConvertPostfix(s4);
        gxD = ConvertPostfix(s5);
        gyD = ConvertPostfix(s6);
        pair <double, double> point;
        cout << "\nEnter the intersection point : \n";
        cin >> point.first >> point.second; /// point
        cout << endl;
        findX1andY1(fxy, fxD, fyD, gxy, gxD, gyD, point);
    }

};
class leastSquavesCurveFitting {
public:
    void calc_a_b(float& a, float& b, float  a1, float  a2, float  b1, float  b2, float  c1, float  c2)
    {
        a = 0.00001;
        b = 0.00001;
        float det;
        det = a1 * b2 - a2 * b1;

        a = (c1 * b2 - b1 * c2) / det;
        b = (a1 * c2 - c1 * a2) / det;
    }
    void straight_line()
    {
        int noOfPoints;
        float* x, * y, * xy, * x2;
        float a, b, a1, a2, b1, b2, c1, c2;

        cout << "Enter Number Of Points : ";
        cin >> noOfPoints;

        system("CLS");

        x = new float[noOfPoints + 1];
        y = new float[noOfPoints + 1];
        xy = new float[noOfPoints + 1];
        x2 = new float[noOfPoints + 1];

        x[noOfPoints] = 0;
        y[noOfPoints] = 0;
        xy[noOfPoints] = 0;
        x2[noOfPoints] = 0;

        cout << endl;

        cout << "Enter Points \n \n";

        for (int i = 0; i < noOfPoints; i++)
        {
            cout << "Enter x" << i << " : ";
            cin >> x[i];
            x[noOfPoints] += x[i];
            cout << "Enter F(" << x[i] << ") : ";
            cin >> y[i];
            y[noOfPoints] += y[i];
            cout << endl;
            xy[i] = x[i] * y[i];
            xy[noOfPoints] += xy[i];
            x2[i] = x[i] * x[i];
            x2[noOfPoints] += x2[i];
        }

        system("CLS");

        cout << "x\tY\txY\tx^2\n\n";
        for (int i = 0; i < noOfPoints; i++)
        {
            cout << x[i] << "\t" << y[i] << "\t" << xy[i] << "\t" << x2[i] << "\n";
        }

        cout << "----------------------------\n";
        cout << x[noOfPoints] << "\t" << y[noOfPoints] << "\t" << xy[noOfPoints] << "\t" << x2[noOfPoints] << "\n";

        cout << endl << endl << endl;

        calc_a_b(a, b, x[noOfPoints], x2[noOfPoints], noOfPoints, x[noOfPoints], y[noOfPoints], xy[noOfPoints]);

        cout << "a = " << a << endl;
        cout << "b = " << b << endl << endl;

        cout << "y = " << a << "x" << " + " << b << endl;
    }
    void exponential()
    {
        int noOfPoints;
        float* x, * y, * Y, * x2, * xY;
        float a, b, a1, a2, b1, b2, c1, c2;

        cout << "Enter Number Of Points : ";
        cin >> noOfPoints;

        system("CLS");

        x = new float[noOfPoints + 1];
        y = new float[noOfPoints + 1];
        Y = new float[noOfPoints + 1];
        x2 = new float[noOfPoints + 1];
        xY = new float[noOfPoints + 1];

        x[noOfPoints] = 0;
        y[noOfPoints] = 0;
        Y[noOfPoints] = 0;
        x2[noOfPoints] = 0;
        xY[noOfPoints] = 0;

        cout << endl;

        cout << "Enter Points \n \n";

        for (int i = 0; i < noOfPoints; i++)
        {
            cout << "Enter x" << i << " : ";
            cin >> x[i];
            x[noOfPoints] += x[i];
            cout << "Enter F(" << x[i] << ") : ";
            cin >> y[i];
            y[noOfPoints] += y[i];
            cout << endl;
            Y[i] = log(y[i]);
            Y[noOfPoints] += Y[i];
            xY[i] = x[i] * Y[i];
            xY[noOfPoints] += xY[i];
            x2[i] = x[i] * x[i];
            x2[noOfPoints] += x2[i];
        }

        system("CLS");

        cout << "x\ty\tY\t\tx^2\txY\n\n";
        for (int i = 0; i < noOfPoints; i++)
        {
            cout << x[i] << "\t" << y[i] << "\t" << Y[i] << "\t\t" << x2[i] << "\t" << xY[i] << "\n";
        }

        cout << "---------------------------------------------\n";
        cout << x[noOfPoints] << "\t" << y[noOfPoints] << "\t" << Y[noOfPoints] << "\t\t" << x2[noOfPoints] << "\t" << xY[noOfPoints] << "\n";

        calc_a_b(a, b, x[noOfPoints], x2[noOfPoints], noOfPoints, x[noOfPoints], Y[noOfPoints], xY[noOfPoints]);

        cout << "a = " << exp(a) << endl;
        cout << "b = " << b / log(E) << endl << endl;

        cout << "y = " << exp(a) << "x" << " + " << b / log(E) << endl;

    }
    void y_eq_a_x_b()
    {
        int noOfPoints;
        float* x, * y, * X, * Y, * X2, * xY, * XY;
        float a, b, a1, a2, b1, b2, c1, c2;

        cout << "Enter Number Of Points : ";
        cin >> noOfPoints;

        system("CLS");

        x = new float[noOfPoints + 1];
        y = new float[noOfPoints + 1];
        X = new float[noOfPoints + 1];
        Y = new float[noOfPoints + 1];
        X2 = new float[noOfPoints + 1];
        XY = new float[noOfPoints + 1];

        x[noOfPoints] = 0;
        y[noOfPoints] = 0;
        X[noOfPoints] = 0;
        Y[noOfPoints] = 0;
        X2[noOfPoints] = 0;
        XY[noOfPoints] = 0;

        cout << endl;

        cout << "Enter Points \n \n";

        for (int i = 0; i < noOfPoints; i++)
        {
            cout << "Enter x" << i << " : ";
            cin >> x[i];
            x[noOfPoints] += x[i];
            cout << "Enter F(" << x[i] << ") : ";
            cin >> y[i];
            y[noOfPoints] += y[i];
            cout << endl;
            X[i] = log(x[i]);
            X[noOfPoints] += X[i];
            Y[i] = log(y[i]);
            Y[noOfPoints] += Y[i];
            XY[i] = X[i] * Y[i];
            XY[noOfPoints] += XY[i];
            X2[i] = X[i] * X[i];
            X2[noOfPoints] += X2[i];
        }

        system("CLS");

        cout << "x\ty\tX\t\tY\t\tX^2\t    XY\n\n";
        for (int i = 0; i < noOfPoints; i++)
        {
            cout << x[i] << "\t" << y[i] << "\t" << setprecision(4) << X[i] << "\t\t" << Y[i] << "\t\t" << X2[i] << setprecision(4) << "\t    " << XY[i] << "\n";
        }

        cout << "--------------------------------------------------------------\n";
        cout << x[noOfPoints] << "\t" << y[noOfPoints] << "\t" << X[noOfPoints] << "\t\t" << Y[noOfPoints] << "\t\t" << setprecision(4) << X2[noOfPoints] << "\t    " << setprecision(4) << XY[noOfPoints] << "\n";

        calc_a_b(a, b, X[noOfPoints], X2[noOfPoints], noOfPoints, X[noOfPoints], Y[noOfPoints], XY[noOfPoints]);

        cout << "a = " << log(a) << endl;
        cout << "b = " << b << endl << endl;

        cout << "y = " << log(a) << "x" << " + " << b << endl;

    }
    void parabola()
    {
        int noOfPoints;
        float* x, * y, * xy, * x2, * x3, * x2y, * x4;

        cout << "Enter Number Of Points : ";
        cin >> noOfPoints;

        system("CLS");

        x = new float[noOfPoints + 1];
        y = new float[noOfPoints + 1];
        xy = new float[noOfPoints + 1];
        x2 = new float[noOfPoints + 1];
        x3 = new float[noOfPoints + 1];
        x4 = new float[noOfPoints + 1];
        x2y = new float[noOfPoints + 1];

        x[noOfPoints] = 0;
        y[noOfPoints] = 0;
        xy[noOfPoints] = 0;
        x2[noOfPoints] = 0;
        x3[noOfPoints] = 0;
        x4[noOfPoints] = 0;
        x2y[noOfPoints] = 0;

        cout << endl;

        cout << "Enter Points \n \n";

        for (int i = 0; i < noOfPoints; i++)
        {
            cout << "Enter x" << i << " : ";
            cin >> x[i];
            x[noOfPoints] += x[i];
            cout << "Enter F(" << x[i] << ") : ";
            cin >> y[i];
            y[noOfPoints] += y[i];

            xy[i] = x[i] * y[i];
            xy[noOfPoints] += xy[i];
            x2[i] = x[i] * x[i];
            x2[noOfPoints] += x2[i];
            x3[i] = x[i] * x[i] * x[i];
            x3[noOfPoints] += x3[i];
            x4[i] = x[i] * x[i] * x[i] * x[i];
            x4[noOfPoints] += x4[i];
            x2y[i] = x2[i] * y[i];
            x2y[noOfPoints] += x2y[i];

            cout << endl;
        }

        system("CLS");

        cout << "x\ty\txY\tx^2\tx^3\tx^4\t(x^2)Y\n\n";
        for (int i = 0; i < noOfPoints; i++)
        {
            cout << x[i] << "\t" << y[i] << "\t" << xy[i] << "\t" << x2[i] << "\t" << x3[i] << "\t" << x4[i] << "\t" << x2y[i] << "\n";
        }

        cout << "--------------------------------------------------------\n";
        cout << x[noOfPoints] << "\t" << y[noOfPoints] << "\t" << xy[noOfPoints] << "\t" << x2[noOfPoints] << "\t" << x3[noOfPoints] << "\t" << x4[noOfPoints] << "\t" << x2y[noOfPoints] << "\n";

    }
    void choices()
    {

        cout << "..:: Curve Fitting ::..\n\n\n";
        cout << "Choose Type Of Curve : \n\n";


        cout << "1.Straight Line ( y = ax + b ) \n\n";
        cout << "2.Parabola ( y = ax^2 + bx + c ) \n\n";
        cout << "3.Exponential ( y = ae^bx ) \n\n";
        cout << "4.curve ( y = ax^b ) \n\n";
    }
};
class NumericalIntegration : public Differentiation {
public:
    double iteratorValueForFx;
    void TrapezoidalRule(string fx, double a, double b, double n, double h) {
        double res = 0, error = 0;
        iteratorValueForFx = a;
        //h/3(f0+2*Efi+Fn)
        //-1/12(b-a)f''(zeta)*h^3
        for (int i = 0; i <= n; i++) {
            double fi = evalPostfix(fx, iteratorValueForFx);
            iteratorValueForFx += h;
            if (i == 0 || i == n) {
                res += fi;
            }
            else {
                res += 2 * fi;
            }
        }
        res *= h / 2;
        string fxD = fx;
        for (int i = 0; i < 2; i++)
            fxD = convertDerivative(fxD);
        iteratorValueForFx = a;
        for (int i = 0; i <= n; i++) {
            double resOfEq;
            resOfEq = -1 / 12.0 * (b - a) * evalPostfix(fxD, iteratorValueForFx) * pow(h, 3);
            iteratorValueForFx += h;
            error = max(error, abs(resOfEq));
        }
        cout << fixed << setprecision(10) << "\nresult =" << res << endl << "error =" << error << endl;
    }
    void SimpsonRule(string fx, double a, double b, double n, double h) {
        //h/3(f0+4*Efi+2*Efi+fn)
        //-1/180(b-a)h^4*f^4(zeta)D
        double res = 0, error = 0;
        iteratorValueForFx = a;
        for (int i = 0; i <= n; i++) {
            double fi = evalPostfix(fx, iteratorValueForFx);
            iteratorValueForFx += h;
            if (i == 0 || i == n) {
                res += fi;
            }
            else if ((i % 2) == 0) {
                res += 2 * fi;
            }
            else
                res += 4 * fi;
        }
        res *= h / 3;
        string fxD = fx;
        for (int i = 0; i < 4; i++)
            fxD = convertDerivative(fxD);
        iteratorValueForFx = a;
        for (int i = 0; i <= n; i++) {
            double resOfEq;
            resOfEq = -1 / 180.0 * (b - a) * evalPostfix(fxD, iteratorValueForFx) * pow(h, 4);
            iteratorValueForFx += h;
            error = max(error, abs(resOfEq));
        }
        cout << fixed << setprecision(10) << "\nresult =" << res << endl << "error =" << error << endl;
    }
    void CallNumericalIntegration() {
        string eq;
        double a, b, n, h;
        char cond;
        cout << "Operators:\n";
        cout << "arithmetic operators: +, -, *, /, ^, ln(x) or lnx, 2log(x) or 2logx, 2root3, exp(x)\n";
        cout << "Trigonometric functions: sin(x), cos(x), tan(x), sec(x), csc(x), cot(x), arcsin(x), arccot(x), arctan(x)\n";
        cout << "x -> variable or number\n";
        cout << "ex. x-cos(x)+3*sinx\n";
        cout << "enter full equation without any spaces\n";
        cin >> eq;
        eq = ConvertPostfix(eq);
        cout << "a: ";
        cin >> a;
        cout << "b: ";
        cin >> b;
        cout << "do you have n: ";
        cin >> cond;
        if (cond == 'y') {
            cout << "n: ";
            cin >> n;
            h = (b - a) / n;
        }
        else {
            cout << "do you have h:";
            cin >> cond;
            if (cond == 'y') {
                cout << "h: ";
                cin >> h;
                n = (b - a) / h;
            }
            else {
                n = 50;
                h = (b - a) / n;
            }
        }
        cout << "TrapezoidalRule: ";
        TrapezoidalRule(eq, a, b, n, h);

        cout << "SimpsonRule: ";
        SimpsonRule(eq, a, b, n, h);
    }
};
class Lagrange {
private:
    double x[1000] = { 0 }, y[1000] = { 0 }, res = 0;
    int n;
public:
    void boardy()
    {
        system("cls");
        for (int i = 0; i <= n; i++) {
            cout << "-------.";
        }
        cout << endl;
        cout << "   X   | ";
        for (int i = 0; i < n; i++) {
            cout << fixed << setprecision(4) << x[i] << "| ";
        }
        cout << endl;
        for (int i = 0; i <= n; i++) {
            cout << "-------.";
        }
        cout << endl;
        cout << "  F(X) | ";
        for (int i = 0; i < n; i++) {
            cout << fixed << setprecision(4) << y[i] << "| ";
        }
        cout << endl;
        for (int i = 0; i <= n; i++) {
            cout << "-------.";
        }
        cout << endl;
    }
    void callLagrange()
    {
        cout << "Enter the number of points" << endl;
        cin >> n;
        boardy();
        for (int i = 0; i < n; i++) {
            cout << "Enter X of " << i << " value: " ;
            cin >> x[i];
            boardy();
        }
        for (int i = 0; i < n; i++) {
            cout << "Enter f(x) of " << i << " value: ";
            cin >> y[i];
            boardy();
        }
        cout << "Enter x to find the function at x" << endl;
        double z; 
        cin >> z;
        for (int i = 0; i < n; i++) {
            double sumt = 1, sumb = 1;
            for (int j = 0; j < n; j++) {
                if (j == i)
                    continue;
                sumt *= (z - x[j]);
                sumb *= (x[i] - x[j]);
            }
            res += (sumt / sumb) * y[i];
        }
        cout << endl << "F(x) = " << res << endl << endl;
    }

};
class divDifference {
private:
    int n;
    float value, sum, y[10][10] = { 0,0 }, x[100] = { 0 };
public:
    float proterm(int i, float value, float x[])
    {
        float pro = 1;
        for (int j = 0; j < i; j++) {
            pro = pro * (value - x[j]);
        }
        return pro;
    }
    void dividedDiffTable(float x[], float y[][10], int n)
    {
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < n - i; j++) {
                y[j][i] = (y[j][i - 1] - y[j + 1]
                    [i - 1]) / (x[j] - x[i + j]);
            }
        }
    }
    float applyFormula(float value, float x[],
        float y[][10], int n)
    {
        float sum = y[0][0];

        for (int i = 1; i < n; i++) {
            sum = sum + (proterm(i, value, x) * y[0][i]);
        }
        return sum;
    }
    void printDiffTable(float y[][10], int n, float x[])
    {
        int t = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - i; j++) {
                cout << setprecision(4) << y[i][j] << "\t ";
                if (t) {
                    cout << x[i] << "\t";
                    t--;
                }
            }
            cout << "\n" << "\n";
            t++;
        }

    }
    float res(float x[], float y[][10], float f, int n) {
        float ress = 0;
        for (int i = 0; i < n; i++) {
            float sumt = 1, sumb = 1;
            for (int j = 0; j < n; j++) {
                if (j == i)
                    continue;
                sumt *= (f - x[j]);
                sumb *= (x[i] - x[j]);
            }
            ress += (sumt / sumb) * y[i][0];
        }
        return ress;
    }
    void boardy()
    {
        system("cls");
        for (int i = 0; i <= n; i++) {
            cout << "-------.";
        }
        cout << endl;
        cout << "   X   | ";
        for (int i = 0; i < n; i++) {
            cout << fixed << setprecision(4) << x[i] << "| ";
        }
        cout << endl;
        for (int i = 0; i <= n; i++) {
            cout << "-------.";
        }
        cout << endl;
        cout << "  F(X) | ";
        for (int i = 0; i < n; i++) {
            cout << fixed << setprecision(4) << y[i][0] << "| ";
        }
        cout << endl;
        for (int i = 0; i <= n; i++) {
            cout << "-------.";
        }
        cout << endl;
    }
    void calldivDifference()
    {
        cout << "Enter the number of points" << endl;
        cin >> n;
        boardy();
        for (int i = 0; i < n; i++) {
            cout << "Enter x of " << i << " value: ";
            cin >> x[i];
            boardy();
        }
        for (int i = 0; i < n; i++) {
            cout << "Enter f(x) of " << i << " value: ";
            cin >> y[i][0];
            boardy();
        }
        cout << "Enter x to find the function at x" << endl;
        float f; cin >> f;
        dividedDiffTable(x, y, n);
        printDiffTable(y, n, x);
        cout << endl << "F(x) = " << res(x, y, f, n) << endl;
    }
};
class NumericalDifferentiation : public Differentiation {
public:
    double pri1[100] = { 0.0 }, pri2[100] = { 0.0 }, point = 0.0, fval = 0.0, hval = 0.0, wherex = 0.0, approx = 0.0; 
    string sfx;
    void boardy()
    {
        system("cls");
        for (int i = 0; i <= point; i++) {
            cout << "-------.";
        }
        cout << endl;
        cout << "   X   | ";
        for (int i = 0; i < point; i++) {
            cout << fixed << setprecision(4) << pri1[i] << "| ";
        }
        cout << endl;
        for (int i = 0; i <= point; i++) {
            cout << "-------.";
        }
        cout << endl;
        cout << "  F(X) | ";
        for (int i = 0; i < point; i++) {
            cout << fixed << setprecision(4) << pri2[i] << "| ";
        }
        cout << endl;
        for (int i = 0; i <= point; i++) {
            cout << "-------.";
        }
        cout << endl;
    }
    double backward(double x, double y) { //1 x=i-1 y=i
        double  bak = 0;
        bak = (y - x) / hval;
        return bak;
    }
    double Central(double x, double y) {//2 x=i+1 y=i-1
        double  bak = 0;
        bak = (x - y) / 2 * hval;
        return bak;
    }
    double forward(double x, double y) {//3 x=i+1 y=i
        double  bak = 0;
        bak = (x - y) / hval;
        return bak;
    }
    double backwardsec(double x, double y, double a) { //4 y=i x=i-1 a=i-2
        double  bak = 0;
        bak = (y - 2 * x + a) / pow(hval, 2);
        return bak;
    }
    double centralsec(double x, double y, double z) {//5 x=i+1 y=i z=i-1
        double  bak = 0;
        bak = (x - 2 * y + z) / pow(hval, 2);

        return bak;
    }
    double forwardsec(double x, double y, double a) {//6 a=i+2 x=i+1 y=i
        double  bak = 0;
        bak = (a - 2 * x + y) / pow(hval, 2);
        return bak;
    }
    double where1[7];
    void pointiy(int wherex) {
        where1[0] = pri2[wherex - 2];
        where1[1] = pri2[wherex - 1];
        where1[2] = pri2[wherex];
        where1[3] = pri2[wherex + 1];
        where1[4] = pri2[wherex + 2];
    }
    void pointin() {
        pri1[0] = fval - (hval * 2);
        pri2[0] = evalPostfix(sfx, pri1[0], 0);
        pri1[1] = fval - hval;
        pri2[1] = evalPostfix(sfx, pri1[1], 0);
        pri1[2] = fval;
        pri2[2] = evalPostfix(sfx, pri1[2], 0);
        pri1[3] = fval + hval;
        pri2[3] = evalPostfix(sfx, pri1[3], 0);
        pri1[4] = fval + (hval * 2);
        pri2[4] = evalPostfix(sfx, pri1[4], 0);
    }
    void NumericalDifferentiationCall()
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    ask:
        system(" cls ");
        cout << "Do you have a valuable table?\n";
        string table;
        cin >> table;
        if (table[0] == 'Y' || table[0] == 'y') {
            cout << "How many point do you have?\n";
            cin >> point;
            boardy();
            cout << "Enter X value: ";
            for (int i = 0; i < point; i++) {
                cin >> pri1[i];
                boardy();
            }
            cout << "Enter F(X) value: ";
            for (int i = 0; i < point; i++) {
                cin >> pri2[i];
                boardy();
            }
        formask:
            cout << "Enter the equation: ";
            cin >> sfx;
            sfx = ConvertPostfix(sfx);
            cout << "\nEnter the value of x you want: ";
            cin >> fval;
            system(" cls ");
            string numfor;
        askmgin:
            cout << "\nChoose the number of the formula you want to solve by :\n";
            cout << "1) BackWord Formula\n2) Central Formula\n3) Forward Formula\n";
            cout << "4) BackWord Formula for second derivative\n5) Central Formula for second derivative\n6) Forward Formula for second derivative\n";
            cin >> numfor;
            for (int i = 0; i < point; i++) {
                if (pri1[i] == fval) {
                    wherex = i;
                }
            }
            if (numfor == "1") {//1 x=i-1 y=i i=2
                approx = backward(where1[1], where1[2]);
                cout << approx << endl;
            }
            else if (numfor == "2") {//2 x=i+1 y=i-1 i=2
                approx = Central(where1[3], where1[1]);
                cout << approx << endl;
            }
            else if (numfor == "3") {//3 x=i+1 y=i i=2
                approx = forward(where1[3], where1[2]);
                cout << approx << endl;
            }
            else if (numfor == "4") {//4 x=i-1 y=i a=i-2 i=2
                approx = backwardsec(where1[1], where1[2], where1[0]);
                cout << approx << endl;
            }
            else if (numfor == "5") {//5 x=i+1 y=i z=i-1 i=2
                approx = centralsec(where1[3], where1[2], where1[1]);
                cout << approx << endl;
            }
            else if (numfor == "6") {//6 x=i+1 y=i a=i+2 i=2
                approx = forwardsec(where1[3], where1[2], where1[4]);
                cout << approx << endl;
            }
            else {
                system(" cls ");
                cout << "Error, Please try again\n";
                goto forask;
            }
            string exer;
            cout << "Do you want the exact value and the error?\n";
            cin >> exer;
            if (exer[0] == 'y' || exer[0] == 'Y') {
                double exact = evalPostfix(convertDerivative(sfx), hval);
                cout << "The exact value is = " << exact << endl;
                cout << "The error is = " << exact - approx << endl;
            }
            else {
                system(" cls ");
                goto askmgin;
            }
        }
        else if (table[0] == 'N' || table[0] == 'n') {
            point = 5;
            cout << "Enter the equation:";
            cin >> sfx;
            sfx = ConvertPostfix(sfx);
            cout << "\nEnter X value:";
            cin >> fval;
            cout << "\nEnter delta x: ";
            cin >> hval;
            pointin();
            boardy();
        forask:
            string numfor;
        askagin:
            cout << "1) BackWord Formula\n2) Central Formula\n3) Forward Formula\n";
            cout << "4) BackWord Formula for second derivative\n5) Central Formula for second derivative\n6) Forward Formula for second derivative\n";
            cin >> numfor;
            wherex = 0;
            if (numfor == "1") {//1 x=i-1 y=i i=2
                approx = backward(pri2[1], pri2[2]);
                cout << approx << endl;
            }
            else if (numfor == "2") {//2 x=i+1 y=i-1 i=2
                approx = Central(pri2[3], pri2[1]);
                cout << approx << endl;
            }
            else if (numfor == "3") {//3 x=i+1 y=i i=2
                approx = forward(pri2[3], pri2[2]);
                cout << approx << endl;
            }
            else if (numfor == "4") {//4 x=i-1 y=i a=i-2 i=2
                approx = backwardsec(pri2[1], pri2[2], pri2[0]);
                cout << approx << endl;
            }
            else if (numfor == "5") {//5 x=i+1 y=i z=i-1 i=2
                approx = centralsec(pri2[3], pri2[2], pri2[1]);
                cout << approx << endl;
            }
            else if (numfor == "6") {//6 x=i+1 y=i a=i+2 i=2
                approx = forwardsec(pri2[3], pri2[2], pri2[4]);
                cout << approx << endl;
            }
            else {
                system(" cls ");
                cout << "Error, Please try again\n";
                goto forask;
            }
            string exer;
            cout << "Do you want the exact value and the error?\n";
            cin >> exer;
            if (exer[0] == 'y' || exer[0] == 'Y') {
                double exact = evalPostfix(convertDerivative(sfx), hval);
                cout << "The exact value is = " << exact << endl;
                cout << "The error is = " << exact - approx << endl;
            }
            else {
                system(" cls ");
                goto askagin;
            }
        }
        else {
            system(" cls ");
            cout << "Error, Please try again\n";
            goto ask;
        }
    }
};
int main()
{
    while (endorNo) {
    point0:
        system(" cls ");
        system("color 70 ");
        cout << "\n Methods That Project Solve , please Enter your number operation\n";
        cout << "  \n 1 - Non linear Algebraic \n 2 - Interpolating Polynomials \n 3 - Least Squaves and Curve Fitting \n 4 - Numerical Differentiation \n 5 - Numerical Intretion \n ";
        string RAD;
        cin >> RAD;
        system(" cls ");
        cout << "\n";

        //1 - start of Non linear algebraic equations
        if (RAD.size() == 1 && RAD[0] == '1') {
        point1:
            cout << "\n Methods of Non linear algebraic equations, please Enter your number operation\n";
            cout << "  \n 1 - Bisection method \n 2 - newton method \n 3 - Newton - jacobian method \n";
            string query;
            cin >> query;

            // 1 - start of Bisection method
            if (query.size() == 1 && query[0] == '1') {
                BisectionMethod bb;
                bb.callBisection();
            }
            // 1 - end of Bisection method

            // 2 - start of newton method
            else if (query.size() == 1 && query[0] == '2') {
                newtonthodMethod nn;
                nn.callNewton();
            }
            // 2 - end of newton method

            // 3 - start of Newton - jacobian method
            else if (query.size() == 1 && query[0] == '3') {
                jacobianMethod jj;
                jj.callJacobian();
            }
            // 3 - Newton - jacobian method

            // ERROR
            else {
                system(" cls ");
                cout << " Please try again .. ";
                goto point1;
            }
        }
        // // end of Non linear algebraic equations

        //2 - start of Interpolating polynomials
        else if (RAD.size() == 1 && RAD[0] == '2') {
        point2:
            cout << "\n Methods of Non linear algebraic equations, please Enter your number operation\n";
            cout << "  \n 1 - Lagrange Ploynomial method \n 2 - Divided Differece method \n";
            string query;
            cin >> query;

            // 1 - start of lagrange
            if (query.size() == 1 && query[0] == '1') {
                Lagrange lagrange;
                lagrange.callLagrange();
            }
            // 1 - end of lagrange

            // 2 - start of difference
            else if (query.size() == 1 && query[0] == '2') {
                divDifference div;
                div.calldivDifference();
            }
            // 2 - end of difference

            // ERROR
            else {
                system(" cls ");
                cout << " Please try again .. ";
                goto point2;
            }
        }
        //2 - end of Interpolating polynomials

        // 3 - start of Least Squaves and Curve Fitting
        else if (RAD.size() == 1 && RAD[0] == '3') {
            int choice;
        start:
            system("CLS");
            leastSquavesCurveFitting curve;
            curve.choices();
            cout << "Your Choice : ";
            cin >> choice;

            cout << endl << endl;
            system("CLS");
            switch (choice) {
            case 1:
                curve.straight_line();
                break;
            case 2:
                curve.parabola();
                break;
            case 3:
                curve.exponential();
                break;
            case 4:
                curve.y_eq_a_x_b();
                break;
            default: {
                system(" cls ");
                cout << " Please try again .. ";
                goto start;
            }
            }
        }
        // 3 - end of Least Squaves and Curve Fitting

        // 4 - start of Numerical Differentiation
        else if (RAD.size() == 1 && RAD[0] == '4') {
            NumericalDifferentiation diff;
            diff.NumericalDifferentiationCall();
        }
        // 4 - end of Numerical Differentiation

        // 5 - start of Numerical Integration
        else if (RAD.size() == 1 && RAD[0] == '5') {
            NumericalIntegration integration;
            integration.CallNumericalIntegration();
        }
        // 5 - end of Numerical Integration

        // error
        else
        {
            system("color 4f ");
            cout << " Error \n\n\n\n";
            cout << "\t\t\t         млпллллм\n";
            cout << "\t\t\t         лллллллл\n";
            cout << "\t\t\t         лллллппп\n";
            cout << "\t\t\t л      мллллппп \n";
            cout << "\t\t\tллм  мллллллммм \n";
            cout << "\t\t\t пллллллллллл  пл \n";
            cout << "\t\t\t   плллллллп     \n";
            cout << "\t\t\t    пллп  ппп    \n";
            cout << "\t\t\t      лл         \n";
            break;  
        }

        string endProject;
        cout << "Do you want to end the project?\n";
        cout << "Enter yes or no\n";
        cin >> endProject;
        if (endProject[0] == 'y' || endProject[0] == 'Y')
            endorNo = false;
        else
            system(" cls ");
    }
}