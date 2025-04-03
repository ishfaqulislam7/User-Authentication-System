
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class registration
{
    string Username, Email, Password;
    string Entered_Username, Entered_Email, Entered_Password;
    fstream file;

public:
    void Login();
    void Signup();
    void ForgotPassword();

} obj;

int main()
{
    char options;
    bool exitprogram = false;

    while (!exitprogram)
    {
        system("clear");

        cout << "══════════════════════════════════════════" << endl;
        cout << "║║                                      ║║" << endl;
        cout << "║║           1. Login                   ║║" << endl;
        cout << "║║           2. Sign Up                 ║║" << endl;
        cout << "║║           3. Forgot Password         ║║" << endl;
        cout << "║║           4. Exit                    ║║" << endl;
        cout << "║║                                      ║║" << endl;
        cout << "══════════════════════════════════════════" << endl;
        cout << endl;
        cout << "Enter Your Option: ";
        cin >> options;
        switch (options)
        {
        case '1':
            cin.ignore();
            obj.Login();
            break;
        case '2':
            cin.ignore();
            obj.Signup();
            break;
        case '3':
            cin.ignore();
            obj.ForgotPassword();
            break;
        case '4':
            cout << endl;
            cout << "----------- GOODBYE! -----------" << endl;
            cout << endl;
            return 0;
            break;
        default:
            cout << "Invalid Options!" << endl;
        }
        if (!exitprogram)
        {
            cout << "Press Enter To Return To Main Menu.";
            // cin.ignore();
            if (cin.peek() == '\n')
            {
                cin.ignore();
            }
        }
    }
    return 0;
}

void registration::Signup()
{
    cout << endl;
    cout << "Enter Your Username: ";
    getline(cin, Username);
    cout << "Enter Your Email: ";
    getline(cin, Email);
    cout << "Enter Your Password: ";
    getline(cin, Password);
    cout << endl;
    file.open("Login.txt", ios::out | ios::app);
    file << Username << "*" << Email << "*" << Password << endl;
    file.close();
}

void registration::Login()
{
    cout << endl;
    cout << "Enter Your Username: ";
    getline(cin, Entered_Username);
    cout << "Enter Your Password: ";
    getline(cin, Entered_Password);

    file.open("Login.txt", ios ::in);

    // Reset file position to the beginning
    file.clear();            // Clear any error flags
    file.seekg(0, ios::beg); // Move to the beginning

    if (!file)
    {
        cout << "Error: Cannot open file or file does not exist!" << endl;
        return;
    }

    bool found = false;

    getline(file, Username, '*');
    getline(file, Email, '*');
    getline(file, Password, '\n');

    while (!file.eof())
    {
        if (Username == Entered_Username)
        {
            if (Password == Entered_Password)
            {
                cout << "\nAccount Login Succesfull!" << endl;
                cout << "\nUsername: " << Username;
                cout << "\nEmail: " << Email << endl;
                cout << endl;
            }
            else
            {
                cout << endl;
                cout << "Password is Incorrect!" << endl;
                cout << endl;
            }
        }
        else
        {
            cout << endl;
            cout << "Username Doesn't Exist!" << endl;
            cout << endl;
        }
        getline(file, Username, '*');
        getline(file, Email, '*');
        getline(file, Password, '\n');
    }
    file.close();
}

void registration::ForgotPassword()
{
    bool found = false;

    cout << endl;
    cout << "Enter Your Username: ";
    getline(cin, Entered_Username);
    cout << "Enter Your Email: ";
    getline(cin, Entered_Email);
    cout << endl;

    file.open("login.txt", ios::in);

    // Reset file position to the beginning
    file.clear();            // Clear any error flags
    file.seekg(0, ios::beg); // Move to the beginning

    if (!file)
    {
        cout << "Error: Cannot open file or file does not exist!" << endl;
        return;
    }

    getline(file, Username, '*');
    getline(file, Email, '*');
    getline(file, Password, '\n');

    fstream tempFile;
    tempFile.open("temp.txt", ios::out);

    while (!file.eof())
    {
        if (file.eof())
            break;

        if (Username == Entered_Username)
        {
            if (Email == Entered_Email)
            {
                cout << "Account Found!" << endl;
                cout << "Account Password: " << Password << endl;
                cout << endl;

                ////////////////////////////// CHANGE PASSWORD ///////////////////////////////
                string choice;
                cout << "Do You Want To Change Your Password? (Yes/No)" << endl;
                cout << "Enter: ";
                cin >> choice;
                cin.ignore();
                cout << endl;

                if (choice == "yes" || choice == "Yes" || choice == "YES")
                {
                    string NewPassword;
                    cout << "Enter New Password: ";
                    getline(cin, NewPassword);

                    tempFile << Username << "*" << Email << "*" << NewPassword << endl;
                    cout << "Password Changed Successfully!" << endl;
                    cout << endl;
                }
                else
                {
                    cout << "Password Was Not Changed!" << endl;
                    tempFile << Username << "*" << Email << "*" << Password << endl;
                }
                /////////////////////////////////////////////////////////////////////////////////
            }
            else
            {
                cout << "Account Not Found!" << endl;
                tempFile << Username << "*" << Email << "*" << Password << endl;
            }
        }
        else
        {
            cout << "Account Not Found! Username or Email Doesn't Match." << endl;
            cout << endl;
            tempFile << Username << "*" << Email << "*" << Password << endl;
        }
        getline(file, Username, '*');
        getline(file, Email, '*');
        getline(file, Password, '\n');
    }

    file.close();
    tempFile.close();

    remove("Login.txt");
    rename("temp.txt", "Login.txt");
}
