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

  //P: If the allocation fails or the size is less than 0 the function returns -1
  if((head == NULL) || (requested_size < 0))
  {
    return -1;
  }

  //P: Setting head characteristics
  head->type = HOLE;
  head->size = requested_size;
  head->next = NULL;
  head->prev = NULL;
  head->algorithm = algorithm;

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
  size_t requested_size = ALIGN4(size);

  Node *new_node, *temp;

  if(head->algorithm == FIRST_FIT)
  {
    temp = head;
    while(temp->next != NULL)
    {
      if(temp->size >= requested_size)
      {
        //J: Temporary Implementation
        // ptr->size = head->size - requested_size;
        // temp->next = ptr;
        // ptr->prev = temp;
        // ptr->next = NULL;
        // ptr->type = PART;

       //P: return location of new node
      }
      temp = temp->next;
    }
  }
  else if(head->algorithm == NEXT_FIT)
  {
    //P: return location of new node
  }
  else if(head->algorithm == BEST_FIT)
  {
    //P: return location of new node
  }
  else if(head->algorithm == WORST_FIT)
  {
    //P: return location of new node
  }
  else
  {
    printf("The code should not print this... Something went wrong with the algorithm enum.\n");
  }

  //P: COULDN'T FIND SPOT, NO SPACE
  printf("Couldn't find a spot to fit the request in... Request cannot be met.\n");
  return NULL;
}

//J: Frees the memory block pointed by the pointer.
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
