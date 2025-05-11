namespace lasd {

/* ************************************************************************** */

template<typename Data>
Vector<Data>::Vector(const unsigned long newsize){
    size = newsize;
    elements = new Data[size] {};
}

template<typename Data>
Vector<Data>::Vector(const TraversableContainer<Data> & container) 
: Vector(container.Size()){
    unsigned long index = 0;
    container.Traverse(
        [this, &index](const Data & dat) {
            elements[index++] = dat;
        }
    );
}

template<typename Data>
Vector<Data>::Vector(MappableContainer<Data> && container) 
: Vector(container.Size()){
    unsigned long index = 0;
    container.Map(
        [this, &index](Data & dat) {
            elements[index++] = std::move(dat);
        }
    );
}

/* ************************************************************************** */
//copy constructor
template<typename Data>
Vector<Data>::Vector(const Vector<Data> & vector) {
    size = vector.size;
    elements = new Data[size];
    std::copy(vector.elements, vector.elements + size, elements);
}

//move constructor
template<typename Data>
Vector<Data>::Vector(Vector<Data>&& vector) noexcept{
    std::swap(size,vector.size);
    std::swap(elements, vector.elements);
}
/* ************************************************************************** */
//destructor
template<typename Data>
Vector<Data>::~Vector() {
    delete[] elements;
}
/* ************************************************************************** */

//copy assignment
template<typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vec) {
    if (this != &vec) {
        Vector<Data>* tmpvec = new Vector<Data>(vec);
        std::swap(*this, *tmpvec);
        delete tmpvec;
    }
    return *this;
}

//move assignment
template<typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data>&& vec) noexcept {
    std::swap(size, vec.size);
    std::swap(elements, vec.elements);
    return *this;
}

/* ************************************************************************** */

// Comparison operators

template<typename Data>
bool Vector<Data>::operator==(const Vector<Data> & vector) const noexcept {
    if (size == vector.size) {
        for(unsigned long index = 0; index < size; ++index) {
            if(elements[index] != vector.elements[index]) {
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
    return !(*this == vector);
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
const Data & Vector<Data>::operator[](const unsigned long index) const {
    if (index < size) {
        return elements[index];
    }else{
        throw std::out_of_range("Access at index " + std::to_string(index) + "; vector size " + std::to_string(size) + ".");
    }
}

template<typename Data>
const Data & Vector<Data>::Front() const{
    if (size > 0) {
        return elements[0];
    }else{
        throw std::length_error("Access to an empty vector.");
    }
}


template<typename Data>
const Data & Vector<Data>::Back() const{
    if (size > 0) {
        return elements[size - 1];
    }else{
        throw std::length_error("Access to an empty vector.");
    }
}

/* ************************************************************************** */

template<typename Data>
void Vector<Data>::Resize(unsigned long newSize) {
    if (newSize != size) {
        Data* newElements = new Data[newSize]{};
        unsigned long minSize = (newSize < size) ? newSize : size;
        for (unsigned long i = 0; i < minSize; ++i) {
            newElements[i] = std::move(elements[i]);
        }
        delete[] elements;
        elements = newElements;
        size = newSize;
    }
}

template<typename Data>
void Vector<Data>::Clear() {
    delete[] elements;
    elements = nullptr;
    size = 0;
}

/* ************************************************************************** */

template <typename Data>
SortableVector<Data> &
SortableVector<Data>::operator=(const SortableVector<Data>& vec) {
  Vector<Data>::operator=(vec);
  return *this;
}

template <typename Data>
SortableVector<Data> &
SortableVector<Data>::operator=(SortableVector<Data>&& vec) noexcept {
  Vector<Data>::operator=(std::move(vec));
  return *this;
}


}