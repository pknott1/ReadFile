#pragma once
#include "CCard.h"
#include "CProfessor.h"
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

class CStudent : public CCard {
public:
    int resilience;

    void Play(vector<unique_ptr<CStudent>>& playerTable) override;
    void Activate(vector<unique_ptr<CStudent>>& playerTable, vector<unique_ptr<CStudent>>& player2Table, CProfessor& professor1, CProfessor& professor2) override;

private:
    void AddToTable(vector<unique_ptr<CStudent>>& playerTable);
    void OutputTable(vector<unique_ptr<CStudent>>& playerTable);
    void AttackProfessor(unique_ptr<CStudent>& attackerCard, CProfessor& professor);
    void AttackStudent(unique_ptr<CStudent>& attackerCard, unique_ptr<CStudent>& targetCard);
    void RemoveDefeatedCards(vector<unique_ptr<CStudent>>& player2Table, int targetIndex);
};


