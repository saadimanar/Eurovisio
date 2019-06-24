#ifndef EUROVISION_H_
#define EUROVISION_H_

#include <iostream>
#include "string"
using std::string;

// it's allowed to define here any using statements, according to needs.
// do NOT define here : using namespace std;

//---------------------------------------------------

enum VoterType { All, Regular, Judge };
enum Phase { Registration, Contest, Voting };

int compareChars(const char* string1, const char* string2){
    int i = 0;
    while((i < (int)(strlen(string1) - 1)) && (i < (int)(strlen(string2) - 1)) &&
          (string1)[i] == (string2)[i]){

        i++;
    }
    if(i >= (int)(strlen(string1) - 1))
        return 1;
    if(i >= (int)(strlen(string2) - 1))
        return (-1);
    return ((string1)[i] - (string2)[i]);
}
int votesToScores(int place){
    switch (place){
        case 0:
            return 12;
        case 1:
            return  10;
        case 2:
            return  8;
        default:
            return (10 - place);
    }
}

template <class T>
T max(const T* array, int length){
    if(length == 0){
        return (-1);
    }
    T result = 0;
    for (int i = 1; i < length; ++i) {
        if (array[result] <= array[i]) {
            result = i;
        }
    }
    return result;
}

template <class T>
T get(const T* array, int length, int place){
    if((place > length) || (length == 0) || (place == 0)){
        return (-1);
    }
    T* newArray = new T[length];
    for (int j = 0; j < length; ++j) {
        newArray[j] = array[j];
    }
    T result = max(array, length);
    for (int i = 1; i < place; ++i) {
        newArray[result] = (-1);
        result = max(newArray, length);
    }
    delete[](newArray);
    return result;
}

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
    if(!this->isRegistered()) {
        if (strcmp(singerName, "") != 0) {
            delete[](this->singerName);
            this->singerName = new char[strlen(singerName) + 1];
            strcpy(this->singerName, singerName);
        }
        if (strcmp(songName, "") != 0) {
            delete[](this->songName);
            this->songName = new char[strlen(songName) + 1];
            strcpy(this->songName, songName);
        }
        if (songTimeLength != 0) {
            this->songTimeLength = songTimeLength;
        }
    }
}
void Participant::updateRegistered(bool isSingerRegistered) {
    this->isSingerRegistered = isSingerRegistered;
}
std::ostream& operator<<(std::ostream &os, Participant& participant){
    os << "[" << participant.state() << '/' << participant.song() << '/' << participant.timeLength() << '/' << participant.singer() << "]";
    return os;
}

int getStatePlace(const char* stateName, Participant** states, int length){
    for (int i = 0; i < length; ++i) {
        if(strcmp((*(states[i])).state(), stateName) == 0)
            return i;
    }
    return (-1);
}
//---------------------------------------------------

class Voter
{
    char* stateName;
    VoterType voter_type;
    int votingTime;

// relevant private members can be defined here, if necessary.

public :
    explicit Voter(const char* stateName, VoterType voterType = Regular, int votingTime = 0);
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
    return (this->votingTime);
}
void Voter::operator++() {
    this->votingTime += 1;
}
std::ostream& operator<<(std::ostream &os, Voter& voter){
    if(voter.voterType() == Regular) {
        os << "<" << voter.state() << '/' << "Regular>";
        return os;
    }
    os << "<" << voter.state() << '/' << "Judge>";
    return os;
}

// -----------------------------------------------------------

struct Vote
{
    Voter* voter;
    char** voting;

    Vote(Voter& voter, const char* stateName1, const char* stateName2 = "", const char* stateName3 = "",
            const char* stateName4 = "", const char* stateName5 = "", const char* stateName6 = "", const char* stateName7 = "",
            const char* stateName8 = "", const char* stateName9 = "", const char* stateName10 = "");
    ~Vote();
// ALL is public here.
// need to define ONLY data members and c'tr and d'tr.
// NO NEED to define anything else.

};

Vote::Vote(Voter &voter, const char *stateName1, const char *stateName2, const char *stateName3,
           const char *stateName4, const char *stateName5, const char *stateName6, const char *stateName7,
           const char *stateName8, const char *stateName9, const char *stateName10) {
    if(voter.voterType() == Judge){
        this->voter = &voter;
        this->voting = new char*[10];
        this->voting[0] = new char[strlen(stateName1)+1];
        strcpy(this->voting[0], stateName1);
        this->voting[1] = new char[strlen(stateName2)+1];
        strcpy(this->voting[1], stateName2);
        this->voting[2] = new char[strlen(stateName3)+1];
        strcpy(this->voting[2], stateName3);
        this->voting[3] = new char[strlen(stateName4)+1];
        strcpy(this->voting[3], stateName4);
        this->voting[4] = new char[strlen(stateName5)+1];
        strcpy(this->voting[4], stateName5);
        this->voting[5] = new char[strlen(stateName6)+1];
        strcpy(this->voting[5], stateName6);
        this->voting[6] = new char[strlen(stateName7)+1];
        strcpy(this->voting[6], stateName7);
        this->voting[7] = new char[strlen(stateName8)+1];
        strcpy(this->voting[7], stateName8);
        this->voting[8] = new char[strlen(stateName9)+1];
        strcpy(this->voting[8], stateName9);
        this->voting[9] = new char[strlen(stateName10)+1];
        strcpy(this->voting[9], stateName10);
        int count = 0;
        for (int i = 0; i < 10; i++){
            if ((strcmp(this->voting[i], voter.state()) == 0) || ((strcmp(stateName1, "") == 0))){
                count++;
                for (int j = i; j < 9; ++j) {
                    delete[](this->voting[i]);
                    this->voting[i] = new char[strlen(this->voting[i+1])+1];
                    this->voting[i] = this->voting[i+1];
                }
                this->voting[10-count] = nullptr;
            }
        }
    }
    if((voter.voterType() == Regular)){
        this->voter = &voter;
        this->voting = new char *[1];
        if((strcmp(voter.state(), stateName1) == 0) || (strcmp(stateName1, "") == 0)){
            this->voting[0] = nullptr;
        } else {
            this->voting[0] = new char[strlen(stateName1)+1];
            strcpy(this->voting[0], stateName1);
        }
    }
}
Vote::~Vote() {
    if(this->voter->voterType() == Regular){
        delete[](this->voting[0]);
    } else{
        for (int i = 0; i < 10; ++i) {
            if(this->voting[i] != nullptr) {
                delete[](this->voting[i]);
            }
        }
    }
    delete[](this->voting);
}

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
    int* judgeVoter;

// relevant private members can be defined here, if necessary.

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
    };

    explicit MainControl(int maxTimeLength = 180, int maxParticipant = 26, int maxVotingTime = 5, Phase phase = Registration);
    ~MainControl();
    bool participate(const char* stateName);
    bool legalParticipant(Participant& participant);
    void setPhase(Phase phase);
    MainControl& operator+=(Participant &participant);
    MainControl& operator+=(Vote &vote);
    MainControl& operator-=(Participant &participant);
    friend std::ostream& operator<<(std::ostream &os, const MainControl& mainControl);
    string operator()(int num, VoterType voterType);
    Iterator iterator();
    Iterator begin();
    Iterator end();

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
    this->participants = new Participant*[maxParticipant];
    this->regularScore = new int[maxParticipant];
    this->judgeScore = new int[maxParticipant];
    this->judgeVoter = new int[maxParticipant];
    for(int i = 0; i < maxParticipant; i++){
        this->participants[i] = nullptr;
        this->regularScore[i] = 0;
        this->judgeScore[i] = 0;
        this->judgeVoter[i] = 0;
    }
}
MainControl::~MainControl() {
    delete[](this->participants);
    delete[](this->judgeScore);
    delete[](this->regularScore);
}
void MainControl::setPhase(Phase phase) {
    this->phase = phase;
}
bool MainControl::participate(const char *stateName) {
    for(int i = 0; i < this->index; i++){
        if(((*this->participants[i]).state() != nullptr)
                       && (stateName != nullptr) && (strcmp((*(this->participants[i])).state(), stateName) == 0)){
            return true;
        }
    }
    return false;
}
bool MainControl::legalParticipant(Participant &participant) {
    if(strcmp(participant.state(), "") == 0)
        return false;
    if(strcmp(participant.singer(), "") == 0)
        return false;
    if(strcmp(participant.song(), "") == 0)
        return false;
    return (participant.timeLength() <= this->maxSongTimeLength);
}
MainControl& MainControl::operator+=(Participant &participant) {
    if(phase == Registration) {
        if (this->index == this->maxParticipant) {
            return *this;
        }
        for (int i = 0; i < this->index; i++) {
            if (strcmp(participant.state(), (*(this->participants[i])).state()) == 0)
                return *this;
        }
        if (!legalParticipant(participant))
            return *this;

        for (int j = 0; j < this->index; j++) {
            if (compareChars((*(this->participants[j])).state(), participant.state()) > 0) {
                for (int i = this->index; i > j; i--) {
                    this->participants[i] = this->participants[i-1];
                    this->judgeScore[i] = this->judgeScore[i-1];
                    this->regularScore[i] = this->regularScore[i-1];
                    this->judgeVoter[i] = this->judgeVoter[i-1];
                }
                this->participants[j] = &participant;
                this->regularScore[j] = 0;
                this->judgeScore [j] = 0;
                this->judgeVoter[j] = 0;
                this->index++;
                participant.updateRegistered(true);
                return *this;
            }
        }
        this->participants[this->index] = &participant;
        this->regularScore[this->index] = 0;
        this->judgeScore [this->index] = 0;
        this->index++;
        participant.updateRegistered(true);
        return *this;
    }
    return *this;
}
MainControl& MainControl::operator-=(Participant &participant) {
    if(phase == Registration) {
        for (int i = 0; i < this->index; i++) {
            if (strcmp(participant.state(), (*(this->participants[i])).state()) == 0) {
                for (int j = i; j < (this->index) + 1; j++) {
                    this->participants[j] = this->participants[j + 1];
                    this->regularScore[j] = this->regularScore[j + 1];
                    this->judgeScore[j] = this->judgeScore[j + 1];
                    this->judgeVoter[j] = this->judgeVoter[j + 1];
                }
                this->index = this->index - 1;
                this->participants[this->index] = nullptr;
                this->judgeVoter[this->index] = 0;
                this->judgeScore[this->index] = 0;
                this->regularScore[this->index] = 0;
                participant.updateRegistered(false);
                return *this;
            }
        }
    }
    return *this;
}
MainControl& MainControl::operator+=(Vote &vote) {
    if(this->phase == Voting){
        if((*vote.voter).voterType() == Regular){
            if((((*vote.voter).timesOfVotes()) < this->maxVotingTime) && (participate(vote.voting[0]))){
                ++(*(vote.voter));
                this->regularScore[getStatePlace(vote.voting[0], this->participants, this->maxParticipant)] += 1;
            }
        }
        if(((*vote.voter).voterType() == Judge) &&
                     (this->judgeVoter[getStatePlace((*vote.voter).state(), this->participants, this->maxParticipant)] == 0)){
            this->judgeVoter[getStatePlace((*vote.voter).state(), this->participants, this->maxParticipant)] = 1;
            int i = 0;
            while((vote.voting[i] != nullptr) && (strcmp(vote.voting[i], "") != 0) && i < 10){
                int place = getStatePlace(vote.voting[i], this->participants, this->maxParticipant);
                this->judgeScore[place] += votesToScores(i);
                i++;
            }
        }
    }
    return *this;
}
string MainControl::operator()(int num, VoterType voterType) {
    int index = -1;
    if(voterType == Regular){
        index = get(this->regularScore, this->index, num);
    }
    if(voterType == Judge){
        index = get(this->judgeScore, this->index, num);
    }
    if(voterType == All){
        int* allScore = new int[this->index];
        for (int i = 0; i < this->index; ++i) {
            allScore[i] = (this->judgeScore[i]) + (this->regularScore[i]);
        }
        index = get(allScore, this->index, num);
        delete[](allScore);
    }
    if(index == (-1)){
        return "";
    }
    return (this->participants[index]->state());
}
std::ostream& operator<<(std::ostream &os, const MainControl& mainControl){
    os << "{" << std::endl;
    if(mainControl.phase == Voting) {
        os << "Voting" << std::endl;
    }
    if(mainControl.phase == Contest) {
        os << "Contest" << std::endl;
    }
    if(mainControl.phase == Registration) {
        os << "Registration" << std::endl;
    }
    if(mainControl.phase != Voting) {
        for (int i = 0; i < mainControl.index; i++) {
            os << *(mainControl.participants[i]) << std::endl;
        }
        os << "}" << std::endl;
        return os;
    }
    if(mainControl.phase == Voting){
        for (int i = 0; i < mainControl.index; i++) {
            os << (*(mainControl.participants[i])).state();
            os << " : ";
            os << "Regular(" << mainControl.regularScore[i] << ")";
            os << " Judge(" << mainControl.judgeScore[i] << ")" << std::endl;
        }
    }
    os << "}" << std::endl;
    return os;
}

MainControl::Iterator MainControl::begin() {
    Iterator iterator;
    iterator.mainControl = this;
    if(this->participants != nullptr) {
        iterator.pointer = participants[0];
        iterator.index = 0;
    } else{
        iterator.pointer = nullptr;
        iterator.index = -1;
    }
    return iterator;
}
MainControl::Iterator MainControl::end() {
    Iterator iterator;
    iterator.mainControl = this;
    if(this->index != 0) {
        iterator.pointer = participants[this->index - 1];
        iterator.index = this->index - 1;
    } else{
        iterator.pointer = nullptr;
        iterator.index = -1;
    }
    return iterator;
}
MainControl::Iterator::Iterator() {
    this->index = (-1);
    this->pointer = nullptr;
    this->mainControl = nullptr;
}
MainControl::Iterator& MainControl::Iterator::operator++() {
    if(this->index < this->mainControl->index) {
        this->index++;
        this->pointer = this->mainControl->participants[this->index];
        return *this;
    }
    return *this;
}
bool MainControl::Iterator::operator<(Iterator iterator) {
    return (this->index < this->mainControl->index);
}
Participant& MainControl::Iterator::operator*() {
    return *this->pointer;
}
bool MainControl::Iterator::operator==(MainControl::Iterator iterator) {
    return (this->index == this->mainControl->index);
}

// -----------------------------------------------------------

#endif
