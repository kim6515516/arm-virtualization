/*!
 * \file    PL011-Uart-FIFO.h
 * \brief   FIFO circular buffers.
 * \date    Copyright 2004-2008 ARM Limited. All rights reserved.
 *
 */

#ifndef PL011_UART_FIFO_H
#define PL011_UART_FIFO_H

#include <assert.h>
#include <stdio.h>

#include <vector>

template <typename Tp>
class FIFO
{
 public:
    typedef Tp                value_type;
    typedef value_type*       pointer;
    typedef const value_type* const_pointer;
    typedef value_type&       reference;
    typedef const value_type& const_reference;
    typedef size_t            size_type;

 protected:
    std::vector<value_type> data;    //!< Buffered data and flags.
    size_type max_size;              //!< Size of circular buffer.
    size_type capacity;         //!< FIFO capacity.
    size_type len;             //!< Number of items in FIFO.
    size_type head;             //!< Index of next value to be read from FIFO.
    size_type tail;             //!< Index of next free slot in FIFO.

 public:
    /*! Construct a FIFO with a maximum capacity of \a size. */
    FIFO(size_type capacity_ = 16) :
        data(capacity_),
        max_size(capacity_),
        capacity(capacity_),
        len(0),
        head(0),
        tail(0)
    {
    }

    /*! Push an element into the FIFO.
     *  \pre !isfull().
     */
    void push_back(const_reference c)
    {
        assert(!full());

        assert(tail < max_size);
        data[tail] = c;
        ++tail;
        if (tail == max_size) {
            tail = 0;
        }
        ++len;
    }

    /*! Return a const_reference to head element from FIFO, without
     *  popping from the FIFO.
     *
     *  \pre !isempty()
     */
    const_reference front() const
    {
        assert(!empty());

        assert(head < max_size);
        return data[head];
    }

    /*! Return a const_reference to an element in the FIFO.
     *  \pre id < level()
     */
    const_reference operator [] (size_type index) const
    {
        assert(index < len);
        return data[(head + index) % max_size];
    }

    /*! Pop the head element from the FIFO.
     *  \pre !isempty()
     */
    void pop_front() {
        assert(!empty());
        assert(head < max_size);
        ++head;
        if (head == max_size) {
            head = 0;
        }
        --len;
    }

    /*! Change the capacity of the FIFO. 
     *  If the current level is greater than the new capacity, no data will 
     *  be truncated: the FIFO will remain 'full' until the level drops
     *  below the capacity.
     *  \pre new_size <= max_size
     */
    void set_capacity(size_type capacity_) {
        assert(capacity_ <= max_size);
        capacity = capacity_;
    }

    /*! Get the number of items currently in the FIFO. */
    size_type size() {
        return len;
    }

    /*! Return true if the FIFO is currently full (size >= capacity). */
    bool full() const {
        return (len >= capacity);
    }

    /*! Return true if the FIFO is empty. */
    bool empty() const {
        return (len == 0);
    }

    /*! Remove all data from the FIFO. */
    void clear() {
        head = 0;
        tail = 0;
        len = 0;
    }
};

#endif // PL011_UART_FIFO_H
