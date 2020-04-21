// HashTable Implementation Starter Code
// CMS 230, 2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Hashtable struct definitions and function prototypes
#include "hashtable.h"


//*** Hash a string to an integer ***//
// Input
//    char *s: the string to hash
// Returns
//    The integer hash code
//
// Implements the basic hashing String hashing algorithm used by Java.
unsigned long int hash(char *s) {
    unsigned long int h = 0;

    int i;
    for (i = 0; i < strlen(s); i++) {
        h += h * 31 + (unsigned long int) s[i];
    }

    return h;
}


//*** Create a new hashtable_t ***//
// Input
//    tableSize: the number of buckets in the new table
// Returns
//    A pointer to the new table
HashTable * hashtableInit(int tableSize) {

    // Allocate memory for a new HashTable
    HashTable* hash_table = malloc(sizeof(HashTable) * 1);
    // Allocate memory for an array of buckets and assign
    // them to the table's buckets field
    hash_table->buckets = malloc(sizeof(HashNode*) * tableSize);
    
    // Set the new HashTable's size field
    hash_table->size = tableSize;
    // Initialize all buscktes to NULL
    int i;
    for (i = 0; i < tableSize; i++) {
        hash_table->buckets[i] = NULL;
    }
    // Return the new HashTable
    return hash_table;
}

//*** Destroy (de-allocate a hashtable) ***//
// Input:
//     hashtable *ht: the hashtable to delete
// Returns:
//     Nothing
void hashTableDestroy(HashTable *ht) {
    int i; 
    // Free memory for nodes if needed
    for (i = 0; i < ht->size; i++) {
        if (ht->buckets[i] != NULL) {
            ht->buckets[i] = NULL;
            free(ht->buckets[i]);
        } else {
            continue;
        }
    }
    // Free memory for array of buckets
    free(ht->buckets);
    // Free memory for hashtable
    free(ht);
}


//*** Insert a key-value pair into a table ***//
// Inputs
//    hashtable *h: the hashtable performing the insertion
//    char *key: the key string
//    char *value: the value string
// Returns
//    Nothing
void hashtableInsert(HashTable *h, char *key, char *value) {
    // Create new node with given key and value
    HashNode* node = malloc(sizeof(HashNode));
    node->key = key;
    node->value = value;
    // Calculate the index to go to in HashTable
    unsigned long int hashCode = hash(key);
    int index = hashCode % h->size;
    // Check if the bucket has nodes and insert at the front
    if(h->buckets[index] != NULL) {
        node->next = h->buckets[index];
        h->buckets[index] = node;
    } else { // make the node the first in the list
        node->next = NULL;
        h->buckets[index] = node;
    }
}


//*** Lookup the value associated with a particular key ***//
// Inputs
//    hashtable_t *h: the table
//    char *key: the key to find
// Returns
//    The char *value associated with the key or NULL if no match exists
char * hashtableLookup(HashTable *h, char *key) {
    // Create temporary pointer
    HashNode* temp;
    // Calculate the index to go to in HashTable
    unsigned long int hashCode = hash(key);
    int index = hashCode % h->size;
    // Find out if the bucket has data
    if (h->buckets[index] != NULL) {
        // Point temp to the first node in bucket
        temp = h->buckets[index];
        // Iterate thorugh the linked list to find desired key
        while (temp != NULL) {
            if(strcmp(key, temp->key) == 0) {
                break;
            }
            temp = temp->next;
        }
        // Return key's value
        return temp->value;
    } else {
        return NULL;
    }

}


//*** Remove a key-value pair from the table if it exists ***//
// Inputs
//    hashtable_t *h: the table
//    char *key: the key to find and remove
// Returns
//    The char *value associated with the key or NULL if no match exists
//    The pair is removed if it exists in the table
char * hashtableRemove(HashTable *h, char *key) {
    // Create temporary and previous pointer
    HashNode* temp;
    HashNode* prev;
    // Calculate the index to go to in HashTable
    unsigned long int hashCode = hash(key);
    int index = hashCode % h->size;
    
    temp = h->buckets[index];
    if(h->buckets[index] == NULL) {
        //Bucket is NULL
        return NULL;
    } else if (strcmp(temp->key, key) == 0) { // match in the first node
        h->buckets[index] = temp->next;
        char* v = temp->value;
        free(temp);
        return v;
    } else {
        temp = temp->next;
        prev = h->buckets[index];
        if (temp == NULL ) {
            // only one node and it didn't match
           return NULL;
        } else { // Iterate through nodes to find match
            while (temp != NULL) {
               if (strcmp(temp->key, key) == 0) {
                   prev->next = temp->next;
                   char* v = temp->value;
                   free(temp);
                   return v;
               }       
               temp = temp->next;
               prev = prev-> next;
            }
        // No match was found
        return NULL;
    }
   }
}

//*** Print a hashtable ***//
// Input
//    hashtable_t *h: the table
// Output
//    the hashtable, printed by buckets
void hashtablePrint(HashTable *h) {
    int i;
    for (i = 0; i < h->size; i++) {
        HashNode *node = h->buckets[i];
        printf("Contents of bucket %d:\n", i);

        while (node != NULL) {
            printf("    <%s, %s>\n", node->key, node->value);
            node = node->next;
        }
    }
}

//*** There is no main function --- use main.c *** //
