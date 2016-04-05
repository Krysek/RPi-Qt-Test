/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DaemonTamer.h
 * Author: christianfrei
 *
 * Created on 29. Dezember 2015, 19:20
 */

#ifndef DAEMONTAMER_H
#define DAEMONTAMER_H

#define DT_STOPPING     -1
#define DT_STOPPED      0
#define DT_OBSERVING    1

#include "HelloForm.h"
#include <QStringList>
#include <string>
#include "Daemon.h"
#include "DaemonList.h"
#include <vector>

class DaemonTamer {
public:
    DaemonTamer();
    DaemonTamer(const DaemonTamer& orig);
    virtual ~DaemonTamer();
    void updateAllDaemonStatus ();
    
   DaemonList* getDaemonList();
    
    void terminateDaemon(Daemon *daemon);
    void terminateDaemon(unsigned int nmbOfDaemon);
    void startDaemon(Daemon *daemon);
    void startDaemon(unsigned int nmbOfDaemon);
    
    void startObservingDaemons();
    void stopObservingDaemons();
    
    void updateDaemonDataOfGUI (unsigned int number);
    void updateDaemonDataOfGUI (Daemon *daemon);
    
    HelloForm* getForm();
    void setForm(HelloForm *form);
    int getDaemonObservingStatus();
private:
    // std::vector<Daemon> daemonList;
    DaemonList daemonList;
    // thread_data threadData;
    int daemonObservingStatus;
    pid_t pidOfObservingDaemons;
    pthread_t observerThread;
    std::string stdPathToRunningDaemon;
    std::string prefixOfDaemonProcessName;
    HelloForm *form;
};

void* observeDaemonsThread(void *arg);
void* startDaemonThread(void *arg);
void* terminateDaemonThread(void *arg);

struct thread_data{
   DaemonTamer *daemonTamer;
};

#endif /* DAEMONTAMER_H */

