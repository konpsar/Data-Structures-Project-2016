#include "Movie.h"


/**
 * @brief Creates a new user.
 * Creates a new user with userID as its identification.
 *
 * @param userID The new user's identification
 *
 * @return 0 on success
 *         1 on failure
 */

 int register_user(unsigned int userID){
	struct user * new_user = new struct user;
	
	//initialize new_user
	new_user->userID = userID;
	new_user->history = NULL;
	

	// Add to the right place of hashtable

	return 1;
 }
 
/**
 * @brief Deletes a user.
 * Deletes a user with userID from the system, along with users' history tree.
 *
 * @param userID The new user's identification
 *
 * @return 0 on success
 *         1 on failure
 */

 int unregister_user(unsigned int userID){
	 return 1;
 }
 
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

 int add_new_movie(unsigned int movieID, int category, int year){
	 return 1;
 }
 
 /**
 * @brief Categorize the movies from new release binary tree to the array of categories.
 *
 * @return 0 on success
 *         1 on failure
 */

 int categorize_movies(void){
	 return 1;
 }
 
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

 int rate_movie(unsigned int userID, unsigned int movieID, int score){
	 return 1;
 }
 
/**
 * @brief Identify the best rating score movie and cluster all the movies of a category.
 *
 * @param category The category of the movie
 *
 * @return 0 on success
 *         1 on failure
 */

 int cluster_movies(int category){
	 return 1;
 }
 
/**
 * @brief Find the median score that user rates movies.
 *
 * @param userID The identifier of the user
 *
 * @return 0 on success
 *         1 on failure
 */

 int user_stats(unsigned int userID){
	 return 1;
 }
 
/**
 * @brief Search for a movie with identification movieID in a specific category.
 *
 * @param movieID The identifier of the movie
 * @param category The category of the movie
 *
 * @return 0 on success
 *         1 on failure
 */

 int search_movie(unsigned int movieID, int category){
	 return 1;
 }
 
 /**
 * @brief Prints the movies in movies categories array.
 * @return 0 on success
 *         1 on failure
 */

 int print_movies(void){
	 return 1;
 }
 
  /**
 * @brief Prints the users hashtable.
 * @return 0 on success
 *         1 on failure
 */

 int print_users(void){
	 return 1;
 }
 
 /**
 * @brief Prints all the system information.
 * @return 0 on success
 *         1 on failure
 */
int print_world(void){
	 return 1;
 }
 