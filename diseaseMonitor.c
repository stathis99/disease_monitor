#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"




int main(int argc, char* argv[]){
  const char* fileName = argv[2];
  struct listNode* list;


 int h1 = atoi(argv[4]);
 int h2 = atoi(argv[6]);
 int b = atoi(argv[8]);


 list = insertRecordsFromFileToLinkedList();
 // printList(list);
 checkFile(list);

 //ftiaxnw ta hash table
 struct bucket** diseaseHashTable = (struct bucket**)malloc(h1*sizeof(struct bucket*));
 struct bucket** countryHashTable = (struct bucket**)malloc(h2*sizeof(struct bucket*));

 initializeHashTable(diseaseHashTable,h1);
 initializeHashTable(countryHashTable,h2);

 insertDataToHashtable(countryHashTable,h2,list,"country");
 insertDataToHashtable(diseaseHashTable,h1,list,"diseaseId");

 // printHashTable(countryHashTable,h2);
 // printHashTable(diseaseHashTable,h1);



  char buf[100];
  char myCmd[100];
  int flag = 0;
  char s1[100] = "null";
  char s2[100] = "null";
  char s3[100] = "null";
  char s4[100] = "null";
  char s5[100] = "null";
  char s6[100] = "null";
  char s7[100] = "null";

  struct dateType date1,date2;

do{

  fgets(buf, sizeof buf, stdin);
  sscanf(buf, "%s %s %s %s %s %s %s %s", myCmd,s1,s2,s3,s4,s5,s6,s7);

  if(!strcmp(myCmd,"/globalDiseaseStats")){
     if(wordsInString(buf) == 1){
       setDate(&date1,0,0,0);
       setDate(&date2,0,0,0);
       globalDiseaseStats(date1,date2,diseaseHashTable,h1);
     }else if(wordsInString(buf) == 3){
       setDateFromString(&date1,s1);
       setDateFromString(&date2,s2);
       globalDiseaseStats(date1,date2,diseaseHashTable,h1);
     }else{
       printf("wrong input!\n");
     }
  }else if(!strcmp(myCmd,"/diseaseFrequency")){
    if(wordsInString(buf) == 4){
      setDateFromString(&date1,s2);
      setDateFromString(&date2,s3);
      diseaseFrequency(date1,date2,diseaseHashTable,h1,s1,"none");
    }else if(wordsInString(buf) == 5){
      setDateFromString(&date1,s2);
      setDateFromString(&date2,s3);
      diseaseFrequency(date1,date2,diseaseHashTable,h1,s1,s4);
    }else{
      printf("wrong input!\n");
    }
  }else if(!strcmp(myCmd,"/insertPatientRecord")){
    if(wordsInString(buf) == 7){
      setDateFromString(&date1,s6);
      setDate(&date2,0,0,0);
      insertPatientRecord(list,diseaseHashTable,countryHashTable,h1,h2,s1,s2,s3,s4,s5,date1,date2);
    }else if(wordsInString(buf) == 8){
      setDateFromString(&date1,s6);
      setDateFromString(&date2,s7);
      insertPatientRecord(list,diseaseHashTable,countryHashTable,h1,h2,s1,s2,s3,s4,s5,date1,date2);
    }else{
      printf("wrong input!\n");
    }
  }else if(!strcmp(myCmd,"/recordPatientExit")){
    if(wordsInString(buf) == 3){
      setDateFromString(&date1,s2);
      recordPatientExit(list,s1,date1);
    }else{
      printf("wrong input!\n");
    }
  }else if(!strcmp(myCmd,"/numCurrentPatients")){
    if(wordsInString(buf) == 1){
      numCurrentPatients(diseaseHashTable,h1,"none");
    }else if(wordsInString(buf) == 2){
      numCurrentPatients(diseaseHashTable,h1,s1);
    }else{
      printf("wrong input!\n");
    }
  }else if(!strcmp(myCmd,"/exit")){
    myExit(diseaseHashTable,countryHashTable,h1,h2);
    flag = 1;
  }else if(!strcmp(myCmd,"/topk-Diseases")){
      if(wordsInString(buf) == 3){
          setDate(&date1,0,0,0);
          setDate(&date2,0,0,0);
          topkDiseases(diseaseHashTable,countryHashTable,h1,h2,s2,date1,date2,atoi(s1));
      }else if(wordsInString(buf) == 5){
        setDateFromString(&date1,s3);
        setDateFromString(&date2,s4);
        topkDiseases(diseaseHashTable,countryHashTable,h1,h2,s2,date1,date2,atoi(s1));
      }else{
        printf("wrong input!\n");
      }
  }else if(!strcmp(myCmd,"/topk-Countries")){
    if(wordsInString(buf) == 3){
        setDate(&date1,0,0,0);
        setDate(&date2,0,0,0);
        topkCountries(diseaseHashTable,countryHashTable,h1,h2,s2,date1,date2,atoi(s1));
    }else if(wordsInString(buf) == 5){
      setDateFromString(&date1,s3);
      setDateFromString(&date2,s4);
      topkCountries(diseaseHashTable,countryHashTable,h1,h2,s2,date1,date2,atoi(s1));
    }else{
      printf("wrong input!\n");
    }
  }else{
      printf("wrong input!\n");
  }
}while(flag==0);

}
