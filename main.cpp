#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <iostream>

#include "moviedb.h"

using namespace std;

#define BUFFER_SIZE 1024  /**< Maximum length of a line in input file */

/* Uncomment the following line to enable debugging prints 
 * or comment to disable it */
#define DEBUG

#ifdef DEBUG
#define DPRINT(...) fprintf(stderr, __VA_ARGS__);
#else  /* DEBUG */
#define DPRINT(...)
#endif /* DEBUG */

int initialize() {
	
	//Users sentinel initialization
	users_sentinel = new struct user;
	users_sentinel->uid = -1;
	users_sentinel->history = NULL;
	users_sentinel->favorites = NULL;
	users_sentinel->next = NULL;

	//Initialize the users_senitnel as the users_list head
	users_list = users_sentinel; 

	//Movie categories array
	for (int i=0;i<M;i++) { 
		Movie_categories[i] = NULL; 
	}

	return 1;

}

int register_user(int uid) {
	struct user * new_user = new struct user;

	//initialize new_user
	new_user->uid = uid;
	new_user->history = NULL;
	new_user->favorites = NULL;
	
	//insert new user in the beginning of the list
	new_user->next = users_list;
	//update users_list head
	users_list = new_user;
	
	cout << "R <" << uid << ">" << endl;
	cout << "\tUsers = <" << users_list->uid << ">";
	for (struct user * current = users_list->next; current->next; current = current -> next){
		cout<< ", <" << current->uid << ">";
	}
    cout<<endl<<"DONE"<<endl<<endl;
	return 1;
}

int unregister_user(int uid) {
	struct user * current = NULL;		
	struct user * prev = NULL;
	users_sentinel->uid = uid;

	// search for target node (linear search)
	for (current=users_list; current->uid!=uid; current = current->next) prev = current;
	
	if (current!=users_sentinel){
		//delete user
		if (!prev){ 
			// delete head of list
			users_list = current->next;
		}else{
			// delete any other node in list
			prev->next = current-> next;
		}
		//free memory
		delete current;
	}
	// reset sentinel to its default values
	users_sentinel->uid = -1; 

	// print users
	cout << "U <" << uid << ">" << endl;
	cout << "\tUsers = <" << users_list->uid << ">";
	for (struct user * current = users_list->next; current->next; current = current -> next){
		cout<< ", <" << current->uid << ">";
	}
    cout<<endl<<"DONE"<<endl<<endl;

	return 1;
}

int add_new_movie(int mid, int category, int year) {
	// new releases list should remain sorted after addition
	// I will implement the addition with the logic of insertion sort
	// First the search for the right index to insert the movie will be implemented 
	// with linear search, and for optimization, I can implement it afterwards with binary search. 

	struct movie *movies_list_head=NULL, *current=NULL, *prev=NULL;
	struct movie *new_movie = new struct movie;
	new_movie->mid      = mid;
	new_movie->category = category;
	new_movie->year     = year;

	// Linear search for the place where new movie should be inserted 
	for (current = Movie_categories[M-1]; current && current->mid<mid; current = current->next) prev = current;
	// new movie should be placed between prev and current
	if (!prev){
		new_movie->next = current;
		Movie_categories[M-1] = new_movie;
	}else{
		prev->next = new_movie;
		new_movie->next = current;	
	}

	// print movies
	cout << "A" << endl << endl;
	cout << "\tMOVIES:";
	for (int i=0; i<M; i++){
		cout << endl << "\t" << categories_array[i] << ":";
		// print all movies from category_i
		for (struct movie * current = Movie_categories[i]; current; current = current -> next){
			cout<< " <" << current->mid << ">";
		}
	}
    cout<<endl<<"DONE"<<endl<<endl;

	return 1;
}

int categorize_movies() {
	return 1;
}

int rate_movie(int uid, int mid, int score) {
	return 1;
}

int identify_favorite_movies() {
	return 1;
}

int suggest_movie(int uid, int mid) {
	return 1;
}

int search_movie(int mid) {
	return 1;
}

int print_movies(void) {
	return 1;
}

int print_users(void) {
	return 1;
}




/**
 * @brief The main function
 *
 * @param argc Number of arguments
 * @param argv Argument vector
 *
 * @return 0 on success
 *         1 on failure
 */
int main(int argc, char** argv)
{
	initialize();
	FILE *fin = NULL;
	char buff[BUFFER_SIZE], event;

	/* Check command buff arguments */
	if ( argc != 2 ) {
		fprintf(stderr, "Usage: %s <input_file> \n", argv[0]);
		return EXIT_FAILURE;
	}

	/* Open input file */
	if (( fin = fopen(argv[1], "r") ) == NULL ) {
		fprintf(stderr, "\n Could not open file: %s\n", argv[1]);
		perror("Opening test file\n");
		return EXIT_FAILURE;
	}

	/* Read input file buff-by-buff and handle the events */
	while ( fgets(buff, BUFFER_SIZE, fin) ) {

		DPRINT("\n>>> Event: %s", buff);

		switch(buff[0]) {

		/* Comment */
		case '#':
			break;

		/* Register user
		 * R <uid> */
		case 'R':
		{
			int uid;
			sscanf(buff, "%c %d", &event, &uid);

			if ( register_user(uid) ) {
				DPRINT("R succeeded\n");
			} else {
				fprintf(stderr, "R failed\n");
			}

			break;
		}

		/* Unregister user
		 * U <uid> */
		case 'U':
		{
			int uid;
			sscanf(buff, "%c %d", &event, &uid);
			DPRINT("%c %d\n", event, uid);

			if ( unregister_user(uid) ) {
				DPRINT("%c %d succeeded\n", event, uid);
			} else {
				fprintf(stderr, "%c %d failed\n", event, uid);
			}

			break;
		}

		/* Add movie
		 * A <mid> <category> <year> */
		case 'A':
		{
			int mid;
			int category;
			int year;
			sscanf(buff, "%c %d %d %d", &event, &mid, &category, &year);
			DPRINT("%c %d %d %d\n", event, mid, category, year);

			if ( add_new_movie(mid, category, year) ) {
				DPRINT("%c %d %d %d succeeded\n", event, mid, category, year);
			} else {
				fprintf(stderr, "%c %d %d %d failed\n", event, mid, category, year);
			}

			break;
		}

		/* Categorize movies
		 * C */
		case 'C':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if ( categorize_movies() ) {
				DPRINT("%c succeeded\n", event);
			} else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Rate movie
		 * G <uid> <mid> <score>*/
		case 'G':
		{
			int uid;
			int mid;
			int score;
			sscanf(buff, "%c %d %d %d", &event, &uid, &mid, &score);
			DPRINT("%c %d %d %d\n", event, uid, mid, score);

			if ( rate_movie(uid, mid, score) ) {
				DPRINT("%c %d %d %d succeeded\n", event, uid, mid, score);
			} else {
				fprintf(stderr, "%c %d %d %d failed\n", event, uid, mid, score);
			}

			break;
		}

		/* Identify favorites
		 * F */
		case 'F':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if ( identify_favorite_movies() ) {
				DPRINT("%c succeeded\n", event);
			} else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Trigger an orphan planet cluster split
		 * C <cid1> <cid2> <cid3> */
		case 'S':
		{
			int uid;
			int mid;
			sscanf(buff, "%c %d %d\n", &event, &uid, &mid);
			DPRINT("%c %d %d\n", event, uid, mid);

			if ( suggest_movie(uid, mid) ) {
				DPRINT("%c %d %d succeeded\n", event, uid, mid);
			} else {
				fprintf(stderr, "%c %d %d failed\n", event, uid, mid);
			}

			break;
		}

		/* Search movie
		 * I <mid> */
		case 'I':
		{
			int mid;
			sscanf(buff, "%c %d", &event, &mid);
			DPRINT("%c %d\n", event, mid);

			if ( search_movie(mid) ) {
				DPRINT("%c %d succeeded\n", event, mid);
			} else {
				fprintf(stderr, "%c %d failed\n", event, mid);
			}

			break;
		}

		/* Print movies
		 * M */
		case 'M':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if ( print_movies() ) {
				DPRINT("%c succeeded\n", event);
			} else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Print users
		 * P */
		case 'P':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if ( print_users() ) {
				DPRINT("%c succeeded\n", event);
			} else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Empty line */
		case '\n':
			break;

		/* Ignore everything else */
		default:
			DPRINT("Ignoring buff: %s \n", buff);

			break;
		}
	}

	return (EXIT_SUCCESS);
}
