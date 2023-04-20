#include<iostream>
#include <list>
#include<algorithm>
#include<fstream>
#include <string>
#include <tgmath.h>
using namespace std;

struct elem {
        string name;
        int n;//number of occurs
    };

bool checkDecisiveArg(string decisiveArg, string record, int xDecisive)
{
    int x = 0;
    string arg="";
    for(int i = 0; i < record.length();i++)
    {
        if(record[i]==',')
        {
            x++;
        }
        else if(x==xDecisive)
            arg+=record[i];
    }
    //cout<<arg<<" x "<<decisiveArg<<" x "<<record<<endl;
    return arg==decisiveArg;
}
void printList(list<elem> &listOfElems, string name)
{
    cout << "DECISIONS: of "<<name<<": \n\n";
    list<elem>::iterator it;
    for(it = listOfElems.begin(); it!= listOfElems.end();it++)
    {
        cout<<it->name<<" "<<it->n<<endl;
    }

    // Iterating over myContainer elements
    // Each element is a list on its own
    //for (int i = 0; i < n; i++)
    //{
    //    print(myContainer[i], i);
    //}
}

elem * contains (list<elem> &listOfElems, string record)
{
    list<elem>::iterator it;
    for(it = listOfElems.begin(); it!= listOfElems.end();it++)
    {
        if((*it).name == record)
            return &(*it);
    }
    return &(*listOfElems.end());

}

//int printList
int getNumOfArgs(string record)
{
    int n = 1;
    for(int i = 0; i<record.length();i++)
        if(record[i]==',')
            n++;
    return n;
}
double I(list<elem> &listOfElems, int N)
{
    double info = 0.0, p = 0.0;
    list<elem>::iterator it;
    for(it = listOfElems.begin(); it!= listOfElems.end();it++)
    {
        p = it->n/(double)N;

        info+=p*log2(p);
        //cout<<it->n<<" "<<N<<" "<<p*log2(p)<<endl;
    }
    info*=(-1);
    return info;
}
double Info(list<elem> &listOfDecisions,int N)
{
    double info = 0.0;
    list<elem>::iterator it;
    for(it = listOfDecisions.begin(); it!= listOfDecisions.end();it++)
    {
        info = info + it->n/(double)N*I(listOfDecisions,N);
    }
    return info;
}
void makeDensity(int x, int attributesNamesLength)
{

    for(int i = 0; i<=x ; i++)
        cout<<"            ";
    //for(int i=0;i<attributesNamesLength;i++)
        //cout<<' ';

    //cout<<"    ";
}
void podzial(list<elem> records[], list<string> database[], int xDecisive, int N, int density)//1 - lista elementow
{
    int n=N,newxDecisive;
    double Inf,SplitInf, Gain, gainRatioMax = -1.0;
    //if(density>0)
        //makeDensity(density);
    cout<<"Atrybut a"<<xDecisive+1<<": "<<endl;
    //N = 4;

    list<elem> newRecords[N];
    list<elem>::iterator it4;


    it4 = records[xDecisive].begin();

    list<string> newDatabase[N];
    list<string>::iterator it1;
    list<int> indexes;
    int index;
    for(;it4!=records[xDecisive].end();it4++)
    {
        //if(it4==records[xDecisive].begin())
            //cout<<it4->name<<" -> ";
        //else
        //{
            makeDensity(density, it4->name.length());
            cout<<it4->name<<" -> ";
        //}
        gainRatioMax = -1;
        for(int i=0;i<N;i++)
        {
            newDatabase[i].clear();
            newRecords[i].clear();
        }
        indexes.clear();
        index=0;
        it1 = database[xDecisive].begin();
        //cout<<"t: "<<*(database[N-1].begin())<<endl;
        for(;it1!=database[xDecisive].end();it1++)//zapisuje indeksy tych rekordow, ktore mnie interesuja
        {

            if(it4->name==*it1)
            {

                indexes.push_front(index);
            }
            index++;
        }

        for(int i = 0;i < N;i++)//tworze nowa baze zawierajaca wylacznie rekordy ktore mnie interesuja
        {
            index = 0;

            it1 = database[i].begin();
            for(;it1!=database[i].end();it1++)
            {
                if(find(indexes.begin(),indexes.end(),index)!=indexes.end())
                {
                    newDatabase[i].push_front(*it1);
                    //cout<<*it1<<" ";
                    auto r = contains(newRecords[i],*it1);
                    if(r != &(*newRecords[i].end()))
                    {
                        (*r).n++;
                        //cout<<"t";
                    }
                    else
                    {
                        elem e;
                        e.name = *it1;
                        e.n=1;
                        newRecords[i].push_front(e);
                    }

                }
                index++;
            }
            //cout<<endl;
        }

            //--------------------------------------------------------------------
            //licze wszystko w newdatabase co wczesniej w database


            for(int i = 0; i<N;i++)
            {
                //cout<<"Atrybut "<<i+1<<": "<<endl;
                if(i==xDecisive)
                {
                    //cout<<it4->name<<" "<<it4->n<<endl;
                    //cout<<"Ilosc mozliwych atrybutu "<<xDecisive+1<<": "<<1<<endl;
                }
                else
                {
                    //list<elem>::iterator it;
                   // for(it = newRecords[i].begin(); it!= newRecords[i].end();it++)
                        //cout<<it->name<<" "<<it->n<<endl;

                    //cout<<"Ilosc mozliwych wariantow atrybutu "<<i+1<<": "<<newRecords[i].size()<<endl;
                }
            }
                //entropia
            Inf = I(newRecords[N-1],newDatabase[N-1].size());
                //cout<<"I(T) = "<<Inf<<endl;

            n = newDatabase[0].size();//n - ilosc rekordow w naszej tabeli

            for(int i = 0; i < N-1;i++)
            {
                double info = 0.0;


                list<elem>::iterator it3;
                it3 = newRecords[i].begin();

                for(;it3!=newRecords[i].end(); it3++)
                {
                    list<elem> decisions;//gathering all options of decisions per one value of attribute
                    list<string>::iterator it1;
                    list<string>::iterator it2;
                    it1 = newDatabase[i].begin();
                    it2 = newDatabase[N-1].begin();
                    for(;it1 != newDatabase[i].end() && it2 != newDatabase[N-1].end() ;it1++,it2++)
                    {
                        if(*it1 == it3->name)
                        {
                            auto r = contains(decisions, *it2);
                            if(r != &(*decisions.end()))
                            {
                                (*r).n++;
                            }
                            else
                            {
                                elem e;
                                e.name = *it2;
                                e.n=1;
                                decisions.push_front(e);
                            }
                        }
                    }
                    info = info + (double)it3->n/(double)n*I(decisions,it3->n);
                }
                //cout<<"Info(a"<<i+1<<",T) = "<<info<<endl;
                Gain = Inf-info;
                //cout<<"Gain(a"<<i+1<<",T) = "<<Gain<<endl;
                SplitInf = I(newRecords[i],newDatabase[i].size());
                //cout<<"SplitInfo(a"<<i+1<<",T) = "<<SplitInf<<endl;
                //cout<<"GainRatio(a"<<i+1<<",T) = "<<Gain/SplitInf<<endl;
            if(Gain/SplitInf>gainRatioMax)
            {
                gainRatioMax = Gain/SplitInf;
                newxDecisive = i;
            }

        }
        //cout<<"GainRatioMax: "<<gainRatioMax<<endl;
        if(gainRatioMax>0)
        {
            //cout<<endl;
            podzial(newRecords,newDatabase,newxDecisive,N,density+1);
        }
        else
        {
            //makeDensity(density);
            cout<<"DECYZJA "<<*(newDatabase[N-1].begin())<<endl;
        }

        //delete newDatabase;
        //delete &it1;
        //delete &indexes;
        //cout<<"---------------------"<<endl;
        }


}


int main()
{
    system("CLS");
    fstream file;
    string record="", a="",filename = "car.data";//gielda.txt testowaTabDec.txt
    int n=1, xDecisive;
    double Inf,SplitInf, Gain, gainRatioMax = -1.0;
    file.open(filename);
    getline(file, record);
    //licze ilosc atrybutow w tabeli decyzyjnej
    n = getNumOfArgs(record);
    const int N=n;
    cout<<n<<endl;//wypisuje ilosc atrybutow

    list<string> database[n];//moja tabela wejsciowa
    list<elem> records[n];//tabela wszystkich mozliwych atrybutow wraz z iloscia poszczegolnych wystapien
    file.close();
    file.open(filename);
    while(true)
    {
        n=0;
        a="";
        getline(file, record);
        if(file.eof())
            break;
        for(int i=0;i<record.length();i++)
        {
            if(record[i]!=',')
            {
                a+=record[i];
            }
            if(record[i]==',' || i==record.length()-1)
            {
                //if(i==record.length()-1)
                    //cout<<"TEST "<<a<<endl;
                auto r = contains( records[n], a);
                if(r != &(*records[n].end()))
                {
                    (*r).n++;
                }
                else
                {
                        elem e;
                        e.name = a;
                        e.n=1;
                        records[n].push_front(e);
                }
                database[n].push_front(a);
                n++;
                a="";
            }
        }
        cout<<record<<endl;
    }
    file.close();
    //n = getNumOfArgs(record);
    for(int i = 0; i<N;i++)
    {
        cout<<"Atrybut "<<i+1<<": "<<endl;
        list<elem>::iterator it;
        for(it = records[i].begin(); it!= records[i].end();it++)
            cout<<it->name<<" "<<it->n<<endl;
        cout<<"Ilosc mozliwych wariantow atrybutu "<<i+1<<": "<<records[i].size()<<endl;
    }
    //entropia
    Inf = I(records[N-1],database[N-1].size());
    cout<<"I(T) = "<<Inf<<endl;


    //funkcja informacji

    /*
        opis struktur danych:
        tablica list records[n] <elem>- zawiera w i-tej kolumnie listê wszystkich roznych wartosci i+1 atrybutu z jego nazw¹ i iloscia wystapien
        tablica list database[n] <string> - zawiera tabele wejsciowa danych
        lista decisions <elem> - zawiera tabele decyzji uzaleznionych od danej wartosci danego atrybutu z nazwa decyzji i iloscia wystapien
    */
    n = database[0].size();//n - ilosc rekordow w naszej tabeli

    for(int i = 0; i < N-1;i++)
    {
        double info = 0.0;


        list<elem>::iterator it3;
        it3 = records[i].begin();

        for(;it3!=records[i].end(); it3++)
        {
            list<elem> decisions;//gathering all options of decisions per one value of attribute
            list<string>::iterator it1;
            list<string>::iterator it2;
            it1 = database[i].begin();
            it2 = database[N-1].begin();
            for(;it1 != database[i].end() && it2 != database[N-1].end() ;it1++,it2++)
            {
                if(*it1 == it3->name)
                {
                    auto r = contains(decisions, *it2);
                    if(r != &(*decisions.end()))
                    {
                        (*r).n++;
                    }
                    else
                    {
                        elem e;
                        e.name = *it2;
                        e.n=1;
                        decisions.push_front(e);
                    }
                }
            }
            info = info + (double)it3->n/(double)n*I(decisions,it3->n);
        }
        cout<<"Info(a"<<i+1<<",T) = "<<info<<endl;
        Gain = Inf-info;
        cout<<"Gain(a"<<i+1<<",T) = "<<Gain<<endl;
        SplitInf = I(records[i],database[i].size());
        cout<<"SplitInfo(a"<<i+1<<",T) = "<<SplitInf<<endl;
        cout<<"GainRatio(a"<<i+1<<",T) = "<<Gain/SplitInf<<endl;
       if(Gain/SplitInf>gainRatioMax)
       {
           gainRatioMax = Gain/SplitInf;
           xDecisive = i;
        }

    }
    cout<<"GainRatioMax: "<<gainRatioMax<<endl;
    //tabela decyzyjna po podziale

    podzial(records, database, xDecisive, N, 0);
    /*
    cout<<"\n\n\nAtrybut a"<<xDecisive+1<<": "<<endl;
    //N = 4;
    list<string> newDatabase[N];
    list<elem>::iterator it;
    list<string>::iterator it1;
    it = records[xDecisive].begin();

    list<int> indexes;
    int index=0;
    for(;it!=records[xDecisive].end();it++)
    {
        index=0;
        indexes.clear();
        it1 = database[xDecisive].begin();
        for(;it1!=database[xDecisive].end();it1++)//zapisuje indeksy tych rekordow, ktore mnie interesuja
        {
            if(checkDecisiveArg(it->name,*it1,xDecisive))
            {
                indexes.push_front(index);
            }
            index++;
        }

        for(int i = 0;i < N;i++)//tworze nowa baze zawierajaca wylacznie rekordy ktore mnie interesuja
        {
            index = 0;

            it1 = database[i].begin();
            for(;it1!=database[i].end();it1++)
            {
                if(find(indexes.begin(),indexes.end(),index)!=indexes.end())
                {
                    newDatabase[i].push_front(*it1);
                    cout<<*it1<<" ";
                }
                index++;
            }
            cout<<endl;

        }
        cout<<"---------------------"<<endl;
    }
    */

    return 0;
}
