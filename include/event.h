#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED
#include "functions.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


//cross-platform support
#ifdef __linux__
#define PLATFORM_NAME "linux"
#elif _WIN32
#define PLATFORM_NAME "windows"
#else
#endif


 class event
{
private:
    int CheckDC,SaveDC,DisarmDC,DMG,dNum;
    string interact_text, check_succ_text,save_succ_text,save_fail_text;
    string skill;
    string save;
    bool eDisc=false;

    public:

    void setCheckDC(int);
    int getCheckDC();
    void setSaveDC(int);
    int getSaveDC();
    void setDMG(int);
    int getDMG();
    void setDNum(int);
    int getDNum();
    void setDisarmDC(int);
    int getDisarmDC();

    void setInteract_text(string);
    string getInteract_text();
    void setCheck_succ_text(string);
    string getCheck_succ_text();
    void setSave_succ_text(string);
    string getSave_succ_text();
    void setSave_fail_text(string);
    string getSave_fail_text();

    void setSkill(string);
    string getSkill();
    void setSave(string);
    string getSave();

    virtual ~event(){};

};

class trap:public event
{
    trap(string);
};

#endif // EVENT_H_INCLUDED
