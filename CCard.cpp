#include "CCard.h"

void CCard::readCardType(ifstream& inFile) {
    inFile >> type;
}

void CCard::readCardData(ifstream& inFile) {
    inFile >> name1 >> name2 >> power;
}

void CCard::Play(vector<unique_ptr<CStudent>>& playerTable) {

}

void CCard::Activate(vector<unique_ptr<CStudent>>& playerTable, vector<unique_ptr<CStudent>>& player2Table, CProfessor& professor1, CProfessor& professor2) {

}


