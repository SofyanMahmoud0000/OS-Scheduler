#include <iostream>
#include "Scheduler.h"
#include <string>
#include <fstream>
#include <random>
#include <chrono>
#include <algorithm>
#include <bits/stdc++.h> 

using namespace std;

Scheduler::Scheduler(string Input , string Algorithm , int Context , int Quantom)
{
    this->Quantom = Quantom;
    this->Context = Context;
    this->CurrentProcess = 0;
    this->CurrentTime = 0;
    ifstream File;
    File.open(Input);
    if (!File)
        return;
    
    int count = 0;
    ProcessInformation temp;
    float x;
    int i = 0;
    while (File >> x) 
    {
        switch(count)
        {
            case(0):
                temp.ProcessId = x;
            break;

            case(1):
                temp.ArrivalTime = x;
            break;

            case(2):
                temp.BurstTime = x;
                temp.RemainingTime = x;
            break;

            case(3):
                temp.Piority = x;
            break;
        }
        
        
        count++;
        if(count == 4)
        {
            this->MyProcesses.push_back(temp);
            count = 0;
        }
    }

    
    cout << endl<<endl;
    if(Algorithm == "HPF")
        this->HPF();
    else if(Algorithm == "FCFS")
        this->FCFS();
    else if(Algorithm == "RR")
        this->RR();
    else if(Algorithm == "SRTN")
        this->SRTN(); 
}

void Scheduler::Write(string Output)
{
    ofstream File;
    File.open(Output);
    for (int i = 0; i < this->Graph.size(); i++)
    {
        if(i != Graph.size()-1)
            File << this->Graph[i].Start << " " << this->Graph[i].Start << " "<<this->Graph[i].End << " " << this->Graph[i].End << " ";
        else File << this->Graph[i].Start << " " << this->Graph[i].Start << " "<<this->Graph[i].End << " " << this->Graph[i].End;

    }
    File << endl;
    File << 0 << " ";
    for (int i = 0 ; i < this->Graph.size() ; i++)
    {
        if(i != Graph.size()-1)
            File << this->Graph[i].ProcessId << " " << this->Graph[i].ProcessId << " "<< 0 << " " << 0 << " ";
        else 
            File << this->Graph[i].ProcessId << " " << this->Graph[i].ProcessId;
    }
    File <<" "<< 0 << " ";
    File.close();
}

void Scheduler::HPF()
{
    Sort("HPF");
    while(this->MyProcesses.size()!=0)
    {
        if(MyProcesses[0].ArrivalTime > this->CurrentTime)
            this->CurrentTime++;
        else
        {
            outGraph temp;
            OutputInformation temp2;
            temp.Start = this->CurrentTime;
            temp.End = this->CurrentTime + this->MyProcesses[0].BurstTime;
            temp.ProcessId = this->MyProcesses[0].ProcessId;
            this->CurrentTime = temp.End;
            this->CurrentTime+=this->Context;

            temp2.ProcessId = this->MyProcesses[0].ProcessId;
            temp2.Turnaround = temp.End - this->MyProcesses[0].ArrivalTime;
            temp2.Wait = temp.Start - this->MyProcesses[0].ArrivalTime; 
            temp2.WeightedTurn = temp2.Turnaround / this->MyProcesses[0].BurstTime;
            this->OutPut.push_back(temp2);
        
            this->Graph.push_back(temp);

            this->MyProcesses.erase(this->MyProcesses.begin());

        }
    }
}
void Scheduler::FCFS()
{     
    Sort("FCFS");
    while(this->MyProcesses.size()!=0)
    {
        if(MyProcesses[0].ArrivalTime > this->CurrentTime)
            this->CurrentTime++;
        else
        {
            outGraph temp;
            OutputInformation temp2;

            temp.Start = this->CurrentTime;
            temp.End = this->CurrentTime + this->MyProcesses[0].BurstTime;
            temp.ProcessId = this->MyProcesses[0].ProcessId;
            this->CurrentTime = temp.End;
            this->CurrentTime+=this->Context;

            temp2.ProcessId = this->MyProcesses[0].ProcessId;
            temp2.Turnaround = temp.End - this->MyProcesses[0].ArrivalTime;
            temp2.Wait = temp.Start - this->MyProcesses[0].ArrivalTime; 
            temp2.WeightedTurn = (float)temp2.Turnaround / this->MyProcesses[0].BurstTime;
            this->OutPut.push_back(temp2);
        
            this->Graph.push_back(temp);

            this->MyProcesses.erase(this->MyProcesses.begin());
        }
    }
}     
void Scheduler::RR()
{
    Sort("FCFS");
    const int size = this->MyProcesses.size(); 
    vector<float>Arr(size);

    for (int i = 0; i < size; i++)
        Arr[i] = this->MyProcesses[i].BurstTime;
    
    while(this->MyProcesses.size()!=0)
    {
        if(MyProcesses[this->CurrentProcess].ArrivalTime > this->CurrentTime)
            this->CurrentTime++;
        else
        {
            outGraph temp;
            OutputInformation temp2;

            temp.Start = this->CurrentTime;
            if(this->MyProcesses[this->CurrentProcess].BurstTime > this->Quantom)
            {
                this->CurrentTime+=Quantom;
                this->MyProcesses[this->CurrentProcess].BurstTime-=this->Quantom;
                temp.End = this->CurrentTime;
                this->Graph.push_back(temp);
            }
            else
            {
                this->CurrentTime += this->MyProcesses[this->CurrentProcess].BurstTime;
                temp2.ProcessId = this->MyProcesses[this->CurrentProcess].ProcessId;
                temp2.Turnaround = this->CurrentTime - this->MyProcesses[this->CurrentProcess].ArrivalTime;
                temp2.WeightedTurn = temp2.Turnaround / Arr[this->CurrentProcess];
                temp2.Wait = this->CurrentTime - (this->MyProcesses[this->CurrentProcess].ArrivalTime + Arr[this->CurrentProcess] );
                this->OutPut.push_back(temp2);
                this->MyProcesses.erase(this->MyProcesses.begin()+this->CurrentProcess);

                if(this->MyProcesses.size() == 0)
                    return;
            }
            this->CurrentTime+=this->Context;
            if(this->CurrentProcess == this->MyProcesses.size()-1)
                this->CurrentProcess = 0;
            else
            {
                if(this->MyProcesses[this->CurrentProcess+1].ArrivalTime > this->CurrentTime)
                    this->CurrentProcess = 0;
                else
                    this->CurrentProcess++;
                
            }
        }
    }
}
void Scheduler::SRTN()
{
    Sort("Remain");
    while(this->MyProcesses.size()!=0)
    {
        if(MyProcesses[this->CurrentProcess].ArrivalTime > this->CurrentTime)
            this->CurrentProcess++;
        else
        {
            outGraph temp;
            OutputInformation temp2;

            temp.Start = this->CurrentTime;
            this->CurrentTime++;
            float Remain = --this->MyProcesses[this->CurrentProcess].RemainingTime;

            while(!this->Check(Remain) && this->MyProcesses[this->CurrentProcess].RemainingTime > 1)
            {
                this->CurrentTime++;
                Remain = --this->MyProcesses[this->CurrentProcess].RemainingTime;
            }

            if(this->MyProcesses[this->CurrentProcess].RemainingTime <= 1)
            {
                this->CurrentTime += this->MyProcesses[this->CurrentProcess].RemainingTime;

                temp.End = this->CurrentTime;
                temp.ProcessId = this->MyProcesses[this->CurrentProcess].ProcessId;
                this->Graph.push_back(temp);

                temp2.ProcessId = this->MyProcesses[this->CurrentProcess].ProcessId;
                temp2.Turnaround = this->CurrentTime - this->MyProcesses[this->CurrentProcess].ArrivalTime;
                temp2.Wait = this->CurrentTime - (this->MyProcesses[this->CurrentProcess].BurstTime + this->MyProcesses[this->CurrentProcess].ArrivalTime); 
                temp2.WeightedTurn = temp2.Turnaround / this->MyProcesses[this->CurrentProcess].BurstTime;
                this->OutPut.push_back(temp2);
                this->MyProcesses.erase(this->MyProcesses.begin()+this->CurrentProcess);


                temp.Start = this->CurrentTime;
                
                this->CurrentTime+=this->Context;

                temp.End = this->CurrentTime;
                temp.ProcessId = .1;
                this->Graph.push_back(temp);

                this->CurrentProcess = 0;
            }
            else
            {
                temp.End = this->CurrentTime;
                temp.ProcessId = this->MyProcesses[this->CurrentProcess].ProcessId;
                this->Graph.push_back(temp);

                Sort("Remain");
                this->CurrentProcess = 0;
                temp.Start = this->CurrentTime;
                
                this->CurrentTime+=this->Context;

                temp.End = this->CurrentTime;
                temp.ProcessId = .1;
                this->Graph.push_back(temp);
                // continue;
            }
        }
        if(this->CurrentProcess == this->MyProcesses.size())
        {
            this->CurrentProcess = 0;
            this->CurrentTime++;
        }
    }
}

bool Scheduler::Check(float RemainingTime)
{
    for (int i = 0; i < this->MyProcesses.size(); i++)
    {
        if(this->CurrentProcess != i && this->MyProcesses[i].RemainingTime < RemainingTime && this->MyProcesses[i].ArrivalTime <= this->CurrentTime)
            return true;
    }
    return false;
    
}


void Scheduler::Sort(string S)
{
    ProcessInformation key;
    int i, j;  
    for (i = 1; i < this->MyProcesses.size(); i++) 
    {  
        key = this->MyProcesses[i];  
        j = i - 1;  

        if(S == "FCFS")
        {
            while (j >= 0 && this->MyProcesses[j].ArrivalTime > key.ArrivalTime) 
            {  
                this->MyProcesses[j + 1] = this->MyProcesses[j];  
                j = j - 1;  
            }  
            this->MyProcesses[j + 1] = key; 
        }
        else if(S == "HPF")
        {
            while (j >= 0 && this->MyProcesses[j].Piority > key.Piority) 
            {  
                this->MyProcesses[j + 1] = this->MyProcesses[j];  
                j = j - 1;  
            }  
            this->MyProcesses[j + 1] = key; 
        }
        else if(S == "Remain")
        {
            while (j >= 0 && this->MyProcesses[j].RemainingTime > key.RemainingTime) 
            {  
                this->MyProcesses[j + 1] = this->MyProcesses[j];  
                j = j - 1;  
            }  
            this->MyProcesses[j + 1] = key; 
        }
    }  
}

void Scheduler::Test()
{

    // for (int i = 0; i < this->MyProcesses.size(); i++)
    // {
    //     cout << MyProcesses[i].ProcessId <<" "<<MyProcesses[i].ArrivalTime<<" "<<MyProcesses[i].BurstTime<<" "<<MyProcesses[i].Piority<<endl;
    // }   

    for (int i = 0; i < this->Graph.size(); i++)
    {
        cout << Graph[i].Start <<" "<<Graph[i].End<<endl;
    }
    
}

void Scheduler::OutputFile(string SS)
{
    OutputInformation key;
    int i, j;  
    for (i = 1; i < this->OutPut.size(); i++) 
    {  
        key = this->OutPut[i];  
        j = i - 1;  

        while (j >= 0 && this->OutPut[j].ProcessId > key.ProcessId) 
        {  
            this->OutPut[j + 1] = this->OutPut[j];  
            j = j - 1;  
        }  
        this->OutPut[j + 1] = key; 
    }  

    float AverageWeight = 0;
    float AverageTurnaroundTime = 0;
    ofstream File;
    File.open(SS);
    for (int i = 0; i < OutPut.size(); i++)
    {
        AverageTurnaroundTime+= OutPut[i].Turnaround;
        AverageWeight+= OutPut[i].WeightedTurn;
        File << OutPut[i].ProcessId << " " << OutPut[i].Turnaround << " " << OutPut[i].WeightedTurn<< " "<<OutPut[i].Wait<<endl;
    }
    File<< "The average weight turnaround time is: " <<AverageWeight/OutPut.size()<<endl;
    File<< "The average turnaround time is: " <<AverageTurnaroundTime/OutPut.size()<<endl;
    File.close();
}




