#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

int toInt(const string& s) {
    if (s.empty()) {
        throw invalid_argument("Invalid string");
    }
    for (size_t i = 0; i < s.length(); ++i) {
        if (i == 0 && (s[i] == '-' || s[i] == '+')) {
            continue;
        }
        if (s[i] < '0' || s[i] > '9') {
            throw invalid_argument("Invalid string");
        }
    }
    return stoi(s);
}

void checkPassword(const string& password) {
    if (password.length() < 8) {
        throw invalid_argument("Password must be at least 8 characters long");
    }
    bool hasDigit = false;
    for (size_t i = 0; i < password.length(); ++i) {
        if (password[i] >= '0' && password[i] <= '9') {
            hasDigit = true;
            break;
        }
    }
    if (!hasDigit) {
        throw invalid_argument("Password must contain at least one digit");
    }
}

class AgeException : public exception {
private:
    int age;
    string message;
public:
    AgeException(int a) : age(a) {
        message = "Age " + to_string(age) + " is not allowed to vote (must be at least 18)";
    }
    const char* what() const noexcept override {
        return message.c_str();
    }
};

void vote(string candidate, int age) {
    if (age < 18) {
        throw AgeException(age);
    }
    cout << "Voted for " << candidate << " successfully!" << endl;
}

int main() {
    try {
        cout << toInt("12345") << endl;
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }

    try {
        checkPassword("pass123");
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }

    try {
        vote("Candidate X", 16);
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }

}