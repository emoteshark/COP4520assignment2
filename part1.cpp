#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <time.h>
#include <cstdlib>
#include <unistd.h>

// number of guests at the party
#define GUESTS 20

/*
Strategy:
The first guest will find a cupcake at the end 100% of the time, and should eat it. Assuming
this guest can see the cupcake after leaving the labryinth (which is not specified but I dont
see how it's solvable otherwise), the first guest should wait and count every time the plate is left
empty after a guest leaves, because each guest should only eat a cupcake (leaving the plate empty) on
their first time in the labryinth. If they enter again they should leave the cupcake on the plate. This
way every time a guest passes through and the plate is empty the counter will know that that guest is going
through for the first time.
*/

std::mutex mtx;

int count = 0;
int cupcake[GUESTS + 1];
int threadID;

// this determines which guest goes next
int turn = -1;

void enterParty(int threadID)
{
    while (1)
    {
        

        if (turn == threadID)
        {
            mtx.lock();
            if (cupcake[threadID] == 0)
            {
                std::cout << "guest " << threadID << " ate a cupcake" << std::endl;
                cupcake[threadID] = 1;
                count++;
            }
            else
            {
                std::cout << "guest " << threadID << " left a cupcake" << std::endl;
            }
            if (count < GUESTS)
                turn = (rand() % (GUESTS - 1 + 1)) + 1;
            mtx.unlock();
            
        }
        if (count == GUESTS)
        {
            return;
        }

        //turn = (rand() % (GUESTS - 1 + 1)) + 1;
    }
}

int main()
{
    for (int i = 1; i <= GUESTS; i++)
    {
        cupcake[i] = 0;
    }

    srand(time(0));
    //turn = (rand() % (GUESTS - 1 + 1)) + 1;

    // spawn threads
    std::thread threads[GUESTS];
    for (int i = 1; i <= GUESTS; i++)
    {
        threads[i - 1] = std::thread(enterParty, i);
    }

    turn = (rand() % (GUESTS - 1 + 1)) + 1;

    //while(count != GUESTS)
        //sleep(1);

    for (int i = 1; i <= GUESTS; i++)
    {
        threads[i - 1].join();
    }

    /*for (int i = 1; i <= GUESTS; i++)
    {
        std::cout << cupcake[i];
    }*/
    //std::cout << '\n';
    //std::cout << "count is " << count << std::endl;
    std::cout << "all guests have made it through the labryinth" << std::endl;
}
