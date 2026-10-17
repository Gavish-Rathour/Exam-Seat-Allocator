#include "StudentManager.h"
#include <fstream>
#include <sstream>
#include <limits>

StudentManager::StudentManager()
{
    count = 0;
}

bool StudentManager::loadFromFile(string fileName)
{
    ifstream inputFile(fileName.c_str());
    if (!inputFile)
        return false;

    count = 0;
    string line, name, rollText, idText, sectionText, subject, course;

    while (getline(inputFile, line) && count < MAX_STUDENTS)
    {
        stringstream ss(line);
        if (!getline(ss, name, '|')) continue;
        if (!getline(ss, rollText, '|')) continue;
        if (!getline(ss, idText, '|')) continue;
        if (!getline(ss, sectionText, '|')) continue;
        if (!getline(ss, subject, '|')) continue;
        if (!getline(ss, course, '|')) continue;

        try
        {
            int roll = stoi(rollText);
            int studentId = stoi(idText);
            char sec = sectionText.empty() ? '-' : sectionText[0];
            students[count] = Student(name, roll, studentId, sec, subject, course);
            count++;
        }
        catch (...)
        {
            cout << "Skipping invalid student record: " << line << endl;
        }
    }
    inputFile.close();
    return true;
}

int StudentManager::getCount() { return count; }
Student* StudentManager::getStudents() { return students; }

void StudentManager::displayAll()
{
    if (count == 0)
    {
        cout << "No student records available.\n";
        return;
    }
    for (int i = 0; i < count; i++)
    {
        Person *person = &students[i];
        person->display();
    }
    cout << "Total students: " << count << endl;
}

int StudentManager::findStudent(int rollno)
{
    for (int i = 0; i < count; i++)
        if (students[i].getRollno() == rollno) return i;
    return -1;
}

int StudentManager::findStudent(string name)
{
    for (int i = 0; i < count; i++)
        if (students[i].getName() == name) return i;
    return -1;
}

void StudentManager::addStudent()
{
    if (count >= MAX_STUDENTS)
    {
        cout << "Student capacity is full.\n";
        return;
    }

    string name, subject, course;
    int roll, studentId;
    char section;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter name: "; getline(cin, name);
    cout << "Enter roll number: "; cin >> roll;
    if (findStudent(roll) != -1)
    {
        cout << "This roll number already exists.\n";
        return;
    }
    cout << "Enter ID: "; cin >> studentId;
    cout << "Enter section character: "; cin >> section;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter subject: "; getline(cin, subject);
    cout << "Enter course: "; getline(cin, course);

    students[count] = Student(name, roll, studentId, section, subject, course);
    count++;
    cout << "Student added in current session.\n";
}

void StudentManager::updateStudent()
{
    int roll;
    cout << "Enter roll number of student to update: ";
    cin >> roll;
    int index = findStudent(roll);
    if (index == -1)
    {
        cout << "Student not found.\n";
        return;
    }

    string name, subject, course;
    int studentId;
    char section;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter new name: "; getline(cin, name);
    cout << "Enter new ID: "; cin >> studentId;
    cout << "Enter new section character: "; cin >> section;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter new subject: "; getline(cin, subject);
    cout << "Enter new course: "; getline(cin, course);

    students[index].setName(name);
    students[index].setId(studentId);
    students[index].setSection(section);
    students[index].setSubject(subject);
    students[index].setCourse(course);
    cout << "Student updated in current session.\n";
}

void StudentManager::deleteStudent()
{
    int roll;
    cout << "Enter roll number of student to delete: ";
    cin >> roll;
    int index = findStudent(roll);
    if (index == -1)
    {
        cout << "Student not found.\n";
        return;
    }

    for (int i = index; i < count - 1; i++)
        students[i] = students[i + 1];
    count--;
    cout << "Student deleted from current session.\n";
}
