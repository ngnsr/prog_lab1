#include <iostream>
#include <vector>
#include <regex>

static const int MAX_SQUARE = 10000;
static const int MIN_SQUARE = 0;
static const int MAX_NUM_OF_BEDROOMS = 20;
static const int MIN_NUM_OF_BEDROOMS = 1;
static const int MAX_NUM_OF_SAN_EDGES = 20;
static const int MIN_NUM_OF_SAN_EDGES = 1;
static const int MAX_MINUTES_TO_METRO = 10000;
static const int MIN_MINUTES_TO_METRO = 1;
static const char *const POSITIVE_INPUT = "yes";
static const char *const NEGATIVE_INPUT = "no";
static const int MIN_NUM_OF_COST = 1;
static const char *const WRONG_INPUT = "Wrong input! Try again";

static const double RESIDENTIAL_SQUARE_MULTIPLIER = 0.5;
static const double RESIDENTIAL_METRO_MULTIPLIER = 0.25;
static const double RESIDENTIAL_BEDROOMS_MULTIPLIER = 0.15;
static const double RESIDENTIAL_SAN_EDGES_MULTIPLIER = 0.1;

static const double COMMERCIAL_SQUARE_MULTIPLIER = 0.5;
static const double COMMERCIAL_METRO_MULTIPLIER = 0.25;
static const double COMMERCIAL_SAN_EDGES_MULTIPLIER = 0.15;
static const double COMMERCIAL_BEDROOMS_MULTIPLIER = 0.1;

static const int MINUTES_IN_HOUR = 60;
static const double COMMERCIAL_MULTIPLIER =
        COMMERCIAL_METRO_MULTIPLIER + COMMERCIAL_BEDROOMS_MULTIPLIER + COMMERCIAL_SAN_EDGES_MULTIPLIER +
        COMMERCIAL_SQUARE_MULTIPLIER;
static const double RESIDENTIAL_MULTIPLIER =
        RESIDENTIAL_SQUARE_MULTIPLIER + RESIDENTIAL_BEDROOMS_MULTIPLIER + RESIDENTIAL_SAN_EDGES_MULTIPLIER +
        RESIDENTIAL_METRO_MULTIPLIER;
using namespace std;

struct Target_Estate {
    double square;
    int num_of_bedrooms;
    int num_of_san_edges;
    int time_to_metro;
    bool is_commercial;
};

struct Real_Estate {
    double square;
    int num_of_bedrooms;
    int num_of_san_edges;
    int time_to_metro;
    bool is_commercial;
    double cost;
};

struct {
    int amount_of_estate;
    double total_square;
    int total_num_of_bedrooms;
    int total_num_of_san_edges;
    int total_time_to_metro;
    double total_cost;
} commercial_statistic, residential_statistic;

void read_additional_estates(const Target_Estate &target_estate);

// The next function of code checks to see if cin failed, then it clears the stream
void clear_input_stream() {
    cin.clear();
    cin.sync();
//    cin.ignore(1000, '\n');
}


bool check_int_num_validity(const string &s) {
    string reg = R"([+-]?\d+)";
    regex rx(reg);

    return regex_match(s.c_str(), rx) && !s.empty();
}

bool check_double_num_validity(const string &s) {
    string reg = R"([+-]?\d+(\.\d+)?)";
    regex rx(reg);

    return regex_match(s.c_str(), rx) && !s.empty();
}

string read_line() {
    string line;
    getline(cin, line);
    return line;
}

int string_to_int(const string &str) {
    if (check_int_num_validity(str)) return stoi(str);
    clear_input_stream();
    return -1;
}

double string_to_double(const string &str) {
    if (check_double_num_validity(str)) return stod(str);
    clear_input_stream();
    return -1;
}

bool is_cost_ok(double cost) {
    return (cost >= MIN_NUM_OF_COST);
}

bool is_commercial_ok(const string &statement) {
    return (statement == POSITIVE_INPUT || statement == NEGATIVE_INPUT);
}

bool is_time_to_metro_ok(int time_to_metro) {
    return (time_to_metro >= MIN_MINUTES_TO_METRO
            && time_to_metro < MAX_MINUTES_TO_METRO);
}

bool is_num_of_san_edges_ok(int num_of_san_edges) {
    return (num_of_san_edges >= MIN_NUM_OF_SAN_EDGES
            && num_of_san_edges < MAX_NUM_OF_SAN_EDGES);
}

bool is_num_of_bedrooms_ok(int num_of_bedrooms) {
    return (num_of_bedrooms >= MIN_NUM_OF_BEDROOMS && num_of_bedrooms < MAX_NUM_OF_BEDROOMS);
}

bool is_square_ok(double square) {
    return (square >= MIN_SQUARE && square < MAX_SQUARE);
}

int read_int() {
    return string_to_int(read_line());
}

double read_double() {
    return string_to_double(read_line());
}

double read_cost() {
    cout << "\nEnter cost( 1 <= n < 10_000)" << endl << "> ";
    double cost;
    while (true) {
        cost = read_double();
        if (is_cost_ok(cost)) return cost;
        else cerr << WRONG_INPUT << endl;
    }
}

bool read_is_commercial() {
    cout << "\nEnter is it commercial ?( \"yes\" OR \"no\" only )" << endl << "> ";
    string statement;
    while (true) {
        statement = read_line();
        if (is_commercial_ok(statement)) return statement == POSITIVE_INPUT;
        else cerr << WRONG_INPUT << endl;
    }
}

int read_time_to_metro() {
    cout << "\nEnter a minutes to the nearest metro station( 1 <= n < 10_000 )" << endl << "> ";
    int time_to_metro;
    while (true) {
        time_to_metro = read_int();
        if (is_time_to_metro_ok(time_to_metro))
            return time_to_metro;
        else cerr << WRONG_INPUT << endl;
    }
}


int read_num_of_san_edges() {
    cout << "\nEnter a number of sanatorium edges ( 1 <= n < 20 )" << endl << "> ";
    int num_of_san_edges;
    while (true) {
        num_of_san_edges = read_int();
        if (is_num_of_san_edges_ok(num_of_san_edges))
            return num_of_san_edges;
        else cerr << WRONG_INPUT << endl;
    }
}


int read_num_of_bedrooms() {
    cout << "\nEnter a number of bedrooms ( 1 <= n < 20 )" << endl << "> ";
    int num_of_bedrooms;
    while (true) {
        num_of_bedrooms = read_int();
        if (is_num_of_bedrooms_ok(num_of_bedrooms))
            return num_of_bedrooms;
        else cerr << WRONG_INPUT << endl;
    }
}

double read_square() {
    cout << "\nEnter square of plot ( 0 <= n )" << endl << "> ";
    double square;
    while (true) {
        square = read_double();
        if (is_square_ok(square)) return square;
        else cerr << WRONG_INPUT << endl;
    }
}

vector<Real_Estate> real_estates;

void update_statistic(Real_Estate real_estate) {
    if (real_estate.is_commercial) {
        commercial_statistic.total_square += real_estate.square;
        commercial_statistic.total_num_of_bedrooms += real_estate.num_of_bedrooms;
        commercial_statistic.total_num_of_san_edges += real_estate.num_of_san_edges;
        commercial_statistic.total_time_to_metro += real_estate.time_to_metro;
        commercial_statistic.total_cost += real_estate.cost;
        commercial_statistic.amount_of_estate++;
    } else {
        residential_statistic.total_square += real_estate.square;
        residential_statistic.total_num_of_bedrooms += real_estate.num_of_bedrooms;
        residential_statistic.total_num_of_san_edges += real_estate.num_of_san_edges;
        residential_statistic.total_time_to_metro += real_estate.time_to_metro;
        residential_statistic.total_cost += real_estate.cost;
        residential_statistic.amount_of_estate++;
    }

}

void read_estates() {
    cout << "Reading" << endl;
    Real_Estate real_estate{};
    while (true) {
        double square = read_square();
        real_estate.square = square;
        if (square == 0) break;
        real_estate.num_of_bedrooms = read_num_of_bedrooms();
        real_estate.num_of_san_edges = read_num_of_san_edges();
        real_estate.time_to_metro = read_time_to_metro();
        real_estate.is_commercial = read_is_commercial();
        real_estate.cost = read_cost();
        update_statistic(real_estate);
        real_estates.push_back(real_estate);
    }
}

double predicate_commercial_estate(Target_Estate target_estate) {
    double average_cost_of_square,
            average_price_of_bedrooms,
            average_price_of_san_edges;
    double total_cost;
    double price_for_square,
            price_for_bedrooms,
            price_for_san_edges,
            price_for_time_to_metro;
    int total_time_to_metro;

    total_cost = commercial_statistic.total_cost;
    average_cost_of_square = total_cost / commercial_statistic.total_square;
    average_price_of_bedrooms = total_cost / commercial_statistic.total_num_of_bedrooms;
    average_price_of_san_edges = total_cost / commercial_statistic.total_num_of_san_edges;
    total_time_to_metro = commercial_statistic.total_time_to_metro;

    price_for_square = COMMERCIAL_SQUARE_MULTIPLIER * average_cost_of_square * target_estate.square;
    price_for_bedrooms = COMMERCIAL_BEDROOMS_MULTIPLIER * average_price_of_bedrooms * target_estate.num_of_bedrooms;
    price_for_san_edges = COMMERCIAL_SAN_EDGES_MULTIPLIER * average_price_of_san_edges * target_estate.num_of_san_edges;
    price_for_time_to_metro =
            COMMERCIAL_METRO_MULTIPLIER * 2 * (price_for_bedrooms + price_for_square + price_for_san_edges);

    if (target_estate.time_to_metro > total_time_to_metro || target_estate.time_to_metro > MINUTES_IN_HOUR) {
        price_for_time_to_metro = 0;
    } else if (target_estate.time_to_metro != total_time_to_metro) {
        price_for_time_to_metro *= 1 - target_estate.time_to_metro / (double) total_time_to_metro;
    }

    double cost = price_for_square + price_for_bedrooms + price_for_san_edges + price_for_time_to_metro;
    cost /= COMMERCIAL_MULTIPLIER;

    return cost;
}

double predicate_residential_estate(Target_Estate target_estate) {
    double average_cost_of_square,
            average_price_of_bedrooms,
            average_price_of_san_edges;
    double total_cost;
    double price_for_square,
            price_for_bedrooms,
            price_for_san_edges,
            price_for_time_to_metro;
    int total_time_to_metro;

    total_cost = residential_statistic.total_cost;
    average_cost_of_square = total_cost / residential_statistic.total_square;
    average_price_of_bedrooms = total_cost / residential_statistic.total_num_of_bedrooms;
    average_price_of_san_edges = total_cost / residential_statistic.total_num_of_san_edges;
    total_time_to_metro = residential_statistic.total_time_to_metro;

    price_for_square = RESIDENTIAL_SQUARE_MULTIPLIER * average_cost_of_square * target_estate.square;
    price_for_bedrooms = RESIDENTIAL_BEDROOMS_MULTIPLIER * average_price_of_bedrooms * target_estate.num_of_bedrooms;
    price_for_san_edges =
            RESIDENTIAL_SAN_EDGES_MULTIPLIER * average_price_of_san_edges * target_estate.num_of_san_edges;
    price_for_time_to_metro =
            RESIDENTIAL_METRO_MULTIPLIER * 2 * (price_for_bedrooms + price_for_square + price_for_san_edges);

    if (target_estate.time_to_metro > total_time_to_metro || target_estate.time_to_metro > MINUTES_IN_HOUR) {
        price_for_time_to_metro = 0;
    } else if (target_estate.time_to_metro != total_time_to_metro) {
        price_for_time_to_metro *= 1 - target_estate.time_to_metro / (double) total_time_to_metro;
    }

    double cost = price_for_square + price_for_bedrooms + price_for_san_edges + price_for_time_to_metro;
    cost /= RESIDENTIAL_MULTIPLIER;

    return cost;
}

double predicate_input(Target_Estate target_estate) {
    read_additional_estates(target_estate);
    if (target_estate.is_commercial) {
        return predicate_commercial_estate(target_estate);
    } else {
        return predicate_residential_estate(target_estate);
    }

}

void read_additional_estates(const Target_Estate &target_estate) {
    while ((target_estate.is_commercial && commercial_statistic.amount_of_estate == 0) ||
           (!target_estate.is_commercial && residential_statistic.amount_of_estate == 0)) {
        cout << "More information is needed for forecasting" << endl;
        read_estates();
    }
}

void read_and_predicate_target_estates() {
    cout << "Predicating" << endl;
    cout << "Enter \"0\" in the square to end the program" << endl;
    while (true) {
        Target_Estate estate{};
        double square = read_square();
        estate.square = square;
        if (square == 0) break;

        estate.num_of_bedrooms = read_num_of_bedrooms();
        estate.num_of_san_edges = read_num_of_san_edges();
        estate.time_to_metro = read_time_to_metro();
        estate.is_commercial = read_is_commercial();

        cout << "Predicted cost : " << predicate_input(estate);
    }
}

int main() {
    read_estates();
    read_and_predicate_target_estates();
    return 0;
}
