# Movie-streaming-service
This is the first project in my Data structures course, the goal is to use data structures to efficiently manage a streaming service.
The server will keep movies, information about users and other statistical data.

I have implemented the server using mainly the AVLTree data structure, and for different objects I wanted the tree to act differently,
therefore I have decided to make it an abstract class.


//__________________________________________________
The service's API includes the following functions:

streaming_database() :
Initiating an empty database for the server.
Time complexity - O(1)

~streaming_database() :
Deleting the database.
Time complexity - linear in the number of users, movies and watch groups

add_movie(int movieId, Genre genre, int views, bool vipOnly) :
Inserts the movie to the data base and document its viewing statistics and meta data.
Time complexity - logarithmic in the number of movies in the system

add_user(int userId, bool isVip) :
Insert a new user's information to the system.
Time complexity - logarithmic in the number of users in the system.

add_group(int groupId) :
Creates a new watching group.
Time complexity - logarithmic in the number of watch groups

add_user_to_group(int userId, int groupId) :
This function also check the user is only in one watch group.
Time complexity O(log(number of users) + log(number of groups))

get_all_movies_count(Genre genre) : 
Query for the number of all the movies of the same genre.
Time complexity - O(1).

get_all_movies(Genre genre, int ∗ const output) : 
Query all the movies of the same genre.
Time complexity - Linear in the number of movies of that genre.

get_num_views(int userId, Genre genre) : 
Query watching statistics of a given user in this genre.
Time complexity - logarithmic in the number of users.

get_group_recommendation(int groupId) : 
The system recogments the group a movie to watch according to their watching statistics.
Time complexity - Logarithmic in the number of groups.

