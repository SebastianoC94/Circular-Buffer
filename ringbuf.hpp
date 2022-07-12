#pragma once

#include <cstddef>
#include <cstdint>

typedef enum 
{
  ringbuf_Error_Ok,
  ringbuf_Error_Full,
  ringbuf_Error_Empty,
  ringbuf_Error_InvalidArgument,
} ringbuf_Error_t;

struct ringbuf_t 
{
	uint8_t* pHead;
	uint8_t* pTail;
	size_t capacity = 0;

	ringbuf_t() : pHead(nullptr), pTail(nullptr) {}
};

/// Initialize a new ringbuf instance from a buffer of known size
/// \param ringbuf a pointer to an uninitialized ringbuf_t instance
/// \param buf a pointer to a valid array
/// \param capacity the capacity of the ringbuf, which is also the size of buf
/// \return ringbuf_Error_Ok if can be correctly initialized, an error code
/// otherwise
ringbuf_Error_t ringbuf_new(ringbuf_t* ringbuf, uint8_t* buf, size_t capacity);

/// Get the capacity of the ringbuf (how many elements can be stored in total)
/// \param ringbuf a pointer to an initialized ringbuf_t instance
/// \return the capacity
size_t ringbuf_get_capacity(ringbuf_t* ringbuf);

/// Get the size of the ringbuf (how many elements have been stored)
/// \param ringbuf a pointer to an initialized ringbuf_t instance
/// \return the number of elements currently in the ringbuf
size_t ringbuf_get_size(ringbuf_t* ringbuf);

/// Get the size of available space
/// \param ringbuf a pointer to an initialized ringbuf_t instance
/// \return the number of elements which can be added until it is full
size_t ringbuf_get_available(ringbuf_t* ringbuf);

/// Add an element to the ringbuf
/// \param ringbuf a pointer to an initialized ringbuf_t instance
/// \param value the value of the element to add to the ringbuf
/// \return ringbuf_Error_Ok if can be added, ringbuf_Error_Full if the ringbufF
/// is full
ringbuf_Error_t ringbuf_push(ringbuf_t* ringbuf, uint8_t value);

/// Get the oldest element added to the ringbuf while removing it
/// \param ringbuf a pointer to an initialized ringbuf_t instance
/// \param value the value of the element to add to the ringbuf
/// \return ringbuf_Error_Ok if can be added, ringbuf_Error_Empty if the ringbufF
/// is empty
ringbuf_Error_t ringbuf_pop(ringbuf_t* ringbuf, uint8_t* value);

/// Check if the ringbuf is full
/// \param ringbuf a pointer to an initialized ringbuf_t instance
/// \return true if full, false otherwise
bool ringbuf_is_full(ringbuf_t* ringbuf);

/// Check if the ringbuf is empty
/// \param ringbuf a pointer to an initialized ringbuf_t instance
/// \return true if empty, false otherwise
bool ringbuf_is_empty(ringbuf_t* ringbuf);
