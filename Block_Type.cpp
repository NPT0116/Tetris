#pragma once


#include "Headers/Block.h"
#include "Headers/Position.h"

class L_block : public Block
{
public:
    L_block()
    {
        this -> id  =  0;
        Block ();
        block[0] = {Position(0,2),Position(1,0),Position(1,1),Position(1,2)};
        block[1] = {Position(0,1),Position(1,1),Position(2,1),Position(2,2)};
        block[2] = {Position(1,0),Position(1,1),Position(1,2),Position(2,0)};
        block[3] = {Position(0,0),Position(0,1),Position(1,1),Position(2,1)};
    }

};
class J_block : public Block
{
public:
    J_block()
    {
        this -> id  =  1;
        block[0] = {Position(0,0),Position(1,0),Position(1,1),Position(1,2)};
        block[1] = {Position(0,1),Position(0,2),Position(1,1),Position(2,1)};
        block[2] = {Position(1,0),Position(1,1),Position(1,2),Position(2,2)};
        block[3] = {Position(0,1),Position(1,1),Position(2,0),Position(2,1)};
    }

};
class I_block : public Block
{
public:
    I_block()
    {
        this -> id  =  2;
        Block();
        block[0] = {Position(1,0),Position(1,1),Position(1,2),Position(1,3)};
        block[1] = {Position(0,2),Position(1,2),Position(2,2),Position(3,2)};
        block[2] = {Position(2,0),Position(2,1),Position(2,2),Position(2,3)};
        block[3] = {Position(0,1),Position(1,1),Position(2,1),Position(3,1)};
    }
};
class O_block : public Block
{
public:
    O_block()
    {
        this -> id  =  3;
        Block ();
        block[0] = {Position(0,0),Position(0,1),Position(1,0),Position(1,1)};
        block[1] = {Position(0,0),Position(0,1),Position(1,0),Position(1,1)};
        block[2] = {Position(0,0),Position(0,1),Position(1,0),Position(1,1)};
        block[3] = {Position(0,0),Position(0,1),Position(1,0),Position(1,1)};
    }
};
class S_block : public Block
{
public:
    S_block()
    {
        this -> id  =  4;
        Block();
        block[0] = {Position(0,1),Position(0,2),Position(1,0),Position(1,1)};
        block[1] = {Position(0,1),Position(1,1),Position(1,2),Position(2,2)};
        block[2] = {Position(1,1),Position(1,2),Position(2,0),Position(2,1)};
        block[3] = {Position(0,0),Position(1,0),Position(1,1),Position(2,1)};
        for (Position po : block[0])
        {
            po.xuat();
        }
    }
};

class T_block : public Block
{
public:
    T_block()
    {
        this -> id  =  5;
        Block ();
        block[0] = {Position(0,1),Position(1,0),Position(1,1),Position(1,2)};
        block[1] = {Position(0,1),Position(1,1),Position(1,2),Position(2,1)};
        block[2] = {Position(1,0),Position(1,1),Position(1,2),Position(2,1)};
        block[3] = {Position(0,1),Position(1,0),Position(1,1),Position(2,1)};
    }
};

class Z_block : public Block
{
public:
    Z_block()
    {
        this -> id  =  6;
        Block ();
        block[0] = {Position(0,0),Position(0,1),Position(1,1),Position(1,2)};
        block[1] = {Position(0,2),Position(1,1),Position(1,2),Position(2,1)};
        block[2] = {Position(1,0),Position(1,1),Position(2,1),Position(2,2)};
        block[3] = {Position(0,1),Position(1,0),Position(1,1),Position(2,0)};
    }
};