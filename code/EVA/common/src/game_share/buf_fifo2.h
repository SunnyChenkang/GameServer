#ifndef NL_BUF_FIFO_DOUBLE_H
#define NL_BUF_FIFO_DOUBLE_H

#include <nel/misc/types_nl.h>
#include <queue>

namespace NLMISC {

template<class T>
class CBufFIFO2
{
public:
	CBufFIFO2 ():m_ReadCount(0),m_WriteCount(0),m_ReadQueue(&m_DataQueqe1),m_WriteQueue(&m_DataQueqe2){}
	~CBufFIFO2 (){}

	bool push_back (T* data)
	{
		m_WriteMutex.enter();

        m_WriteQueue->push(data);
        m_WriteCount = m_WriteQueue->size();

		m_WriteMutex.leave();
		return true;
	}

	T* pop_front()
	{
		T* pRet = private_pop_front();

        if ( pRet==NULL )
        {
            swap();
            pRet = private_pop_front();
        }
		return pRet;
	}


	uint32 size()
	{
		return m_ReadCount+m_WriteCount;
	}


    T* private_pop_front()
    {
        T* pRet = NULL;

        if ( m_ReadCount > 0 )
        {
            m_ReadMutex.enter();
            pRet = m_ReadQueue->front();
            m_ReadQueue->pop();
            m_ReadCount = m_ReadQueue->size();
            m_ReadMutex.leave();
        }

        return pRet;
    }

    //   ½»»»
    void swap()
    {
        m_ReadMutex.enter();
        m_WriteMutex.enter();

        TBuf2Queue* pTmp = m_ReadQueue;
        m_ReadQueue  = m_WriteQueue;
        m_WriteQueue = pTmp;

        m_ReadCount  = m_ReadQueue->size();
        m_WriteCount = m_WriteQueue->size();

        m_WriteMutex.leave();
        m_ReadMutex.leave();
    }

private:

    volatile  uint32    m_ReadCount;
    volatile  uint32    m_WriteCount;

    CMutex          m_WriteMutex;
    CMutex          m_ReadMutex;

    typedef std::queue<T*>  TBuf2Queue;

    TBuf2Queue*     m_ReadQueue;
    TBuf2Queue*     m_WriteQueue;

    TBuf2Queue      m_DataQueqe1;
    TBuf2Queue      m_DataQueqe2;
};


} // NLMISC

#endif // NL_BUF_FIFO_DOUBLE_H

/* End of buf_fifo2.h */
