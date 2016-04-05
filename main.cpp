/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: christianfrei
 *
 * Created on 26. Dezember 2015, 11:58
 */

#include <QApplication>

#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include "signal.h"
#include "HelloForm.h"
#include "DaemonTamer.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    std::cout << "Elternprozess gestartet" << std::endl;
    
    QApplication app(argc, argv);
    int         returnValue;
    DaemonTamer daemonTamer;
    HelloForm form;
    
    form.setDaemonTamer(&daemonTamer);
    daemonTamer.setForm(&form);
    
    form.show();
    daemonTamer.startObservingDaemons();
    
    returnValue = app.exec();
    
    
    std::cout << "Elternprozess beendet1" << std::endl;
    daemonTamer.stopObservingDaemons();
    std::cout << "Elternprozess beendet2" << std::endl;
    
    return returnValue;
}
