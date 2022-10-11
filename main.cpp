#include <iostream>
#include "Sequence.h"

using namespace std;

int main() {
    Sequence Tarea1(1, 1, 1);
    string S1 = Tarea1.GenSequence();
    Tarea1.PrintSequence(S1);

    string MutatedS1 = Tarea1.MutateSequence(S1);
    Tarea1.PrintSequence(MutatedS1);

    cout << "Score: " << Tarea1.NeedlemanWunsch(S1, MutatedS1) << endl;
    return 0;
}