#include "TaskManager.cpp"
#include <chrono>
#include <mutex>

using namespace std::chrono_literals;

void teste(std::string str)
{
  std::mutex mx;
  std::this_thread::sleep_for(2s);
  std::lock_guard<std::mutex> lock(mx);
  std::cout << str +"\n";
}

int rechne(int a, int b)
{
  return a+b;
}

int main(int argc, char const *argv[]) {

  TaskManager taskManager;

  std::string test,test1,test2;
  test ="blaa";
  test1= "test1";
  test2 = "test2";

  void (*foo)(std::string);
  foo =  &teste;

  int (*bar)(int,int);
  bar = &rechne;

  auto task1 = taskManager.getThread(*bar,2,4);
  auto task = taskManager.getThread(*bar,2,6);




  /*task.wait();
  threadPool.decreaseNumberOfThreads();
  auto task6 = threadPool.getThread(*foo,"juuuuu");
  task1.wait();
  threadPool.decreaseNumberOfThreads();
  task2.wait();
  threadPool.decreaseNumberOfThreads();
  task6.wait();
  threadPool.decreaseNumberOfThreads();
  task3.wait();
  threadPool.decreaseNumberOfThreads();
  task4.wait();
  threadPool.decreaseNumberOfThreads();
  task5.wait();
  threadPool.decreaseNumberOfThreads();
  */

  //Eigentlich sollte die Ausgabe beides mal gelingen. aber aus irgendeinem grund macht er das nicht. Ich hab auch schon die beiden Tasks vertauscht aber der Task1 macht probleme. Beim task1.get() tritt ein Fehler auf..
  //Vielleicht findest du wo ;) Danke!
    std::mutex mu;

    task1.wait();
    auto blubb = task1.get();
    {
    std::lock_guard<std::mutex> lock(mu);
    std::cout << blubb << std::endl;
    }

    std::cout << taskManager.getNumberOfThreads() << std::endl ;
    taskManager.decreaseNumberOfThreads();
    taskManager.decreaseNumberOfThreads();
    task.wait();
    std::cout << task.get() << std::endl;
    std::cout << taskManager.getNumberOfThreads() << std::endl ;


  //task.get();

  return 0;
}
