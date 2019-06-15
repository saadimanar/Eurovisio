#ifndef EUROVISION_H_
#define EUROVISION_H_

#include <iostream>

// it's allowed to define here any using statements, according to needs.
// do NOT define here : using namespace std;

//---------------------------------------------------

enum VoterType { All, Regular, Judge };
enum Phase { Registration, Contest, Voting };

class Participant
{
    char* stateName;
    char* singerName;
    int songTimeLength;
    char* songName;
    bool isSingerRegistered;

// relevant private members can be defined here, if necessary.

public :
    Participant(const char* stateName, const char* songName, int songTimeLength, const char* singerName, bool isSingerRegistered = false);
    Participant();
    ~Participant();
    const char* state();
    const char* song();
    int timeLength();
    const char* singer();
    bool isRegistered();
    void update(const char* songName, int songTimeLength, const char* singerName);
    void updateRegistered(bool isSingerRegistered);

// need to define here possibly c'tr and d'tr and ONLY methods that
// are mentioned and demonstrated in the test example that has been published.
// NO OTHER METHODS SHOULD APPEAR HERE.
// NO friend is allowed here.
};

Participant::Participant(const char* stateName, const char* songName, int songTimeLength, const char* singerName, bool isSingerRegistered){
    this->songTimeLength = songTimeLength;
    this->stateName = new char[strlen(stateName)+1];
    strcpy(this->stateName, stateName);
    this->singerName = new char[strlen(singerName)+1];
    strcpy(this->singerName, singerName);
    this->songName = new char[strlen(songName)+1];
    strcpy(this->songName, songName);
    this->isSingerRegistered = isSingerRegistered;
}
Participant::Participant() {
    this->songTimeLength = 0;
    this->stateName = nullptr;
    this->singerName = nullptr;
    this->songName = nullptr;
    this->isSingerRegistered = false;
}
Participant::~Participant(){
    delete[](this->songName);
    delete[](this->singerName);
    delete[](this->stateName);
}
const char* Participant::song() {
    return this->songName;
}
const char* Participant::state() {
    return this->stateName;
}
const char* Participant::singer() {
    return this->singerName;
}
int Participant::timeLength() {
    return this->songTimeLength;
}
bool Participant::isRegistered() {
    return this->isSingerRegistered;
}
void Participant::update(const char *songName, int songTimeLength, const char *singerName) {
    if(strcmp(singerName, "") != 0){
        delete[](this->singerName);
        this->singerName = new char[strlen(singerName)+1];
        strcpy(this->singerName, singerName);
    }
    if(strcmp(songName, "") != 0){
        delete[](this->songName);
        this->songName = new char[strlen(songName)+1];
        strcpy(this->songName, songName);
    }
    if(songTimeLength != 0){
        this->songTimeLength = songTimeLength;
    }
}
void Participant::updateRegistered(bool isSingerRegistered) {
    this->isSingerRegistered = isSingerRegistered;
}
std::ostream& operator<<(std::ostream &os, Participant& participant){
    os << "[" << participant.state() << '/' << participant.song() << '/' << participant.timeLength() << '/' << participant.singer() << "]";
    return os;
}

//---------------------------------------------------

class Voter
{
    char* stateName;
    VoterType voter_type;
    int votingTime;

// relevant private members can be defined here, if necessary.

public :
    Voter(const char* stateName, VoterType voterType = Regular, int votingTime = 0);
    Voter() = default;
    Voter(const Voter& voter);
    ~Voter();
    char* state();
    VoterType voterType();
    int timesOfVotes();
    void operator++();
// need to define here possibly c'tr and d'tr and ONLY methods that
// are mentioned and demonstrated in the test example that has been published.
// NO OTHER METHODS SHOULD APPEAR HERE.

// NO friend is allowed here.
};

Voter::Voter(const char *stateName, VoterType voterType, int votingTime) {
    this->stateName = new char[strlen(stateName)+1];
    strcpy(this->stateName, stateName);
    this->voter_type = voterType;
    this->votingTime = votingTime;
}
Voter::Voter(const Voter &voter) {
    this->stateName = new char[strlen(voter.stateName)+1];
    strcpy(this->stateName, voter.stateName);
    this->voter_type = voter.voter_type;
    this->votingTime = voter.votingTime;
}
Voter::~Voter() {
    delete[](this->stateName);
}
char* Voter::state() {
    return this->stateName;
}
VoterType Voter::voterType() {
    return this->voter_type;
}
int Voter::timesOfVotes() {
    return this->votingTime;
}
void Voter::operator++() {
    this->votingTime = this->votingTime + 1;
}
std::ostream& operator<<(std::ostream &os, Voter& voter){
    os << "<" << voter.state() << '/' << voter.voterType() << ">";
    return os;
}

// -----------------------------------------------------------

struct Vote
{
    Voter voter;
    char* voting[10];

    Vote(const Voter& voter, const char* stateName1, const char* stateName2 = "", const char* stateName3 = "",
            const char* stateName4 = "", const char* stateName5 = "", const char* stateName6 = "", const char* stateName7 = "",
            const char* stateName8 = "", const char* stateName9 = "", const char* stateName10 = "");
// ALL is public here.
// need to define ONLY data members and c'tr and d'tr.
// NO NEED to define anything else.

};

Vote::Vote(const Voter &voter, const char *stateName1, const char *stateName2, const char *stateName3,
           const char *stateName4, const char *stateName5, const char *stateName6, const char *stateName7,
           const char *stateName8, const char *stateName9, const char *stateName10) {
    this->voter = Voter(voter);
    strcpy(this->voting[0], stateName1);
    strcpy(this->voting[1], stateName2);
    strcpy(this->voting[2], stateName3);
    strcpy(this->voting[3], stateName4);
    strcpy(this->voting[4], stateName5);
    strcpy(this->voting[5], stateName6);
    strcpy(this->voting[6], stateName7);
    strcpy(this->voting[7], stateName8);
    strcpy(this->voting[8], stateName9);
    strcpy(this->voting[9], stateName10);
}

// -----------------------------------------------------------


class MainControl {
    Phase phase;
    int maxParticipant ;
    int maxSongTimeLength;
    int maxVotingTime;
    int index;
    Participant* participants;
// relevant private members can be defined here, if necessary.

public :
    MainControl(int maxTimeLength = 180, int maxParticipant = 26, int maxVotingTime = 5, Phase phase = Registration);
    ~MainControl();
    bool participate(const char* stateName);
    bool legalParticipant(Participant& participant);
    void setPhase(Phase phase);
    MainControl& operator+=(Participant &participant);
//    MainControl& operator+=(Vote vote);
    MainControl& operator-=(Participant &participant);
    friend std::ostream& operator<<(std::ostream &os, const MainControl& mainControl);

// need to define here possibly c'tr and d'tr and ONLY methods that
// are mentioned and demonstrated in the test example that has been published.
// NO OTHER METHODS SHOULD APPEAR HERE.

// Also it's allowed here to define friend.

};

MainControl::MainControl(int maxTimeLength, int maxParticipant, int maxVotingTime, Phase phase) {
    this->maxParticipant = maxParticipant;
    this->phase = phase;
    this->maxSongTimeLength = maxTimeLength;
    this->maxVotingTime = maxVotingTime;
    this->index = 0;
    this->participants = new Participant[maxParticipant];
}
MainControl::~MainControl() {
    delete[](this->participants);
}
void MainControl::setPhase(Phase phase) {
    this->phase = phase;
}
bool MainControl::participate(const char *stateName) {
    for(int i = 0; i < this->maxParticipant; i++){
        if(strcmp(this->participants[i].state(), stateName) == 0)
            return true;
    }
    return false;
}
bool MainControl::legalParticipant(Participant &participant) {
    for(int i = 0; i < this->maxParticipant; i++){
        if(strcmp(this->participants[i].state(), "") == 0)
            return false;
        if(strcmp(this->participants[i].singer(), "") == 0)
            return false;
        if(strcmp(this->participants[i].song(), "") == 0)
            return false;
        if(this->participants[i].timeLength() > this->maxSongTimeLength)
            return false;
    }
    return true;
}
MainControl& MainControl::operator+=(Participant &participant) {
    if(phase == Registration){
        if(index == this->maxParticipant){
            return *this;
        }
        for(int i = 0; i < this->maxParticipant; i++){
            if(strcmp(participant.state(), this->participants[i].state()) == 0)
                return *this;
        }
        if(strcmp(participant.state(), "") == 0)
            return *this;
        if(strcmp(participant.singer(), "") == 0)
            return *this;
        if(strcmp(participant.song(), "") == 0)
            return *this;
        if(participant.timeLength() > this->maxSongTimeLength)
            return *this;

        this->participants[index] = Participant(participant);
        index ++;
        return *this;
    }
    return *this;
}
MainControl& MainControl::operator-=(Participant &participant) {
    if(this->index == 0)
        return *this;
    if(this->index == 1){
        if(strcmp(participant.state(), this->participants[1].state()) == 0){
            this->participants[1] = Participant();
        }
    }
    for(int i = 2; i < this->maxParticipant; i++){
        if(strcmp(participant.state(), this->participants[i].state()) == 0) {
            this->participants[i] = this->participants[this->index - 1];
            this->participants[this->index] = Participant();
            this->index --;
            return *this;
        }
    }
    return *this;
}
//MainControl& MainControl::operator+=(Vote vote) {
//
//}
std::ostream& operator<<(std::ostream &os, const MainControl& mainControl){
    if(mainControl.phase != Voting) {
        for (int i = 0; i < mainControl.maxParticipant; i++) {
            os << mainControl.participants[i];
        }
        return os;
    }
    return os;
}

// -----------------------------------------------------------

#endif
