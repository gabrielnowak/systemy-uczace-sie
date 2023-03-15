#include<iostream>
#include <list>
#include<algorithm>
#include<fstream>
#include <string>
using namespace std;

struct elem {
        string name;
        int n;//number of occurs
    };

void print(list<string>* myContainer, int n)
{
    cout << "Database elements:\n\n";

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
int main()
{
    fstream file;
    string record="", a="";
    int n=1,N;
    file.open("gielda.txt");
    getline(file, record);
    //licze ilosc atrybutow w tabeli decyzyjnej
    n = getNumOfArgs(record);
    N=n;
    cout<<n<<endl;//wypisuje ilosc atrybutow

    list<string> database[n];//moja tabela wejsciowa
    list<elem> records[n];//tabela wszystkich mozliwych atrybutow wraz z iloscia poszczegolnych wystapien
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
    //n = getNumOfArgs(record);
    for(int i = 0; i<N;i++)
    {
        cout<<"Atrybut "<<i+1<<": "<<endl;
        list<elem>::iterator it;
        for(it = records[i].begin(); it!= records[i].end();it++)
            cout<<it->name<<" "<<it->n<<endl;
        cout<<"Ilosc mozliwych wariantow atrybutu "<<i+1<<": "<<records[i].size()<<endl;
    }
    file.close();
    return 0;
}
