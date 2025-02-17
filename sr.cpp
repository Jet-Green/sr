#include <iostream>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

struct Student {
    int Id;
    string Sex;
    unsigned int Age;
    string City;
    float AcademicPressure;
    float StudyPleasure;
    string SleepHours;
    string DietHabits;
    bool SuicidalThoughts;
    float WorkStudyHours;
    float FinancialPressure;
    bool HasEverHadMentalIllnessInFamily;
    int Depression;
};

struct IdIndex {
    int OriginalIndex;
    int Id;
};

struct AgeIndex {
    int OriginalIndex;
    int Age;
};

int integerInput(string msg) {
    bool isCorrect = false;
    int result;

    do {
        cout << msg << endl;
        cin >> result;

        if (cin.fail()) {
            cout << "Было введено не число!" << endl;
            cin.clear();
            cin.ignore(1000, '\n'); // Очистка ввода
        }
        else {
            isCorrect = true;
        }
    } while (!isCorrect);

    return result;
}


float floatInput(string msg) {
    bool isCorrect = false;
    float result;

    do {
        cout << msg << endl;
        cin >> result;

        if (cin.fail()) {
            cout << "Было введено не число!" << endl;
            cin.clear();
            cin.ignore(1000, '\n'); // Очистка ввода
        }
        else {
            isCorrect = true;
        }
    } while (!isCorrect);

    return result;
}

string sexInput() {
    bool isCorrect = false;
    string sex;

    do {
        cout << "Введите пол (Мужчина/Женщина):" << endl;
        cin >> sex;

        if (sex == "Мужчина" || sex == "Женщина") {
            isCorrect = true;
        }
        else {
            cout << "Некорректный ввод" << endl;
        }
    } while (!isCorrect);

    return sex;
}

string dietHabitsInput() {
    bool isCorrect = false;
    string dietHabits;

    do {
        cout << "Введите пищевые привычки (Здоровое/Умеренное/Нездоровое):" << endl;
        cin >> dietHabits;

        if (dietHabits == "Здоровое" || dietHabits == "Умеренное" || dietHabits == "Нездоровое") {
            isCorrect = true;
        }
        else {
            cout << "Некорректный ввод" << endl;
        }
    } while (!isCorrect);

    return dietHabits;
}

bool booleanInput(string msg) {
    string result;
    
    cout << msg << endl;

    do {
        cout << "Введите да/нет: " << endl;
        cin >> result;

        if (result == "да") {
            return true;
        }
        if (result == "нет") {
            return false;
        }
    } while (true);
}

int depressionInput() {
    int result = 0;
    bool isAccepted = false;

    do {
        result = integerInput("Введите показатель Депрессии(0 или 1): ");

        if (result == 0 || result == 1) {
            isAccepted = true;
        }
    } while (!isAccepted);

    return result;
}

void studentInput(Student* student) {
    if (student == nullptr) return;

    student->Id = integerInput("Введите ИД: ");
    student->Sex = sexInput();
    student->Age = integerInput("Введите возраст: ");

    std::cout << "Введите город: " << std::endl;
    std::cin >> student->City;

    student->AcademicPressure = floatInput("Введите показатель академического давления: ");
    student->StudyPleasure = floatInput("Введите показатель удовлетворённости обучением: ");

    std::cout << "Введите диапазон сна: " << std::endl;
    std::cin >> student->SleepHours;

    student->DietHabits = dietHabitsInput();
    student->SuicidalThoughts = booleanInput("Были ли суицидальные мысли? ");
    student->WorkStudyHours = floatInput("Часов учёбы/работы: ");
    student->FinancialPressure = floatInput("Введите показатель финансового давления: ");
    student->HasEverHadMentalIllnessInFamily = booleanInput("Семейная история психических заболеваний: ");
    student->Depression = depressionInput();
}

void studentsMainInput(Student** ptr, int length) {
    if (ptr == nullptr || length <= 0) return;

    *ptr = new Student[length];
    for (int i = 0; i < length; i++) {
        studentInput(&((*ptr)[i]));
    }
}

void printStudent(const Student& student, int index) {
    std::cout << "\nСтудент #" << (index + 1) << ":\n"
        << "ИД: " << student.Id << "\n"
        << "Пол: " << student.Sex << "\n"
        << "Возраст: " << student.Age << "\n"
        << "Город: " << student.City << "\n"
        << "Академическое давление: " << student.AcademicPressure << "\n"
        << "Удовлетворённость обучением: " << student.StudyPleasure << "\n"
        << "Диапазон сна: " << student.SleepHours << "\n"
        << "Привычки питания: " << student.DietHabits << "\n"
        << "Суицидальные мысли: " << (student.SuicidalThoughts ? "Да" : "Нет") << "\n"
        << "Часов учёбы/работы: " << student.WorkStudyHours << "\n"
        << "Финансовое давление: " << student.FinancialPressure << "\n"
        << "История психических заболеваний: " << (student.HasEverHadMentalIllnessInFamily ? "Да" : "Нет") << "\n"
        << "Депрессия: " << student.Depression << "\n";
}

void printAllStudents(Student* students, int length) {
    for (int i = 0; i < length; i++) {
        printStudent(students[i], i);
    }
}


// Функция для преобразования строкового значения в булевое
bool parseBool(const string& str) {
    return str == "1" || str == "yes" || str == "true" || str == "да";
}

bool readStudentsFromFile(const string& filename, Student** students, int& studentCount) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << filename << endl;
        return false;
    }

    vector<Student> studentList; // Используем временный вектор для хранения студентов

    string line;
    while (getline(file, line)) {
        Student student;
        stringstream ss(line);
        string temp;

        try {
            // Читаем и парсим каждое поле из CSV строки
            getline(ss, temp, ';');
            student.Id = stoi(temp);

            getline(ss, student.Sex, ';');

            getline(ss, temp, ';');
            student.Age = stoi(temp);

            getline(ss, student.City, ';');

            getline(ss, temp, ';');
            student.AcademicPressure = stof(temp);

            getline(ss, temp, ';');
            student.StudyPleasure = stof(temp);

            getline(ss, student.SleepHours, ';');

            getline(ss, student.DietHabits, ';');

            getline(ss, temp, ';');
            student.SuicidalThoughts = (temp == "да");

            getline(ss, temp, ';');
            student.WorkStudyHours = stof(temp);

            getline(ss, temp, ';');
            student.FinancialPressure = stof(temp);

            getline(ss, temp, ';');
            student.HasEverHadMentalIllnessInFamily = (temp == "да");

            getline(ss, temp, ';');
            student.Depression = stoi(temp);

            // Добавляем студента в список
            studentList.push_back(student);
        }
        catch (exception& e) {
            cerr << "Ошибка при обработке строки: " << line << ". Пропускаем..." << endl;
            continue; // Если ошибка во входных данных - пропустить строку
        }
    }

    file.close();

    // Если в файле нет валидных данных
    if (studentList.empty()) {
        cerr << "Ошибка: не удалось прочитать данные из файла или файл пуст.\n";
        return false;
    }

    // Выделяем память под массив студентов
    studentCount = studentList.size();
    *students = new Student[studentCount];

    // Копируем студентов из вектора в динамический массив
    for (int i = 0; i < studentCount; ++i) {
        (*students)[i] = studentList[i];
    }

    cout << "Успешно прочитано " << studentCount << " студентов.\n";
    return true;
}

void indexedSortById(IdIndex* idIndexesPtr, int length, bool isAscending) {
    if (isAscending) {
        // Сортировка по возрастанию
        for (int i = 1; i < length; i++) {
            IdIndex key = idIndexesPtr[i];
            int j = i - 1;

            while (j >= 0 && idIndexesPtr[j].Id > key.Id) {
                idIndexesPtr[j + 1] = idIndexesPtr[j];
                j--;
            }

            idIndexesPtr[j + 1] = key;
        }
        cout << "Массив отсортирован по возрастанию" << endl;
    }
    else {
        // Сортировка по убыванию
        for (int i = 1; i < length; i++) {
            IdIndex key = idIndexesPtr[i];
            int j = i - 1;

            while (j >= 0 && idIndexesPtr[j].Id < key.Id) {
                idIndexesPtr[j + 1] = idIndexesPtr[j];
                j--;
            }

            idIndexesPtr[j + 1] = key;
        }
        cout << "Массив отсортирован по убыванию" << endl;
    }
}

void printAllStudentByIdIndexes(Student* students, IdIndex* indexesPtr, int length) {
    for (int i = 0; i < length; i++) {
        int index = indexesPtr[i].OriginalIndex; // Получение индекса из массива индексов
        printStudent(students[index], index);
    }
}

int main()
{
    // кодировка
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Student* studentsPtr = nullptr;
    int length = 0;

    int answer = 0;

    cout << "Выберите из меню: " << endl;
    cout << "1. Ручной ввод" << endl;
    cout << "2. Ввод из файла" << endl;
    cin >> answer;

    switch (answer) {
        case 1:
            length = integerInput("Введите длину массива: ");

            studentsMainInput(&studentsPtr, length);
            printAllStudents(studentsPtr, length);
            break;
        case 2:
            const int maxStudents = 100; // Максимально допустимое количество студентов
            studentsPtr = new Student[maxStudents];
            readStudentsFromFile("РИС-24-10 Дзюин ГВ (СР данные).csv", &studentsPtr, length);

            IdIndex* idIndexesPtr = new IdIndex[length]; // индексы, которые мы будем сортировать
            for (int i = 0; i < length; i++) {
                idIndexesPtr[i].OriginalIndex = i;
                idIndexesPtr[i].Id = studentsPtr[i].Id;
            }
            
            while (answer != 0) {
                answer = integerInput("\nВыберите из списка: \n1. Сортировка по возрастанию по Id\n2. Сортировка по убыванию по Id\n3. Вывести отсортированный массив\n0. Выход\n");

                switch (answer) {
                    case 1:
                        indexedSortById(idIndexesPtr, length, true);
                        break;
                    case 2:
                        indexedSortById(idIndexesPtr, length, false);
                        break;
                    case 3:
                        printAllStudentByIdIndexes(studentsPtr, idIndexesPtr, length);
                        break;
                }
            }
            break;
    }

    // освобождаем память
    delete[] studentsPtr;
}