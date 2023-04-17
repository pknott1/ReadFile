#pragma once
#include "Readfile.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <vector>

using namespace std;

class CCard {
public:
    int type;
    string name1;
    string name2;
    int power;
    int resilience;

    virtual ~CCard() {}

    virtual void readCardType(ifstream& inFile) {
        inFile >> type;
    }

    virtual void readCardData(ifstream& inFile) {
        inFile >> name1 >> name2 >> power;
    }

    virtual void Play(vector<unique_ptr<CStudent>>& playerTable) {

    }

    virtual void Activate(vector<unique_ptr<CStudent>>& playerTable, vector<unique_ptr<CStudent>>& player2Table, CProfessor& professor1, CProfessor& professor2) {
    }
};

