#ifndef __TDATALOOP_INC__
#define __TDATALOOP_INC__


  /**
   * \brief The default constructor
   *
   * \detail The default constructor creates an empty DataLoop, i.e. start is nullptr and count is 0.
   */
template <typename T> TDataLoop<T>::TDataLoop(){
    start = nullptr;
    count = 0;
}
  /**
  
   * \brief An alternate constructor
   *
   * \detail This alternate constructor creates a DataLoop with one node that contains the parameter value. The node is dynamically allocated and should be the start of the loop. Its next and prev fields should point to itself.
   *
   * \param[in] num The integer value to be added to the DataLoop
   */
template <typename T> TDataLoop<T>::TDataLoop(const T & num){
    _Node* n = new _Node{num, nullptr, nullptr};
    n->next = n;
    n->prev = n;
    start = n;
    count = 1;
}
  /**
   * \brief The copy constructor
   *
   * \detail The copy constructor creates a copy of the parameter DataLoop (rhs)
   *
   * \param[in] rhs A constant reference to the function input DataLoop object
   */ 

template <typename T> TDataLoop<T>::TDataLoop(const TDataLoop<T>& rhs){
    start = nullptr;
    count = 0;
    *this = rhs;
}

  /**
   * \brief Overloaded operator= to assign a DataLoop to another DataLoop
   *
   * \detail This overloaded operator assigns the input DataLoop (rhs) to the current DataLoop (*this, the current object).
   *
   * \note If the current DataLoop is not empty, this function releases formerly allocated memory as needed to avoid memory leaks. 
   *
   * \param[in] rhs A constant reference to the input DataLoop object
   *
   * \return A reference to the updated DataLoop object
   */
template <typename T> TDataLoop<T>& TDataLoop<T>::operator=(const TDataLoop<T> & rhs){
    if(this == &rhs){
        return *this;
    }
    /*clear previous*/
    if(start != nullptr){
        _Node* cur = start;
        start->prev->next = nullptr;
        if(cur->next == start){
            delete start;
        }
        else {
            while(cur != nullptr){
                _Node *temp = cur->next;
                delete cur;
                cur = temp;
            }
        }
        count = 0;
    }
    /*assign new*/
    if(rhs.start != nullptr){
        _Node* copy = rhs.start;
        _Node* newNode = new _Node{copy->data, nullptr, nullptr};
        newNode->next = newNode;
        newNode->prev = newNode;
        start = newNode;
        count++;
        copy = copy->next;

        while(copy != rhs.start){
            newNode = new _Node{copy->data, nullptr, nullptr};
            start->prev->next = newNode;
            newNode->prev = start->prev;
            start->prev = newNode;
            newNode->next = start;
            
            copy = copy->next;
        }
        start->prev = newNode;
        //link start to end and end to start
    }
    else{
        start = nullptr;
        count = 0;
        return *this;
    }
    count = rhs.count;
    return *this;
}

  /**
   * \brief The destructor
   *
   * \detail The destructor releases allocated memory as needed to avoid leaks.
   */
template <typename T> TDataLoop<T>::~TDataLoop(){
    if(start != nullptr){
    _Node* cur = start->next;
    while(cur != start){
        cur = cur->next;
        delete cur->prev;
    }
    delete start;
    }
}

  /**
   * \brief Overloaded operator+= to add a value to the end of this dataloop
   *
   * \detail This operator takes an integer, creates a new _Node to hold it, and inserts that at the end of this dataloop. In other words, the new node will be immediately before the start node, but the start is not changed. 
   *
   * \param[in] num A constant reference to an integer value
   *
   * \return A reference to this updated DataLoop object with the new value added
   */
template <typename T> TDataLoop<T>& TDataLoop<T>::operator+=(const T & num){
    _Node* add = new _Node{num, nullptr, nullptr};
    if(start == nullptr){
        start = add;
        start->next = start;
        start->prev = start;
    }
    else if(start->next == start){
        start->next = add;
        start->prev = add;
        add->next = start;
        add->prev = start;
    }
    else{
        add->next = start;
        add->prev = start->prev;
        start->prev->next = add;
        start->prev = add;
    }
    count++;
    return *this;
}

  /**
   * \brief Overloaded operator== to check if two DataLoops are the same
   *
   * \detail This operator compares the current DataLoop (*this) with the input DataLoop (rhs). It returns true if both DataLoops are the same node by node, including the starting position and count. Otherwise, it returns false.
   *
   * \param[in] rhs A constant reference to a DataLoop object to compare
   *
   * \return true if two DataLoops are the same node by node, else false
   */
template <typename T> bool TDataLoop<T>::operator==(const TDataLoop<T> & rhs) const{
    if(start == nullptr && rhs.start == nullptr){
        return true;
    }
    else if(start ==nullptr || rhs.start == nullptr){
        return false;
    }
    _Node* curL = start;
    _Node* curR = rhs.start;
    while(curL->next != start){
        if(curR->next == rhs.start){
            return false;
        }
        if(curL->data != curR->data){
            return false;
        }
        curL = curL->next;
        curR = curR->next;
    }
    return true;
  }

  /**
   * \brief Overloaded operator+ to concatenate copies of two DataLoops
   *
   * \detail This operator creates a third DataLoop by concatenating copies of the current DataLoop (*this) and the parameter DataLoop (rhs), adding the rhs copy to the end of the current DataLoop copy. The start position for the new DataLoop should mimic the start of *this and the count should be updated as well. [Note that the original DataLoops are not affected.]
   *
   * \param[in] rhs A constant reference to a DataLoop object to add to the end of *this
   *
   * \return A new DataLoop object with the concatenated result
   */
template <typename T> TDataLoop<T> TDataLoop<T>::operator+(const TDataLoop<T> & rhs) const{
    TDataLoop<T> sum(*this);
    if(rhs.start != nullptr){
        _Node* it = rhs.start;
        while(it->next != rhs.start){
            sum += it->data;
            it = it->next;
        }
        sum += it->data;
    }
    return sum;
}

  /**
   * \brief Overloaded output stream operator<< to print the DataLoop
   *
   * \detail This operator prints the input DataLoop (dl) to the ostream (os) in the format 
   * "-> data1 <--> data2 <--> ... <--> datax <-" where data1 is the value in the start node
   *   e.g. if we have a DataLoop with three elements 32, 12, 20 starting at 12
   *        it will print "-> 12 <--> 20 <--> 32 <-"
   *   If the DataLoop is empty, it prints ">no values<".
   *
   * \param[in] os A reference to the output stream object
   * \param[in] q A constant reference to the DataLoop object to be printed
   *
   * \return A reference to the output stream object
   */
template <typename U> std::ostream & operator<<(std::ostream & os, const TDataLoop<U> & dl){
    if(dl.start == nullptr){
        os << ">no values<";
        return os;
    }
   for(typename TDataLoop<U>::_Node* cur = dl.start; cur->next != dl.start; cur = cur->next){
        os << "-> " << cur->data << " <-";
   }
    os << "-> " << dl.start->prev->data << " <-";
    return os;
}

  /**
   * \brief Overloaded operator^ to shift the start position in *this TDataLoop according to the parameter offset - forward for a positive value and backward for a negative value
   *
   * \detail This overloaded operator takes an integer and shifts the starting position forward (positive num) or backward (negative num) that many nodes, looping around as much as necessary. [A 0 offset does not make any changes, and no changes are made to an empty TDataLoop or one with only one _Node.]
   *
   * \param[in] offset The number of nodes/positions to move the start position, positive for forward shifting, negative for backward motion
   *
   * \return A reference to the updated TDataLoop object
   */
template <typename T> TDataLoop<T> & TDataLoop<T>::operator^(int offset){
    if(offset > 0){
        for(int i = 0; i < offset; i++){
            start = start->next;
        }
    }
    else{
        for(int i = 0; i > offset; i--){
            start = start->prev;
        }
    }
    return *this;
}

  /**
   * \brief Function splice to insert an entire TDataLoop into this one
   *
   * \detail This function inserts the entire parameter TDataLoop (rhs) into the current TDataLoop (*this) at the indicated position (pos), where 0 would indicate the starting position of the current TDataLoop and update `start` accordingly. An insert position of n would indicate that the start node of rhs comes after node n in the current TDataLoop (assuming you start counting nodes with 1). The values from the input TDataLoop (rhs) should be inserted in their current order, beginning with that object's starting node. The count for the current TDataLoop should be updated. If the indicated position is larger than the current count, effectively loop around as much as necessary to get to the indicated spot. This function must also reset the parameter dataloop, making rhs an empty list, since both can't co-exist.
   *
   * \param[in] rhs A reference to a TDataLoop object to insert into *this
   *
   * \param[in] pos The insertion position 
   *
   * \return A reference to the updated TDataLoop object 
   */
template <typename T> TDataLoop<T> & TDataLoop<T>::splice(TDataLoop<T> & rhs, size_t pos){
    if(this->start == nullptr){
        if(rhs.start == nullptr){
            return *this;
        }
        return rhs;
    }

    *this ^ pos;
    *this = rhs + *this;
    *this ^ (-pos % count);
    if(this != &rhs){
        rhs = TDataLoop();
    }
    return *this;
}

// #include "TDataLoop.inc"
#endif // __TDATALOOP_INC__