#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

class Plant {
public:
    string name;
    int stock;
    float price;
    int soldCount;

    Plant() {
        name = "";
        stock = 0;
        price = 0;
        soldCount = 0;
    }

    Plant(string n, int s, float p) {
        name = n;
        stock = s;
        price = p;
        soldCount = 0;
    }
};

class NurseryManager {
private:
    vector<Plant> inventory;
    float totalRevenue;

public:
    NurseryManager() {
        totalRevenue = 0;
        loadFromFile();
    }

    void loadFromFile() {
        ifstream file("nursery.txt");

        if (!file) return;

        int n;
        file >> n;
        file >> totalRevenue;
        file.ignore();

        for (int i = 0; i < n; i++) {
            Plant p;
            getline(file, p.name);
            file >> p.stock >> p.price >> p.soldCount;
            file.ignore();
            inventory.push_back(p);
        }

        file.close();
    }

    void saveToFile() {
        ofstream file("nursery.txt");

        file << inventory.size() << endl;
        file << totalRevenue << endl;

        for (int i = 0; i < inventory.size(); i++) {
            file << inventory[i].name << endl;
            file << inventory[i].stock << " "
                 << inventory[i].price << " "
                 << inventory[i].soldCount << endl;
        }

        file.close();
    }

    void addPlant() {
        string name;
        int qty;
        float prc;

        cout << "\n--- Add New Plant ---\n";

        cin.ignore();
        cout << "Plant Name: ";
        getline(cin, name);

        cout << "Initial Stock: ";
        cin >> qty;

        cout << "Price per Plant: ";
        cin >> prc;

        Plant p(name, qty, prc);
        inventory.push_back(p);

        saveToFile();

        cout << "Plant added successfully!\n";
    }

    void viewStock() {
        cout << "\n---------------- Current Stock ----------------\n";
        cout << left << setw(20) << "Name"
             << setw(10) << "Stock"
             << setw(10) << "Price"
             << setw(10) << "Sold" << endl;

        cout << "-----------------------------------------------\n";

        for (int i = 0; i < inventory.size(); i++) {
            cout << left << setw(20) << inventory[i].name
                 << setw(10) << inventory[i].stock
                 << setw(10) << inventory[i].price
                 << setw(10) << inventory[i].soldCount << endl;
        }
    }

    void sellPlant() {
        string name;
        int qty;

        cout << "\n--- Sell Plant ---\n";

        cin.ignore();
        cout << "Enter Plant Name: ";
        getline(cin, name);

        for (int i = 0; i < inventory.size(); i++) {
            if (inventory[i].name == name) {
                cout << "Available Stock: " << inventory[i].stock;
                cout << "\nEnter quantity: ";
                cin >> qty;

                if (qty <= inventory[i].stock) {
                    inventory[i].stock -= qty;
                    inventory[i].soldCount += qty;

                    float sale = qty * inventory[i].price;
                    totalRevenue += sale;

                    saveToFile();

                    cout << "Sale Successful! Rs. " << sale << endl;
                } else {
                    cout << "Not enough stock!\n";
                }
                return;
            }
        }

        cout << "Plant not found!\n";
    }

    void showReport() {
        cout << "\n--- Financial Report ---\n";
        cout << "Total Revenue: Rs. " << totalRevenue << endl;
    }
};

int main() {
    NurseryManager myNursery;
    int choice;

    while (1) {
        cout << "\n===== Plant Nursery Management System =====\n";
        cout << "1. Add New Plant\n";
        cout << "2. View Stock\n";
        cout << "3. Sell Plant\n";
        cout << "4. View Report\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";

        cin >> choice;

        switch (choice) {
            case 1: myNursery.addPlant(); break;
            case 2: myNursery.viewStock(); break;
            case 3: myNursery.sellPlant(); break;
            case 4: myNursery.showReport(); break;
            case 5: return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}

