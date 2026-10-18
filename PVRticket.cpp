
#include <iostream>
#include <string>
#include <random>
#include <limits>
#include <fstream>
using namespace std;

int main() {
    string name;
    string movieName[5] = {
        "Pink",
        "Neeraja",
        "Jindagi na milegi dobara",
        "Udaan",
        "Kapoor and Sons"
    };

    string seatType[4] = {
        "Front",
        "General",
        "Prime",
        "Balcony"
    };

    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    string ticketNumber = "";

    int age, movieChoice, seatChoice;
    bool validBooking = false;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, alphabet.size() - 1);

    cout << "===== Welcome to National PVR Cinemas =====\n";

    // Repeat the entire booking process until valid
    while (!validBooking) {

        cout << "\n--- Enter Your Details ---\n";

        cout << "Enter your name: ";
        getline(cin, name);

        // Validate age input
        cout << "Enter your age: ";
        while (!(cin >> age)) {
            cout << "Invalid input! Enter your age in numbers: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (age < 16) {
            cout << "\nYou are not eligible to watch these movies."
                 << "\nMinimum age required is 16."
                 << "\nPlease enter your details again.\n";
            continue;
        }

        // Movie selection
        cout << "\nPlease select your movie:\n";

        for (int i = 0; i < 5; i++) {
            cout << i + 1 << ". " << movieName[i] << endl;
        }

        cout << "Enter your movie choice (1-5): ";

        while (!(cin >> movieChoice)) {
            cout << "Invalid input! Enter a number from 1 to 5: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Seat selection
        cout << "\nPlease select your seat:\n";

        for (int j = 0; j < 4; j++) {
            cout << j + 1 << ". " << seatType[j] << endl;
        }

        cout << "Enter your seat choice (1-4): ";

        while (!(cin >> seatChoice)) {
            cout << "Invalid input! Enter a number from 1 to 4: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Check both selections
        if (movieChoice >= 1 && movieChoice <= 5 &&
            seatChoice >= 1 && seatChoice <= 4) {

            validBooking = true;

        } else {
            cout << "\nWrong selection!"
                 << "\nYou must enter a valid movie and seat number."
                 << "\nPlease enter your ENTIRE details again.\n";
        }
    }

    // Generate ticket number only after valid booking
    for (int i = 0; i < 10; i++) {
        ticketNumber += alphabet[dist(gen)];
    }
    
    // Save ticket details to a file
    ofstream file("tickets.txt", ios::app);

if (file.is_open()) {
    file << name << "|"
         << age << "|"
         << movieName[movieChoice - 1] << "|"
         << seatType[seatChoice - 1] << "|"
         << ticketNumber << "\n";

    file.close();

    cout << "\nTicket saved successfully!\n";
} else {
    cout << "\nError: Could not save ticket details.\n";
}

    // Display ticket details
    cout << "\n===== Your Ticket Details =====\n";
    cout << "Name         : " << name << endl;
    cout << "Age          : " << age << endl;
    cout << "Movie        : " << movieName[movieChoice - 1] << endl;
    cout << "Seat         : " << seatType[seatChoice - 1] << endl;
    cout << "Ticket Number: " << ticketNumber << endl;

    cout << "\nPress Enter to Exit...";
    cin.get();

    return 0;
}
