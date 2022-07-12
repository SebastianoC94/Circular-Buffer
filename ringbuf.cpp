#include <memory.h>		//memcpy
#include "ringbuf.hpp"

ringbuf_Error_t ringbuf_new(ringbuf_t* ringbuf, uint8_t* buf, size_t capacity) 
{
	ringbuf_Error_t res = ringbuf_Error_InvalidArgument;

	if (ringbuf && buf && capacity > 0)
	{
		ringbuf->pHead = buf;
		ringbuf->pTail = buf;

		ringbuf->capacity = capacity;

		res = ringbuf_Error_Ok;
	}
	else
	{
		; // Invalid arguments!
	}

	return res;
}

size_t ringbuf_get_capacity(ringbuf_t* ringbuf) 
{
	size_t res = 0;

	if (ringbuf)
	{
		res = ringbuf->capacity;
	}
	else
	{
		; // Invalid arguments!
	}

	return res;
}

size_t ringbuf_get_size(ringbuf_t* ringbuf) 
{
	size_t res = 0;

	if (ringbuf)
	{
		res = ringbuf->pTail - ringbuf->pHead;
	}
	else
	{
		; // Invalid arguments!
	}

	return res;
}

size_t ringbuf_get_available(ringbuf_t* ringbuf) 
{
	size_t res = 0;

	if (ringbuf)
	{
		res = ringbuf->capacity - (ringbuf->pTail - ringbuf->pHead);
	}
	else
	{
		; // Invalid arguments!
	}

	return res;
}

ringbuf_Error_t ringbuf_push(ringbuf_t* ringbuf, uint8_t value) 
{
	ringbuf_Error_t res = ringbuf_Error_InvalidArgument;

	if (ringbuf)
	{
		if ((ringbuf->pTail - ringbuf->pHead) < static_cast<unsigned>(ringbuf->capacity))
		{
			*ringbuf->pTail = value;
			ringbuf->pTail++;
			res = ringbuf_Error_Ok;
		}
		else
		{
			res = ringbuf_Error_Full;
		}
	}
	else
	{
		; // Invalid argument
	}

	return res;
}

ringbuf_Error_t ringbuf_pop(ringbuf_t* ringbuf, uint8_t* value) 
{
	ringbuf_Error_t res = ringbuf_Error_InvalidArgument;

	if (ringbuf && value)
	{
		if ((ringbuf->pTail - ringbuf->pHead) > 0)
		{
			*value = *ringbuf->pHead;
			ringbuf->pTail--;
			memcpy(ringbuf->pHead, ringbuf->pHead + 1, ringbuf->pTail - ringbuf->pHead);	
			res = ringbuf_Error_Ok;
		}
		else
		{
			res = ringbuf_Error_Empty;
		}
	}
	else
	{
		; // Invalid argument
	}

	return res;
}

bool ringbuf_is_full(ringbuf_t* ringbuf) 
{
	bool res = true;

	if (ringbuf)
	{
		res = (ringbuf->pTail - ringbuf->pHead) == ringbuf->capacity;
	}
	else
	{
		; // Invalid arguments!
	}

	return res;
}

bool ringbuf_is_empty(ringbuf_t* ringbuf) 
{
	bool res = true;

	if (ringbuf)
	{
		res = (ringbuf->pTail - ringbuf->pHead) == 0;
	}
	else
	{
		; // Invalid arguments!
	}

	return res;
}