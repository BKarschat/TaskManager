/*Copyright (c) <2016>, <Bastian Karschat>
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "TaskManager.hpp"

/*how to use!
typedef std::function<void(std::string) > Funcp;
Funcp foo = std::bind(&Class::MemberFunc, object, std::placeholders::_1);
Or use lamdas!  auto funcptr = [](){return true;};
*/


//returns futures
template <typename F, typename ...Args>
decltype(auto) TaskManager::getThread(F &func_ptr, Args &&... params)
{
std::lock_guard<std::shared_timed_mutex> lock(rwMux);
if (iNumberOfThreads<5) {
  iNumberOfThreads ++;
  return reallyasync(func_ptr, params...);
} else {

  std::cout << "to many Threads! Using other one!\n";

  return notreallyasync(func_ptr, params...);
}

}



//creates thread and return the future
template <typename F, typename... Args>
inline
auto TaskManager::reallyasync(F &&func_ptr, Args &&... args)
{
  return std::async(std::launch::async, std::forward<F>(func_ptr), std::forward<Args>(args)...);
}

//maybe creates thread and returns the future
template <typename F, typename ...Args>
inline
auto TaskManager::notreallyasync(F &&func_ptr, Args &&... args)
{
  return std::async(std::forward<F> (func_ptr),std::forward<Args>(args)...);
}


TaskManager::TaskManager()
{
  iNumberOfThreads = 0;
}

//locked exclusive for one writer
void TaskManager::decreaseNumberOfThreads()
{
  std::lock_guard<std::shared_timed_mutex> lock(rwMux);
  if(iNumberOfThreads!=0)
  iNumberOfThreads--;
}

//multiple reader can use the function
int TaskManager::getNumberOfThreads()
{
  std::shared_lock<std::shared_timed_mutex> lock(rwMux);
  return iNumberOfThreads;
}

TaskManager::~TaskManager()
{
}
