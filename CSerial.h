#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "CCard.h"
class CSerial : public CCard {
public:
    int resilience;
    void Activate(vector<unique_ptr<CStudent>>& playerTable, vector<unique_ptr<CStudent>>& player2Table, CProfessor& professor1, CProfessor& professor2) override {

    }
};
