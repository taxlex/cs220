#include "arrayList.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#define INITSIZE 16

bool arrayListEnlarge(arrayList list);

arrayList arrayListCreate() {
	arrayList list = (arrayList)malloc(sizeof(struct arrayListStruct));
	if (list==NULL) return list;
	list->data=(int *)malloc(sizeof(int)*INITSIZE);
	list->numUsed=0;
	list->numAlloc=INITSIZE;
	return list;
}

bool arrayListEnlarge(arrayList list) {
	list->data=(int *)realloc(list->data,sizeof(int) * (2*list->numAlloc));
	if (list->data==NULL) return false;
	list->numAlloc *=2;
	return true;
}
bool arrayListAdd(arrayList list, int item){
	bool added = false;
	if(list->numUsed<list->numAlloc){
		list->data[list->numUsed] = item;
		list->numUsed++;
		added = true;
	}
	else{
		arrayListEnlarge(list);
		list->data[list->numUsed] = item;
		list->numUsed++;
		added = true;
	}
	return added;
}
void arrayListClear(arrayList list){
	int i;
	for(i = 0; i < list->numUsed; i++){
		list->data[i] = 0;
	}
	list->numUsed = 0;
}
bool arrayListContains(arrayList list, int item){
	bool contains = false;
	int i;
	for(i = 0; i < list->numUsed; i++){
		if(list->data[i] == item) contains = true;
	}
	return contains;
}
int arrayListGet(arrayList list,int index){
	assert(index >= 0 && index < list->numUsed);
	int val = list->data[index];
	return val;
}
int arrayListIndexOf(arrayList list, int item){
	int i;
	for(i = 0; i < list->numUsed; i++){
		if(list->data[i] == item) return i;
	}
	return -1;
}
bool arrayListIsEmpty(arrayList list){
	if(list->numUsed == 0) return true;
	return false;
}
int arrayListSet(arrayList list, int index, int item){
	assert(index >= 0);
	int prevVal = -1;
	if(index < list->numAlloc){
		prevVal = list->data[index];
		list->data[index] = item;
	}
	else{
		arrayListEnlarge(list);
		prevVal = arrayListSet(list, index, item);
	}
	return prevVal;
}
int arrayListSize(arrayList list){
	return list->numUsed;
}
char * arrayListToString(arrayList list,char *buffer){
	int i;
	/*
	for(i = 0; i < list->numUsed; i++){
		snprintf(buffer,list->numUsed,"%d",list->data[i]);
	}
	*/
	return buffer;
}
/* Put definitions of the other arrayList methods in arrayList.h here */

void arrayListFree(arrayList list) {
	free(list->data);
	free(list);
}
