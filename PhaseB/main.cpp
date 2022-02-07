#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <cmath>

#include "Movie.hpp"

#define BUFFER_SIZE 1024  /**< Maximum length of a line in input file */

/* Uncomment the following line to enable debugging prints 
 * or comment to disable it */
#define DEBUG

#ifdef DEBUG
#define DPRINT(...) fprintf(stderr, __VA_ARGS__);
#else  /* DEBUG */
#define DPRINT(...)
#endif /* DEBUG */

int          hashtable_size; 	/** The size of the users hashtable (>0) */
unsigned int max_users;         /** The maximum number of registrations (users) */
unsigned int max_id;            /** The maximum user ID */

// This is a very conservative progress on the hashtable. Our purpose
// is to force many rehashes to check the stability of the code.
unsigned int primes_g[160] = {  5,   7,  11,  13,  17,  19,  23,  29,  31,  37,
                               41,  43,  47,  53,  59,  61,  67,  71,  73,  79,
                               83,  89,  97, 101, 103, 107, 109, 113, 127, 131,
                              137, 139, 149, 151, 157, 163, 167, 173, 179, 181,
                              191, 193, 197, 199, 211, 223, 227, 229, 233, 239,
                              241, 251, 257, 263, 269, 271, 277, 281, 283, 293,
                              307, 311, 313, 317, 331, 337, 347, 349, 353, 359,
                              367, 373, 379, 383, 389, 397, 401, 409, 419, 421,
                              431, 433, 439, 443, 449, 457, 461, 463, 467, 479,
                              487, 491, 499, 503, 509, 521, 523, 541, 547, 557,
                              563, 569, 571, 577, 587, 593, 599, 601, 607, 613,
                              617, 619, 631, 641, 643, 647, 653, 659, 661, 673,
                              677, 683, 691, 701, 709, 719, 727, 733, 739, 743,
                              751, 757, 761, 769, 773, 787, 797, 809, 811, 821,
                              823, 827, 829, 839, 853, 857, 859, 863, 877, 881,
                              883, 887, 907, 911, 919, 929, 937, 941, 947, 953};

user_t **user_hashtable_p;	/* The users hashtable. This is an array of chains (pinakas katakermatismoy xrhstwn)*/
movie_t *new_releases;     /* New releases simply-linked binary tree*/
movieCategory_t *categoryArray[5];  /* The categories array (pinakas kathgoriwn)*/


// Idea of simple hash:
// Make set of possible hash function outputs smaller using given information about the number and the id of the users.
// hash function (kmodM) where M is the size of the hash table.
// [0 max_id] all possible user ids -  big interval. ways to make it smaller?
// We assume the user-IDs are split uniformly in the [0 max_id], thus 
// if we map it [0 max_id] into [0 max_users], on avg, one user will fall in each interval.
// M_step = max_id/max_users. 
// mul_map = max_users/max_id
// M = max_users 
// Hash function = (k/M_step)modM = (k*mul_map)modM
// should be revised and cheched thorougly to be sure theoretically
// if max_id = 100 and max_users=25
// hash table size is  25 with step 4??
// for key=4: HF = (floor(4/4))mod25 =1mod25 = 1
// for key=14: HF = (floor(14/4))mod25 =3mod25 = 3
// for key=93: HF = (floor(93/4))mod25 =23mod25 = 23
// for key=100: HF = (floor(100/4))mod25 = 25mod25 = 0
// to reduce possibility of collisions, i will use the first prime number 
// bigger than max_users

int get_hash(int key, int hashtable_size){
	// int M_step = int(max_id/max_users);
	int mul_map = int(std::floor(max_users/max_id));
	return (key*mul_map)%hashtable_size;
}

int hash_lookup(int key){
	return 1;
}

/**
 * @brief Initializes all structures that have to be created and initialized.
 * 
 * @return 0 on success
 *         1 on failure
 */


 int initialize(){
	 //max users num -> max_users
	 //max userID -> max_id
	 int i=0;
	 int hash_size_not_prime = max_users;
	//  if (hash_size_not_prime<1) hash_size_not_prime = max_users/max_id;

	 // CHECK < or <=
	//  while(primes_g[i]<max_id) i++;
	 while(primes_g[i]<hash_size_not_prime) i++;
	 hashtable_size = primes_g[i];
	 
	 return 1;
 }

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

		DPRINT("Event: %s \n", buff);

		switch(buff[0]) {

		/* Comment */
		case '#':
			break;
		/* max_users */
		case '0': {
			sscanf(buff, "%c %u", &event, &max_users);
			DPRINT("max users: %u\n", max_users);
			break;
		}
		/* max_id */
		case '1': {
			sscanf(buff, "%c %u", &event, &max_id);
			DPRINT("max id: %u\n", max_id);
			break;
		}		
		/* Event R : R <userID> - Register user. */
		case 'R':
		{
			unsigned int userID;
			sscanf(buff, "%c %d", &event, &userID);
			DPRINT("%c %d\n", event, userID);
			if ( register_user(userID) ) {
				DPRINT("%c succeeded\n", event);
			} else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}
		/* Event U : U <userID> - Unregister user. */
		case 'U':
		{
			unsigned int userID;
			sscanf(buff, "%c %d", &event, &userID);
			DPRINT("%c %d\n", event, userID);

			if ( unregister_user(userID) ) {
				DPRINT("%c %d succeeded\n", event, userID);
			} else {
				fprintf(stderr, "%c %d failed\n", event, userID);
			}

			break;
		}
		/* Event A : A <movieID> <category> <year> - Add new movie. */
		case 'A':
		{
			unsigned movieID;
			int category, year;
			sscanf(buff, "%c %d %d %d", &event, &movieID, &category, &year);
			DPRINT("%c %d %d %d\n", event, movieID, category, year);

			if ( add_new_movie(movieID, category, year) ) {
				DPRINT("%c %d %d %d succeeded\n", event, movieID, category, year);
			} else {
				fprintf(stderr, "%c %d %d %d failed\n", event, movieID, category, year);
			}

			break;
		}
		/* Event C : C  - Categorize movies. */
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
		/* Event G : G <userID> <movieID> <score>  - Rate movie */
		case 'G':
		{
			unsigned int userID, movieID;
			int score;
			sscanf(buff, "%c %d %d %d", &event, &userID, &movieID, &score);
			DPRINT("%c %d %d %d\n", event, userID, movieID, score);

			if ( rate_movie(userID, movieID, score) ) {
				DPRINT("%c %d %d %d succeeded\n", event, userID, movieID, score);
			} else {
				fprintf(stderr, "%c %d %d %d failed\n", event, userID, movieID, score);
			}

			break;
		}
		/* Event S : S <category>  - Cluster movies */
		case 'S':
		{
			
			int category;
			sscanf(buff, "%c %d\n", &event, &category);
			DPRINT("%c %d\n", event, category);

			if ( cluster_movies(category) ) {
				DPRINT("%c %d succeeded\n", event, category);
			} else {
				fprintf(stderr, "%c %d failed\n", event, category);
			}

			break;
		}
		/* Event Q : Q <userID> - User statistics */
		case 'Q':
		{
			unsigned int userID;
			sscanf(buff, "%c %d\n", &event, &userID);
			DPRINT("%c %d\n", event, userID);

			if ( user_stats(userID) ) {
				DPRINT("%c %d succeeded\n", event, userID);
			} else {
				fprintf(stderr, "%c %d failed\n", event, userID);
			}

			break;
		}
		/* Event I : I <movieID> <category> - Search movie */
		case 'I':
		{
			unsigned int movieID;
			int category;
			sscanf(buff, "%c %d %d\n", &event, &movieID, &category);
			DPRINT("%c %d %d\n", event, movieID, category);

			if ( search_movie(movieID, category) ) {
				DPRINT("%c %d %d succeeded\n", event, movieID, category);
			} else {
				fprintf(stderr, "%c %d %d failed\n", event, movieID, category);
			}

			break;
		}
		/* Event M : M  - Print movies */
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
		/* Event P : P  - Print users */
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
		/* Event W : W  - Print world */
		case 'W':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if ( print_world() ) {
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
