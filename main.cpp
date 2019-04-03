//
//	Matthew Shaw
//	Movie Database
//
//



#include <iostream>
#include <cstdlib>
#include "MovieTree.hpp"
#include <fstream>

using namespace std;

enum CHOICE { FIND, RENT, PRINT, DELETE, COUNT, QUIT };

CHOICE menu()
{
	char selection;
	CHOICE result;
	cout << "======Main Menu======" << endl;
	cout << "1. Find a movie" << endl;
	cout << "2. Rent a movie" << endl;
	cout << "3. Print the inventory" << endl;
	cout << "4. Delete a movie" << endl;
	cout << "5. Count the movies" << endl;
	cout << "6. Quit" << endl;

	cin >> selection;
	switch( selection )
	{
		case '1':
			result = FIND;
			break;
		case '2':
			result = RENT;
			break;
		case '3':
			result = PRINT;
			break;
		case '4':
			result = DELETE;
			break;
		case '5':
			result = COUNT;
			break;
		case '6':
			result = QUIT;
			break;
		default:
			result = menu();
	}
	return (result);
}

int main (int argc, char* argv[]) 
{

	MovieTree tree;

	int ranking;
	string title;
	int releaseYear;
	int quantity;

	string titleWanted;


	string word;
	fstream wordStream;
	wordStream.open(argv[1]); // opens move list file

	while (getline(wordStream, word, ',')) // iterates through the file, adding all movies 
	{
		ranking = stoi(word);
		getline(wordStream, word, ',');
		title = word;
		getline(wordStream, word, ',');
		releaseYear = stoi(word);
		getline(wordStream, word, '\n');
		quantity = stoi(word);

		tree.addMovieNode(ranking, title, releaseYear, quantity);
	}

	CHOICE c;

	do
	{
		c = menu();
		switch( c )
		{
			case FIND:
				cout << "Enter title: " << endl;
				cin.ignore();
				getline(cin,titleWanted, '\n'); 
				tree.findMovie(titleWanted);
				break;
			case RENT:
				cout << "Enter title: " << endl;
				cin.ignore();
				getline(cin,titleWanted, '\n'); 
				tree.rentMovie(titleWanted);
				break;
			case PRINT:
				tree.printMovieInventory();
				break;
			case DELETE:
				cout << "Enter title: " << endl;
				cin.ignore();
				getline(cin,titleWanted, '\n');
				tree.deleteMovieNode(titleWanted);
				break;
			case COUNT:
				cout << "Tree contains: " << tree.countMovieNodes() << " movies." << endl;
				break;
			case QUIT:
				cout << "Goodbye!" << endl;
				c = QUIT;
		}

	} while (c != QUIT);


	wordStream.close();

	return 0;
}