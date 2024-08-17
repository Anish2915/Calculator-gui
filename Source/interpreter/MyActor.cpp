// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include <iostream>
#include <string>
#include <vector>
#include "Containers/UnrealString.h"
#include <stack>
#include <regex>
using namespace std;

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

int searchResult(vector<char> arr, char k) {
	vector<char>::iterator it;
	it = find(arr.begin(), arr.end(), k);
	if (it != arr.end())
		return (it - arr.begin());
	else
		return -1;
}

int AMyActor::calculate(std::string s)
{
    std::stack<int> st;
    int curr = 0;
    char sign = '+';

    for (int i = 0; i < s.size(); i++) {
        if (isdigit(s[i])) {
            curr = 10 * curr + int(s[i] - '0');
        }
        if (!isdigit(s[i]) && s[i] != ' ' || i == s.size() - 1) {
            if (sign == '+') {
                st.push(curr);
            }
            else if (sign == '-') {
                st.push(-curr);
            }
            else {
                int num;
                if (sign == '*') {
                    num = st.top() * curr;
                }
                else {
                    num = st.top() / curr;
                }
                st.pop();
                st.push(num);
            }
            sign = s[i];
            curr = 0;
        }

    }
    int sum = 0;
    while (!st.empty()) {
        sum += st.top();
        st.pop();
    }
    return sum;
}

bool AMyActor::isValidNumber(string str) {
    regex pattern("^[-+]?([0-9]+\\.?[0-9]*|\\.[0-9]+)$");
    return regex_match(str, pattern);
}


void AMyActor::Called(FString input,FString& Output)
{
	string ok = TCHAR_TO_UTF8(*input);
    string ok1;
    string Out;
    vector<char> temp;
    string local;
    vector<char> oprTemp;
    vector<string> arrInt;
    double num = 0;
    double ST = 0;

    string Oprt = "/*+-";
    if (ok[0] == Oprt[0] || ok[0] == Oprt[1]   )
    {
        Output = TEXT("no operator allowed in first place");
        return;
    }
    if (ok[ok.length() - 1] == Oprt[0] || ok[ok.length() - 1] == Oprt[1] || ok[ok.length() - 1] == Oprt[2] || ok[ok.length() - 1] == Oprt[3])
    {
        Output = TEXT("no operator allowed in last place");
        return;
    }
    if (ok[0] == Oprt[3] || ok[0] == Oprt[2]) {
        ok1 = '0' + ok;
        ok = ok1;
    }
    for (int i = 0; i < ok.length(); i++)
    {
        if (ok[i] == Oprt[0] || ok[i] == Oprt[1] || ok[i] == Oprt[2] )
        {
            oprTemp.push_back(ok[i]);
            arrInt.push_back(local);
            local.clear();
        }
        else if (ok[i] == Oprt[3]) {
            oprTemp.push_back(Oprt[2]);
            arrInt.push_back(local);
            local.clear();
            local = local + "-";
        }
        else
        {
            local = local + ok[i];
        }
    }
    arrInt.push_back(local);
    

    for (auto &it : arrInt) {
        if (!isValidNumber(it)) {
            Output = TEXT("Wrong Decimal");
            return;
        };
    }

    for (int j = 0; j < 4; j++)
    {
        for (int k = 0; k < oprTemp.size(); k++)
        {
            if (Oprt[j] == oprTemp[k])
            {
                if (j == 0)
                {
                    if (stod(arrInt[k + 1]) == 0) {
                        Output = TEXT("somewhere devided by 0");
                        return;
                    }
                    ST = (stod(arrInt[k])) / (stod(arrInt[k + 1]));

                }
                else if (j == 1)
                {
                    ST = (stod(arrInt[k])) * (stod(arrInt[k + 1]));
                }
                else if (j == 2)
                {
                    ST = (stod(arrInt[k])) + (stod(arrInt[k + 1]));
                }
                else if (j == 3)
                {
                    ST = (stod(arrInt[k])) - (stod(arrInt[k + 1]));
                }
                arrInt.erase(arrInt.begin() + k);
                arrInt.erase(arrInt.begin() + k);
                arrInt.insert(arrInt.begin() + k, to_string(ST));
                arrInt.insert(arrInt.begin() + k, "a");
                oprTemp.erase(oprTemp.begin() + k);
                oprTemp.insert(oprTemp.begin() + k, '&');
            }
        }
        for (int l = 0; l < oprTemp.size(); l++) {
            if (oprTemp[l] == '&') {
                oprTemp.erase(oprTemp.begin() + l);
                l = l - 1;
            }
        }

        for (int l = 0; l < arrInt.size(); l++)
        {
            if (arrInt[l] == "a") {
                arrInt.erase(arrInt.begin() + l);
                l = l - 1;
            }

        }

    }

    Out = arrInt[0];
    std::cout << Out;
    double dd;
    dd = std::stod(Out);

	Output = Out.c_str();
	return;
}

void AMyActor::Check(FString input, FString& Output)
{
    FString allowedChars = "0123456789*+-/";
    FString filteredInput;

    for (int32 i = 0; i < input.Len(); i++)
    {
        TCHAR currentChar = input[i];
        
    }

    Output = filteredInput;
}



// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



