## Binary Search Trees and Linked Lists

### Description
This program simulates a movie rental database using a binary search tree for the first letter of the movie that points to a linked list that hold the movies in alphbetical order.

It has the following functions:
```
======Main Menu======
1. Find a movie
2. Rent a movie
3. Print the inventory
4. Delete a movie
5. Count the movies
6. Quit
```
1. Find a movie - searches for a movie based on user input
	* case-sensitive
	* if movie exists in database, it returns:
		* IMDB ranking
    	* Title of movie
    	* Year the movie came out
    	* Quantity available for rent
2. Rent a movie - reduces movie quantity by 1
	* if renting movie reduces quantity to zero, the movie is removed from the database
3. Print the inventory - prints an alphabetical list of movies in database
4. Delete a movie - deletes a movie from the database
	* if the movie is the last of it first letter list, it's BST letter node is deleted and the BST is restructured
5. Count the movies - counts how many unique movies are in the database
6. Quit - quits program
	* deletes all nodes in LL and BST before quitting


### File Descriptions

* main.cpp - this is the main file
* MovieTree.hpp - header file with:
	* MovieTree class
	* MovieNodeLL struct
	* MovieNodeBST struct
* MovieTree.cpp - implementation file of MovieTree class
* readme.md - this is what you are reading now

### Build Instructions

This program was written in Sublime Text on MacOs, and was compiled and run in the terminal. Please use the following command to build:

```
g++ -std=c++11 MovieTree.cpp main.cpp -o MovieDatabase
```

The when running the program, please include a *.txt file as an argument at the command line:

```
./<filename> <text file to read>
```

```
./MovieDatabase MovieList.txt
```

### Miscellaneous

Enjoy!
