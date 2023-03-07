#include<iostream>
#include <list>
#include<fstream>
#include <string>
using namespace std;

void print(list<string>* myContainer, int n)
{
    cout << "Database elements:\n\n";

    // Iterating over myContainer elements
    // Each element is a list on its own
    for (int i = 0; i < n; i++)
    {
        print(myContainer[i], i);
    }
}
int main()
{
    fstream file;
    string record="", a="";
    int n=1,numOfRec = 0;
    file.open("gielda.txt");
    getline(file, record);
    numOfRec++;
    for(int i = 0; i<record.length();i++)
        if(record[i]==',')
            n++;
    cout<<n<<endl;

    list<string> database[n];
    while(!file.eof())
    {
        n=0;
        a="";
        getline(file, record);
        for(int i=0;i<record.length();i++)
        {
            if(!record[i]==',')
            {
                a+=record[i];
            }
            else if(record[i]==',' || i==record.length()-1)
            {
                database[n].push_front(a);
                n++;
                a="";
            }
        }
        cout<<record<<endl;
    }

    file.close();
    return 0;
}
