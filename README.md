# CS201Project
# IMDB Movie Collection Database
A movie catalog with CRUD access using the IMDB Database

# Getting Started
1. Download the following files from the repository into one folder:
	da.c
	da.h
	main.c
	makefile
	movieBST.c
	movieBST.h
2. Enter the terminal on your computer and navigate to the folder where you saved the above files
3. Enter 'wget https://datasets.imdbws.com/title.basics.tsv.gz' to download the most updated version of the database
4. Go into file explorer, and right-click on the title.basics.tsv.gz file
5. Unzip that file (if you are on windows, you will have to use 7zip)
6. Navigate into that folder
7. Take the data file in there and move it to where you saved the above programs
8. Back in the terminal, enter 'grep "movie" data.tsv > movie_records

# Running the program
1. Open the terminal
	1a. If you are in Windows, you will need to navigate to the terminal for the Windows subsystem, by typing 'bash'
2. Navigate to the folder holding the programs
3. Enter 'collection'
4. Enter a user
	4a. If this user already exists:
		4a.1. If you are a returning user, enter 'y' for yes, verifying this is your file
		4a.2. If you are a new user, enter 'n' for no, and it will reprompt for a new username
5. Follow the prompts for what you want to do (additional instructions below)

NOTE: All of the following instructions assume you have completed the 'Getting Started' Steps

# Viewing Your Collection
1. Enter 'r'

# Adding a New Record
1. Enter 'c'
2. Enter the title you want to search for
3. Select the Movie
	3a. If the movie you want is shown above
		3a.1 Enter 'y'
		3a.2 Enter the number shown next to your selection
	3b. If the movie is not there
		3b.a Enter 'c' if you want to continue forward searching
		3b.b Enter 'b' if you want to go back a page in the search
		3b.c Enter 'e' if you wish to terminate the program
4. Choose the media type
	4a. If the movie is a dvd, enter 'v'
	4b. If the movie is a bluray, enter 'b'
	4c. If the movie is digital, enter 'd'
5. Confirm the media type
6. Enter the date you acquired the movie
7. Confirm the date
8. If you would like to do something else, enter 'y'; otherwise, enter 'n' to terminate

# Updating A Record
1. Enter 'u'
2. Enter the title you want to search for
3. Select the Movie
	3a. If the movie you want is shown above
		3a.1 Enter 'y'
		3a.2 Enter the number shown next to your selection
	3b. If the movie is not there
		3b.a Enter 'c' if you want to continue forward searching
		3b.b Enter 'b' if you want to go back a page in the search
		3b.c Enter 'e' if you wish to terminate the program
4. Select what you want to update
	4a. If you want to update only the media type, enter 'm'
	4b. If you want to update only the date, enter 'd'
	4c. If you want to update both, enter 'b'
5. Enter the info you are prompted for
6. Confirm your choices
7. If you would like to do something else, enter 'y'; otherwise, enter 'n' to terminate

# Delete a Record
1. Enter 'd'
2. Enter the title you want to search for
3. Select the Movie
	3a. If the movie you want is shown above
		3a.1 Enter 'y'
		3a.2 Enter the number shown next to your selection
	3b. If the movie is not there
		3b.a Enter 'c' if you want to continue forward searching
		3b.b Enter 'b' if you want to go back a page in the search
		3b.c Enter 'e' if you wish to terminate the program
4. If you would like to do something else, enter 'y'; otherwise, enter 'n' to terminate

