
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

/**
    c++14
    TaskManager.cpp
    Purpose: Create a new thread to execute given function.

    @author Bastian Karschat
    @version 1.0 08/10/16
*/


#include <thread>
#include <vector>
#include <future>
#include <mutex>
#include <shared_mutex>
#include <chrono>
#include <iostream>


using std::thread;

class TaskManager{
public:
  TaskManager(int maxThreads);
  ~TaskManager();
  int getNumberOfThreads();
  template <typename F, typename ...Args>
  decltype(auto) getThread(F &func_ptr, Args &&... params);
  bool stopped;
  void stopThread(int ThreadId);
  void decreaseNumberOfThreads();
private:
  std::mutex mux;
  std::shared_timed_mutex rwMux;
  int maxNumberOfThreads;
  template <typename F, typename ...Args>
  auto notreallyasync(F &&func_ptr, Args &&... args);
  template <typename F, typename ...Args>
  auto reallyasync(F&& func_ptr, Args &&... args);
  int iNumberOfThreads;
  std::condition_variable cond;
};
