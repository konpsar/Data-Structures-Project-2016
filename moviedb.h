/* Number of movie categories (drama, oscar, cinephile, documentary, cartoon, new releases) */
#define M 6 
const char *categories_array[M] = {"drama", "oscar", "cinephile", "documentary", "cartoon", "new releases"};


/* Structure defining a node of the movie lists */
struct movie {
		int 	mid; 			
		int category; 		
		int 	year; 			
		struct  movie *next;	
};

/* Structure defining a node of a user's history / favorites movie list */
struct user_movie {
		int mid; 					
		int category; 			
		int score; 					
		struct user_movie *prev; 	
		struct user_movie *next; 	
};

/* Structure defining a node of the users list */
struct user {
		int uid; 						/* The identifier of the user */
		struct user_movie * history; 	/* The history list of user */
		struct user_movie * favorites; 	/* The favorites movies list of user */
		struct user *next; 				/* Singly-linked, unsorted with sentinel */
};


struct movie * Movie_categories[M]; /*The array of the movie categories*/

struct user * users_list; 	 /* global variable, pointer to the beginning of the users list*/
struct user * users_sentinel; /* global variable, pointer to the sentinel node of the users list */


/*Needed function protypes definition*/

/**
 * @brief Create a new user and add him to the users list
 *
 * @param uid The new user's id
 *
 * @return 1 on success
 *         0 on failure
 */
int register_user(int uid);


/**
 * @brief Remove user from user's list
 *
 * @param uid The id of the user to be deleted
 *
 * @return 1 on success
 *         0 on failure
 */
int unregister_user(int uid);


/**
 * @brief Create a new movie and add it to the new releases category
 *
 * @return 1 on success
 *         0 on failure
 */
int add_new_movie(int mid, int category, int year);


/**
 * @brief Categorize new releases to the appropriate category list
 *
 * @return 1 on success
 *         0 on failure
 */
int categorize_movies();


/**
 * @brief Insert a movie to a user's history with the corresponding rating score
 * 
 * @param uid The id of user
 * @param mid The movie id
 * @param score The rating score of the movie
 * 
 * @return 1 on success
 *         0 on failure
 */
int rate_movie(int uid, int mid, int score);


/**
 * @brief Identify favorite movies of all users
 *
 * @return 1 on success
 *         0 on failure
 */
int identify_favorite_movies();


/**
 * @brief Suggest a movie to a user from its favorites lists based on another movie
 * 
 * @param uid The user's id
 * @param mid The id of the base movie
 *
 * @return 1 on success
 *         0 on failure
 */
int suggest_movie(int uid, int mid);


/**
 * @brief Search for a specific movie on all categories
 *
 * @param pid The id of the movie to be searched
 *
 * @return 1 on success
 *         0 on failure
 */
int search_movie(int pid);


/**
 * @brief Print the movies of all categories
 *
 * @return 1 on success
 *         0 on failure
 */
int print_movies();
		

/**
 * @brief Print all users
 *
 * @return 1 on success
 *         0 on failure
 */
int print_users();


/**
 * @brief Print the id of available presents of the stock
 *
 * @return 1 on success
 *         0 on failure
 */
int print_stock();
		
/**
 * @brief Print the most popular present of each district
 *
 * @return 1 on success
 *         0 on failure
 */
int advanced_analytics();


