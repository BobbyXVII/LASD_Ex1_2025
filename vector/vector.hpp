#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector : virtual public MutableLinearContainer<Data>, virtual public ResizableContainer {

private:

protected:

  using Container::size;

  Data* elements = nullptr;

public:

  // Default constructor
  Vector() = default;

  // Constructor with initial size
  Vector(const unsigned long);

  // Constructor from TraversableContainer
  Vector(const TraversableContainer<Data>&);

  // Constructor from MappableContainer (rvalue)
  Vector(MappableContainer<Data>&&);

  // Copy constructor
  Vector(const Vector<Data>&);

  // Move constructor
  Vector(Vector<Data>&&) noexcept;

  // Destructor
  virtual ~Vector();

  // Copy assignment
  Vector<Data>& operator=(const Vector<Data>&);

  // Move assignment
  Vector<Data>& operator=(Vector<Data>&&) noexcept;

  // Comparison operators
  bool operator==(const Vector<Data>&) const noexcept;
  inline bool operator!=(const Vector<Data>&) const noexcept;

  // Access operators (Mutable)
  Data& operator[](unsigned long) override;

  Data& Front() override;

  Data& Back() override;

  // Access operators (Immutable)
  const Data& operator[](unsigned long) const override;

  const Data& Front() const override;

  const Data& Back() const override;

  // Resize function
  void Resize(unsigned long) override;

  // Clear function
  void Clear() override;

protected:

  // Funzioni ausiliarie, se necessarie

};

/* ************************************************************************** */

template <typename Data>
class SortableVector : virtual public Vector<Data>, virtual public SortableLinearContainer<Data> {

private:

protected:

  using Container::size;

public:

  // Default constructor
  SortableVector() = default;

  // Constructor with initial size
  SortableVector(unsigned long initialSize) : Vector<Data>(initialSize) {}

  // Constructor from TraversableContainer
  SortableVector(const TraversableContainer<Data>& container) : Vector<Data>(container) {}

  // Constructor from MappableContainer (rvalue)
  SortableVector(MappableContainer<Data>&& container) : Vector<Data>(std::move(container)) {}

  // Copy constructor
  SortableVector(const SortableVector<Data>& vector) : Vector<Data>(vector) {}

  // Move constructor
  SortableVector(SortableVector<Data>&& vector) noexcept : Vector<Data>(std::move(vector)) {}

  // Destructor
  virtual ~SortableVector() = default;

  // Copy assignment
  SortableVector<Data>& operator=(const SortableVector<Data>& vector);

  // Move assignment
  SortableVector<Data>& operator=(SortableVector<Data>&& vector) noexcept;

protected:

  // Funzioni ausiliarie, se necessarie

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
