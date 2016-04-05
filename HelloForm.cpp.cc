/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   HelloForm.cpp
 * Author: christianfrei
 *
 * Created on 26. Dezember 2015, 12:02
 */

#include "HelloForm.h"
#include "stdio.h"
#include "signal.h"
#include <iostream>
#include <string>
#include "DaemonTamer.h"
#include "Daemon.h"
#include "ui_HelloForm.h"

HelloForm::HelloForm() {
    widget.setupUi(this);
    
    connect(widget.hsSwitch0, SIGNAL(sliderPressed()), this, SLOT(sliderPressed()));
    connect(widget.hsSwitch0, SIGNAL(sliderReleased()), this, SLOT(sliderReleased()));
    
    connect(widget.hsSwitch1, SIGNAL(sliderPressed()), this, SLOT(sliderPressed()));
    connect(widget.hsSwitch1, SIGNAL(sliderReleased()), this, SLOT(sliderReleased()));
    
    connect(widget.hsSwitch2, SIGNAL(sliderPressed()), this, SLOT(sliderPressed()));
    connect(widget.hsSwitch2, SIGNAL(sliderReleased()), this, SLOT(sliderReleased()));
    
    connect(widget.hsSwitch3, SIGNAL(sliderPressed()), this, SLOT(sliderPressed()));
    connect(widget.hsSwitch3, SIGNAL(sliderReleased()), this, SLOT(sliderReleased()));
    
    connect(widget.hsSwitch4, SIGNAL(sliderPressed()), this, SLOT(sliderPressed()));
    connect(widget.hsSwitch4, SIGNAL(sliderReleased()), this, SLOT(sliderReleased()));
    
    connect(widget.hsSwitch5, SIGNAL(sliderPressed()), this, SLOT(sliderPressed()));
    connect(widget.hsSwitch5, SIGNAL(sliderReleased()), this, SLOT(sliderReleased()));
    

}

HelloForm::~HelloForm() {
}

void HelloForm::sliderPressed() {
    QSlider* silder = qobject_cast<QSlider*>(sender());
    if( silder != NULL ) 
    {
        sliderValueAtTheBeginning = silder->value();
    }
}

unsigned int HelloForm::getNumberOfSlider (QSlider* silder) {
    unsigned int number;
    
    if (silder == widget.hsSwitch0) {
        number = 0;
    } else if (silder == widget.hsSwitch1) {
        number = 1;
    } else if (silder == widget.hsSwitch2) {
        number = 2;
    } else if (silder == widget.hsSwitch3) {
        number = 3;
    } else if (silder == widget.hsSwitch4) {
        number = 4;
    } else if (silder == widget.hsSwitch5) {
        number = 5;
    }
    
    return number;
}

void HelloForm::sliderReleased() {
    std::cout << "sliderReleased0" <<std::endl; 
    
    QSlider* silder = qobject_cast<QSlider*>(sender());
    
    if( silder != NULL ) 
    {
        unsigned int number = getNumberOfSlider(silder);
        std::cout << "slider # " << number << std::endl; 
        int sliderValueNow = silder->value();

        if ((sliderValueAtTheBeginning == sliderValueNow && sliderValueNow == 1) ||
                (sliderValueAtTheBeginning != sliderValueNow && 0 == sliderValueNow)) {

            silder->setValue(0);

            int returnValue;

            std::cout << "Start: " << sliderValueNow <<std::endl;   
            daemonTamer->startDaemon(number);

            if (returnValue == -1) {
                std::cout << "Kann Prozess nicht ansprechen!" <<std::endl;   
            }

        } else {
            silder->setValue(1);

            int returnValue;

            std::cout << "Beenden: " << sliderValueNow <<std::endl;   

            // returnValue = kill (pid, SIGTERM);
            std::cout << "slider # " << number << std::endl; 
            daemonTamer->terminateDaemon(number);

            if (returnValue == -1) {
                std::cout << "Kann Prozess nicht ansprechen!" <<std::endl;   
            }
        }   
    }

    std::cout << "Released: Slider!" << std::endl;
}

DaemonTamer* HelloForm::getDaemonTamer() {
    return daemonTamer;
}

void HelloForm::setDaemonTamer(DaemonTamer *daemonTamer) {
    this->daemonTamer = daemonTamer;
}


void HelloForm::updateDaemon(Daemon *daemon, unsigned int i) {
    std::string name = daemon->getName();
    int         iStatus = daemon->getStatus();
    int         iSwitchStatus = 0;
    bool        enableStatus = true;
    QString     qstrStatus = QString("");
    
    switch(iStatus) {
        case 1:
            qstrStatus.append("Running");
            iSwitchStatus = 0;
            enableStatus = true;
            break;
        case 2:
            qstrStatus.append("Stopped");
            iSwitchStatus = 1;
            enableStatus = true;
            break;
        case 3:
            qstrStatus.append("Stopping");
            iSwitchStatus = 0;
            enableStatus = false;
            break;
        case 4:
            qstrStatus.append("Starting");
            iSwitchStatus = 1;
            enableStatus = false;
            break;
    }
    
    std::cout << "UPDATING" << std::endl;
    
    switch(i) {
        case 0:
            widget.hsSwitch0->setEnabled(enableStatus);
            widget.hsSwitch0->setValue(iSwitchStatus);
            widget.lblStatus0->setText(qstrStatus);
            break;
        case 1:
            std::cout << "UPDATING1" << std::endl;
            widget.hsSwitch1->setEnabled(enableStatus);
            widget.hsSwitch1->setValue(iSwitchStatus);
            widget.lblStatus1->setText(qstrStatus);
            break;
        case 2:
            std::cout << "UPDATING2" << std::endl;
            widget.hsSwitch2->setEnabled(enableStatus);
            widget.hsSwitch2->setValue(iSwitchStatus);
            widget.lblStatus2->setText(qstrStatus);
            break;
        case 3:
            std::cout << "UPDATING3" << std::endl;
            widget.hsSwitch3->setEnabled(enableStatus);
            widget.hsSwitch3->setValue(iSwitchStatus);
            widget.lblStatus3->setText(qstrStatus);
            break;
        case 4:
            std::cout << "UPDATING4" << std::endl;
            widget.hsSwitch4->setEnabled(enableStatus);
            widget.hsSwitch4->setValue(iSwitchStatus);
            widget.lblStatus4->setText(qstrStatus);
            break;
        case 5:
            std::cout << "UPDATING5" << std::endl;
            widget.hsSwitch5->setEnabled(enableStatus);
            widget.hsSwitch5->setValue(iSwitchStatus);
            widget.lblStatus5->setText(qstrStatus);
            break;
    }
}

void HelloForm::updateDaemonAt(unsigned int i) {
    if (i > 5 )
        return;
    
    DaemonList *daemonList = this->daemonTamer->getDaemonList();
    
    if (i >= daemonList->size()) {
        // Außerhalb der Range
        // this->deactiveGroupBox(i);
    } else {
        Daemon *daemon = &daemonList->at(i);
        
        daemon->lockMutex();
        updateDaemon(daemon, i);
        daemon->unlockMutex();
    }
}

void HelloForm::updateAllDaemons() {
    DaemonList *daemonList = this->daemonTamer->getDaemonList();
    unsigned int i;
    
    for (i=0 ; i < daemonList->size() ; i++) {
        this->updateDaemonAt(i);
    }
}