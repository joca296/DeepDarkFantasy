#include "statusEffect.h"
#include "functions.h"

statusEffect::statusEffect(string n)
{
    ifstream f;
    string path;
    jname=path;

    if(PLATFORM_NAME == "windows") path = "statusEffects\\"+n+".json";
    else path = "./statusEffects/"+n+".json";
    f.open(path);
    if(f.is_open())
    {
        const Document& document = parseFromFile(&f);
        name=document["Name"].GetString();
        val=document["Value"].GetInt();
        saving_throw_skill=document["SavingThrowSkill"].GetString();
        saveDC=document["SaveDC"].GetInt();
        duration=document["Duration"].GetInt();
        target=document["Target"].GetString();
        DOTflag=document["DOT"].GetBool();
        description=document["Description"].GetString();
        if(target!="Self" && target!="Enemy") cout<<"POSSIBLE ERROR IN "<<jname<<" TARGET NEITHER 'Self' nor 'Enemy'"<<endl;

        const Value& a = document["Affects"];

        for(SizeType i = 0; i<a.Size(); i++)
        {
            affects.emplace_back(a[i].GetString());
        }


    }
    f.close();

}


