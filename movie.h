#ifndef MOVIE_H
#define MOVIE_H

#include "AVLTree.h"

class Movie {
public:

    void addViews(int views);// to delete
    void addRating(int rating);

    Movie(int views, int movieId);
    int recogmented;
    int favouriteMovie; // It is promised that favouriteMovie is the MvieId of the heighest ranked in the sub-tree;
    int views;
    int rating;// 
};

//AVLTree<Movie> *setVip(AVLTree<Movie> *movie, int key);arrangeMovies

/** Returns a pointer to an AVL tree of movies
 * params: 
 * @key - movieId, identifier for the tree.
 * @views - an integer that describes the view count of the movie
 * @vip - boolean value, determins if the movie can be watched only by vip members
 * return value:
 * @ a pointer to the root of the tree.
*/
AVLTree<Movie> *creatMovie(int key = 0, int views = 0,bool vip = false);
// Note: default settings key == 0, views == 0, vip = false;


/** An algorithm to determine for each movie if it is the most favorite
 * in it's sub-tree;
 * params: 
 * @ movie - a pointer to the root of the tree.
 * @ key - movieId, identifier for the tree.
 * @ views - an integer that describes the view count of the movie.
 * @ rating - an integer
 * return value:
 * @ a pointer to the root of the tree.
*/
AVLTree<Movie> *adjustRating(AVLTree<Movie> *movie, int key, int views);

/** Given a none empty tree and a valid key such that the tree holds a node 
 * with the exact same key, the following function retrives a pointer to the exact same node
 * params:
 * @ tree - a pointer to the root of the tree.
 * @ key - movieId, identifier for the tree.
 * return value:
 * @ a pointer to the node of the tree - <key> as it's key.
*/
AVLTree<Movie> *seekMovie(AVLTree<Movie> *tree, int key);

/** Adds a new node to a given movie AVL tree
 * params: 
 * @ movie - a pointer to the root of the tree.
 * @ key - movieId, identifier for the tree.
 * @ views - an integer that describes the view count of the movie.
 * @ vip - boolean value, determins if the movie can be watched only by vip members.
 * return value:
 * @ a pointer to the root of the tree.
*/
AVLTree<Movie> *insertMovie(AVLTree<Movie> *movie, int key, int views, bool vip, int recogmented = 0);
// take care of default instance
// add exceptions if needed;

/** Deletes a node in the movie AVL tree
 * params:
 * @ movie - a pointer to the root of the tree.
 * @ key - movieId, identifier for the tree.
 * return value:
 * @ a pointer to the root of the tree.
*/
AVLTree<Movie> *deleteMovie(AVLTree<Movie> *movie, int key);

/** Incrementing "views" field by the value of views
 * params:
 * @ movie - a pointer to the root of the tree.
 * @ key - movieId, identifier for the tree.
 * @ views - an integer that describes the view count of the movie.
 * return value:
 * @ a pointer to the root of the tree.
*/
AVLTree<Movie> *movieAddViews(AVLTree<Movie> *movie, int key, int views);

/** Incrementing the "rating"-field of the movie <key>
 * params:
 * @ movie - a pointer to the root of the tree.
 * @ key - movieId, identifier for the tree.
 * @ rating - an integer.
 * return value:
 * @ a pointer to the root of the tree.
*/
AVLTree<Movie> *movieAddRating(AVLTree<Movie> *movie, int key, int rating);


//_____________ problem in implementing _____________


/** Writes to output all the movie ID's in order
 * params:
 * @ movie - a pointer to the root of the tree.
 * output - a constant pointer to an integer array
*/
void dumpMovies(AVLTree<Movie> *movie, int *const output);

AVLTree<Movie> *fillTree(AVLTree<Movie> *tree, AVLTree<Movie> *movies);

void arrangeAllCategories(AVLTree<Movie> *comedie, AVLTree<Movie> *drama, AVLTree<Movie> *action,
    AVLTree<Movie> *fantasy, int *const output);

#endif