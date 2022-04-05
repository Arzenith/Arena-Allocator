#include "mavalloc.h"
#include "tinytest.h"
#include <stdio.h>
#include <string.h>

int test_case_1()
{
  char * ptr = ( char * ) mavalloc_alloc ( 65535 );
  mavalloc_free( ptr );

  return 1;
}

int test_case_2()
{
  mavalloc_init( 128000, BEST_FIT );

  char * ptr1    = (char*)mavalloc_alloc( 65535 );
  char * ptr2    = (char*)mavalloc_alloc( 65 );

  // If you failed here your allocation on line 37 failed
  TINYTEST_ASSERT( ptr1 ); 

  // If you failed here your allocation on line 38 failed
  TINYTEST_ASSERT( ptr2 ); 

  mavalloc_free( ptr1 );
  mavalloc_free( ptr2 );

  int size = mavalloc_size();

  // If you failed here your linked list did not have a single node
  // check your mavalloc_alloc or mavalloc_size and make sure you
  // are combining adjacent free nodes and counting your link list
  // correctly

  TINYTEST_EQUAL( size, 1 ); 

  mavalloc_destroy( );
  return 1;
}

int test_case_3()
{
  // intentionally fail this test for now
  
  TINYTEST_EQUAL(1, 0);

  return 1;
}

int test_case_4()
{
  mavalloc_init( 65535, FIRST_FIT );

  char * ptr1  = ( char * ) mavalloc_alloc ( 10000 );
  char * ptr2  = ( char * ) mavalloc_alloc ( 65 );

  int size = mavalloc_size();

  // If you failed here your allocation on line 110 failed
  TINYTEST_ASSERT( ptr1 ); 

  // If you failed here your allocation on line 111 failed
  TINYTEST_ASSERT( ptr2 ); 

  // If you failed here your linked list did not have three nodes
  // check your mavalloc_alloc or mavalloc_size and make sure you
  // are allocating and splitting nodes and counting your link list
  // correctly

  TINYTEST_EQUAL( size, 3); 
  mavalloc_destroy( );
  return 1;
}

int test_case_5()
{
  mavalloc_init( 4144, NEXT_FIT );

  char * ptr1 = ( char * ) mavalloc_alloc ( 1024 );
  char * buf1 = ( char * ) mavalloc_alloc ( 4 );
  char * ptr6 = ( char * ) mavalloc_alloc ( 16 );
  char * buf2 = ( char * ) mavalloc_alloc ( 4 );
  char * ptr2 = ( char * ) mavalloc_alloc ( 2048 );
  char * buf3 = ( char * ) mavalloc_alloc ( 4 );
  char * ptr7 = ( char * ) mavalloc_alloc ( 16 );
  char * buf4 = ( char * ) mavalloc_alloc ( 4 );
  char * ptr3 = ( char * ) mavalloc_alloc ( 1024 );

  // If you failed here your allocation on line 141 failed
  TINYTEST_ASSERT( ptr1 ); 
  
  // If you failed here your allocation on line 145 failed
  TINYTEST_ASSERT( ptr2 ); 
  
  // If you failed here your allocation on line 149 failed
  TINYTEST_ASSERT( ptr3 ); 
  
  // If you failed here your allocation on line 143 failed
  TINYTEST_ASSERT( ptr6 ); 
  
  // If you failed here your allocation on line 147 failed
  TINYTEST_ASSERT( ptr7 ); 

  mavalloc_free( ptr1 ); 
  mavalloc_free( ptr2 ); 
  mavalloc_free( ptr3 ); 

  char * ptr5 = ( char * ) mavalloc_alloc ( 2000 );

  // If you failed here your allocation on line 170 failed
  TINYTEST_ASSERT( ptr5 ); 

  ptr5 = ptr5;
  ptr7 = ptr7;
  ptr6 = ptr6;
  buf1 = buf1;
  buf2 = buf2;
  buf3 = buf3;
  buf4 = buf4;

  char * ptr4 = ( char * ) mavalloc_alloc ( 1000 );

  // If you failed here your allocation on line 183 failed
  TINYTEST_ASSERT( ptr4 ); 

  // If you failed here your allocation on line 149 failed
  TINYTEST_ASSERT( ptr3 ); 

  // If you failed here your Next Fit algorithm is not choosing
  // the correct hole 
  TINYTEST_EQUAL( ptr3, ptr4 ); 
  mavalloc_destroy( );
  return 1;
}

int tinytest_setup(const char *pName)
{
    fprintf( stderr, "tinytest_setup(%s)\n", pName);
    return 0;
}

int tinytest_teardown(const char *pName)
{
    fprintf( stderr, "tinytest_teardown(%s)\n", pName);
    return 0;
}


TINYTEST_START_SUITE(MavAllocTestSuite);
  TINYTEST_ADD_TEST(test_case_1,tinytest_setup,tinytest_teardown);
  //TINYTEST_ADD_TEST(test_case_2,tinytest_setup,tinytest_teardown);
  TINYTEST_ADD_TEST(test_case_3,tinytest_setup,tinytest_teardown);
  TINYTEST_ADD_TEST(test_case_4,tinytest_setup,tinytest_teardown);
  //TINYTEST_ADD_TEST(test_case_5,tinytest_setup,tinytest_teardown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(MavAllocTestSuite);
