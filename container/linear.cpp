namespace lasd {

    /* ************************************************************************** */
    
    template <typename Data>
    bool LinearContainer<Data>::operator==(const LinearContainer<Data> & con) const noexcept {
        if (size == con.size) {
            for (ulong index = 0; index < size; ++index) {
                if (operator[](index) != con.operator[](index)) {
                    return false;
                }
            }
            return true;
        } else {
            return false;
        }
    }
    
    template <typename Data>
    inline bool LinearContainer<Data>::operator!=(const LinearContainer<Data> & con) const noexcept {
        return !(*this == con);
    }
    
    /* ************************************************************************** */
    
    // Specific member functions (LinearContainer)
    
    template <typename Data>
    inline const Data & LinearContainer<Data>::Front() const {
        return operator[](0);
    }
    
    template <typename Data>
    inline const Data & LinearContainer<Data>::Back() const {
        return operator[](size - 1);
    }
    
    /* ************************************************************************** */
    
    // Specific member functions (LinearContainer) (inherited from TraversableContainer)
    
    template <typename Data>
    inline void LinearContainer<Data>::Traverse(TraverseFun fun) const {
        PreOrderTraverse(fun);
    }
    
    /* ************************************************************************** */
    
    // Specific member functions (LinearContainer) (inherited from PreOrderTraversableContainer)
    
    template <typename Data>
    inline void LinearContainer<Data>::PreOrderTraverse(TraverseFun fun) const {
        for (ulong index = 0; index < size; ++index) {
            fun(operator[](index));
        }
    }
    
    /* ************************************************************************** */
    
    // Specific member functions (LinearContainer) (inherited from PostOrderTraversableContainer)
    
    template <typename Data>
    inline void LinearContainer<Data>::PostOrderTraverse(TraverseFun fun) const {
        ulong index = size;
        while (index > 0) {
            fun(operator[](--index));
        }
    }
    
    /* ************************************************************************** */
    
    // Specific member functions (MutableLinearContainer) (inherited from MappableContainer)
    
    template <typename Data>
    inline void MutableLinearContainer<Data>::Map(MapFun fun) {
        PreOrderMap(fun);
    }
    
    /* ************************************************************************** */
    
    // Specific member functions (MutableLinearContainer) (inherited from PreOrderMappableContainer)
    
    template <typename Data>
    inline void MutableLinearContainer<Data>::PreOrderMap(MapFun fun) {
        for (unsigned long index = 0; index < size; ++index) {
            fun(operator[](index));
        }
    }
    
    /* ************************************************************************** */
    
    // Specific member functions (MutableLinearContainer) (inherited from PostOrderMappableContainer)
    
    template <typename Data>
    inline void MutableLinearContainer<Data>::PostOrderMap(MapFun fun) {
        unsigned long index = size;
        while (index > 0) {
            fun(operator[](--index));
        }
    }
    
    /* ************************************************************************** */
    
    }