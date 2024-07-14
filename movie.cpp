

#include<assert.h>
#include "movie.h"
#include "AVLTree.h"

Movie::Movie(int views = 0, int movieId = 0) : views(views), favouriteMovie(movieId), recogmented(movieId)
{
    this->rating = 0; 
}

/** Returns a pointer to an AVL tree of movies
 * params: 
 * @key - movieId, identifier for the tree.
 * @views - an integer that describes the view count of the movie
 * @vip - boolean value, determins if the movie can be watched only by vip members
 * return value:
 * @ a pointer to the root of the tree.
*/
AVLTree<Movie> *creatMovie(int key, int views,bool vip)
{
    Movie node = Movie(views, key);
    AVLTree<Movie> movies = AVLTree<Movie>(key);
    movies.node = node;
    movies.vip = vip;
    return &movies;
}
//adjustRating
//============ Helper functions:

/** Given a none empty tree and a valid key such that the tree holds a node 
 * with the exact same key, the following function retrives a pointer to the exact same node
 * params:
 * @ tree - a pointer to the root of the tree.
 * @ key - movieId, identifier for the tree.
 * return value:
 * @ a pointer to the node of the tree - <key> as it's key.
*/
AVLTree<Movie> *seekMovie(AVLTree<Movie> *tree, int key)
{
    assert(key > 0 && tree != NULL);
    bool check = tree->keyExists(key);
    assert(check);

    if(key < tree->key){
        return seekMovie(tree->left_child, key);
    } else if( tree->key < key){
        return seekMovie(tree->right_child, key);
    }
    return tree;
}

int getFavourite(AVLTree<Movie> *favourite, AVLTree<Movie> *newMovie)
{
    assert(favourite != NULL && newMovie != NULL);
    if(favourite->node.rating <= newMovie->node.rating){
        if(favourite->node.views <= newMovie->node.views){
            if(newMovie->key <= favourite->key){
                return newMovie->key;
            }
        }
    }
    return favourite->key;
}


/** Trickle Fucntions asses each time which nodes are more recogmented*/
void trickleRating(AVLTree<Movie> *tree, AVLTree<Movie> *newMovie)
{
    if(tree == NULL || newMovie == NULL){
        return;
    }
    if(tree->node.rating < newMovie->node.rating && tree->right_child != NULL){
        if(tree->right_child->node.rating <= newMovie->node.rating){
            trickleRating(tree->right_child, newMovie);
        }
        tree->node.recogmented = newMovie->key;
        return;
    } else if(tree->node.rating > newMovie->node.rating && tree->left_child != NULL){
        if(tree->left_child->node.rating >= newMovie->node.rating){
            trickleRating(tree->left_child, newMovie);
        }
        return;
    } else {
        if(tree->node.views < newMovie->node.views){
            trickleViews(tree->right_child, newMovie);
        }else if( newMovie->node.views < tree->node.views){
            trickleViews(tree->left_child, newMovie);
        } else {
            if(tree->key < newMovie->key){
                trickleId(tree->right_child, newMovie);
            }
            tree->node.recogmented = newMovie->key;
            return;
        }
    }
}
void trickleViews(AVLTree<Movie> *tree, AVLTree<Movie> *newMovie){
    if(tree == NULL || newMovie == NULL){
        return;
    }
    if(tree->node.rating == newMovie->node.rating){
        if(tree->node.views < newMovie->node.views && tree->right_child != NULL){
            if(tree->right_child->node.views <= newMovie->node.views &&
                tree->right_child->node.rating == newMovie->node.rating){
                trickleViews(tree->right_child, newMovie);
            }
            tree->node.recogmented = newMovie->key;
            return;
        } else if(tree->node.views > newMovie->node.views && tree->left_child != NULL){
            if(tree->left_child->node.views >= newMovie->node.views &&
                tree->left_child->node.rating == newMovie->node.rating){
                    trickleViews(tree->left_child, newMovie);
            }
            return;
        } else {
            if(tree->key < newMovie->key){
                trickleId(tree->right_child, newMovie);
            } else 
            tree->node.recogmented = newMovie->key;
        }
    }
}

void trickleId(AVLTree<Movie> *tree, AVLTree<Movie> *newMovie){
    if(tree == NULL || newMovie == NULL){
        return;
    }
    if(tree->node.rating == newMovie->node.rating && tree->node.views == newMovie->node.views){
        if(tree->key < newMovie->key){
            trickleId(tree->right_child, newMovie);
        }
        tree->node.recogmented = newMovie->key;
    }
}

/** An algorithm that reasseses the most favourite movies in the tree
 * works in 0(log(n))
*/
AVLTree<Movie> *assertFavourites(AVLTree<Movie> *tree, int newMovieId)
{
    if(tree == NULL){
        return NULL;
    }
    assert(newMovieId > 0);

    int oldFavourite = tree->node.favouriteMovie;
    AVLTree<Movie> *newMovie = seekMovie(tree, newMovieId);
    AVLTree<Movie> *favourite = seekMovie(tree, oldFavourite);
    int newFavourite = getFavourite(favourite, newMovie);
    tree->node.favouriteMovie = newFavourite;
    if(oldFavourite == newFavourite){
        trickleRating(tree, newMovie);
    } else {
        trickleRating(tree, favourite);
    }
    return tree;
}

AVLTree<Movie> *assertFavouritesAfterDeletion(AVLTree<Movie> *tree)
{
    int middle = tree->node.favouriteMovie;
    int left = tree->left_child->node.favouriteMovie;
    int right = tree->right_child->node.favouriteMovie;

    int check1 = getFavourite(tree->left_child, tree);
    int check2 = getFavourite(tree->right_child, tree->left_child);

    if(check1 == left && check2 == right){    
        tree = assertFavourites(tree, right);// middle < left < right
    } else if(check1 == left && check2 == left){
        tree = assertFavourites(tree, left);// middle < left && right <= left
    } else if(check1 == middle && check2 == right){
        int check3 = getFavourite(tree, tree->right_child);// left <= middle && left < right
        if(check3 == middle){ //right < middle
            tree = assertFavourites(tree, middle);
        } else {
            tree = assertFavourites(tree, right);
        }
    } else if(check1 == middle && check2 == left){
        tree = assertFavourites(tree, middle);// left <= middle && right <= left
    }

}

//========== End of helper functions;

/** Adds a new node to a given movie AVL tree
 * params: 
 * @ movie - a pointer to the root of the tree.
 * @ key - movieId, identifier for the tree.
 * @ views - an integer that describes the view count of the movie.
 * @ vip - boolean value, determins if the movie can be watched only by vip members.
 * return value:
 * @ a pointer to the root of the tree.
*/
AVLTree<Movie> *insertMovie(AVLTree<Movie> *movie, int key, int views, bool vip, int rating)
{
    if(movie == NULL){
        return NULL;
    }
    assert(key > 0|| views >=0 );
    if(movie->key == 0){
        movie->key = key;
        movie->node.views = views;
        movie->vip = vip;
        if(rating != 0){
            movie->node.rating = rating;
        }
    }
    Movie node(views, key);
    if(rating != 0){
        node.rating = rating;
    }
    movie->insertNode(node, key);

    AVLTree<Movie> *temp = seekMovie(movie, key);
    temp->vip = vip;
    movie = assertFavourites(movie, key);
    return movie;
}

/** Deletes a node in the movie AVL tree
 * params:
 * @ movie - a pointer to the root of the tree.
 * @ key - movieId, identifier for the tree.
 * return value:
 * @ a pointer to the root of the tree.
*/
AVLTree<Movie> *deleteMovie(AVLTree<Movie> *movie, int key)
{
    assert(key > 0 && movie != NULL);
    bool check = movie->keyExists(key);
    if(!check){
        return movie;
    }
    AVLTree<Movie> *temp = movie->treeDeleteNode(key);
    temp = assertFavouritesAfterDeletion(temp);
    return temp;
}

/** Incrementing "views" field by the value of views
 * params:
 * @ movie - a pointer to the root of the tree.
 * @ key - movieId, identifier for the tree.
 * @ views - an integer that describes the view count of the movie.
 * return value:
 * @ a pointer to the root of the tree.
*/
AVLTree<Movie> *movieAddViews(AVLTree<Movie> *movie, int key, int views)
{
    assert(key > 0 && views > 0);
    assert(movie != NULL);
    //
    AVLTree<Movie> *viewedMovie = seekMovie(movie, key);
    viewedMovie->node.views += views;
    movie = assertFavourites(movie, key);
    return movie;
}

/** Incrementing the "rating"-field of the movie <key>
 * params:
 * @ movie - a pointer to the root of the tree.
 * @ key - movieId, identifier for the tree.
 * @ rating - an integer.
 * return value:
 * @ a pointer to the root of the tree.
*/
AVLTree<Movie> *movieAddRating(AVLTree<Movie> *movie, int key, int rating)
{
    assert(key > 0 && 0 <= rating && rating <= 100);
    assert(movie != NULL);
    
    AVLTree<Movie> *ratedMovie = seekMovie(movie, key);
    ratedMovie->node.rating += rating;
    return assertFavourites(movie, key);
}
//_________________ Recogmenting Section _______________

bool goRightFirst(AVLTree<Movie> *tree, int first, int secound)
{
    if(first <= 0 || secound <=0){
        return false;
    }
    assert(tree != NULL);
    AVLTree<Movie> *movie1 = seekMovie(tree, first);
    AVLTree<Movie> *movie2 = seekMovie(tree, secound);
    //
    if(movie1->node.rating > movie2->node.rating){
        return false;
    }
    if(movie1->node.views > movie2->node.views){
        return false;
    }
    if(movie2->key < movie1->key){
        return true;
    }
    return false;
}

/** Getting ruffly ordered tree and making the order complete 
 * works in 0(n)
*/
AVLTree<Movie> *adjustRating(AVLTree<Movie> *tree)
{
    if(tree == NULL){
        return NULL;
    }
    AVLTree<Movie> *right = adjustRating(tree->right_child);
    if(right == NULL){
        if(tree->left_child != NULL){
            tree->left_child->node.favouriteMovie = tree->node.favouriteMovie;
            return tree;
        }
        else {
            return tree;
        }
    } else {

    }
}

void dumpAux(AVLTree<Movie> *movie, int *const output)
{
    if(movie == NULL ){
        return;
    }
    if(movie->right_child != NULL){
        int first = movie->node.favouriteMovie;
        int secound = movie->right_child->node.favouriteMovie;
        if(goRightFirst(movie, first, secound)){

        }
    }
    output[0] = movie->node.favouriteMovie;
    dumpAux(movie->right_child, output+1);
    int buffer = movie->heap - movie->right_child->heap;
    dumpAux(movie->left_child, output + buffer);
    return;
}

/** Writes to output all the movie ID's in order
 * params:
 * @ movie - a pointer to the root of the tree.
 * output - a constant pointer to an integer array
*/
void dumpMovies(AVLTree<Movie> *movie, int *const output)
{
    if(movie == NULL){
        return;
    }
    dumpMovies(movie->right_child, output+1);
    output[0] = movie->node.favouriteMovie;
    int buffer = movie->heap - movie->right_child->heap;
    dumpMovies(movie->left_child, output+buffer);
}

AVLTree<Movie> *fillTree(AVLTree<Movie> *tree, AVLTree<Movie> *movies)
{
    if(tree == NULL){
        return NULL;
    }
    tree = fillTree(tree, movies->left_child);
    tree = insertMovie(tree, movies->key, movies->node.views, movies->vip, movies->node.rating);
    tree = fillTree(tree, movies->right_child);
    return tree;
}
