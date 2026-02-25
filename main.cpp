#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_APPLIANCES = 100;

struct Appliance {
    string name;
    double watts;
    double hours;
};

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
        cout << "Storage full. Cannot add more appliances.\n";
        return;
    }

    Appliance a;
    cout << "Enter appliance name: ";
    cin.ignore();
    getline(cin, a.name);

    cout << "Enter power rating (watts): ";
    cin >> a.watts;

    cout << "Enter daily usage hours: ";
    cin >> a.hours;

    arr[count] = a;
    count++;
    cout << "Appliance added (not saved to file yet).\n";
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
        int choice;
        cout << "Choose (1-6): ";
        cin >> choice;

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
