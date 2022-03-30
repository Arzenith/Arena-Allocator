/*
  Patrick Arzoumanian
  Justine Tran
*/

#include "mavalloc.h"

Node *head;

//J: [size] - large memory pool allocation on application startup
//J: [ALGORITHM] - First Fit, Best Fit, Worst Fit, Next Fit
int mavalloc_init( size_t size, enum ALGORITHM algorithm )
{
 
  //P: ALLOCATING ARENA
  size_t requested_size = ALIGN4( size );
  head = (Node *) malloc(requested_size * sizeof(Node)); 

  head->type = HOLE;
  head->size = requested_size;
  head->prev = NULL;
  head->next = NULL;
  head->algorithm = algorithm;

  //P: If the allocation fails or the size is less than 0 the function returns -1
  if((head == NULL) || (requested_size < 0))
  {
    return -1;
  }

  return 0;
}

void mavalloc_destroy( )
{
  free(head);
  return;
}

//J: Allocates size bytes from preallocated memory arena
//J: [Hole/Process] [Start Number] [Length] [Prev] [Next]
void * mavalloc_alloc( size_t size )
{
  Node *ptr;
  size_t requested_size = ALIGN4(size);

  //Searches the arena for a free block using the heap allocation algo.
  //Specified when the arean was allocated.
  //Heap allocation alo. Finds where to allocate memory in linked list
  Node *temp;
  
  // FIRST FIT ALGO
  if(head->algorithm == 0)
  {
    //Finding end of linked list
    temp = head;
    while(temp->next != NULL)
    {
      temp = temp->next;
    }
  }
  // NEXT FIT ALGO
  else if(head->algorithm == 1)
  {

  }
  // BEST FIT ALGO
  else if(head->algorithm == 2)
  {

  }
  // WORST FIT ALGO
  else
  {
    
  }

  //There is no available block of memory the function returns NULL
  if(head->size <= 0 || (head->size - requested_size) < 0)
  {
    //There is no more preallocated memory arena or enough
    return NULL;
  }
  else
  {
    ptr->size = head->size - requested_size;
    temp->next = ptr;
    ptr->prev = temp;
    ptr->next = NULL;
    ptr->type = PART;
  }

  return ptr;
}

//Frees the memory block pointed by the pointer.
void mavalloc_free( void * ptr )
{
  
  return;
}

//J: Function returns the number of nodes in the memory area
int mavalloc_size( )
{
  int number_of_nodes = 0;

  return number_of_nodes;
}
