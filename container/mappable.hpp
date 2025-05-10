
#ifndef MAPPABLE_HPP
#define MAPPABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "traversable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class MappableContainer : virtual public TraversableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~MappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  MappableContainer & operator=(const MappableContainer &) = delete;

  // Move assignment
  MappableContainer & operator=(MappableContainer &&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const MappableContainer &) const noexcept;
  bool operator!=(const MappableContainer &) const noexcept;

  /* ************************************************************************ */

  // Specific member function

  using MapFun = std::function<void(Data &)>;

  // type Map(argument) specifiers;

};

/* ************************************************************************** */

template <typename Data>
class PreOrderMappableContainer : virtual public MappableContainer<Data>,
  virtual public PreOrderTraversableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~PreOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  PreOrderMappableContainer & operator(const PreOrderMappableContainer &) = delete;

  // Move assignment
  PreOrderMappableContainer & operator(PreOrderMappableContainer &&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PreOrderMappableContainer &) const noexcept;
  bool operator!=(const PreOrderMappableContainer &) const noexcept;

  /* ************************************************************************ */

  // Specific member function

  using typename MappableContainer<Data>::MapFun;

  // type PreOrderMap(argument) specifiers;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  // type Map(argument) specifiers; // Override MappableContainer member

};

/* ************************************************************************** */

template <typename Data>
class PostOrderMappableContainer : virtual public MappableContainer<Data>,
  PostOrderTraversableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~PostOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  PostOrderMappableContainer &operator=(const PostOrderMappableContainer &) = delete;

  // Move assignment
  PostOrderMappableContainer &operator=(PostOrderMappableContainer &&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PostOrderMappableContainer &) const noexcept;
  bool operator!=(const PostOrderMappableContainer &) const noexcept;

  /* ************************************************************************ */

  // Specific member function

  // using typename MappableContainer<Data>::MapFun;

  // type PostOrderMap(argument) specifiers;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  // type Map(argument) specifiers; // Override MappableContainer member

};

/* ************************************************************************** */

}

#include "mappable.cpp"

#endif
