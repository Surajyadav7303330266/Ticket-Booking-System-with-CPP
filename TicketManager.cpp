
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

struct Ticket {
    string name;
    int age;
    string movie;
    string seat;
    string ticketNumber;
};

// Convert text to lowercase for case-insensitive searching
string toLowerCase(string text) {
    transform(text.begin(), text.end(), text.begin(),
              [](unsigned char c) {
                  return tolower(c);
              });
    return text;
}

// Read all saved tickets from the file
vector<Ticket> loadTickets() {
    vector<Ticket> tickets;
    ifstream file("tickets.txt");

    Ticket t;
    string ageText;

    while (getline(file, t.name, '|')) {
        if (!getline(file, ageText, '|') ||
            !getline(file, t.movie, '|') ||
            !getline(file, t.seat, '|') ||
            !getline(file, t.ticketNumber)) {
            break;
        }

        try {
            t.age = stoi(ageText);
            tickets.push_back(t);
        } catch (...) {
            continue;
        }
    }

    return tickets;
}

// Display a single ticket
void displayTicket(const Ticket& t) {
    cout << "\n-----------------------------\n";
    cout << "Name         : " << t.name << '\n';
    cout << "Age          : " << t.age << '\n';
    cout << "Movie        : " << t.movie << '\n';
    cout << "Seat         : " << t.seat << '\n';
    cout << "Ticket Number: " << t.ticketNumber << '\n';
    cout << "-----------------------------\n";
}

int main() {
    int choice;

    do {
        cout << "\n===== PVR TICKET MANAGEMENT =====\n";
        cout << "1. View all tickets\n";
        cout << "2. Search by customer name\n";
        cout << "3. Search by ticket number\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid menu number.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vector<Ticket> tickets = loadTickets();

        if (choice == 1) {
            if (tickets.empty()) {
                cout << "No tickets found.\n";
            } else {
                cout << "\nTotal tickets: "
                     << tickets.size() << '\n';

                for (const Ticket& t : tickets) {
                    displayTicket(t);
                }
            }
        }

        else if (choice == 2) {
            string searchName;
            bool found = false;

            cout << "Enter customer name to search: ";
            getline(cin, searchName);

            for (const Ticket& t : tickets) {
                if (toLowerCase(t.name).find(
                        toLowerCase(searchName))
                    != string::npos) {
                    displayTicket(t);
                    found = true;
                }
            }

            if (!found) {
                cout << "No matching customer found.\n";
            }
        }

        else if (choice == 3) {
            string searchNumber;
            bool found = false;

            cout << "Enter ticket number: ";
            getline(cin, searchNumber);

            for (const Ticket& t : tickets) {
                if (toLowerCase(t.ticketNumber) ==
                    toLowerCase(searchNumber)) {
                    displayTicket(t);
                    found = true;
                }
            }

            if (!found) {
                cout << "Ticket number not found.\n";
            }
        }

        else if (choice == 4) {
            cout << "Exiting Ticket Manager. Goodbye!\n";
        }

        else {
            cout << "Invalid choice. Select 1-4.\n";
        }

    } while (choice != 4);

    return 0;
}
