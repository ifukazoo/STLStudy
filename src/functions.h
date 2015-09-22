#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

template<typename T, std::size_t SIZE>
std::size_t array_length(const T (&)[SIZE])
{
  return SIZE;
}

template<typename MapIterator>
void print_key_val(MapIterator i)
{
  std::cout << "(" << i->first << ", " << i->second << ")" << std::endl;
}

inline void print_sep(int n)
{
  std::cout << "========== " << n << " ==========" << std::endl;
}
#endif

