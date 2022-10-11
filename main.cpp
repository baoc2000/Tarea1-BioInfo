#include <iostream>
#include "Sequence.h"

using namespace std;

int main() {
    Sequence Tarea1(2, 1, 1);
    string S1 = Tarea1.GenSequence();
    Tarea1.PrintSequence(S1);

    string MutatedS1 = Tarea1.MutateSequence(S1);
    Tarea1.PrintSequence(MutatedS1);
    return 0;
}