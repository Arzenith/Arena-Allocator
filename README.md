## Project Overview

In this project, we study concepts of memory management by constructring a custom allocator which allows the user to allocate chunks of memory within a preexisting arena initialized by the user. To better understand how the Operating System decides which free block to allocate, we implement four of the most common allocation algoritms: First fit, Next fit, Best fit, and Worst fit. To do this, we use linked lists and enumerated types to keep track of holes in memory.

## To run
Clone the repo type `make` into your terminal. Then, type `./unit_test`.

You will see the 20 unit tests all pass. To see these unit tests, open `main.c`.

## Things to try

Due to the nature of this program, not a lot can be seen to understand what's happening. So, we developed a function to help visualize the placement of these algorithms by printing out to console. For example, this is what prints to console when you run test case 7.

### Test case 7 code in main.c
```c
mavalloc_init( 75000, BEST_FIT );

char * ptr1    = ( char * ) mavalloc_alloc ( 65535 );
char * buffer1 = ( char * ) mavalloc_alloc( 1 );
char * ptr4    = ( char * ) mavalloc_alloc ( 65 );
char * buffer2 = ( char * ) mavalloc_alloc( 1 );
char * ptr2    = ( char * ) mavalloc_alloc ( 1500 );

mavalloc_free( ptr1 ); 
mavalloc_free( ptr2 ); 

char * ptr3 = ( char * ) mavalloc_alloc ( 1000 );

mavalloc_destroy( );
```

### Test case 7 output
```
tinytest_setup(test_case_7)

   DLL
----------
[P | 65536] --> [H | 9464] --> NULL


   DLL
----------
[P | 65536] --> [P | 4] --> [H | 9460] --> NULL


   DLL
----------
[P | 65536] --> [P | 4] --> [P | 68] --> [H | 9392] --> NULL


   DLL
----------
[P | 65536] --> [P | 4] --> [P | 68] --> [P | 4] --> [H | 9388] --> NULL


   DLL
----------
[P | 65536] --> [P | 4] --> [P | 68] --> [P | 4] --> [P | 1500] --> [H | 7888] --> NULL


   DLL
----------
[H | 65536] --> [P | 4] --> [P | 68] --> [P | 4] --> [P | 1000] --> [H | 8388] --> NULL

tinytest_teardown(test_case_7)

```

To try this with any placement algorithm, type `print_dll()` before any return statement in each of the placement algorithm's functions.
For this past example, the code looked like this:

```c
void *best_fit(size_t requested_size)
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
    
    print_dll();
    return NULL;
  }

  //P: If the requested size is the same exact size as the largest size, there's no need to make a new node, make the HOLE a PART
  if(requested_size == smallest_size)
  {
    temp->type = PART;
    previous = temp;
    
    print_dll();
    return (void *) temp->arena;
  }

  //P: Make a HOLE after temp with a size of the remaining memory
  Node *memory_left_over = insert_node_after(temp, temp->size - requested_size, HOLE);

  //P: Make the original HOLE a PART with the size requested
  temp->size = requested_size;
  temp->type = PART;

  previous = temp;
  
  print_dll();
  return (void *) temp->arena;
}
```
