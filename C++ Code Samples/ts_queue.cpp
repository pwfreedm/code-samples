/*
  Filename   : ts_queue.cpp
  Author     : Peter Freedman
  Description: Demo implementation of a thread safe queue.
*/

//For exclusivity
#include <mutex>
#include <condition_variable>

//For data storage
#include <queue>





template <typename T> 
struct queue 
{
  //private to force thread safe uses only.
  private:
  //lineReady is not needed for this example, but this is generically
  //how condition variables operate.
   bool lineReady{false};
   std::mutex m;
   std::condition_variable cv;
   std::queue<T> data;
  
  public:

  /** Pushes an element into the back of the shared queue.
  *
  * @param element - the element to be pushed onto the queue.
  */
  void
  enque (const T& element)
  {
    {
    std::lock_guard lk (m);
    data.push (element);
    lineReady = true;
    }
    cv.notify_one();
  }

  /** Pops the front element from the queue. 
  *
  * @return - an element from the queue
  */
  T
  dequeue ()
  {
    T line;
    {  
      std::unique_lock lk (m);
      cv.wait(lk, [&]{ return lineReady;});

      line = data.front();
      data.pop ();
      lineReady = !data.empty();

      lk.unlock();
    }
    cv.notify_one();
    return line;
  }
};