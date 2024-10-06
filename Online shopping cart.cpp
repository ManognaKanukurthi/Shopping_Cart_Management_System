#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class User1 {
protected:
    string username;
    string password;

public:
    User1(const string &_username, const string &_password) {
        username = _username;
        password = _password;
    }

    bool isLoggedIn() {
        string enteredUsername, enteredPassword, un, pw;
        cout << "Enter username: ";
        cin >> enteredUsername;
        cout << "Enter password: ";
        cin >> enteredPassword;

        ifstream read("username.txt");
        getline(read, un);
        getline(read, pw);
        read.close();

        if (un == enteredUsername && pw == enteredPassword)
            return true;
        else
            return false;
    }
};

struct Item {
    int itemId;
    string itemName;
    float itemPrice;
    int quantity;
    struct Item *next;
};

struct Item *AOP[10];

void createhash(int id, string name, float price, int qty) {
    struct Item *temp, *p1;
    int k = id % 10;

    p1 = new Item;

    p1->itemId = id;
    p1->itemName = name;
    p1->itemPrice = price;
    p1->quantity = qty;

    p1->next = NULL;
    if (AOP[k] == NULL)
        AOP[k] = p1;
    else {
        p1->next = AOP[k];
        AOP[k] = p1;
    }
}

void deleteItem(int id) {
    struct Item *curr, *prev;
    int k = id % 10;
    curr = AOP[k];
    prev = NULL;
    while (curr != NULL) {
        if (curr->itemId == id) {
            if (prev == NULL) {
                AOP[k] = curr->next;
            } else {
                prev->next = curr->next;
            }
            delete (curr);
            cout << "Item id " << id << " deleted from the cart";
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    cout << "Item with id " << id << " not found in cart " << endl;
}

void displaycart() {
    struct Item *temp;
    cout<<"Item Id:         Item Name:      Item price:         Quantity:\n";
    for (int i = 0; i < 10; i++) {
        temp = AOP[i];
        
        while (temp != NULL) {
           /* cout << "Item ID:" << temp->itemId << endl
                 << "Item NAME:" << temp->itemName << endl
                 << "Item Price: " << temp->itemPrice << endl
                 << "Quantity: " << temp->quantity << endl;*/
                 cout<<"   "<<temp->itemId<<"             " <<temp->itemName<<"             "<<temp->itemPrice<<"                 "<<temp->quantity<<endl;
            temp = temp->next;
        }
    }
    cout << endl
         << endl;
}

void generatebill() {
    struct Item *temp;
    float total = 0.0;
    cout<<"***************************************\n";
    cout<<"--------PRICE DETAILS--------\n";

    cout<<"Item Name:      Item price:         Quantity:\n";
    for (int i = 0; i < 10; i++) {
        temp = AOP[i];
        while (temp != NULL) {
            cout << temp->itemName << "            " << temp->itemPrice << " bucks            " << temp->quantity << endl;
            total += temp->itemPrice * temp->quantity;
            temp = temp->next;
        }
    }

    cout << "\nTotal: " << total <<" bucks"<<endl;
}

int main() {
    int choice, Id, quantity;
    string username, password, itemname;
    float itemprice;

    ofstream file;  
    do {
        cout << "\n1. Sign Up\n";
        cout << "2. Login\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Select a username: ";
            cin >> username;
            cout << "Select a password: ";
            cin >> password;
            file.open("username.txt");
            file << username << endl
                 << password;
            file.close();
            cout << "Registered successfully!!";
            break;

        case 2: {
            User1 person(username, password);
            bool status = person.isLoggedIn();

            if (status) {
                cout << "Login successful.\n";
                for (int i = 0; i < 10; i++)
                    AOP[i] = NULL;

                do {
                    cout << "\n1. Add Item to Cart\n";
                    cout << "2. Display Cart\n";
                    cout << "3. Generate Bill\n";
                    cout << "4. Delete Item from Cart\n";
                    cout << "0. Logout\n";
                    cout << "Enter your choice: ";
                    cin >> choice;

                    switch (choice) {
                    case 1:
                        cout << "Enter Item ID: ";
                        cin >> Id;
                        cout << "Enter Item Name: ";
                        cin >> itemname;
                        cout << "Enter Item Price: ";
                        cin >> itemprice;
                        cout << "Enter Quantity: ";
                        cin >> quantity;
                        createhash(Id, itemname, itemprice, quantity);
                        break;

                    case 2:
                        displaycart();
                        break;

                    case 3:
                        generatebill();
                        break;

                    case 4:
                        cout << "Enter Item ID to delete: ";
                        cin >> Id;
                        deleteItem(Id);
                        break;

                    case 0:
                        cout << "Logging out.\n";
                        break;

                    default:
                        cout << "Invalid choice. Please try again.\n";
                    }
                } while (choice != 0);
            } else {
                cout << "Login failed. User not found.\n";
            }
            break;
        }

        case 0:
            cout << "Exiting program.\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
