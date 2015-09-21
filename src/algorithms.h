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
template<typename ForwardIt>
void print_pair_container(ForwardIt first, ForwardIt last)
{
  std::string sep("");
  while (first != last) {
    std::cout << sep << "(" << first->first << ", " << first->second << ")";
    sep = " ";
    first++;
  }
  std::cout << std::endl;
}


#ifdef _MSC_VER
// MSVC

#if _MSC_VER < 1600 // visual studio 2008 := 1500
#define NOT_IMPLEMENTS
#endif

#else
// GCC

#if __cplusplus < 201103L
#define NOT_IMPLEMENTS
#endif

#endif

#ifdef NOT_IMPLEMENTS
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

#endif // NOT_IMPLEMENTS

#endif
