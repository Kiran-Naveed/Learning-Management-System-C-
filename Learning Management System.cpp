#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

void initializeCourses(string codeList[], string nameList[], int crtHrsList[], int semList[], int size);
void initializeUsers(string usernames[], string passwords[], int size);
void initializeStudents(string studentName[], string regNo[], string stdCourseList[], int size);

//function for data persistent
bool saveCourse(string codeList[], string nameList[], int crtHrsList[], int semList[], int size);
bool saveStudent(string stdRegNoList[], string stdNameList[], string stdCourseList[], int size);
bool loadCourses(string codeList[], string nameList[], int crtHrsList[], int semList[], int size);
bool loadUser(string usersList[], string passwordList[], int size);
bool loadStudents(string stdRegNoList[], string stdNameList[], string stdCourseList[], int size);

//COURSE MANAGEMENT
int searchCourseCode(string codeList[], int size, string courseCode);
bool addCourses(string codeList[], string nameList[], int creditHours[], int semList[], int size, string courseCode, string courseName, int credit, int semester);
void viewCourses(string codeList[], string nameList[], int creditHours[], int semList[], int size);
void viewSemesterCourse(string codeList[], string nameList[], int creditHours[], int semList[], int size, int semester);
bool updateCourse(string codeList[], string nameList[], int creditHours[], int semList[], int size, string courseCode, string courseName, int credit, int semester);
bool deleteCourse(string codeList[], string nameList[], int creditHours[], int semList[], int size, string courseCode);
bool stdSearchCourseCode(string stdCourseList[], string courseCode);

//VALIDATION FUNCTIONS
bool isValidCourseCode(string code);
bool isValidCreditHours(int creditHours);
bool isValidSemester(int semester);
bool isValidCourseName(string name);
bool validateAllData(string courseCode, string courseName, int credit, int semester);
bool isValidRegistrationNumber(string regNumber);
bool isValidStudentName(string stdName);

//USER MANAGEMENT
bool userExist(string user[], string pass[], string users, string passs, int size);
void login(string &userName, string &password);

//Student Management
bool addStudent(string stdNamesList[], string stdRegNoList[], int MAX_STUDENTS, string studentName, string regNnumber);
bool updateStudent(string stdNamesList[], string stdRegNoList[], int size, string stdRegNoToUpdate, string studentName, string regNnumber);
bool deleteStudent(string stdNamesList[], string stdRegNoList[], string stdCourseList[], int size, string regNnumber);
bool registerCourse(string stdRegNoList[], string stdCourseList[], string courseCodeList[], int sizestd, int sizeCourse, string regNo, string courseCode);
bool unRegisterCourse(string stdRegNoList[], string stdCourseList[], int size, string regNo, string courseCode);
int searchStudent(string stdRegNo[], int size, string registration);
void viewAllStudents(string stdNamesList[], string stdRegNoList[], string stdCourseList[], int size);

int main()
{

    //Maximum Size of All arrays
    int MAX_COURSES = 10;
    int MAX_USERS = 10;
    int MAX_STUDENTS = 10;
    bool flag = false;
    string userName;
    string password;
    string courseCode;
    string courseName;
    string studentName;
    string regNnumber;
    string updateRegNumber;
    int credit;
    int semester;
    int input;
    //Declare All Arrays
    string usersList[MAX_USERS], passwordList[MAX_USERS];
    string codeList[MAX_COURSES], nameList[MAX_COURSES];
    string stdNamesList[MAX_STUDENTS], stdRegNoList[MAX_STUDENTS], stdCourseList[MAX_STUDENTS];
    int creditHours[MAX_COURSES], semList[MAX_COURSES];

    //Initialize all arrays
    initializeCourses(codeList, nameList, creditHours, semList, MAX_COURSES);
    initializeUsers(usersList, passwordList, MAX_USERS);
    initializeStudents(stdNamesList, stdRegNoList, stdCourseList, MAX_STUDENTS);

    //This function will load the courses in arrays
    loadCourses(codeList, nameList, creditHours, semList, MAX_COURSES);

    //This function will load the users in array
    loadUser(usersList, passwordList, MAX_USERS);
    //This function will load users in arrays
    loadStudents(stdRegNoList, stdNamesList, stdCourseList, MAX_STUDENTS);

    //For starting code
    login(userName, password);

    do
    {

        while (userExist(usersList, passwordList, userName, password, MAX_USERS) != true || (userName == "" && password == ""))
        {
            cout << "Incorrect info please reenter username and password" << endl;
            cout << "Enter User name: ";
            cin >> userName;
            cout << "Enter Password: ";
            cin >> password;
            cout << endl;
        }

        if (userExist(usersList, passwordList, userName, password, MAX_USERS))
        {

            cout << "Choose the following option" << endl;
            cout << "1   Add Courses" << endl;
            cout << "2   Update Courses" << endl;
            cout << "3   Delete Courses" << endl;
            cout << "4   View All Courses" << endl;
            cout << "5   View Courses of a Semester" << endl;
            cout << "6   Add New Student" << endl;
            cout << "7   Update Student" << endl;
            cout << "8   Delete Student" << endl;
            cout << "9   View All Student" << endl;
            cout << "10  Register the course for student" << endl;
            cout << "11  UnRegister course for student" << endl;
            cout << "12  Logout of the system" << endl;
            cout << "13  Exit Program" << endl;
            cout << "Enter the option: ";
            cin >> input;
            switch (input)
            {
            // This case for adding the course details
            case 1:

                cout << "Enter the details of the course: ";
                cin >> courseCode;
                cin >> credit;
                cin >> semester;
                cin.ignore();
                getline(cin, courseName);

                //Check validity of all inputs
                if (validateAllData(courseCode, courseName, credit, semester))
                {
                    //Call addCourse function
                    if (addCourses(codeList, nameList, creditHours, semList, MAX_COURSES, courseCode, courseName, credit, semester))
                    {
                        cout << "Course Successfully added" << endl;
                    }
                    else
                    {
                        cout << "Sorry No space to add new course" << endl;
                    }
                }
                else
                {
                    //If any validity is false it will not add the course
                    cout << "Invalid details" << endl;
                }

                break;

            // This case for Updating the course details
            case 2:

                cout << "Enter the course code" << endl;
                cin >> courseCode;

                //check validity of courseCode
                if (!isValidCourseCode(courseCode))
                {

                    //Find the index of courseCode which user entered to update the course details

                    cout << "Enter the details of the course: ";
                    cin >> courseCode;
                    cin >> credit;
                    cin >> semester;
                    cin.ignore();
                    getline(cin, courseName);
                    //Check validity of all details entered by user
                    if (validateAllData(courseCode, courseName, credit, semester))
                    {

                        if (updateCourse(codeList, nameList, creditHours, semList, MAX_COURSES, courseCode, courseName, credit, semester))
                        {
                            cout << "Course successfully updated" << endl;
                        }
                        else
                        {
                            cout << "No course found" << endl;
                        }
                    }
                    else
                    {
                        cout << "Invalid data" << endl;
                    }
                }
                else
                {
                    //here we will show message of not valid data
                    cout << "Invalid Data" << endl;
                }

                break;

                //This case for deleting the course details

            case 3:
                cout << "Enter Course code" << endl;
                cin >> courseCode;
                //Validate the course Code
                if (!isValidCourseCode(courseCode))
                {
                    //call function to delete the course detail which has same course code as user enter
                    if (deleteCourse(codeList, nameList, creditHours, semList, MAX_COURSES, courseCode))
                    {
                        cout << "Course Successfully deleted" << endl;
                    }
                    else
                    {
                        cout << "Sorry No Course found " << endl;
                    }
                }
                else
                {
                    //if course code is invalid then this message will show
                    cout << "Invalid Course code" << endl;
                }

                break;

                //This case for displaying all details of all courses

            case 4:
                //View All details of All courses
                viewCourses(codeList, nameList, creditHours, semList, MAX_COURSES);
                break;

            //This case for displaying course details of specific semester
            case 5:
                cout << "Enter the semester:";
                cin >> semester;
                //Check valildidty of semester entered by user
                if (isValidSemester(semester))
                {
                    //Show All details of course of the semester entered by user
                    viewSemesterCourse(codeList, nameList, creditHours, semList, MAX_COURSES, semester);
                }
                else
                {
                    //If our semester is invalid
                    cout << "Invalid data" << endl;
                }

                break;
            // For adding a new student
            case 6:
                cout << "Add new student" << endl;
                cout << "Enter details of Student: ";
                cin >> regNnumber;
                cin.ignore();
                getline(cin, studentName);
                if (isValidRegistrationNumber(regNnumber) && isValidStudentName(studentName))
                {
                    if (addStudent(stdNamesList, stdRegNoList, MAX_STUDENTS, studentName, regNnumber))
                    {
                        cout << "Student Added Successfully" << endl;
                    }
                    else
                    {
                        cout << "No space available" << endl;
                    }
                }
                else
                {
                    cout << "Invalid details" << endl;
                }
                break;
            case 7:
                //For update a  student..
                cout << "Enter Registration Number to Edit: ";
                cin >> updateRegNumber;
                if (isValidRegistrationNumber(updateRegNumber))
                {
                    cout << "Enter details of students: ";
                    cin >> regNnumber;
                    cin.ignore();
                    getline(cin, studentName);
                    if (isValidRegistrationNumber(regNnumber) && isValidStudentName(studentName))
                    {

                        if (updateStudent(stdNamesList, stdRegNoList, MAX_STUDENTS, updateRegNumber, studentName, regNnumber))
                        {
                            cout << "Student details Updated Successfully" << endl;
                        }
                        else
                        {
                            cout << "Student Not Found" << endl;
                        }
                    }
                    else
                    {
                        cout << "Invalid Data" << endl;
                    }
                }
                else
                {
                    cout << "Invalid Registration number" << endl;
                }

                break;
                //For register a student..
            case 8:

                cout << "Enter the registration number to delete students: ";
                cin >> regNnumber;
                if (isValidRegistrationNumber(regNnumber))
                {
                    if (deleteStudent(stdNamesList, stdRegNoList, stdCourseList, MAX_STUDENTS, regNnumber))
                    {
                        cout << "Student delete successfully" << endl;
                    }
                    else
                    {
                        cout << "No student found of this registration number" << endl;
                    }
                }
                else
                {
                    cout << "Invalid Registration Number" << endl;
                }
                break;

                //View All students....
            case 9:
                viewAllStudents(stdNamesList, stdRegNoList, stdCourseList, MAX_STUDENTS);
                break;

                //For register the students...
            case 10:
                cout << "Enter Registration number of student for course Regstration: ";
                cin >> regNnumber;
                cout << "Enter course code to register: ";
                cin >> courseCode;
                if (isValidCourseCode(courseCode) && isValidRegistrationNumber(regNnumber))
                {
                    if (registerCourse(stdRegNoList, stdCourseList, codeList, MAX_STUDENTS, MAX_COURSES, regNnumber, courseCode))
                    {
                        cout << "Course Register Seccessfully" << endl;
                    }
                    else
                    {
                        cout << "Some data not found" << endl;
                    }
                }
                else
                {
                    cout << "Invalid Data" << endl;
                }

                break;

                //For unregister the students
            case 11:
                cout << "Enter Registration number of student for course UN_Regstration: ";
                cin >> regNnumber;
                cout << "Enter course code to UN_Register: ";
                cin >> courseCode;
                if (isValidCourseCode(courseCode) && isValidRegistrationNumber(regNnumber))
                {
                    if (unRegisterCourse(stdRegNoList, stdCourseList, MAX_STUDENTS, regNnumber, courseCode))
                    {
                        cout << "Course Un Register Seccessfully" << endl;
                    }
                    else
                    {
                        cout << "Some data not found" << endl;
                    }
                }
                else
                {
                    cout << "Invalid Data" << endl;
                }
                break;

                //Save All data After the user logout...
            case 12:

                if (saveCourse(codeList, nameList, creditHours, semList, MAX_COURSES) && saveStudent(stdRegNoList, stdNamesList, stdCourseList, MAX_STUDENTS))
                {
                    cout << "All courses ans students Data Saved successfully" << endl;
                }
                else
                {
                    cout << "All data you entered is lost due to some error" << endl;
                }
                userName = "";
                password = "";
                login(userName, password);
                break;

                //Save Al data After the program exit....
            case 13:
                if (saveCourse(codeList, nameList, creditHours, semList, MAX_COURSES) && saveStudent(stdRegNoList, stdNamesList, stdCourseList, MAX_STUDENTS))
                {
                    cout << "All courses and students Data Saved successfully" << endl;
                }
                else
                {
                    cout << "All data you entered is lost due to some error" << endl;
                }
                cout << "Program closed ";
                break;
            default:
                cout << "Invalid choice";
            }
        }
    } while (input != 13);

    return 0;
}

void initializeCourses(string codeList[], string nameList[], int crtHrsList[], int semList[], int size)
{
    for (int s = 0; s < size; s++)
    {
        codeList[s] = " ";
        nameList[s] = " ";
        crtHrsList[s] = 0;
        semList[s] = 0;
    }
}

void initializeUsers(string usernames[], string passwords[], int size)
{
    for (int s = 0; s < size; s++)
    {
        usernames[s] = " ";
        passwords[s] = " ";
    }
}

void initializeStudents(string studentName[], string regNo[], string stdCourseList[], int size)
{
    for (int i = 0; i < size; i++)
    {
        studentName[i] = " ";
        regNo[i] = " ";
        stdCourseList[i] = "";
    }
}

bool saveCourse(string codeList[], string nameList[], int crtHrsList[], int semList[], int size)
{
    // This variable for read data from file
    ofstream myfile;
    /*Open the file if exist if not exist then make new file of this name ios::app maens that the new data will append in file and 
	not remove previous content of file */
    myfile.open("Courses.txt");
    //This function will check if the file open then write data from file
    if (myfile.is_open())
    {
        for (int i = 0; i < size; i++)
        {
            if (codeList[i] != "" && nameList[i] != "" && crtHrsList[i] != 0 && semList[i] != 0)
            {
                //These lines will write all array data to the file and make a comma separated file
                myfile << codeList[i] << ",";
                myfile << nameList[i] << ",";
                myfile << crtHrsList[i] << ",";
                myfile << semList[i] << endl;
            }
        }

        myfile.close();
        return true;
    }
    else
    {
        //If there is error while opening file this function will return false
        return false;
    }
}

bool saveStudent(string stdRegNoList[], string stdNameList[], string stdCourseList[], int size)
{
    ofstream myfile;

    myfile.open("Students.txt");
    //This function will check if the file open then write data from file
    if (myfile.is_open())
    {
        for (int i = 0; i < size; i++)
        {
            if (stdRegNoList[i] != " " && stdNameList[i] != " ")
            {
                //These lines will write all array data to the file and make a comma separated file
                myfile << stdRegNoList[i] << ",";
                myfile << stdNameList[i] << ",";
                myfile << stdCourseList[i] << endl;
            }
        }

        myfile.close();
        return true;
    }
    else
    {
        //If there is error while opening file this function will return false
        return false;
    }
}

bool loadStudents(string stdRegNoList[], string stdNameList[], string stdCourseList[], int size)
{
    int i = 0;
    ifstream getStudent("Students.txt");
    if (!getStudent.is_open())
    {
        cout << "File failed to open" << endl;
        return false;
    }
    else
    {
        string studentName, registrationNumber;
        string registerCourses;
        string line;
        while (!getStudent.eof() && i < size)
        {
            getline(getStudent, line);
            if (line == "")
                continue;
            stringstream ss(line);
            getline(ss, registrationNumber, ',');
            stdRegNoList[i] = registrationNumber;

            getline(ss, studentName, ',');
            stdNameList[i] = studentName;

            getline(ss, registerCourses, ',');
            stdCourseList[i] = registerCourses;
            i++;
        }

        getStudent.close();
        return true;
    }
}
//Function to load course in arrays
bool loadCourses(string codeList[], string nameList[], int crtHrsList[], int semList[], int size)
{
    int i = 0;
    ifstream getCourse("Courses.txt");
    if (!getCourse.is_open())
    {
        cout << "File failed to open" << endl;
        return false;
    }
    else
    {
        string courseCode, courseName;
        string creditHours, semester;
        int credit, sem;
        string line;
        while (!getCourse.eof() && i < size)
        {
            getline(getCourse, line);
            if (line == "")
                continue;
            stringstream ss(line);
            getline(ss, courseCode, ',');
            codeList[i] = courseCode;
            getline(ss, courseName, ',');
            nameList[i] = courseName;
            getline(ss, creditHours, ',');
            credit = stoi(creditHours);
            crtHrsList[i] = credit;
            getline(ss, semester, ',');
            sem = stoi(semester);
            semList[i] = sem;
            i++;
        }

        getCourse.close();
        return true;
    }
}

//Fuunction to read users from file and load then onto the arrays
bool loadUser(string usersList[], string passwordList[], int size)
{
    int i = 0;
    ifstream getUsers("Users.txt");
    if (!getUsers.is_open())
    {
        cout << "File failed to open" << endl;
        return false;
    }
    else
    {
        string username, password;
        string line;
        while (!getUsers.eof() && i < size)
        {
            getline(getUsers, line);
            stringstream ss(line);
            getline(ss, username, ',');
            usersList[i] = username;
            getline(ss, password, ',');
            passwordList[i] = password;
            i++;
        }

        getUsers.close();
        return true;
    }
}

int searchCourseCode(string codeList[], int size, string courseCode)
{
    int index = -1;
    for (int i = 0; i < size; i++)
    {
        if (codeList[i] == courseCode)
        {
            index = i;
            break;
        }
    }
    return index;
}

//This Function Will add the function
bool addCourses(string codeList[], string nameList[], int creditHours[], int semList[], int size, string courseCode, string courseName, int credit, int semester)
{
    bool flag = false;
    int i = searchCourseCode(codeList, size, " ");
    if (i != -1)
    {

        codeList[i] = courseCode;
        nameList[i] = courseName;
        creditHours[i] = credit;
        semList[i] = semester;
        flag = true;
    }
    return flag;
}

// This Function will display all course details
void viewCourses(string codeList[], string nameList[], int creditHours[], int semList[], int size)
{

    for (int u = 0; u < 80; u++)
        cout << "-";
    cout << endl;
    cout << left;
    cout << setw(10) << "Course"
         << setw(50) << "Course"
         << setw(10) << "Credit"
         << setw(10) << "Semester" << endl;
    cout << setw(10) << "Code"
         << setw(50) << "Name"
         << setw(10) << "Hours"
         << setw(10) << "" << endl;
    for (int u = 0; u < 80; u++)
        cout << "-";
    cout << endl;
    for (int i = 0; i < size; i++)
    {
        if (codeList[i] != " ")
        {

            cout << setw(10) << codeList[i]
                 << setw(50) << nameList[i]
                 << setw(10) << creditHours[i]
                 << setw(10) << semList[i] << endl;
        }
    }
    cout << endl;
    for (int u = 0; u < 80; u++)
        cout << "-";
    cout << endl;
}

//This function will display the course details of the specific semester
void viewSemesterCourse(string codeList[], string nameList[], int creditHours[], int semList[], int size, int semester)
{

    for (int u = 0; u < 80; u++)
        cout << "-";
    cout << endl;
    cout << left;
    cout << setw(10) << "Course"
         << setw(50) << "Course"
         << setw(10) << "Credit"
         << setw(10) << "Semester" << endl;
    cout << setw(10) << "Code"
         << setw(50) << "Name"
         << setw(10) << "Hours"
         << setw(10) << "" << endl;
    for (int u = 0; u < 80; u++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < size; i++)
    {
        if (semList[i] == semester && codeList[i] != "")
        {
            cout << setw(10) << codeList[i]
                 << setw(50) << nameList[i]
                 << setw(10) << creditHours[i]
                 << setw(10) << semList[i] << endl;
        }
    }
    cout << endl;
    for (int u = 0; u < 80; u++)
        cout << "-";
    cout << endl;
}

// This function will update the course 
bool updateCourse(string codeList[], string nameList[], int creditHours[], int semList[], int size, string courseCode, string courseName, int credit, int semester)
{
    bool flag = false;
    int updateIndex = searchCourseCode(codeList, size, courseCode);
    if (updateIndex != -1)
    {
        codeList[updateIndex] = courseCode;
        nameList[updateIndex] = courseName;
        creditHours[updateIndex] = credit;
        semList[updateIndex] = semester;
        flag = true;
    }
    return flag;
}

// This function will delete the course by using courseCode
bool deleteCourse(string codeList[], string nameList[], int creditHours[], int semList[], int size, string courseCode)
{
    bool flag = false;
    int i = searchCourseCode(codeList, size, courseCode);
    if (i != -1)
    {
        codeList[i] = " ";
        nameList[i] = " ";
        creditHours[i] = 0;
        semList[i] = 0;
        flag = true;
    }

    return flag;
}
//checking validity of coursecode
bool isValidCourseCode(string code)
{
    int x = code.length();
    bool flag = true;
    if (x == 5)
    {

        for (int i = 0; i < 2; i++)
        {
            if (!((code[i] >= 'a' && code[i] <= 'z') || (code[i] >= 'A' && code[i] <= 'Z')))
            {
                flag = false;
                break;
            }
        }

        for (int i = 2; i < 5 && flag; i++)
        {
            if (!(code[i] >= '0' && code[i] <= '9'))
            {
                flag = false;
                break;
            }
        }
    }

    return flag;
}

// checking the credit hours
bool isValidCreditHours(int creditHours)
{
    bool flag = true;
    if (!(creditHours >= 1 && creditHours <= 3))
    {
        flag = false;
    }

    return flag;
}

//checking semester
bool isValidSemester(int semester)
{
    bool flag = true;
    if (!(semester >= 1 && semester <= 9))
    {
        flag = false;
    }
    return flag;
}

//checking coursename
bool isValidCourseName(string name)
{
    bool flag = true;
    if (name.length() <= 50)
    {
        for (int i = 0; i < name.length(); i++)
        {
            if (!((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z') || (name[i] == ' ')))
                flag = false;
        }
    }
    else
        flag = false;

    return flag;
}

bool validateAllData(string courseCode, string courseName, int credit, int semester)
{
    cout << isValidCourseCode(courseCode) << endl;
    cout << isValidCourseName(courseName) << endl;
    cout << isValidCreditHours(credit) << endl;
    cout << isValidSemester(semester) << endl;
    if (!(isValidCourseCode(courseCode) && isValidCreditHours(credit) && isValidSemester(semester) && isValidCourseName(courseName)))
    {
        return false;
    }
    return true;
}

bool userExist(string user[], string pass[], string users, string passs, int size)
{
    bool flag = false;
    int i;
    for (i = 0; i < size; i++)
    {
        if (user[i] == users && pass[i] == passs)
        {
            flag = true;
            break;
        }
    }

    return flag;
}

void login(string &userName, string &password)
{

    system("cls");
    cout << endl;
    cout << "** Welcome To University Learning Management System ** " << endl;
    cout << "Dear users current software is intended for authorized users only." << endl;
    cout << "Login to the system to get access" << endl;
    cout << "Enter User name: ";
    cin >> userName;
    cout << "Enter Password: ";
    cin >> password;
    cout << endl;
}

//This function will show all stuents details...
void viewAllStudents(string stdNamesList[], string stdRegNoList[], string stdCourseList[], int size)
{
    for (int u = 0; u < 80; u++)
        cout << "-";
    cout << endl;
    cout << left;
    cout << setw(10) << "Student"
         << setw(50) << "Registration"
         << setw(10) << "Registered" << endl;
    cout << setw(10) << "Name"
         << setw(50) << "Number"
         << setw(10) << "Courses" << endl;
    for (int u = 0; u < 80; u++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < size; i++)
    {
        if (stdNamesList[i] != " " && stdRegNoList[i] != " ")
        {
            cout << setw(10) << stdNamesList[i]
                 << setw(50) << stdRegNoList[i]
                 << setw(10) << stdCourseList[i]
                 << endl;
        }
    }
    cout << endl;
    for (int u = 0; u < 80; u++)
        cout << "-";
    cout << endl;
}

//This function will check that is students is exist or not corresponding to regisration number....
int searchStudent(string stdRegNo[], int size, string registration)
{
    int index = -1;
    for (int i = 0; i < size; i++)
    {
        if (stdRegNo[i] == registration)
        {
            index = i;
            break;
        }
    }
    return index;
}

//This function will add the students data in arrays...
bool addStudent(string stdNamesList[], string stdRegNoList[], int size, string studentName, string regNnumber)
{
    bool flag = false;
    int i = searchStudent(stdRegNoList, size, " ");
    if (i != -1)
    {
        stdNamesList[i] = studentName;
        stdRegNoList[i] = regNnumber;
        flag = true;
    }
    return flag;
}

//This function will update the student data based on registration number...
bool updateStudent(string stdNamesList[], string stdRegNoList[], int size, string stdRegNoToUpdate, string studentName, string regNnumber)
{
    bool flag = false;
    int updateIndex = searchStudent(stdRegNoList, size, stdRegNoToUpdate);
    if (updateIndex != -1)
    {
        stdNamesList[updateIndex] = studentName;
        stdRegNoList[updateIndex] = regNnumber;
        flag = true;
    }
    return flag;
}

//This function will delete the student data based on registration number....

bool deleteStudent(string stdNamesList[], string stdRegNoList[], string stdCourseList[], int size, string regNnumber)
{

    bool flag = false;
    int i = searchStudent(stdRegNoList, size, regNnumber);
    if (i != -1)
    {
        stdNamesList[i] = " ";
        stdRegNoList[i] = " ";
        stdCourseList[i] = " ";
        flag = true;
    }

    return flag;
}

//This function will search in the student regisered list that the course code
//is already exist or not in student registered courses....

int stdSearchCourseCode(string stdCourseList[], string courseCode, int index)
{

    int M = courseCode.length();
    int N = stdCourseList[index].length();
    string value = stdCourseList[index];

    //TO check that the course code is exist in the string or not...

    for (int i = 0; i <= N - M; i++)
    {
        int j;
        for (j = 0; j < M; j++)
            if (value[i + j] != courseCode[j])
                break;

        if (j == M)
            return i;
    }

    return -1;
}

//This function will registered the course ...
bool registerCourse(string stdRegNoList[], string stdCourseList[], string courseCodeList[], int sizestd, int sizeCourse, string regNo, string courseCode)
{
    bool flag = false;
    string value;
    //This will check at witch index student of the particular registration number is exist...
    int i = searchStudent(stdRegNoList, sizestd, regNo);
    //This will check is course code is exist in courses list...
    int j = searchCourseCode(courseCodeList, sizeCourse, courseCode);
    //This function is important which wil check that is the course is already registered or not by the students....
    int k = stdSearchCourseCode(stdCourseList, courseCode, i);
    if (k == -1 && i != -1 && j != -1)
    {

        int lengthc = courseCodeList[j].length(); //Length of registered course string of particular uset
        int lengthsc = stdCourseList[i].length(); //Length od course code which we want to enter in registered courses...
        if (lengthsc != 0)
        {
            stdCourseList[i] += ':';
        }

        for (int j = 0; j < lengthc; j++)
        {
            stdCourseList[i] = stdCourseList[i] + courseCode[j];
        }
        flag = true;
    }

    return flag;
}

//This function will unregister the courses...
bool unRegisterCourse(string stdRegNoList[], string stdCourseList[], int size, string regNo, string courseCode)
{

    bool flag = false;
    string value;
    string finalString;
    int i = searchStudent(stdRegNoList, size, regNo);

    //By this function we will get the index from which our course code name start that we want to remove

    int index = stdSearchCourseCode(stdCourseList, courseCode, i);
    if (i != -1 && index != -1)
    {

        int lengthc = courseCode.length();        //Length of course code which we want to add in student registered course list...
        int lengthsc = stdCourseList[i].length(); //Length of he registered course list
        string value = stdCourseList[i];

        //But if we have first registered course the index will be zero and before 1st course code there is no collen(:)

        if (index == 0)
        {
            index = index + 1;
        }
        //SO if we get the index then we add the (5) length of course code and then replate every character with empty valu
        //SO we also want to remove the collen(:) before the course code name to that we minus the index by 1
        for (int k = index - 1; k < (index + lengthc); k++)
        {

            value[k] = ' ';
        }
        //Here i take new string to eliminate the null values..
        for (int i = 0; i < value.length(); i++)
        {
            if (value[i] != ' ')
            {
                finalString = finalString + value[i];
            }
        }
        //Then At last store the new and final string at our registered course list...
        stdCourseList[i] = finalString;
        flag = true;
    }
    return flag;
}

//Validate that is the students name is valid or not .....
bool isValidStudentName(string stdName)
{
    bool flag = true;
    if (stdName.length() <= 40)
    {
        for (int i = 0; i < stdName.length(); i++)
        {
            if (!((stdName[i] >= 'A' && stdName[i] <= 'Z') || (stdName[i] >= 'a' && stdName[i] <= 'z') || (stdName[i] == ' ')))
            {
                flag = false;
            }
        }
    }
    else
    {
        flag = false;
    }
    return flag;
}

//Validate is the students registration number is valid or not
bool isValidRegistrationNumber(string regNumber)
{
    bool flag = true;
    if (regNumber.length() == 11)
    {
        for (int i = 0; i < 5; i++)
        {
            if (i >= 0 && i <= 3)
            {
                if (!(regNumber[i] >= '0' && regNumber[i] <= '9'))
                {
                    flag = false;
                }
            }
            else
            {

                if (!(regNumber[i] == '-' && flag == true))
                {
                    flag = false;
                }
            }
        }
        for (int i = 5; i < 8 && flag; i++)
        {
            if (i >= 5 && i <= 6)
            {
                if (!(regNumber[i] >= 'A' && regNumber[i] <= 'Z'))
                {
                    flag = false;
                }
            }
            else
            {
                if (!(regNumber[i] == '-' && flag == true))
                {
                    flag = false;
                }
            }
        }
        for (int i = 8; i < 11 && flag; i++)
        {
            if (!(regNumber[i] >= '0' && regNumber[i] <= '9'))
            {
                flag = false;
            }
        }
    }
    else
    {
        flag = false;
    }
    return flag;
}