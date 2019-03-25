#include <stdio.h>
#include <stdlib.h>
#include "da.h"
#include "movieBST.h"
#include <string.h>
#include <ctype.h>

#include <unistd.h>

//Fix all the includes!!!!!!!!!!!!!!!!

//function declarations
MOVIE* promptForAction(MOVIE* dirRoot, MOVIE* colRoot);
MOVIE* runCreate(MOVIE* dirRoot, MOVIE* colRoot);
void runRetrieve(MOVIE* colRoot);
MOVIE* runUpdate(MOVIE* colRoot);
MOVIE* runDelete(MOVIE* colRoot);
char* promptForMediaType(char* type);
char* promptForDate(char* date);
MOVIE* findMovieInDB(MOVIE* dirRoot);
void displayFoundDBMovies(DA *foundMovies, int start, int end);
MOVIE* selectAMovie(DA *foundMovies, int start, int end);

void endSequence(MOVIE* dirRoot, MOVIE* colRoot, FILE* collection);


int main()
{
	//initializing variables
	char* tID;
	char* type;
	char* pTitle;
	char* oTitle;
	char* adult;
	char* sYear;
	char* eYear;
	char* runTime;
	char* inGenres;
	MOVIE* colRoot = NULL;																	//initializes a movie pointer that points to the root of the bst for the collection
	MOVIE* dirRoot = NULL;																	//initializes a movie pointer that points to the root of the bst for the directory
	FILE* collection;
	
	FILE *movieRecs = fopen("movie_recordsTEST.txt", "r");											//opens the imdb file
	if (movieRecs == NULL)																	//if it can"t open the file, crash the program
    {
        printf("Cannot open movie_records \n");
        exit(0);
    }
	//max number of characters is 216
	char line[216];
	while (fgets(line, 216, movieRecs)){									//read in a line (with max 216 characters) from movie_records and saves it to the char[] line
		//used strtok to separate and save all values from the file
		const char delim[] = "\t";
		char *token;
		token = strtok(line, delim);
		int tracker = 1;
		while(token != NULL){
			
			if(tracker == 1){
				tID = token;
			} else if (tracker == 2){
				type = token;
			} else if (tracker == 3){
				pTitle = token;
			} else if (tracker == 4){
				oTitle = token;
			} else if (tracker == 5){
				adult = token;
			} else if (tracker == 6){
				sYear = token;
			} else if(tracker == 7){
				eYear = token;
			} else if(tracker == 8){
				runTime = token;
			} else if(tracker == 9){
				inGenres = token;
			} else {
				printf("error");
				exit(0); 
			}
			token = strtok(NULL, delim);
			tracker++;
		}
		MOVIE* new_mov = newMovie(tID, type, pTitle, oTitle, adult, sYear, eYear, runTime, inGenres);
		dirRoot = insertMovie(dirRoot, new_mov);		//insert the movie into the BST
	}
	printTree(dirRoot);
	fclose(movieRecs);
	
	//finds a unique user's file
	char ans[] = "n";
	while((strcmp(ans, "n")==0)||(strcmp(ans, "N")==0)){
		printf("What is your username?\n");		//prompt for username
		char user[240];
		
		scanf("%s\n", user);						//reads in given userID
		printf("%s\n", user);
		char* fileName = strcat(user,".txt");	//saves the file name as the <userID>.log
		printf("%s\n", fileName);	 //TEST
		//opens/creates the collection
		//collection = fopen(fileName, "r+");
		//int result = access(fileName, F_OK);
		//printf("%d", result);
	}//REMOVE
		/*if(result != -1){													//if the file already exists
			printf("This user already exists. Is this you? (y or n)");			//verify this is the right user, if yes, read in the file, if no reprompt
			scanf("%s", ans);
			while((strcmp(ans, "y")!=0)&&(strcmp(ans, "Y")!=0)&&(strcmp(ans, "n")!=0)&&(strcmp(ans, "N")!=0)){
				printf("This user already exists. Is this you? (y or n)\n");
				scanf("%s", ans);
			}
			if((strcmp(ans, "n")==0)||(strcmp(ans, "N")==0)){		//reprompt if no (break the loop)
				break;
			}
			//reads in the collection that was already there
			collection = fopen(fileName, "r+");
			char line[216];
			while (fgets(line, 216, collection) != NULL){								//read in a line (with max 216 characters) from the collection and saves it to the char[] line
				//used strtok to separate and save all values from the file
				const char delim2[] = "	";
				char *token2;
				token2 = strtok(line, delim2);
				int tracker = 1;
				while(token2 != NULL){
					if(tracker == 1){
						tID = token2;
					} else if (tracker == 2){
						type = token2;
					} else if (tracker == 3){
						pTitle = token2;
					} else if (tracker == 4){
						oTitle = token2;
					} else if (tracker == 5){
						adult = token2;
					} else if (tracker == 6){
						sYear = token2;
					} else if(tracker == 7){
						eYear = token2;
					} else if(tracker == 8){
						runTime = token2;
					} else if(tracker == 9){
						inGenres = token2;
					} else {
						printf("error");
						exit(0); 
					}
					token2 = strtok(NULL, delim2);
					tracker++;
				}
				MOVIE* new_mov = newMovie(tID, type, pTitle, oTitle, adult, sYear, eYear, runTime, inGenres);
				colRoot = insertMovie(colRoot, new_mov);		//insert the movie into the BST
			}
		} else {																//if the file doesn"t already exist, create it																							//if the file doesn"t already exist, create one for writing
			strcpy(ans, "y");
			//ans = "y";																									//makes sure the while loop doesn"t run again
			fclose(collection);
			collection = fopen(fileName, "w+");
		}
		
	}
	colRoot = promptForAction(dirRoot, colRoot);
	endSequence(dirRoot, colRoot, collection);
	
	fclose(collection);*/
	
	return(0);
}

MOVIE* promptForAction(MOVIE* dirRoot, MOVIE* colRoot){
	char ans[2];
	printf("What would you like to do? VIEW YOUR COLLECTION (r), ADD A NEW RECORD (c), UPDATE A RECORD (u), DELETE A RECORD (d), or EXIT (e)\n");
	scanf("%s", ans);
	if((strcmp(ans, "c")==0)||(strcmp(ans, "C")==0)){
		runCreate(dirRoot, colRoot);
	} else if ((strcmp(ans, "r")==0)||(strcmp(ans, "R")==0)){
		runRetrieve(colRoot);
	} else if ((strcmp(ans, "u")==0)||(strcmp(ans, "U")==0)){
		runUpdate(colRoot);
	} else if ((strcmp(ans, "d")==0)||(strcmp(ans, "D")==0)){
		runDelete(colRoot);
	} else if ((strcmp(ans, "e")==0)||(strcmp(ans, "E")==0)){
		exit(0);
	} else {
		printf("Invalid Response. Please Try Again.\n");
		promptForAction(dirRoot, colRoot);
	}
	
	return colRoot;
}

MOVIE* runCreate(MOVIE* dirRoot, MOVIE* colRoot){
	MOVIE* orig = findMovieInDB(dirRoot);
	//get other info
	char* mediaType = promptForMediaType(mediaType);
	char* date = promptForDate(date);
	colRoot = insertMovie(colRoot, orig);
	setMediaType(find(colRoot, getPTitle(orig)), mediaType);
	setDate(find(colRoot, getPTitle(orig)), date);
	
	return colRoot;
}

void runRetrieve(MOVIE* colRoot){					//print out the whole collection
	printTree(colRoot);
}

MOVIE* runUpdate(MOVIE* colRoot){						//update the media type or the date
	MOVIE* orig = findMovieInDB(colRoot);
	printf("Update media type (m), date aquired (d), or both (b)?");
	char ans[2];
	char newMediaType[8];
	char newDate[10];
	scanf("%s", ans);
	if((strcmp(ans, "m")==0)||(strcmp(ans, "M")==0)){
		setMediaType(orig,promptForMediaType(newMediaType));
	} else if ((strcmp(ans, "d")==0)||(strcmp(ans, "D")==0)){
		setDate(orig, promptForDate(newDate));
	} else if ((strcmp(ans, "b")==0)||(strcmp(ans, "B")==0)){
		setMediaType(orig,promptForMediaType(newMediaType));
		setDate(orig, promptForDate(newDate));
	} else {
		printf("Invalid Response. Please Try Again.\n");
		runUpdate(colRoot);
	}
	
	return colRoot;
}

MOVIE* runDelete(MOVIE* colRoot){						//delete a record
	MOVIE* orig = findMovieInDB(colRoot);
	colRoot = removeMovie(colRoot, getPTitle(orig));
	return colRoot;
}

char* promptForMediaType(char* type){
	printf("What is the media type for this movie? DVD (v), Bluray (b), or Digital (d)\n");
	char ans[2];
	//char type[8];
	scanf("%s", ans);
	if((strcmp(ans, "v")==0)||(strcmp(ans, "V")==0)){
		strcpy(type, "DVD");
		//type = "DVD";
	} else if((strcmp(ans, "b")==0)||(strcmp(ans, "B")==0)){
		strcpy(type, "Bluray");
		//type = "Bluray";
	} else if((strcmp(ans, "d")==0)||(strcmp(ans, "D")==0)){
		strcpy(type, "Digital");
		//type = "Digital";
	} else {
		printf("Invalid Response. Try Again.\n");
		return promptForMediaType(type);
	}
	//confirm choice
	while((strcmp(ans, "y")!=0)&&(strcmp(ans, "Y")!=0)&&(strcmp(ans, "n")!=0)&&(strcmp(ans, "N")!=0)){
		printf("Is the movie a %s? (y or n)\n", type);
		scanf("%s", ans);
		if(ans == "n" || ans == "N"){
			return promptForMediaType(type);
		}
	}
	return type;
}

char* promptForDate(char* date){
	printf("When did you acquire this movie? (MM/DD/YY)\n");
	char ans[2];
	//char date[10];
	scanf("%s", ans);
	//confirm choice
	while((strcmp(ans, "y")!=0)&&(strcmp(ans, "Y")!=0)&&(strcmp(ans, "n")!=0)&&(strcmp(ans, "N")!=0)){
		printf("Did you aquire the movie on %s? (y or n)\n", date);
		scanf("%s", ans);
		if((strcmp(ans, "n")==0)||(strcmp(ans, "N")==0)){
			return promptForDate(date);
		}
	}
	return date;
}

MOVIE* findMovieInDB(MOVIE* dirRoot){
	//prompt for title
	char title[240];
	printf("What title would you like to search for?\n");
	scanf("%s", title);
	DA *foundMovies = findMovies(dirRoot, title);
	//display first 10 options with that title with numbers 1-10 next to them
	displayFoundDBMovies(foundMovies, 0, 10);
	//prompt for number of chosen movie (1-10), if they want to continue the search, enter (c), if they want to go back (b)
	return selectAMovie(foundMovies, 0, 10);
}

void displayFoundDBMovies(DA *foundMovies, int start, int end){
	int i = start;
	int max = end;
	if(start >= sizeDA(foundMovies)){
		printf("There are no more movies to show.\n");
		return;
	}
	if(max > sizeDA(foundMovies)){
		max = sizeDA(foundMovies);
	}
	for(i = start; i < max; i++){
		printf("%d. ", i+1);
		printMovie(getDA(foundMovies, i));
		printf("\n");
	}
}

MOVIE* selectAMovie(DA *foundMovies, int start, int end){
	//prompt for number of chosen movie (1-10), if they want to continue the search, enter (c), if they want to go back (b)
	printf("What is the number of the movie you wish to add? If you wish to continue the search, enter 'c'. If you want to go back to the previous 10 search values, enter 'b'.\n");
	char ans[3];
	scanf("%s", ans);
	if((strcmp(ans, "c")==0)||(strcmp(ans, "C")==0)){
		start+=10;
		end+=10;
		displayFoundDBMovies(foundMovies, start, end);
	} else if ((strcmp(ans, "b")==0)||(strcmp(ans, "B")==0)){
		start-=10;
		end-=10;
		displayFoundDBMovies(foundMovies, start, end);
	} else if (isdigit(ans)){
		if((isdigit(ans)>=start)&&(isdigit(ans)<=end)){
			//valid number
			MOVIE* chosen = getDA(foundMovies, isdigit(ans));
			//confirm
			printf("Is this the movie you want add? (y or n)\n");
			printMovie(chosen);
			printf("\n");
			char* conf = "s";
			while((conf != "y" && conf!="Y")&&(conf != "n" && conf != "N")){
				scanf("%s", conf);
				if(conf == "y" || conf=="Y"){
					return chosen;
				} else if(conf == "n" || conf=="N"){
					return selectAMovie(foundMovies, start, end);
				}
			}
		} else {
			//invalid number
			printf("Invalid number. Please try again.\n");
		}
	} else {
		printf("Invalid entry. Please try again.\n");
	}
	return selectAMovie(foundMovies, start, end);
}

void endSequence(MOVIE* dirRoot, MOVIE* colRoot, FILE* collection){
	char ans[] = "y";
	while((strcmp(ans, "n")!=0)&&(strcmp(ans, "n")!=0)){
		printf("Would you like to do anything else?");
		scanf("%s", ans);
		if ((strcmp(ans, "y")==0)||(strcmp(ans, "Y")==0)){
			colRoot = promptForAction(dirRoot, colRoot);
		}
	}
	printTreeForFile(colRoot, collection);
}
