/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DaemonList.cpp
 * Author: Christian Frei
 * 
 * Created on 31. Dezember 2015, 15:15
 */

#include "DaemonList.h"
#include "Daemon.h"
#include <string>

DaemonList::DaemonList() {
}

DaemonList::~DaemonList() {
}

/*
Daemon DaemonList::operator[](unsigned int i) {
}

Daemon DaemonList::operator[](std::string str) {
}
*/

Daemon* DaemonList::getDaemon(std::string daemonName) {
    unsigned int i;
    Daemon daemon;
    
    for (i=0; i <= this->size(); i++) {
        // daemon = this->at(i);
        if ( this->at(i).getProcessName() == daemonName) {
            return &this->at(i);
        }
    }
    return NULL;
}

unsigned int DaemonList::getDaemonID(std::string daemonName) {
    unsigned int i;
    Daemon daemon;
    
    for (i=0; i <= this->size(); i++) {
        //daemon = this->at(i);
        if ( this->at(i).getProcessName() == daemonName) {
            return i;
        }
    }
    return -1; 
}