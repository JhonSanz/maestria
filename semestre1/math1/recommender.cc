
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>
#include <set>
#include "graph.hh"


#define INCLUDE_SOLUTION 1
using namespace std;

/**
 * @brief Movie representation.
 *
 * Every movie has:
 * - @a identifier_ : a unique positive integer.
 * - @a title_ : the title of the movie.
 * - @a releaseDate_ : the date in which the movie was released to the media.
 * - @a cinemaDate_ : the date in which the movie was presented for the first
 *      time to the general public.
 * - @a imdbURL : web page of the movie in the IMDB database.
 */
class Movie {
private:
  string identifier_;
  string title_;
  string releaseDate_;
  string cinemaDate_;
  string imdbURL_;
  vector<string> genre_;

public:
  Movie() {}
  Movie(string identifier, string title, string url) {
    identifier_ = identifier;
    title_ = title;
    imdbURL_ = url;
  }
  void setRleaseDate(string newDate) { releaseDate_ = newDate; }
  void setCinemaDate(string newDate) { cinemaDate_ = newDate; }
  void addGenre(string g) { genre_.push_back(g); }
  string getId() const { return identifier_; }
  const vector<string> getGenres(void) const { return genre_; }
  /**
   * The following method is required for objects of this type to be keys in an
   * unordered_map.
   *
   * You don't have to understand this.
   */
  bool operator==(const Movie& other) const {
    return identifier_ == other.identifier_; /**SOBRECARGA DE OPERADOR*/
  }
};

/**
 * The following code is required for Movie objects to be keys in an
 * unordered_map.
 *
 * You don't have to understand this.
 */
namespace std {
template <>
struct hash<Movie> {
  size_t operator()(const Movie& m) const { return hash<string>()(m.getId()); }/** hash para movies*/
};
}
//------------------------------^ CLASE PELÍCULA ^----------------------------------------------
/**
 * @brief User representation.
 *
 * Every user has:
 * - @a identifier_ : a unique positive integer.
 * - @a age_ : the age of the user.
 * - @a gender_ : the gender of the user: 'M' for male and 'F' for female.
 * - @a occupation_ : the user's ocupation.
 * - @a location_ : user's location.
 */
class User {
private:
  string identifier_;
  int age_;
  char gender_;
  string occupation_;
  string location_;

public:
  User() {}
  User(string identifier, int age, char gender, string occupation,
       string location) {
    identifier_ = identifier;
    age_ = age;
    gender_ = gender;
    occupation_ = occupation;
    location_ = location;
  }
  string getId(void) const { return identifier_; }
  /**
   * The following method is required for objects of this type to be keys in an
   * unordered_map.
   *
   * You don't have to understand this.
   */
  bool operator==(const User& other) const {
    return identifier_ == other.identifier_;
  }
};

/**
 * The following code is required for Movie objects to be keys in an
 * unordered_map.
 *
 * You don't hav to understand this.
 */
namespace std {
template <>
struct hash<User> {
  size_t operator()(const User& u) const { return hash<string>()(u.getId()); }
};
}
//--------------------------------------^ CLASE USUARIO ^------------------------------------------------
/**
 * @brief Represents a calification made by a user on a movie.
 *
 * - @a user_ : the identifier of the user that rated the movie.
 * - @a movie_ : the identifier of the rated movie
 * - @a raiting_ : number between 1 and 5 representing how much the user liked
 *      the movie.
 */
class Rate {
private:
  string user_;
  string movie_;
  int rating_;

public:
  Rate(string user, string movie, int rating) {
    user_ = user;
    movie_ = movie;
    rating_ = rating;
  }

  string getUser(void) const { return user_; }
  string getMovie(void) const { return movie_; }
  int getRating(void) const { return rating_; }
};

//----------------------^ CLASE CALIFICACION, (HECHA POR UN USUARIO A UNA PELÍCULA) ^-------------------------------

#ifdef INCLUDE_SOLUTION
enum class NodeType { USER, MOVIE, GENRE };
#endif
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
/**
* @brief Definition of a node in the recommendation graph.
*/
class Node {
private:
  /**
   * This is the node identifier.
   *
   * If the node represents a user then it matches the user identifier. If
   * representing a movie then is the movie identifier.
   */
  string id_;
#ifdef INCLUDE_SOLUTION
  // Type of the information stored by the node
  NodeType type_;
#endif

public:
  Node(void) {}
  Node(string id) { id_ = id; }

  string getId(void) const { return id_; }
  void setId(string id) { id_ = id; }
#ifdef INCLUDE_SOLUTION
  void setType(NodeType t) { type_ = t; }

  bool isMovie(void) const { return type_ == NodeType::MOVIE; }  //NodeType{ USER, MOVIE, GENRE }. 
  bool isUser(void) const { return type_ == NodeType::USER; }
  bool isGenre(void) const { return type_ == NodeType::GENRE; }
#endif
};

//-----------------^ CLASE NODO, (cada nodo puede ser o usuario, película, género)^--------------------

/**
 * @brief Definition of a particular edge in the graph.
 */
class Edge {
private:
  Node* start_;
  Node* end_;
  int weight_;

public:
  Edge(void) { weight_ = 0; }

  void setStart(Node* s) { start_ = s; }
  void setEnd(Node* e) { end_ = e; }

  Node* getStart(void) const { return start_; }
  Node* getEnd(void) const { return end_; }

  void setWeight(int w) { weight_ = w; }
  int getWeight(void) const { return weight_; }
};

//--------------------------------^ CLASE ARCO ^-----------------------------------------------------

void printHelp(void) {
  cout << "Recommender help:" << endl;
  cout << "\tTo execute the recommendation system you need three files: "
       << endl;
  cout << "\t\t- movies.txt that contains the information about movies."
       << endl;
  cout << "\t\t- users.txt that contains the information about users." << endl;
  cout << "\t\t- ratings.txt that contains the raiting information." << endl;
  cout << "\tThe way to call this program is:" << endl;
  cout << "\t./recommender movies.txt users.txt ratings.txt" << endl;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Reads the file with name @a fileName line by line and returns its
 * contents as a vector.
 *
 * Returns in a vector the contents of the file. Assumes that every line
 * contains information and that the information is separated by '|'. Every line
 * is transformed to a vector of strings. There are as many entries in that
 * vector as strings separated by '|' in the line. All the lines are finally
 * aggregated in a vector.
 */
vector<vector<string>> readFile(string fileName) {
  ifstream input(fileName);
  vector<vector<string>> contents;
  if (!input) {
    cerr << "Error reading " << fileName << endl;
    return contents;
  }
  string line;
  while (getline(input, line)) {
    stringstream ss(line);
    vector<string> lineContents;
    string elem;
    while (getline(ss, elem, '|')) {
      lineContents.push_back(elem);
    }
    contents.push_back(lineContents);
  }
  return contents;
}

//----------------------------^FUNCION PARA LEER UN ARCHIVO ^---------------------------------------
//----------------------------------------------------------------------------------------

#ifdef INCLUDE_SOLUTION
/**
 * @brief Reads the contents of the movies file.
 *
 * Returns a vector<vector<string>>. That is, a two dimensional vector. Every
 * entry in the main vector contains the information of a single movie. Here
 * is the description of the information. Let m of type vector<string> be one of
 * the elements in the returned vector.
 *
 * m[0] : movie identifier
 * m[1] : title
 * m[2] : release date
 * m[3] : video release date
 * m[4] : URL of the movie at IMDB
 * m[5] : Not ussed
 *
 * The next entries in the vector specify the genre of the movie. As a movie
 *can
 * have several genres then there is 1 or 0 for the remining entries.
 * m[6]  -> Action;  m[7]  -> Adventure; m[8] -> Animation;  m[9] -> Children;
 * m[10] -> Comedy;  m[11] -> Crime;     m[12] -> Documentary; m[13] -> Drama;
 * m[14] -> Fantasy; m[15] -> FilmNoir; m[16] -> Horror; m[17] ->  Musical;
 * m[18] -> Mystery; m[19] -> Romance; m[20] -> SciFi; m[21] -> Thriller;
 * m[22] -> War; m[23] -> Western.
 */
vector<Movie> readMovies(string fileName) {
  vector<Movie> movies;
  vector<vector<string>> data = readFile(fileName);
  vector<string> allGenres = {
      "Action",      "Adventure", "Animation", "Children", "Comedy", "Crime",
      "Documentary", "Drama",     "Fantasy",   "FilmNoir", "Horror", "Musical",
      "Mystery",     "Romance",   "SciFi",     "Thriller", "War",    "Western"};

  for (const vector<string>& movieDesc : data) {
    string identifier(movieDesc[0] + "m");
    Movie m(identifier, movieDesc[1], movieDesc[4]);
    for (int i = 6; i <= 23; i++)
      if (movieDesc[i] == "1")
        m.addGenre(allGenres[i - 6]);
      else if (movieDesc[i] == "0") { /* skip */
      } else
        cout << "Unknown spec " << movieDesc[i] << endl;
    movies.push_back(m);
  }
  return movies;
}

//--------------------------^ FUNCIÓN PARA LEER EL ARCHIVO DE PELÍCULAS ^-------------------
/**
 * @brief Reads the contents of the users file.
 *
 * m[0] : user identifier
 * m[1] : age
 * m[2] : gender
 * m[3] : ocupation
 * m[4] : location
 */
vector<User> readUsers(string fileName) {
  vector<User> users;
  vector<vector<string>> data = readFile(fileName);
  for (const vector<string>& userDesc : data) {
    string identifier(userDesc[0] + "u");
    char gender = userDesc[2] == "M" ? 'M' : 'F';
    int age = atoi(userDesc[1].c_str());
    User u(identifier, age, gender, userDesc[3], userDesc[4]);
    users.push_back(u);
  }
  return users;
}

//--------------------------^ FUNCIÓN PARA LEER EL ARCHIVO DE USUARIOS ^-------------------

/**
 * @brief Reads the ratings file.
 *
 * m[0] : user identifier
 * m[1] : movie identifier
 * m[2] : rating
 * m[3] : unused
 */
vector<Rate> readRatings(string fileName) {
  vector<Rate> ratings;
  vector<vector<string>> data = readFile(fileName);
  for (const vector<string>& ratingDesc : data) {
    string userId(ratingDesc[0] + "u");
    string movieId(ratingDesc[1] + "m");
    size_t rate = atoi(ratingDesc[2].c_str());
    Rate r(userId, movieId, rate);
    ratings.push_back(r);
  }
  return ratings;
}

//--------------------------^ FUNCIÓN PARA LEER EL ARCHIVO DE RATINGS ^----------------------------------



Graph<Node, Edge>* createRecommendationGraph(const vector<Movie>& movies,
                                             const vector<User>& users,
                                             const vector<Rate>& ratings) {
  Graph<Node, Edge>* r = new Graph<Node, Edge>();

  // Every user is represented as a node in the graph
  for (const User& u : users) {
    Node* n = r->addNode(u.getId());
    n->setType(NodeType::USER);
  }
  // Every movie is represented as a node in the graph
  for (const Movie& m : movies) {
    Node* n = r->addNode(m.getId());
    n->setType(NodeType::MOVIE);
  }
  // Ratings are represented as edges in the graph
  for (const Rate& c : ratings)
    r->addEdge(c.getUser(), c.getMovie(), c.getRating());
  return r;
}

//-------------^ CREA EL GRAFO de usuarios y peliculas cada uno de estos siendo un nodo ^-------------------------- 
/**------------------ ^ LA CALIFICACIÓN REPRESENTA EL *//*ARCO*//**DENTRO DEL GRAFO ^-------------------------------*/
//------------------------------------------------------------------------------------------------------------------

void graphStats(string s, Graph<Node, Edge>* g) {
  cout << "Statistics for :" << s << endl;
  cout << "\tNodes: " << g->numNodes() << endl;
  cout << "\tEdges: " << g->numEdges() << endl;
}

unordered_map<string, Movie> createIdToMovies(const vector<Movie>& movies) {
  unordered_map<string, Movie> idToMovies;
  for (const Movie& m : movies) idToMovies.insert({m.getId(), m});
  return idToMovies;
}

unordered_map<string, User> createIdToUsers(const vector<User>& users) {
  unordered_map<string, User> idToUsers;
  for (const User& u : users) idToUsers.insert({u.getId(), u});
  return idToUsers;
}
//--------------^ ASOCIA EN UNA TABLA HASH EL IDENTIFICADOR Y LA PELÍCULA-USUARIO ^---------------------------------

unordered_map<User, vector<Movie>>
watchedMovies(const unordered_map<string, Movie>& movies,
              const unordered_map<string, User>& users,
              const vector<Rate>& ratings) {

  unordered_map<User, vector<Movie>> watched;
  for (const Rate& r : ratings) {
    const User& u = users.at(r.getUser());
    const Movie& m = movies.at(r.getMovie());
    watched[u].push_back(m);
  }
  return watched;
}

//--------^ EN UNA TABLA HASH PONE LA INFORMACIÓN DE LAS PELICULAS QUE VIO CADA USUARIO ^----------------------
/**
 * Returns a collection of "good movies".
 *
 * A movie is considered good if it was rated in the interval [lb, ub] by more
 * than @a percentage of the users that watched it.
 */
vector<string> goodMovies(Graph<Node, Edge>* base, int lb, int ub,
                          double percentage) {
  vector<string> good;
  Graph<Node, Edge>* transposed = transpose(base);
  graphStats("Transposed", transposed);
  for (Node* n : transposed->getNodes()) {
    if (n->isMovie()) {
      // Number the times that the movie has been rated
      double timesRated = (double)transposed->outDegree(n);
      // Number of times it obtained a rating in [lb,ub]
      size_t goodRates = 0;
      for (Edge* e : transposed->getEdgesFrom(n))
        if (e->getWeight() >= lb && e->getWeight() <= ub) goodRates++;
      bool isGood = (goodRates / timesRated) >= percentage;
      if (isGood) good.push_back(n->getId());
    }
  }
  return good;
}

//---------------------------------------------------------------------------------------
/** Cada posicion del vector 6 a 23 se sabe que es un género, y la información en esa posición será las veces que se repite ese género */
 
vector<int> goodGenre(Graph<Node, Edge>* g, Node * usuario)
{
	vector<int> GenerosRepetidos;		
	int P = 1;						
	list<Node*> adjacents = g->getAdjacentTo(usuario);			//los adyacentes a un usuario son películas
	for(Node*n : adjacents)                    					//n es una pelicula
	{
		vector<string> aux = n->getGenres();
		for(int i = 6; i <= 23; i++)           					 // géneros
		{
			if(aux[i] == '1')
				GenerosRepetidos[i-6] = aux[i] + 1;
				GenerosRepetidos[24] = GenerosRepetidos[24] + P;
		}
		P++;
	}
	return GenerosRepetidos;
}

vector<bool> majPercent(vector<int> vec, double porcentaje)
{
	vector<bool> aux;
	for(int i = 0; i <= 18; i++)
	{
		if(vec[i] > vec[24]*0.2)
			aux[i] = true;
		else aux[i] = false;
	}
	return aux;
}

vector<vector<string>>  genrePerUser(Graph<Node, Edge> *g, int lb, int ub, double percentaje )
{
	vector<vector<string>> result;
	vector<bool> porcentajes;
	vector<int> calificacionGenero;
	for(Node *n : g->getNodes())
	{
		if(n->isUser())
		{
			for(Edge *e : g->getEdgesFrom(n))
			{
				if (e->getWeight() >= lb && e->getWeight() <= ub) 
				{
					calificacionGenero = goodGenre(g,n);
					porcentajes  =  majPercent(calificacionGenero, percentaje);
					for(int i = 0; i <= 18; i++)
					{
						if(porcentajes[i])
						{
							result[i].push_back(e->getStart()->getId());
						}
					}
				}
			}
		}
	}
	return result;
}

//---------------------------------------------------------------------------------------
/**
 * Creates the Genre graph that associates users with the genres they have
 * watched.
 */
Graph<Node, Edge>*
createGenreGraph(Graph<Node, Edge>* base,
                 const unordered_map<string, User>& users,
                 const unordered_map<string, Movie>& movies) {

  Graph<Node, Edge>* genres = new Graph<Node, Edge>();

  for (Node* n : base->getNodes())
    if (n->isUser()) {
      if (!genres->hasNodeWithId(n->getId())) genres->addNode(n->getId());
      for (Node* m : base->getAdjacentTo(n)) {
        assert(m->isMovie());
        string movieId = m->getId();
        for (const string& g : movies.at(movieId).getGenres()) {
          if (!genres->hasNodeWithId(g)) genres->addNode(g);
          genres->addEdge(n->getId(), g);
        }
      }
    }
  return genres;
}
#endif

int main(int argc, char** argv) { //argc cuantos parametros llama el programa incluyendo el exe,  
  if (argc != 4) {				//argv arreglo de cadenas de caracteres: argv={ ./recommender , movies.txt, users.xt , ratings.txt}
    printHelp();
    return 1;
  }
  string movies(argv[1]);
  string users(argv[2]);
  string ratings(argv[3]);
/*
  cout << "Movie recommender system!!" << endl;
  cout << "Movie file: " << movies << endl;
  cout << "Users file: " << users << endl;
  cout << "Ratings file: " << ratings << endl;
*/
#ifdef INCLUDE_SOLUTION
  vector<Movie> movieData = readMovies(movies);
  cout << "Number of movies: " << movieData.size() << endl;
  vector<User> usersData = readUsers(users);
  cout << "Number of users: " << usersData.size() << endl;
  vector<Rate> ratingsData = readRatings(ratings);
  cout << "Number of ratings: " << ratingsData.size() << endl;

  Graph<Node, Edge>* r =
      createRecommendationGraph(movieData, usersData, ratingsData);/**====================================================*/
  graphStats("Recomendation base", r);

  unordered_map<string, User> idToUser = createIdToUsers(usersData);
  unordered_map<string, Movie> idToMovie = createIdToMovies(movieData);

  for (const string& s : idToMovie.at("1m").getGenres()) {
    cout << s << " ";
  }
  cout << endl;

  Graph<Node, Edge>* genres = createGenreGraph(r, idToUser, idToMovie);
  graphStats("Genres graph", genres);
/*
  vector<string> good = goodMovies(r, 3, 5, 0.7);
  cout << "Good movies: " << good.size() << endl;
 */
#endif
  return 0;
}
