namespace lasd {

    /* ************************************************************************** */
    
    // Auxiliary protected functions
    template <typename Data>
    ulong SetVec<Data>::BinarySearch(const Data& data) const {
      if (size == 0 || Vector<Data>::elements == nullptr) {
      return size;
      }
    
      ulong left = 0;
      ulong right = size - 1;
    
      while (left <= right) {
      ulong mid = left + (right - left) / 2;
    
      if (Vector<Data>::elements[mid] == data) {
        return mid;
      }
    
      if (Vector<Data>::elements[mid] < data) {
        left = mid + 1;
      } else {
        if (mid == 0) {
        break;
        }
        right = mid - 1;
      }
      }
    
      return size;
    }
    
    template <typename Data>
    ulong SetVec<Data>::BinarySearchInsertion(const Data& data) const {
      if (size == 0 || Vector<Data>::elements == nullptr) {
        return 0;
      }
    
      ulong left = 0;
      ulong right = size - 1;
    
      while (left <= right) {
        ulong mid = left + (right - left) / 2;
    
        if (Vector<Data>::elements[mid] == data) {
          return mid;
        }
    
        if (Vector<Data>::elements[mid] < data) {
          left = mid + 1;
        } else {
          if (mid == 0) {
            break;
          }
          right = mid - 1;
        }
      }
    
      return left;
    }
    
    // ShiftRight
    template <typename Data>
    void SetVec<Data>::ShiftRight(ulong index) {
        if (size == capacity || Vector<Data>::elements == nullptr) {
            capacity = (capacity == 0) ? 1 : capacity * 2;
            
            Data* newElements = new Data[capacity]{};
            
            for (ulong i = 0; i < index; i++) {
                newElements[i] = Vector<Data>::elements[i];
            }
            
            for (ulong i = size; i > index; i--) {
                newElements[i] = Vector<Data>::elements[i-1];
            }
            
            delete[] Vector<Data>::elements;
            Vector<Data>::elements = newElements;
        } else {
            for (ulong i = size; i > index; i--) {
                Vector<Data>::elements[i] = Vector<Data>::elements[i-1];
            }
        }
        
        size++;
    }
    
    // ShiftLeft
    template <typename Data>
    void SetVec<Data>::ShiftLeft(ulong index) {
        if (size == 0) return;
        
        for (ulong i = index; i < size - 1; i++) {
            Vector<Data>::elements[i] = Vector<Data>::elements[i+1];
        }
        
        size--;
        
        if (size > 0 && size <= capacity / 4 && capacity > 1) {
            capacity = capacity / 2;
            Data* newElements = new Data[capacity]{};
            
            for (ulong i = 0; i < size; i++) {
                newElements[i] = Vector<Data>::elements[i];
            }
            
            delete[] Vector<Data>::elements;
            Vector<Data>::elements = newElements;
        }
    }
    
    // Specific constructors
    
    template <typename Data>
    SetVec<Data>::SetVec(const TraversableContainer<Data>& container) 
        : Vector<Data>(), capacity(0) {
        std::vector<Data> tempElements;
    
        container.Traverse([&tempElements](const Data& data) {
            tempElements.push_back(data);
        });
    
        for (const auto& data : tempElements) {
            Insert(data);
        }
    }
    
    template <typename Data>
    SetVec<Data>::SetVec(MappableContainer<Data>&& container)
        : Vector<Data>(), capacity(0) {
        std::vector<Data> tempElements;
    
        container.Map([&tempElements](Data& data) {
            tempElements.push_back(std::move(data));
        });
    
        for (auto& data : tempElements) {
            Insert(std::move(data));
        }
    }
    
    template <typename Data>
    SetVec<Data>::SetVec(const SetVec<Data>& other)
        : Vector<Data>(other), capacity(other.capacity) {
    }
    
    template <typename Data>
    SetVec<Data>::SetVec(SetVec<Data>&& other) noexcept
        : Vector<Data>(std::move(other)), capacity(other.capacity) {
        other.capacity = 0;
    }
    
    // Copy assignment
    template <typename Data>
    SetVec<Data>& SetVec<Data>::operator=(const SetVec<Data>& other) {
        if (this != &other) {
            Vector<Data>::operator=(other);
            capacity = other.capacity;
        }
        return *this;
    }
    
    // Move assignment
    template <typename Data>
    SetVec<Data>& SetVec<Data>::operator=(SetVec<Data>&& other) noexcept {
        if (this != &other) {
            Vector<Data>::operator=(std::move(other));
            capacity = other.capacity;
            other.capacity = 0;
        }
        return *this;
    }
    
    // Comparison operators
    template <typename Data>
    bool SetVec<Data>::operator==(const SetVec<Data>& other) const noexcept {
      return Vector<Data>::operator==(other);
    }
    
    template <typename Data>
    inline bool SetVec<Data>::operator!=(const SetVec<Data>& other) const noexcept {
      return !(*this == other);
    }
    
    // Specific member functions (inherited from OrderedDictionaryContainer)
    
    template <typename Data>
    const Data& SetVec<Data>::Min() const {
      if (size == 0 || Vector<Data>::elements == nullptr) {
        throw std::length_error("Empty set");
      }
    
      return Vector<Data>::elements[0];
    }
    
    template <typename Data>
    Data SetVec<Data>::MinNRemove() {
      if (size == 0 || Vector<Data>::elements == nullptr) {
        throw std::length_error("Empty set");
      }
    
      Data min = Vector<Data>::elements[0];
      ShiftLeft(0);
    
      return min;
    }
    
    template <typename Data>
    void SetVec<Data>::RemoveMin() {
      if (size == 0 || Vector<Data>::elements == nullptr) {
        throw std::length_error("Empty set");
      }
    
      ShiftLeft(0);
    }
    
    template <typename Data>
    const Data& SetVec<Data>::Max() const {
      if (size == 0 || Vector<Data>::elements == nullptr) {
        throw std::length_error("Empty set");
      }
    
      return Vector<Data>::elements[size - 1];
    }
    
    template <typename Data>
    Data SetVec<Data>::MaxNRemove() {
      if (size == 0 || Vector<Data>::elements == nullptr) {
        throw std::length_error("Empty set");
      }
    
      Data max = Vector<Data>::elements[size - 1];
      ShiftLeft(size - 1);
    
      return max;
    }
    
    template <typename Data>
    void SetVec<Data>::RemoveMax() {
      if (size == 0 || Vector<Data>::elements == nullptr) {
        throw std::length_error("Empty set");
      }
    
      ShiftLeft(size - 1);
    }
    
    template <typename Data>
    const Data& SetVec<Data>::Predecessor(const Data& data) const {
      if (size == 0 || Vector<Data>::elements == nullptr) {
        throw std::length_error("Empty set");
      }
    
      ulong index = BinarySearchInsertion(data);
    
      if (index == 0) {
        throw std::length_error("Predecessor not found");
      }
    
      return Vector<Data>::elements[index - 1];
    }
    
    template <typename Data>
    Data SetVec<Data>::PredecessorNRemove(const Data& data) {
      if (size == 0 || Vector<Data>::elements == nullptr) {
        throw std::length_error("Empty set");
      }
    
      ulong index = BinarySearchInsertion(data);
    
      if (index == 0) {
        throw std::length_error("Predecessor not found");
      }
    
      Data pred = Vector<Data>::elements[index - 1];
      ShiftLeft(index - 1);
    
      return pred;
    }
    
    template <typename Data>
    void SetVec<Data>::RemovePredecessor(const Data& data) {
      if (size == 0 || Vector<Data>::elements == nullptr) {
        throw std::length_error("Empty set");
      }
    
      ulong index = BinarySearchInsertion(data);
    
      if (index == 0) {
        throw std::length_error("Predecessor not found");
      }
    
      ShiftLeft(index - 1);
    }
    
    template <typename Data>
    const Data& SetVec<Data>::Successor(const Data& data) const {
      if (size == 0 || Vector<Data>::elements == nullptr) {
        throw std::length_error("Empty set");
      }
    
      ulong index = BinarySearchInsertion(data);
    
      if (index >= size || Vector<Data>::elements[index] == data) {
        if (index + 1 >= size) {
          throw std::length_error("Successor not found");
        }
        index++;
      }
    
      return Vector<Data>::elements[index];
    }
    
    template <typename Data>
    Data SetVec<Data>::SuccessorNRemove(const Data& data) {
      if (size == 0 || Vector<Data>::elements == nullptr) {
        throw std::length_error("Empty set");
      }
    
      ulong index = BinarySearchInsertion(data);
    
      if (index >= size || Vector<Data>::elements[index] == data) {
        if (index + 1 >= size) {
          throw std::length_error("Successor not found");
        }
        index++;
      }
    
      Data succ = Vector<Data>::elements[index];
      ShiftLeft(index);
    
      return succ;
    }
    
    template <typename Data>
    void SetVec<Data>::RemoveSuccessor(const Data& data) {
      if (size == 0 || Vector<Data>::elements == nullptr) {
        throw std::length_error("Empty set");
      }
    
      ulong index = BinarySearchInsertion(data);
    
      if (index >= size || Vector<Data>::elements[index] == data) {
        if (index + 1 >= size) {
          throw std::length_error("Successor not found");
        }
        index++;
      }
    
      ShiftLeft(index);
    }
    
    // Specific member functions (inherited from DictionaryContainer)
    
    // Insert
    template <typename Data>
    bool SetVec<Data>::Insert(const Data& data) {
        if (size > 0 && Vector<Data>::elements != nullptr) {
            ulong index = BinarySearchInsertion(data);
            
            if (index < size && Vector<Data>::elements[index] == data) {
                return false;
            }
            
            ShiftRight(index);
            Vector<Data>::elements[index] = data;
        } else {
            capacity = 1;
            Vector<Data>::elements = new Data[capacity]{};
            Vector<Data>::elements[0] = data;
            size = 1;
        }
        
        return true;
    }
    
    template <typename Data>
    bool SetVec<Data>::Insert(Data&& data) {
      if (size > 0 && Vector<Data>::elements != nullptr) {
        ulong index = BinarySearchInsertion(data);
    
        if (index < size && Vector<Data>::elements[index] == data) {
          return false;
        }
    
        ShiftRight(index);
        Vector<Data>::elements[index] = std::move(data);
      } else {
        Vector<Data>::elements = new Data[1];
        Vector<Data>::elements[0] = std::move(data);
        size = 1;
      }
    
      return true;
    }
    
    template <typename Data>
    bool SetVec<Data>::Remove(const Data& data) {
      if (size == 0 || Vector<Data>::elements == nullptr) {
        return false;
      }
    
      ulong index = BinarySearch(data);
    
      if (index >= size) {
        return false;
      }
      
      ShiftLeft(index);
      return true;
    }
    
    /* ************************************************************************** */
    
    }