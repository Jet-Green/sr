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

// Узел бинарного дерева для индексации по Id
struct TreeNode {
    int id;               // Ключевой атрибут (Id)
    int originalIndex;    // Индекс записи в массиве
    TreeNode* left;       // Указатель на левого потомка
    TreeNode* right;      // Указатель на правого потомка

    TreeNode(int k, int i) : id(k), originalIndex(i), left(nullptr), right(nullptr) {}
};

// Добавление узла в бинарное дерево
TreeNode* insert(TreeNode* root, int id, int originalIndex) {
    if (!root) {
        return new TreeNode(id, originalIndex); // Создаем новый узел
    }
    if (id < root->id) {
        root->left = insert(root->left, id, originalIndex); // Рекурсивно идем влево
    }
    else if (id > root->id) {
        root->right = insert(root->right, id, originalIndex); // Рекурсивно идем вправо
    }
    return root; // Возвращаем корень дерева
}

// Поиск элемента в бинарном дереве по ключу
int find(TreeNode* root, int id) {
    if (!root) {
        return -1; // Элемент не найден
    }
    if (root->id == id) {
        return root->originalIndex; // Возвращаем индекс записи
    }
    if (id < root->id) {
        return find(root->left, id); // Рекурсивно ищем в левом поддереве
    }
    else {
        return find(root->right, id); // Рекурсивно ищем в правом поддереве
    }
}

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
    cout << "\nСтудент #" << (index + 1) << ":\n"
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
        cout << "Массив отсортирован по возрастанию Id" << endl;
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
        cout << "Массив отсортирован по убыванию Id" << endl;
    }
}

void printAllStudentByIdIndexes(Student* students, IdIndex* indexesPtr, int length) {
    for (int i = 0; i < length; i++) {
        int index = indexesPtr[i].OriginalIndex; // Получение индекса из массива индексов
        printStudent(students[index], index);
    }
}

void indexedSortByAge(AgeIndex* ageIndexesPtr, int length, bool isAscending) {
    if (isAscending) {
        // Сортировка по возрастанию
        for (int i = 1; i < length; i++) {
            AgeIndex key = ageIndexesPtr[i];
            int j = i - 1;

            while (j >= 0 && ageIndexesPtr[j].Age > key.Age) {
                ageIndexesPtr[j + 1] = ageIndexesPtr[j];
                j--;
            }

            ageIndexesPtr[j + 1] = key;
        }
        cout << "Массив отсортирован по возрастанию Age" << endl;
    }
    else {
        // Сортировка по убыванию
        for (int i = 1; i < length; i++) {
            AgeIndex key = ageIndexesPtr[i];
            int j = i - 1;

            while (j >= 0 && ageIndexesPtr[j].Age < key.Age) {
                ageIndexesPtr[j + 1] = ageIndexesPtr[j];
                j--;
            }

            ageIndexesPtr[j + 1] = key;
        }
        cout << "Массив отсортирован по убыванию Age" << endl;
    }
}

void printAllStudentByAgeIndexes(Student* students, AgeIndex* indexesPtr, int length) {
    for (int i = 0; i < length; i++) {
        int index = indexesPtr[i].OriginalIndex; // Получение индекса из массива индексов
        printStudent(students[index], index);
    }
}

// Бинарный поиск по Id в массиве, отсортированном по возрастанию, итеративный вариант
bool binarySearchByIdAscending(IdIndex* idIndexesPtr, int length, int targetId, IdIndex& result) {
    int low = 0;
    int high = length - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (idIndexesPtr[mid].Id == targetId) {
            result = idIndexesPtr[mid];
            return true;
        }
        else if (idIndexesPtr[mid].Id < targetId) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    return false;
}

// Рекурсивный бинарный поиск по Age в массиве, отсортированном по возрастанию
bool binarySearchByAgeAscendingRecursive(AgeIndex* ageIndexesPtr, int low, int high, int targetAge, AgeIndex& result) {
    if (low > high) {
        return false;
    }

    int mid = low + (high - low) / 2;
    if (ageIndexesPtr[mid].Age == targetAge) {
        result = ageIndexesPtr[mid];
        return true;
    }
    else if (ageIndexesPtr[mid].Age < targetAge) {
        return binarySearchByAgeAscendingRecursive(ageIndexesPtr, mid + 1, high, targetAge, result);
    }
    else {
        return binarySearchByAgeAscendingRecursive(ageIndexesPtr, low, mid - 1, targetAge, result);
    }
}

bool findStudentByAge(Student* studentsPtr, AgeIndex& ageSearchResult, AgeIndex* ageIndexesPtr, int length)
{
    int targetAge = integerInput("Введите Age, по которому нужно найти студента: ");
    bool isAgeFound = binarySearchByAgeAscendingRecursive(ageIndexesPtr, 0, length - 1, targetAge, ageSearchResult);

    if (isAgeFound) {
        cout << "Результат поиска: " << endl;
        printStudent(studentsPtr[ageSearchResult.OriginalIndex], ageSearchResult.OriginalIndex);
    }
    else {
        cout << "Студент с Age: " << targetAge << " не найден" << endl;
    }

    return isAgeFound;
}

bool findStudentById(Student* studentsPtr, IdIndex& searchResult, IdIndex* idIndexesPtr, int length)
{
    int targetId = integerInput("Введите Id, по которому нужно найти студента: ");
    bool isIdFound = binarySearchByIdAscending(idIndexesPtr, length, targetId, searchResult);

    if (isIdFound) {
        cout << "Результат поиска: " << endl;
        printStudent(studentsPtr[searchResult.OriginalIndex], searchResult.OriginalIndex);
    }
    else {
        cout << "Студент с Id " << targetId << " не найден" << endl;
    }

    return isIdFound;
}

void editStudentById(Student* studentsPtr, IdIndex* idIndexesPtr, int length) {
    IdIndex searchResult;
    bool isFound = findStudentById(studentsPtr, searchResult, idIndexesPtr, length);

    if (isFound)
    {
        int targetId = integerInput("Введите, на какое Id заменить: ");

        for (int i = 0; i < length; i++) {
            if (searchResult.Id == idIndexesPtr[i].Id)
            {
                idIndexesPtr[i].Id = targetId;
                studentsPtr[searchResult.OriginalIndex].Id = targetId;

                cout << "Студент успешно отредактирован, результат: " << endl;
                printStudent(studentsPtr[searchResult.OriginalIndex], searchResult.OriginalIndex);
                return;
            }
        }
    }
}

void editStudentByAge(Student* studentsPtr, AgeIndex* ageIndexesPtr, IdIndex* idIndexesPtr, int length) {
    IdIndex searchResult;
    bool isFound = findStudentById(studentsPtr, searchResult, idIndexesPtr, length);

    if (isFound)
    {
        int targetAge = integerInput("Введите, на какой Age заменить: ");

        studentsPtr[searchResult.OriginalIndex].Age = targetAge;
        for (int i = 0; i < length; i++) {
            if (ageIndexesPtr[i].OriginalIndex == searchResult.OriginalIndex)
            {
                ageIndexesPtr[i].Age = targetAge;
                return;
            }
        }
    }
}

void deleteStudentById(Student* studentsPtr, IdIndex* idIndexesPtr, AgeIndex* ageIndexesPtr, int& length)
{
    IdIndex searchResult;
    bool isFound = findStudentById(studentsPtr, searchResult, idIndexesPtr, length);

    if (isFound)
    {
        // удаление из массива, индексированного по Id
        for (int i = 0; i < length - 1; i++)
        {
            if (idIndexesPtr[i].Id == searchResult.Id) {
                // сдвинуть все элементы
                for (int j = i + 1; j < length; j++) {
                    idIndexesPtr[j - 1] = idIndexesPtr[j];
                }
            }
        }

        // удаление из массива, индексированного по Age
        for (int i = 0; i < length - 1; i++)
        {
            if (ageIndexesPtr[i].OriginalIndex == searchResult.OriginalIndex) {
                // сдвинуть все элементы
                for (int j = i + 1; j < length; j++) {
                    ageIndexesPtr[j - 1] = ageIndexesPtr[j];
                }
            }
        }

        // удаление из исходного массива
        for (int i = 0; i < length - 1; i++)
        {
            if (studentsPtr[i].Id == searchResult.Id) {
                // сдвинуть все элементы
                for (int j = i + 1; j < length; j++) {
                    studentsPtr[j - 1] = studentsPtr[j];
                }
            }
        }

        cout << "Студент с Id " << searchResult.Id << " удалён!" << endl << endl;
        length -= 1;
    }
}

// Обход для вывода данных
void recursiveAscendingPrintByTree(TreeNode* node, Student* studentsPtr) {
    if (!node) return;

    recursiveAscendingPrintByTree(node->left, studentsPtr); // Рекурсивный обход левого поддерева
    printStudent(studentsPtr[node->originalIndex], node->originalIndex);
    recursiveAscendingPrintByTree(node->right, studentsPtr); // Рекурсивный обход правого поддерева
}

// Обход по убыванию для вывода данных
void recursiveDescendingPrintByTree(TreeNode* node, Student* studentsPtr) {
    if (!node) return;

    recursiveDescendingPrintByTree(node->right, studentsPtr); // Рекурсивный обход правого поддерева
    printStudent(studentsPtr[node->originalIndex], node->originalIndex); // Вывод данных
    recursiveDescendingPrintByTree(node->left, studentsPtr); // Рекурсивный обход левого поддерева
}

// Функция поиска элемента по Id
void searchByIdInTree(TreeNode* root, int targetId, Student* studentsPtr) {
    if (!root) {
        cout << "Студент с Id " << targetId << " не найден." << endl << endl;
        return;
    }

    if (targetId == root->id) {
        printStudent(studentsPtr[root->originalIndex], root->originalIndex);
    }
    else if (targetId < root->id) {
        searchByIdInTree(root->left, targetId, studentsPtr); // Поиск в левом поддереве
    }
    else {
        searchByIdInTree(root->right, targetId, studentsPtr); // Поиск в правом поддереве
    }
}

int main()
{
    // кодировка
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const int maxStudents = 100; // Максимально допустимое количество студентов

    Student* studentsPtr = nullptr;
    int length = 0;

    IdIndex idSearchResult;
    AgeIndex ageSearchResult;

    // Построение бинарного дерева индексации на основе Id
    TreeNode* rootNode = nullptr;

    int answer = 0;

    cout << "Выберите из меню: " << endl;
    cout << "1. Ручной ввод с построением дерева" << endl;
    cout << "2. Ввод из файла" << endl;
    cin >> answer;

    switch (answer) {
        case 1:
            /*length = integerInput("Введите длину массива: ");

            studentsMainInput(&studentsPtr, length);*/

            studentsPtr = new Student[maxStudents];
            readStudentsFromFile("РИС-24-10 Дзюин ГВ (СР данные).csv", &studentsPtr, length);
            
            for (int i = 0; i < length; i++) {
                rootNode = insert(rootNode, studentsPtr[i].Id, i);
            }
            while (answer != 0) {
                answer = integerInput("1. Рекурсивный вывод данных по возрастанию Id\n2. Рекурсивный вывод данных по убыванию Id\n\n3. Поиск по дереву по Id\n0. Выход");

                switch (answer) {
                    case 1:
                        recursiveAscendingPrintByTree(rootNode, studentsPtr);
                        break;
                    case 2:
                        recursiveDescendingPrintByTree(rootNode, studentsPtr);
                        break;
                    case 3:
                        int targetId = integerInput("Введите Id, по которому нужно найти студента: ");
                        searchByIdInTree(rootNode, targetId, studentsPtr);
                        break;
                }
            }
            break;
        case 2:
            studentsPtr = new Student[maxStudents];
            readStudentsFromFile("РИС-24-10 Дзюин ГВ (СР данные).csv", &studentsPtr, length);

            IdIndex* idIndexesPtr = new IdIndex[length]; // индексы, которые мы будем сортировать по Id
            bool areIdIndexesSorted = false;
            for (int i = 0; i < length; i++) {
                idIndexesPtr[i].OriginalIndex = i;
                idIndexesPtr[i].Id = studentsPtr[i].Id;
            }

            AgeIndex* ageIndexesPtr = new AgeIndex[length]; // индексы, которые мы будем сортировать по Age
            bool areAgeIndexesSorted = false;
            for (int i = 0; i < length; i++) {
                ageIndexesPtr[i].OriginalIndex = i;
                ageIndexesPtr[i].Age = studentsPtr[i].Age;
            }
            
            while (answer != 0) {
                answer = integerInput("\nВыберите из списка: \n1. Сортировка по возрастанию по Id\n2. Сортировка по убыванию по Id\n3. Вывести массив, индексированный по Id\n\n4. Сортировка по возрастанию по Age\n5. Сортировка по убыванию по Age\n6. Вывести массив, индексированный по Age\n\n7. Найти студена по Id (итеративный вариант)\n8. Найти студента по Age (реккурентный вариант)\n\n9. Найти по Id и отредактировать Id\n10. Найти по Id и отредактировать Age\n\n11. Удалить студента по Id\n0. Выход\n");

                switch (answer) {
                    case 1:
                        indexedSortById(idIndexesPtr, length, true);
                        areIdIndexesSorted = true;
                        break;
                    case 2:
                        indexedSortById(idIndexesPtr, length, false);
                        break;
                    case 3:
                        printAllStudentByIdIndexes(studentsPtr, idIndexesPtr, length);
                        break;
                    case 4:
                        indexedSortByAge(ageIndexesPtr, length, true);
                        areAgeIndexesSorted = true;
                        break;
                    case 5:
                        indexedSortByAge(ageIndexesPtr, length, false);
                        break;
                    case 6:
                        printAllStudentByAgeIndexes(studentsPtr, ageIndexesPtr, length);
                        break;
                    case 7:
                        if (!areIdIndexesSorted) {
                            cout << "Массив, индексированный по Id, не отсортирован по возрастанию!" << endl << endl;
                            break;
                        }
                        findStudentById(studentsPtr, idSearchResult, idIndexesPtr, length);
                        
                        break;
                    case 8:
                        if (!areAgeIndexesSorted) {
                            cout << "Массив, индексированный по Age, не отсортирован по возрастанию!" << endl << endl;
                            break;
                        }
                        findStudentByAge(studentsPtr, ageSearchResult, ageIndexesPtr, length);
                        break;
                    case 9:
                        if (!areIdIndexesSorted) {
                            cout << "Массив, индексированный по Id, не отсортирован по возрастанию!" << endl << endl;
                            break;
                        }
                        editStudentById(studentsPtr, idIndexesPtr, length);
                        areIdIndexesSorted = false;
                        break;
                    case 10:
                        if (!areIdIndexesSorted) {
                            cout << "Массив, индексированный по Id, не отсортирован по возрастанию!" << endl << endl;
                            break;
                        }
                        editStudentByAge(studentsPtr, ageIndexesPtr, idIndexesPtr, length);
                        areAgeIndexesSorted = false;
                        break;
                    case 11:
                        if (!areIdIndexesSorted) {
                            cout << "Массив, индексированный по Id, не отсортирован по возрастанию!" << endl << endl;
                            break;
                        }

                        deleteStudentById(studentsPtr, idIndexesPtr, ageIndexesPtr, length);
                        break;
                }
            }
            break;
    }

    // освобождаем память
    delete[] studentsPtr;
}