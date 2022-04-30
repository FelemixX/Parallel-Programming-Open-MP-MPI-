#include <iostream>
#include <fstream>
#include <omp.h>
#include <string>
#include <windows.h>
#include <time.h>

using namespace std;

ofstream stream("philosophers.txt");

const int philosopherCount = 5;
bool forks[philosopherCount];

string getTime()
{
    SYSTEMTIME timeStamp; //структура для определения времени 
    GetLocalTime(&timeStamp); //получаем текущее время, пишем в timeStamp
    return to_string(timeStamp.wHour) + ":" + to_string(timeStamp.wMinute) + ":" + to_string(timeStamp.wSecond) + ":" + to_string(timeStamp.wMilliseconds);
}


void changeForksAvailability(int forkLeft, bool newValue)
{
#pragma omp critical(forks) //делаем так, чтобы в один момент можно было выполнять не больше одной строки 
    {
        forks[forkLeft] = newValue; //вилка слева от философа
        forks[forkLeft + 1] = newValue; //вилка справа от философа
    }
}

bool checkForks(int forkLeft)
{
    bool isFree = false;
#pragma omp critical(check)
    {
#pragma omp flush(forks) //делаем так, чтобы все команды выполнялись последовательно, а не разбросанно
        isFree = forks[forkLeft] && forks[forkLeft + 1]; //если обе вилки свободны - маркер становится истинным
        if (isFree) changeForksAvailability(forkLeft, false); //если обе вилки свободны, то философ может их взять
    }
    return isFree;
}

void writeAndDump(string txt)
{
#pragma omp critical(out)
    {
        cout << txt;
        stream << txt;
    }
}

class Philosopher
{
    int philosopherNumber;
    bool thinking;
public:
    Philosopher()
    {
        philosopherNumber = 0; //номер философа
    }
    Philosopher(int num)
    {
        philosopherNumber = num;
        for (int i = 0; i < philosopherCount; i++)
        {
            forks[i] = true; //вилка свободна
        }
    }
    void eat()
    {
        int forkLeft = philosopherNumber - 1; //первая вилка находится слева от философа
        int forkRight = forkLeft < philosopherCount ? forkLeft + 1 : 0;  //если слева есть свободная вилка, то подбираем вилку справа. Если вилки слева нет, то не едим. Надо подумать...
        bool check = checkForks(forkLeft);
        if (check) //если оказалось так, что философ может взять две вилки, то он может поесть 
        {
            thinking = false; //изначально философ не думает
            string time = getTime();
            string stringOut = "Philosopher " + to_string(philosopherNumber) + " has a meal with a " + time + " fork " + to_string(forkLeft) + " and " + to_string(forkRight) + "\n";
            writeAndDump(stringOut);
            int timeWait = rand() * philosopherNumber % 9000 + 1000;
            Sleep(timeWait);
            time = getTime();
            stringOut = "Philosopher " + to_string(philosopherNumber) + " had meal at " + time + " after " + to_string(timeWait / 1000) + " second(s) " + "\n";
            writeAndDump(stringOut);
            changeForksAvailability(forkLeft, true);
        }
        else
        {
            if (!thinking) //а если не может взять, то время подумать
            {
                string strOut = "Philosopher " + to_string(philosopherNumber) + " is thinking" + "\n";
                writeAndDump(strOut);
                thinking = true;
            }
        }

    }
};
int main(void)
{
    setlocale(LC_ALL, "Russian");
    Philosopher ph[philosopherCount + 1]; //выбираем первого философа
    for (int i = 1; i <= philosopherCount; i++)
    {
        ph[i] = Philosopher(i); //итерируем остальных философов
    }
    time_t timeStamp;
    time_t timeStampTmp;
    time(&timeStamp);
    time(&timeStampTmp);
    while ((timeStampTmp - timeStamp) < 100000) //пока разница между временем конца и начала трапезы больше 10
    {
        time(&timeStampTmp);
#pragma omp parallel num_threads(philosopherCount) //философы - количество потоков
        {
            int threadNum = omp_get_thread_num();
            ph[threadNum + 1].eat(); //можно покушать
        }
        cout << "End of another iteration \n";
        stream << "-----------------------\nEnd of another iteration\n-----------------------\n";
    }
    stream.close();
    return 0;
}
