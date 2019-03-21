/*
 * da.c
 * dynamic array class
 *
 *  Created on: Aug 28, 2018
 *      Author: Emily Schroeder
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "da.h"

typedef struct da{	//struct definition
	int size;
	int capacity;
	void **store;
	void (*displayFunc)(void *, FILE *);
	void (*freeFunc)(void *);
	int debugFlag;
}DA;

DA* newDA(void){	//constructor
	DA *items = malloc(sizeof(*items));
	items->store = malloc(1*sizeof(void*));
	items->size = 0;
	items->capacity = 1;
	items->debugFlag = 0;
	return items;
}

void  setDAdisplay(DA *da,void (*function)(void *, FILE *)){ //set the display function
	da->displayFunc = function;
}

void  setDAfree(DA *da,void (*function)(void *)){ //set the free function
	da->freeFunc = function;
}

void  insertDA(DA *items,int index,void *value){
	assert(index>=0 && index<=(items->size)); //Kills program if the index is invalid
	if((items->size)==(items->capacity)){	//need to double the array before inserting
		items->capacity = 2*(items->capacity);
		items->store = realloc(items->store, sizeof(void*)*(items->capacity));
	}
	if(index < items->size){	//Shifts the values to make room at index
		int i;
		for(i = items->size; i > index; i--){
			setDA(items, i, getDA(items, i-1));
		}
		items->size--;
	}
	items->store[index] = value; //inserts the value
	items->size++;
}

void* removeDA(DA *items,int index){
	assert(index>=0 && index<=(items->size)); //Kills program if the index is invalid //FIX TO GETSIZE() ONCE WRITTEN
	void *returnedVal = getDA(items, index); //saves the current value at that index to be returned later
	items->size--; //reduces the size
	if(index < (items->size)){ //if it wants to remove anything but the last element
		int i;
		for(i = index; i < (items->size); i++){ //moves any elements past the removed element back one in the array
			setDA(items, i, getDA(items, i+1));
		}
	}
	if(items->size == 0){
			items->capacity = 1;
			items->store = realloc(items->store, sizeof(void*)*(items->capacity));
	}
	else if(items->size < (items->capacity)/4){ //if the size is less than one fourth the capacity
		items->capacity /= 2;
		items->store = realloc(items->store, sizeof(void*)*(items->capacity));
	}
	return returnedVal;
}

void  unionDA(DA *recipient,DA *donor){ //takes two array and moves all the items in the donor array to the recipient array
	int i;
	for(i=donor->size-1; i >= 0; i--){
		void *d = removeDA(donor, i);
		insertDA(recipient, recipient->size, d);
		donor->freeFunc(d);
	}

}

void* getDA(DA *items,int index){ //Returns the value at the given index
	assert(index>=0 && index<=(items->size)); //Kills program if the index is invalid //FIX TO GETSIZE() ONCE WRITTEN
	return items->store[index];
}

void* setDA(DA *items,int index,void *value){	//The method returns the replaced value or the null pointer if no value was replaced
	assert(index>=0 && index<=(items->size)); //Kills program if the index is invalid //FIX TO GETSIZE() ONCE WRITTEN
	void* returnedVal;
	if(index == items->size){ //Just insert the value at the end of the array
		insertDA(items, index, value);
		returnedVal = NULL;
	} else { //it's replacing an element
		returnedVal = items->store[index];
		items->store[index] = value;
	}
	return returnedVal;
}

int sizeDA(DA *items){ //returns the size of the array
	return items->size;
}

void  displayDA(DA *items,FILE *fp){	//displays the array
	fprintf(fp, "[");
	int i;
	for(i=0; i < items->size; i++){
		(items->displayFunc)(items->store[i], fp);
		
		if(i != items->size-1){
			fprintf(fp, ",");
		}
	}
	if(items->debugFlag>0){ //if debug flag was set above 0
		if(items->size != 0){
			fprintf(fp, ",");
		}
		fprintf(fp, "[%d]",  ((items->capacity) - (items->size)));
		
	}
	fprintf(fp, "]");
}

int   debugDA(DA *items,int level){	//sets debug flag to level
	int old = items->debugFlag;
	items->debugFlag = level;
	return old;
}

void  freeDA(DA *items){	//frees the array
	int i;
	for(i=items->size-1; i >= 0; i--){
		items->freeFunc(items->store[i]);
	}
	items->freeFunc(items->store);
	items->size = 0;
	items->capacity=0;
	free(items);
}
