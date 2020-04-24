
struct dateType {
  int day;
  int month;
  int year;
};

struct patient {
  char recordId[20];
  char patientFirstName[20];
  char patientLastName[20];
  char diseaseId[20];
  char country[20];
  struct dateType entryDate;
  struct dateType exitDate;
  };


struct listNode {
    struct patient record;
    struct listNode* next;
};

struct bucket_entry{
  char* key;
  struct Node* pointer;
};

struct bucket {
  struct bucket_entry* data;
  struct bucket* next;
};


struct Node
{
    struct listNode* pointer;
    struct dateType key;
    struct Node *left;
    struct Node *right;
    int height;
};
struct arrayNode{
  int key1;
  char key2[20];
};


struct heapNode{
    struct arrayNode* value;
    struct heapNode * left;
    struct heapNode * right;
};



int height(struct Node *N);
int max(int a, int b);
struct Node* newNode( struct dateType key,struct listNode* listPointer);
struct Node *rightRotate(struct Node *y);
struct Node *leftRotate(struct Node *x);
int getBalance(struct Node *N);
struct Node* insert(struct Node* node, struct dateType key,struct listNode* listPointer);
void preOrder(struct Node *root);
int hash(char *s,int hash_size);
void printList(struct listNode* myList);
struct listNode* insertRecordsFromFileToLinkedList();
int compareDates(struct dateType date1,struct dateType date2);
void checkFile(struct listNode* myList);
void insertDataToHashtable(struct bucket** hashTable,int hashSize, struct listNode* myList, char dataType[20]);
struct bucket* initializeNewBucket();
void initializeHashTable(struct bucket** hashTable,int hashSize);
void printHashTable(struct bucket** hashTable,int hashSize);
int countTreeNodes(struct Node*root,int* sum);
void countTreeNodesBetweenDates(struct Node*root,int* sum,struct dateType date1,struct dateType date2);
void countTreeNodesBetweenDatesforCountry(struct Node*root,int* sum,struct dateType date1,struct dateType date2,char* country);
void globalDiseaseStats(struct dateType date1,struct dateType date2,struct bucket** hashTable,int hashSize);
void diseaseFrequency(struct dateType date1,struct dateType date2,struct bucket** hashTable,int hashSize,char* virusName,char* country);
int isNullDate(struct dateType date);
void printRecordsInHospital(struct Node* root);
void patientsInHospital(struct Node*root,int* sum);
void numCurrentPatients(struct bucket** hashTable,int hashSize,char* disease);
void recordPatientExit(struct listNode* list,char* recordId,struct dateType date);
void insertPatientRecord(struct listNode* list,struct bucket** diseaseHashTable,struct bucket** countryHashTable,int h1,int h2,char* recordId,char* firstName,char* lastName,char* diseaseId,char* country, struct dateType entryDate, struct dateType exitDate);
int wordsInString(char *str);
void setDate(struct dateType* date,int day,int month,int year);
void setDateFromString(struct dateType* date,char*str);
void reheapify(struct heapNode * N);
void printLevel(struct heapNode * root, int level);
void heapify(struct heapNode * heap);
struct heapNode *newEmptyTree(void);
struct heapNode *heap_from_array(struct arrayNode* arr, int index, int elements);
void printPre(struct heapNode * root);
int heightOfTree(struct heapNode * root);
void fixTabeleFromTree(struct Node*root,struct arrayNode* my_array,int array_size,struct dateType date1,struct dateType date2 );
void fixTabeleFromTree2(struct Node*root,struct arrayNode* my_array,int array_size,struct dateType date1,struct dateType date2 );
int numOfDiseases(struct bucket** diseaseHashTable,int h1);
void topkDiseases(struct bucket** diseaseHashTable, struct bucket** countryHashTable,int h1,int h2,char* country,struct dateType date1,struct dateType date2,int k);
void topkCountries(struct bucket** diseaseHashTable, struct bucket** countryHashTable,int h1,int h2,char* disease,struct dateType date1,struct dateType date2,int k);
void myExit(struct bucket** diseaseHashTable, struct bucket** countryHashTable,int h1,int h2);
void deleteTree(struct Node* node);
