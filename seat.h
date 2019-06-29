
//
// Created by manar on 24/06/2019.
//
#ifndef SEAT_H
#define SEAT_H

#include <iostream>
#include <string>
using std::string;
using std::exception;
using std::cout;
using std::endl;



class NoPrice:public exception{
public:
    const char* what() const noexcept override;

};



class Seat
{
    int lineNumber;
    int chairNumber;
protected:
    int Price;
public:

    Seat(int linenumber, int chairnumber,int price):lineNumber(linenumber),chairNumber(chairnumber),Price(price){}
    virtual ~Seat()= default;
    virtual string location() ;
    virtual int price() const=0;

};



class GreenRoomSeat:public Seat
{
public:
    GreenRoomSeat(int linenumber,int chairnumber):Seat(linenumber,chairnumber,0){}
    string location()  override;
    int price() const override;


};


class MainHallSeat:public Seat
{
public:
    MainHallSeat(int linenumber, int chairnumber,int price):Seat(linenumber,chairnumber,price+100){}
    int price() const override;


};


class SpecialSeat:public MainHallSeat
{
public:
    SpecialSeat(int linenumber, int chairnumber,int price):
            MainHallSeat(linenumber,chairnumber,price+300){}
    int price() const override;

};


class GoldenCircleSeat:public SpecialSeat
{
public:
    GoldenCircleSeat(int linenumber, int chairnumber,int price):
            SpecialSeat(linenumber,chairnumber,price+1000){}
    string location()  override;
    int price() const override;
};


class DisablePodiumSeat:public SpecialSeat
{
private:
    int specialPrice;
public:
    DisablePodiumSeat(int linenumber, int chairnumber,int price=0):
            SpecialSeat(linenumber,chairnumber,price),specialPrice(200){}
    string location()  override;
    int price() const override;
};


class RegularSeat:public MainHallSeat
{
protected:
    char area;
public:
    RegularSeat(char area,int linenumber, int chairnumber,int price):
            MainHallSeat(linenumber,chairnumber,price){
        this->area=area;
    }


    int price() const override;

};


class FrontRegularSeat:public RegularSeat
{
public:
    FrontRegularSeat(char area,int linenumber, int chairnumber,int price):
            RegularSeat(area,linenumber,chairnumber,price+500){}
    string location()  override;
    int price() const override;

};


class MiddleRegularSeat:public RegularSeat
{
public:
    MiddleRegularSeat(char area,int linenumber, int chairnumber,int price):
            RegularSeat(area,linenumber,chairnumber,price+250){}
    string location()  override;
    int price() const override;
};


class RearRegularSeat:public RegularSeat
{
public:
    RearRegularSeat(char rear,int linenumber, int chairnumber,int price):
            RegularSeat(rear,linenumber,chairnumber,price){}
    string location()  override;
    int price() const override;

};

// ---------------------------------------------







#endif