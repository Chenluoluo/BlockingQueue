#include <iostream>
#include <memory>
#include <functional>
#include <unistd.h>
#include "../BlockingQueue.h"
#include "../Thread.h"
void* Produce1(std::shared_ptr<BlockingQueue<int> > queue)
{
    while(true)
    {
        const int product=rand()%1000+1;
        std::cout<<"Produce1: "<<product<<std::endl;
        queue->put(product);
        sleep(rand()%5);
    }

}
void* Produce2(std::shared_ptr<BlockingQueue<int> > queue)
{
    while(true)
    {
        const int product=rand()%1000+1;
        std::cout<<"Produce2: "<<product<<std::endl;
        queue->put(product);
        sleep(rand()%5);
    }

}
void* Consome1(std::shared_ptr<BlockingQueue<int> > queue)
{
    while(true)
    {
        int product=queue->take();
        std::cout<<"Consome1: "<<product<<std::endl;
    }
}

void* Consome2(std::shared_ptr<BlockingQueue<int> > queue)
{
    while(true)
    {
        int product=queue->take();
        std::cout<<"Consome2: "<<product<<std::endl;
    }
}
int main() {

    std::shared_ptr<BlockingQueue<int> > blockingQueue(new BlockingQueue<int>);
    Thread thread1(std::bind(Produce1,blockingQueue));
    Thread thread2(std::bind(Produce2,blockingQueue));
    Thread thread3(std::bind(Consome1,blockingQueue));
    Thread thread4(std::bind(Consome2,blockingQueue));

    thread1.run();
    thread2.run();
    thread3.run();
    thread4.run();

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();

    while (1);

    return 0;
}