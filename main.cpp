#include <iostream>
#include "Sequence.h"
#include "pbPlots.hpp"
#include "supportLib.hpp"

using namespace std;

/*
    Libreria de Plots extraida de:
    https://github.com/InductiveComputerScience/pbPlots/tree/master/Cpp
*/

int main() {
    Sequence Tarea1(1, 1, 1);
    
    string input;
    cout << "Ingrese Indice de Pregunta (A, B, C):" << endl;
    cin >> input;

    //PREGUNTA A
    if (input.compare("A") == 0) {
        cout << "Ejecutando Pregunta A..." << endl;
        int i;
        vector<double> X_PA;
        vector<double> Data_PA;
        
        string S_PA = Tarea1.GenSequence();
        string MutatedS_PA;
        for (i = 0; i <= 300; i++) {
            X_PA.push_back((double)i);
            MutatedS_PA = Tarea1.MutateSequence(S_PA, i);
            Data_PA.push_back((double)Tarea1.LevenshteinDistance(S_PA, MutatedS_PA));
        }

        //GRAFICO PREGUNTA A
        RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
        StringReference *ErrorMsg = CreateStringReferenceLengthValue(0, L' ');

        ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
        series -> xs = &X_PA;
        series -> ys = &Data_PA;

        ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
        settings -> width = 600;
        settings -> height = 400;
        settings -> title = toVector(L"Pregunta a)");
        settings -> xLabel = toVector(L"Numero de mutaciones M");
        settings -> yLabel = toVector(L"Distancia de Levenshtein D");
        settings -> scatterPlotSeries -> push_back(series);
        
        bool success = DrawScatterPlotFromSettings(imageRef, settings, ErrorMsg);
        
        if (success) {
            vector<double> *pngData = ConvertToPNG(imageRef->image);
            WriteToFile(pngData, "./Plots/PreguntaA.png");
            DeleteImage(imageRef->image);
            cout << "Grafico Pregunta a) generado." << endl;
        }
        else {
            cerr << "Error: ";
            for (wchar_t c: *ErrorMsg->string)
                wcerr << c;
            cerr << endl;
        }
        FreeAllocations();
    }
    else if (input.compare("B") == 0) {
        cout << "Ejecutando Pregunta B..." << endl;
    }
    else if (input.compare("C") == 0) {
        cout << "Ejecutando Pregunta C..." << endl;
    }

    return 0;
}