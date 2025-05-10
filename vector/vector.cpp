#include "vector.hpp"

namespace lasd {

/* ************************************************************************** */

template<typename Data>
Vector<Data>::Vector(const ulong newsize){
    size = newsize;
    elements= new Data[size] {};
}

template<typename Data>
Vector<Data>::Vector(const TraversableContainer<Data> & container) : Vector(container.Size()){
    ulong index = 0;
    container.Traverse(
        [this, &index](const Data & dat) {
            Elements[index++] = dat;
        }
    );
}

template<typename Data>
Vector<Data>::Vector(MappableContainer<Data> && container) : Vector(container.Size()){
    ulong index = 0;
    container.Map(
        [this, &index](const Data & dat) {
            Elements[index++] = std::move(dat);
        }
    );
}

/* ************************************************************************** */
//copy constructor
template<typename Data>
Vector<Data>::Vector(const Vector<Data> & vector) {
    size = vector.size;
    Elements = new Data[size];
    std::copy(vector.Elements, vector.Elements + size, Elements);
}

//move constructor
template<typename Data>
Vector<Data>::Vector(const Vector<Data> & vector) {
    std::swap(size,vector.size);
    std::swap(Elements, vector.Elements);
}
/* ************************************************************************** */
//destructor
template<typename Data>
Vector<Data>::~Vector() {
    delete[] Elements;
}
/* ************************************************************************** */
//copy assignment
template<typename Data>
Vector<Data> & Vector<Data>::operator=(const Vector<Data> & vec) {
    Vector<Data> * tmpvec = new Vector<Data>(vec);
    std::swap(*tmpvec, *this);
    delete tmpvec;
    return *this;
}

//move assignment
template<typename Data>
Vector<Data> & Vector<Data>::operator=(Vector<Data> && vec) noexcept {
    std::swap(size,vec.size);
    std::swap(Elements,vec.Elements);
    return *this;
}
/* ************************************************************************** */
//comparison operators
template<typename Data>
bool Vector<Data>::operator==(const Vector<Data> & vector) const noexcept {
    if (size == vector.size) {
        for(unsigned long index = 0; index < size; ++index) {
            if(Elements[index] != vector.elements[index]) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

template<typename Data>
inline bool Vector<Data>::operator!=(const Vector<Data> & vector) const noexcept {
    return !(*this = vector);
}
/* ************************************************************************** */
// specific member function - from MutableLinearContainer
template<typename Data>
Data & Vector<Data>::operator[](const unsigned long index) {
    return const_cast<Data &>(static_cast<const Vector<Data> *>(this)->operator[](index));
}

template<typename Data>
Data & Vector<Data>::Front() {
    return const_cast<Data &>(static_cast<const Vector<Data> *>(this)->Front());
}


template<typename Data>
Data & Vector<Data>::Back() {
    return const_cast<Data &>(static_cast<const Vector<Data> *>(this)->Back());
}
/* ************************************************************************** */
// specific member function - from LinearContainer
template<typename Data>
const Data & Vector<Data>::operator[](const ulong index) const {
    if (index < size) {
        return elements[index];
    }else{
        throw std::__throw_out_of_range("Access at index " + std::to_string(index) + ";  vector size " + std::to_string(size) + ".");
    }
}

template<typename Data>
const Data & Vector<Data>::Front() const{
    if (size != 0) {
        return Elements[0];
    }else{
        throw std::length_error("Access to an empty vector.");
    }
}


template<typename Data>
const Data & Vector<Data>::Back() const{
    if (size != 0) {
        return Elements[size - 1];
    }else{
        throw std::length_error("Access to an empty vector.");
    }
}

/* ************************************************************************** */
template <typename Data>
inline SortableVector<Data> &
SortableVector<Data>::operator=(const SortableVector<Data> &vec) {
  Vector<Data>::operator=(vec);
  return *this;
}

template <typename Data>
inline SortableVector<Data> &
SortableVector<Data>::operator=(SortableVector<Data> &&vec) noexcept {
  Vector<Data>::operator=(std::move(vec));
  return *this;
}


}