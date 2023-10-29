// IteratorProject.cpp
#include <iostream>
//#include <cstddef>
#include <string>
#include <vector>

#define lambdaStr "?"
#define lambdaChar '?'


void outputLanguage(std::vector<std::string> L)
{ // Outputs signs in L language
    if (L.size() != 0)
    {
        std::cout << "<";
        for (int i = 0; i < L.size(); i++)
        {
            if (L[i] != lambdaStr)
                std::cout << L[i];
            else std::cout << "" << std::endl;
            if (i + 1 != L.size())
                std::cout << ";";
        } std::cout << ">" << std::endl;
    }
    else 
    {
        std::cout << "<>" << std::endl;
    }
}

void inputStr(std::vector<std::string> &inputString)
{ // The elements are listed comma-separated (without spaces)
    std::string getStr;
    getline(std::cin, getStr);
    std::string dividerStr;
    //String analyzator
    
    if (getStr.length() == 0)
    {
        inputString.push_back(lambdaStr);
    }
    else
    {
        for (int i = 0; i < getStr.length(); i++)
        {
            if (getStr[i] == ',')
            {
                inputString.push_back(getStr.substr(0, i));
                getStr.erase(0, i + 1);
                i = 0;
            }
        }
        inputString.push_back(getStr);
    }
}

bool isLambda(std::string str)
{ // return true if str is a lambda symbol
    if (str.length() > 0 && str.length() == 1)
    {
        if (str[0] == lambdaChar)
            return true;
        else return false;
    }
    else {
        return false;
    }
}

bool isContainLambda(std::string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == lambdaChar)
            return true;
    }
    return false;
}

void returnStrWithoutLambdas(std::string &strWithLambdas)
{
    for (int i = 0; i < strWithLambdas.length(); i++)
    {
        if (strWithLambdas[i] == lambdaChar)
        {
            strWithLambdas.erase(i, 1);
            i--;
        }
        
    }
}

void iterateLanguages(std::vector <std::string> L, std::vector <std::string> &L0_change, int iterateCount)
{ // Iterates L and L0_change languages for iterateCount times and return result in L0_change;
    if (iterateCount > 0)
    {
        std::vector <std::string> newL;
        for (int j = 0; j < L.size(); j++)
            for (int i = 0; i < L0_change.size(); i++)
            {
                if (!isLambda(L[j]))
                {
                    if ((!isLambda(L0_change[i])))
                    {
                        if (isContainLambda(L0_change[i]))
                            returnStrWithoutLambdas(L0_change[i]);
                        if (isContainLambda(L[j]))
                            returnStrWithoutLambdas(L[j]);
                        newL.push_back(L[j] + L0_change[i]);
                    }
                    else 
                    {
                        if (isContainLambda(L[j]))
                            returnStrWithoutLambdas(L[j]);
                        newL.push_back(L[j]);
                    }
                }
                else 
                {
                    if (!isLambda(L0_change[i]))
                    {
                        if (isContainLambda(L0_change[i]))
                            returnStrWithoutLambdas(L0_change[i]);
                        newL.push_back(L0_change[i]);
                    }
                }
            }
        L0_change = newL;
        newL.clear();
        iterateLanguages(L, L0_change, iterateCount - 1);
    }
}

void enterCountOfIterates(int& iters)
{
    std::cout << "Count of iterates: ";
    std::cin >> iters;
    while (!std::cin)
    {
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cout << "Enter a number from 0 to " << INT_MAX << ": ";
        std::cin >> iters;
    }
    if (iters < 0)
    {
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        enterCountOfIterates(iters);
    }
}

int main()
{ // lambda
    
    //create types
    std::vector <std::string> Language; //base-language
    std::vector <std::string> Language1; //0-language
    int countOfIter = 0;

    //input data
    std::cout << "L: ";
    inputStr(Language);
    std::cout<<"L1: ";
    inputStr(Language1); 
    enterCountOfIterates(countOfIter);
    
    //iterate
    iterateLanguages(Language, Language1, countOfIter);

    //output
    outputLanguage(Language1);
}
