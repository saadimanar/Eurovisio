
//
// Created by manar on 24/06/2019.
//

#include <iostream>
#include <string>
using std::string;
using std::exception;
using std::cout;
using std::endl;

#include "seat.h"



const char* NoPrice::what() const noexcept {
    return "Not For Sale !";
}

string Seat::location()  {
    string d = std::to_string(lineNumber);
    string f = std::to_string(chairNumber);
    string string = "line: "+ d + "," +" chair: "+ f;
    return string;
}

string GreenRoomSeat::location()  {
    string string1="Green Room-> "+(Seat::location());
    return string1;
}

int GreenRoomSeat::price() const {
    throw NoPrice() ;
}

int MainHallSeat::price() const {
    return this->Price;
}

int SpecialSeat::price() const {

    return this->Price;
}

string GoldenCircleSeat::location()  {
    string string1 = "Golden Circle-> "+(SpecialSeat::location());
    return string1;
}

int GoldenCircleSeat::price() const {
    return this->Price;
}

string DisablePodiumSeat::location() {

    string string1 = "Disable Podium-> "+(SpecialSeat::location());
    return string1;
}

int DisablePodiumSeat::price() const {
    return this->specialPrice;
}

int RegularSeat::price() const {
    return this->Price;
}

string FrontRegularSeat::location()  {
    char x= this->area;
    string s(1,x);
    string string1 = "Front-> area: " + s + ", " +(Seat::location());
    return string1;
}

int FrontRegularSeat::price() const {
    return this->Price;
}

string MiddleRegularSeat::location() {
   char x= this->area;
   string s(1,x);

    return "Middle-> area: " + s +", "+RegularSeat::location();

}

int MiddleRegularSeat::price() const {
    return this->Price;
}

string RearRegularSeat::location()  {
    char x= this->area;
    string s(1,x);
    return "Rear-> area: " + s +", " +(RegularSeat::location());
}

int RearRegularSeat::price() const {
    return this->Price;
}