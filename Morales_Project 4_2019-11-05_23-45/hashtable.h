//*** Structure definitions ***//
typedef struct _hashnode_t {
    char* key;
    char* value;
    struct _hashnode_t* next;
} HashNode;

typedef struct _hash_t {
	
    // Each bucket is a linked list accessed by a HashNode* pointer
    // The table itself has an array of buckets, which is equivalent to an array
    // of HashNode*; this is implemented using HashNode**.
    HashNode** buckets;
  
    // The number of buckets in the table
    int size;
} HashTable;

//*** Function prototypes ***//
unsigned long int hash(char*);
HashTable* hashtableInit(int);
void hashTableDestroy(HashTable*);
void hashtableInsert(HashTable*, char*, char*);
void hashtablePrint(HashTable*);
char* hashtableRemove(HashTable*, char*);
char* hashtableLookup(HashTable*, char*);

