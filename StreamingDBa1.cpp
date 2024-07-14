#include "StreamingDBa1.h"
#include "movie.h"
#include "user.h"
#include "group.h"
#include "AVLTree.h"

streaming_database::streaming_database()
{
	// Users
	AVLTree<User> userTemp(0);
	this->users = &userTemp;
	// Movies
	this->comedie = creatMovie(0, 0, false);
	this->drama = creatMovie(0, 0, false);
	this->action = creatMovie(0, 0, false);
	this->fantasy = creatMovie(0, 0, false);
	// Groups
	this->groups = CreateGroupTree(0);
}

streaming_database::~streaming_database(){
	if(users != NULL){
		delete users;
	}
	if(comedie != NULL){
		delete comedie;
	}
	if(drama != NULL){
		delete drama;
	}
	if(action != NULL){
		delete action;
	}
	if(fantasy != NULL){
		delete fantasy;
	}
	if(groups != NULL){
		delete groups;
	}
}
//insertMovie
StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{
	if(movieId <= 0 || genre == Genre::NONE || views < 0){
		return StatusType::INVALID_INPUT;
	}
	if(this->comedie->keyExists(movieId) || this->drama->keyExists(movieId) || 
		this->action->keyExists(movieId) || this->fantasy->keyExists(movieId)){
		return StatusType::FAILURE;
	}
	switch (genre)
	{
	case Genre::COMEDY :
		try{
			this->comedie = insertMovie(this->comedie, movieId, views, vipOnly);
		}
		catch(...){
			return StatusType::ALLOCATION_ERROR;
		}
		break;
	case Genre::DRAMA :
		try{
			this->drama = insertMovie(this->drama, movieId, views, vipOnly);
		}
		catch(...){
			return StatusType::ALLOCATION_ERROR;
		}
		break;
	case Genre::ACTION :
		try{
			this->action = insertMovie(this->action, movieId, views, vipOnly);
		}
		catch(...){
			return StatusType::ALLOCATION_ERROR;
		}
		break;
	case Genre::FANTASY :
		try{
			this->fantasy = insertMovie(this->fantasy, movieId, views, vipOnly);
		}
		catch(...){
			return StatusType::ALLOCATION_ERROR;
		}
		break;
	default:
		break;
	}
	return StatusType::SUCCESS;
}
//groupTreeAddUser
StatusType streaming_database::remove_movie(int movieId)
{
	if(movieId <= 0){
		return StatusType::INVALID_INPUT;
	}
	if(!(this->comedie->keyExists(movieId) || this->drama->keyExists(movieId) || 
		this->action->keyExists(movieId) || this->fantasy->keyExists(movieId))){
		return StatusType::FAILURE;
	}
	if(this->comedie->keyExists(movieId)){
		this->comedie = deleteMovie(this->comedie, movieId);
		return StatusType::SUCCESS;
	}
	if(this->drama->keyExists(movieId)){
		this->drama = deleteMovie(this->drama, movieId);
		return StatusType::SUCCESS;
	}
	if(this->action->keyExists(movieId)){
		this->action = deleteMovie(this->action, movieId);
		return StatusType::SUCCESS;
	}
	if(this->fantasy->keyExists(movieId)){
		this->fantasy = deleteMovie(this->fantasy, movieId);
		return StatusType::SUCCESS;
	}
	return StatusType::SUCCESS;
}

StatusType streaming_database::add_user(int userId, bool isVip)
{
	if(userId <= 0){
		return StatusType::INVALID_INPUT;
	}
	if(this->users->keyExists(userId)){
		return StatusType::FAILURE;
	}
	try{
		this->users = insertUser(this->users, userId, isVip);
	}
	catch(...){
		return StatusType::ALLOCATION_ERROR;
	}
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_user(int userId)
{
	if(userId <= 0 ){
		return StatusType::INVALID_INPUT;
	}
	if(!this->users->keyExists(userId)){
		return StatusType::FAILURE;
	}
	this->users = deleteUser(this->users, userId);
	return StatusType::SUCCESS;
}

StatusType streaming_database::add_group(int groupId)
{
	if(groupId <= 0){
		return StatusType::INVALID_INPUT;
	}
	if(!this->groups->keyExists(groupId)){
		return StatusType::FAILURE;
	}
	try{
		this->groups = insertGroup(this->groups, groupId);
	}
	catch(...){
		return StatusType::ALLOCATION_ERROR;
	}
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_group(int groupId)
{
	if(groupId <= 0){
		return StatusType::INVALID_INPUT;
	}
	if(!this->groups->keyExists(groupId)){
		return StatusType::FAILURE;
	}
	try{
		this->groups = deleteGroupTreeNode(this->groups, groupId);
	}
	catch(...){
		return StatusType::ALLOCATION_ERROR;
	}
	return StatusType::SUCCESS;
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)
{
	if(userId <= 0 || groupId <= 0){
		return StatusType::INVALID_INPUT;
	}
	if(!this->users->keyExists(userId) || !this->groups->keyExists(groupId)){
		return StatusType::FAILURE;
	}
	if(!userInGroup(this->users, userId, 0)){
		return StatusType::FAILURE;
	}
	try{
		AVLTree<GroupTree> *group = seekGroup(this->groups, groupId);
		AVLTree<User> *seek = seekUser(this->users, userId);
		Group node(seek);
		group->node.group = group->node.group->insertNode(node, seek->key);
		//this->groups = groupTreeAddUser(this->groups, seek ,groupId);
		this->users = setGroup(seek, userId, group);
	}
	catch(...){
		return StatusType::ALLOCATION_ERROR;
	}
	return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId)
{
	if(movieId <= 0 || userId <= 0){
		return StatusType::INVALID_INPUT;
	}
	if(!this->users->keyExists(userId)){
		return StatusType::FAILURE;
	}
	bool vipUser = this->users->isVip(userId);
	bool vipMovie = true;
	if(this->comedie->keyExists(movieId)){
		vipMovie = this->comedie->isVip(movieId);
		if(vipMovie && !vipUser){// Rational: if either user is a vip, or the movie isn't vip only 
			return StatusType::FAILURE;//then there is no problem//
		}
		this->users = userAddViews(this->users, userId, Genre::COMEDY);
		this->comedie = movieAddViews(this->comedie, movieId, 1);
		return StatusType::SUCCESS;
	} else if(this->drama->keyExists(movieId)){
		vipMovie = this->drama->isVip(movieId);
		if(vipMovie && !vipUser){
			return StatusType::FAILURE;
		}
		this->users = userAddViews(this->users, userId, Genre::DRAMA);
		this->drama = movieAddViews(this->drama, movieId, 1);
		return StatusType::SUCCESS;
	} else if(this->action->keyExists(movieId)){
		vipMovie = this->action->isVip(movieId);
		if(vipMovie && !vipUser){
			return StatusType::FAILURE;
		}
		this->users = userAddViews(this->users, userId, Genre::ACTION);
		this->action = movieAddViews(this->action, movieId, 1);
		return StatusType::SUCCESS;
	} else if(this->fantasy->keyExists(movieId)){
		vipMovie = this->fantasy->isVip(movieId);
		if(vipMovie && !vipUser){
			return StatusType::FAILURE;
		}
		this->users = userAddViews(this->users, userId, Genre::FANTASY);
		this->fantasy = movieAddViews(this->fantasy, movieId, 1);
		return StatusType::SUCCESS;
	}
    return StatusType::FAILURE;
}
//userGetViews
StatusType streaming_database::group_watch(int groupId,int movieId)
{
	if(movieId <= 0 || groupId <= 0){
		return StatusType::INVALID_INPUT;
	}
	if(!this->groups->keyExists(groupId)){
		return StatusType::FAILURE;
	}
	bool vipGroup = this->groups->isVip(groupId);
	bool vipMovie = true;
	if(this->comedie->keyExists(movieId)){//=======================
		vipMovie = this->comedie->isVip(movieId);
		if(vipMovie && !vipGroup){// Rational: if either user is a vip, or the movie isn't vip only 
			return StatusType::FAILURE;//then there is no problem//
		}
		this->groups = groupAddViews(this->groups, groupId, Genre::COMEDY);
		int groupSize = getGroupSize(this->groups, groupId);
		this->comedie = movieAddViews(this->comedie, movieId, groupSize);
		return StatusType::SUCCESS;
	} else if(this->drama->keyExists(movieId)){//==================
		vipMovie = this->drama->isVip(movieId);
		if(vipMovie && !vipGroup){// Rational: if either user is a vip, or the movie isn't vip only 
			return StatusType::FAILURE;//then there is no problem//
		}
		this->groups = groupAddViews(this->groups, groupId, Genre::DRAMA);
		int groupSize = getGroupSize(this->groups, groupId);
		this->drama = movieAddViews(this->drama, movieId, groupSize);
		return StatusType::SUCCESS;
	} else if(this->action->keyExists(movieId)){//=================
		vipMovie = this->action->isVip(movieId);
		if(vipMovie && !vipGroup){// Rational: if either user is a vip, or the movie isn't vip only 
			return StatusType::FAILURE;//then there is no problem//
		}
		this->groups = groupAddViews(this->groups, groupId, Genre::ACTION);
		int groupSize = getGroupSize(this->groups, groupId);
		this->action = movieAddViews(this->action, movieId, groupSize);
		return StatusType::SUCCESS;
	} else if(this->fantasy->keyExists(movieId)){//================
		vipMovie = this->fantasy->isVip(movieId);
		if(vipMovie && !vipGroup){// Rational: if either user is a vip, or the movie isn't vip only 
			return StatusType::FAILURE;//then there is no problem//
		}
		this->groups = groupAddViews(this->groups, groupId, Genre::FANTASY);
		int groupSize = getGroupSize(this->groups, groupId);
		this->fantasy = movieAddViews(this->fantasy, movieId, groupSize);
		return StatusType::SUCCESS;
	}
	return StatusType::FAILURE;
}

output_t<int> streaming_database::get_all_movies_count(Genre genre)
{
	if(genre == Genre::COMEDY){
		const int movieNum = this->comedie->heap;
		output_t<int> out(movieNum);
		return out;
	} else if(genre == Genre::DRAMA){
		const int movieNum = this->drama->heap;
		output_t<int> out(movieNum);
		return out;
	} else if(genre == Genre::ACTION){
		const int movieNum = this->action->heap;
		output_t<int> out(movieNum);
		return out;
	} else if(genre == Genre::FANTASY){
		const int movieNum = this->fantasy->heap;
		output_t<int> out(movieNum);
		return out;
	}
	int sum = 0;
	sum += this->comedie->heap;
	sum += this->drama->heap;
	sum += this->action->heap;
	sum += this->fantasy->heap;
	const int movieTotal = sum;
	output_t<int> out(movieTotal);
	return out;
	/*
    static int i = 0;
    return (i++==0) ? 11 : 2;movieAddRating
	*/
}

StatusType streaming_database::get_all_movies(Genre genre, int *const output)
{
	if(output == NULL){
		return StatusType::INVALID_INPUT;
	}
	try{
		switch (genre)
		{
		case Genre::COMEDY :
			if(this->comedie->heap <= 0){
				return StatusType::FAILURE;
			}
			dumpMovies(this->comedie, output);
			return StatusType::SUCCESS;
			break;
		case Genre::DRAMA :
			if(this->drama->heap <= 0){
				return StatusType::FAILURE;
			}
			dumpMovies(this->drama, output);
			return StatusType::SUCCESS;
			break;
		case Genre::ACTION :
			if(this->action->heap <= 0){
				return StatusType::FAILURE;
			}
			dumpMovies(this->action, output);
			return StatusType::SUCCESS;
			break;
		case Genre::FANTASY :
			if(this->fantasy->heap <= 0){
				return StatusType::FAILURE;
			}
			dumpMovies(this->fantasy, output);
			return StatusType::SUCCESS;
			break;
		default:
			if(this->comedie <=0 && this->drama <= 0 && this->action <= 0 && this->fantasy <=0){
				return StatusType::FAILURE;
			}
			AVLTree<Movie> *all_movies = creatMovie();
			all_movies = fillTree(all_movies, this->comedie);
			all_movies = fillTree(all_movies, this->drama);
			all_movies = fillTree(all_movies, this->action);
			all_movies = fillTree(all_movies, this->fantasy);
			dumpMovies(all_movies, output);
			break;
		}
	}
	catch(StatusType &status){
		return status;
	}
	catch(...){
		StatusType::ALLOCATION_ERROR;
	}
	return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{
	if(userId <= 0){
		output_t<int> out(StatusType::INVALID_INPUT);
		return out;
	}
	if(!this->users->keyExists(userId)){
		output_t<int> out(StatusType::FAILURE);
		return out;
	}
	const int ans = userGetViews(this->users, userId, genre);
	output_t<int> out(ans);
	return out;
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{
	if(userId <= 0 || movieId <= 0 || rating < 0 || rating > 100){
		return StatusType::INVALID_INPUT;
	}
	if(!this->users->keyExists(userId)){
		return StatusType::FAILURE;
	}
	bool vipUser = this->users->isVip(userId);
	bool vipMovie = true;
	if(this->comedie->keyExists(movieId)){
		vipMovie = this->comedie->isVip(movieId);
		if(vipMovie && !vipUser){
			return StatusType::FAILURE;
		}
		this->comedie = movieAddRating(this->comedie, movieId, rating);
		return StatusType::SUCCESS;
	} else if(this->drama->keyExists(movieId)){
		vipMovie = this->drama->isVip(movieId);
		if(vipMovie && !vipUser){
			return StatusType::FAILURE;
		}
		this->drama = movieAddRating(this->drama, movieId, rating);
		return StatusType::SUCCESS;
	} else if(this->action->keyExists(movieId)){
		vipMovie = this->drama->isVip(movieId);
		if(vipMovie && !vipUser){
			return StatusType::FAILURE;
		}
		this->action = movieAddRating(this->action, movieId, rating);
		return StatusType::SUCCESS;
	} else if(this->fantasy->keyExists(movieId)){
		vipMovie = this->drama->isVip(movieId);
		if(vipMovie && !vipUser){
			return StatusType::FAILURE;
		}
		this->fantasy = movieAddRating(this->fantasy, movieId, rating);
		return StatusType::SUCCESS;
	}
	return StatusType::FAILURE;
}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{
	if(groupId <= 0){
		output_t<int> out(StatusType::INVALID_INPUT);
		return out;
	}
	bool groupExist = this->groups->keyExists(groupId);
	AVLTree<GroupTree> *temp = seekGroup(this->groups, groupId);
	bool notEmpty = temp->node.group->heap; // should make this a function
	if(!groupExist || (groupExist && !notEmpty)){
		output_t<int> out(StatusType::FAILURE);
		return out;
	}
	Genre favouriteGenre = getFavouriteGenre(temp);
	switch (favouriteGenre)
	{
	case Genre::COMEDY :
		const int ans = this->comedie->node.favouriteMovie;
		output_t<int> out(ans);
		break;
	case Genre::DRAMA :
		const int ans = this->drama->node.favouriteMovie;
		output_t<int> out(ans);
		break;
	case Genre::ACTION :
		const int ans = this->action->node.favouriteMovie;
		output_t<int> out(ans);
		break;
	default :
		const int ans = this->fantasy->node.favouriteMovie;
		output_t<int> out(ans);
		break;
	return out;
}


