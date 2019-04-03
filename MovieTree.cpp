//
// Matthew Shaw
// Assignment 3
//
//
//
//


#include "MovieTree.hpp"
#include <iostream>

using namespace std;


MovieTree::MovieTree()
{
	root = NULL;
}
MovieTree::~MovieTree()
{
	DeleteAll(root);
}

void MovieTree::printMovieInventory()
{
	printMovieInventory(root);
}

int MovieTree::countMovieNodes()
{
	int count = 0;

	countMovieNodes(root, &count);

	return count;
}

void MovieTree::deleteMovieNode(std::string title)
{
	char first_letter = title[0];

	// 1. Finding the Tree node that the movie should be in
	MovieNodeBST* tmpbst = searchBST(root, title);

	if (tmpbst == NULL) // if node doesn't exist, return
	{
		cout << "Movie not found\n";
		return;
	}


	// 2. Find the linked list node of the movie
	MovieNodeLL* tmpll = searchLL(tmpbst->head, title);

	if (tmpll == NULL) // if the movie doesn't exit, return
	{
		cout << "Movie not found.\n";
		return;
	}

	MovieNodeLL* tmpllprev = tmpbst->head; // sets up a new pointer to point at node prior to one being deleted

	while ((tmpllprev->next !=  tmpll) && (tmpllprev->next != NULL)) // moves pointer through linked list until it is right before tmpll
	{
		tmpllprev = tmpllprev->next;
	}

	if ((tmpll == tmpbst->head) && (tmpll->next == NULL)) // Deleting only remaining node in LL
	{
		tmpbst->head = NULL;
		delete tmpll;
	}
	else if ((tmpll == tmpbst->head) && (tmpll->next != NULL)) // Deleting the first LL node
	{
		tmpbst->head = tmpll->next;
		delete tmpll;
	}
	else // deleting LL node other than first node
	{
		tmpllprev->next = tmpll->next;
		delete tmpll;
	}

	// 3. Check if need to delete tree node
	if (tmpbst->head != NULL)
	{
		return;
	}
		
	// Perform delete, one of three cases
	if (tmpbst->leftChild == tmpbst->rightChild) // no children
	{
		if (tmpbst->parent != NULL) // not the root
		{
			if (tmpbst->letter < tmpbst->parent->letter)
			{
				tmpbst->parent->leftChild = NULL;
			} 
			else
			{
				tmpbst->parent->rightChild = NULL;
			}
			delete tmpbst;
			return;
		}
		else
		{
			delete tmpbst;
			root = NULL;
			return;
		}
	}
	else if ((tmpbst->leftChild != NULL) != (tmpbst->rightChild != NULL)) // one child
	{
		if (tmpbst->parent != NULL) // not the root
		{
			if (tmpbst->letter < tmpbst->parent->letter) // we are left of the parent
			{
				if (tmpbst->leftChild != NULL) // which child do we have?
				{
					tmpbst->parent->leftChild = tmpbst->leftChild;
					tmpbst->leftChild->parent = tmpbst->parent;
				}
				else
				{
					tmpbst->parent->leftChild = tmpbst->rightChild;
					tmpbst->rightChild->parent = tmpbst->parent;
				}
			}
			else // we are right of the parent
			{
				if (tmpbst->leftChild != NULL) // which child do we have?
				{
					tmpbst->parent->rightChild = tmpbst->leftChild;
					tmpbst->leftChild->parent = tmpbst->parent;
				}
				else
				{
					tmpbst->parent->rightChild = tmpbst->rightChild;
					tmpbst->rightChild->parent = tmpbst->parent;
				}
			}
			delete tmpbst;
			return;
		}
		else // node to be deleted is root
		{
			if (tmpbst->rightChild != NULL)
			{
				tmpbst->rightChild->parent = NULL;
				root = tmpbst->rightChild;
			}
			else
			{
				tmpbst->leftChild->parent = NULL;
				root = tmpbst->leftChild;
			}
			delete tmpbst;
			return;
		}

	}
	else // two children
	{
		MovieNodeBST* rightMin = treeMinimum(tmpbst->rightChild); 
		if (tmpbst->parent != NULL) // not the root
		{
			// update right child pointer 
			if (rightMin->letter != tmpbst->rightChild->letter)
			{
				rightMin->rightChild = tmpbst->rightChild;
				tmpbst->rightChild->parent = rightMin;
				rightMin->parent->leftChild = NULL;
			}
			
			// update parent pointers
			rightMin->parent = tmpbst->parent;
			if (tmpbst->letter < tmpbst->parent->letter) // we are left of parent
			{
				tmpbst->parent->leftChild = rightMin;
			}
			else // to the right of parent
			{
				tmpbst->parent->rightChild = rightMin;
			}

			// update left child pointer (referring to the tmp)
			if (tmpbst->leftChild != NULL)
			{
				rightMin->leftChild = tmpbst->leftChild;
				tmpbst->leftChild->parent = rightMin;
			}

		delete tmpbst;
		return;
		}
		else // node to be deleted is root
		{
			if (rightMin == tmpbst->rightChild) // rightMin is right child
			{
				root = rightMin;
				rightMin->parent = NULL;
				tmpbst->leftChild->parent = rightMin;
				rightMin->leftChild = tmpbst->leftChild;
			}
			else
			{
				root = rightMin;
				if (rightMin->rightChild != NULL) // rightMin has a child
				{
					rightMin->rightChild->parent = rightMin->parent;
				}
				rightMin->parent->leftChild = rightMin->rightChild;
				rightMin->parent = NULL;
				rightMin->leftChild = tmpbst->leftChild;
				if (tmpbst->leftChild != NULL)
				{
					tmpbst->leftChild->parent = rightMin;
				}
				rightMin->rightChild = tmpbst->rightChild;
				if (tmpbst->rightChild != NULL)
				{
					tmpbst->rightChild->parent = rightMin;
				}
			}

			delete tmpbst;
			return;
		}
	}
	

}

void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity)
{
	char first_letter = title[0];

	MovieNodeLL* newNode = new MovieNodeLL(ranking, title, releaseYear, quantity);

	MovieNodeBST* tmpbst = root;
	MovieNodeBST* bstparent = tmpbst;

	while (tmpbst != NULL) // traverses tree to find node with same first letter
	{
		bstparent = tmpbst;
		if (first_letter < tmpbst->letter)
		{
			tmpbst = tmpbst->leftChild;
		}
		else if (first_letter > tmpbst->letter)
		{
			tmpbst = tmpbst->rightChild;
		}
		else
		{
			tmpbst = NULL;
		}
	}

	if (bstparent == NULL) // inserting at root of tree
	{
		MovieNodeBST* tmp =  new MovieNodeBST(first_letter);
		root = tmp;
		tmp->parent = bstparent;
		root->head = newNode;
		return;
	}

	
	MovieNodeLL* tmpll = bstparent->head;
	MovieNodeLL* prevll = tmpll;


	if (first_letter == bstparent->letter) // if LL already exists with first letter
	{
		if (tmpll->next == NULL) // inserting at head
		{
			if (newNode->title < tmpll->title)
			{
				newNode->next = tmpll;
				bstparent->head = newNode;
				return;
			}
			else
			{
				tmpll->next = newNode;
				return;
			}
		}

		while ((newNode->title > tmpll->title) && (tmpll->next != NULL)) // searching for where to insert linked list node
		{
			prevll = tmpll;
			tmpll = tmpll->next;
		}

		if (tmpll == bstparent->head) // inserting at head
		{
			if (newNode->title < tmpll->title)
			{
				newNode->next = tmpll;
				bstparent->head = newNode;
				return;
			}
			else
			{
				newNode->next = tmpll->next;
				tmpll->next = newNode;
				return;
			}
		}

		if ((tmpll->next == NULL) && (newNode->title > tmpll->title)) // inserting at tail
		{
			tmpll->next = newNode;
			return;
		}

		else // inserting in middle
		{
			newNode->next = tmpll;
			prevll->next = newNode;
			return;
		}
	}
	else // no LL exist for first letter. so create new BST node and insert into tree
	{
		MovieNodeBST* tmp =  new MovieNodeBST(first_letter);
		if (first_letter < bstparent->letter)
		{
			bstparent->leftChild = tmp;
			tmp->parent = bstparent;
			tmp->head = newNode;
			return;
		}
		else if (first_letter > bstparent->letter)
		{
			bstparent->rightChild = tmp;
			tmp->parent = bstparent;
			tmp->head = newNode;
			return;
		}
	}

}

void MovieTree::findMovie(std::string title)
{
	MovieNodeBST* tmpbst = searchBST(root, title); // finds correct BST node
	if (tmpbst == NULL)
	{
		cout << "Movie not found.\n";
		return;
	}
	MovieNodeLL* tmpll = searchLL(tmpbst->head, title); // finds correct LL node
	if (tmpll == NULL)
	{
		cout << "Movie not found.\n";
		return;
	}

	cout << "Movie Info:" << endl;
	cout << "===========" << endl;
	cout << "Ranking:" << tmpll->ranking << endl;
	cout << "Title:" << tmpll->title << endl;
	cout << "Year:" << tmpll->year << endl;
	cout << "Quantity:" << tmpll->quantity << endl;
}

void MovieTree::rentMovie(std::string title)
{
	MovieNodeBST* tmpbst = searchBST(root, title); // finds correct BST node
	if (tmpbst == NULL)
	{
		cout << "Movie not found.\n";
		return;
	}
	MovieNodeLL* tmpll = searchLL(tmpbst->head, title); // finds correct LL node
	if (tmpll == NULL)
	{
		cout << "Movie not found.\n";
		return;
	}

	tmpll->quantity -= 1; // reduces quantity by 1

	cout << "Movie has been rented." << endl;
	cout << "Movie Info:" << endl;
	cout << "===========" << endl;
	cout << "Ranking:" << tmpll->ranking << endl;
	cout << "Title:" << tmpll->title << endl;
	cout << "Year:" << tmpll->year << endl;
	cout << "Quantity:" << tmpll->quantity << endl;

	if (tmpll->quantity == 0) // if quantity is zero, delete LL node
	{
		deleteMovieNode(title);
	}


}

void MovieTree::DeleteAll(MovieNodeBST * node) //use this for the post-order traversal deletion of the tree
{
	if (node == NULL)
	{
		return;
	}

	// Go left;
	DeleteAll(node->leftChild);

	// Go right;
	DeleteAll(node->rightChild);

	// Delete linked list
	MovieNodeLL* tmp = node->head;
	MovieNodeLL* tmp_next = tmp;
	while (tmp != NULL)
	{
		cout << "Deleting: " << tmp->title << endl;
		tmp_next = tmp->next;
		delete tmp;
		tmp = tmp->next;
	}

	// Delete tree node
	delete node;


}

void MovieTree::printMovieInventory(MovieNodeBST * node)
{
	if (node->leftChild != NULL)
	{
		printMovieInventory(node->leftChild);
	}

	MovieNodeLL* tmp = node->head;
	while (tmp != NULL)
	{
		cout << "Movie: " << tmp->title << " " << tmp->quantity << endl;
		tmp = tmp->next;
	}

	if (node->rightChild != NULL)
	{
		printMovieInventory(node->rightChild);
	}
}

void MovieTree::countMovieNodes(MovieNodeBST *node, int *c)
{
	if (node->leftChild != NULL)
	{
		countMovieNodes(node->leftChild, c);
	}

	MovieNodeLL* tmp = node->head;

	while(tmp != NULL) // counts each node in LL
	{
		(*c) += 1;
		tmp = tmp->next;
	}

	if (node->rightChild != NULL)
	{
		countMovieNodes(node->rightChild, c);
	}

}

MovieNodeBST* MovieTree::searchBST(MovieNodeBST *node, std::string title) //use this recursive function to find a pointer to a node in the BST, given a MOVIE TITLE
{
	char first_letter = title[0];

	if (node != NULL)
	{
		if (node->letter == first_letter)
		{
			return node;
		}
		else if (node->letter > first_letter)
		{
			return searchBST(node->leftChild, title);
		}
		else
		{
			return searchBST(node->rightChild, title);
		}
	}
	else
	{
	return NULL;
	}
}

MovieNodeLL* MovieTree::searchLL(MovieNodeLL* head, std::string title) //use this to return a pointer to a node in a linked list, given a MOVIE TITLE and the head of the linked list
{
	MovieNodeLL* tmp = head;

	while (tmp != NULL)
	{
		if (title == tmp->title)
		{
			return tmp;
		}
		tmp = tmp->next;
	}

	return NULL;
}

MovieNodeBST* MovieTree::treeMinimum(MovieNodeBST *node) //use this to find the left most leaf node of the BST, you'll need this in the delete function
{
	while (node->leftChild != NULL)
	{
		node = node->leftChild;
	}
	return node;
}



