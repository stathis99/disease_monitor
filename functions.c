#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#define bs 10

int height(struct Node *N){
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b){
    return (a > b)? a : b;
}

struct Node* newNode( struct dateType key,struct listNode* listPointer){
    struct Node* node = (struct Node*)
                        malloc(sizeof(struct Node));
    node->pointer = listPointer;
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}

struct Node *rightRotate(struct Node *y){
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    // Return new root
    return x;
}

struct Node *leftRotate(struct Node *x){
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    // Return new root
    return y;
}

int getBalance(struct Node *N){
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct Node* insert(struct Node* node, struct dateType key,struct listNode* listPointer){
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(key,listPointer));

    if (compareDates(key,node->key)==1){
        node->left  = insert(node->left, key, listPointer);
    }else{
      node->right = insert(node->right, key, listPointer);
    }



    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                           height(node->right));

    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && compareDates(key,node->left->key)==1)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && compareDates(key,node->right->key)==0)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && compareDates(key,node->left->key) == 0)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && compareDates(key,node->right->key)==1)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

void preOrder(struct Node *root){
    if(root != NULL)
    {
        printf(" %d-%d-%d ", root->key.day,root->key.month,root->key.year);
        preOrder(root->left);
        preOrder(root->right);
    }
}

int hash(char *s,int hash_size){
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31*hashval;
    return hashval % hash_size;
}

void printList(struct listNode* myList){
  while(myList->next!=NULL){
    printf("id = %s\nname = %s\nsurname = %s\ndiseaseId = %s\ncountry = %s\nentryDate = %d-%d-%d\nexitDate = %d-%d-%d\n\n",
    myList->record.recordId,myList->record.patientFirstName,myList->record.patientLastName,myList->record.diseaseId,
    myList->record.country,myList->record.entryDate.day,myList->record.entryDate.month,myList->record.entryDate.year,
    myList->record.exitDate.day,myList->record.exitDate.month,myList->record.exitDate.year);
    myList = myList->next;
  };
  printf("id = %s\nname = %s\nsurname = %s\ndiseaseId = %s\ncountry = %s\nentryDate = %d-%d-%d\nexitDate = %d-%d-%d\n\n",
  myList->record.recordId,myList->record.patientFirstName,myList->record.patientLastName,myList->record.diseaseId,
  myList->record.country,myList->record.entryDate.day,myList->record.entryDate.month,myList->record.entryDate.year,
  myList->record.exitDate.day,myList->record.exitDate.month,myList->record.exitDate.year);
  myList = myList->next;

};

struct listNode* insertRecordsFromFileToLinkedList(){



   char str[999];
   FILE * file;
   file = fopen( "small.txt" , "r");

   struct listNode* head = NULL;
   struct listNode* listPointer = NULL;
   struct listNode* tempListNode = NULL;


   if (file) {

        while (fscanf(file, "%s", str)!=EOF){
            tempListNode = (struct listNode*)malloc(sizeof(struct listNode));
            if(head == NULL){
              head = tempListNode;
              listPointer = tempListNode;
            }else{
              listPointer->next = tempListNode;
              listPointer = tempListNode;
            }

            strcpy(listPointer->record.recordId,str);
            fscanf(file, "%s", str);
            strcpy(listPointer->record.patientFirstName,str);
            fscanf(file, "%s", str);
            strcpy(listPointer->record.patientLastName,str);
            fscanf(file, "%s", str);
            strcpy(listPointer->record.diseaseId,str);
            fscanf(file, "%s", str);
            strcpy(listPointer->record.country,str);
            fscanf(file, "%s", str);

                    char tmp_buf[20];//tmp buffer so i can keep the whole date in the other on
                    strncpy(tmp_buf, str, 20);
                    //Get day
                    const char s[2] = "-";
                    char *token;
                    token = strtok(tmp_buf, s);//breaks string str into a series of tokens using the delimiter delim.
                  //  rec->entryDate.Day = atoi(token);
                  listPointer->record.entryDate.day = atoi(token);
                    //Get month
                    char*tmp;
                    strncpy(tmp_buf, str, 20);//take the whole date again
                    tmp = tmp_buf;
                    while(tmp[0]!=s[0])//skip the Day
                    {
                      tmp++;
                    }
                    tmp++;
                    token = strtok(tmp, s);
                    listPointer->record.entryDate.month = atoi(token);
                    //rec->entryDate.Month = atoi(token);
                    //printf("Entry Month is %d\n",rec->entryDate.Month);
                    //Get year
                    strncpy(tmp_buf, str, 20);//take the whole date again
                    tmp = tmp_buf;
                    int flag=0;
                    while(tmp[0]!=s[0])//skip the Day
                    {
                      tmp++;
                    }
                    tmp++;
                    while(tmp[0]!=s[0])//skip the Month
                    {
                      tmp++;
                    }
                    tmp++;
                    token = strtok(tmp, s);
                    listPointer->record.entryDate.year = atoi(token);
                    //rec->entryDate.Year = atoi(token);
                    //printf("Entry Year is %d\n",rec->entryDate.Year);




            fscanf(file, "%s", str);

            strncpy(tmp_buf, str, 20);
            //Get day

            token = strtok(tmp_buf, s);
          //  rec->entryDate.Day = atoi(token);
          if(token != NULL){
            listPointer->record.exitDate.day = atoi(token);
          }

            //Get month

            strncpy(tmp_buf, str, 20);//take the whole date again
            tmp = tmp_buf;
            while(tmp[0]!=s[0])//skip the Day
            {
              tmp++;
            }
            tmp++;
            token = strtok(tmp, s);
            if(token!=NULL){
              listPointer->record.exitDate.month = atoi(token);
            }

            //Get year
            strncpy(tmp_buf, str, 20);//take the whole date again
            tmp = tmp_buf;
            flag=0;
            while(tmp[0]!=s[0])//skip the Day
            {
              tmp++;
            }
            tmp++;
            while(tmp[0]!=s[0])//skip the Month
            {
              tmp++;
            }
            tmp++;
            token = strtok(tmp, s);
            if(token!=NULL){
                listPointer->record.exitDate.year = atoi(token);
            }
            listPointer->next = NULL;


       }


   }
  return head;

  fclose(file);
}

int compareDates(struct dateType date1,struct dateType date2){
  if(date1.year < date2.year || (date1.year == date2.year && date1.month < date2.month) || (date1.year == date2.year && date1.month == date2.month && date1.day < date2.day)){
    return 1;
  }
  return 0;}

void checkFile(struct listNode* myList){
  struct listNode *temp;
  temp = myList;
  while(myList->next != NULL){
    if(myList->record.exitDate.year != 0 && compareDates(myList->record.exitDate,myList->record.entryDate) == 1){
      printf(" %s \n",myList->record.recordId);
      printf("the file has wrong dates\n");
    }
    while(temp->next != NULL){
      temp = temp->next;
      if(myList->record.recordId == temp->record.recordId ){
        printf("the file has duplicate id");
      }
    }
    myList = myList->next;
  }}

void insertDataToHashtable(struct bucket** hashTable,int hashSize, struct listNode* myList, char dataType[20]){
int key;
if(!strcmp(dataType,"diseaseId")){
      while(myList->next!= NULL){
        key = hash(myList->record.diseaseId,hashSize);

        for(int i=0;i<bs;i++){
          if(hashTable[key]->data[i].key == NULL){
            hashTable[key]->data[i].key = myList->record.diseaseId;
            hashTable[key]->data[i].pointer = insert(hashTable[key]->data[i].pointer, myList->record.entryDate, myList);
            break;
          }
          if(!strcmp(hashTable[key]->data[i].key,myList->record.diseaseId)){
            hashTable[key]->data[i].pointer = insert(hashTable[key]->data[i].pointer, myList->record.entryDate, myList);
            break;
          }

        }

        myList = myList->next;

      }
      key = hash(myList->record.diseaseId,hashSize);

      for(int i=0;i<bs;i++){
        if(hashTable[key]->data[i].key == NULL){
          hashTable[key]->data[i].key = myList->record.diseaseId;
          hashTable[key]->data[i].pointer = insert(hashTable[key]->data[i].pointer, myList->record.entryDate, myList);
          break;
        }
        if(!strcmp(hashTable[key]->data[i].key,myList->record.diseaseId)){
          hashTable[key]->data[i].pointer = insert(hashTable[key]->data[i].pointer, myList->record.entryDate, myList);
          break;
        }

      }
    }
    if(!strcmp(dataType,"country")){
          while(myList->next!= NULL){
            key = hash(myList->record.country,hashSize);

            for(int i=0;i<bs;i++){
              if(hashTable[key]->data[i].key == NULL){
                hashTable[key]->data[i].key = myList->record.country;
                hashTable[key]->data[i].pointer = insert(hashTable[key]->data[i].pointer, myList->record.entryDate, myList);
                break;
              }
              if(!strcmp(hashTable[key]->data[i].key,myList->record.country)){
                  hashTable[key]->data[i].pointer = insert(hashTable[key]->data[i].pointer, myList->record.entryDate, myList);
                break;
              }

            }

            myList = myList->next;
          }
          key = hash(myList->record.country,hashSize);

          for(int i=0;i<bs;i++){
            if(hashTable[key]->data[i].key == NULL){
              hashTable[key]->data[i].key = myList->record.country;
              hashTable[key]->data[i].pointer = insert(hashTable[key]->data[i].pointer, myList->record.entryDate, myList);
              break;
            }
            if(!strcmp(hashTable[key]->data[i].key,myList->record.country)){
                hashTable[key]->data[i].pointer = insert(hashTable[key]->data[i].pointer, myList->record.entryDate, myList);
              break;
            }

          }
        }
}

struct bucket* initializeNewBucket(){
  struct bucket* temp;
  temp = (struct bucket*) malloc(sizeof(struct bucket));
  temp->next = NULL;
  temp->data = (struct bucket_entry*)malloc(bs*sizeof(struct bucket_entry)); //prepei na allaxw to 4

  for(int i=0;i<bs;i++){
    temp->data[i].key = NULL;
    temp->data[i].pointer = NULL;
  }
  return temp;
}

void initializeHashTable(struct bucket** hashTable,int hashSize){
  for(int i=0;i<hashSize;i++){
    hashTable[i] = initializeNewBucket();
  }
}

void printHashTable(struct bucket** hashTable,int hashSize){
  for(int i=0;i<hashSize;i++){
    printf("Bucket %d \n",i);
    for(int j=0;j<bs;j++){
      printf(" %s ->  ",hashTable[i]->data[j].key);
      preOrder(hashTable[i]->data[j].pointer);
      printf("\n");
    }
    printf("\n");
  }
  printf("\n");
}

int countTreeNodes(struct Node*root,int* sum){
  if(root != NULL)
  {
      (*sum)++;
      countTreeNodes(root->left,sum);
      countTreeNodes(root->right,sum);
  }

}

void countTreeNodesBetweenDates(struct Node*root,int* sum,struct dateType date1,struct dateType date2){
  if(root != NULL)
  {
    if(compareDates(date1,root->key)==1 && compareDates(root->key,date2)==1)
      (*sum)++;

      countTreeNodesBetweenDates(root->left,sum,date1,date2);
      countTreeNodesBetweenDates(root->right,sum,date1,date2);
  }
}

void countTreeNodesBetweenDatesforCountry(struct Node*root,int* sum,struct dateType date1,struct dateType date2,char* country){
  if(root != NULL)
  {
    if(compareDates(date1,root->key)==1 && compareDates(root->key,date2)==1 &&  strcmp(country,root->pointer->record.country)==0){
      (*sum)++;

    }


      countTreeNodesBetweenDatesforCountry(root->left,sum,date1,date2,country);
      countTreeNodesBetweenDatesforCountry(root->right,sum,date1,date2,country);
  }
}

void globalDiseaseStats(struct dateType date1,struct dateType date2,struct bucket** hashTable,int hashSize){
    if(date1.year == 0){ //an den dothei date1 date2 ekthpwse ta ola
      for(int i=0;i<hashSize;i++){
        for(int j=0;j<bs;j++){
          if(hashTable[i]->data[j].key != NULL){
            int nodes = 0;
            countTreeNodes(hashTable[i]->data[j].pointer,&nodes);
            printf(" %s %d \n",hashTable[i]->data[j].key,nodes);
          }
        }
      }
    }else{//an dwthei date1 date2 mono afta pou eina anamesa
      for(int i=0;i<hashSize;i++){
        for(int j=0;j<bs;j++){
          if(hashTable[i]->data[j].key != NULL){
            int nodes = 0;
            countTreeNodesBetweenDates(hashTable[i]->data[j].pointer,&nodes,date1,date2);
            printf(" %s %d \n",hashTable[i]->data[j].key,nodes);
          }
        }
      }
    }
 }

void diseaseFrequency(struct dateType date1,struct dateType date2,struct bucket** hashTable,int hashSize,char* virusName,char* country){
  if(!strcmp(country,"none")){
    for(int i=0;i<hashSize;i++){
      for(int j=0;j<bs;j++){
        if(hashTable[i]->data[j].key != NULL && strcmp(hashTable[i]->data[j].key,virusName)==0 ){
          int nodes = 0;
          countTreeNodesBetweenDates(hashTable[i]->data[j].pointer,&nodes,date1,date2);
          printf(" %s %d \n",hashTable[i]->data[j].key,nodes);
        }
      }
    }
  }else{
    for(int i=0;i<hashSize;i++){
      for(int j=0;j<bs;j++){
        if(hashTable[i]->data[j].key != NULL && strcmp(hashTable[i]->data[j].key,virusName)==0 ){
          int nodes = 0;
          countTreeNodesBetweenDatesforCountry(hashTable[i]->data[j].pointer,&nodes,date1,date2,country);
          printf(" %s %d %s \n",hashTable[i]->data[j].key,nodes,country);
        }
      }
    }
  }
};

int isNullDate(struct dateType date){
  if(date.year==0 && date.month ==0 && date.day ==0)
    return 1;
  return 0;
};

void printRecordsInHospital(struct Node* root){
  if(root != NULL)
  {
      if(isNullDate(root->pointer->record.exitDate)==1){
          printf("Id = %s \n",root->pointer->record.recordId);
      }
      printRecordsInHospital(root->left);
      printRecordsInHospital(root->right);
  }
};

void patientsInHospital(struct Node*root,int* sum){
  if(root != NULL)
  {
    if(isNullDate(root->pointer->record.exitDate)==1)
      (*sum)++;
      patientsInHospital(root->left,sum);
      patientsInHospital(root->right,sum);
  }

};

void numCurrentPatients(struct bucket** hashTable,int hashSize,char* disease){
  if(!strcmp(disease,"none")){
    for(int i=0;i<hashSize;i++){
      for(int j=0;j<bs;j++){
        if(hashTable[i]->data[j].key != NULL){
          printf(" %s \n",hashTable[i]->data[j].key);
          printRecordsInHospital(hashTable[i]->data[j].pointer);
          printf("\n");
        }
      }
    }
  }else{
    for(int i=0;i<hashSize;i++){
      for(int j=0;j<bs;j++){
        if(hashTable[i]->data[j].key != NULL && strcmp(disease,hashTable[i]->data[j].key)==0){
          printf(" %s ",hashTable[i]->data[j].key);
          int sum=0;
          patientsInHospital(hashTable[i]->data[j].pointer,&sum);
          printf(" %d ",sum);
          printf("\n");
        }
      }
  }
}
};

void recordPatientExit(struct listNode* list,char* recordId,struct dateType date){
  while(list->next != NULL){
    if(!strcmp(recordId,list->record.recordId)){
      list->record.exitDate.year = date.year;
      list->record.exitDate.month = date.month;
      list->record.exitDate.day = date.day;
    }
    list = list->next;
  }
  if(!strcmp(recordId,list->record.recordId)){
    list->record.exitDate.year = date.year;
    list->record.exitDate.month = date.month;
    list->record.exitDate.day = date.day;
  }
  printf("Record updated\n");
}

void insertPatientRecord(struct listNode* list,struct bucket** diseaseHashTable,struct bucket** countryHashTable,int h1,int h2,char* recordId,
char* firstName,char* lastName,char* diseaseId,char* country, struct dateType entryDate, struct dateType exitDate){
 struct listNode* tempListNode = NULL;
  tempListNode = (struct listNode*)malloc(sizeof(struct listNode));
  strcpy(tempListNode->record.recordId,recordId);
  strcpy(tempListNode->record.patientFirstName,firstName);
  strcpy(tempListNode->record.patientLastName,lastName);
  strcpy(tempListNode->record.diseaseId,diseaseId);
  strcpy(tempListNode->record.country,country);
  tempListNode->record.entryDate.year = entryDate.year;
  tempListNode->record.entryDate.month = entryDate.month;
  tempListNode->record.entryDate.day = entryDate.day;
  tempListNode->record.exitDate.year = exitDate.year;
  tempListNode->record.exitDate.month = exitDate.month;
  tempListNode->record.exitDate.day = exitDate.day;
  tempListNode->next = NULL;
  while(list->next != NULL){
    list = list->next;
  }

  list->next = tempListNode;
  insertDataToHashtable(countryHashTable,h2,tempListNode,"country");
  insertDataToHashtable(diseaseHashTable,h1,tempListNode,"diseaseId");
  printf("Record Added\n");

}

int wordsInString(char *str){
    int state = 0;
    unsigned wc = 0;  // word count

    // Scan all characters one by one
    while (*str)
    {
        // If next character is a separator, set the
        // state as OUT
        if (*str == ' ' || *str == '\n' || *str == '\t')
            state = 0;

        // If next character is not a word separator and
        // state is OUT, then set the state as IN and
        // increment word count
        else if (state == 0)
        {
            state = 1;
            ++wc;
        }

        // Move to next character
        ++str;
    }

    return wc;
}

void setDate(struct dateType* date,int day,int month,int year){
  date->year = year;
  date->month = month;
  date->day = day;
}

void setDateFromString(struct dateType* date,char*str){
  char tmp_buf[20];//tmp buffer so i can keep the whole date in the other on
  strncpy(tmp_buf, str, 20);
  //Get day
  const char s[2] = "-";
  char *token;
  token = strtok(tmp_buf, s);
//  rec->entryDate.Day = atoi(token);
  date->day = atoi(token);
  //Get month
  char*tmp;
  strncpy(tmp_buf, str, 20);//take the whole date again
  tmp = tmp_buf;
  while(tmp[0]!=s[0])//skip the Day
  {
    tmp++;
  }
  tmp++;
  token = strtok(tmp, s);
  date->month = atoi(token);
  //rec->entryDate.Month = atoi(token);
  //printf("Entry Month is %d\n",rec->entryDate.Month);
  //Get year
  strncpy(tmp_buf, str, 20);//take the whole date again
  tmp = tmp_buf;
  int flag=0;
  while(tmp[0]!=s[0])//skip the Day
  {
    tmp++;
  }
  tmp++;
  while(tmp[0]!=s[0])//skip the Month
  {
    tmp++;
  }
  tmp++;
  token = strtok(tmp, s);
  date->year = atoi(token);
};

void reheapify(struct heapNode * N){
    struct heapNode * M;
    struct arrayNode* V1;
    struct arrayNode* V2;
    struct arrayNode* temp;

    V1 = N->value;

    while(N->left != NULL && N->right != NULL){
        if (N->left->value->key1 > N->right->value->key1){
            M = N->left;
        }
        else if (N->left->value->key1 < N->right->value->key1){
            M = N->right;
        }

        V2 = M->value;

        if (V1->key1 >= V2->key1){
            return;
        } else {
            temp = N->value;
            N->value = M->value;
            M->value = temp;

            N = M;
            V1 = N->value;
        }
    }
}

void printLevel(struct heapNode * root, int level){
    if (root == NULL) return;
    //if (level == 1) printf("%d ",root -> value);
    if (level == 1) reheapify(root);
    else if (level > 1){
        printLevel(root -> left, level-1);
        printLevel(root -> right, level-1);
    }
}

void heapify(struct heapNode * heap){
    int height = heightOfTree(heap);

    for(int i = height;i >= 1;i--) printLevel(heap,i);
}

struct heapNode *newEmptyTree(void) {
    struct heapNode *new = malloc(sizeof (struct heapNode));
    if (new == NULL) {
        printf("Failed allocation.\n");
        return NULL;
    }
    new->value = NULL;
    new->left = NULL;
    new->right = NULL;
    return new;
}

struct heapNode *heap_from_array(struct arrayNode* arr, int index, int elements) {

    if (index >= elements) return NULL;

    struct heapNode *this = newEmptyTree();

    this->value = &arr[index];
    this->left = heap_from_array(arr, 2*index + 1, elements);
    this->right = heap_from_array(arr, 2*index + 2, elements);

    return this;
}

void printPre(struct heapNode * root){
    struct heapNode * parent = root;
    if (parent == NULL) return;

    printf("%s %d\n",parent->value->key2,parent ->value->key1);
    printPre(parent -> left);
    printPre(parent -> right);
}

int heightOfTree(struct heapNode * root){
    if (root == NULL) return 0;
    else{
        int leftHieght = heightOfTree(root -> left);
        int rightHeight = heightOfTree(root -> right);

        if (leftHieght > rightHeight) return leftHieght+1;
        else return rightHeight+1;
    }
}

void fixTabeleFromTree(struct Node*root,struct arrayNode* my_array,int array_size,struct dateType date1,struct dateType date2 ){

  if(root != NULL)
  {
    if((compareDates(date1,root->key)==1 && compareDates(root->key,date2)==1) || date1.year == 0){
      for(int i=0;i<array_size;i++){
        if(!strcmp(my_array[i].key2,"x")){
            strcpy(my_array[i].key2,root->pointer->record.diseaseId);
            my_array[i].key1 = my_array[i].key1 + 1;
            break;
        }else if(!strcmp(my_array[i].key2,root->pointer->record.diseaseId)){
          my_array[i].key1 = my_array[i].key1 + 1;
          break;
        }
      }
    }

      fixTabeleFromTree(root->left,my_array,array_size,date1,date2);
      fixTabeleFromTree(root->right,my_array,array_size,date1,date2);
  }

}

void fixTabeleFromTree2(struct Node*root,struct arrayNode* my_array,int array_size,struct dateType date1,struct dateType date2 ){

  if(root != NULL)
  {
    if((compareDates(date1,root->key)==1 && compareDates(root->key,date2)==1) || date1.year == 0){
      for(int i=0;i<array_size;i++){
        if(!strcmp(my_array[i].key2,"x")){
            strcpy(my_array[i].key2,root->pointer->record.country);
            my_array[i].key1 = my_array[i].key1 + 1;
            break;
        }else if(!strcmp(my_array[i].key2,root->pointer->record.country)){
          my_array[i].key1 = my_array[i].key1 + 1;
          break;
        }
      }
    }

      fixTabeleFromTree2(root->left,my_array,array_size,date1,date2);
      fixTabeleFromTree2(root->right,my_array,array_size,date1,date2);
  }

}
int numOfDiseases(struct bucket** diseaseHashTable,int h1){
  int sum = 0;
  for(int i=0;i<h1;i++){
    for(int j=0;j<bs;j++){
      if(diseaseHashTable[i]->data[j].key != NULL){
        sum++;
      }
    }
  }
  return sum;
}

void topkDiseases(struct bucket** diseaseHashTable, struct bucket** countryHashTable,int h1,int h2,char* country,struct dateType date1,struct dateType date2,int k){

  int key = hash(country,h2);
    for(int j=0;j<bs;j++){
      if(countryHashTable[key]->data[j].key != NULL && strcmp(country,countryHashTable[key]->data[j].key)==0){
        int diseaseSum = numOfDiseases(diseaseHashTable,h1);
        struct arrayNode* my_array = malloc(diseaseSum*sizeof (struct arrayNode));
        for(int i=0;i<diseaseSum;i++){
          my_array[i].key1 = 0;
          strcpy(my_array[i].key2,"x");
        }

        fixTabeleFromTree(countryHashTable[key]->data[j].pointer,my_array,diseaseSum,date1,date2);



        struct heapNode * heap = NULL;
        heap = heap_from_array(my_array,0,diseaseSum);
        printf("Height of tree: %d\n",heightOfTree(heap));
         heapify(heap);
         printPre(heap);
         printf("\n");
      }
    }
}


void topkCountries(struct bucket** diseaseHashTable, struct bucket** countryHashTable,int h1,int h2,char* disease,struct dateType date1,struct dateType date2,int k){

    int key = hash(disease,h1);
    for(int j=0;j<bs;j++){
      if(diseaseHashTable[key]->data[j].key != NULL && strcmp(disease,diseaseHashTable[key]->data[j].key)==0){
        int countrySum = numOfDiseases(countryHashTable,h2);
        struct arrayNode* my_array = malloc(countrySum*sizeof (struct arrayNode));
        for(int i=0;i<countrySum;i++){
          my_array[i].key1 = 0;
          strcpy(my_array[i].key2,"x");
        }

        fixTabeleFromTree2(diseaseHashTable[key]->data[j].pointer,my_array,countrySum,date1,date2);



        struct heapNode * heap = NULL;
        heap = heap_from_array(my_array,0,countrySum);
        printf("Height of tree: %d\n",heightOfTree(heap));
        printPre(heap);
        printf("\n");
        // heapify(heap);
        // printPre(heap);
        // printf("\n");
      }
    }
}

void deleteTree(struct Node* node)
{
    if (node == NULL) return;

    deleteTree(node->left);
    deleteTree(node->right);

    free(node->pointer); //me afto diagrafete paralila kai h lista
    free(node);
}


void myExit(struct bucket** diseaseHashTable, struct bucket** countryHashTable,int h1,int h2){
  for(int i=0;i<h1;i++){
    for(int j=0;j<bs;j++){
      if(diseaseHashTable[i]->data[j].key != NULL){
        deleteTree(diseaseHashTable[i]->data[j].pointer);
      }
    }
    free(diseaseHashTable[i]->data);
  }
  free(*diseaseHashTable);
  for(int i=0;i<h1;i++){

    free(countryHashTable[i]->data);
  }
  free(*countryHashTable);

  printf("exiting\n");
}
