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

  //Write algorithmn here: Based on user
  //First Fit, Best Fit, Worst Fit, Next Fit
  //After we allocate the memory and place it in its location

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
  Node *ptr, *temp;
  //Finding end of linked list
  temp = head;
  while(temp->next != NULL)
  {
    temp = temp->next;
  }

  size_t requested_size = ALIGN4(size);

  // FIRST FIT ALGO
  if(head->algorithm == 0)
  {

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

  //Taking memory from preallocated memory arena
  if(head->size <= 0 || (head->size - requested_size) < 0)
  {
    //J: There is no more preallocated memory arena or enough
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
