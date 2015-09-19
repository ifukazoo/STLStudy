#ifndef _ALGORITHMS_H_
#define _ALGORITHMS_H_

template<typename ForwardIt>
void print_container(ForwardIt first, ForwardIt last)
{
  while (first != last) {
    std::cout << *first << " ";
    first++;
  }
  std::cout << std::endl;
}

template <typename InputIterator,  typename OutputIterator,  typename Predicate>
OutputIterator copy_if(InputIterator first,  InputIterator last,
    OutputIterator result,  Predicate pred)
{
  while (first != last) {
    if (pred(*first)) {
      *result++ = *first;
    }
    ++first;
  }
  return result;
}

#endif
