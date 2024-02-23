#include <iostream> 
#include <thread> 
#include <queue>
#include <mutex>
#include <unistd.h>

/*
Strategy 3:
Since this prompt does not explain how to terminate, I just assumed the minotaur would have
a limited amount of showings available to see the vase, and once that many viewings have occurred
the door would lock and nobody else could see the vase. Guests queue up randomly, some may
never see the vase and some may see it multiple times.
*/

//we have 10 guests and 20 open viewing slots
#define GUESTS 10
#define VIEWS 20

std::mutex mtx;

//tracks how many times the vase has been viewed
int viewcount = 0;

//std::queue<int> guestQ;

int turn = -1;
std::queue<int> gq;


void viewVase(int threadID)
{
    while (1)
    {
        while (turn != threadID && gq.size())
            ;

        if (turn == threadID)
        {
            mtx.lock();
            std::cout<< "guest #" << threadID<< " is in the showroom" << std::endl;
            if(viewcount < VIEWS)
            {
                viewcount++;
            }

            std::cout << "This is viewing #" <<viewcount <<std::endl;

            /*for(int i = 0; i < VIEWS; i++)
              {
              viewcount++;
              }*/
            //std::cout << "inside lock: " << viewcount << std::endl;

            mtx.unlock();

            //std::cout << "outside lock: " << viewcount << std::endl;

            // let the next guy know
            if (gq.size())
            {
                int front = gq.front();
                gq.pop();
                turn = front;
            }
        }

        if (!gq.size())
            return;
    }
}

void print_queue(std::queue<int> q)
{
    std::queue<int> temp = q;
    while (!temp.empty()) 
    {
        std::cout << temp.front()<<" ";
        temp.pop();
    }
    std::cout << '\n';
}


int main()
{
    //std::cout<< "starting count is " <<viewcount << std::endl;

    std::thread threads[GUESTS];

    while(gq.size() < VIEWS)
    {
        gq.push((rand() % (GUESTS - 1 + 1)) + 1);
    }

    std::cout<< "the queue is ";
    print_queue(gq);

    // start the threads
    for(int i = 1; i <= GUESTS; i++)
    {
        threads[i-1] = std::thread(viewVase, i);
    }

    // start the first one
    int front = gq.front();
    gq.pop();
    turn = front;

    while(gq.size())
        sleep(1);

    for(int i = 1; i <= GUESTS; i++)
    {
        threads[i-1].join();
    }

    std::cout << "finished, the view count has been reached" << std::endl;
}
