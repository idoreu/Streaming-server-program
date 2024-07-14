# Movie-streaming-service
This is the first project in my Data structures course, the goal is to use data structures to efficiently manage a streaming service.
The server will keep movies and information about customers and wether or not they are part of a watching group.

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

