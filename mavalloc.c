/*
  Patrick Arzoumanian
  Justine Tran
*/

#include "mavalloc.h"

Node *head;


int mavalloc_init( size_t size, enum ALGORITHM algorithm )
{
  head = malloc(size * sizeof(Node)); 

  //If the allocation fails or the size is less than 0 the function returns -1
  if((head == NULL) || (size < 0))
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

void * mavalloc_alloc( size_t size )
{
  // only return NULL on failure
  return NULL;
}

void mavalloc_free( void * ptr )
{
  return;
}

int mavalloc_size( )
{
  int number_of_nodes = 0;

  return number_of_nodes;
}
