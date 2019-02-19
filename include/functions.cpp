#include <vector>
#include "functions.h"

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

int randomWeight(const vector<int>& choiceWeight){
    int sum_of_weight = 0;
    for(int i=0; i<choiceWeight.size(); i++) {
        sum_of_weight += choiceWeight[i];
    }
    int rnd = rand()%sum_of_weight;
    for(int i=0; i<choiceWeight.size(); i++) {
        if(rnd < choiceWeight[i]){
            return i;
        }
        rnd -= choiceWeight[i];
    }
    assert(!"should never get here");
}

Document parseFromFile(ifstream *f){
    //converting file to a char* to parse file
    stringstream stream;
    stream<<f->rdbuf();
    string str = stream.str();
    const char* json = str.c_str();
    Document document;
    document.Parse(json);
    return document;
}
