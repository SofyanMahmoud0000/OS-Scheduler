#include <iostream>
#include "Scheduler.h"
#include <random>
#include <chrono>
#include <algorithm>
using namespace std;

int main(int argc , char* argv[])
{
    string Input = "input.txt";
    string Output = argv[1];
    string Algorithm = argv[2];
    int Context = atoi(argv[3]);
    int Quantom = 0;
    if(Algorithm == "RR")
    {
        Quantom = atoi(argv[4]);
    }

    Scheduler S(Input, Algorithm, Context, Quantom);
    S.Write("output.txt");
    S.OutputFile(Output);
    system("python Chart.py");
    return 0; 
}