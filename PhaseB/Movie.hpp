#ifndef MOVIE_FILE
#define MOVIE_FILE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>


/**
* Structure defining a node of movie binary tree (dendro tainiwn kathgorias)
*/
typedef struct movie{
	int movieID; 				/* The movie identifier*/
	int category;				/* The category of the movie*/
	int year;					/* The year movie released*/
	int watchedCounter;	 		/* How many users rate the movie*/
	int sumScore;				/* The sum of the ratings of the movie*/
	float medianScore;		    /* Median score of the ratings of the movie*/
	struct movie *leftChild;	/* Pointer to the node's left child*/
	struct movie *rightChild;	/* Pointer to the node's right child*/
}movie_t;


/**
* Structure defining movie_category
*/

typedef struct movie_category{
	movie_t *movie;
	movie_t *sentinel;
	int movieCounter;
}movieCategory_t;

/**
* Structure defining a node of user_movie for history doubly linked binary 
* tree (dentro istorikou) 
*/
typedef struct user_movie{
	int movieID; 					/* The movie identifier*/
	int category;					/* The category of the movie*/
	int score;						/* The score of the movie*/
	struct user_movie *parent;		/* Pointer to the node's parent*/
	struct user_movie *leftChild;	/* Pointer to the node's left child*/
	struct user_movie *rightChild;	/* Pointer to the node's right child*/
}userMovie_t;

/**
* Structure defining a node of users' hashtable (pinakas katakermatismou
* xrhstwn)
*/
typedef struct user {
	int userID; 			/* The user's identifier*/
	userMovie_t *history;	/* A doubly linked binary tree with the movies watched by the user*/
	struct user *next;		/* Pointer to the next node of the chain*/	
}user_t;

extern movieCategory_t *categoryArray[5];  /* The categories array (pinakas kathgoriwn)*/
extern movie_t *new_releases;    		   /* New releases simply-linked binary tree*/
extern user_t **user_hashtable_p;		   /* The users hashtable. This is an array of chains (pinakas katakermatismoy xrhstwn)*/
extern int hashtable_size;				   /* The size of the users hashtable, parsed from the command line (>0)*/
extern unsigned int max_users;					   /* The maximum number of registrations (users)*/			
extern unsigned int max_id;   			   /* The maximum account ID */
extern unsigned int primes_g[160];



int get_hash(int key, int hashtable_size);
int hash_lookup(int key);

/**
 * @brief Creates a new user.
 * Creates a new user with userID as its identification.
 *
 * @param userID The new user's identification
 *
 * @return 0 on success
 *         1 on failure
 */

 int register_user(unsigned int userID);
 
/**
 * @brief Deletes a user.
 * Deletes a user with userID from the system, along with users' history tree.
 *
 * @param userID The new user's identification
 *
 * @return 0 on success
 *         1 on failure
 */

 int unregister_user(unsigned int userID);
 
 /**
 * @brief Add new movie to new release binary tree.
 * Create a node movie and insert it in 'new release' binary tree.
 *
 * @param movieID The new movie identifier
 * @param category The category of the movie
 * @param year The year movie released
 *
 * @return 0 on success
 *         1 on failure
 */

 int add_new_movie(unsigned int movieID, int category, int year);
 
 /**
 * @brief Categorize the movies from new release binary tree to the array of categories.
 *
 * @return 0 on success
 *         1 on failure
 */

 int categorize_movies(void);
 
 /**
 * @brief User rates the movie with identification movieID with score
 *
 * @param userID The identifier of the user
 * @param movieID The identifier of the movie
 * @param score The score that user rates the movie with id movieID
 *
 * @return 0 on success
 *         1 on failure
 */

 int rate_movie(unsigned int userID, unsigned int movieID, int score);
 
/**
 * @brief Identify the best rating score movie and cluster all the movies of a category.
 *
 * @param movieID The identifier of the movie
 * @param category The category of the movie
 *
 * @return 0 on success
 *         1 on failure
 */

 int cluster_movies(int category);
 
/**
 * @brief Find the median score that user rates movies.
 *
 * @param userID The identifier of the user
 *
 * @return 0 on success
 *         1 on failure
 */

 int user_stats(unsigned int userID);
 
/**
 * @brief Search for a movie with identification movieID in a specific category.
 *
 * @param movieID The identifier of the movie
 * @param category The category of the movie
 *
 * @return 0 on success
 *         1 on failure
 */

 int search_movie(unsigned int movieID, int category);
 
 /**
 * @brief Prints the movies in movies categories array.
 * @return 0 on success
 *         1 on failure
 */

 int print_movies(void);
 
  /**
 * @brief Prints the users hashtable.
 * @return 0 on success
 *         1 on failure
 */

 int print_users(void);
 
 /**
 * @brief Prints all the system information.
 * @return 0 on success
 *         1 on failure
 */
int print_world(void);
 
 #endif
