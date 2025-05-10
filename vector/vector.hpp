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

  // Nessun membro privato aggiuntivo

protected:

  using Container::size;

  Data* elements = nullptr;

public:

  // Default constructor
  Vector() = default;

  // Constructor with initial size
  Vector(const unsigned long initialSize) {
    elements = new Data[initialSize]{};
    size = initialSize;
  }

  // Constructor from TraversableContainer
  inline Vector(const TraversableContainer<Data>&);

  // Constructor from MappableContainer (rvalue)
  inline Vector(MappableContainer<Data>&&);

  // Copy constructor
  Vector(const Vector<Data>&);

  // Move constructor
  Vector(Vector<Data>&&) noexcept;

  // Destructor
  virtual ~Vector() { delete[] elements; }

  // Copy assignment
  inline Vector<Data>& operator=(const Vector<Data>&);

  // Move assignment
  inline Vector<Data>& operator=(Vector<Data>&&) noexcept;

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

  // Nessun membro privato aggiuntivo

protected:

  // Nessun using necessario qui, ereditato da Vector
  using Container::size;

public:

  // Default constructor
  SortableVector() = default;

  // Constructor with initial size
  inline SortableVector(unsigned long initialSize) : Vector<Data>(initialSize) {}

  // Constructor from TraversableContainer
  inline SortableVector(const TraversableContainer<Data>& container) : Vector<Data>(container) {}

  // Constructor from MappableContainer (rvalue)
  inline SortableVector(MappableContainer<Data>&& container) : Vector<Data>(std::move(container)) {}

  // Copy constructor
  inline SortableVector(const SortableVector<Data>& vector) : Vector<Data>(vector) {}

  // Move constructor
  inline SortableVector(SortableVector<Data>&& vector) noexcept : Vector<Data>(std::move(vector)) {}

  // Destructor
  virtual ~SortableVector() = default;

  // Copy assignment
  inline SortableVector<Data>& operator=(const SortableVector<Data>& vector);

  // Move assignment
  inline SortableVector<Data>& operator=(SortableVector<Data>&& vector) noexcept;

protected:

  // Funzioni ausiliarie, se necessarie

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
