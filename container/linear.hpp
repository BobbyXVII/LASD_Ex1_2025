
#ifndef LINEAR_HPP
#define LINEAR_HPP

/* ************************************************************************** */

#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class LinearContainer : virtual public PreOrderTraversableContainer<Data>, virtual public PostOrderTraversableContainer<Data>{

private:

  // ...

protected:

  using Container::size;

public:

  // Destructor
  virtual ~LinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  LinearContainer & operator=(const LinearContainer &) = delete;

  // Move assignment
  LinearContainer & operator=(LinearContainer &&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const LinearContainer &) const noexcept;
  bool operator!=(const LinearContainer &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data & operator[](const ulong) const = 0;

  virtual const Data & Front() const;

  virtual const Data & Back() const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  void Traverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  void PreOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  void PostOrderTraverse(TraverseFun) const override;

};

/* ************************************************************************** */

template <typename Data>
class MutableLinearContainer: virtual public LinearContainer<Data>,
 virtual public PreOrderMappableContainer<Data>,
  virtual public PostOrderMappableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~MutableLinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  MutableLinearContainer & operator=(const MutableLinearContainer &) = delete;

  // Move assignment
  MutableLinearContainer & operator=(MutableLinearContainer &&) noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  virtual Data & operator[](const ulong) = 0;

  virtual Data & Front() = 0;

  virtual Data & Back() = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  inline void Map(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  inline void PreOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  inline void PostOrderMap(MapFun) override;

};

template <typename Data>
class SortableLinearContainer : virtual public MutableLinearContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~SortableLinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  SortableLinearContainer & operator=(const SortableLinearContainer &) = delete;

  // Move assignment
  SortableLinearContainer & operator=(SortableLinearContainer &&) noexcept = delete;

  /* ************************************************************************ */

  // Specific member function

  virtual void Sort() = 0;

protected:

  // Auxiliary member functions

};

/* ************************************************************************** */

}

#include "linear.cpp"

#endif