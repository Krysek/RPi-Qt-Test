/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Daemon.h"
#include <time.h>
#include <string>
#include <iostream>
#include "signal.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>

Daemon::Daemon() {
    initMutex();
    prefixOfDaemonProcessName   = "p_";
}

Daemon::~Daemon() {
    destroyMutex();
}

int Daemon::initMutex() {
    return pthread_mutex_init (&this->mutex, NULL);
}

int Daemon::destroyMutex() {
    pthread_mutex_unlock(&this->mutex);
    return pthread_mutex_destroy(&this->mutex);
}

int Daemon::lockMutex() {
   return pthread_mutex_lock(&this->mutex); 
    
}

int Daemon::unlockMutex() {
   return pthread_mutex_unlock(&this->mutex); 
}

void Daemon::setPID(pid_t pid) {
    this->pid = pid;
}

void Daemon::updateLastUpdateTime() {
    this->lastUpdateTime = time(NULL);
}

void Daemon::setName(std::string name) {
    this->name = name;
}

void Daemon::setPIDFilePath(std::string pidFilePath) {
    this->pidFilePath = pidFilePath;
}

void Daemon::setScriptName(std::string scriptName) {
    this->scriptName = scriptName;
}

void Daemon::setProcessName(std::string processName) {
    this->processName = processName;
    
}

void Daemon::setStatus(int status) {
    this->status = status;
}


pid_t Daemon::getPID() {
    return pid;
}

time_t Daemon::getLastUpdateTime() {
    return lastUpdateTime;
}

std::string Daemon::getName() {
    return name;
}

std::string Daemon::getPIDFilePath() {
    return pidFilePath;
}

std::string Daemon::getScriptName() {
    return scriptName;
}

std::string Daemon::getProcessName() {
    return processName;
}

int Daemon::getStatus() {
    return status;
}

void Daemon::startDaemon() {
    pid_t pid;
    int   status;

    if ((pid = fork()) < 0) {
        perror("fork");
        return;
    } else if (pid == 0) {
        std::string str = prefixOfDaemonProcessName + this->getName();

        execl ( this->getScriptName().c_str(),
                str.c_str(),
                "start",
                NULL);
    } else {
        waitpid (pid, &status, 0);

        /*
        Auswertung des status.

        if ((! WIFEXITED (status)) || (WEXITSTATUS (status) != 0)) {
             perror ("Printing");
        }
         */
    }
}

void Daemon::terminateDaemon() {
    pid_t pid;
    int   status;

    if ((pid = fork()) < 0) {
        perror("fork");
        return;
    } else if (pid == 0) {
        std::string str = prefixOfDaemonProcessName + this->getName();

        std::cout << "???" << this->getScriptName().c_str() << std::endl;
        execl ( this->getScriptName().c_str(),
                str.c_str(),
                "stop",
                NULL);
    } else {
        waitpid (pid, & status, 0);

        if ((! WIFEXITED (status)) || (WEXITSTATUS (status) != 0)) {
            perror ("Printing");
        }
        // this->updateDaemonStatus();
        if (this->getStatus() == DAEMONRUNNING) {
            kill (this->getPID(), SIGTERM);
        }
    }
}

pid_t Daemon::getCurrentPIDfromPIDFILE(const std::string *pathToPid) {
    this->setPIDFilePath(*pathToPid);
    return getCurrentPIDfromPIDFILE();
}

pid_t Daemon::getCurrentPIDfromPIDFILE() {
    std::ifstream file;
    file.open(this->getPIDFilePath().c_str(), file.out);

    std::string str;
    pid_t pid;

    if (!file.eof())
    {
        std::getline(file, str);
        pid = atoi(str.c_str());
    }
    else {
        pid = -1;
    }

    file.close();
    
    return pid;
}

int Daemon::updateDaemonStatus() {
    Daemon currentDaemonStatus;
    pid_t pidFromFile;
    int updateFlag = 0;
    
    std::cout <<  "BLA" << std::endl;
    
    currentDaemonStatus.setProcessName(this->getProcessName());
    currentDaemonStatus.setPID(this->getPID());
    currentDaemonStatus.setStatus(this->getStatus());
    currentDaemonStatus.setPIDFilePath(this->getPIDFilePath());
    
    std::string str = currentDaemonStatus.getPIDFilePath();
    pidFromFile = getCurrentPIDfromPIDFILE(&str);
    
    if (pidFromFile > 0) {
        currentDaemonStatus.setStatus(DAEMONRUNNING);
        currentDaemonStatus.setPID(pidFromFile);
    } else {
        currentDaemonStatus.setStatus(DAEMONSTOPPED);
        currentDaemonStatus.setPID(pidFromFile);
    }
    
    if (    currentDaemonStatus.getProcessName() != this->getProcessName() ||
            currentDaemonStatus.getPID() != this->getPID() ||
            currentDaemonStatus.getStatus() != this->getStatus()) {
            updateFlag = 1;
            std::cout <<  "UPDATE" << std::endl;
    }
    
    std::cout << currentDaemonStatus.getProcessName() << " : " << currentDaemonStatus.getPID() << " : " << currentDaemonStatus.getStatus() << std::endl;
    
    this->setProcessName(currentDaemonStatus.getProcessName());
    this->setPID(currentDaemonStatus.getPID());
    this->setStatus(currentDaemonStatus.getStatus());
    
    return updateFlag;
}