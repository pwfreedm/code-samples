/*
  Filename   : template_vector_generation.cpp
  Author     : Peter Freedman
  Description: Demo implementation of a thread safe queue.
*/


#include <vector>
//includes distributions and rand
#include <random>
//for ranges::generate
#include <algorithm> 

using std::vector;
/** Generates a vector that is aligned on a cache boundary.
*
* @param s - the size of the vector to generate. 
* @param lowerBound - the lower bound of the range for the values in the vector
* @param upperBound - the upper bound of the range of the values in the vector
*
* @return - a vector of size s that is aligned.
*/
template<typename T>
vector<T>
generateVector (const size_t s, const T &lowerBound, const T &upperBound)
{
    //conditional_t evaluates at compile time to decide if an int or real dist is needed.
  using uniform_distribution =
    std::conditional_t<std::is_integral_v<T>, std::uniform_int_distribution<T>,
                       std::uniform_real_distribution<T>>;

  vector<T> ret (s);

  //can be replaced with random number generation method of choice
  static std::minstd_rand rand (0);
  uniform_distribution dist (lowerBound, upperBound);

  std::ranges::generate (ret, [&] { return dist (rand); });
  return ret;
}