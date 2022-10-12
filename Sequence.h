#ifndef UTILS_T1
#define UTILS_T1

#include <string>
#include <vector>

#define MAX_N 200

using namespace std;

class Sequence {
    private:
        int match_score;
        int mismatch_score;
        int gap_score;
    
    public:
        Sequence(int, int, int);
        ~Sequence();
        string GenSequence();
        void PrintSequence(string);
        string MutateSequence(string, int, bool = false);
        string MutateSequenceOnce(string, bool = false);
        int LevenshteinDistance(string, string);
        int NeedlemanWunsch(string, string);
};

#endif