
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "eurovision.h"
using std::vector;
using std::string;
using std::list;

//---------------------------------------------------

int votesToScores(int place) {
    switch (place) {
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
int getMaxIndex(const int* array, int length, int index, int num) {
    int count = 0;
    for (int k = 0; k < length; ++k) {
        if (array[k] > index) {
            count++;
        }
    }
    int j = 0;
    num = num - count;
    for (int i = length - 1; i >= 0; i--) {
        if (array[i] == index) {
            num--;
            j = i;
            if (num == 0) {
                break;
            }
        }
    }
    return j;
}

Participant::Participant(const string& stateName, const string& songName, int songTimeLength, const string& singerName, bool isSingerRegistered) {
    this->songTimeLength = songTimeLength;
    this->stateName = stateName;
    this->singerName = singerName;
    this->songName = songName;
    this->isSingerRegistered = isSingerRegistered;
}
const string Participant::song() {
    return this->songName;
}
const string Participant::state() {
    return this->stateName;
}
const string Participant::singer() {
    return this->singerName;
}
int Participant::timeLength() {
    return this->songTimeLength;
}
bool Participant::isRegistered() {
    return this->isSingerRegistered;
}
void Participant::update(const string& songName, int songTimeLength, const string& singerName) {
    if (!this->isRegistered()) {
        if (!singerName.empty()) {
            this->singerName = singerName;
        }
        if (!songName.empty()) {
            this->songName = songName;
        }
        if (songTimeLength != 0) {
            this->songTimeLength = songTimeLength;
        }
    }
}
void Participant::updateRegistered(bool isSingerRegistered) {
    this->isSingerRegistered = isSingerRegistered;
}
std::ostream& operator<<(std::ostream &os, Participant& participant) {
    os << "[" << participant.state() << '/' << participant.song() << '/' << participant.timeLength() << '/' << participant.singer() << "]";
    return os;
}

int getStatePlace(const string& stateName, Participant** states, int length) {
    for (int i = 0; i < length; ++i) {
        if ((*(states[i])).state() == stateName) {
            return i;
        }
    }
    return (-1);
}

//---------------------------------------------------

Voter::Voter(const string& stateName, VoterType voterType, int votingTime) {
    this->stateName = stateName;
    this->voter_type = voterType;
    this->votingTime = votingTime;
}
string Voter::state() {
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
std::ostream& operator<<(std::ostream &os, Voter& voter) {
    if (voter.voterType() == Regular) {
        os << "<" << voter.state() << '/' << "Regular>";
        return os;
    }
    os << "<" << voter.state() << '/' << "Judge>";
    return os;
}

// -----------------------------------------------------------

void fill(const string& stateName, const string& state, int index, string* array){
    if ((stateName == state) || ((stateName.empty()))) {
        array[index] = "";
    }
    else{
        array[index] = stateName;
    }
}

Vote::Vote(Voter &voter, const string& stateName1, const string& stateName2, const string& stateName3,
           const string& stateName4, const string& stateName5, const string& stateName6, const string& stateName7,
           const string& stateName8, const string& stateName9, const string& stateName10) {
    if (voter.voterType() == Judge) {
        this->voter = &voter;
        this->voting = new string[10];
        fill(stateName1, voter.state(), 0, this->voting);
        fill(stateName2, voter.state(), 1, this->voting);
        fill(stateName3, voter.state(), 2, this->voting);
        fill(stateName4, voter.state(), 3, this->voting);
        fill(stateName5, voter.state(), 4, this->voting);
        fill(stateName6, voter.state(), 5, this->voting);
        fill(stateName7, voter.state(), 6, this->voting);
        fill(stateName8, voter.state(), 7, this->voting);
        fill(stateName9, voter.state(), 8, this->voting);
        fill(stateName10, voter.state(), 9, this->voting);
    }
    if ((voter.voterType() == Regular)) {
        this->voter = &voter;
        this->voting = new string[1];
        if ((voter.state() == stateName1) || (stateName1.empty())) {
            this->voting[0] = "";
        }
        else {
            this->voting[0] = stateName1;
        }
    }
}
Vote::~Vote() {
    delete[](this->voting);
}

// -----------------------------------------------------------

MainControl::MainControl(int maxTimeLength, int maxParticipant, int maxVotingTime, Phase phase) {
    this->maxParticipant = maxParticipant;
    this->phase = phase;
    this->maxSongTimeLength = maxTimeLength;
    this->maxVotingTime = maxVotingTime;
    this->index = 0;
    this->participants = new Participant*[maxParticipant];
    this->regularScore = new int[maxParticipant];
    this->judgeScore = new int[maxParticipant];
    for (int i = 0; i < maxParticipant; i++) {
        this->participants[i] = nullptr;
        this->regularScore[i] = 0;
        this->judgeScore[i] = 0;
    }
}
MainControl::~MainControl() {
    for (int i = 0; i < this->index; ++i) {
        this->participants[i]->updateRegistered(false);
    }
    delete[](this->participants);
    delete[](this->judgeScore);
    delete[](this->regularScore);
}
void MainControl::setPhase(Phase phase) {
    if((this->phase == Registration) && (phase == Contest)) {
        this->phase = phase;
    }
    if((this->phase == Contest) && (phase == Voting)) {
        this->phase = phase;
    }
}
bool MainControl::participate(const string& stateName) {
    for (int i = 0; i < this->index; i++) {
        if ((!((*this->participants[i]).state()).empty()) && (!stateName.empty()) && ((*(this->participants[i])).state() == stateName)) {
            return true;
        }
    }
    return false;
}
bool MainControl::legalParticipant(Participant &participant) {
    if ((participant.state()).empty())
        return false;
    if ((participant.singer()).empty())
        return false;
    if ((participant.song()).empty())
        return false;
    return (participant.timeLength() <= this->maxSongTimeLength);
}
MainControl& MainControl::operator+=(Participant &participant) {
    if (phase == Registration) {
        if(participant.isRegistered()){
            return *this;
        }
        if (this->index == this->maxParticipant) {
            return *this;
        }
        for (int i = 0; i < this->index; i++) {
            if (participant.state() == (*(this->participants[i])).state())
                return *this;
        }
        if (!legalParticipant(participant))
            return *this;

        for (int j = 0; j < this->index; j++) {
            if ((*(this->participants[j])).state() > participant.state()) {
                for (int i = this->index; i > j; i--) {
                    this->participants[i] = this->participants[i - 1];
                    this->judgeScore[i] = this->judgeScore[i - 1];
                    this->regularScore[i] = this->regularScore[i - 1];
                }
                this->participants[j] = &participant;
                this->regularScore[j] = 0;
                this->judgeScore[j] = 0;
                this->index++;
                participant.updateRegistered(true);
                return *this;
            }
        }
        this->participants[this->index] = &participant;
        this->regularScore[this->index] = 0;
        this->judgeScore[this->index] = 0;
        this->index++;
        participant.updateRegistered(true);
        return *this;
    }
    return *this;
}
MainControl& MainControl::operator-=(Participant &participant) {
    if (phase == Registration) {
        if(!participant.isRegistered()){
            return *this;
        }
        for (int i = 0; i < this->index; i++) {
            if ((participant.state() == (*(this->participants[i])).state())) {
                for (int j = i; j < (this->index) - 1; j++) {
                    this->participants[j] = this->participants[j + 1];
                    this->regularScore[j] = this->regularScore[j + 1];
                    this->judgeScore[j] = this->judgeScore[j + 1];
                }
                this->index = this->index - 1;
                this->participants[this->index] = nullptr;
                this->judgeScore[this->index] = 0;
                this->regularScore[this->index] = 0;
                participant.updateRegistered(false);
                return *this;
            }
        }
    }
    return *this;
}
MainControl& MainControl::operator+=(const Vote& vote) {
    if (this->phase == Voting) {
        if ((*(vote.voter)).voterType() == Regular) {
            if ((((*(vote.voter)).timesOfVotes()) < this->maxVotingTime) && (participate(vote.voting[0])) && (participate((vote.voter)->state()))) {
                int j = getStatePlace(vote.voting[0], this->participants, this->index);
                if (j != (-1)) {
                    this->regularScore[j] += 1;
                    ++(*(vote.voter));
                }
            }
        }
        if ((*(vote.voter)).voterType() == Judge) {
            if((participate(vote.voter->state())) && ((*vote.voter).timesOfVotes() == 0)) {
                int i = 0;
                while (i < 10) {
                    if((vote.voting[i]).empty()){
                        i++;
                        continue;
                    }
                    int place = getStatePlace(vote.voting[i], this->participants, this->index);
                    if (place != (-1)) {
                        this->judgeScore[place] += votesToScores(i);
                        if((vote.voter)->timesOfVotes() == 0){
                            ++(*vote.voter);
                        }
                    }
                    i++;
                }
            }
        }
    }
    return *this;
}
string MainControl::operator()(int num, VoterType voterType) {
    vector<int> vector1;
    vector<int>::iterator index;
    int j = 0;
    if(voterType == Regular){
        for (int i = 0; i < this->index; ++i) {
            vector1.push_back(this->regularScore[i]);
        }
        index = get(vector1.begin(), vector1.end(), num);
        if(index == vector1.end()){
            return "";
        }
        j = getMaxIndex(this->regularScore, this->index, *index, num);
    }
    if(voterType == Judge){
        for (int i = 0; i < this->index; ++i) {
            vector1.push_back(this->judgeScore[i]);
        }
        index = get(vector1.begin(), vector1.end(), num);
        if(index == vector1.end()){
            return "";
        }
        j = getMaxIndex(this->judgeScore, this->index, *index, num);
    }
    if(voterType == All){
        int* allScore = new int[this->index];
        for (int i = 0; i < this->index; ++i) {
            allScore[i] = ((this->regularScore[i]) + (this->judgeScore[i]));
        }
        for (int i = 0; i < this->index; ++i) {
            vector1.push_back(allScore[i]);
        }
        index = get(vector1.begin(), vector1.end(), num);
        if(index == vector1.end()){
            return "";
        }
        j = getMaxIndex(allScore, this->index, *index, num);
        delete[]allScore;
    }
    return(this->participants[j]->state());
}
std::ostream& operator<<(std::ostream &os, const MainControl& mainControl) {
    os << "{" << std::endl;
    if (mainControl.phase == Voting) {
        os << "Voting" << std::endl;
    }
    if (mainControl.phase == Contest) {
        os << "Contest" << std::endl;
    }
    if (mainControl.phase == Registration) {
        os << "Registration" << std::endl;
    }
    if (mainControl.phase == Registration) {
        for (int i = 0; i < mainControl.index; i++) {
            os << *(mainControl.participants[i]) << std::endl;
        }
        os << "}" << std::endl;
        return os;
    }
    if (mainControl.phase == Voting) {
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
    if (this->participants != nullptr) {
        iterator.pointer = participants[0];
        iterator.index = 0;
    }
    else {
        iterator.pointer = nullptr;
        iterator.index = -1;
    }
    return iterator;
}
MainControl::Iterator MainControl::end() {
    Iterator iterator;
    iterator.mainControl = this;
    if (this->index != 0) {
        iterator.pointer = participants[this->index - 1];
        iterator.index = this->index;
    }
    else {
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
    if (this->index < this->mainControl->index) {
        this->index++;
        this->pointer = this->mainControl->participants[this->index];
        return *this;
    }
    return *this;
}
bool MainControl::Iterator::operator<(Iterator iterator) {
    return (this->index < iterator.index);
}
Participant& MainControl::Iterator::operator*() {
    return *this->pointer;
}
bool MainControl::Iterator::operator==(MainControl::Iterator iterator) {
    return (this->index == iterator.index);
}

// -----------------------------------------------------------
