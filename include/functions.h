#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include "rapidjson/document.h"



using namespace std;
using namespace rapidjson;

#ifndef DEEPDARKFANTASY_FUNCTIONS_H
#define DEEPDARKFANTASY_FUNCTIONS_H

int dRoll(int sideNum = 20, int adv = 0,int dNum = 1);
int randomWeight(int numberOfChoices, int choiceWeight[]);

//bool combatOverCheck(head,creature* p);

int dRoll(int sideNum, int adv, int dNum)
{
    int r1=0, r2=0,sum=0;
    if(adv == 0)
    {
        for(int i=0; i<dNum; i++)
        {
            sum+=rand()%sideNum+1;
            //cout<<"sum = "<<sum<<" i = "<<i<<endl;
        }
        //cout<<"Rolled: "<<sum<<endl;
        return sum;
    }
    if(adv>0)
    {
        r1 = rand()%sideNum+1;
        // cout<<"r1 = "<<r1<<endl;
        r2 = rand()%sideNum+1;
        //cout<<"r2 = "<<r2<<endl;
        adv--;
        while(adv>0)
        {
            r1<r2? r1= rand()%sideNum+1 : r2 = rand()%sideNum+1;
           /* cout<<"r1 = "<<r1<<endl;
            cout<<"r2 = "<<r2<<endl;*/
            adv--;
        }

        return r1>r2 ? r1:r2;
    }
    if(adv<0)
    {
        r1 = rand()%sideNum+1;
        //cout<<"r1 = "<<r1<<endl;
        r2 = rand()%sideNum+1;
        //cout<<"r2 = "<<r2<<endl;
        adv--;
        while(adv<0)
        {
            r1>r2? r1= rand()%sideNum+1 : r2 = rand()%sideNum+1;
            /*cout<<"r1 = "<<r1<<endl;
            cout<<"r2 = "<<r2<<endl;*/
            adv++;
        }
        return r1>r2 ? r2:r1;
    }
    return 0;
}

int randomWeight(int numberOfChoices, int choiceWeight[]){
    int sum_of_weight = 0;
    for(int i=0; i<numberOfChoices; i++) {
        sum_of_weight += choiceWeight[i];
    }
    int rnd = rand()%sum_of_weight;
    for(int i=0; i<numberOfChoices; i++) {
        if(rnd < choiceWeight[i]){
            return i;
        }
        rnd -= choiceWeight[i];
    }
    assert(!"should never get here");
}

#endif // DEEPDARKFANTASY_FUNCTIONS_H
