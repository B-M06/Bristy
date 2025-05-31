#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

const int TOTAL_SEATS = 10;
string seats[TOTAL_SEATS];
string waiting_list[5];
int front = -1, rear = -1;
int hash_table[TOTAL_SEATS];

// Fixed ticket costs for destinations
const vector<int> ticket_costs = {0, 20, 25, 30, 35, 15}; // Index matches countries

struct Edge {
    int src, dest, time;
};

vector<Edge> edges;
vector<string> countries = {"Bangladesh", "USA", "UK", "UAE", "Germany", "India"};

int hashFunc(string name) {
    int hash = 0;
    for (char ch : name) hash += ch;
    return hash % TOTAL_SEATS;
}

void insertToHash(string name, int index) {
    int key = hashFunc(name);
    while (seats[key] != "" && seats[key] != name) {
        key = (key + 1) % TOTAL_SEATS;
    }
    hash_table[key] = index;  // Ensure seat index is correctly stored
}

int searchHash(string name) {
    int key = hashFunc(name);
    int count = 0;

    while (count < TOTAL_SEATS) {
        if (hash_table[key] >= 0 && hash_table[key] < TOTAL_SEATS) {  // Bounds check
            if (seats[hash_table[key]] == name)
                return hash_table[key];
        }
        key = (key + 1) % TOTAL_SEATS;
        count++;
    }

    return -1;
}

bool bellmanFord(int V, int src, int dest, int departure_time) {
    vector<int> dist(V, INT_MAX);
    vector<int> parent(V, -1);
    dist[src] = 0;

    for (int i = 1; i < V; i++) {
        for (Edge e : edges) {
            if (dist[e.src] != INT_MAX && dist[e.src] + e.time < dist[e.dest]) {
                dist[e.dest] = dist[e.src] + e.time;
                parent[e.dest] = e.src;
            }
        }
    }

    if (dist[dest] == INT_MAX) {
        cout << "No path exists.\n";
        return false;
    }

    vector<int> path;
    for (int at = dest; at != -1; at = parent[at])
        path.push_back(at);
    reverse(path.begin(), path.end());

    int landing_time = departure_time + dist[dest];

    cout << "\nFlight Route: ";
    for (int p : path) cout << countries[p] << (p == dest ? "" : " -> ");
    cout << "\nTotal travel time: " << dist[dest] << " hours\n";
    cout << "Departure Time: " << departure_time << ":00\n";
    cout << "Landing Time: " << landing_time << ":00\n";
    cout << "Ticket Cost: $" << ticket_costs[dest] << "\n";

    cout << "\nProceed with booking? (Y/N): ";
    char decision;
    cin >> decision;

    return (decision == 'Y' || decision == 'y'); // If 'N', return false and cancel booking
}

void bookTicket(string name) {
    int src = 0, dest;

    cout << "Available countries with ticket costs:\n";
    for (int i = 1; i < countries.size(); i++)
        cout << i << ": " << countries[i] << " - $" << ticket_costs[i] << endl;

    cout << "Enter destination country ID: ";
    cin >> dest;

    int departure_time;
    cout << "Enter preferred departure time (hour in 24-hour format): ";
    cin >> departure_time;

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clears buffer for safe input

    if (!bellmanFord(countries.size(), src, dest, departure_time)) {
        cout << "Booking cancelled.\n";
        return;
    }

    for (int i = 0; i < TOTAL_SEATS; i++) {
        if (seats[i] == "") {
            seats[i] = name;
            insertToHash(name, i);
            cout << "Seat booked for " << name << " at Seat " << i + 1 << endl;
            return;
        }
    }

    if (rear < 4) {
        if (front == -1) front = 0;
        waiting_list[++rear] = name;
        cout << "All seats full. Added " << name << " to waiting list.\n";
    } else {
        cout << "Booking failed. Waiting list full.\n";
    }
}

void cancelTicket(string name) {
    int index = searchHash(name);

    if (index == -1 || index >= TOTAL_SEATS) { // Bounds check
        cout << "No booking found for " << name << endl;
        return;
    }

    cout << "Cancelled seat for " << name << " at Seat " << index + 1 << endl;
    seats[index] = "";

    if (front != -1 && front <= rear) {
        seats[index] = waiting_list[front];
        insertToHash(waiting_list[front], index);
        cout << "Seat given to " << waiting_list[front] << " from waiting list.\n";
        front++;
        if (front > rear) front = rear = -1;
    }
}

void displaySeats() {
    cout << "\n--- Booked Seats ---\n";
    for (int i = 0; i < TOTAL_SEATS; i++) {
        if (seats[i] != "")
            cout << "Seat " << i + 1 << ": " << seats[i] << endl;
    }

    cout << "\n--- Waiting List ---\n";
    for (int i = front; i <= rear; i++) {
        cout << i - front + 1 << ". " << waiting_list[i] << endl;
    }
}

void initGraph() {
    edges = {
        {0, 1, 14}, {0, 2, 10}, {0, 3, 8}, {0, 4, 12}, {0, 5, 5},
        {1, 2, 6}, {2, 3, 2}, {3, 4, 4}, {4, 5, 3}
    };
}

int main() {
    initGraph();
    fill(begin(hash_table), end(hash_table), -1); // Initialize hash table

    int choice;
    string name;

    while (true) {
        cout << "\n--- Airline Reservation System ---\n";
        cout << "1. Book Ticket\n";
        cout << "2. Cancel Ticket\n";
        cout << "3. Display Seats and Waiting List\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                cout << "Enter passenger name: ";
                getline(cin, name);
                bookTicket(name);
                break;
            case 2:
                cout << "Enter passenger name to cancel: ";
                getline(cin, name);
                cancelTicket(name);
                break;
            case 3:
                displaySeats();
                break;
            case 4:
                cout << "Exiting the system. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

