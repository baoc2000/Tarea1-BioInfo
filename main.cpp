#include <iostream>
#include <cmath>
#include <numeric>
#include "Sequence.h"
#include "pbPlots.hpp"
#include "supportLib.hpp"

using namespace std;

/*
    Libreria de Plots extraida de:
    https://github.com/InductiveComputerScience/pbPlots/tree/master/Cpp
*/

double VectorMin(vector<double> Data) {
    int pos = 0;
    int i;
    for (i = 1; i < (int)Data.size(); i++) {
        if (Data[i] <= Data[pos])
            pos = i;
    }
    return Data[pos];
}

double VectorMax(vector<double> Data) {
    int pos = 0;
    int i;
    for (i = 1; i < (int)Data.size(); i++) {
        if (Data[i] >= Data[pos])
            pos = i;
    }
    return Data[pos];
}

vector<double> CalculateHistogram(vector<double> Data, int bins) {
    int n = (int)Data.size();
    double min_value = VectorMin(Data);
    double max_value = VectorMax(Data);
    double range = abs(max_value - min_value);
    double width = range / bins;

    vector<double> intervals;
    int i;
    intervals.push_back(min_value);
    for (i = 0; i < bins; i++) {
        intervals.push_back(intervals[i] + width);
    }
    
    vector<double> DataCopy = Data;
    vector<double> Columns(bins);
    int j;
    double value;
    bool set_flag;
    //Contar frecuencias
    while (!DataCopy.empty()) {
        value = DataCopy.back();
        set_flag = false;
        
        for (j = 0; j < (int)intervals.size(); j++) {   
            if (value == max_value) {
                Columns[Columns.size() - 1]++;
                set_flag = true;
                break;
            }      
            if (value >= intervals[j] && value < intervals[j + 1]) {
                Columns[j]++;
                set_flag = true;
                break;
            }
        }
        if(!set_flag)
            Columns[Columns.size() - 1]++;
        DataCopy.pop_back();
    }

    return Columns;
}

vector<double> CalculateHistogramIntervals(vector<double> Data, int bins) {
    int n = (int)Data.size();
    double min_value = VectorMin(Data);
    double max_value = VectorMax(Data);
    double range = abs(max_value - min_value);
    double width = range / bins;

    vector<double> intervals;
    int i;
    intervals.push_back(min_value);
    for (i = 0; i < bins; i++) {
        intervals.push_back(intervals[i] + width);
    }
    return intervals;
}

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
        int i;
        vector<double> X_PB;
        vector<double> Data_PB;

        string S_PB = Tarea1.GenSequence();
        string MutatedS_PB1, MutatedS_PB2;
        for (i = 0; i <= 300; i++) {
            X_PB.push_back((double)i);
            MutatedS_PB1 = Tarea1.MutateSequence(S_PB, i);
            MutatedS_PB2 = Tarea1.MutateSequence(S_PB, i);
            Data_PB.push_back((double)Tarea1.LevenshteinDistance(MutatedS_PB1, MutatedS_PB2));
        }

        //GRAFICO PREGUNTA B
        RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
        StringReference *ErrorMsg = CreateStringReferenceLengthValue(0, L' ');

        ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
        series -> xs = &X_PB;
        series -> ys = &Data_PB;

        ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
        settings -> width = 600;
        settings -> height = 400;
        settings -> title = toVector(L"Pregunta b)");
        settings -> xLabel = toVector(L"Numero de mutaciones M");
        settings -> yLabel = toVector(L"Distancia de Levenshtein D'");
        settings -> scatterPlotSeries -> push_back(series);

        bool success = DrawScatterPlotFromSettings(imageRef, settings, ErrorMsg);
        
        if (success) {
            vector<double> *pngData = ConvertToPNG(imageRef->image);
            WriteToFile(pngData, "./Plots/PreguntaB.png");
            DeleteImage(imageRef->image);
            cout << "Grafico Pregunta b) generado." << endl;
        }
        else {
            cerr << "Error: ";
            for (wchar_t c: *ErrorMsg->string)
                wcerr << c;
            cerr << endl;
        }
        FreeAllocations();
    }
    else if (input.compare("C") == 0) {
        cout << "Ejecutando Pregunta C..." << endl;
        int i;
        vector<string> Secuencias1;
        vector<string> Secuencias2;

        //Generar pares de secuencias
        cout << "Generando Secuencias..." << endl;
        for (i = 0; i < 10000; i++) {
            Secuencias1.push_back(Tarea1.GenSequence());
            Secuencias2.push_back(Tarea1.GenSequence());
        }

        vector<double> Data_PC;
        for (i = 0; i < 10000; i++)
            Data_PC.push_back((double)Tarea1.LevenshteinDistance(Secuencias1[i], Secuencias2[i]));

        int bins = 50;
        vector<double> Columns = CalculateHistogram(Data_PC, bins);
        Columns.push_back(0);
        vector<double> X_PC = CalculateHistogramIntervals(Data_PC, bins);
        for (i = 0; i < (int)Columns.size() - 1; i++) {
            if (Columns[i] == 0) {
                Columns.erase(Columns.begin() + i);
                X_PC.erase(X_PC.begin() + i);
                i = 0;
            }      
        }

        double sum = accumulate(Data_PC.begin(), Data_PC.end(), 0.0);
        double mean = sum / Data_PC.size();
        cout << "Promedio de Distancias: " << mean << endl;

        /*
        Desviacion estandar extraida de 
        https://stackoverflow.com/questions/7616511/calculate-mean-and-standard-deviation-from-a-vector-of-samples-in-c-using-boos
        */
        double sq_sum = inner_product(Data_PC.begin(), Data_PC.end(), Data_PC.begin(), 0.0);
        double std = sqrt(sq_sum / Data_PC.size() - mean * mean);
        cout << "Desviacion Estandar: " << std << endl;
        

        //GRAFICO PREGUNTA C
        RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
        StringReference *ErrorMsg = CreateStringReferenceLengthValue(0, L' ');

        ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
        series -> xs = &X_PC;
        series -> ys = &Columns;

        ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
        settings -> width = 600;
        settings -> height = 400;
        settings -> title = toVector(L"Pregunta c)");
        settings -> xLabel = toVector(L"Distancia de Levenshtein D");
        settings -> yLabel = toVector(L"Frecuencia");
        settings -> scatterPlotSeries -> push_back(series);

        bool success = DrawScatterPlotFromSettings(imageRef, settings, ErrorMsg);
        
        string text1("Prom: ");
        text1 += to_string(mean);
        string text2("DesEst: ");
        text2 += to_string(std);

        wstring wtext1;
        for (i = 0; i < (int)text1.size(); i++)
            wtext1 += wchar_t(text1[i]);
        const wchar_t *wctext1 = wtext1.c_str();

        wstring wtext2;
        for (i = 0; i < (int)text2.size(); i++)
            wtext2 += wchar_t(text2[i]);
        const wchar_t *wctext2 = wtext2.c_str();

        if (success) {
            DrawText(imageRef->image, 10, 10, toVector(wctext1), GetBlack());
            DrawText(imageRef->image, 10, 24, toVector(wctext2), GetBlack());
            vector<double> *pngData = ConvertToPNG(imageRef->image);
            WriteToFile(pngData, "./Plots/PreguntaC.png");
            DeleteImage(imageRef->image);
            cout << "Grafico Pregunta c) generado." << endl;
        }
        else {
            cerr << "Error: ";
            for (wchar_t c: *ErrorMsg->string)
                wcerr << c;
            cerr << endl;
        }
        FreeAllocations();
    }

    return 0;
}