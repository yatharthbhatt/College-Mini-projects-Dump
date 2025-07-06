#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <cctype>

#define FILE_NAME "accounts.csv"
#define COMPLAINT_FILE "complaints.csv"
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin123"

using namespace std;

struct Account
{
    string username;
    string password;
};

struct Complaint
{
    int complaint_id;
    string student_name;
    long int student_id;
    string department;
    int year_of_study;
    string email;
    string phone;
    string category;
    string description;
    string date_filed;
    string status;
    string assigned_authority;
};

string currentUser;

// Utility Functions
bool isLeapYear(int year)
{
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

bool isValidDate(const string &date)
{
    if (date.length() != 8)
        return false;
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(2, 2));
    int year = stoi(date.substr(4, 4));

    if (year < 2010 || year > 2024)
        return false;

    vector<int> daysInMonth = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear(year))
        daysInMonth[2] = 29;

    if (month < 1 || month > 12)
        return false;
    if (day < 1 || day > daysInMonth[month])
        return false;

    return true;
}

bool isNumber(const string &s)
{
    return all_of(s.begin(), s.end(), ::isdigit);
}

// Complaint Functions
void addComplaint()
{
    Complaint complaint;
    string temp;
    ofstream file(COMPLAINT_FILE, ios::app);
    if (!file.is_open())
    {
        cerr << "Error opening complaint file!" << endl;
        return;
    }

    cout << "Enter Complaint ID: ";
    while (!(cin >> complaint.complaint_id))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid ID! Try again: ";
    }
    cin.ignore();

    do
    {
        cout << "Enter Student Name: ";
        getline(cin, complaint.student_name);
        if (all_of(complaint.student_name.begin(), complaint.student_name.end(), [](char c)
                   { return isalpha(c) || isspace(c); }))
            break;
        cout << "Invalid name! Try again.\n";
    } while (true);

    cout << "Enter Student ID: ";
    while (!(cin >> complaint.student_id))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid ID! Try again: ";
    }
    cin.ignore();

    do
    {
        cout << "Enter Department [Computer Science, Information Technology, Electronics and Communication]: ";
        getline(cin, complaint.department);
        string dept = complaint.department;
        transform(dept.begin(), dept.end(), dept.begin(), ::tolower);
        if (dept == "computer science" || dept == "information technology" || dept == "electronics and communication")
            break;
        cout << "Invalid department.\n";
    } while (true);

    cout << "Enter Year of Study [2010-2025]: ";
    while (!(cin >> complaint.year_of_study) || complaint.year_of_study < 2010 || complaint.year_of_study > 2025)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid year! Try again: ";
    }
    cin.ignore();

    cout << "Enter Email: ";
    getline(cin, complaint.email);

    do
    {
        cout << "Enter Phone Number: ";
        getline(cin, complaint.phone);
    } while (complaint.phone.length() != 10 || !isNumber(complaint.phone));

    do
    {
        cout << "Enter Complaint Category (Academic, Administrative, Infrastructure): ";
        getline(cin, complaint.category);
        string cat = complaint.category;
        transform(cat.begin(), cat.end(), cat.begin(), ::tolower);
        if (cat == "academic" || cat == "administrative" || cat == "infrastructure")
            break;
        cout << "Invalid category.\n";
    } while (true);

    cout << "Enter Complaint Description: ";
    getline(cin, complaint.description);

    do
    {
        cout << "Enter Date Filed (ddmmyyyy): ";
        getline(cin, complaint.date_filed);
    } while (!isValidDate(complaint.date_filed));

    complaint.status = "Pending";
    complaint.assigned_authority = "Not Assigned";

    file << complaint.complaint_id << ","
         << complaint.student_name << ","
         << complaint.student_id << ","
         << complaint.department << ","
         << complaint.year_of_study << ","
         << complaint.email << ","
         << complaint.phone << ","
         << complaint.category << ","
         << complaint.description << ","
         << complaint.date_filed << ","
         << complaint.status << ","
         << complaint.assigned_authority << "\n";

    file.close();
    cout << "Complaint submitted!\n";
}

void viewComplaints()
{
    ifstream file(COMPLAINT_FILE);
    if (!file.is_open())
    {
        cout << "No complaints to show.\n";
        return;
    }

    string line;
    cout << "\n--- Complaints ---\n";
    while (getline(file, line))
    {
        stringstream ss(line);
        string field;
        vector<string> fields;
        while (getline(ss, field, ','))
        {
            fields.push_back(field);
        }
        if (fields.size() >= 12)
        {
            cout << "\nID: " << fields[0]
                 << "\nName: " << fields[1]
                 << "\nStudent ID: " << fields[2]
                 << "\nDepartment: " << fields[3]
                 << "\nYear: " << fields[4]
                 << "\nEmail: " << fields[5]
                 << "\nPhone: " << fields[6]
                 << "\nCategory: " << fields[7]
                 << "\nDescription: " << fields[8]
                 << "\nDate: " << fields[9]
                 << "\nStatus: " << fields[10]
                 << "\nAuthority: " << fields[11]
                 << "\n------------------------";
        }
    }
    file.close();
}

void deleteComplaint()
{
    int id;
    cout << "Enter Complaint ID to delete: ";
    cin >> id;

    ifstream in(COMPLAINT_FILE);
    ofstream out("temp.csv");
    string line;
    bool found = false;

    while (getline(in, line))
    {
        stringstream ss(line);
        string field;
        getline(ss, field, ',');
        if (stoi(field) != id)
        {
            out << line << "\n";
        }
        else
        {
            found = true;
        }
    }

    in.close();
    out.close();
    remove(COMPLAINT_FILE);
    rename("temp.csv", COMPLAINT_FILE);

    if (found)
        cout << "Complaint deleted.\n";
    else
        cout << "Complaint ID not found.\n";
}

void searchComplaint()
{
    ifstream file(COMPLAINT_FILE);
    if (!file.is_open())
    {
        cout << "Error: File not found.\n";
        return;
    }

    int choice;
    cout << "Search by:\n1. Complaint ID\n2. Student ID\nEnter choice: ";
    cin >> choice;

    string line;
    bool found = false;

    if (choice == 1)
    {
        int search_id;
        cout << "Enter Complaint ID: ";
        cin >> search_id;
        while (getline(file, line))
        {
            stringstream ss(line);
            string field;
            getline(ss, field, ',');
            if (stoi(field) == search_id)
            {
                cout << "Found Complaint: " << line << endl;
                found = true;
                break;
            }
        }
    }
    else if (choice == 2)
    {
        long int search_id;
        cout << "Enter Student ID: ";
        cin >> search_id;
        while (getline(file, line))
        {
            stringstream ss(line);
            string field;
            getline(ss, field, ','); // complaint_id
            getline(ss, field, ','); // student_name
            getline(ss, field, ','); // student_id
            if (stol(field) == search_id)
            {
                cout << "Found Complaint: " << line << endl;
                found = true;
            }
        }
    }

    if (!found)
        cout << "No results found.\n";
    file.close();
}

void generateReport()
{
    ifstream file(COMPLAINT_FILE);
    string line;
    int academic = 0, admin = 0, infra = 0;
    while (getline(file, line))
    {
        stringstream ss(line);
        string field;
        for (int i = 0; i < 8; ++i)
        {
            getline(ss, field, ',');
        }
        string cat = field;
        transform(cat.begin(), cat.end(), cat.begin(), ::tolower);
        if (cat == "academic")
            academic++;
        else if (cat == "administrative")
            admin++;
        else if (cat == "infrastructure")
            infra++;
    }
    cout << "\nReport:\nAcademic: " << academic << "\nAdministrative: " << admin << "\nInfrastructure: " << infra << endl;
    file.close();
}

// Account Functions
void createAccount()
{
    Account newAcc, temp;
    cout << "Choose username: ";
    cin.ignore();
    getline(cin, newAcc.username);
    cout << "Choose password: ";
    getline(cin, newAcc.password);

    ifstream in(FILE_NAME);
    string line;
    while (getline(in, line))
    {
        stringstream ss(line);
        string uname, pwd;
        getline(ss, uname, ',');
        getline(ss, pwd, ',');
        if (uname == newAcc.username)
        {
            cout << "Username exists!\n";
            return;
        }
    }
    in.close();

    ofstream out(FILE_NAME, ios::app);
    out << newAcc.username << "," << newAcc.password << "\n";
    out.close();
    cout << "Account created.\n";
}

int login()
{
    cout << "Enter username: ";
    cin.ignore();
    getline(cin, currentUser);

    cout << "Enter password: ";
    string password;
    getline(cin, password);

    if (currentUser == ADMIN_USERNAME && password == ADMIN_PASSWORD)
    {
        cout << "Admin login successful.\n";
        return 2; // Admin
    }

    ifstream file(FILE_NAME);
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string uname, pwd;
        getline(ss, uname, ',');
        getline(ss, pwd, ',');
        if (uname == currentUser && pwd == password)
        {
            cout << "Login successful.\n";
            return 1; // Student
        }
    }
    cout << "Login failed.\n";
    return 0; // Failed
}

int main()
{
    int choice;
    do
    {
        cout << "\n------------------------------------------------------------- Student Grievance Redressal Cell --------------------------------------------------------------\n";
        cout << "1. Create Account\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            createAccount();
            break;

        case 2:
        {
            int role = login();
            if (role == 1)
            { // Student
                int studentChoice;
                do
                {
                    cout << "\nStudent Menu\n";
                    cout << "1. File Complaint\n";
                    cout << "2. View Complaints\n";
                    cout << "3. Search Complaint\n";
                    cout << "4. Logout\n";
                    cout << "Enter choice: ";
                    cin >> studentChoice;

                    switch (studentChoice)
                    {
                    case 1:
                        addComplaint();
                        break;
                    case 2:
                        viewComplaints();
                        break;
                    case 3:
                        searchComplaint();
                        break;
                    case 4:
                        cout << "Logging out...\n";
                        break;
                    default:
                        cout << "Invalid choice.\n";
                    }
                } while (studentChoice != 4);
            }
            else if (role == 2)
            { // Admin
                int adminChoice;
                do
                {
                    cout << "\nAdmin Menu\n";
                    cout << "1. View All Complaints\n";
                    cout << "2. Delete Complaint\n";
                    cout << "3. Search Complaint\n";
                    cout << "4. Generate Report\n";
                    cout << "5. Logout\n";
                    cout << "Enter choice: ";
                    cin >> adminChoice;

                    switch (adminChoice)
                    {
                    case 1:
                        viewComplaints();
                        break;
                    case 2:
                        deleteComplaint();
                        break;
                    case 3:
                        searchComplaint();
                        break;
                    case 4:
                        generateReport();
                        break;
                    case 5:
                        cout << "Logging out...\n";
                        break;
                    default:
                        cout << "Invalid choice.\n";
                    }
                } while (adminChoice != 5);
            }
            break;
        }

        case 3:
            cout << "Exiting the system.\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
