#ifndef __COLLECTION_INCLUDED__
    #define __COLLECTION_INCLUDED__

	#include <stdlib.h>
	#include <assert.h>
	#include "movieBST.h"
	#include <string.h>
	#include "da.h"
	#include "movieBST.h"
	
	typedef struct movie MOVIE;
	MOVIE* newMovie(char* tID, char* type, char* pTitle, char* oTitle, char* adult, char* sYear, char* eYear, char* runTime, char* inGenres);
	char* getID(MOVIE* mov);
	char* getType(MOVIE* mov);
	char* getPTitle(MOVIE* mov);
	char* getOTitle(MOVIE* mov);
	char* getAdult(MOVIE* mov);
	char* getSYear(MOVIE* mov);
	char* getEYear(MOVIE* mov);
	char* getRuntime(MOVIE* mov);
	char* getGenres(MOVIE* mov);
	char* getMediaType(MOVIE* mov);
	char* getDate(MOVIE* mov);
	void setParent(MOVIE* mov, MOVIE* par);
	void setMediaType(MOVIE* mov, char* medType);
	void setDate(MOVIE* mov, char* d);
	MOVIE* insertMovie(MOVIE *root, MOVIE *newMov/*char* tID, char* type, char* pTitle, char* oTitle, char* adult, char* sYear, char* eYear, char* runTime, char* inGenres*/);
	MOVIE* removeMovie(MOVIE *root, char* pTitle);
	DA* findMovies(MOVIE *root, const char* pTitle);
	void printTree(MOVIE* root);
	void dispose(MOVIE* root);
	void printMovie(MOVIE* mov);
	MOVIE* find(MOVIE *root, const char* pTitle);
	void printTreeForFile(MOVIE* root, FILE* f);

    
#endif