// 定义队列类;

#ifndef __BASE_QUEUE_H
#define __BASE_QUEUE_H

#include "base_namespace.h"
#include "base_typedef.h"
#include "base_guard.h"

BASE_NAMESPACE_BEGIN_DECL

template<class T, class LOCK, int32_t CAPACITY>
class BaseQueue_T
{
public:
    BaseQueue_T()
    {
        data_ = new T[CAPACITY];
        rindex_ = 0;
        windex_ = 0;
    };

    ~BaseQueue_T()
    {
        delete []data_;
    };

    bool put( const T& element )
    {
        lock_.acquire();

        //队列满;
        if( rindex_ == 0 && windex_ + 1 == CAPACITY )
        {
            lock_.release();
            return false;
        }

        //队列满;
        if( windex_ + 1 == rindex_ )
        {
            lock_.release();
            return false;
        }

        data_[windex_] = element;
        if( windex_ + 1 < CAPACITY )
        {
            windex_ ++;
        }
        else
        {
            windex_ = 0;
        }

        lock_.release();
        return true;
    };

    bool get( T& element )
    {
        lock_.acquire();

        if( rindex_ == windex_ )
        {
            lock_.release();
            return false;
        }

        element = data_[rindex_];
        if( rindex_ + 1 < CAPACITY )
        {
            rindex_ ++;
        }
        else
        {
            rindex_ = 0;
        }

        lock_.release();
        return true;
    };

    int32_t size()
    {
        return ( windex_ >= rindex_) ? (windex_ - rindex_) : (windex_ + CAPACITY - rindex_ );
    };

private:
    T*                  data_;
    volatile int32_t    rindex_;
    volatile int32_t    windex_;
    LOCK                lock_;
};

BASE_NAMESPACE_END_DECL

#endif