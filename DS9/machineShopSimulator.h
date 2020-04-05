#pragma once
#ifndef _MACHINESHOPSIMULATOR_H
#define _MACHINESHOPSIMULATOR_H
#include "arrayQueue.h"
#include <exception>
#include <string>

struct task {
	int machine;
	int time;
	//Exercise 34
	int waitTime;//time to wait before schedule this task
	int toWait;//time to count the time to wait
	task(int theMachine = 0, int theTime = 0/*Exercise 34*/,int theWaitTime=0) 
		:machine(theMachine), time(theTime),waitTime(theWaitTime), toWait(theWaitTime) {}
};

struct job {
	arrayQueue<task> taskQ;
	int length;
	int arrivalTime;
	int id;
	//Exercise 35
	int createTime;

	job(int theId = 0, int theCreateTime = 0) :id(theId), length(0), arrivalTime(theCreateTime), createTime(theCreateTime) {}

	void addTask(int theMachine, int theTime) {	taskQ.push(task(theMachine, theTime)); }
	//Exercise 34
	void addTask(int theMachine, int theTime, int theWaitTime) { taskQ.push(task(theMachine, theTime, theWaitTime)); }
	int removeNextTask() {
		int theTime = taskQ.front().time;
		taskQ.pop();
		length += theTime;
		return theTime;
	}
};

struct machine {
	arrayQueue<job*> jobQ;
	
	int changeTime;
	int totalWait;
	int numTasks;
	job* activeJob;

	machine():totalWait(0), numTasks(0), activeJob(nullptr) {}
};

class eventList {
public:
	eventList(int theNumMachines, int theLargeTime) {
		if (theNumMachines < 1)
			throw std::invalid_argument("number of machines must be >= 1");
		numMachines = theNumMachines;
		finishTime = new int[numMachines + 1];

		for (int i = 1; i <= numMachines; ++i) {
			finishTime[i] = theLargeTime;
		}
	}
	
	int nextEventMachine() {
		int p = 1;
		int t = finishTime[1];
		for (int i = 2; i <= numMachines; ++i) {
			if (finishTime[i] < t) {
				p = i;
				t = finishTime[i];
			}
		}
		return p;
	}

	int nextEventTime(int theMachine) {
		return finishTime[theMachine];
	}

	void setFinishTime(int theMachine, int theTime) {
		finishTime[theMachine] = theTime;
	}

private:
	int* finishTime;
	int numMachines;
};

class machineShopSimulator {
public:
	machineShopSimulator(int theNumMachines, int theNumJobs, int theEndTime = 10000):numMachines(theNumMachines),numJobs(theNumJobs), endTime(theEndTime){
		eList = new eventList(numMachines, largeTime);
		mArray = new machine[numMachines + 1];
	}
	void inputData(std::string changeTimeStr, std::string taskStr);
	void startShop();
	void simulate();
	void outputStatistics();
private:
	job* changeState(int theMachine);
	bool moveToNextMachine(job* theJob);

	int timeNow;
	int numMachines;
	int numJobs;
	eventList* eList;
	machine* mArray;
	//Exercise 35
	int endTime;
	const int largeTime = 10000;
};



#endif