#pragma once
#include<iostream>
#include<string>
using namespace std;

struct qInt {
	int data[4];
};

typedef struct qInt QInt;

void ScanQInt(QInt& x);
void PrintQInt(QInt x);