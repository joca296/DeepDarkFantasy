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
    float SaveMulti;
    string interact_text, check_succ_text,save_succ_text,save_fail_text,disarm_succ_text,disarm_fail_text;
    string skill;
    string save;


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

    void setSaveMulti(float);
    float getSaveMulti();

    void setInteract_text(string);
    string getInteract_text();
    void setCheck_succ_text(string);
    string getCheck_succ_text();
    void setSave_succ_text(string);
    string getSave_succ_text();
    void setSave_fail_text(string);
    string getSave_fail_text();

    void setDisarm_succ_text(string);
    string getDisarm_succ_text();
    void setDisarm_fail_text(string);
    string getDisarm_fail_text();

    bool eDisc=false;
    bool isDisarmed=false;



    void setSkill(string);
    string getSkill();
    void setSave(string);
    string getSave();
    //virtual void throwAwayFunction()=0;
    virtual ~event(){};

};

class trap:public event
{
    public:
    trap(string);
};

#endif // EVENT_H_INCLUDED
