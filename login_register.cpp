#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
#include<algorithm>
using namespace std;

// Function to validate password strength
bool validatePassword(string password)
{
    if(password.length() < 6)
    {
        cout << "  [ERROR] Password must be at least 6 characters long!" << endl;
        return false;
    }
    
    bool hasUpper = false, hasLower = false, hasDigit = false;
    
    for(char c : password)
    {
        if(isupper(c)) hasUpper = true;
        if(islower(c)) hasLower = true;
        if(isdigit(c)) hasDigit = true;
    }
    
    if(!hasUpper)
    {
        cout << "  [ERROR] Password must contain at least one uppercase letter!" << endl;
        return false;
    }
    
    if(!hasLower)
    {
        cout << "  [ERROR] Password must contain at least one lowercase letter!" << endl;
        return false;
    }
    
    if(!hasDigit)
    {
        cout << "  [ERROR] Password must contain at least one digit!" << endl;
        return false;
    }
    
    return true;
}

// Function to validate username
bool validateUsername(string username)
{
    if(username.length() < 3)
    {
        cout << "  [ERROR] Username must be at least 3 characters long!" << endl;
        return false;
    }
    
    if(username.length() > 20)
    {
        cout << "  [ERROR] Username must not exceed 20 characters!" << endl;
        return false;
    }
    
    for(char c : username)
    {
        if(!isalnum(c) && c != '_')
        {
            cout << "  [ERROR] Username can only contain letters, digits, and underscores!" << endl;
            return false;
        }
    }
    
    return true;
}

// Function to check if username already exists
bool usernameExists(string username)
{
    ifstream file("users_database.txt");
    string line, fileUsername;
    
    if(file.is_open())
    {
        while(getline(file, line))
        {
            size_t pos = line.find(":");
            if(pos != string::npos)
            {
                fileUsername = line.substr(0, pos);
                if(fileUsername == username)
                {
                    file.close();
                    return true;
                }
            }
        }
        file.close();
    }
    
    return false;
}

// Registration Function
void registration()
{
    string username, password, confirmPassword;
    
    cout << "\n========== USER REGISTRATION ==========" << endl;
    
    while(true)
    {
        cout << "\nEnter Username: ";
        getline(cin, username);
        
        if(!validateUsername(username))
        {
            continue;
        }
        
        if(usernameExists(username))
        {
            cout << "  [ERROR] Username already exists! Please choose a different username." << endl;
            continue;
        }
        
        break;
    }
    
    while(true)
    {
        cout << "\nEnter Password (Min 6 chars, 1 uppercase, 1 lowercase, 1 digit): ";
        getline(cin, password);
        
        if(!validatePassword(password))
        {
            continue;
        }
        
        cout << "Confirm Password: ";
        getline(cin, confirmPassword);
        
        if(password != confirmPassword)
        {
            cout << "  [ERROR] Passwords do not match! Please try again." << endl;
            continue;
        }
        
        break;
    }
    
    // Store credentials in file
    ofstream file("users_database.txt", ios::app);
    
    if(file.is_open())
    {
        file << username << ":" << password << endl;
        file.close();
        
        cout << "\n[SUCCESS] User registered successfully!" << endl;
        cout << "Username: " << username << endl;
        cout << "======================================\n" << endl;
    }
    else
    {
        cout << "\n[ERROR] Failed to open database file!" << endl;
    }
}

// Login Function
void login()
{
    string username, password;
    string fileUsername, filePassword;
    bool found = false;
    
    cout << "\n========== USER LOGIN ==========" << endl;
    
    cout << "\nEnter Username: ";
    getline(cin, username);
    
    cout << "Enter Password: ";
    getline(cin, password);
    
    ifstream file("users_database.txt");
    
    if(file.is_open())
    {
        string line;
        while(getline(file, line))
        {
            size_t pos = line.find(":");
            if(pos != string::npos)
            {
                fileUsername = line.substr(0, pos);
                filePassword = line.substr(pos + 1);
                
                if(fileUsername == username && filePassword == password)
                {
                    found = true;
                    break;
                }
            }
        }
        file.close();
    }
    else
    {
        cout << "\n[ERROR] Database file not found! No users registered yet." << endl;
        cout << "Please register first." << endl;
        cout << "==============================\n" << endl;
        return;
    }
    
    if(found)
    {
        cout << "\n[SUCCESS] Login successful!" << endl;
        cout << "Welcome, " << username << "!" << endl;
        cout << "==============================\n" << endl;
    }
    else
    {
        cout << "\n[ERROR] Invalid username or password!" << endl;
        cout << "==============================\n" << endl;
    }
}

// Main menu
void displayMenu()
{
    cout << "\n========== LOGIN & REGISTRATION SYSTEM ==========" << endl;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Exit" << endl;
    cout << "=================================================" << endl;
    cout << "Enter your choice (1-3): ";
}

int main()
{
    int choice;
    
    cout << "\n**** Welcome to Login & Registration System ****\n" << endl;
    
    while(true)
    {
        displayMenu();
        cin >> choice;
        cin.ignore(); // To ignore the newline character after integer input
        
        switch(choice)
        {
            case 1:
                registration();
                break;
                
            case 2:
                login();
                break;
                
            case 3:
                cout << "\n[INFO] Thank you for using our system. Goodbye!" << endl;
                cout << "================================================\n" << endl;
                return 0;
                
            default:
                cout << "\n[ERROR] Invalid choice! Please enter 1, 2, or 3." << endl;
        }
    }
    
    return 0;
}
