#include <iostream>
using namespace std;

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

int main() {
    cout << "Electrical Load Monitoring & Billing System\n";

    while (true) {
        showMenu();
        int choice;
        cout << "Choose (1-6): ";
        cin >> choice;

        switch (choice) {
            case 1: cout << "Register appliance (coming soon)\n"; break;
            case 2: cout << "View appliances (coming soon)\n"; break;
            case 3: cout << "Search appliance (coming soon)\n"; break;
            case 4: cout << "Billing (coming soon)\n"; break;
            case 5: cout << "Save appliances (coming soon)\n"; break;
            case 6: cout << "Goodbye!\n"; return 0;
            default: cout << "Invalid choice. Try again.\n"; break;
        }
    }
}