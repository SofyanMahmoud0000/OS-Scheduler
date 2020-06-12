#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include <string>
#include <vector>
#include <random>
using namespace std;

struct ProcessInformation{
    float ArrivalTime;
    float Piority;
    float BurstTime;
    float RemainingTime;
    int ProcessId;
};


struct OutputInformation{
    float Turnaround;
    float WeightedTurn;
    int ProcessId;
    float Wait;
};

struct outGraph
{
    float ProcessId;
    float Start;
    float End;
};



class Scheduler
{
private:
    vector<ProcessInformation> MyProcesses;
    vector<outGraph>Graph;
    vector<OutputInformation>OutPut;
    float CurrentTime;
    int CurrentProcess;
    int Context;
    int Quantom;

public:
    Scheduler(string , string , int , int = 0);
    void FCFS();
    void HPF();
    void RR();
    void SRTN();
    void Write(string);
    void Sort(string);
    bool Check(float);
    void OutputFile(string);
    void Test();
};


#endif