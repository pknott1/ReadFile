#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "CCard.h"
class CResearch : public CCard {
public:
    int powerIncrement;
    void Activate(vector<unique_ptr<CStudent>>& playerTable, vector<unique_ptr<CStudent>>& player2Table, CProfessor& Attacker, CProfessor& professor2) override {

    }
};

