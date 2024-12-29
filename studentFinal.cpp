/*
Student Record Management System
----------------------------------k
o Recording student & course info
o Course registration
o Checking course pre-request
o Find semester load
o Compute cumulative grade
o Generate student rank based on CGP
o Determine Student status (pass/warning/dismissal)
o Produce various statistical report (such as No. of passed, warned
*/
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <string.h>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <conio.h> //to use getch()

using namespace std;

int stud_num, id, total_stud = 0, choice;
bool shut = false;

// it will be unneccessory
struct Mark
{
    float FII, DT, STAT, DB, DL;
};

// for course registration
struct course
{
    string subject;
};

struct Address
{
    string city, phoneNumber;
};

struct Student
{
    string full_name, stud_Id;
    int age;
    char sex;
    string address, status, grade[5];
    Mark mark;
    float cgp;
} stud[5000], Stud, temp; // For datain etc that needs all data we take emp or emp[] array but for delete search etc
                          //  that is need only to work with a single data we take Stud.

Student dataIn(Student stud[]);
void dataDisp();
void Delete(Student stud);
void update(Student stud);
void Search(Student stud);
Student runk(Student stud[]);
void statstics(Student stud[]);
void course_Dtails();
string grade_cul(float mark);
// string course_Registration();
void menu();
void login();
void aboutUs();
void contactUs();
void generateCSV();
int main()
{
    cout << "\n\n\n                                WElcome to Student Recored Management System!"
            " \n\n                              STARTING THE PROGRAM NOW"
            "\n\n                                 LOADING...";
    Sleep(1000);
    system("cls");
    login(); // login first
    if (!shut)
    {
        menu();
    }

    return 0;
}

void menu()
{
    system("cls");

menustart:
    cout << "\t\t\t******************************************************************\n";
    cout << "\t\t\t//////////     Student management system         ///////////////\n";
    cout << "\t\t\t******************************************************************\n";
    //   dataIn(stud);
    cout << "\t\t\t~~~~~~\n\t\t\tMENU\n\t\t\t~~~~~~\n\n";
    cout << "\t\t\t1. Add Record\n";
    cout << "\t\t\t2. Display Record\n"; // we can add \a to add some sound here
    cout << "\t\t\t3. Modify Record\n";
    cout << "\t\t\t4. Delete Record\n";
    cout << "\t\t\t5. Search Record-------------(Modified Feature)\n";
    cout << "\t\t\t6. Rank of students\n";
    cout << "\t\t\t7. Statistics \n";
    cout << "\t\t\t8. Generate CSV file-----------(New Feature) \n";
    cout << "\t\t\t9. To see about course details\n";
    cout << "\t\t\t10. About Us \n";
    cout << "\t\t\t11.Contact Us \n";
    cout << "\t\t\t-1.Exit \n";
    cout << "\t\t\tchoice option:[ 1/2/3/4/5/6/7/8/9/10/-1 ]\n";
    cout << "\t\t\tEnter your choice: \n";
    int choice;
    cin >> choice;
    // course_Dtails();
    switch (choice)
    {
    case 1:
        dataIn(stud);
        system("cls");
        goto menustart;
        break;
    case 2:
        dataDisp();
        break;
    case 3:
        update(Stud);
        break;
    case 4:
        Delete(Stud);
        break;
    case 5:
        Search(Stud);
        break;
    case 6:
        runk(stud);
        cout << "\t\t\tyour command is done successfully \n display the data to see rank of the student\n";
        break;
    case 7:
        statstics(stud);
        break;
    case 8:
        generateCSV();
        cout << "CSV file 'students.csv' has been created." << endl;
        break;
    case 9:
        course_Dtails();
        break;
    case 10:
        aboutUs();
        break;
    case 11:
        contactUs();
        break;
    case -1:
        goto a;
        break;
    default:
        cout << "Invalid choice...Try again...";
    }
    cout << "\n\t\t\tdo you want to continue? y/n: ";
    char menus;
    cin >> menus;
    if (menus == 'y' || menus == 'Y')
    {
        system("cls");
        cout << endl
             << endl;
        goto menustart;
    }
a:
    system("cls");
    cout << "\n\n\n\a                                Good by\n\n                              Logout ...";
    Sleep(2000);
    system("cls");
    system("exit");
}

// it will be modified
void course_Dtails()
{

    cout << "////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////////////          Course Details of software engineering Department   //////////////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////\n\n";

    cout << "////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "////  Course Name       |Course Code  |   Credit_hour | pre_requests                ////\n";
    cout << "----------------------------------------------------------------------------------------\n";
    cout << "////  Programming II     FFII             3             Programming I               ////\n";
    cout << "////  Data communication DT               4             Software Requirement        ////\n";
    cout << "////  Statistics         Stat             3             None                        ////\n";
    cout << "////  DataBase           Db               4             None                        ////\n";
    cout << "////  Digital Logic      Dl               4             None                        ////\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////\n\n\n";
    //
    //   int ch;
    //   cout<<"To continue press 1 to quit press 0\n";
    //   cin>>ch;
    //   if(ch == 1) menu();
    //   else  system("exit");
}

// for data registration
Student dataIn(Student *stud) // All data are entered here
{
    cout << "\t\t\tHow many students do you want to add ?* ";
    cin >> stud_num;
    system("cls");

    cout << "--------------------------------------------------------------------------------------"
            "------------------------------------------------------------------------\n";
    cout << "------------------------------------------------------------------------ ADD RECORD ";
    cout << "-------------------------------------------------------------------------\n";

    fstream Outfile;
    Outfile.open("student.txt", ios::out | ios::app);

    for (int i = total_stud; i < stud_num + total_stud; i++)
    {
        cout << "Insert the detail of Student : \n";
        cout << "Enter the name of the student: " << endl;
        cin.ignore();
        getline(cin, stud[i].full_name);

    idagain:
        cout << "enter id : ";
        cin >> stud[i].stud_Id;

        // to check id if it is already registered.
        //*********************************************************************************//
        string line, name, idregistered;
        fstream CheckFile;
        CheckFile.open("student.txt", ios::in);
        if (!CheckFile)
        {
            // cout<< "!Sorry the file could not be opened....";
        }
        else
        {
            while (getline(CheckFile, line))
            {
                stringstream ss(line);
                getline(ss, name, ',');
                getline(ss, idregistered, ',');

                if (stud[i].stud_Id == idregistered)
                {
                    cout << "This Id is already registerd please try to use unregistered Id!\n";
                    goto idagain;
                }
            }
        }
        //*********************************************************************************//

        cout << "Enter age : ";
        cin >> stud[i].age;
    sex:
        cout << "Enter sex 'm' or 'f' : ";
        cin >> stud[i].sex;
        if (stud[i].sex != 'm' && stud[i].sex != 'f')
        {
            cout << "Invalid input \n";
            goto sex;
        }

        cout << "address : ";
        cin.ignore();
        getline(cin, stud[i].address);

        // result out of 100
        // FII, DT, STAT, DB, DL;
        cout << "Enter the result out of 100\n";
        cout << "Fundamental of Programming II: ";
        cin >> stud[i].mark.FII;
        // grade
        stud[i].grade[0] = grade_cul(stud[i].mark.FII);
        cout << "Data Communication: ";
        cin >> stud[i].mark.DT;
        stud[i].grade[1] = grade_cul(stud[i].mark.DT);
        cout << "Statistics: ";
        cin >> stud[i].mark.STAT;
        stud[i].grade[2] = grade_cul(stud[i].mark.STAT);
        cout << "Database: ";
        cin >> stud[i].mark.DB;
        stud[i].grade[3] = grade_cul(stud[i].mark.DB);
        cout << "Digital Logic: ";
        cin >> stud[i].mark.DL;
        stud[i].grade[4] = grade_cul(stud[i].mark.DL);
        float sum = 0, credit;
        // CGP
        for (int j = 0; j < 5; j++)
        {

            // float credit;
            if (j == 0)
                credit = 3;
            else if (j == 1)
                credit = 4;
            else if (j == 2)
                credit = 3;
            else if (j == 3)
                credit = 4;
            else
                credit = 4; // for the 4th subject

            // calculate CGP based on ones grade!
            if (stud[i].grade[j] == "A+" || stud[i].grade[j] == "A")
            {
                sum += 4 * credit;
            }
            else if (stud[i].grade[j] == "B+")
            {
                sum += 3.5 * credit;
            }
            else if (stud[i].grade[j] == "B")
            {
                sum += 3 * credit;
            }
            else if (stud[i].grade[j] == "C")
            {
                sum += 2.5 * credit;
            }
            else if (stud[i].grade[j] == "D")
            {
                sum += 1 * credit;
            }
            else if (stud[i].grade[j] == "F")
            {
                sum += 0 * credit;
            }
            else
            {
                sum = -1;
            }
            //        }
        }
        if (sum == -1)
            stud[i].cgp = 0; // here 0 means his grade information is incomplete
        else
            stud[i].cgp = sum / 18;
        if (stud[i].cgp >= 3.5)
        {
            stud[i].status = "Passed with excellent result";
        }
        else if (stud[i].cgp >= 2.5)
        {
            stud[i].status = "Passed";
        }
        else if (stud[i].cgp >= 2.0)
        {
            stud[i].status = "Warning";
        }
        else
        {
            stud[i].status = "Failed";
        }

        // save the file
        // taken courses :>> FII, DT, STAT, DB, DL;
    }
    for (int i = total_stud; i < stud_num + total_stud; i++)
    {
        Outfile << stud[i].full_name << ',' << stud[i].stud_Id << ',' << stud[i].sex << ',' << stud[i].age << ','
                << stud[i].address << ',' << stud[i].cgp << ',' << stud[i].status << ',' << stud[i].mark.FII << ','
                << stud[i].mark.DT << ',' << stud[i].mark.STAT << ',' << stud[i].mark.DB << ',' << stud[i].mark.DL << ',' << endl;
    }
    Outfile.close();
    total_stud += stud_num;
    return *stud;
}

void dataDisp()
{
    system("cls");

    cout << "-----------------------------------------------------------------------------------------"
            "---------------------------------------------------------------------\n";
    cout << "------------------------------------------------------------------------ DISPLAY RECORD ";
    cout << "-------------------------------------------------------------------------\n";

    cout << left << setw(32) << "NAME" << left << setw(15) << "ID" << left << setw(15) << "SEX"
         << left << setw(15) << "AGE" << left << setw(15) << "ADDRESS" << left << setw(15) << "GRADE" << left << setw(15) << "STATUS(pass/fail)\n"
         << "***************************************************************************"
            "**************************************************************"
         << endl
         << endl;

    string line, temp1, temp2, temp3, temp4, temp5, temp6;

    fstream InFile;
    InFile.open("student.txt", ios::in);

    if (!InFile)
    {
        cout << "!Sorry the file could not be opened....";
    }

    else
    {
        while (getline(InFile, line))
        {
            stringstream ss(line);
            getline(ss, Stud.full_name, ',');
            getline(ss, temp1, ',');

            getline(ss, temp2, ',');

            getline(ss, temp3, ',');
            getline(ss, temp4, ',');
            getline(ss, temp5, ',');
            getline(ss, temp6, ',');

            cout << left << setw(32) << Stud.full_name << left << setw(15) << temp1 << left << setw(15) << temp2 << left << setw(15) << temp3
                 << left << setw(15) << temp4 << left << setw(15) << temp5 << left << setw(15) << temp6 << endl
                 << endl;
        }
        InFile.close();
    }
}

void generateCSV() {
    fstream InFile;
    InFile.open("student.txt", ios::in);
    fstream OutFile;
    OutFile.open("students.csv", ios::out);

    if (!InFile) {
        cout << "!Sorry, the file could not be opened....";
    } else {
        OutFile << "NAME,ID,SEX,AGE,ADDRESS,GRADE,STATUS(pass/fail)" << endl; // Writing CSV header

        string line, temp1, temp2, temp3, temp4, temp5, temp6;
        while (getline(InFile, line)) {
            stringstream ss(line);
            getline(ss, temp1, ',');
            getline(ss, temp2, ',');
            getline(ss, temp3, ',');
            getline(ss, temp4, ',');
            getline(ss, temp5, ',');
            getline(ss, temp6, ',');

            OutFile << temp1 << "," << temp2 << "," << temp3 << "," << temp4 << "," << temp5 << "," << temp6 << endl;
        }
        InFile.close();
        OutFile.close();
    }
}

void Delete(Student stud)
{
    fstream file, file1;

    file.open("student.txt", ios::in);
    bool check = false;
    // bool deleted = false;

    string Id;

    if (!file)
    {
        cout << "File couldn't open...";
    }
    else
    {

        cout << "Enter the Id number you want to Delete: ";
        cin >> Id;
        file1.open("tempdata.txt", ios::app | ios::out);
        string line, temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8, temp9, temp10, temp11;

        while (file.good())
        {
            // name,Id,age,sex,address
            while (getline(file, line))
            {
                stringstream ss(line);
                getline(ss, stud.full_name, ',');
                getline(ss, temp1, ','); // id

                getline(ss, temp2, ','); // sex

                getline(ss, temp3, ','); // age

                getline(ss, temp4, ',');  // address
                getline(ss, temp5, ',');  // cgp
                getline(ss, temp6, ',');  // status
                getline(ss, temp7, ',');  // FII
                getline(ss, temp8, ',');  // DT
                getline(ss, temp9, ',');  // STAT
                getline(ss, temp10, ','); // DB
                getline(ss, temp11, ','); // DL

                if (temp1 == Id)
                {
                    check = true;
                    cout << "The data you want to delete!\n";
                    //
                    cout << left << setw(32) << "NAME" << left << setw(15) << "ID" << left << setw(15) << "SEX"
                         << left << setw(15) << "AGE" << left << setw(15) << "ADDRESS" << left << setw(15) << "GRADE"
                         << left << setw(15) << "STATUS(pass/fail)\n"
                         << "***************************************************************************"
                            "**************************************************"
                         << endl
                         << endl;

                    cout << left << setw(32) << stud.full_name << left << setw(15) << temp1 << left << setw(15) << temp2
                         << left << setw(15) << temp3 << left << setw(15) << temp4 << left << setw(15) << temp5
                         << left << setw(15) << temp6 << endl
                         << endl;

                    cout << "Are you sure you want to delete this data?\n";
                    cout << "To continue press any character or letter key other than c or C!"
                            "\nTo cancel press c or C!\n";
                    char c;
                    cin >> c;
                    if (c == 'c' || c == 'C')
                    {
                        // goto cancel;
                        file1 << stud.full_name << ',' << temp1 << ',' << temp2 << ',' << temp3 << ',' << temp4 << ',' << temp5 << ','
                              << temp6 << ',' << temp7 << ',' << temp8 << ',' << temp9 << ',' << temp10 << ',' << temp11 << endl;
                    } //
                    // cout<< "it success fully deleted...";
                    // deleted = true;
                }
                else
                {
                    // cancel:
                    file1 << stud.full_name << ',' << temp1 << ',' << temp2 << ',' << temp3 << ',' << temp4 << ',' << temp5 << ','
                          << temp6 << ',' << temp7 << ',' << temp8 << ',' << temp9 << ',' << temp10 << ',' << temp11 << endl;
                }
            }
            if (!check) // to check either the data is found or not
            {
                cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
                cout << "\n\aSorry, your request is unsuccessful!\n"; // \a bip sound
                cout << "\nId number " << Id << " is not found in the list!\n";
            }
        }

        file1.close();
        file.close();
        remove("student.txt");
        rename("tempdata.txt", "student.txt");
    }
}

void update(Student stud)
{
    fstream file, file1;

    file.open("student.txt", ios::in);
    bool check2 = false;
    string Id;

    if (!file)
    {
        cout << "File couldn't open...";
    }
    else
    {

        cout << "Enter the Id number you want to modify: ";
        cin >> Id;
        file1.open("tempdata.txt", ios::app | ios::out);
        string line, temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8, temp9, temp10, temp11;
        while (file.good())
        {
            // name,Id,age,sex,edulevel,basicSalary, category, dd, mm , yy, overtime , address, phonenum
            while (getline(file, line))
            {
                stringstream ss(line);
                getline(ss, stud.full_name, ',');
                getline(ss, temp1, ','); // id

                getline(ss, temp2, ','); // sex

                getline(ss, temp3, ','); // age

                getline(ss, temp4, ',');  // address
                getline(ss, temp5, ',');  // cgp
                getline(ss, temp6, ',');  // status
                getline(ss, temp7, ',');  // FII
                getline(ss, temp8, ',');  // DT
                getline(ss, temp9, ',');  // STAT
                getline(ss, temp10, ','); // DB
                getline(ss, temp11, ','); // DL

                if (temp1 == Id)
                {

                    cout << "Insert the detail of Student : \n";
                    cout << "Enter the name of the student: " << endl;
                    cin.ignore();
                    getline(cin, stud.full_name);

                idtry:
                    cout << "enter id : ";
                    cin >> stud.stud_Id;

                    // to check id if it is already registered.
                    //*********************************************************************************//
                    string line, name, idregistered;
                    fstream CheckFile;
                    CheckFile.open("student.txt", ios::in);
                    if (!CheckFile)
                    {
                        // cout<< "!Sorry the file could not be opened....";
                    }
                    else
                    {
                        while (getline(CheckFile, line))
                        {
                            stringstream ss(line);
                            getline(ss, name, ',');
                            getline(ss, idregistered, ',');

                            if (stud.stud_Id == idregistered && Id != idregistered)
                            { // Id != idregistered  to use this id again
                                cout << "This Id is already registerd please try to use unregistered Id!\n";
                                goto idtry;
                            }
                        }
                    }
                    //*********************************************************************************//

                    cout << "Enter age : ";
                    cin >> stud.age;
                sex:
                    cout << "Enter sex 'm' or 'f' : ";
                    cin >> stud.sex;
                    if (stud.sex != 'm' && stud.sex != 'f')
                    {
                        cout << "Invalid input \n";
                        goto sex;
                    }

                    cout << "address : ";
                    cin.ignore();
                    getline(cin, stud.address);

                    // result out of 100
                    // FII, DT, STAT, DB, DL;
                    cout << "Enter the result out of 100\n";
                    cout << "Fundamental of Programming II: ";
                    cin >> stud.mark.FII;
                    // grade
                    stud.grade[0] = grade_cul(stud.mark.FII);
                    cout << "Data Communication: ";
                    cin >> stud.mark.DT;
                    stud.grade[1] = grade_cul(stud.mark.DT);
                    cout << "Statistics: ";
                    cin >> stud.mark.STAT;
                    stud.grade[2] = grade_cul(stud.mark.STAT);
                    cout << "Database: ";
                    cin >> stud.mark.DB;
                    stud.grade[3] = grade_cul(stud.mark.DB);
                    cout << "Digital Logic: ";
                    cin >> stud.mark.DL;
                    stud.grade[4] = grade_cul(stud.mark.DL);
                    float sum = 0, credit;
                    // CGP
                    for (int j = 0; j < 5; j++)
                    {

                        // float credit;
                        if (j == 0)
                            credit = 3;
                        else if (j == 1)
                            credit = 4;
                        else if (j == 2)
                            credit = 3;
                        else if (j == 3)
                            credit = 4;
                        else
                            credit = 4; // for the 4th subject

                        // calculate CGP based on ones grade!
                        if (stud.grade[j] == "A+" || stud.grade[j] == "A")
                        {
                            sum += 4 * credit;
                        }
                        else if (stud.grade[j] == "B+")
                        {
                            sum += 3.5 * credit;
                        }
                        else if (stud.grade[j] == "B")
                        {
                            sum += 3 * credit;
                        }
                        else if (stud.grade[j] == "C")
                        {
                            sum += 2.5 * credit;
                        }
                        else if (stud.grade[j] == "D")
                        {
                            sum += 1 * credit;
                        }
                        else if (stud.grade[j] == "F")
                        {
                            sum += 0 * credit;
                        }
                        else
                        {
                            sum = -1;
                        }
                        //        }
                    }
                    if (sum == -1)
                        stud.cgp = 0; // here 0 means his grade information is incomplete
                    else
                        stud.cgp = sum / 18;
                    if (stud.cgp >= 3.5)
                    {
                        stud.status = "Passed with excellent result";
                    }
                    else if (stud.cgp >= 2.5)
                    {
                        stud.status = "Passed";
                    }
                    else if (stud.cgp >= 2.0)
                    {
                        stud.status = "Warning";
                    }
                    else
                    {
                        stud.status = "Failed";
                    }

                    check2 = true;

                    // from
                    file1 << stud.full_name << ',' << stud.stud_Id << ',' << stud.sex << ',' << stud.age << ','
                          << stud.address << ',' << stud.cgp << ',' << stud.status << ',' << stud.mark.FII << ','
                          << stud.mark.DT << ',' << stud.mark.STAT << ',' << stud.mark.DB << ',' << stud.mark.DL << ',' << endl;

                    // file1<<stud.full_name<< ','<<stud.stud_Id<<','<<stud.sex<<','<<stud.age<<','<<stud.address<<','<<temp5<<','
                    //<<temp6<<','<<temp7<<','<<temp8<<','<<temp9<<','<<temp10<<','<<temp11<<','<<endl;
                }
                else
                {
                    file1 << stud.full_name << ',' << temp1 << ',' << temp2 << ',' << temp3 << ',' << temp4 << ',' << temp5 << ','
                          << temp6 << ',' << temp7 << ',' << temp8 << ',' << temp9 << ',' << temp10 << ',' << temp11 << ',' << endl;
                }
            }
            if (!check2) // to check either the data is found or not
            {
                cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
                cout << "\n\aSorry, your request is unsuccessful!\n";
                cout << "\nId number " << Id << " is not found in the list!\n";
            }
            file1.close();
            file.close();
            remove("student.txt");
            rename("tempdata.txt", "student.txt");
        }
    }
}

void Search(Student stud)
{
    fstream file;
    file.open("student.txt", ios::in);
    string Id, Name;
    bool found = false;

    if (!file)
    {
        cout << "File couldn't open...";
        return;
    }

    // Let the user choose the search criterion
    int searchOption;
    cout << "Search by:\n1. ID\n2. Name\nEnter your choice (1 or 2): ";
    cin >> searchOption;

    if (searchOption == 1)
    {
        cout << "Enter the ID number to search: ";
        cin >> Id;
    }
    else if (searchOption == 2)
    {
        cout << "Enter the Name to search: ";
        cin.ignore(); // To handle any leftover newline characters
        getline(cin, Name);
    }
    else
    {
        cout << "Invalid choice!";
        return;
    }

    // Display header
    cout << left << setw(32) << "NAME" << left << setw(15) << "ID" << left << setw(15) << "SEX"
         << left << setw(15) << "AGE" << left << setw(15) << "ADDRESS" << left << setw(15) << "GRADE"
         << left << setw(15) << "STATUS(pass/fail)\n"
         << "***************************************************************************"
            "**************************************************"
         << endl
         << endl;

    // Read file line by line
    string line, temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8, temp9, temp10, temp11;
    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, stud.full_name, ','); // Name
        getline(ss, temp1, ',');          // ID
        getline(ss, temp2, ',');          // Sex
        getline(ss, temp3, ',');          // Age
        getline(ss, temp4, ',');          // Address
        getline(ss, temp5, ',');          // CGP
        getline(ss, temp6, ',');          // Status
        getline(ss, temp7, ',');          // FII
        getline(ss, temp8, ',');          // DT
        getline(ss, temp9, ',');          // STAT
        getline(ss, temp10, ',');         // DB
        getline(ss, temp11, ',');         // DL

        // Search logic based on the chosen criterion
        if ((searchOption == 1 && temp1 == Id) || (searchOption == 2 && stud.full_name == Name))
        {
            cout << left << setw(32) << stud.full_name << left << setw(15) << temp1 << left << setw(15) << temp2
                 << left << setw(15) << temp3 << left << setw(15) << temp4 << left << setw(15) << temp5
                 << left << setw(15) << temp6 << endl
                 << endl;

            // Display further info
            cout << "\nResult of each subject out of 100\n"
                    "####################################"
                 << endl
                 << endl;
            cout << left << setw(32) << "Fundamental of Programming" << left << setw(20) << "Data Communication"
                 << left << setw(20) << "Statistics" << left << setw(20) << "Database" << left << setw(20) << "Digital Logic"
                 << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
                    "~~~~~~~~~~~~~~~~~~~"
                 << endl
                 << endl;
            cout << left << setw(32) << temp7 << left << setw(20) << temp8 << left << setw(20) << temp9
                 << left << setw(20) << temp10 << left << setw(20) << temp11 << endl
                 << endl;

            found = true;
            break; // Exit loop after finding a match
        }
    }

    // If no match was found
    if (!found)
    {
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
        cout << "\n\aSorry, your request is unsuccessful!\n";
        if (searchOption == 1)
            cout << "\nID number " << Id << " is not found in the list!\n";
        else
            cout << "\nName \"" << Name << "\" is not found in the list!\n";
    }

    file.close();
}



// grade culculator
string grade_cul(float mark)
{
    string gr;
    if (mark >= 90 && mark <= 100)
    {
        gr = "A+";
    }
    else if (mark >= 80 && mark < 90)
    {
        gr = "A";
    }
    else if (mark >= 70 && mark < 80)
    {
        gr = "B+";
    }
    else if (mark >= 60 && mark < 70)
    {
        gr = "B";
    }
    else if (mark >= 50 && mark < 60)
    {
        gr = "C";
    }
    else if (mark >= 40 && mark < 50)
    {
        gr = "D";
    }
    else if (mark > 0 && mark < 40)
    {
        gr = "F";
    }
    else
    {
        gr = "non_graded";
    }
    return gr;
}

Student runk(Student stud[])
{
    ifstream sortfile("student.txt");
    int i = 0, count = 0;
    ofstream infile("tempdata.txt");
    string line, temp1, temp2, temp3, temp4, temp5, temp7, temp8, temp9, temp10, temp11;
    while (sortfile.good())
    {
        while (getline(sortfile, line))
        {
            stringstream ss(line);
            getline(ss, stud[i].full_name, ',');
            getline(ss, stud[i].stud_Id, ','); // id
            // stud[i].stud_Id = atoi(temp1.c_str()); // casting variable
            getline(ss, temp2, ','); // sex
            stud[i].sex = temp2[0];
            getline(ss, temp3, ','); // age
            stud[i].age = atoi(temp3.c_str());
            getline(ss, stud[i].address, ','); // address
            // stud[i].address =  atoi(temp4.c_str());
            getline(ss, temp5, ','); // grade
            stud[i].cgp = atof(temp5.c_str());
            // 2getline(ss, stud[i].status, ','); // id
            getline(ss, stud[i].status, ','); // status
            getline(ss, temp7, ',');          // FII
            getline(ss, temp8, ',');          // DT
            getline(ss, temp9, ',');          // STAT
            getline(ss, temp10, ',');         // DB
            getline(ss, temp11, ',');         // DL

            i++;
            count++;
        }
    }
    for (int i = 0; i < count; i++)
    {
        for (int j = count - 1; j >= i; j--)
        {
            if (stud[i].cgp < stud[j].cgp)
            {
                temp = stud[i];
                stud[i] = stud[j];
                stud[j] = temp;
            }
        }
    }

    for (int i = 0; i < count; i++)
    {
        // infile<<stud[i].full_name<< ','<<stud[i].stud_Id<<','<<stud[i].sex<<','<<stud[i].age<<','
        //<<stud[i].address<<','<<stud[i].cgp<<endl;
        infile << stud[i].full_name << ',' << stud[i].stud_Id << ',' << stud[i].sex << ',' << stud[i].age << ','
               << stud[i].address << ',' << stud[i].cgp << ',' << stud[i].status << ',' << temp7 << ','
               << temp8 << ',' << temp9 << ',' << temp10 << ',' << temp11 << ','
               << endl;
    }
    infile.close();
    sortfile.close();
    remove("student.txt");
    rename("tempdata.txt", "student.txt");

    return *stud;
}

void statstics(Student *stud)
{
    // statistics
    //  detail data about the data(statstics) will display here
    int noFemale = 0, noMale = 0, total_student = 0, nopass = 0, nopass_with_warning = 0,
        nofail = 0;
    float total_average_cgp = 0, sum = 0, percent_passed;
    string percent, percentage;

    // to concatenate float with string

    ifstream statfile("student.txt");
    int i = 0, count = 0;
    string line, temp1, temp2, temp3, temp4, temp5;
    while (statfile.good())
    {
        while (getline(statfile, line))
        {
            stringstream ss(line);
            getline(ss, stud[i].full_name, ',');
            getline(ss, stud[i].stud_Id, ','); // id
            // stud[i].stud_Id = atoi(temp1.c_str()); // casting variable
            getline(ss, temp2, ','); // sex
            stud[i].sex = temp2[0];  // remove temp2[0]
            getline(ss, temp3, ','); // age
            stud[i].age = atoi(temp3.c_str());
            getline(ss, stud[i].address, ','); // address
            // stud[i].address =  atoi(temp4.c_str());
            getline(ss, temp5, ','); // grade
            stud[i].cgp = atof(temp5.c_str());
            getline(ss, stud[i].status, ','); // status

            i++;
            count++;
        }
        // Total student
        total_student = count;

        // number of Male and Female
        for (int i = 0; i < count; i++)
        {
            if (stud[i].sex == 'f' || stud[i].sex == 'F')
            {
                noFemale += 1;
            }
            else if (stud[i].sex == 'm' || stud[i].sex == 'M')
            {
                noMale += 1;
            }
        }

        // Number of pass and fail
        for (int i = 0; i < count; i++)
        {
            if (stud[i].status == "Passed" | stud[i].status == "Passed with excellent result")
            {
                nopass += 1;
            }
            else if (stud[i].status == "Warning")
            {
                nopass_with_warning += 1;
            }
            else if (stud[i].status == "Failed")
            {
                nofail += 1;
            }
        }

        // total average cgp of the department
        for (int i = 0; i < count; i++)
        {
            sum += stud[i].cgp;
        }
        total_average_cgp = sum / total_student;

        // passed students in percent
        percent_passed = (((nopass + nopass_with_warning) * 100)) / total_student;
//        percent = std::to_string(percent_passed) + "%"; // cast float to string then concatenate with % symbol
//        percentage = "";
        for (int i = 0; i < 5; i++)
        {
            percentage += percent[i];
        }
//        percentage += "%";
    }
    // Displayed informations or statistics
    cout << left << setw(30) << "STUDENTS STATISTICS INFO" << left << setw(30) << "QUANTITY\n"
                                                                                  "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
         << endl
         << endl;
    cout << left << setw(30) << "Total students" << left << setw(30) << total_student << endl
         << endl;
    cout << left << setw(30) << "Total Female" << left << setw(30) << noFemale << endl
         << endl;
    cout << left << setw(30) << "Total Male" << left << setw(30) << noMale << endl
         << endl;
    cout << left << setw(30) << "passed without warning" << left << setw(30) << nopass << endl
         << endl;
    cout << left << setw(30) << "passed students with warning" << left << setw(30) << nopass_with_warning << endl
         << endl;
    cout << left << setw(30) << "Failed students" << left << setw(30) << nofail << endl
         << endl;
    cout << left << setw(30) << "Average CGP of students" << left << setw(30) << total_average_cgp << endl
         << endl;
    // cout<<left<<setw(30)<< "Passed students out of 100"<<left<<setw(30)<< percent<<endl<<endl;
    cout << left << setw(30) << "Passed students out of 100" << left << setw(30) << percentage << endl
         << endl;

    statfile.close();
}

void login()
{
    int a = 0, i = 0;
    char uname[10], c = ' ';
    char pword[10], code[10];
    char user[10] = "user";
    char pass[10] = "1234";
    do
    {
        cout << "\n                \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\x20"
			 << " LOGIN FIRST  \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\x20  \n";
		cout << "\n\n                                 ENTER USERNAME:=";
		cin.getline(uname, 10);
		cout << "\n\n                                 ENTER PASSWORD:=";

        while (i < 10)
        {
            pword[i] = getch();
            c = pword[i];
            // in the bellow code 13 means : when you press enter key on the keyboard the ASCII value for this is 13.
            //  ASCII value of 13 == carriage return
            if (c == 13)
                break; // A carriage return is the term for the result of hitting
                       // the "enter" or "return" key on a keyboard when creating text.
            else
                cout << "*";
            ;
            i++;
        }
        pword[i] = '\0';
        // char code=pword;
        i = 0;
        // scanf("%s",&pword);
        if (strcmp(uname, "user") == 0 && strcmp(pword, "1234") == 0)
        {
            cout << "  \n\n\n                      WELCOME TO STUDENT MANAGEMENT SYSTEM !!!! LOGIN IS SUCCESSFUL";
            cout << "\n\n\n\t\t\t\t         Press any key to continue...";
            getch(); // holds the screen
            break;
        }
        else
        {
            cout << "\n\a                      SORRY !!!!  LOGIN IS UNSUCESSFUL"; // \a here create a pop sound to notice your error!
            a++;

            getch(); // holds the screen
        }
    } while (a <= 2);
    if (a > 2)
    {
        cout << "\n\a           Sorry you have entered the wrong username or password for four times!!!\n"
                "Try again later!";

        getch();
        // system("cls");
        // goto shut;
        shut = true;
        system("exit");
    }

    // getch() is a predefined function in "conio.h" (console input output header file)
    // will tell to the console wait for some time until a key is hit given after running of program.
}

// Ststus here?
//  recomendation using cgp
void aboutUs()
{
    //
    cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
    cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
    cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^  Wellcome To About Us Page  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
    cout << "****                                                                                ****\n";
    cout << "****  We are Students at Addis Ababa Science and Technology University!             ****\n";
    cout << "****  Department: Software engineering.                                             ****\n";
    cout << "****  Year: 2nd Year.                                                               ****\n";
    cout << "****  Team size: 5                                                                  ****\n";
    cout << "****                                                                                ****\n";
    cout << "****  Members                                                                       ****\n";
    cout << "****  No_    Name                                          Id                       ****\n";
    cout << "****  1.    Agumas Desalew                                 ETS1559/13               ****\n";
    cout << "****  2.    Rahel Abera                                    ETS1081/13               ****\n";
    cout << "****  3.    Samrawit Eshetu                                ETS0076/13               ****\n";
    cout << "****  4.    Simret Belete                                  ETS0076/13               ****\n";
    cout << "****  5.    Tamirat Areda                                  ETS0076/13               ****\n";
    cout << "****                                                                                ****\n";
    cout << "****  \"Alone we can do so little; together we can do so much.\" : Our Motive         ****\n";
    cout << "****  \"Knowledge is your operating system.\"                                         ****\n";
    cout << "****                                                                                ****\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n";
}
void contactUs()
{
    //
    cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
    cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
    cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^  Wellcome To Contact Us Page  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
    cout << "****                                                                                ****\n";
    cout << "****  We are Students at Addis Ababa Science and Technology University (AASTU)!     ****\n";
    cout << "****  2nd Year Software engineering.                                                ****\n";
    cout << "****  Be free to share your feeling here!                                           ****\n";
    cout << "****  Comments, Recommendations, To work together or other ideas all are acceptable!****\n";
    cout << "****                                                                                ****\n";
    cout << "****  Location: AASTU , Addis Ababa, Ethiopia                                       ****\n";
    cout << "****  Email: team5@gmail.com                                                        ****\n";
    cout << "****  Telegram username: @team.tm                                                   ****\n";
    cout << "****  Phone Number: 0921278377 or 0900102231                                        ****\n";
    cout << "****                                                                                ****\n";
    cout << "****  \"Alone we can do so little; together we can do so much.\" : Our Motive         ****\n";
    cout << "****  \"Knowledge is your operating system.\"                                         ****\n";
    cout << "****                                                                                ****\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n";
}