#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "movieBST.h"
#include <string.h>
#include "da.h"
#include "movieBST.h"

typedef struct movie {	//struct definition
	char* tconst;              //tracker1
	char* titleType;           //tracker2
	char *primaryTitle;        //tracker3						//key
	char *originalTitle;       //tracker4
	char* isAdult;             //tracker5
	char* startYear;           //tracker6
	char* endYear;             //tracker7
	char* runtimeMinutes;      //tracker8
	char *genres;  		       //tracker9
	
	char* mediaType;			//set later by user in collection only
	char* date;					//set later by user in colleciton only
	
	MOVIE* left;
	MOVIE* right;
	MOVIE* parent;
}MOVIE;

MOVIE* newMovie(char* tID, char* type, char* pTitle, char* oTitle, char* adult, char* sYear, char* eYear, char* runTime, char* inGenres) {
    MOVIE *new_movie = (MOVIE*)malloc(sizeof(MOVIE));
	
    if(new_movie == NULL) {
        fprintf (stderr, "Something went wrong with malloc for new movie\n");
        exit(1);
    }
	char tempID[10];
	strcpy(tempID, tID);
	char tempType[6];
	strcpy(tempType, type);
	char tempPTitle[240];
	strcpy(tempPTitle, pTitle);
	char tempOTitle[240];
	strcpy(tempOTitle, oTitle);
	char tempAdult[2];
	strcpy(tempAdult, adult);
	char tempSYear[5];
	strcpy(tempSYear, sYear);
	char tempEYear[5];
	strcpy(tempEYear, eYear);
	char tempRuntime[5];
	strcpy(tempRuntime, runTime);
	char tempGenres[240];
	strcpy(tempGenres, inGenres);
	
	new_movie->tconst = tempID;
	new_movie->titleType = tempType;
	new_movie->primaryTitle = tempPTitle;
	new_movie->originalTitle = tempOTitle;
	new_movie->isAdult = tempAdult;
	new_movie->startYear = tempSYear;
	new_movie->endYear = tempEYear;
	new_movie->runtimeMinutes = tempRuntime;
	new_movie->genres = tempGenres;
	
    //set later as needed
	new_movie->left = NULL;
    new_movie->right = NULL;
	new_movie->parent = NULL;
	//set later by user in collection only
	new_movie->mediaType = NULL;
	new_movie->date = NULL;
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
	mov->mediaType = medType;
}

void setDate(MOVIE* mov, char* d){
	mov->date = d;
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
			r = strcmp(getPTitle(newMov),current->primaryTitle);													//compare the title passed to the function with the title of the current movie
            //TESTER
			printf("TESTING STRCMP r = %d when comparing pTitle: %s and current->primaryTitle: %s\n", r, getPTitle(newMov), current->primaryTitle);
			
			prev = current;																				//set the previous node to current
            if(r < 0) {																					//if the title passed is "less than" the current title
				is_left = 1;																			//mark that it should go left
                current = current->left;																//set the current value to the current value's left value
            } else if(r > 0) {																			//if the title passed is "greater than" the current title
				is_left = 0;																			//mark that it should go right
                current = current->right;																//set the current value to the current value's right value
            } 
			//TESTER
			else {
				char ans[2];
				while(ans!="y" && ans!="n"){
					printf("This movie already exists. Would you like to insert it again? (y or n)\n");
					scanf("%s", ans);
					printf("%s\n", ans);
					if(ans == "n" || ans == "N"){
						printf("Won't add this one.");
						return root;
					}
				}
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
			root->tconst = current->tconst;
			root->titleType = current->titleType;
			root->primaryTitle = current->primaryTitle;
			root->originalTitle = current->originalTitle;
			root->isAdult = current->isAdult;
			root->startYear = current->startYear;
			root->endYear = current->endYear;
			root->runtimeMinutes = current->runtimeMinutes;
			root->genres = current->genres;
            if (parent != NULL)
                parent->left = removeMovie(parent->left, parent->left->primaryTitle);
            else
                root->right = removeMovie(root->right, root->right->primaryTitle);
        }
    }
    return root;
}

DA* findMovies(MOVIE *root, const char* pTitle){															//if anything is broken, it's probably this
    MOVIE* current = root;
	MOVIE* prev = NULL;
	DA* array = newDA();
	while(current != NULL){
		if(current->left != NULL){
			prev = current;
			current = current->left;
		} else {	//if current has no left child
			//check for right child
			if(current->right != NULL){
				prev = current;
				current = current->right;
			} else {	//if current has no right child
				//check if current value is what we are looking for
				if(strstr(current->primaryTitle, pTitle) != NULL){	//if it contains the substring
					insertDA(array, sizeDA(array), current);		//add it to the dynamic array
				}
				current = prev;										//move to the parent node 
				prev = prev->parent;								//set prev to its parent
			}
		}
	}
	return array;
}

void printTree(MOVIE* root){		//inorder traversal
	if(root == NULL){
		return;
	}
	printTree(root->left);	//left
	printMovie(root);		//center
	printTree(root->right); //right
}

void printTreeForFile(MOVIE* root, FILE* f){		//preorder traversal
	if(root == NULL){
		return;
	}
	//center
    fprintf(f, "%s	", getID(root));
	fprintf(f, "%s	", getType(root));
	fprintf(f, "%s	", getPTitle(root));
	fprintf(f, "%s	", getOTitle(root));
	fprintf(f, "%s	", getAdult(root));
	fprintf(f, "%s	", getSYear(root));
	fprintf(f, "%s	", getEYear(root));
	fprintf(f, "%s	", getRuntime(root));
	fprintf(f, "%s	", getGenres(root));
	fprintf(f, "%s	", getMediaType(root));
	fprintf(f, "%s\n", getDate(root));
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

void printMovie(MOVIE* mov)
{
    if(mov != NULL){
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s", getID(mov), getType(mov), getPTitle(mov), getOTitle(mov), getAdult(mov), getSYear(mov), getEYear(mov), getRuntime(mov), getGenres(mov));
		if(getMediaType(mov) != NULL){
			printf("\t%s", getMediaType(mov));
		}
		if(getDate(mov) != NULL){
			printf("\t%s", getDate(mov));
		}
		printf("\n");
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
