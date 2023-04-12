#pragma once
#include "service.h"
#include "domain.h"
#include "repository.h"
#include <cassert>




void TEST_REPO() {
	repository repo;
	user newUser;
	int counter = repo.getAllUsers().size();
	repo.addUser(newUser);
	assert(repo.getAllUsers().size() == counter +1);
	repo.deleteUser(newUser);
	assert(repo.getAllUsers().size() == counter );
	counter = repo.getAllMovies().size();
	movie newMovie;
	repo.addMovie(newMovie);
	assert(repo.getAllMovies().size() == counter + 1);
	repo.deleteMovie(newMovie);
	assert(repo.getAllMovies().size() == counter);
	repo.userDump();
	repo.movieDump();
	repo.addMovie(newMovie);
	repo.likeMovie(counter);
	assert(repo.getMovie(counter).likes == newMovie.likes+1);
	repo.updateMovie(newMovie);
	assert(repo.getMovie(counter) == newMovie);
	repo.addUser(newUser);
	repo.updateCrtUser(newUser);
}
void TEST_SERVICE_ADMIN(){
	service serv;
	movie newMovie;
	user newUser;
	int counterUsers = serv.repo.getAllUsers().size();
	int counterMovies = serv.repo.getAllMovies().size();
	serv.addUser("John", "1");
	serv.addUser("John", "1");
	assert(serv.Login("John", "0") == false);
	assert(serv.Login("Jho", "1") == false);
	assert(serv.GetUsername() == "Not logged in!");
	assert(serv.Login("admin", "admin") == true);
	assert(serv.GetUsername() == "admin");
	assert(serv.currentUser==serv.searchUser("admin"));
	assert(serv.listUsers()[counterUsers].username == "John");
	serv.addMovie("Title", 420, "Genre", 69, "www.gogu.com");
	serv.addMovie("Title", 420, "Genre", 69, "www.gogu.com");
	assert(serv.listMovies()[counterMovies].title == "Title");
	assert(serv.searchMovie("Title") == serv.listMovies()[counterMovies]);
	assert(serv.searchMovieByUUID(serv.listMovies()[counterMovies].uuid) == serv.listMovies()[counterMovies]);
	assert(serv.currentUser.uuid == serv.searchUser("admin").uuid);
	assert(serv.searchMovieByUUID(" ")==movie());
	assert(serv.searchUser(" ")==user());
	assert(serv.searchMovie(" ")==movie());
	serv.updateCurrentUser();
	serv.updateMovieGenre("Title", "Genre1");
	serv.updateMovieGenre("Title1", "Genre1");
	assert(serv.listMovies()[counterMovies].genre == "Genre1");
	serv.updateMovieLikes("Title", 421);
	serv.updateMovieLikes("Title1", 421);
	assert(serv.listMovies()[counterMovies].likes == 421);
	serv.likeMovie(counterMovies);
	assert(serv.listMovies()[counterMovies].likes == 422);
	serv.updateMovieTrailer("Title", "www.gogu1.co");
	serv.updateMovieTrailer("Title1", "www.gogu1.co");
	assert(serv.listMovies()[counterMovies].trailer == "www.gogu1.co");
	serv.updateMovieYear("Title1", 421);
	serv.updateMovieYear("Title", 421);
	assert(serv.listMovies()[counterMovies].year == 421);
	serv.updateMovieTitle("Title", "Title1");
	serv.updateMovieTitle("Title", "Title1");
	assert(serv.listMovies()[counterMovies].title == "Title1");
	serv.removeMovie("Title1");
	serv.removeMovie("Title1");
	assert(serv.listMovies().size() == counterMovies);
	serv.removeUser("John");
	serv.removeUser("John");
	assert(serv.listUsers().size() == counterUsers);

}
void TEST_SERVICE_USER() {
	service serv;
	movie movie1;
	serv.Login("test", "test");
	serv.addMovie("Title", 420, "Genre", 69, "www.gogu.com");
	assert(serv.getWatchlist().size()==0);
	serv.addMovieToWatchlist(serv.listMovies().back());
	assert(serv.getWatchlist().size() == 1);
	serv.checkMovieWatchlist(serv.listMovies().back());
	serv.removeMovieWatchlist(0);
	assert(serv.getWatchlist().size() == 0);
	serv.checkMovieWatchlist(serv.listMovies().back());
}
void TEST_ALL() {
	TEST_REPO();
	TEST_SERVICE_ADMIN();
	TEST_SERVICE_USER();
}
