#ifndef NODE_HPP
#define NODE_HPP

namespace lebedev
{
  namespace detail
  {
    template< class T >
    struct Node
    {
      T data_;
      Node * next_;
      Node * prev_;

      Node();
      Node(const T & data, Node * next, Node * prev);
      ~Node() = default;
    };

    template< class T >
    Node< T >::Node():
      data_(0),
      next_(nullptr),
      prev_(nullptr)
    {}
    template< class T >
    Node< T >::Node(const T & data, Node * next, Node * prev):
      data_(data),
      next_(next),
      prev_(prev)
    {}
  }
}

#endif
