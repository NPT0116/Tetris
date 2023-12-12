#pragma once
#include <iostream>
using namespace std;
class Position
{
public:
    int row;
    int col;
    Position(int ,int );
    void xuat()
    {
        cout<<"row : "<<row<<" col: "<<col<<endl;
    }
};