#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
class CEasy : public CCard {
public:
    int resilience;
    int powerIncrement;
    void Activate(vector<unique_ptr<CStudent>>& playerTable, vector<unique_ptr<CStudent>>& player2Table, CProfessor& professor1, CProfessor& professor2) override {

    }
};
