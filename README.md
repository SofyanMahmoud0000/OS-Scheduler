# OS Scheduler
produces the schedules for the current process in the system based on the chosen algorithm
> The available algorithms: FCFS, HPF, RR, SRTN

## Getting started 
* Clone the repo 
* Create input file 
    * The structure for the input file is showen below 
* Running the code 
    * There will be some inputs during the running in the following order:
        * Name of output file, Algorithm, Context switch, Quantom -in case of **RR** Algorithm-

    * Example:

    ```bash
        ./a.out OutputData.txt FCFS 1
    ``` 

* Get the result and Enjoy !!!

## Inputs 
* The structure of the input file is: 
    * Each line contains the parameters for one process only, separated by a white space, in the     following order:
        * process number, arrival time, burst time andpriority.

* Example:

    ![Example of input file](https://github.com/sofyanmahmoud0000/OS-Scheduler/blob/master/Input.png)

## Output
* The output will be 
    * a text file containing the following metrics for the generated schedule: 
        * Waiting time of each process.
        * Turnaround time of each process.
        * Weighted Turnaround time of each process.
        * Average Turnaround time of the schedule.
        * Average Weighted turnaround time of the schedule.

        * Example:

            ![Example of output file](https://github.com/sofyanmahmoud0000/OS-Scheduler/blob/master/Output.png)

    * A visual graph that shows the generated schedule.

        * Example 

            ![Example of output file](https://github.com/sofyanmahmoud0000/OS-Scheduler/blob/master/Graph.png)

## Build with 
* [C++](https://www.python.org/download/releases/3.0/) - Language used for scheduler
* [Python](https://jupyter.org/) - Language used for chart

## Development and support 
If you have any questions on how to use this scheduler, or have ideas for future development, please send me an e-mail to sofyan1020@gmail.com.

## Authors 
[Sofyan Mahmoud](https://github.com/sofyanmahmoud0000) - Computer engineer

## Licence 
MIT