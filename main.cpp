#include <iostream>
#include <vector>
#include <regex>

static const int MAX_SQUARE = 1000000;
static const int MIN_SQUARE = 0;
static const int MAX_NUM_OF_BEDROOMS = 20;
static const int MIN_NUM_OF_BEDROOMS = 0;
static const int MIN_NUM_OF_SANATORIUM_EDGES = 0;
static const int MAX_NUM_OF_SANATORIUM_EDGES = 20;
static const int MAX_NUM_OF_TIME_TO_STATION = 10000;
static const char *const POSITIVE_INPUT = "yes";
static const char *const NEGATIVE_INPUT = "no";
static const int MIN_NUM_OF_COST = 0;
static const char *const WRONG_INPUT = "Wrong input! Try again";
static const int MIN_NUM_OF_TIME_TO_STATION = 0;
using namespace std;

struct Target_Estate {
    double square_of_plot;
    int number_of_bedrooms;
    int number_of_sanatorium_edges;
    int time_to_the_nearest_metro_station;
    bool is_commercial;
};

struct Real_Estate {
    double square_of_plot;
    int number_of_bedrooms;
    int number_of_sanatorium_edges;
    int time_to_the_nearest_metro_station;
    bool is_commercial;
    double cost;

    void print() const {
        cout << "square : " << square_of_plot << endl;
        cout << "bedrooms : " << number_of_bedrooms << endl;
        cout << "san_edges : " << number_of_sanatorium_edges << endl;
        cout << "time : " << time_to_the_nearest_metro_station << endl;
        cout << "is_commercial : " << is_commercial << endl;
        cout << "cost : " << cost << endl;
    }
};

void clear_console() {
    #if (__APPLE__ || __Linux__)
        system("clear");
    #elif _WIN32
        system("cls");
    #endif
}

// The next function of code checks to see if cin failed, then it clears the stream
void clear_input_stream() {
    cin.clear();
    cin.ignore(1000, '\n');
}

bool check_number_validity(const string &s) {
    string reg = R"([+-]?\d+(\.\d+)?)";
    regex rx(reg);

    return regex_match(s.c_str(), rx);
}

string read_input_string() {
    string input;
    cin >> input;
    return input;
}

int string_to_int(const string &str) {
    if (check_number_validity(str)) return stoi(str);
    clear_input_stream();
    return -1;
}

double string_to_double(const string &str) {
    if (check_number_validity(str)) return stod(str);
    clear_input_stream();
    return -1;
}

bool is_cost_ok(double cost) {
    return (cost >= MIN_NUM_OF_COST);
}

bool is_commercial_ok(const string &statement) {
    return (statement == POSITIVE_INPUT || statement == NEGATIVE_INPUT);
}

bool is_time_to_the_nearest_metro_station_ok(int time_to_the_nearest_metro_station) {
    return (time_to_the_nearest_metro_station >= MIN_NUM_OF_TIME_TO_STATION
            && time_to_the_nearest_metro_station < MAX_NUM_OF_TIME_TO_STATION);
}

bool is_number_of_sanatorium_edges_ok(int number_of_sanatorium_edges) {
    return (number_of_sanatorium_edges >= MIN_NUM_OF_SANATORIUM_EDGES
            && number_of_sanatorium_edges < MAX_NUM_OF_SANATORIUM_EDGES);
}

bool is_number_of_bedrooms_ok(int number_of_bedrooms) {
    return (number_of_bedrooms >= MIN_NUM_OF_BEDROOMS && number_of_bedrooms < MAX_NUM_OF_BEDROOMS);
}

bool is_square_ok(double square) {
    return (square >= MIN_SQUARE && square < MAX_SQUARE);
}

int read_int() {
    return string_to_int(read_input_string());
}

double read_double() {
    return string_to_double(read_input_string());
}

double read_cost() {
    cout << "\nEnter cost(lungs integer)" << endl;
    double cost;
    while (true) {
        cost = read_double();
        if (is_cost_ok(cost)) return cost;
        else cout << WRONG_INPUT << endl;
    }
}

bool read_is_commercial() {
    cout << "\nEnter is it commercial ?( \"yes\" OR \"no\" only )" << endl;
    string statement;
    while (true) {
        statement = read_input_string();
        if (is_commercial_ok(statement)) return statement == POSITIVE_INPUT;
        else cout << WRONG_INPUT << endl;
    }
}


int read_time_to_the_nearest_metro_station() {
    cout << "\nEnter a time to the nearest metro station( integer max 10_000 )" << endl;
    int time_to_the_nearest_metro_station;
    while (true) {
        time_to_the_nearest_metro_station = read_int();
        if (is_time_to_the_nearest_metro_station_ok(time_to_the_nearest_metro_station))
            return time_to_the_nearest_metro_station;
        else cout << WRONG_INPUT << endl;
    }
}


int read_number_of_sanatorium_edges() {
    cout << "\nEnter a number of sanatorium edges ( integer max 20)" << endl;
    int number_of_sanatorium_edges;
    while (true) {
        number_of_sanatorium_edges = read_int();
        if (is_number_of_sanatorium_edges_ok(number_of_sanatorium_edges))
            return number_of_sanatorium_edges;
        else cout << WRONG_INPUT << endl;
    }
}

int read_number_of_bedrooms() {
    cout << "\nEnter a number of bedrooms ( integer )" << endl;
    int number_of_bedrooms;
    while (true) {
        number_of_bedrooms = read_int();
        if (is_number_of_bedrooms_ok(number_of_bedrooms))
            return number_of_bedrooms;
        else cout << WRONG_INPUT << endl;
    }
}

double read_square() {
    cout << "\nEnter square of plot ( lungs number in square metres)" << endl;
    double square_of_plot;
    while (true) {
        square_of_plot = read_double();
        if (is_square_ok(square_of_plot)) return square_of_plot;
        else cout << WRONG_INPUT << endl;
    }
}

vector<Real_Estate> real_estates;

Target_Estate read_target_estate() {
    Target_Estate target_estate{};
    double square_of_plot = read_square();
    target_estate.square_of_plot = square_of_plot;
    if (square_of_plot == 0) return target_estate;

    target_estate.number_of_bedrooms = read_number_of_bedrooms();
    target_estate.number_of_sanatorium_edges = read_number_of_sanatorium_edges();
    target_estate.time_to_the_nearest_metro_station = read_time_to_the_nearest_metro_station();
    target_estate.is_commercial = read_is_commercial();


    return target_estate;
}

Real_Estate read_estate() {
    Real_Estate real_estate{};
    double square_of_plot = read_square();
    real_estate.square_of_plot = square_of_plot;
    if (square_of_plot == 0) return real_estate;

    real_estate.number_of_bedrooms = read_number_of_bedrooms();
    real_estate.number_of_sanatorium_edges = read_number_of_sanatorium_edges();
    real_estate.time_to_the_nearest_metro_station = read_time_to_the_nearest_metro_station();
    real_estate.is_commercial = read_is_commercial();
    real_estate.cost = read_cost();

    return real_estate;
}


void menu() {
    while (true) {
        Real_Estate real_estate{};
        real_estate = read_estate();
        if (real_estate.square_of_plot == 0) break;

        real_estates.push_back(real_estate);
        clear_console();
        real_estate.print();
    }

    Target_Estate target_estate{};
    target_estate = read_target_estate();
    if (target_estate.square_of_plot == 0) system("exit");


}

int main() {
    menu();
    return 0;
}
