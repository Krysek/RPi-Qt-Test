/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DaemonTamer.cpp
 * Author: christianfrei
 * 
 * Created on 29. Dezember 2015, 19:20
 */

#include "DaemonTamer.h"
#include <QStringList>
#include <iostream>
#include <fstream>
#include <string>
#include "Daemon.h"
#include "signal.h"
#include <unistd.h>
#include <sys/wait.h>
#include "signal.h"
#include "HelloForm.h"

struct startAndStopParameters {
    DaemonTamer *daemonTamer;
    Daemon *daemon;
};

DaemonTamer::DaemonTamer() {
    Daemon nginx;
    nginx.setName("Nginx");
    nginx.setPIDFilePath("/var/run/nginx.pid");
    nginx.setScriptName("/etc/init.d/nginx");
    nginx.setProcessName("nginx");
    daemonList.push_back(nginx);
    
    Daemon mysqld;
    mysqld.setName("MySQL");
    mysqld.setPIDFilePath("/var/run/mysqld/mysql.pid");
    mysqld.setScriptName("/etc/init.d/mysql");
    mysqld.setProcessName("mysqld");
    daemonList.push_back(mysqld);
    
    Daemon php5fpm;
    php5fpm.setName("PHP5-fpm");
    php5fpm.setPIDFilePath("/var/run/php5-fpm.pid");
    php5fpm.setScriptName("/etc/init.d/php5-fpm");
    php5fpm.setProcessName("php5-fpm");
    daemonList.push_back(php5fpm);
    
    Daemon samba;
    samba.setName("Samba");
    samba.setPIDFilePath("/var/run/samba/smbd.pid");
    samba.setScriptName("/etc/init.d/samba");
    samba.setProcessName("samba");
    daemonList.push_back(samba);
    
    Daemon shairPort;
    shairPort.setName("ShairPort");
    shairPort.setPIDFilePath("/var/run/ShairPort.pid");
    shairPort.setScriptName("/etc/init.d/ShairPort");
    shairPort.setProcessName("ShairPort");
    daemonList.push_back(shairPort);
    
    stdPathToRunningDaemon      = "/etc/init.d/";
    prefixOfDaemonProcessName   = "p_";
}

DaemonTamer::DaemonTamer(const DaemonTamer& orig) {
    //*(this->form) = *(orig.form);
}

DaemonTamer::~DaemonTamer() {
    //free(stopObserving);
    //stopObserving = NULL;
}

void DaemonTamer::updateAllDaemonStatus () {
    unsigned int nmbOfDaemon;
    int iChangeFlag;
        
    for (nmbOfDaemon = 0; nmbOfDaemon < daemonList.size(); nmbOfDaemon++) {
        iChangeFlag = 0;
        
        daemonList[nmbOfDaemon].lockMutex();
        
        std::cout << "Update of " << nmbOfDaemon << std::endl;
        iChangeFlag = daemonList[nmbOfDaemon].updateDaemonStatus();
        daemonList[nmbOfDaemon].unlockMutex();
        
        if (iChangeFlag == 1) {
           std::cout << "Change of " << nmbOfDaemon << std::endl;
           this->form->updateDaemonAt(nmbOfDaemon);
        }
    }
}

void DaemonTamer::terminateDaemon(Daemon *daemon) {
    pthread_t thread;
    int rc;
    startAndStopParameters *param = (startAndStopParameters*) malloc(sizeof(startAndStopParameters));
    
    param->daemonTamer  = this;
    param->daemon       = daemon;
    
    std::cout << "Terminate daemon \"" << daemon->getName() << "\" - Initialize thread for observing daemons." << std::endl;
    
    rc = pthread_create(&thread, 
                        NULL,
                        &terminateDaemonThread,
                        (void*) param);
    
    if (rc){
        std::cout << "Terminate daemon \"" << daemon->getName() << "\" - ERROR " << rc << "; Could not create a thread for terminating dameon \"" << daemon->getName() << "\"." << std::endl;
    } else {
        std::cout << "Terminate daemon \"" << daemon->getName() << "\" - Thread is started." << std::endl;
    }
    
    param = NULL;
    pthread_join(thread, NULL);
}

void DaemonTamer::terminateDaemon(const unsigned int nmbOfDaemon) {
    if (nmbOfDaemon <= (daemonList.size() -1)){
        terminateDaemon(&(daemonList[nmbOfDaemon]));
    }
}

void DaemonTamer::startObservingDaemons() {
    int rc;
    
    std::cout << "Observe daemons - Initialize thread for observing daemons." << std::endl;
    
    this->daemonObservingStatus = true;
    
    rc = pthread_create(&observerThread, 
                        NULL,
                        &observeDaemonsThread,
                        (void*) this);
    
    if (rc){
        std::cout << "Observe daemons - ERROR: " << rc << "; Could not create a thread for observing dameons." << std::endl;
    } else {
        std::cout << "Observe daemons - Thread is started." << std::endl;
    }
}

int DaemonTamer::getDaemonObservingStatus() {
    return daemonObservingStatus;
}

void DaemonTamer::stopObservingDaemons() {
    std::cout << "stopObservingDaemons" << std::endl;
    daemonObservingStatus = DT_STOPPING;
    
    /* sleep(10);
    pthread_exit(observerThread);*/
    
    daemonObservingStatus = DT_STOPPED;
}

void DaemonTamer::startDaemon(const unsigned int nmbOfDaemon) {
    if (nmbOfDaemon <= (daemonList.size() -1)){
        startDaemon(&(daemonList[nmbOfDaemon]));
    }
}

void DaemonTamer::startDaemon(Daemon *daemon) {
    pthread_t thread;
    int rc;
    startAndStopParameters *param = (startAndStopParameters*) malloc(sizeof(startAndStopParameters));
    
    param->daemonTamer  = this;
    param->daemon       = daemon;
    
    std::cout << "Start daemon \"" << daemon->getName() << "\" - Initialize thread for observing daemons." << std::endl;
    
    rc = pthread_create(&thread, 
                        NULL,
                        &startDaemonThread,
                        (void*) param);
    
    if (rc){
        std::cout << "Start daemon \"" << daemon->getName() << "\" - ERROR: " << rc << "; Could not create a thread for starting dameon \"" << daemon->getName() << "\"." << std::endl;
    } else {
        std::cout << "Start daemon - Thread is started." << std::endl;
    }
    
    pthread_join(thread, NULL);
}

DaemonList* DaemonTamer::getDaemonList() {
    return &daemonList;
}

HelloForm* DaemonTamer::getForm() {
    return form;
}

void DaemonTamer::setForm(HelloForm *form) {
    this->form = form;
}

void DaemonTamer::updateDaemonDataOfGUI (unsigned int number) {
    this->form->updateDaemon(&daemonList[number], number); 
}

void DaemonTamer::updateDaemonDataOfGUI (Daemon *daemon) {
    unsigned int number = 0;
    
    while (daemonList.size() > number & &daemonList[number] != daemon) {
        number++;
    }
    std::cout << "update n: " << number << " daemon: " << &daemonList[number] << " status: " << daemonList[number].getStatus() << std::endl;
    if (daemonList.size() > number & &daemonList[number] == daemon) {
        std::cout << "update -> " << number << std::endl;
        this->form->updateDaemon(&daemonList[number], number);   
    }
}
    
void* observeDaemonsThread(void *arg) {
    DaemonTamer *daemonTamer = (DaemonTamer*) arg;
    
    std::cout << "XXX" << std::endl;
    do {
    std::cout << "XXX" << std::endl;
            daemonTamer->updateAllDaemonStatus();
            sleep(3);
    } while (daemonTamer->getDaemonObservingStatus() == DT_OBSERVING);
    
    pthread_exit((void *)pthread_self());
}

void* terminateDaemonThread(void *arg) {
    startAndStopParameters *param = (startAndStopParameters*) arg;
    int rv;                     // return value
    
    Daemon *daemon              = param->daemon;
    DaemonTamer *daemonTamer    = param->daemonTamer;
    
    daemon->lockMutex();
    
    rv = daemon->updateDaemonStatus();
    
    if (daemon->getStatus() == DAEMONRUNNING) {
        daemon->setStatus(DAEMONSTOPPING);
        
        daemonTamer->updateDaemonDataOfGUI(daemon);
        
        daemon->terminateDaemon();
        
        rv = daemon->updateDaemonStatus();
        
        if (rv != 0) {
            daemonTamer->updateDaemonDataOfGUI(daemon);
        }
    }
    daemon->unlockMutex();
    
    free(param);
    param = NULL;
    
    pthread_exit((void *)pthread_self());
}

void* startDaemonThread(void *arg) {
    startAndStopParameters *param = (startAndStopParameters*) arg;
    int rv;                     // return value
    
    Daemon *daemon              = param->daemon;
    DaemonTamer *daemonTamer    = param->daemonTamer;
    
    daemon->lockMutex();
    
    rv = daemon->updateDaemonStatus();
    
    if (daemon->getStatus() == DAEMONSTOPPED) {
        daemon->setStatus(DAEMONSTARTING);
        
        daemonTamer->updateDaemonDataOfGUI(daemon);
        
        daemon->startDaemon();

        rv = daemon->updateDaemonStatus();
        if (rv != 0) {
            daemonTamer->updateDaemonDataOfGUI(daemon);
        }
    }
    
    daemon->unlockMutex();
    
    free(param);
    param = NULL;
    
    pthread_exit((void *)pthread_self());
}

