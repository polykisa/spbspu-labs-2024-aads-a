#include "print.hpp"

size_t zakozhurnikova::getMaxSize(const List< pair >& l)
{
  size_t max = 0;
  for (pair p : l)
  {
    size_t size = p.second.size();
    max = std::max(max, size);
  }
  return max;
}

void zakozhurnikova::printNames(const List<pair>& l)
{
  for (auto it = l.begin(); it != l.end(); ++it)
  {
    std::cout << it->first;
    auto temp = it;
    std::advance(temp, 1);
    if (temp != l.end())
    {
      std::cout << ' ';
    }
  }
  if (l.size() != 0)
  {
    std::cout << '\n';
  }
}

void zakozhurnikova::printByIndex(const List< pair > &l)
{
  size_t maxSize = getMaxSize(l);
  for (size_t i = 0; i < maxSize; ++i)
  {
    size_t printed = 0;
    for (auto it = l.cbegin(); it != l.cend(); ++it)
    {
      if (i >= it->second.size())
      {
        continue;
      }
      auto temp = it->second.cbegin();
      std::advance(temp, i);
      std::cout << (printed++ == 0 ? "" : " ") << *(temp);
    }
    std::cout << '\n';
  }
}

void zakozhurnikova::printSums(const List< pair >& l, bool& overflow)
{
  constexpr size_t max = std::numeric_limits< size_t >::max();
  size_t maxSize = getMaxSize(l);
  List < size_t > listSum;
  for (size_t i = 0; i < maxSize; ++i)
  {
    size_t sum = 0;
    for (pair p : l)
    {
      if (i >= p.second.size())
      {
        continue;
      }
      if (max - sum > *(std::next(p.second.cbegin(), i)))
      {
        sum += *(std::next(p.second.cbegin(), i));
      }
      else
      {
        overflow = true;
      }
    }
    listSum.push_back(sum);
  }
  if (overflow)
  {
    throw std::range_error("Failed input numbers with overflow");
  }
  for (auto it = listSum.begin(); it != listSum.end(); ++it)
  {
    std::cout << *(it);
    if (std::next(it, 1) != listSum.end())
    {
      std::cout << ' ';
    }
  }
  if (maxSize == 0)
  {
    std::cout << "0";
  }
}
