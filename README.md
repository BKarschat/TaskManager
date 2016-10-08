# TaskManager
TaskManager


The TaskManager should manage your tasks on one place in your code. So it is able to watch how many threads are already in use and returns a future wich you can use for storing results.
It is very small and you just get the future back. By using tasks instead of threads, the you don't have to care about joinable or detachble threads.
Just call wait() on the future and use get() for the returning value (if there is anyone). Call the decreaseNumberOfThreads() function in the end.
Compile it with -std=c++14!


Example:
TaskManager manager{2}; //taskmanager with max 2 threads

//typedef for function pointer
typedef std::function<int(std::string) > Funcp;                            

//bind memberfunction
Funcp foo = std::bind(&Class::MemberFunc, object, std::placeholders::_1);   

//Or use lamdas!  
auto funcptr = [](){return true;};                        

//you are able to use function from 0 to many params
auto future = manager.getThread(*foo,"test");

//wait for the thread
future.wait();                               

//get the return value
auto bar = future.get();                     

//Decrease number. Still working on that...
manager.decreaseNumberOfThreads();



