#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <cstring>
#include <conio.h>
#include <algorithm>
#include <cstdio>
#include <cctype>
#include <vector>
#include <windows.h>

using namespace std;

//-----------------------------------------------Class "Hotel" Attributes and methods-----------------------------------------------//

class Hotel
{
protected:
    string name;
    string id;
    string address;
    string phone_number;
    int room_number;
    char room_type[20];
    int peoples_stayed_with;
    int days;
    float pay_first;
    float bills;
    int a, b; // a = rating for cleaniness, b = rating for booking experience
    char review[700];

public:
    void header();  // done
    void menu();    // done
    float type_of_room(); // done
    void display_customer_data_by_room_number(); //done
    void display_customer_data_by_months(); //done
    void display_all_customer_data(); //done
    void display_room_available(); //done
    void edit_customer_detail(); //done
    void feedback_and_review(string name); // Done
    void updateRoomsFile(int roomToBook, string status); // Done
};

//-----------------------------------------------Class "Admin" : Attributes and methods-----------------------------------------------//

class Admin : public Hotel
{
private:
    string username;
    string password;

public:
    Admin()
    {
        username = "admin";
        password = "password";
    }

    string getUsername();
    string getPassword();
    void admin_login_account();
    void admin_menu();
    void booking_room();
    void display_customer_details(); // Display by room number
    void display_all_record();       // Display by months and display all
    void display_income();           // Display by months and total income
    void edit_room_info();                // Check by room number
    void cancel_booking(); // Check by room number and customer name
    void read_feedback_and_review();
};

//-----------------------------------------------Class "Customer" : Attributes and methods-----------------------------------------------//

class Customer : public Hotel
{
protected:
    string customer_name;

public:
    void customer_menu();
    void customer_check_in();      // Check in by using name and phone number for confirmation
    void customer_check_out();     // also check out by using name and phone number for confirmation then leave a rating and review
};

//-----------------------------------------------Hotel : display room available-----------------------------------------------//

void Hotel::display_room_available()
{
    ifstream file("rooms.csv"); // Open the rooms.csv file
    if (!file.is_open())
    {
        cerr << "\t\t\t\t\t\t\t\tError: Could not open the rooms.csv file!" << endl;
        return;
    }

    string line, roomNumber, roomType, roomStatus;

    // Display table header
    cout << "\n\t\t\t\t\t\t\tRoom Availability\n";
    cout << "\t\t\t\t\t\t\t-------------------------------------------\n";
    cout << "\t\t\t\t\t\t\tRoom Number\t  Type\t\tStatus\n";
    cout << "\t\t\t\t\t\t\t-------------------------------------------\n";

    // Read each line from the file and display room details
    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, roomNumber, ',');
        getline(ss, roomType, ',');
        getline(ss, roomStatus, ',');

        cout << "\t\t\t\t\t\t" << setw(10) << setfill(' ') << roomNumber 
             << "\t\t"  << setw(10) << setfill(' ') << roomType 
             << "\t" << setw(10) << setfill(' ') << roomStatus << endl;
    }

    file.close(); // Close the file
}

//-----------------------------------------------Hotel : Room type-----------------------------------------------//

float Hotel::type_of_room()
{
    int room_type_choice;

    // Display room types and prices
    cout << "\n\t\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-|" << endl;
    cout << "\t\t\t\t\t\t\t\t|                                      |" << endl;
    cout << "\t\t\t\t\t\t\t\t|       Types of Room Available        |" << endl;
    cout << "\t\t\t\t\t\t\t\t|                                      |" << endl;
    cout << "\t\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-|" << endl;
    cout << "\t\t\t\t\t\t\t\t|                                      |" << endl;
    cout << "\t\t\t\t\t\t\t\t| 1. Standard - $ 20 per day           |" << endl;
    cout << "\t\t\t\t\t\t\t\t| 2. Deluxe   - $ 50 per day           |" << endl;
    cout << "\t\t\t\t\t\t\t\t| 3. Suite    - $ 100 per day          |" << endl;
    cout << "\t\t\t\t\t\t\t\t|                                      |" << endl;
    cout << "\t\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-|" << endl;
    cout << "\n\t\t\t\t\t\t\tEnter your choice (1/2/3): ";
    cin >> room_type_choice;

    // Validate input
    if (room_type_choice < 1 || room_type_choice > 3)
    {
        cout << "\n\t\t\t\t\t\t\tInvalid choice. Please try again.\n";
        return type_of_room();
    }

    return room_type_choice;
}

//-----------------------------------------------Hotel : display customer data (room number , months , all)-----------------------------------------------//

// display by room number
void Hotel::display_customer_data_by_room_number() {
    int roomID;
    cout << "\n\t\t\t\t\t\t\tEnter Room ID: ";
    cin >> roomID;

    ifstream file("customer_info.csv");
    if (!file.is_open()) {
        cerr << "\t\t\t\t\t\t\t\tError: Could not open the customer_info.csv file!\n";
        return;
    }

    string line;
    bool found = false;
    cout << "\n\t\t\t\t\t\t\tCustomer Details for Room " << roomID << ":\n";
    cout << "\t\t\t\t\t\t\t---------------------------------------------\n";

    // Skip the header line if there is one
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string room, day, month, year, hour, minute, name, id, address, phone, people, days, type, total, advance;

        // Read room ID from line
        getline(ss, room, ',');

        // Validate room ID
        if (room.empty() || !all_of(room.begin(), room.end(), ::isdigit)) {
            cerr << "\t\t\t\t\t\t\t\tError: Invalid Room ID in file: " << room << "\n";
            continue;
        }

        // Check if room matches the input ID
        if (stoi(room) == roomID) {
            getline(ss, day, ',');
            getline(ss, month, ',');
            getline(ss, year, ',');
            getline(ss, hour, ',');
            getline(ss, minute, ',');
            getline(ss, name, ',');
            getline(ss, id, ',');
            getline(ss, address, ',');
            getline(ss, phone, ',');
            getline(ss, people, ',');
            getline(ss, days, ',');
            getline(ss, type, ',');
            getline(ss, total, ',');
            getline(ss, advance, ',');

            // Display customer details
            cout << "\t\t\t\t\t\t\tRoom Type            : " << type << "\n";
            cout << "\t\t\t\t\t\t\tName                 : " << name << "\n";
            cout << "\t\t\t\t\t\t\tID                   : " << id << "\n";
            cout << "\t\t\t\t\t\t\tAddress              : " << address << "\n";
            cout << "\t\t\t\t\t\t\tPhone Number         : " << phone << "\n";
            cout << "\t\t\t\t\t\t\tPeople stayed with   : " << people << "\n";
            cout << "\t\t\t\t\t\t\tDays Stayed          : " << days << "\n";
            cout << "\t\t\t\t\t\t\tTotal Bill           : $ " << total << "\n";
            cout << "\t\t\t\t\t\t\tAdvance Paid         : $ " << advance << "\n\n";

            found = true;
        }
    }

    if (!found) {
        cout << "\t\t\t\t\t\t\tNo details found for Room ID " << roomID << ".\n";
    }

    file.close();
}

// Display by Month
void Hotel::display_customer_data_by_months()
{
    int month;
    cout << "\n\t\t\t\t\t\t\tEnter Month (1-12): ";
    cin >> month;

    ifstream file("customer_info.csv");
    if (!file.is_open())
    {
        cerr << "\t\t\t\t\t\t\t\tError: Could not open the customer_info.csv file!\n";
        return;
    }

    string line;
    bool found = false;
    cout << "\n\t\t\t\t\t\t\tCustomer Details for Month " << month << ":\n";
    cout << "\t\t\t\t\t\t\t---------------------------------------------\n";

    getline(file, line);
    while (getline(file, line))
    {
        stringstream ss(line);
        string room, day, monthStr, year, hour, minute, name, id, address, phone, people, days, type, total, advance;

        getline(ss, room, ',');
        getline(ss, day, ',');
        getline(ss, monthStr, ',');
        getline(ss, year, ',');
        getline(ss, hour, ',');
        getline(ss, minute, ',');
        if (stoi(monthStr) == month)
        {
            getline(ss, name, ',');
            getline(ss, id, ',');
            getline(ss, address, ',');
            getline(ss, phone, ',');
            getline(ss, people, ',');
            getline(ss, days, ',');
            getline(ss, type, ',');
            getline(ss, total, ',');
            getline(ss, advance, ',');

            cout << "\t\t\t\t\t\t\tRoom                 : " << room << "\n";
            cout << "\t\t\t\t\t\t\tRoom Type            : " << type << "\n";
            cout << "\t\t\t\t\t\t\tName                 : " << name << "\n";
            cout << "\t\t\t\t\t\t\tID                   : " << id << "\n";
            cout << "\t\t\t\t\t\t\tAddress              : " << address << "\n";
            cout << "\t\t\t\t\t\t\tPhone Number         : " << phone << "\n";
            cout << "\t\t\t\t\t\t\tPeople stayed with   : " << people << "\n";
            cout << "\t\t\t\t\t\t\tDays Stayed          : " << days << "\n";
            cout << "\t\t\t\t\t\t\tTotal Bill           : $ " << total << "\n";
            cout << "\t\t\t\t\t\t\tAdvance Paid         : $ " << advance << "\n\n";

            found = true;
        }
    }

    if (!found)
    {
        cout << "\t\t\t\t\t\t\tNo details found for Month " << month << ".\n";
    }

    file.close();
}

// Display All Customers
void Hotel::display_all_customer_data()
{
    ifstream file("customer_info.csv");
    if (!file.is_open())
    {
        cerr << "\t\t\t\t\t\t\t\tError: Could not open the customer_info.csv file!\n";
        return;
    }

    string line;
    cout << "\n\t\t\t\t\t\t\tAll Customer Details:\n";
    cout << "\t\t\t\t\t\t\t---------------------------------------------\n";

    // bool isheader= true;
    getline(file, line);
    while (getline(file, line))
    {
        stringstream ss(line);
        string room, day, month, year, hour, minute, name, id, address, phone, people, days, type, total, advance;

        getline(ss, room, ',');
        getline(ss, day, ',');
        getline(ss, month, ',');
        getline(ss, year, ',');
        getline(ss, hour, ',');
        getline(ss, minute, ',');
        getline(ss, name, ',');
        getline(ss, id, ',');
        getline(ss, address, ',');
        getline(ss, phone, ',');
        getline(ss, people, ',');
        getline(ss, days, ',');
        getline(ss, type, ',');
        getline(ss, total, ',');
        getline(ss, advance, ',');

        cout << "\t\t\t\t\t\t\tRoom                 : " << room << "\n";
        cout << "\t\t\t\t\t\t\tRoom Type            : " << type << "\n";
        cout << "\t\t\t\t\t\t\tName                 : " << name << "\n";
        cout << "\t\t\t\t\t\t\tID                   : " << id << "\n";
        cout << "\t\t\t\t\t\t\tAddress              : " << address << "\n";
        cout << "\t\t\t\t\t\t\tPhone Number         : " << phone << "\n";
        cout << "\t\t\t\t\t\t\tPeople stayed with   : " << people << "\n";
        cout << "\t\t\t\t\t\t\tDays Stayed          : " << days << "\n";
        cout << "\t\t\t\t\t\t\tTotal Bill           : $ " << total << "\n";
        cout << "\t\t\t\t\t\t\tAdvance Paid         : $ " << advance << "\n\n";
    }
    file.close();
}

//-----------------------------------------------Hotel: Update Status-----------------------------------------------//
void Hotel::updateRoomsFile(int roomToBook, string status)
{
    string line, roomNumber, roomType, roomStatus;
    vector<string> updatedRooms;
    bool roomFound = false; // Track if the room exists in the file

    ifstream roomFileIn("rooms.csv");
    if (!roomFileIn.is_open())
    {
        cerr << "\t\t\t\t\t\t\t\tError: Unable to open rooms.csv for reading.\n";
        return;
    }

    // Read the file line by line
    while (getline(roomFileIn, line))
    {
        stringstream ss(line);
        if (!getline(ss, roomNumber, ',') || !getline(ss, roomType, ',') || !getline(ss, roomStatus, ','))
        {
            cerr << "\t\t\t\t\t\t\t\tWarning: Skipping malformed line in rooms.csv: " << line << "\n";
            continue;
        }

        // Check if the current room is the one to update
        if (roomNumber == to_string(roomToBook))
        {
            updatedRooms.push_back(roomNumber + "," + roomType + "," + status); // Update the status
            roomFound = true;
        }
        else
        {
            updatedRooms.push_back(line); // Keep other lines unchanged
        }
    }
    roomFileIn.close();

    // If the room was not found, log a message and return
    if (!roomFound)
    {
        cerr << "\t\t\t\t\t\t\t\tError: Room number " << roomToBook << " not found in rooms.csv.\n";
        return;
    }

    // Write updated data to a temporary file
    ofstream roomFileOut("temp.csv");
    if (!roomFileOut.is_open())
    {
        cerr << "\t\t\t\t\t\t\t\tError: Unable to create temp.csv for writing.\n";
        return;
    }

    for (const string &updatedLine : updatedRooms)
    {
        roomFileOut << updatedLine << "\n";
    }
    roomFileOut.close();

    // Replace the original file with the updated file
    if (remove("rooms.csv") != 0)
    {
        cerr << "\t\t\t\t\t\t\t\tError: Unable to delete the original rooms.csv file.\n";
        return;
    }

    if (rename("temp.csv", "rooms.csv") != 0)
    {
        cerr << "\t\t\t\t\t\t\t\tError: Unable to rename temp.csv to rooms.csv.\n";
        return;
    }

    // cout << "\n\t\t\t\t\t\t\tRoom status updated successfully in rooms.csv.\n";
}

//-----------------------------------------------Admin : Login Account-----------------------------------------------//

string Admin::getPassword()
{
    return password;
}

string Admin::getUsername()
{
    return username;
}

//-----------------------------------------------Admin: Menu-----------------------------------------------//

void Admin::admin_menu()
{
    system("cls");
    while (1)
    {
        system("cls");
        header();
        cout << "\t\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-|" << endl;
        cout << "\t\t\t\t\t\t\t\t|                                      |" << endl;
        cout << "\t\t\t\t\t\t\t\t|              ADMIN MENU              |" << endl;
        cout << "\t\t\t\t\t\t\t\t|                                      |" << endl;
        cout << "\t\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-|" << endl;
        cout << "\t\t\t\t\t\t\t\t|                                      |" << endl;
        cout << "\t\t\t\t\t\t\t\t|  1. Display room available           |" << endl;
        cout << "\t\t\t\t\t\t\t\t|  2. Book a room                      |" << endl;
        cout << "\t\t\t\t\t\t\t\t|  3. Display Customer Details         |" << endl;
        cout << "\t\t\t\t\t\t\t\t|  4. Cancel Reservation               |" << endl;
        cout << "\t\t\t\t\t\t\t\t|  5. Edit Room Information            |" << endl;
        cout << "\t\t\t\t\t\t\t\t|  6. Display Income                   |" << endl;
        cout << "\t\t\t\t\t\t\t\t|  7. Read Feedback and Reviews        |" << endl;
        cout << "\t\t\t\t\t\t\t\t|  8. Go Back to Main Menu             |" << endl;
        cout << "\t\t\t\t\t\t\t\t|                                      |" << endl;
        cout << "\t\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-|" << endl;
        cout << "\t\t\t\t\t\t\t\t|                                      |" << endl;
        cout << "\t\t\t\t\t\t\t\t|  Choose Option : [1/2/3/4/5/6/7/8}   |" << endl;
        cout << "\t\t\t\t\t\t\t\t|                                      |" << endl;
        cout << "\t\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-|" << endl;
        cout << endl;

        int choice;
        char c = 'Y';
        cout << "\t\t\t\t\t\t\t\tEnter your option: ";
        cin >> choice;

        switch (choice)
        {
            system("cls");

        case 1:

            system("cls");
            display_room_available();
            cout << "\n\t\t\t\t\t\t\tPress any key to return to main menu " << endl;
            break;

        case 2:
            do
            {
                system("cls");
                booking_room();
                cout << "\t\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-|" << endl;
                cout << "\t\t\t\t\t\t\t\t|                                              |" << endl;
                cout << "\t\t\t\t\t\t\t\t|    Do you want to book another room ?(y/n)   |" << endl;
                cout << "\t\t\t\t\t\t\t\t|                                              |" << endl;
                cout << "\t\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*|" << endl;
                cout << "\t\t\t\t\t\t\t";
                cin  >> c;
            } while (c == 'y' || c == 'Y');
            cout << "\n\t\t\t\t\t\t\tThank you for Booking !!! " << endl;
            cout << "\t\t\t\t\t\t\tPress any key to return to main menu " << endl;
            _getch();
            break;

        case 3:
            system("cls");
            display_customer_details();
            break;

        case 4:
            system("cls");
            cancel_booking();
            break;

            case 5:
                system("cls");
                edit_room_info();
                break;

            case 6:
                system("cls");
                display_income ();
                break;

            // case 7:
            //     system("cls");
            //     read_feedback_and_reviews();
            //     break;

        case 8:
            system("cls");
            menu();
            break;

        default:
            cout << "\n\t\t\t\t\t\t\t\tInvalid input " << endl;
            cout << "\\t\t\t\t\t\t\t\tReturning to main menu " << endl;
            Sleep(5000);
            break;
        }
        _getch();
    }
}

//-----------------------------------------------Admin: Booking-----------------------------------------------//

void Admin::booking_room()
{
    system("cls");
    header();
    int room;
    float per_day_price = 0;
    int min_room = 0, max_room = 0;
    string selectedType;

    time_t currentTime = time(nullptr);
    tm *localTime = localtime(&currentTime);

    ofstream writer("customer_info.csv", ios::app);
    ofstream writer1("all_info.csv", ios::app);

    cout << "\t\t\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*|" << endl;
    cout << "\t\t\t\t\t\t\t\t\t|                           |" << endl;
    cout << "\t\t\t\t\t\t\t\t\t|   Enter Customer Details  |" << endl;
    cout << "\t\t\t\t\t\t\t\t\t|                           |" << endl;
    cout << "\t\t\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*|" << endl;

    // Room Type Selection
    int room_type_choice = type_of_room();
    switch (room_type_choice)
    {
    case 1:
        selectedType = "Standard";
        per_day_price = 20;
        min_room = 1;
        max_room = 10;
        break;
    case 2:
        selectedType = "Deluxe";
        per_day_price = 50;
        min_room = 11;
        max_room = 20;
        break;
    case 3:
        selectedType = "Suite";
        per_day_price = 100;
        min_room = 21;
        max_room = 25;
        break;
    default:
        cout << "\n\t\t\t\t\t\t\tInvalid choice. Please try again.\n";
        return;
    }

    // Display Available Rooms
    cout << "\n\t\t\t\t\t\t\tAvailable Rooms - " << selectedType << "\n";
    cout << "\t\t\t\t\t\t\t-------------------------------------------\n";
    cout << "\t\t\t\t\t\t\tRoom Number\tStatus\n";
    cout << "\t\t\t\t\t\t\t-------------------------------------------\n";

    ifstream file("rooms.csv");
    if (!file.is_open())
    {
        cerr << "\t\t\t\t\t\t\t\tError: Could not open the rooms.csv file!" << endl;
        return;
    }

    string line, roomNumber, roomType, roomStatus;
    bool found = false;

    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, roomNumber, ',');
        getline(ss, roomType, ',');
        getline(ss, roomStatus, ',');

        if (roomType == selectedType && roomStatus == "available")
        {
            cout << "\t\t\t\t\t\t\t" << roomNumber << "\t\t" << roomStatus << endl;
            found = true;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\n\t\t\t\t\t\t\tNo available rooms of type " << selectedType << ".\n";
        return;
    }

    // Input Room Number
    cout << "\n\t\t\t\t\t\t\tEnter Room No (between " << min_room << " and " << max_room << ") : ";
    cin >> room;

    // Validate Room Number
    if (room < min_room || room > max_room)
    {
        cout << "\n\t\t\t\t\t\t\tInvalid Room Number for the selected type.\n";
        return;
    }

    // Check if the room is already booked
    ifstream roomFileIn("rooms.csv");
    bool isAlreadyBooked = false;

    while (getline(roomFileIn, line))
    {
        stringstream ss(line);
        getline(ss, roomNumber, ',');
        getline(ss, roomType, ',');
        getline(ss, roomStatus, ',');

        if (roomNumber == to_string(room))
        {
            if (roomStatus == "booked")
            {
                isAlreadyBooked = true;
                break;
            }
        }
    }
    roomFileIn.close();

    if (isAlreadyBooked)
    {
        cout << "\n\t\t\t\t\t\t\tError: Room " << room << " is already booked.\n";
        return;
    }

    cin.ignore(); // Clear input buffer

    // Customer details
    cout << "\t\t\t\t\t\t\tDate                                 : "
         << setw(2) << setfill('0') << localTime->tm_mday << " "
         << setw(2) << setfill('0') << (localTime->tm_mon + 1) << " "
         << (1900 + localTime->tm_year) << endl;

    cout << "\t\t\t\t\t\t\tTime                                 : " << localTime->tm_hour << " : " << localTime->tm_min << endl;

    cout << "\t\t\t\t\t\t\tEnter customer name                  : ";
    getline(cin, name);

    cout << "\t\t\t\t\t\t\tEnter customer ID                    : ";
    getline(cin, id);

    cout << "\t\t\t\t\t\t\tEnter customer address               : ";
    getline(cin, address);

    cout << "\t\t\t\t\t\t\tEnter customer phone number          : ";
    getline(cin, phone_number);

    cout << "\t\t\t\t\t\t\tEnter people staying in the room     : ";
    cin >> peoples_stayed_with;

    cout << "\t\t\t\t\t\t\tEnter number of days to checkout     : ";
    cin >> days;

    bills = days * per_day_price;
    cout << "\t\t\t\t\t\t\tTotal                                : $ " << bills << endl;

    cout << "\t\t\t\t\t\t\tPay in advance                       : $ ";
    cin >> pay_first;

    // Write to customer_info.csv
    writer << room << ',' << localTime->tm_mday << ',' << (localTime->tm_mon + 1) << ','
           << (1900 + localTime->tm_year) << ',' << localTime->tm_hour << ',' 
           << localTime->tm_min << ',' << name << ',' << id << ',' << address << ','
           << phone_number << ',' << peoples_stayed_with << ',' << days << ',' 
           << selectedType << ',' << bills << ',' << pay_first << '\n';

    // Write to all_info.csv
    writer1 << room << ',' << localTime->tm_mday << ',' << (localTime->tm_mon + 1) << ','
           << (1900 + localTime->tm_year) << ',' << localTime->tm_hour << ',' 
           << localTime->tm_min << ',' << name << ',' << id << ',' << address << ','
           << phone_number << ',' << peoples_stayed_with << ',' << days << ',' 
           << selectedType << ',' << bills << ',' << pay_first << '\n';

    updateRoomsFile(room, "booked");

    cout << "\n\t\t\t\t\t\t\tRoom is booked successfully!\n";

    writer.close();
    writer1.close();
}

//-----------------------------------------------Admin: Display customer details-----------------------------------------------//
void Admin::display_customer_details()
{
    system("cls");
    header();
    int choice;
    cout << "\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|" << endl;
    cout << "\t\t\t\t\t\t\t|                                           |" << endl;
    cout << "\t\t\t\t\t\t\t|          DISPLAY CUSTOMER DETAILS         |" << endl;
    cout << "\t\t\t\t\t\t\t|                                           |" << endl;
    cout << "\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|" << endl;
    cout << "\t\t\t\t\t\t\t|                                           |" << endl;
    cout << "\t\t\t\t\t\t\t|  1. Display by Room Number                |" << endl;
    cout << "\t\t\t\t\t\t\t|  2. Display by Month                      |" << endl;
    cout << "\t\t\t\t\t\t\t|  3. Display All                           |" << endl;
    cout << "\t\t\t\t\t\t\t|                                           |" << endl;
    cout << "\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|" << endl;
    cout << "\t\t\t\t\t\t\tEnter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        display_customer_data_by_room_number();
        break;
    case 2:
        display_customer_data_by_months();
        break;
    case 3:
        display_all_customer_data();
        break;
    default:
        cout << "\t\t\t\t\t\t\tInvalid Choice! Returning to menu.\n";
        return;
    }
}

//-----------------------------------------------Admin: Cancel Booking-----------------------------------------------//
void Admin::cancel_booking() {
    system("cls");
    header();
    int room;
    string line, roomNumber, roomType, roomStatus;
    bool found = false;

    // Input Room Number to Cancel
    cout << "\n\t\t\t\t\t\t\tEnter room number to cancel Reservation: ";
    cin >> room;

    // Check if the room exists and find the reservation in customer_info.csv
    ifstream customerFile("customer_info.csv");
    ofstream tempCustomerFile("temp_customer_info.csv");
    ifstream allInfoFile("all_info.csv");
    ofstream tempAllInfoFile("temp_all_info.csv");

    while (getline(customerFile, line)) {
        stringstream ss(line);
        getline(ss, roomNumber, ',');
        // If the room number matches, do not write it to temp file
        if (roomNumber == to_string(room)) {
            found = true;  // Reservation found
            cout << "\n\t\t\t\t\t\t\tReservation for Room " << room << " has been canceled.\n";
            continue; // Skip writing this line to the temp file
        }
        // Write the rest of the lines to the temporary file
        tempCustomerFile << line << endl;
    }
    customerFile.close();
    tempCustomerFile.close();

    // Now process all_info.csv
    while (getline(allInfoFile, line)) {
        stringstream ss(line);
        getline(ss, roomNumber, ',');
        // If the room number matches, do not write it to temp file
        if (roomNumber == to_string(room)) {
            continue; // Skip writing this line to the temp file
        }
        // Write the rest of the lines to the temporary file
        tempAllInfoFile << line << endl;
    }
    allInfoFile.close();
    tempAllInfoFile.close();

    // Update rooms.csv to set the room status to available
    ifstream roomsFile("rooms.csv");
    ofstream tempRoomsFile("temp_rooms.csv");

    while (getline(roomsFile, line)) {
        stringstream ss(line);
        getline(ss, roomNumber, ',');
        getline(ss, roomType, ',');
        getline(ss, roomStatus, ',');

        if (roomNumber == to_string(room)) {
            roomStatus = "available"; // Update status
        }
        // Write the updated line to the temporary file
        tempRoomsFile << roomNumber << ',' << roomType << ',' << roomStatus << endl;
    }
    
    roomsFile.close();
    tempRoomsFile.close();

    // Replace original files with the temp files
    remove("customer_info.csv");
    rename("temp_customer_info.csv", "customer_info.csv");

    remove("all_info.csv");
    rename("temp_all_info.csv", "all_info.csv");

    remove("rooms.csv");
    rename("temp_rooms.csv", "rooms.csv");

    if (!found) {
        cout << "\n\t\t\t\t\t\t\tNo reservation found for Room " << room << ".\n";
    } else {
        cout << "\n\t\t\t\t\t\t\tRoom status updated to available.\n";
    }
}

//-----------------------------------------------Admin: Edit Customer Info-----------------------------------------------//
void Admin::edit_room_info() {
    system("cls");
    header();
    int room;
    string line, roomNumber;
    bool found = false;
    string selectedType, roomType, roomStatus, bills, payAdvanced;
    float per_day_price = 0;
    int min_room = 0, max_room = 0;
    int oldRoomNumber;

    // Get current date
    time_t currentTime = time(nullptr);
    tm *localTime = localtime(&currentTime);
    string currentHour = to_string(localTime->tm_hour);
    string currentMinute = to_string(localTime->tm_min);
    string currentDay = to_string(localTime->tm_mday);
    string currentMonth = to_string(localTime->tm_mon + 1);
    string currentYear = to_string(localTime->tm_year + 1900);

    // Input Room ID to Edit
    cout << "\n\t\t\t\t\t\t\tEnter room number to edit Reservation: ";
    cin >> oldRoomNumber;

    // Display old reservation information
    cout << "\n\t\t\t\t\t\t\tExisting Reservation details:\n";
    display_customer_data_by_room_number(); // Function to display current details

    // Open files for reading and writing
    ifstream customerFile("customer_info.csv");
    ofstream tempCustomerFile("temp_customer_info.csv");
    if (!customerFile.is_open() || !tempCustomerFile.is_open()) {
        cerr << "\t\t\t\t\t\t\t\tError: Could not open customer_info.csv or temp file for writing!" << endl;
        return;
    }

    ifstream allInfoFile("all_info.csv");
    ofstream tempAllInfoFile("temp_all_info.csv");
    if (!allInfoFile.is_open() || !tempAllInfoFile.is_open()) {
        cerr << "\t\t\t\t\t\t\t\tError: Could not open all_info.csv or temp file for writing!" << endl;
        return;
    }

    string header;
    getline(allInfoFile, header); // Read the header line
    tempAllInfoFile << header << '\n'; // Write the header to the temp file

    string name, id, address, phone_number, people, days, oldRoomType, hour, minute;
    while (getline(customerFile, line)) {
        stringstream ss(line);
        getline(ss, roomNumber, ',');

        if (roomNumber == to_string(oldRoomNumber)) {
            found = true;

            // Read old reservation details
            getline(ss, currentDay, ','); 
            getline(ss, currentMonth, ',');
            getline(ss, currentYear, ',');
            getline(ss, hour, ',');
            getline(ss, minute, ',');
            getline(ss, name, ',');
            getline(ss, id, ',');
            getline(ss, address, ',');
            getline(ss, phone_number, ',');
            getline(ss, people, ',');
            getline(ss, days, ',');
            getline(ss, oldRoomType, ','); // Store old room type for status update
            getline(ss, bills, ',');
            getline(ss, payAdvanced, ',');

            // Get new room type
            int room_type_choice = type_of_room();
            switch (room_type_choice) {
                case 1:
                    selectedType = "Standard";
                    per_day_price = 20;
                    min_room = 1;
                    max_room = 10;
                    break;
                case 2:
                    selectedType = "Deluxe";
                    per_day_price = 50;
                    min_room = 11;
                    max_room = 20;
                    break;
                case 3:
                    selectedType = "Suite";
                    per_day_price = 100;
                    min_room = 21;
                    max_room = 25;
                    break;
                default:
                    cout << "\n\t\t\t\t\t\t\tInvalid choice. Aborting.\n";
                    return;
            }

            cout << "\n\t\t\t\t\t\t\tAvailable Rooms - " << selectedType << "\n";
            cout << "\t\t\t\t\t\t\t-------------------------------------------\n";
            cout << "\t\t\t\t\t\t\tRoom Number\tStatus\n";
            cout << "\t\t\t\t\t\t\t-------------------------------------------\n";

            ifstream file("rooms.csv");
            if (!file.is_open())
            {
                cerr << "\t\t\t\t\t\t\t\tError: Could not open the rooms.csv file!" << endl;
                return;
            }

            string line, roomNumber, roomType, roomStatus;
            bool found = false;

            while (getline(file, line))
            {
                stringstream ss(line);
                getline(ss, roomNumber, ',');
                getline(ss, roomType, ',');
                getline(ss, roomStatus, ',');

                if (roomType == selectedType && roomStatus == "available")
                {
                    cout << "\t\t\t\t\t\t\t" << roomNumber << "\t\t" << roomStatus << endl;
                    found = true;
                }
            }

            file.close();

            if (!found)
            {
                cout << "\n\t\t\t\t\t\t\tNo available rooms of type " << selectedType << ".\n";
                return;
            }

            // Input new room number
            cout << "\n\t\t\t\t\t\t\tEnter new room number (" << min_room << " to " << max_room << "): ";
            cin >> room;

            if (room < min_room || room > max_room) {
                cout << "\n\t\t\t\t\t\t\tInvalid Room Number.\n";
                return;
            }

            // Check if the room is already booked
            ifstream roomFile("rooms.csv");
            bool isBooked = false;
            while (getline(roomFile, line)) {
                stringstream ss(line);
                getline(ss, roomNumber, ',');
                getline(ss, roomType, ',');
                getline(ss, roomStatus, ',');

                if (roomNumber == to_string(room) && roomStatus == "booked") {
                    isBooked = true;
                    break;
                }
            }
            roomFile.close();

            if (isBooked) {
                cout << "\n\t\t\t\t\t\t\tRoom " << room << " is already booked.\n";
                return;
            }

            // Update old room to "available"
            updateRoomsFile(oldRoomNumber, "available");

            // Update new room to "booked"
            updateRoomsFile(room, "booked");

            // Get updated customer details
            cin.ignore();

            cout << "\n\t\t\t\t\t\t\tDate                             : " << currentDay<< " " << currentMonth<< " " << currentYear<< endl;

            cout << "\t\t\t\t\t\t\tTime                             : " << currentHour<< " : " << currentMinute<< endl;

            cout << "\t\t\t\t\t\t\tEnter new customer name          : ";
            getline(cin, name);

            cout << "\t\t\t\t\t\t\tEnter new customer ID            : ";
            getline(cin, id);

            cout << "\t\t\t\t\t\t\tEnter new Address                : ";
            getline(cin, address);

            cout << "\t\t\t\t\t\t\tEnter new phone number           : ";
            getline(cin, phone_number);

            cout << "\t\t\t\t\t\t\tPeople stayed with               : ";
            getline(cin, people);

            cout << "\t\t\t\t\t\t\tEnter day stayed                 : ";
            getline(cin, days);

            // Calculate updated bills
            int numDays = stoi(days);
            float totalBill = numDays * per_day_price;

            // Format the bill to 2 decimal places
            ostringstream billStream;
            billStream << fixed << setprecision(0) << totalBill;
            string formattedBills = billStream.str(); // Convert the formatted result to string
            cout << "\t\t\t\t\t\t\tUpdated Total Bill               : $ " << formattedBills << endl;

            cout << "\t\t\t\t\t\t\tEnter paid advanced              : $ ";
            getline(cin, payAdvanced);

            // Write updated details
            tempCustomerFile << room << ',' << currentDay << ',' << currentMonth << ',' << currentYear << ','
                             << currentHour << ',' << currentMinute << ',' << name << ',' << id 
                             << ',' << address << ',' << phone_number << ',' << people << ',' << days << ',' 
                             << selectedType << ',' << formattedBills << ',' << payAdvanced << '\n';

            tempAllInfoFile  << room << ',' << currentDay << ',' << currentMonth << ',' << currentYear << ','
                             << currentHour << ',' << currentMinute << ',' << name << ',' << id 
                             << ',' << address << ',' << phone_number << ',' << people << ',' << days << ',' 
                             << selectedType << ',' << formattedBills << ',' << payAdvanced << '\n';

            continue; // Skip original line
        }
        tempCustomerFile << line << '\n';
    }
    // Process all_info.csv and update as needed
    while (getline(allInfoFile, line)) {
        stringstream ss(line);
        getline(ss, roomNumber, ',');

        if (roomNumber == to_string(oldRoomNumber)) {
            // Skip original line (already written as updated above)
            continue;
        }

        // Write the unchanged line
        tempAllInfoFile << line << '\n';
    }

    // Close all file streams
    customerFile.close();
    tempCustomerFile.close();
    allInfoFile.close();
    tempAllInfoFile.close();

    // Replace original files with updated files
    remove("customer_info.csv");
    rename("temp_customer_info.csv", "customer_info.csv");

    remove("all_info.csv");
    rename("temp_all_info.csv", "all_info.csv");

    if (found) {
        cout << "\n\t\t\t\t\t\t\tReservation updated successfully.\n";
    } else {
        cout << "\n\t\t\t\t\t\t\tRoom number not found in records.\n";
    }
}

//-----------------------------------------------Admin: Display Total Income-----------------------------------------------//
void Admin::display_income() {
    int choice;
    header();

    cout << "\n\t\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|" << endl;
    cout << "\t\t\t\t\t\t\t\t|                                           |" << endl;
    cout << "\t\t\t\t\t\t\t\t|           Income Calculation Menu         |" << endl;
    cout << "\t\t\t\t\t\t\t\t|                                           |" << endl;
    cout << "\t\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|" << endl;
    cout << "\t\t\t\t\t\t\t\t|                                           |" << endl;
    cout << "\t\t\t\t\t\t\t\t|  1. Display Income by Month               |" << endl;
    cout << "\t\t\t\t\t\t\t\t|  2. Display Total Income                  |" << endl;
    cout << "\t\t\t\t\t\t\t\t|                                           |" << endl;
    cout << "\t\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|" << endl;
    cout << "\t\t\t\t\t\t\t\tEnter your choice : ";
    cin >> choice;

    ifstream file("all_info.csv");
    if (!file.is_open()) {
        cerr << "\t\t\t\t\t\t\t\tError: Could not open the all_info.csv file!" << endl;
        return;
    }

    string line, header, room, day, month, year, name, id, address, phone, people, days, roomType, bills, payAdvanced, hour, minute;
    double totalIncome = 0.0;
    double monthlyIncome = 0.0;
    string targetMonth;

    // Skip the header line
    getline(file, header);

    switch (choice) {
    case 1: {
        // Calculate income by month
        cout << "\n\t\t\t\t\t\t\t\tEnter the month (1 - 12) : ";
        cin >> targetMonth;

        while (getline(file, line)) {
            stringstream ss(line);

            getline(ss, room, ',');
            getline(ss, day, ',');
            getline(ss, month, ',');
            getline(ss, year, ',');
            getline(ss, hour, ',');
            getline(ss, minute, ',');
            getline(ss, name, ',');
            getline(ss, id, ',');
            getline(ss, address, ',');
            getline(ss, phone, ',');
            getline(ss, people, ',');
            getline(ss, days, ',');
            getline(ss, roomType, ',');
            getline(ss, bills, ','); // Extract the bill amount as string
            getline(ss, payAdvanced, ',');

            // Convert bills to double and add to monthly income if the month matches
            try {
                if (month == targetMonth) {
                    monthlyIncome += stod(bills);
                }
            } catch (exception &e) {
                cerr << "\t\t\t\t\t\t\t\tError parsing bill amount: " << bills << endl;
            }
        }

        cout << "\n\t\t\t\t\t\t\t\t--- Monthly Income Report ---\n";
        cout << "\t\t\t\t\t\t\t\tIncome for Month " << targetMonth << ": $ " << fixed << setprecision(2) << monthlyIncome << endl;
        break;
    }
    case 2:
        // Calculate total income
        while (getline(file, line)) {
            stringstream ss(line);

            getline(ss, room, ',');
            getline(ss, day, ',');
            getline(ss, month, ',');
            getline(ss, year, ',');
            getline(ss, hour, ',');
            getline(ss, minute, ',');
            getline(ss, name, ',');
            getline(ss, id, ',');
            getline(ss, address, ',');
            getline(ss, phone, ',');
            getline(ss, people, ',');
            getline(ss, days, ',');
            getline(ss, roomType, ',');
            getline(ss, bills, ','); // Extract the bill amount as string
            getline(ss, payAdvanced, ',');

            // Convert bills to double and add to total income
            try {
                totalIncome += stod(bills);
            } catch (exception &e) {
                cerr << "\t\t\t\t\t\t\t\tError parsing bill amount: " << bills << endl;
            }
        }

        cout << "\n\t\t\t\t\t\t\t\t--- Total Income Report ---\n";
        cout << "\t\t\t\t\t\t\t\tTotal Income: $ " << fixed << setprecision(0) << totalIncome << endl;
        break;

    default:
        cout << "\t\t\t\t\t\t\t\tInvalid choice. Please select 1 or 2.\n";
        break;
    }

    file.close();
}

//-----------------------------------------------Customer: Check In-----------------------------------------------//

void Customer::customer_check_in()
{
    system("cls"); // Clear the console
    header();
    cout << "\n\t\t\t\t\t\t\t\t--- Customer Check-In Process ---\n";

    string inputName, inputPhoneNumber;

    time_t now = time(0);
    tm *localTime = localtime(&now);
    stringstream checkInTimeStream;
    checkInTimeStream << setw(2) << setfill('0') << localTime->tm_hour << ":"
                      << setw(2) << setfill('0') << localTime->tm_min;
    string checkInTime = checkInTimeStream.str();

    cout << "\n\t\t\t\t\t\t\t\tEnter Name for Confirmation          : ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any leftover input
    getline(cin, inputName);
    cout << "\t\t\t\t\t\t\t\tEnter Phone Number for Confirmation  : ";
    getline(cin, inputPhoneNumber);

    ifstream customerFile("customer_info.csv");
    if (!customerFile.is_open()) {
        cerr << "\t\t\t\t\t\t\t\tError: Could not open the file customer_info.csv" << endl;
        return;
    }

    // Skip the header line
    string customerline;
    if (!getline(customerFile, customerline)) {
        cerr << "\t\t\t\t\t\t\t\tError: The file is empty or improperly formatted." << endl;
        customerFile.close();
        return;
    }

    bool customerfound = false;

    cout << "\n\t\t\t\t\t\t\t\tSearching for customer...\n";
    Sleep(500);

    while (getline(customerFile, customerline)) {
        stringstream ss(customerline);
        string roomID, day, month, year, name, ID, address, phoneNumber, people, days, roomType, bills, payAdvanced, hour, minute;

        getline(ss, roomID, ',');
        getline(ss, day, ',');
        getline(ss, month, ',');
        getline(ss, year, ',');
        getline(ss, hour, ',');
        getline(ss, minute, ',');
        getline(ss, name, ',');
        getline(ss, ID, ',');
        getline(ss, address, ',');
        getline(ss, phoneNumber, ',');
        getline(ss, people, ',');
        getline(ss, days, ',');
        getline(ss, roomType, ',');
        getline(ss, bills, ',');
        getline(ss, payAdvanced, ',');

        // Compare input with CSV data
        if (strcasecmp(name.c_str(), inputName.c_str()) == 0 && 
            strcasecmp(phoneNumber.c_str(), inputPhoneNumber.c_str()) == 0) {
            customerfound = true;
            // Display customer details
            cout << "\n\t\t\t\t\t\t\t\tCustomer Found! Details:\n";
            cout << "\t\t\t\t\t\t\t\t----------------------------------\n";
            cout << "\t\t\t\t\t\t\t\tRoom ID                : " << roomID << endl;
            cout << "\t\t\t\t\t\t\t\tName                   : " << name << endl;
            cout << "\t\t\t\t\t\t\t\tID                     : " << ID << endl;
            cout << "\t\t\t\t\t\t\t\tAddress                : " << address << endl;
            cout << "\t\t\t\t\t\t\t\tPhone Number           : " << phoneNumber << endl;
            cout << "\t\t\t\t\t\t\t\tNumber of People       : " << people << endl;
            cout << "\t\t\t\t\t\t\t\tNumber of Days         : " << days << endl;
            cout << "\t\t\t\t\t\t\t\tRoom Type              : " << roomType << endl;
            cout << "\t\t\t\t\t\t\t\tTotal Bill             : $ " << bills << endl;
            cout << "\t\t\t\t\t\t\t\tPaid in Advance        : $ " << payAdvanced << endl;
            cout << "\t\t\t\t\t\t\t\t----------------------------------\n";
            break;
        }
    }

    cin.ignore();

    if (!customerfound) {
        cout << "\n\t\t\t\t\t\t\t\tNo matching customer found. Please check your input details.\n";
    }

    customerFile.close();

    // Add check-in time to the corresponding record in all_info.csv
    ifstream allInfoFile("all_info.csv");
    ofstream tempFile("all_info_temp.csv");
    if (!allInfoFile.is_open() || !tempFile.is_open()) {
        cerr << "\t\t\t\t\t\t\t\tError: Could not open all_info.csv for reading or writing.\n";
        return;
    }

    string allinfoline;
    bool recordUpdated = false;

    while (getline(allInfoFile, allinfoline)) {
        stringstream ss(allinfoline);
        string roomID, day, month, year, name, ID, address, phoneNumber, people, days, roomType, bills, payAdvanced, hour, minute, CheckInHour, CheckInMinute;


        getline(ss, roomID, ',');
        getline(ss, day, ',');
        getline(ss, month, ',');
        getline(ss, year, ',');
        getline(ss, hour, ',');
        getline(ss, minute, ',');
        getline(ss, name, ',');
        getline(ss, ID, ',');
        getline(ss, address, ',');
        getline(ss, phoneNumber, ',');
        getline(ss, people, ',');
        getline(ss, days, ',');
        getline(ss, roomType, ',');
        getline(ss, bills, ',');
        getline(ss, payAdvanced, ',');
        getline(ss, CheckInHour, ',');
        getline(ss, CheckInMinute, ',');

        if (!recordUpdated && strcasecmp(name.c_str(), inputName.c_str()) == 0 &&
            strcasecmp(phoneNumber.c_str(), inputPhoneNumber.c_str()) == 0 &&
            (CheckInHour.empty() || CheckInHour == " ")) {
            CheckInHour = to_string(localTime->tm_hour);
            CheckInMinute = to_string(localTime->tm_min);
            recordUpdated = true;
            cout << "\n\t\t\t\t\t\t\t\tCheck-In Successful!\n";
        }

        // Write updated or unchanged line to temp file
        tempFile << roomID << ',' << day << ',' << month << ',' << year << ','
                 << hour << ',' << minute << ',' << name << ',' << ID << ',' << address << ',' 
                 << phoneNumber << ','<< people << ',' << days << ',' << roomType << ',' 
                 << bills << ',' << payAdvanced  << ',' << CheckInHour << ',' << CheckInMinute << '\n';
    }

    allInfoFile.close();
    tempFile.close();

    if (recordUpdated) {
        remove("all_info.csv");
        rename("all_info_temp.csv", "all_info.csv");
    } else {
        remove("all_info_temp.csv");
        cout << "\n\t\t\t\t\t\t\t\tNo matching reservation found in all_info.csv.\n";
    }
}

//-----------------------------------------------Customer: Check Out-----------------------------------------------//
void Customer ::customer_check_out() 
{
    system("cls");
    header();
    cout << "\n\t\t\t\t\t\t\t\t--- Customer Check-Out Process ---\n";

    string inputName, inputPhoneNumber;

    // Get the current time
    time_t now = time(0);
    tm *localTime = localtime(&now);
    stringstream checkOutTimeStream;
    checkOutTimeStream << setw(2) << setfill('0') << localTime->tm_hour << ":"
                       << setw(2) << setfill('0') << localTime->tm_min;
    string checkOutTime = checkOutTimeStream.str();

    cout << "\n\t\t\t\t\t\t\t\tEnter Name for Confirmation          : ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any leftover input
    getline(cin, inputName);
    cout << "\t\t\t\t\t\t\t\tEnter Phone Number for Confirmation  : ";
    getline(cin, inputPhoneNumber);

    // Open customer_info.csv for reading
    ifstream customerFile("customer_info.csv");
    if (!customerFile.is_open()) {
        cerr << "\t\t\t\t\t\t\t\tError: Could not open customer_info.csv for reading.\n";
        return;
    }

    // Create a temp file to store updated customer data
    ofstream tempFile("customer_info_temp.csv");
    if (!tempFile.is_open()) {
        cerr << "\t\t\t\t\t\t\t\tError: Could not open temp file for writing.\n";
        return;
    }

    string customerLine;
    bool customerFound = false;
    string roomID, customerDay, customerMonth, customerYear; // Store data for later use

    while (getline(customerFile, customerLine)) {
        stringstream ss(customerLine);
        string roomIDFromFile, day, month, year, hour, minute, name, ID, address, phoneNumber, people, days, Roomtype, bills, PayAdvanced;

        // Extract fields from customer_info.csv
        getline(ss, roomIDFromFile, ',');
        getline(ss, day, ',');
        getline(ss, month, ',');
        getline(ss, year, ',');
        getline(ss, hour, ',');
        getline(ss, minute, ',');
        getline(ss, name, ',');
        getline(ss, ID, ',');
        getline(ss, address, ',');
        getline(ss, phoneNumber, ',');
        getline(ss, people, ',');
        getline(ss, days, ',');
        getline(ss, Roomtype, ',');
        getline(ss, bills, ',');
        getline(ss, PayAdvanced, ',');

        // Compare input with CSV data
        if (strcasecmp(name.c_str(), inputName.c_str()) == 0 &&
            strcasecmp(phoneNumber.c_str(), inputPhoneNumber.c_str()) == 0) {
            customerFound = true;
            roomID = roomIDFromFile;    // Save Room ID for later
            customerDay = day;         // Save Check-in Day
            customerMonth = month;     // Save Check-in Month
            customerYear = year;       // Save Check-in Year
            continue;                  // Skip this line to remove it
        }

        // Write remaining lines to the temp file
        tempFile << customerLine << "\n";
    }

    customerFile.close();
    tempFile.close();

    // Replace original customer_info.csv
    if (customerFound) {
        remove("customer_info.csv");
        rename("customer_info_temp.csv", "customer_info.csv");

        // Update room status in rooms.csv using updateRoomsFile
        try {
            updateRoomsFile(stoi(roomID), "Available");
        } catch (const invalid_argument&) {
            cerr << "\t\t\t\t\t\t\t\tError: Invalid Room ID in customer_info.csv.\n";
            return;
        }

        // Update all_info.csv
        ifstream allInfoFile("all_info.csv");
        ofstream tempAllInfoFile("all_info_temp.csv");

        if (!allInfoFile.is_open() || !tempAllInfoFile.is_open()) {
            cerr << "\t\t\t\t\t\t\t\tError: Could not open all_info.csv for reading or writing.\n";
            return;
        }

        string allInfoLine;

        while (getline(allInfoFile, allInfoLine)) {
            stringstream ss(allInfoLine);
            string tempRoomID, day, month, year, hour, minute, name, ID, address, phoneNumber, people, days, Roomtype, bills, PayAdvanced, CheckIn_hour, CheckIn_minute;

            // Extract fields from all_info.csv
            getline(ss, tempRoomID, ',');
            getline(ss, day, ',');
            getline(ss, month, ',');
            getline(ss, year, ',');
            getline(ss, hour, ',');
            getline(ss, minute, ',');
            getline(ss, name, ',');
            getline(ss, ID, ',');
            getline(ss, address, ',');
            getline(ss, phoneNumber, ',');
            getline(ss, people, ',');
            getline(ss, days, ',');
            getline(ss, Roomtype, ',');
            getline(ss, bills, ',');
            getline(ss, PayAdvanced, ',');
            getline(ss, CheckIn_hour, ',');
            getline(ss, CheckIn_minute, ',');

            if (tempRoomID == roomID) {
                // Add check-out time and prompt for feedback
                int bookingRating, cleanlinessRating;
                string review;

                cout << "\n\t\t\t\t\t\t\t\tCheck-Out Successful!\n";
                cout << "\t\t\t\t\t\t\t\tCheck-Out Time: " << checkOutTime << "\n";

                cout << "\n\t\t\t\t\t\t\t\tRate the booking service (1-10): ";
                cin >> bookingRating;
                cout << "\t\t\t\t\t\t\t\tRate the room cleanliness (1-10): ";
                cin >> cleanlinessRating;
                cin.ignore(); // Ignore leftover newline
                cout << "\t\t\t\t\t\t\t\tWrite a review (max 400 characters): ";
                getline(cin, review);

                // Write updated line with check-out details, ratings, and review
                tempAllInfoFile << tempRoomID << ',' << day << ',' << month << ',' << year << ',' 
                                << hour << ',' << minute << ',' << name << ',' << ID << ',' << address << ',' 
                                << phoneNumber << ',' << people << ',' << days << ',' << Roomtype << ',' 
                                << bills << ',' << PayAdvanced << ',' << CheckIn_hour << ',' << CheckIn_minute << ',' 
                                << localTime->tm_hour << ',' << localTime->tm_min << ',' << bookingRating << ',' 
                                << cleanlinessRating << ',' << "\"" << review << "\"" << '\n';
            } else {
                tempAllInfoFile << allInfoLine << '\n'; // Write unmodified line
            }
        }

        allInfoFile.close();
        tempAllInfoFile.close();

        // Replace original all_info.csv
        remove("all_info.csv");
        rename("all_info_temp.csv", "all_info.csv");

        cout << "\n\t\t\t\t\t\t\t\tYour feedback has been recorded. Thank you!\n";

    } else {
        remove("customer_info_temp.csv");
        cout << "\n\t\t\t\t\t\t\t\tNo matching reservation found. Please check your details.\n";
    }
}

//-----------------------------------------------Header-----------------------------------------------//

void Hotel::header()
{
    cout << "\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|" << endl;
    cout << "\t\t\t\t\t\t\t|                                                       |" << endl;
    cout << "\t\t\t\t\t\t\t|                 Hotel Management System               |" << endl;
    cout << "\t\t\t\t\t\t\t|                                                       |" << endl;
    cout << "\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|" << endl;
}

//-----------------------------------------------Main Menu Interface-----------------------------------------------//
void Hotel::menu()
{
    Customer u;
    Admin a;
    system("cls");
    int n;
    char ch;
    char c = 'Y';
    int flag = 0;

    cout << "\t\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-|" << endl;
    cout << "\t\t\t\t\t\t\t\t|                                      |" << endl;
    cout << "\t\t\t\t\t\t\t\t|      HOTEL MANAGEMENT SYSTEM         |" << endl;
    cout << "\t\t\t\t\t\t\t\t|                                      |" << endl;
    cout << "\t\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-|" << endl;
    cout << "\t\t\t\t\t\t\t\t|                                      |" << endl;
    cout << "\t\t\t\t\t\t\t\t|  1. ADMIN                            |" << endl;
    cout << "\t\t\t\t\t\t\t\t|  2. USER                             |" << endl;
    cout << "\t\t\t\t\t\t\t\t|  3. EXIT                             |" << endl;
    cout << "\t\t\t\t\t\t\t\t|                                      |" << endl;
    cout << "\t\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-|" << endl;
    cout << "\t\t\t\t\t\t\t\t|                                      |" << endl;
    cout << "\t\t\t\t\t\t\t\t|    Choose Option : {1/2/3}           |" << endl;
    cout << "\t\t\t\t\t\t\t\t|                                      |" << endl;
    cout << "\t\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-|" << endl;
    cout << endl;
    cout << "\t\t\t\t\t\t\t\tEnter Your Option : ";
    cin >> n;
    switch (n)
    {

    case 1:
        system("cls");
        a.admin_login_account();
        break;

    case 2:
        system("cls");
        u.customer_menu();
        break;

    case 3:
        cout << "\n\n\t\t\t\t\t\t\t\tThank you for using the application" << endl;
        exit(0);

    default:
        cout << "\t\t\t\t\t\t\t\tInvalid Input" << endl;
        exit(0);
    }
}

//-----------------------------------------------Customer : Menu-----------------------------------------------//
void Customer::customer_menu()
{
    for (int i = 0; i < 2; i++)
    {
        system("cls");
    }
    header();   
    while (1)
    {
        int choice;
        cout << "\t\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-|" << endl;
        cout << "\t\t\t\t\t\t\t\t|                                      |" << endl;
        cout << "\t\t\t\t\t\t\t\t|              USER MENU               |" << endl;
        cout << "\t\t\t\t\t\t\t\t|                                      |" << endl;
        cout << "\t\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-|" << endl;
        cout << "\t\t\t\t\t\t\t\t|                                      |" << endl;
        cout << "\t\t\t\t\t\t\t\t|  1. Check-In                         |" << endl;
        cout << "\t\t\t\t\t\t\t\t|  2. Check-Out                        |" << endl;
        cout << "\t\t\t\t\t\t\t\t|  3. Exit                             |" << endl;
        cout << "\t\t\t\t\t\t\t\t|                                      |" << endl;
        cout << "\t\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-|" << endl;
        cout << "\t\t\t\t\t\t\t\t|                                      |" << endl;
        cout << "\t\t\t\t\t\t\t\t|       Choose Option : [1/2/3}        |" << endl;
        cout << "\t\t\t\t\t\t\t\t|                                      |" << endl;
        cout << "\t\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-|" << endl;
        cin >> choice;

        switch (choice)
        {
            system("cls");
        case 1:
            system("cls");
            customer_check_in();
            cout << "\n\n\t\t\t\t\t\t\t\tPress any key to continue " << endl;
            _getch();
            customer_menu();
            break;

        case 2:
            system("cls");
            customer_check_out();
            cout << "\n\n\t\t\t\t\t\t\t\tPress any key to continue " << endl;
            _getch();
            customer_menu();
            break;

        case 3:
            system("cls");
            menu();
            break;

        default:
            cout << "\t\t\t\t\t\t\t\tInvalid input " << endl;
            cout << "\t\t\t\t\t\t\t\tPress any key to return to main menu " << endl;
            _getch();  
            break;
        }
        _getch();
    }
}

//-----------------------------------------------Admin: Log In-----------------------------------------------//
void Admin::admin_login_account()
{
    string adminuname, adminpasswd;
    string useruname, userpasswd;
    char ch;
    cout << "\t\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-|" << endl;
    cout << "\t\t\t\t\t\t\t\t|                                      |" << endl;
    cout << "\t\t\t\t\t\t\t\t|              ADMIN LOGIN             |" << endl;
    cout << "\t\t\t\t\t\t\t\t|                                      |" << endl;
    cout << "\t\t\t\t\t\t\t\t|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-|" << endl;
    cout << "\t\t\t\t\t\t\t\tEnter username: ";
    cin.ignore();
    getline(cin, adminuname);
    cout << "\t\t\t\t\t\t\t\tEnter password: ";
    ch = _getch();
    while (ch != 13) // Check for "Enter" key (key code 13)
    {
        adminpasswd.push_back(ch);
        cout << "*";
        ch = _getch();
    }

    if (adminpasswd == getPassword() && adminuname == getUsername())
    {
        cout << "\n\n\t\t\t\t\t\t\t\t| Verfiying Admin |\n";
        cout << "\t\t\t\t\t\t\t\t";
        for (int a = 1; a < 8; a++)
        {
            Sleep(500);
            cout << "...";
        }
        cout << "\n\t\t\t\t\t\t\t\tAccess Granted..\n\n";
        cout << "\n\t\t\t\t\t\t\t\tPress any key to continue..";
        _getch();
        admin_menu();
    }
    else
    {
        cout << endl;
        cout << "\n\n\t\t\t\t\t\t\t\t| Verfiying Admin |\n";
        cout << "\t\t\t\t\t\t\t\t";
        for (int a = 1; a < 8; a++)
        {
            Sleep(500);
            cout << "...";
        }
        cout << endl;
        cout << "\n\t\t\t\t\t\t\t\tWrong Credentials" << endl;
        cout << "\t\t\t\t\t\t\t\tYou will be redirected to Main Menu..." << endl;
        Sleep(3000);
        menu();
    }
    _getch();
}

int main()
{
    Hotel h;
    h.menu();
    
    return 0;
}
