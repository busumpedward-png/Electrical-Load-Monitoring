#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

const int MAX_APPLIANCES = 100;
const string APPLIANCES_FILE = "appliances.txt";

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

string toLowerSimple(string s) {
    for (int i = 0; i < (int)s.size(); i++) {
        char c = s[i];
        if (c >= 'A' && c <= 'Z') s[i] = char(c - 'A' + 'a');
    }
    return s;
}

double applianceKwh(const Appliance &a) {
    return (a.watts / 1000.0) * a.hours;
}

double totalKwh(const Appliance arr[], int count) {
    double total = 0;
    for (int i = 0; i < count; i++) total += applianceKwh(arr[i]);
    return total;
}

bool saveAppliances(const Appliance arr[], int count) {
    ofstream fout(APPLIANCES_FILE.c_str());
    if (!fout.is_open()) return false;

    for (int i = 0; i < count; i++) {
        fout << arr[i].name << "|" << arr[i].watts << "|" << arr[i].hours << "\n";
    }
    fout.close();
    return true;
}

bool loadAppliances(Appliance arr[], int &count) {
    count = 0;
    ifstream fin(APPLIANCES_FILE.c_str());
    if (!fin.is_open()) return false;

    string line;
    while (getline(fin, line)) {
        if (line.size() == 0) continue;

        int p1 = (int)line.find('|');
        if (p1 == -1) continue;
        int p2 = (int)line.find('|', p1 + 1);
        if (p2 == -1) continue;

        string name = line.substr(0, p1);
        string wattsStr = line.substr(p1 + 1, p2 - (p1 + 1));
        string hoursStr = line.substr(p2 + 1);

        double w = 0, h = 0;
        stringstream sw(wattsStr); if (!(sw >> w)) continue;
        stringstream sh(hoursStr); if (!(sh >> h)) continue;

        if (name.size() > 0 && w > 0 && h >= 0 && h <= 24) {
            if (count < MAX_APPLIANCES) {
                arr[count].name = name;
                arr[count].watts = w;
                arr[count].hours = h;
                count++;
            }
        }
    }
    fin.close();
    return true;
}

void showMenu() {
    cout << "\n========== ELECTRICAL LOAD MONITOR ==========\n";
    cout << "1. Register appliance\n";
    cout << "2. View appliances + kWh\n";
    cout << "3. Search appliance\n";
    cout << "4. Billing (tariff + total cost)\n";
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

    saveAppliances(arr, count);
    cout << "Appliance registered and saved.\n";
}

void viewAppliances(const Appliance arr[], int count) {
    if (count == 0) {
        cout << "No appliances registered.\n";
        return;
    }

    cout << left << setw(4) << "#"
         << setw(25) << "Name"
         << setw(12) << "Watts"
         << setw(12) << "Hours/day"
         << setw(12) << "kWh/day" << "\n";
    cout << "---------------------------------------------------------------\n";

    cout << fixed << setprecision(2);
    for (int i = 0; i < count; i++) {
        cout << left << setw(4) << (i + 1)
             << setw(25) << arr[i].name
             << setw(12) << arr[i].watts
             << setw(12) << arr[i].hours
             << setw(12) << applianceKwh(arr[i]) << "\n";
    }

    cout << "---------------------------------------------------------------\n";
    cout << "TOTAL DAILY ENERGY: " << totalKwh(arr, count) << " kWh\n";
}

void searchAppliance(const Appliance arr[], int count) {
    if (count == 0) {
        cout << "No appliances registered.\n";
        return;
    }

    string query = readNonEmptyLine("Enter name to search: ");
    query = toLowerSimple(query);

    bool found = false;
    cout << fixed << setprecision(2);

    for (int i = 0; i < count; i++) {
        string nameLower = toLowerSimple(arr[i].name);
        if (nameLower.find(query) != string::npos) {
            if (!found) cout << "Matches:\n";
            cout << "- " << arr[i].name
                 << " | " << arr[i].watts << "W"
                 << " | " << arr[i].hours << " hrs/day"
                 << " | " << applianceKwh(arr[i]) << " kWh/day\n";
            found = true;
        }
    }

    if (!found) cout << "No appliance found.\n";
}

void billing(const Appliance arr[], int count) {
    if (count == 0) {
        cout << "No appliances registered. Register appliances first.\n";
        return;
    }

    double tariff = readPositiveDouble("Enter tariff per kWh (positive): ");

    double total = totalKwh(arr, count);
    double cost = total * tariff;

    cout << fixed << setprecision(2);
    cout << "\n========== BILLING SUMMARY ==========\n";
    cout << "Tariff: " << tariff << " per kWh\n";
    cout << "Total daily energy: " << total << " kWh\n";
    cout << "Total daily cost:  " << cost << "\n";
    cout << "=====================================\n";
}

int main() {
    Appliance appliances[MAX_APPLIANCES];
    int count = 0;

    loadAppliances(appliances, count);
    cout << "Electrical Load Monitoring & Billing System\n";
    cout << "Loaded appliances: " << count << "\n";

    while (true) {
        showMenu();
        int choice = readInt("Choose (1-6): ");

        switch (choice) {
            case 1: registerAppliance(appliances, count); break;
            case 2: viewAppliances(appliances, count); break;
            case 3: searchAppliance(appliances, count); break;
            case 4: billing(appliances, count); break;
            case 5:
                if (saveAppliances(appliances, count)) cout << "Saved.\n";
                else cout << "Failed to save.\n";
                break;
            case 6:
                saveAppliances(appliances, count);
                cout << "Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
                break;
        }
    }
}
