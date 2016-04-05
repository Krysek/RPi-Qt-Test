/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Daemon.h
 * Author: christianfrei
 *
 * Created on 29. Dezember 2015, 22:44
 */

#ifndef DAEMON_H
#define DAEMON_H

#define DAEMONRUNNING   1
#define DAEMONSTOPPED   2
#define DAEMONSTOPPING   3
#define DAEMONSTARTING  4

#include <string>
#include <time.h>

struct Daemon
{
public:
    Daemon();
    // Daemon(const Daemon& orig);
    virtual ~Daemon();
    
    
    int initMutex();
    int destroyMutex();
    int lockMutex();
    int unlockMutex();
    
    void setPID(pid_t pid);
    void updateLastUpdateTime();
    void setName(std::string name);
    void setMutex(pthread_mutex_t *mutex);
    void setPIDFilePath(std::string pidFilePath);
    void setScriptName(std::string scriptName);
    void setProcessName(std::string processName);
    void setStatus(int status);
    
    void startDaemon();
    void terminateDaemon();
    
    pid_t getPID();
    time_t getLastUpdateTime();
    std::string getName();
    pthread_mutex_t* getMutex();
    std::string getPIDFilePath();
    std::string getScriptName();
    std::string getProcessName();
    int getStatus();
    
    
    int updateDaemonStatus();
    std::string prefixOfDaemonProcessName;
private:
    pid_t pid;
    time_t lastUpdateTime;
    std::string name;
    std::string pidFilePath;
    std::string scriptName;
    std::string processName;
    int status;
    pthread_mutex_t mutex;
    
    pid_t getCurrentPIDfromPIDFILE(const std::string *pathToPid);
    pid_t getCurrentPIDfromPIDFILE();
};

#endif /* DAEMON_H */

