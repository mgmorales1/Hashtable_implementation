#include <hashtable.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

  // read in command line argument with testcase number
  int test;
   if(argc > 1) {
    test = atoi(argv[1]);
  } else {
    printf("Run this program as:\n\thash_table_test number\nwhere number is the number of the testcase to run");
    return 0;
  }


  /*** Series of testcases which can be run individually.
      The value of test is set as a command line argument.
      See the comments inside each portion of the if-else
      statement for a description about what value runs which
      test.   

      Testcases 1 and 11 need to be run through valgrind (see
      assignment handout).

      If you wish to add testcases, do so after the existing testcases.

      ***/

  if(test == 0) {
    // Create an empty HashTable
    HashTable *h = hashtableInit(10);
    hashtablePrint(h);
    return 0;
  }  else if (test == 1) {
    //Create an empty HashTable and then destory it
    //Need to use valgrind to make sure this testcase passes
    HashTable *h = hashtableInit(10);
    hashTableDestroy(h);
    return 0;
  } else if(test == 2) {
    //Insert single k-v pair into HT
    HashTable *h = hashtableInit(10);
    hashtableInsert(h, "apple", "value1");
    hashtablePrint(h);
    return 0;
  }  else if (test == 3) {
    //Insert and then lookup
    HashTable *h = hashtableInit(10);
    hashtableInsert(h, "apple", "value1");
    char *value = hashtableLookup(h, "apple");
    printf("%s", value);
    return 0;
  } else if (test == 4) {
    //Insert and then remove
    HashTable *h = hashtableInit(10);
    hashtableInsert(h, "apple", "value1");
    char *value = hashtableRemove(h, "apple");
    printf("%s\n", value);
    hashtablePrint(h);
    return 0;
  } else if (test == 5) {
    //Insert multiple items
    HashTable *h = hashtableInit(10);

    int i;
    for (i = 0; i < 50; i++) {
      char *newKey = malloc(2 * sizeof(char));
      newKey[0] = 'A' + i;
      newKey[1] = '\0';

      hashtableInsert(h, newKey, "");
    }

    hashtablePrint(h);

    return 0;
  }  else if (test == 6) {
    //Insert and then lookup multiple items
    HashTable *h = hashtableInit(10);

    int i;
    for (i = 0; i < 50; i++) {
      char *newKey = malloc(2 * sizeof(char));
      newKey[0] = 'A' + i;
      newKey[1] = '\0';

      // Value is the same as the key
      hashtableInsert(h, newKey, newKey);
    }

    for (i = 0; i < 50; i++) {
      char *lookupKey = malloc(2 * sizeof(char));
      lookupKey[0] = 'A' + i;
      lookupKey[1] = '\0';

      printf("%s\n", hashtableLookup(h, lookupKey));
    }

    return 0;
  } else if (test == 7) {
    //Insert and Remove Multiple items
    HashTable *h = hashtableInit(10);

    int i;
    for (i = 0; i < 50; i++) {
      char *newKey = malloc(2 * sizeof(char));
      newKey[0] = 'A' + i;
      newKey[1] = '\0';

      // Value is the same as the key
      hashtableInsert(h, newKey, newKey);
    }

    for (i = 0; i < 50; i++) {
      char *lookupKey = malloc(2 * sizeof(char));
      lookupKey[0] = 'A' + i;
      lookupKey[1] = '\0';

      printf("%s\n", hashtableRemove(h, lookupKey));
    }

        hashtablePrint(h);
        return 0;  
  } else if (test == 8) {
    //Try to lookup something which doesn't exist
    HashTable *h = hashtableInit(10);
    char *value = hashtableLookup(h, "apple");
    if (value == NULL) {
      printf("NULL");
    } else {
      printf("Not NULL");
    }
    return 0;
  } else if (test == 9) {
    //Try to remove something that doesn't exist
    HashTable *h = hashtableInit(10);
    char *value = hashtableRemove(h, "apple");
    if (value == NULL) {
      printf("NULL");
    } else {
      printf("Not NULL");
    }
    return 0;
  } else if (test == 10) {
    //Insert multiple items then remove first
    HashTable *h = hashtableInit(10);

    //insert 3 things which has to same bucket
    char key1[] = "n";
    char key2[] = "d";
    char key3[] = "Z";

    hashtableInsert(h, key1, key1);
    hashtableInsert(h, key2, key2);
    hashtableInsert(h, key3, key3);

    //remove first key in chain
    printf("%s\n", hashtableRemove(h, key3));

    //others should remain in bucket0
    hashtablePrint(h);
    return 0;
  } else if (test == 11) {
    //Insert and remove 1,000,000 k-v pairs and check memory management
    //Need run this test via valgrind to make sure this testcase passes
    HashTable *h = hashtableInit(10);
    int i;
    for (i = 0; i < 1000000; i++) {
      hashtableInsert(h, "", "");
      hashtableRemove(h, "");
    }

    printf("Survived");
    hashTableDestroy(h);
    return 0;
  } else {
    //your tests can go here
  } 
}