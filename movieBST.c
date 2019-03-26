#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "movieBST.h"
#include <string.h>
#include "da.h"
#include "movieBST.h"

#include <ctype.h>

typedef struct movie {	//struct definition
	char tconst[10];
	char titleType[6];
	char primaryTitle[240];        //used as key for the BST
	char originalTitle[240];
	char isAdult[2];
	char startYear[5];
	char endYear[5];
	char runtimeMinutes[5];
	char genres[240];
	
	int visited;
	
	char mediaType[8];			//set later by user in collection only
	char date[10];				//set later by user in colleciton only
	
	MOVIE* left;
	MOVIE* right;
	MOVIE* parent;
}MOVIE;

//creates a new movie node
MOVIE* newMovie(char* tID, char* type, char* pTitle, char* oTitle, char* adult, char* sYear, char* eYear, char* runTime, char* inGenres) {
    MOVIE *new_movie = (MOVIE*)malloc(sizeof(MOVIE));//allocates enough memory for the movie node
	
    if(new_movie == NULL) {
        fprintf (stderr, "Something went wrong with malloc for new movie\n");
        exit(1);
    }
	//setting the variables to what were passed
	strcpy(new_movie->tconst, tID);
	strcpy(new_movie->titleType, type);
	strcpy(new_movie->primaryTitle, pTitle);
	strcpy(new_movie->originalTitle, oTitle);
	strcpy(new_movie->isAdult, adult);
	strcpy(new_movie->startYear, sYear);
	strcpy(new_movie->endYear, eYear);
	strcpy(new_movie->runtimeMinutes, runTime);
	strcpy(new_movie->genres, inGenres);
	
	new_movie->visited = 0;//hasn't been visited yet in a search
	
    //set later as needed
	new_movie->left = NULL;
    new_movie->right = NULL;
	new_movie->parent = NULL;
	//pass back the movie
    return new_movie;
}

//accessor methods
char* getID(MOVIE* mov){
	return mov->tconst;
}

char* getType(MOVIE* mov){
	return mov->titleType;
}

char* getPTitle(MOVIE* mov){
	return mov->primaryTitle;
}

char* getOTitle(MOVIE* mov){
	return mov->originalTitle;
}

char* getAdult(MOVIE* mov){
	return mov->isAdult;
}

char* getSYear(MOVIE* mov){
	return mov->startYear;
}

char* getEYear(MOVIE* mov){
	return mov->endYear;
}

char* getRuntime(MOVIE* mov){
	return mov->runtimeMinutes;
}

char* getGenres(MOVIE* mov){
	return mov->genres;
}

char* getMediaType(MOVIE* mov){
	return mov->mediaType;
}

char* getDate(MOVIE* mov){
	return mov->date;
}

//mutator methods
void setParent(MOVIE* mov, MOVIE* par){
	mov->parent = par;
}

void setMediaType(MOVIE* mov, char* medType){
	strcpy(mov->mediaType, medType);
}

void setDate(MOVIE* mov, char* d){
	strcpy(mov->date, d);
}

MOVIE* insertMovie(MOVIE *root, MOVIE *newMov) {
    if(root == NULL) {
        root = newMov;																					//if there are no other movies, create a new movie and set it as the root of the tree
    } else {
        int is_left  = 0;																				//saves if it should be the left or right child
        int r        = 0;																				//saves the comparison value
        MOVIE* current = root;																			//sets the current movie to the root to start
        MOVIE* prev   = NULL;																			//sets the prev value to null for the root
 
        while(current != NULL) {																		//if the current movie isn't null
			r = strcmp(getPTitle(newMov),current->primaryTitle);										//compare the title passed to the function with the title of the current movie			
			prev = current;																				//set the previous node to current
            if(r < 0) {																					//if the title passed is "less than" the current title
				is_left = 1;																			//mark that it should go left
                current = current->left;																//set the current value to the current value's left value
            } else if(r > 0) {																			//if the title passed is "greater than" the current title
				is_left = 0;																			//mark that it should go right
                current = current->right;																//set the current value to the current value's right value
            } 
			else {																						//if the current is the same
				is_left = 1;																			//mark it to go left
				current = current->left;																//set the current value to the current value's left value
			}
 
        }
        if(is_left){																					//if it should be a left value
			prev->left = newMov;																		//set the prev movie's left to the new movie
			setParent(prev->left, prev);																//set the parent
		} else {																						//if it should be a right value
			prev->right = newMov;																		//set the prev movie's right to the new movie
			setParent(prev->right, prev);																//set the parent
		}
 
    }
    return root;
}

MOVIE* removeMovie(MOVIE *root, char* pTitle)															//removes the movie from the list
{
    if(root == NULL)																					//if root is null, return now
        return NULL;
 
    MOVIE *current;
    int r = strcmp(pTitle,root->primaryTitle);															//compare the searched title to the current title
    if( r < 0)
        root->left = removeMovie( root->left, pTitle);													//run the remove function on the left subtree
    else if( r > 0 )
        root->right = removeMovie(root->right, pTitle);													//run the remove function on the right subtree
    else
    {
        if (root->left == NULL)
        {
            current = root->right;																		//set current to right
            free(root);																					//remove the root
            root = current;																				//set root to current
        }
        else if (root->right == NULL)
        {
            current = root->left;																		//set current to left
            free(root);																					//remove the root
            root = current;																				//set root to current
        }
        else    //2 children
        {
            current = root->right;																		//set current to right
            MOVIE *parent = NULL;																		//create a parent node
 
            while(current->left != NULL)																//while there is a left node to look at
            {
                parent = current;																		//set parent to current
                current = current->left;																//set current to left
            }
            //setting root to current
			strcpy(root->tconst, current->tconst);
			strcpy(root->titleType, current->titleType);
			strcpy(root->primaryTitle, current->primaryTitle);
			strcpy(root->originalTitle, current->originalTitle);
			strcpy(root->isAdult, current->isAdult);
			strcpy(root->startYear, current->startYear);
			strcpy(root->endYear, current->endYear);
			strcpy(root->runtimeMinutes, current->runtimeMinutes);
			strcpy(root->genres, current->genres);
			setMediaType(root, current->mediaType);
			setDate(root, current->date);
            if (parent != NULL)
                parent->left = removeMovie(parent->left, parent->left->primaryTitle);					//remove parent's left node
            else
                root->right = removeMovie(root->right, root->right->primaryTitle);						//remove root's right node
        }
    }
    return root;
}

DA* findMovies(MOVIE *root, const char* pTitle){	//Linear search to find any entry that contains the word
	MOVIE* current = root;
	MOVIE* prev = NULL;
	DA* array = newDA();																				//holds all the movies found
	char inTitle[240];																					//holds pTitle, so it can be changed to lowercase
	strcpy(inTitle, pTitle);
	int i;
	for(int i=0; i < strlen(inTitle); i++){																//changes inTitle (pTitle) to all lowercase
		inTitle[i] = tolower(inTitle[i]);
	}
	while(current != NULL){	
		char compString[240];																			//holds current->primaryTitle, so it can be changed
		strcpy(compString, getPTitle(current));
		
		for(int i = 0; i < strlen(compString); i++){													//changes compString (current->primaryTitle) to all lowercase
			compString[i] = tolower(compString[i]);
		}
		
		char* check = strstr(compString, inTitle);														//compare the passed title to the current's title
		if((check!=NULL) && (current->visited != 1)){	//if it contains the substring
			insertDA(array, sizeDA(array), current);		//add it to the dynamic array
		}
		current->visited = 1;																			//mark as visited
		//if left exists, and has not been visited, check that one
		if(current->left != NULL && current->left->visited != 1){
			prev = current;
			current = current->left;
		}
		//if those conditions fail, then
		else {
			//if right exists and has not been visited, check that one
			if(current->right != NULL && current->right->visited != 1){
				prev = current;
				current = current->right;
			}
			//if that fails, back up
			else {
				if(prev == NULL){
					break;
				}
				current = prev;										//move to the parent node 
				prev = prev->parent;								//set prev to its parent
			}
		}
	}
	
	//reseting visited to 0, for future searches
	reset(root);
	
	return array;
}
//marks every node as unvisited
void reset(MOVIE *root){
	if(root == NULL){
		return;
	}
	root->visited = 0;
	reset(root->left);
	reset(root->right);
}

void printTree(MOVIE* root, FILE* f){		//inorder traversal
	if(root == NULL){
		return;
	}
	printTree(root->left, f);	//left
	printMovie(root, f);		//center
	printTree(root->right, f); //right
}

void printTreeForFile(MOVIE* root, FILE* f){		//preorder traversal, so when it rebuilds the tree, it shouldn't be a regular linked list
	if(root == NULL){
		return;
	}
	//center
	printMovie(root, f);
	printTreeForFile(root->left, f);	//left
	printTreeForFile(root->right, f);	//right
}

//frees the whole tree
void dispose(MOVIE* root) {
    if(root != NULL)
    {
        dispose(root->left);
        dispose(root->right);
        free(root);
    }
}

void printMovie(MOVIE* mov, FILE *f)
{
    if(mov != NULL){
		fprintf(f, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s", getID(mov), getType(mov), getPTitle(mov), getOTitle(mov), getAdult(mov), getSYear(mov), getEYear(mov), getRuntime(mov), getGenres(mov), getMediaType(mov), getDate(mov));
		fprintf(f, "\n");
	}
}

//find the movie if the whole title is given
MOVIE* find(MOVIE *root, const char* pTitle){	//log(n) search function, used when finding movies in the code
	//if root is null, return
	if(root == NULL)
        return NULL;
 
    int r;
    MOVIE* current = root;
    while(current != NULL)
    {
        //compare the passed title to the current title
		r = strcmp(pTitle,current->primaryTitle);
        //if the passed title is less, go left
		if(r < 0)
            current = current->left;
        //if the passed title is more, go right
		else if(r > 0)
            current = current->right;
        //if they match, return the current node
		else
            return current;
    }
    return current;
}