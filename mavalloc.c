/*
  Patrick Arzoumanian
  Justine Tran
*/

#include "mavalloc.h"

//P: Making these two variables "global" allows ease of access
Node *head;
enum ALGORITHM algorithm_g;

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

  //P: Setting global algorithm
  algorithm_g = algorithm;

  return 0;
}

void mavalloc_destroy( )
{
  //P: freeing a DLL implementation
  Node *temp = head;
  Node *next_node = NULL;
  while(temp != NULL)
  {
    next_node = temp->next;
    free(temp);
    temp = next_node;
  }

  return;
}

//J: Allocates size bytes from preallocated memory arena
//J: [Hole/Process] [Start Number] [Length] [Prev] [Next]
void * mavalloc_alloc( size_t size )
{
  size_t requested_size = ALIGN4(size);

  Node *temp;

  if(algorithm_g == FIRST_FIT)
  {
    temp = head;
    while(temp != NULL)
    {
      //P: If request is smaller than the size of a hole...
      if(temp->size > requested_size && temp->type == HOLE)
      {
        Node *memory_left_over = insert_node_after(temp, temp->size - requested_size, HOLE);
        temp->size = requested_size;
        temp->type = PART;

        printf("new node addy = %p\n", memory_left_over);
        return memory_left_over;
      }
      //P: If requested size is the exact same size as the hole, make the HOLE a PART
      if(temp->size == requested_size)
      {
        temp->type = PART;
        return temp;
      }

      temp = temp->next;
    }
  }
  else if(algorithm_g == NEXT_FIT)
  {
    //P: return location of new node
  }
  else if(algorithm_g == BEST_FIT)
  {
    //P: return location of new node
  }
  else if(algorithm_g == WORST_FIT)
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

//P: When the user mavalloc_alloc(), the new node will be the new head of the list with type "PART"
void push_node(size_t size)
{
  //P: Create new node and set it's data
  Node *new_node = malloc(sizeof(Node));
  new_node->size = size;
  new_node->type = PART;

  //P: Place the new_node BEFORE the head by setting it's next to the head's position
  new_node->next = head;
  new_node->prev = NULL;

  //P: Update location of head to the NEW beginning of the DLL
  head->prev = new_node;
  head = new_node;
}

//P: We will be using this function when needed during any of the 4 algorithms
void *insert_node_after(Node *prev_node, size_t size, enum TYPE type)
{
  //P: Create new node and set it's data
  Node *new_node = malloc(sizeof(Node));
  new_node->size = size;
  new_node->type = type;

  //P: Setting up pointers for new node
  new_node->next = prev_node->next;
  prev_node->next = new_node;
  new_node->prev = prev_node;

  //P: Setting the node FOLLOWING the new_node's previous pointer to the new node to link them up
  if(new_node->next != NULL)
  {
    new_node->next->prev = new_node;
  }

  return new_node;
}

//P: Made the function for debugging purposes so that we can see what the arena looks like
void print_dll()
{
  Node *temp = head;
  printf("\n\n   DLL\n----------\n");
  while(temp != NULL)
  {
    //P: If node is of type "HOLE"
    if(temp->type == 0)
    {
      printf("[H | %ld] --> ", temp->size);
    }
    //P: If node is of type "PART"
    else
    {
      printf("[P | %ld] --> ", temp->size);
    }
    temp = temp->next;
  }
  printf("NULL\n\n");
}
