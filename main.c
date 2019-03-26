#include <stdio.h>
#include <stdlib.h>
#include "da.h"
#include "movieBST.h"
#include <string.h>
#include <ctype.h>

#include <unistd.h>


//function declarations
MOVIE* promptForAction(MOVIE* dirRoot, MOVIE* colRoot, FILE *f);
MOVIE* runCreate(MOVIE* dirRoot, MOVIE* colRoot, FILE *f);
void runRetrieve(MOVIE* colRoot, FILE *f);
MOVIE* runUpdate(MOVIE* colRoot, FILE *f);
MOVIE* runDelete(MOVIE* colRoot, FILE *f);
char* promptForMediaType(char* type);
char* promptForDate(char* date);
MOVIE* findMovieInDB(MOVIE* dirRoot, FILE *f);
void displayFoundDBMovies(DA *foundMovies, int start, int end, FILE *f);
MOVIE* selectAMovie(DA *foundMovies, int start, int end, FILE *f);

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
	char* medType;
	char* date;
	MOVIE* colRoot = NULL;																	//initializes a movie pointer that points to the root of the bst for the collection
	MOVIE* dirRoot = NULL;																	//initializes a movie pointer that points to the root of the bst for the directory
	FILE* collection;
	
	int c;
	
	//reads in the movies from the database file
	FILE *movieRecs = fopen("movie_records", "r");											//opens the imdb file
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
	fclose(movieRecs);
	
	//finds a unique user's file
	char ans[] = "n";
	while((strcmp(ans, "n")==0)||(strcmp(ans, "N")==0)){
		printf("What is your username?\n");		//prompt for username
		char user[240];
		
		scanf("%239s", user);						//reads in given userID
		while ((c = fgetc(stdin)) != '\n' && c != EOF); // Flush stdin
		char* fileName = strcat(user,".log");	//saves the file name as the <userID>.log
		//opens/creates the collection
		int result = access(fileName, F_OK);
		if(result != -1){													//if the file already exists
			printf("This user already exists. Is this you? (y or n)");			//verify this is the right user, if yes, read in the file, if no reprompt
			scanf("%1s", ans);
			while ((c = fgetc(stdin)) != '\n' && c != EOF); // Flush stdin
			while((strcmp(ans, "y")!=0)&&(strcmp(ans, "Y")!=0)&&(strcmp(ans, "n")!=0)&&(strcmp(ans, "N")!=0)){
				printf("This user already exists. Is this you? (y or n)\n");
				scanf("%1s", ans);
				while ((c = fgetc(stdin)) != '\n' && c != EOF); // Flush stdin
			}
			if((strcmp(ans, "y")==0)||(strcmp(ans, "Y")==0)){		//if yes, read in the file already there
				//reads in the collection that was already there
				collection = fopen(fileName, "r");
				char line[216];		//the longest line in the imdb file is 202 characters, 216 gives a buffer
				while (fgets(line, 216, collection) != NULL){	//read in a line (with max 216 characters) from the collection and saves it to the char[] line
					//used strtok to separate and save all values from the file
					const char delim2[] = "\t";
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
					char line2[216];
					//read second line and delineate for type and genre
					if(fgets(line2, 216, collection) != NULL){
						char *token3;
						token3 = strtok(line2, delim2);
						int tracker2 = 1;
						while(token3 != NULL){
							if(tracker2 == 1){
								medType = token3;
							} else if (tracker2 == 2){
								date = token3;
								if( date[strlen(date)-1] == '\n' )//newline remove from date
									date[strlen(date)-1] = 0;
							} else {
								printf("Something went wrong\n");
							}
							token3 = strtok(NULL, delim2);
							tracker2++;
						}
						
					}
					//create a new movie with those details
					MOVIE* new_mov = newMovie(tID, type, pTitle, oTitle, adult, sYear, eYear, runTime, inGenres);
					//insert it into the collection
					colRoot = insertMovie(colRoot, new_mov);
					//set media type and date
					setMediaType(find(colRoot, getPTitle(new_mov)), medType);
					setDate(find(colRoot, getPTitle(new_mov)), date);
				}
				//close the collection that is only read
				fclose(collection);
			}
		} else {																//if the file doesn't already exist																					//if the file doesn"t already exist, create one for writing
			//get out of the loop
			strcpy(ans, "y");
			
		}
		//open the file with write+ permissions, so it will truncate the original to 0
		collection = fopen(fileName, "w");
	}
	
	colRoot = promptForAction(dirRoot, colRoot, collection);
	endSequence(dirRoot, colRoot, collection);
	//close the file
	fclose(collection);
	//free the trees
	dispose(dirRoot);
	dispose(colRoot);
	
	return(0);
}

MOVIE* promptForAction(MOVIE* dirRoot, MOVIE* colRoot, FILE *f){												//prompt for what they want to do
	int c;
	char ans[2];
	printf("What would you like to do? VIEW YOUR COLLECTION (r), ADD A NEW RECORD (c), UPDATE A RECORD (u), or DELETE A RECORD (d)\n");
	scanf("%1s", ans);
	//while ((c = fgetc(stdin)) != '\n' && c != EOF); // Flush stdin//WHY??????????????
	//run the function for what they want
	if((strcmp(ans, "c")==0)||(strcmp(ans, "C")==0)){
		colRoot = runCreate(dirRoot, colRoot, f);
	} else if ((strcmp(ans, "r")==0)||(strcmp(ans, "R")==0)){
		runRetrieve(colRoot, f);
	} else if ((strcmp(ans, "u")==0)||(strcmp(ans, "U")==0)){
		colRoot = runUpdate(colRoot, f);
	} else if ((strcmp(ans, "d")==0)||(strcmp(ans, "D")==0)){
		colRoot = runDelete(colRoot, f);
	} else {																									//reprompt until valid input
		printf("Invalid Response. Please Try Again.\n");
		promptForAction(dirRoot, colRoot, f);
	}
	
	return colRoot;
}

//create a new record to add to the collection
MOVIE* runCreate(MOVIE* dirRoot, MOVIE* colRoot, FILE *f){
	//find which movie they want to add
	MOVIE* orig = findMovieInDB(dirRoot, f);
	//get other info
	char mediaType[8];
	strcpy(mediaType, promptForMediaType(mediaType));
	char date[10];
	strcpy(date, promptForDate(date));
	//create a new movie to insert with the details above
	MOVIE* insMov = newMovie(getID(orig), getType(orig), getPTitle(orig), getOTitle(orig), getAdult(orig), getSYear(orig), getEYear(orig), getRuntime(orig), getGenres(orig));
	//insert the movie into the collection
	colRoot = insertMovie(colRoot, insMov);
	//set media type and date
	setMediaType(find(colRoot, getPTitle(insMov)), mediaType);
	setDate(find(colRoot, getPTitle(insMov)), date);
	
	return colRoot;
}

void runRetrieve(MOVIE* colRoot, FILE *f){					//print out the whole collection
	printTree(colRoot, stdout);
}

MOVIE* runUpdate(MOVIE* colRoot, FILE *f){						//update the media type or the date
	int c;
	//find the movie they want to update
	MOVIE* orig = findMovieInDB(colRoot, f);
	printf("Update media type (m), date aquired (d), or both (b)?");
	char ans[2];
	char newMediaType[8];
	char newDate[10];
	scanf("%1s", ans);
	while ((c = fgetc(stdin)) != '\n' && c != EOF); // Flush stdin
	if((strcmp(ans, "m")==0)||(strcmp(ans, "M")==0)){
		setMediaType(orig,promptForMediaType(newMediaType));
	} else if ((strcmp(ans, "d")==0)||(strcmp(ans, "D")==0)){
		setDate(orig, promptForDate(newDate));
	} else if ((strcmp(ans, "b")==0)||(strcmp(ans, "B")==0)){
		setMediaType(orig,promptForMediaType(newMediaType));
		setDate(orig, promptForDate(newDate));
	} else {
		printf("Invalid Response. Please Try Again.\n");
		runUpdate(colRoot, f);
	}
	
	return colRoot;
}

MOVIE* runDelete(MOVIE* colRoot, FILE *f){						//delete a record
	//find the movie they want to delete
	MOVIE* orig = findMovieInDB(colRoot, f);
	//remove that movie
	colRoot = removeMovie(colRoot, getPTitle(orig));
	return colRoot;
}

//find out what the media type is
char* promptForMediaType(char* type){
	int c;
	printf("What is the media type for this movie? DVD (v), Bluray (b), or Digital (d)\n");
	char ans[2];
	scanf("%1s", ans);
	while ((c = fgetc(stdin)) != '\n' && c != EOF); // Flush stdin
	if((strcmp(ans, "v")==0)||(strcmp(ans, "V")==0)){
		strcpy(type, "DVD");
	} else if((strcmp(ans, "b")==0)||(strcmp(ans, "B")==0)){
		strcpy(type, "Bluray");
	} else if((strcmp(ans, "d")==0)||(strcmp(ans, "D")==0)){
		strcpy(type, "Digital");
	} else {
		printf("Invalid Response. Try Again.\n");
		return promptForMediaType(type);
	}
	return type;
}
//find out what the date is
char* promptForDate(char* date){
	int c;
	printf("When did you acquire this movie? (MM/DD/YY)\n");
	char ans[2];
	char selection[10];
	scanf("%8s", selection);
	while ((c = fgetc(stdin)) != '\n' && c != EOF); // Flush stdin
	strcpy(date, selection);
	return date;
}

//runs prompts to search for the movie in the passed database
MOVIE* findMovieInDB(MOVIE* dirRoot, FILE *f){
	//prompt for title
	char title[240];
	printf("What title would you like to search for?\n");
	int c;
	while ((c = getchar()) != '\n' && c != EOF);//gets rid of any trailing newline characters
	fgets(title, 240, stdin);
	if( title[strlen(title)-1] == '\n' )//newline remove from title
		title[strlen(title)-1] = 0;
	DA *foundMovies = findMovies(dirRoot, title);//saves all movies that contain the search phrase
	//display first 10 options with that title with numbers 1-10 next to them
	displayFoundDBMovies(foundMovies, 0, 10, f);
	//prompt for number of chosen movie (1-10), if they want to continue the search, enter (c), if they want to go back (b)
	return selectAMovie(foundMovies, 0, 10, f);
}

//display the found movies from start to end 
void displayFoundDBMovies(DA *foundMovies, int start, int end, FILE *f){
	int i = start;
	int max = end;
	if(start >= sizeDA(foundMovies)){
		printf("There are no more movies to show.\n");
		return;
	}
	if(max > sizeDA(foundMovies)){
		//if the max is bigger than the array given, don't let it go outside
		max = sizeDA(foundMovies);
	}
	//print the movies in that range
	for(i = start; i < max; i++){
		printf("%d. ", i+1);
		printMovie(getDA(foundMovies, i), stdout);
		printf("\n");
	}
}

//pick a movie from the display
MOVIE* selectAMovie(DA *foundMovies, int start, int end, FILE *f){
	int c;
	//prompt for number of chosen movie (1-10), if they want to continue the search, enter (c), if they want to go back (b)
	printf("Is the movie you want there? If it is, enter 'y'. If you wish to continue the search, enter 'c'. If you want to go back to the previous 10 search values, enter 'b'.\n");
	char ans[2];
	scanf("%1s", ans);
	while ((c = fgetc(stdin)) != '\n' && c != EOF); // Flush stdin
	if((strcmp(ans, "c")==0)||(strcmp(ans, "C")==0)){
		//show the next ten movies
		start+=10;
		end+=10;
		displayFoundDBMovies(foundMovies, start, end, f);
	} else if ((strcmp(ans, "b")==0)||(strcmp(ans, "B")==0)){
		//show the previous ten movies
		start-=10;
		end-=10;
		displayFoundDBMovies(foundMovies, start, end, f);
	} else if ((strcmp(ans, "y")==0)||(strcmp(ans, "Y")==0)){
		//if the movie is there, pick it
		printf("What is the number of the movie you wish to select?\n");
		int index;
		scanf("%d", &index);
		index -= 1;
		if(index>=start && index<=end){
			//valid number
			MOVIE* chosen = getDA(foundMovies, index);
			return chosen;
		} else {
			//invalid number
			printf("Invalid number. Please try again.\n");
		}
	} else {
		printf("Invalid entry. Please try again.\n");
	}
	return selectAMovie(foundMovies, start, end, f);
}

//runs after each action
void endSequence(MOVIE* dirRoot, MOVIE* colRoot, FILE* collection){
	int c;
	char ans[] = "y";
	while((strcmp(ans, "n")!=0)&&(strcmp(ans, "N")!=0)){
		printf("Would you like to do anything else?\n");
		scanf("%1s", ans);
		while ((c = fgetc(stdin)) != '\n' && c != EOF); // Flush stdin
		if ((strcmp(ans, "y")==0)||(strcmp(ans, "Y")==0)){
			colRoot = promptForAction(dirRoot, colRoot, collection);
		}
	}
	//prints final tree to the file when finished
	printTreeForFile(colRoot, collection);
}