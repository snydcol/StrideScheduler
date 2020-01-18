//Name: Colby Snyder 
//Date: 11/7/19 
//Program: An implementation of Stride Scheduling 
#include <stdlib.h>
#include<limits.h>
#include<stdio.h>

struct Process{
  int priority;
  int quantums;
  int id;
  float meter;
}typedef Process;

int main(int argc, char *argv[] ){
  int numProcesses = (argc-1) / 2;
  int totalQuantums = 0;
  //Create an array for the processes
  Process ProcessArr[numProcesses];

  //Check if the right number of args were provided
  if(!(argc % 2)){
    printf("Wrong number of arguments\n");
    return -1;
  }
  //Creating an array of Processes
  for(int i=1; i<argc; i+=2){
    int priority = atoi(argv[i]);
    int quantums = atoi(argv[i+1]);
    totalQuantums += quantums;
    //Create a new Process and store it in the array
    Process n = {priority, quantums,(i/2)+1, 0};
    ProcessArr[i/2] = n;   
  }

  for(int j=0; j<totalQuantums; j++){
    //Create a template process that will be compared to all processes in the array 
    Process b = {INT_MAX, INT_MAX, INT_MAX, INT_MAX};
    Process *best = &b;
    //Loop through the array of Processes and find the one with the lowest meter
    for(int i=0; i<numProcesses; i++){
      //Check to see if process has a lower meter then our best process
      if(ProcessArr[i].meter < best->meter && ProcessArr[i].quantums !=0){  
        best=&ProcessArr[i];
      }else if(ProcessArr[i].meter == best->meter && ProcessArr[i].quantums !=0){
        //Meters are equal find the one with highest priority
        if(ProcessArr[i].priority > best->priority){  
          best=&ProcessArr[i]; 
        
        //Priorities are equal find the one with lowest Id    
        }else if(ProcessArr[i].priority == best->priority && ProcessArr[i].id < best->id){
            best=&ProcessArr[i];
        }
      }
    }
    //Add to the meter and decrease the quantums of the scheduled process
    best->meter += 1.0/(float)best->priority;
    best->quantums--;
    printf("%d\n",best->id);
  }
}
