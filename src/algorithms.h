#ifndef _ALGORITHMS_H_
#define _ALGORITHMS_H_

template<class ForwardIt>
void print_container(ForwardIt first, ForwardIt last)
{
  while (first != last) {
    std::cout << *first << " ";
    first++;
  }
  std::cout << std::endl;
}

#endif
