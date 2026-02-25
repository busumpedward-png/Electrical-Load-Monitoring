#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

const int MAX_APPLIANCES = 100;

struct Appliance {
    string name;
    double watts;
    double hours;
};

void clearBadInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readInt(const string &prompt) {
    while (true) {
        cout << prompt;
        int x;
        if (cin >> x) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
        cout << "Invalid number. Try again.\n";
        clearBadInput();
    }
}

double readDouble(const string &prompt) {
    while (true) {
        cout << prompt;
        double x;
        if (cin >> x) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
        cout << "Invalid number. Try again.\n";
        clearBadInput();
    }
}

string readNonEmptyLine(const string &prompt) {
    while (true) {
        cout << prompt;
        string s;
        getline(cin, s);
        if (s.size() > 0) return s;
        cout << "Name must not be empty. Try again.\n";
    }
}

double readPositiveDouble(const string &prompt) {
    while (true) {
        double v = readDouble(prompt);
        if (v > 0) return v;
        cout << "Value must be greater than 0.\n";
    }
}

double readHours(const string &prompt) {
    while (true) {
        double h = readDouble(prompt);
        if (h >= 0 && h <= 24) return h;
        cout << "Hours must be between 0 and 24.\n";
    }
}

void showMenu() {
    cout << "\n========== ELECTRICAL LOAD MONITOR ==========\n";
    cout << "1. Register appliance\n";
    cout << "2. View appliances\n";
    cout << "3. Search appliance\n";
    cout << "4. Billing\n";
    cout << "5. Save appliances\n";
    cout << "6. Exit\n";
    cout << "===========================================\n";
}

void registerAppliance(Appliance arr[], int &count) {
    if (count >= MAX_APPLIANCES) {
        cout << "Storage full.\n";
        return;
    }

    Appliance a;
    a.name  = readNonEmptyLine("Enter appliance name: ");
    a.watts = readPositiveDouble("Enter power rating (watts > 0): ");
    a.hours = readHours("Enter daily usage hours (0-24): ");

    arr[count] = a;
    count++;
    cout << "Appliance added.\n";
}

void viewAppliances(Appliance arr[], int count) {
    if (count == 0) {
        cout << "No appliances registered.\n";
        return;
    }

    cout << left << setw(4) << "#"
         << setw(25) << "Name"
         << setw(12) << "Watts"
         << setw(12) << "Hours/day" << "\n";
    cout << "-------------------------------------------------\n";

    for (int i = 0; i < count; i++) {
        cout << left << setw(4) << (i + 1)
             << setw(25) << arr[i].name
             << setw(12) << arr[i].watts
             << setw(12) << arr[i].hours << "\n";
    }
}

int main() {
    Appliance appliances[MAX_APPLIANCES];
    int count = 0;

    cout << "Electrical Load Monitoring & Billing System\n";

    while (true) {
        showMenu();
        int choice = readInt("Choose (1-6): ");

        switch (choice) {
            case 1: registerAppliance(appliances, count); break;
            case 2: viewAppliances(appliances, count); break;
            case 3: cout << "Search appliance (coming soon)\n"; break;
            case 4: cout << "Billing (coming soon)\n"; break;
            case 5: cout << "Save appliances (coming soon)\n"; break;
            case 6: cout << "Goodbye!\n"; return 0;
            default: cout << "Invalid choice. Try again.\n"; break;
        }
    }
}
