#include <iostream>
#include <vector>
using std::vector;

template<typename Iterator, typename Predicate>
int getNumber(Iterator first, Iterator last, Predicate pred) {
    int count = 0;
    for (first; first != last; ++first) {
        Iterator firstHelp = first;
        ++firstHelp;
        for (firstHelp; firstHelp!=last; ++firstHelp) {
            if (pred(*first, *firstHelp))
                count++;
        }
        if (pred(*first, *firstHelp))
            count++;
    }
    return count;
}

bool isSorted(vector<int> v){
    
}

int main() {

    return 0;
}