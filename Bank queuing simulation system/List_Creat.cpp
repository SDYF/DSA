#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    srand((int)time(NULL));
    ofstream fs;
    fs.open("List.txt");
    char VIP, name;
    char *name_1;
    int arrival, service_time, n, i, p, j, total = 0;
    n = 15 + rand() % 21;
    fs << n << endl;

    for (i = 0; i < n; i++)
    {

        p = 3 + rand() % 4;
        name_1 = new char[p + 1];
        for (j = 0; j <= p - 1; j++)
        {
            name = (char)(97 + rand() % 26);
            name_1[j] = name;
            //cout << name_1[j];
        }
        //    cin >> VIP;
        name_1[p] = '\0';

        arrival = rand() % 480;

        service_time = 5 + rand() % 26;

        if (rand() % 4 == 0)
            VIP = '1';
        else
            VIP = '0';

        fs << VIP << ' ' << name_1 << ' ' << arrival << ' ' << service_time << endl;

        total += service_time;

        for (j = 0; j <= p; j++)
            name_1[j] = '\0';
    }
    fs.close();
    //   cout << total << endl;
}