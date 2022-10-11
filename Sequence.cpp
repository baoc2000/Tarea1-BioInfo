#include <ctime>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include "Sequence.h"

using namespace std;

static const char alfabeto[] = 
    "ACGTBD";

Sequence::Sequence(int ms, int mms, int gs) {
    match_score = ms;
    mismatch_score = mms;
    gap_score = gs;

    srand((unsigned)time(NULL) * getpid());
}

Sequence::~Sequence() {}

string Sequence::GenSequence() {
/*
    Codigo de generacion de strings extraido de:
    https://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
*/
    cout << "Generando secuencia..." << endl << endl;

    string temp_s;
    temp_s.reserve(MAX_N);

    int i;
    for (i = 0; i < MAX_N; i++) {
        temp_s += alfabeto[rand() % (sizeof(alfabeto) - 1)];
    }

    return temp_s;
}

void Sequence::PrintSequence(string S) {
    cout << "Secuencia:" << endl;
    int i, j, k;
    for (i = 0; i < (int)S.size(); i += 50) {
        try {
            for (j = 0; j < 4; j++) {
                cout << S.substr(i + j * 10, 10) << " ";
            }
            cout << S.substr(i + j * 10, 10) << endl;
        }    
        catch(const out_of_range& e) {}
    }
    cout << endl;
}

string Sequence::MutateSequence(string S, bool verbose) {
    int M = rand() % (MAX_MUTATIONS + 1);

    cout << "Cantidad de Mutaciones: " << M << endl << endl;

    int i, j;
    int pos, mutation;
    string MutatedS = S;
    string new_letter;
    string replace_alfabet;
    for (i = 0; i < M; i++) {
        mutation = rand() % 3; //0 - Insercion, 1 - Borrado, 2 - Reemplazo
        pos = rand() % MutatedS.size();

        switch (mutation) {
        case 0:
            // Insercion
            new_letter.push_back(alfabeto[rand() % (sizeof(alfabeto) - 1)]);

            if (verbose) cout << "Insercion de " << new_letter << " en posicion " << pos << endl;
            MutatedS.insert(pos, new_letter);

            new_letter.clear();
            break;
        
        case 1:
            // Borrado
            if (verbose) cout << "Borrado de " << MutatedS.at(pos) << " en posicion " << pos << endl;
            MutatedS.erase(pos, 1);
            break;
        
        case 2:
            //Reemplazo
            for (j = 0; j < 6; j++) {
                if (alfabeto[j] != MutatedS.at(pos)) {
                    replace_alfabet.push_back(alfabeto[j]);
                }
            }
            new_letter.push_back(replace_alfabet.at(rand() % replace_alfabet.size()));

            if (verbose) 
                cout << "Reemplazo de " << MutatedS.at(pos) << " por " << new_letter << " en posicion " << pos << endl;
            MutatedS.replace(pos, 1, new_letter);

            new_letter.clear();
            replace_alfabet.clear();
            break;
        
        default:
            break;
        }
    }

    return MutatedS;
}

int Sequence::LevenshteinDistance(string S1, string S2) {
/*
    Codigo de Distancia de Levenshtein extraido de:
    https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C++
*/
    return 0;
}

int Sequence::NeedlemanWunsch(string S1, string S2) {
/*
    Codigo de Needleman-Wunsch extraido de:
    https://github.com/ldfaiztt/Algorithms-2/blob/master/Dynamic%20Programming/Needleman-Wunsch.cpp
    apoyado de:
    https://en.wikipedia.org/wiki/Needleman%E2%80%93Wunsch_algorithm
*/

    int **dp;
    int len1 = (int)S1.size();
    int len2 = (int)S2.size();
    int Max_length = (len1 >= len2) ? len1 : len2;

    int i, j;
    dp = (int **)malloc((Max_length + 1) * sizeof(int *));
    for (i = 0; i <= Max_length; i++)
        dp[i] = (int *)malloc((Max_length + 1) * sizeof(int));

    for (i = 0; i <= len1; i++) dp[i][0] = i * -gap_score;
    for (i = 0; i <= len2; i++) dp[0][i] = i * -gap_score;

    for (i = 1; i <= len1; i++) {
        for (j = 1; j <= len2; j++) {
            int S = (S1[i - 1] == S2[j - 1]) ? match_score : -mismatch_score;
            dp[i][j] = max(
                    dp[i - 1][j - 1] + S,
                max(dp[i - 1][j] - gap_score, 
                    dp[i][j - 1] - gap_score
            ));
        }
    }

    int final_score = dp[len1][len2];

    for (i = 0; i <= Max_length; i++)
        free(dp[i]);
    free(dp);

    return final_score;
}