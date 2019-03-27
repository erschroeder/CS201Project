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
2. Open the terminal on your computer
	2a. If you are in Windows, you will need to navigate to the terminal for the Windows subsystem, by typing 'bash'
		2a.a If you don't have the Linux Subsystem installed
			2a.a.1 Open Powershell as an Administrator
			2a.a.2 Run "Enable-WindowsOptionalFeature -Online -FeatureName Microsoft-Windows-Subsystem-Linux"
			2a.a.3 Restart when prompted
3. Navigate to the folder where you saved the above files
4. Enter 'wget https://datasets.imdbws.com/title.basics.tsv.gz' to download the most updated version of the database
5. Go into file explorer, and right-click on the title.basics.tsv.gz file
6. Unzip that file (if you are on windows, you will have to use 7zip)
7. Navigate into that folder
8. Take the data file in there and move it to where you saved the above programs
9. Back in the terminal, enter 'grep "movie" data.tsv > movie_records

# Running the program
1. Open the terminal
	1a. If you are in Windows, you will need to navigate to the terminal for the Windows subsystem, by typing 'bash'
		1a.a If you don't have the Linux Subsystem installed
			1a.a.1 Open Powershell as an Administrator
			1a.a.2 Run "Enable-WindowsOptionalFeature -Online -FeatureName Microsoft-Windows-Subsystem-Linux"
			1a.a.3 Restart when prompted
2. Navigate to the folder holding the programs
3. Enter 'make'
4. Enter 'collection'
5. Enter a user
	5a. If this user already exists:
		5a.1. If you are a returning user, enter 'y' for yes, verifying this is your file
		5a.2. If you are a new user, enter 'n' for no, and it will reprompt for a new username
6. Follow the prompts for what you want to do (additional instructions below)

NOTE: All of the following instructions assume you have completed the 'Getting Started' Steps

NOTE 2: If you terminate the program without completing the started tasks, the user file will be lost.

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

# Tutorial Links
Getting Started and Basic Usage: https://youtu.be/uTz6ZoQ__18
Returning User Basic Usage: https://youtu.be/dzor7Kam92g
