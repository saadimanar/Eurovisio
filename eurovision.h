#ifndef EUROVISION_H_
#define EUROVISION_H_

#include <iostream>
#include <string>
#include <list>

using std::string;
using std::list;

enum VoterType { All, Regular, Judge };
enum Phase { Registration, Contest, Voting };

template<typename Iterator>
Iterator maxElement(Iterator begin, Iterator end) {
    if (begin == end) {
        return end;
    }
    Iterator maximum = begin;
    for(Iterator i = ++begin; i != end; ++i) {
        if (**i > **maximum) {
            maximum = i;
        }
    }
    return maximum;
}

template <typename Iterator>
Iterator get(Iterator first, Iterator last, int place){
    if(place == 0){
        return(last);
    }
    int size = 0;
    for (Iterator i = first; i < last; ++i) {
        size++;
    }
    if(place > size){
        return(last);
    }
    list<Iterator> copy = {};
    for (Iterator i = first; i < last; ++i) {
        copy.push_back(i);
    }
    for(int i = 1; i < place; i++) {
        copy.erase(maxElement(copy.begin(), copy.end()));
    }
    Iterator maximum = first;
    for (Iterator j = first; j < last; ++j) {
        if(**maxElement(copy.begin(), copy.end()) == *j){
            maximum = j;
        }
    }
    return (maximum);
}

//---------------------------------------------------

class Participant
{
    string stateName;
    string singerName;
    int songTimeLength;
    string songName;
    bool isSingerRegistered;

public :
    Participant(const string& stateName, const string& songName, int songTimeLength, const string& singerName, bool isSingerRegistered = false);
    Participant() = delete;
    Participant(Participant& participant) = delete;
    ~Participant() = default;
    const string state();
    const string song();
    int timeLength();
    const string singer();
    bool isRegistered();
    void update(const string& songName, int songTimeLength, const string& singerName);
    void updateRegistered(bool isSingerRegistered);
    Participant&operator=(Participant& participant) = delete;
};

std::ostream& operator<<(std::ostream &os, Participant& participant);

//---------------------------------------------------

class Voter
{
    string stateName;
    VoterType voter_type;
    int votingTime;

public :
    explicit Voter(const string& stateName, VoterType voterType = Regular, int votingTime = 0);
    Voter() = default;
    ~Voter() = default;
    string state();
    VoterType voterType();
    int timesOfVotes();
    void operator++();
    void operator--() = delete;
};

std::ostream& operator<<(std::ostream &os, Voter& voter);

// -----------------------------------------------------------

struct Vote
{
    Voter* voter;
    string * voting;

    Vote(Voter& voter, const string& stateName1, const string& stateName2 = "", const string& stateName3 = "",
         const string& stateName4 = "", const string& stateName5 = "", const string& stateName6 = "", const string& stateName7 = "",
         const string& stateName8 = "", const string& stateName9 = "", const string& stateName10 = "");
    ~Vote();
};

// -----------------------------------------------------------

class MainControl {
    Phase phase;
    int maxParticipant ;
    int maxSongTimeLength;
    int maxVotingTime;
    int index;
    Participant** participants;
    int* judgeScore;
    int* regularScore;

public :

    class Iterator
    {
        int index;
        Participant* pointer;
        MainControl* mainControl;
    public:
        friend class MainControl;
        Iterator();
        ~Iterator() = default;

        Iterator& operator++();
        bool operator<(Iterator iterator);
        Participant& operator*();
        bool operator==(Iterator iterator);
        Iterator&operator--() = delete;
    };

    explicit MainControl(int maxTimeLength = 180, int maxParticipant = 26, int maxVotingTime = 5, Phase phase = Registration);
    ~MainControl();
    bool participate(const string& stateName);
    bool legalParticipant(Participant& participant);
    void setPhase(Phase phase);
    MainControl& operator+=(Participant &participant);
    MainControl& operator+=(const Vote& vote);
    MainControl& operator-=(Participant &participant);
    friend std::ostream& operator<<(std::ostream &os, const MainControl& mainControl);
    string operator()(int num, VoterType voterType);
    Iterator begin();
    Iterator end();
};

std::ostream& operator<<(std::ostream &os, const MainControl& mainControl);

// -----------------------------------------------------------

#endif
