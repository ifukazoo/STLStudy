#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

template<typename T, std::size_t SIZE>
std::size_t array_length(const T (&)[SIZE]) {
  return SIZE;
}
#endif

