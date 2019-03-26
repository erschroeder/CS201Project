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
	strcpy(new_movie->tconst, tID);
	strcpy(new_movie->titleType, type);
	strcpy(new_movie->primaryTitle, pTitle);
	strcpy(new_movie->originalTitle, oTitle);
	strcpy(new_movie->isAdult, adult);
	strcpy(new_movie->startYear, sYear);
	strcpy(new_movie->endYear, eYear);
	strcpy(new_movie->runtimeMinutes, runTime);
	strcpy(new_movie->genres, inGenres);
	
	new_movie->visited = 0;
	
    //set later as needed
	new_movie->left = NULL;
    new_movie->right = NULL;
	new_movie->parent = NULL;
	//set later by user in collection only
	//new_movie->mediaType = NULL;
	//new_movie->date = NULL;
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
	//mov->mediaType = medType;
}

void setDate(MOVIE* mov, char* d){
	strcpy(mov->date, d);
	//mov->date = d;
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
			else {
				is_left = 1;
				current = current->left;
			}
 
        }
        if(is_left){																					//if it should be a left value
			prev->left = newMov;	//set the prev movie's left to the new movie
			setParent(prev->left, prev);
		} else {																						//if it should be a right value
			prev->right = newMov;	//set the prev movie's right to the new movie
			setParent(prev->right, prev);
		}
 
    }
    return root;
}

MOVIE* removeMovie(MOVIE *root, char* pTitle)
{
    if(root == NULL)
        return NULL;
 
    MOVIE *current;
    int r = strcmp(pTitle,root->primaryTitle);
    if( r < 0)
        root->left = removeMovie( root->left, pTitle);
    else if( r > 0 )
        root->right = removeMovie(root->right, pTitle);
    else
    {
        if (root->left == NULL)
        {
            current = root->right;
            free(root);
            root = current;
        }
        else if (root->right == NULL)
        {
            current = root->left;
            free(root);
            root = current;
        }
        else    //2 children
        {
            current = root->right;
            MOVIE *parent = NULL;
 
            while(current->left != NULL)
            {
                parent = current;
                current = current->left;
            }
            //setting root to current
			strcpy(root->tconst, current->tconst);
			//root->tconst = current->tconst;
			strcpy(root->titleType, current->titleType);
			//root->titleType = current->titleType;
			strcpy(root->primaryTitle, current->primaryTitle);
			//root->primaryTitle = current->primaryTitle;
			strcpy(root->originalTitle, current->originalTitle);
			//root->originalTitle = current->originalTitle;
			strcpy(root->isAdult, current->isAdult);
			//root->isAdult = current->isAdult;
			strcpy(root->startYear, current->startYear);
			//root->startYear = current->startYear;
			strcpy(root->endYear, current->endYear);
			//root->endYear = current->endYear;
			strcpy(root->runtimeMinutes, current->runtimeMinutes);
			//root->runtimeMinutes = current->runtimeMinutes;
			strcpy(root->genres, current->genres);
			//root->genres = current->genres;
			setMediaType(root, current->mediaType);
			setDate(root, current->date);
            if (parent != NULL)
                parent->left = removeMovie(parent->left, parent->left->primaryTitle);
            else
                root->right = removeMovie(root->right, root->right->primaryTitle);
        }
    }
    return root;
}

DA* findMovies(MOVIE *root, const char* pTitle){	//FIX: Need to make everything lowercase, if time, change to only search first word
	MOVIE* current = root;
	MOVIE* prev = NULL;
	DA* array = newDA();
	char inTitle[240];
	strcpy(inTitle, pTitle);
	int i;
	for(int i=0; i < strlen(inTitle); i++){
		inTitle[i] = tolower(inTitle[i]);
	}
	while(current != NULL){
		char compString[240];
		strcpy(compString, getPTitle(current));
		
		for(int i = 0; i < strlen(compString); i++){
			compString[i] = tolower(compString[i]);
		}
		
		char* check = strstr(compString/*current->primaryTitle*/, inTitle);
		if((check!=NULL) && (current->visited != 1)){	//if it contains the substring
			insertDA(array, sizeDA(array), current);		//add it to the dynamic array
		}
		current->visited = 1;
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

void printTreeForFile(MOVIE* root, FILE* f){		//preorder traversal
	if(root == NULL){
		return;
	}
	//center
	printMovie(root, f);
	printTreeForFile(root->left, f);	//left
	printTreeForFile(root->right, f);	//right
}

void dispose(MOVIE* root)
{
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

MOVIE* find(MOVIE *root, const char* pTitle){
	if(root == NULL)
        return NULL;
 
    int r;
    MOVIE* current = root;
    while(current != NULL)
    {
        r = strcmp(pTitle,current->primaryTitle);
        if(r < 0)
            current = current->left;
        else if(r > 0)
            current = current->right;
        else
            return current;
    }
    return current;
}
