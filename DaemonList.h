/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DaemonList.h
 * Author: christianfrei
 *
 * Created on 31. Dezember 2015, 15:15
 */

#ifndef DAEMONLIST_H
#define DAEMONLIST_H

#include <vector>
#include "Daemon.h"
#include <string>

// <Daemon>
class DaemonList : public std::vector<Daemon> {
public:
    DaemonList();
    // DaemonList(const DaemonList& orig);
    virtual ~DaemonList();
    
    // Daemon operator[](unsigned int i);
    // Daemon operator[](std::string str);
    Daemon* getDaemon(std::string  str);
    unsigned int getDaemonID(std::string daemonName);
private:

};

#endif /* DAEMONLIST_H */

