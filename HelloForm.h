/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HelloForm.h
 * Author: christianfrei
 *
 * Created on 26. Dezember 2015, 12:02
 */

#ifndef _HELLOFORM_H
#define _HELLOFORM_H

#include "ui_HelloForm.h"
// #include "DaemonTamer.h"
#include "Daemon.h"

class DaemonTamer;

class HelloForm : public QDialog {
    Q_OBJECT
public:
    HelloForm();
    virtual ~HelloForm();
    DaemonTamer* getDaemonTamer();
    void setDaemonTamer(DaemonTamer *daemonTamer);
    void updateDaemon(Daemon *daemon, unsigned int i);
    void updateDaemonAt(unsigned int i);
    void updateAllDaemons();
    unsigned int getNumberOfSlider (QSlider* silder);
public slots:
    void sliderPressed();
    void sliderReleased();
private:
    Ui::DaemonControlCenter widget;
    int sliderValueAtTheBeginning;
    DaemonTamer *daemonTamer;
};
#endif /* _HELLOFORM_H */
