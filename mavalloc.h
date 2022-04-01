// The MIT License (MIT)
// 
// Copyright (c) 2022 Trevor Bakker 
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define ALIGN4(s)  (((((s) - 1) >> 2) << 2) + 4)

enum ALGORITHM
{
  FIRST_FIT = 0,
  NEXT_FIT,
  BEST_FIT,
  WORST_FIT
}; 

//J: Used for each entry in the linked list
//J: Hole (H) Part (P) - Process allocation
enum TYPE
{
  HOLE = 0,
  PART
};

//J: [Start Address] [Length] [Pointer to next Item] [Pointer to Prev.]
typedef struct node Node;
struct node 
{
  void * arena;
  enum TYPE type;
  size_t size;
  Node* next;
  Node* prev;
};

/**
 * @brief Initialize the allocation arena and set the algorithm type
 *
 * This function takes the provided size and calls malloc to allocate a 
 * memory arena. The size must be aligned to a word boundary.
 * 
 * If the allocation succeeds it returns 0. If the allocation fails or the 
 * size is less than 0 the function returns -1
 *
 * \param size The size of the pool to allocate in bytes
 * \param algorithm The heap algorithm to implement
 * \return 0 on success. -1 on failure
 **/
int mavalloc_init( size_t size, enum ALGORITHM algorithm );


/**
 * @brief Destroy the arena 
 *
 * This function releases the arena
 *
 * \return None 
 **/
void mavalloc_destroy( );


/**
 * @brief Allocate memory from the arena 
 *
 * This function allocated memory from the arena.  The parameter size 
 * specifies the number of bytes to allocates.  This _must_ be 4 byte aligned using the 
 * ALIGN4 macro. 
 * 
 * The function searches the arena for a free block using the heap allocation algorithm 
 * specified when the arena was allocated.
 *
 * If there is no available block of memory the function returns NULL
 *
 * \return A pointer to the available memory or NULL if no free block is found 
 **/
void * mavalloc_alloc( size_t size );


/*
 * \brief free the pointer
 *
 * frees the memory block pointed to by pointer. if the block is adjacent
 * to another block then coalesce (combine) them
 *
 * \param ptr the heap memory to free
 *
 * \return none
 */
void mavalloc_free(void *ptr);

/*
 * \brief Allocator size
 *
 * Return the number of nodes in the allocators linked list 
 *
 * \return The size of the allocator linked list 
 */
int mavalloc_size( );

void push_node(size_t size);
void *insert_node_after(Node *prev_node, size_t size, enum TYPE type);
void print_dll();