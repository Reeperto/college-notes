/*********************************************************
 * AUTHOR           : Eli Griffiths
 * Lab #15          : Movie Data
 * CLASS            : CS 002
 * SECTION          : Asynchronous
 * Due Date         : 11/22/23
 *********************************************************/
#include <fstream>
#include <iostream>
using namespace std;
/*********************************************************
 *
 * Movie Data
 *
 * ________________________________________________________
 *
 * Reads in movie data and prints it
 *
 * ________________________________________________________
 * INPUT:
 *
 * OUTPUT:
 *
 *********************************************************/

struct MovieData
{
    string title;
    string director;
    int year;
    int running_time;
};

void printMovieData(const MovieData &m);

int main()
{
    // OUTPUT - Class header information
    // cout << "*****************************************\n";
    // cout << " Programmed by  : Eli Griffiths\n";
    // cout << " Student ID     : 10680823\n";
    // cout << " CS002          : Asynchronous\n";
    // cout << " Lab #15        : Movie Data\n";
    // cout << "*****************************************\n";
    // cout << "\n";

    MovieData input_movie; // INPUT - The user provided movie data
    ifstream input_file;   // INPUT - A file containing movie data
    MovieData movies[12];  // PROCESSING - Array of movies

    MovieData appolo = {"Apollo 13", "Ron Howard", 1995, 140};

    // INPUT - Get movie information from the user and store into the input
    // struct fields
    cout << "Enter Title: ";
    getline(cin, input_movie.title);
    cout << "\n";

    cout << "Enter Director: ";
    getline(cin, input_movie.director);
    cout << "\n";

    cout << "Enter Year Released: ";
    cin >> input_movie.year;
    cout << "\n";

    cout << "Enter Running Time (in minutes): ";
    cin >> input_movie.running_time;
    cout << "\n";

    // PROCESSING - Store the hard coded movie data and input data into the
    // array of movie data structs
    movies[0] = appolo;
    movies[1] = input_movie;

    // INPUT - Read in the movie data from the input text file
    input_file.open("movies.txt");
    for (int i = 2; i < 12; ++i)
    {
        getline(input_file, movies[i].title);
        getline(input_file, movies[i].director);
        input_file >> movies[i].year;
        input_file >> movies[i].running_time;
        input_file.ignore(10, '\n');
        input_file.ignore(10, '\n');
    }

    // OUTPUT - Pretty print the movie data entries in the array
    for (int i = 0; i < 12; ++i)
    {
        printMovieData(movies[i]);
        cout << "\n";
    }

    return 0;
}

/*********************************************************
 * FUNCTION printMovieData
 * ________________________________________________________
 * Pretty prints a movie data struct's info
 * ________________________________________________________
 * PRE-CONDITIONS
 *  m: The movie data with all data fields filled out
 *
 * POST-CONDITIONS
 *  none
 *********************************************************/
void printMovieData(
    const MovieData &m) // IN - The movie data struct to output
{
    cout << "Title: " << m.title << "\n";
    cout << "Director: " << m.director << "\n";
    cout << "Year released: " << m.year << "\n";
    cout << "Running Time: " << m.running_time << "\n";
}
