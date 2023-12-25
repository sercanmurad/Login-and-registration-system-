#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// User structure to store user information
struct User {
    string username;
    string password;
};

// Function declarations
void registerforUser();
bool loginUser();

// Global vector to store registered users
vector<User> users;

// Function to save users to a file
void saveUsersToFile() {
    ofstream file("users.txt");
    for (const User& user : users) {
        file << user.username << " " << user.password << "\n";
    }
    file.close();
}

// Function to load users from a file
void loadUsersFromFile() {
    ifstream file("users.txt");
    if (file.is_open()) {
        while (!file.eof()) {
            User user;
            file >> user.username >> user.password;
            if (!user.username.empty() && !user.password.empty()) {
                users.push_back(user);
            }
        }
        file.close();
    }
}

int main() {
    loadUsersFromFile();

    int choice;
    do {
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser()) {
                    cout << "Login successful!\n";
                } else {
                    cout << "Login failed. Invalid username or password.\n";
                }
                break;
            case 3:
                saveUsersToFile();
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}

void registerUser() {
    User newUser;
    cout << "Enter username: ";
    cin >> newUser.username;

    // Check if the username already exists
    for (const User& user : users) {
        if (user.username == newUser.username) {
            cout << "Username already exists. Please choose a different one.\n";
            return;
        }
    }

    cout << "Enter password: ";
    cin >> newUser.password;

    // Add the new user to the vector
    users.push_back(newUser);
    cout << "Registration successful!\n";
}

bool loginUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Check if the username and password match
    for (const User& user : users) {
        if (user.username == username && user.password == password) {
            return true; // Login successful
        }
    }

    return false; // Login failed
}

