/*
  Patrick Arzoumanian
  Justine Tran
*/

#include "mavalloc.h"

//P: Making these three variables "global" allows ease of access
Node *head;
Node *temp = NULL;
Node *previous = NULL;
void *arena;
enum ALGORITHM algorithm_g;

//J: [size] - large memory pool allocation on application startup
//J: [ALGORITHM] - First Fit, Best Fit, Worst Fit, Next Fit
int mavalloc_init( size_t size, enum ALGORITHM algorithm )
{
  //P: ALLOCATING ARENA
  size_t requested_size = ALIGN4(size);
  arena = malloc(requested_size);
  head = (Node *) malloc(sizeof(Node)); 

  //P: If the allocation fails or the size is less than 0 the function returns -1
  if((head == NULL) || (requested_size < 0))
  {
    return -1;
  }

  //P: Setting head characteristics
  head->arena = arena;
  head->type = HOLE;
  head->size = requested_size;
  head->next = NULL;
  head->prev = NULL;

  //P: Setting global algorithm
  algorithm_g = algorithm;
  previous = head;

  return 0;
}

void mavalloc_destroy( )
{
  //P: Freeing a DLL implementation
  Node *temp = head;
  Node *next_node = NULL;
  while(temp != NULL)
  {
    next_node = temp->next;
    free(temp);
    temp = next_node;
  }
  head = NULL;
  
  return;
}

//J: Allocates size bytes from preallocated memory arena
//J: [Hole/Process] [Start Number] [Length] [Prev] [Next]
void * mavalloc_alloc( size_t size )
{
  size_t requested_size = ALIGN4(size);

  if(head == NULL)
  {
    // printf("\nNo arena allocated. mavalloc_alloc() cannot be called\n");
    return NULL;
  }

  if(algorithm_g == FIRST_FIT)
  {
    temp = head;
    while(temp)
    {
      //P: If request is smaller than the size of a hole...
      if(temp->size > requested_size && temp->type == HOLE)
      {
        //P: Make a HOLE after temp with a size of the remaining memory
        Node *memory_left_over = insert_node_after(temp, temp->size - requested_size, HOLE);

        //P: Make the original HOLE a PART with the size requested
        temp->size = requested_size;
        temp->type = PART;

        previous = memory_left_over;
        return (void *) temp->arena;
      }
      //P: If requested size is the exact same size as the hole, make the HOLE a PART
      if(temp->size == requested_size)
      {
        temp->type = PART;

        previous = temp;
        return (void *) temp->arena;
      }
      temp = temp->next;
    }
  }
  else if(algorithm_g == NEXT_FIT)
  {
    //J: Start from head if there is no next pointer left off
    if(previous == NULL)
      previous = head;

    //J: Assuming there was a left of part
    temp = previous;
    while(temp != NULL)
    {
      //J: Similar to FIRST_FIT Excepts starts at PART left off
      if(temp->size > requested_size && temp->type == HOLE)
      {
        Node *memory_left_over = insert_node_after(temp,temp->size - requested_size,HOLE);
        temp->size = requested_size;
        temp->type = PART;

        previous = temp;
        return (void *) temp->arena;
      }

      //J: If pointer allocator is the same size as the HOLE
      if(temp->size == requested_size && temp->type == HOLE)
      {
        temp->type = PART;

        previous = temp;
        return (void *) temp->arena;
      }

      temp = temp->next;
      //J: Gone through whole array
      if(temp == previous)
        break;
      //J: We have reached the head, starting from the beginning
      if(temp == NULL)
        temp = head;
    }
  }
  else if(algorithm_g == BEST_FIT)
  {
    Node *smallest_hole;
    size_t smallest_size = INT_MAX;
    
    temp = head;
    while(temp != NULL)
    {
      //P: If temp has a bigger size than the largest_hole we've seen so far, update largest_hole 
      if(temp->type == HOLE && temp->size <= smallest_size)
      {
        smallest_size = temp->size;
        smallest_hole = temp;
      }
      temp = temp->next;
    }

    //P: Set temp's address to the largest_hole's address
    temp = smallest_hole;

    if(requested_size > smallest_size)
    {
      // printf("\nCouldn't find a spot to fit the request in... Request cannot be met.\n");
      return NULL;
    }

    //P: If the requested size is the same exact size as the largest size, there's no need to make a new node, make the HOLE a PART
    if(requested_size == smallest_size)
    {
      temp->type = PART;
      previous = temp;
      return (void *) temp->arena;
    }

    //P: Make a HOLE after temp with a size of the remaining memory
    Node *memory_left_over = insert_node_after(temp, temp->size - requested_size, HOLE);

    //P: Make the original HOLE a PART with the size requested
    temp->size = requested_size;
    temp->type = PART;

    previous = temp;
    return (void *) temp->arena;
  }
  else if(algorithm_g == WORST_FIT)
  {
    //P: Make another temp variable to hold the locatation of the biggest hole and the biggest size
    Node *largest_hole;
    size_t largest_size = 0;
    
    temp = head;
    while(temp != NULL)
    {
      //P: If temp has a bigger size than the largest_hole we've seen so far, update largest_hole 
      if(temp->type == HOLE && temp->size >= largest_size)
      {
        largest_size = temp->size;
        largest_hole = temp;
      }
      temp = temp->next;
    }

    //P: Set temp's address to the largest_hole's address
    temp = largest_hole;

    if(requested_size > largest_size)
    {
      // printf("\nCouldn't find a spot to fit the request in... Request cannot be met.\n");
      return NULL;
    }

    //P: If the requested size is the same exact size as the largest size, there's no need to make a new node, make the HOLE a PART
    if(requested_size == largest_size)
    {
      temp->type = PART;
      previous = temp;
      return (void *) temp->arena;
    }

    //P: Make a HOLE after temp with a size of the remaining memory
    Node *memory_left_over = insert_node_after(temp, temp->size - requested_size, HOLE);

    //P: Make the original HOLE a PART with the size requested
    temp->size = requested_size;
    temp->type = PART;

    previous = temp;
    return (void *) temp->arena;
  }
  else
  {
    // printf("The code should not print this... Something went wrong with the algorithm enum.\n");
  }

  //P: COULDN'T FIND SPOT, NO SPACE
  // printf("\nCouldn't find a spot to fit the request in... Request cannot be met.\n");
  return NULL;
}

//J: Frees the memory block pointed by pointer back to preallocated memory arena
//J: Two consecutive blocks free then combine (coalesce) them
void mavalloc_free( void * ptr )
{
  Node * node = head;
  //P: Loop through DLL until pointers match
  while( node )
  {
    if( node -> arena == ptr )
    {
      if( node -> type == HOLE )
      {
        printf("Warning: Double free detected\n");
      }

      //P: Change node to hole
      node -> type = HOLE;
      break;
    }
    node = node -> next;
  }

  //P: Reset node back to head
  node = head;

  //P: "Coalesce" node's surrounding desired hole
  while( node )
  {
    if( node -> next && node -> type == HOLE && node -> next -> type == HOLE  )
    {
      Node * previous = node -> next;
      node -> size = node -> size + node -> next -> size;
      node -> next = node -> next -> next;
      free( previous );
      continue;
    }
    node = node -> next;
  }

  return;
}

//J: Function returns the number of nodes in the memory area
int mavalloc_size( )
{
  int number_of_nodes = 0;
  Node *temp = head;
  while(temp)
  {
    number_of_nodes++;
    temp = temp->next;
  }

  return number_of_nodes;
}

//P: We will be using this function when needed during any of the 4 algorithms
void *insert_node_after(Node *prev_node, size_t size, enum TYPE type)
{
  //P: Create new node and set it's data
  Node *new_node = (Node *)malloc(sizeof(Node));
  //J: Placing leftover arena into new_node
  new_node->arena = prev_node->arena+size;
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
