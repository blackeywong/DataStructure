#include "machineShopSimulator.h"
#include <sstream>


void machineShopSimulator::inputData(std::string changeTimeStr, std::string taskStr) {
	std::istringstream issChangeTime(changeTimeStr);
	std::istringstream issTask(taskStr);

	int ct;
	for(int j=1;j<=numMachines;++j){
		issChangeTime >> ct;
		if (ct < 0)
			throw std::invalid_argument("change-over time must be >=0");

		mArray[j].changeTime = ct;
	}

	job* theJob;
	int numTasks, firstMachine, theMachine, theTaskTime, theWaitTime/*Exercise 35*/, createTime;
	for (int i = 1; i <= numJobs; ++i) {
		issTask >> numTasks >> createTime;
		if(numTasks <1 || createTime < 0)
			throw std::invalid_argument("each job must have >1 task || job enters should be >= 0");
		firstMachine = 0;
		theJob = new job(i, createTime);
		for (int j = 1; j <= numTasks; ++j) {
			//Exercise 34
			issTask >> theMachine >> theTaskTime >> theWaitTime;
			//issTask >> theMachine >> theTaskTime;
			if(theMachine < 1 || theMachine > numMachines || theTaskTime < 1)
				throw std::invalid_argument("bad machine time or task time");
			if (j == 1)
				firstMachine = theMachine;
			theJob->addTask(theMachine, theTaskTime, theWaitTime);
			//theJob->addTask(theMachine, theTaskTime);
		}
		mArray[firstMachine].jobQ.push(theJob);
	}
}

void machineShopSimulator::startShop() {
	for (int p = 1; p <= numMachines; ++p) {
		changeState(p);
	}
}

job* machineShopSimulator::changeState(int theMachine) {
	job* lastJob;
	std::cout << "change state for machine:" << theMachine << " at time: " << timeNow << std::endl;
	if (mArray[theMachine].activeJob == nullptr) {
		lastJob = nullptr;

		if (mArray[theMachine].jobQ.empty()) {
			eList->setFinishTime(theMachine, largeTime);
			std::cout << "machine: " << theMachine << " job queue is empty. set largeTime" << std::endl;
		}
		else {
			//Exercise 34
			job* job = mArray[theMachine].jobQ.front();
			//Exercise 35
			if (timeNow < job->createTime) {
				std::cout << "job: " << job->id << " created at: " << job->createTime << " so cannot start" << std::endl;
				if (mArray[theMachine].jobQ.size() == 1) {
					eList->setFinishTime(theMachine, job->createTime);
				}
				else {
					mArray[theMachine].jobQ.push(job);
					mArray[theMachine].jobQ.pop();
				}
				//++timeNow;
				return lastJob;
			}

			task& task = job->taskQ.front();
			task.toWait = task.waitTime - (timeNow - job->arrivalTime);
			if (task.toWait > 0) {
				std::cout << "job: " << job->id << " current task needs to wait total: " << task.waitTime << " to wait left: " << task.toWait << std::endl;
				if (mArray[theMachine].jobQ.size() == 1) {
					eList->setFinishTime(theMachine, timeNow + task.toWait);
				}
				else{
					mArray[theMachine].jobQ.pop();
					mArray[theMachine].jobQ.push(job);
				}
			}
			else {
				mArray[theMachine].activeJob = job;
				mArray[theMachine].jobQ.pop();
				//Exercise 34
				mArray[theMachine].totalWait += timeNow - mArray[theMachine].activeJob->arrivalTime - task.waitTime;
				//mArray[theMachine].totalWait += timeNow - mArray[theMachine].activeJob->arrivalTime;
				mArray[theMachine].numTasks++;
				int t = mArray[theMachine].activeJob->removeNextTask();
				eList->setFinishTime(theMachine, timeNow + t);
				std::cout << "job: " << job->id << " with task time cost: " << t << std::endl;
			}
		}
	}
	else {
		lastJob = mArray[theMachine].activeJob;
		mArray[theMachine].activeJob = nullptr;
		eList->setFinishTime(theMachine, timeNow + mArray[theMachine].changeTime);
		std::cout << "machine: " << theMachine << " enter change time cost: " << mArray[theMachine].changeTime << std::endl;
	}

	return lastJob;
}

void machineShopSimulator::simulate() {
	//Exercise 35
	while (numJobs > 0 && timeNow <= endTime) {
	//while (numJobs > 0) {
		int nextToFinish = eList->nextEventMachine();
		timeNow = eList->nextEventTime(nextToFinish);
		if (timeNow > endTime) {
			timeNow = endTime;
			break;
		}
		job* theJob = changeState(nextToFinish);
		if (theJob != nullptr && !moveToNextMachine(theJob))
			--numJobs;
	}
}

bool machineShopSimulator::moveToNextMachine(job* theJob) {
	if (theJob->taskQ.empty()) {
		std::cout << "Job " << theJob->id << " has completed at " << timeNow << " Total wait was " << (timeNow - theJob->length - theJob->createTime) << std::endl;
		return false;
	}
	else {
		int p = theJob->taskQ.front().machine;
		mArray[p].jobQ.push(theJob);

		theJob->arrivalTime = timeNow;
		if (eList->nextEventTime(p) == largeTime)
			changeState(p);
	}
	return true;
}

void machineShopSimulator::outputStatistics() {
	std::cout << "Finish time = " << timeNow << std::endl;
	for (int p = 1; p <= numMachines; ++p) {
		std::cout << "Machine " << p << " completed " << mArray[p].numTasks << " tasks" << std::endl;
		std::cout << "The total wait time was " << mArray[p].totalWait << std::endl;
		std::cout << std::endl;
	}
	//Exercise 35
	std::cout << "Unfinished job/task: " << std::endl;
	for (int p = 1; p <= numMachines; ++p) {
		if (mArray[p].activeJob != nullptr) {
			std::cout << "Machine " << p << " has task of job " << mArray[p].activeJob->id << " running" << std::endl;
		}
	}

	for (int p = 1; p <= numMachines; ++p) {
		if (!mArray[p].jobQ.empty()) {
			{
				//std::cout << "Machine " << p << " has job " << mArray[p].jobQ << " waiting" << std::endl;
				std::cout << "Machine " << p << " has job waiting" << std::endl;
			}
		}
	}
}