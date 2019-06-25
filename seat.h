#include <iostream>
#include <string>
using std::string;
using std::exception;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;


class NoPrice{
    string what(){
        return ("Not For Sale !");
    }

};



// ---------------------------------------------
class Seat
{
    int lineNumber;
    int chairNumber;
protected:
    int Price;
public:

    Seat(int linenumber, int chairnumber,int price):lineNumber(linenumber),chairNumber(chairnumber),Price(price){}
    virtual ~Seat()= default;
    virtual string location() const{
        string d = std::to_string(lineNumber);
        string f = std::to_string(chairNumber);
        string string = "line "+ d +" chair "+ f;
        return string;
    }
    virtual int price() const=0;

};

// ---------------------------------------------
class GreenRoomSeat:public Seat
{
public:
    GreenRoomSeat(int linenumber,int chairnumber):Seat(linenumber,chairnumber,0){}
    string location() const override{
        string string1="GreenRoomSeat->"+(Seat::location());
        return string1;
    }


//    class NoPrice{
//        string what(){
//            return ("Not For Sale !");
//        }
//
//    };


    int price() const override{
        throw NoPrice() ;
    }

};

// ---------------------------------------------
class MainHallSeat:public Seat
{
public:
    MainHallSeat(int linenumber, int chairnumber,int price):Seat(linenumber,chairnumber,price+100){}
    int price() const override{
        return this->Price;
    }

};

// ---------------------------------------------
class SpecialSeat:public MainHallSeat
{
public:
    SpecialSeat(int linenumber, int chairnumber,int price):MainHallSeat(linenumber,chairnumber,price){}
    int price() const override{
        return this->Price;
    }
};

// ---------------------------------------------
class GoldenCircleSeat:public SpecialSeat
{
public:
    GoldenCircleSeat(int linenumber, int chairnumber,int price):SpecialSeat(linenumber,chairnumber,price+1000){}
    int price() const override{
       return this->Price;
    }

};

// ---------------------------------------------
class DisablePodiumSeat:public SpecialSeat
{
private:
    int specialPrice;
public:
    DisablePodiumSeat(int linenumber, int chairnumber,int price=0):
    SpecialSeat(linenumber,chairnumber,price),specialPrice(200){}
    int price() const override{
        return this->specialPrice;
    }
};

class RegularSeat:public MainHallSeat
{
private:
   char area;
public:
    RegularSeat(char area,int linenumber, int chairnumber,int price):
    MainHallSeat(linenumber,chairnumber,price){
        this->area=area;
    }
//    virtual void location() const override {
//       cout<<"area:"<<area;
//      MainHallSeat::location();
//    }
    int price() const override{
        return this->Price;
    }

};


class FrontRegularSeat:public RegularSeat
{
public:
    FrontRegularSeat(char area,int linenumber, int chairnumber,int price):
    RegularSeat(area,linenumber,chairnumber,price+500){}
    string location() const override{
        string string1 = "Front->area:"+RegularSeat::location();
        return string1;

    }
    int price() const override{
        return this->Price;
    }

};


class MiddleRegularSeat:public RegularSeat
{
public:
    MiddleRegularSeat(char area,int linenumber, int chairnumber,int price):
            RegularSeat(area,linenumber,chairnumber,price+250){}
    string location() const override{
        string string1="Middle->area:"+RegularSeat::location();
        return string1;
    }
    int price() const override{
        return this->Price;
    }
};

// ---------------------------------------------
class RearRegularSeat:public RegularSeat
{
public:
    RearRegularSeat(char rear,int linenumber, int chairnumber,int price):
    RegularSeat(rear,linenumber,chairnumber,price){}
    string location() const override{
        return ("Rear->area:"+RegularSeat::location());
    }
    int price() const override{
        return this->Price;
    }

};

// ---------------------------------------------

