#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

// Перелік спеціальностей
enum Specialnist { KOMP_NAUKY, INFORMATYKA, MAT_EKON, FIZ_INF, TRUD_NAVCH };

// Структура для Рівня А (без об'єднань)
struct Student
{
    string prizv;
    unsigned kurs;
    Specialnist spec;
    int fizyka;
    int matematyka;
    int informatyka;
};

// Прототипи функцій
void Create(Student* s, const int N);
void Print(const Student* s, const int N, const string* specStr);
void PrintExcellentStudents(const Student* s, const int N);
double CalcPercentHighAvg(const Student* s, const int N);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const string specStr[] = {
        "Комп. науки",
        "Інформатика",
        "Мат. та екон.",
        "Фіз. та інф.",
        "Труд. навч."
    };

    int N;
    cout << "Введіть кількість студентів N: ";
    cin >> N;

    if (N <= 0)
    {
        cout << "Кількість студентів має бути більшою за 0." << endl;
        return 1;
    }

    Student* s = new Student[N];

    Create(s, N);
    Print(s, N, specStr);

    PrintExcellentStudents(s, N);

    double percent = CalcPercentHighAvg(s, N);
    cout << fixed << setprecision(2);
    cout << "\nПроцент студентів, у яких середній бал більший за 4.5: "
        << percent << "%" << endl;

    delete[] s;
    return 0;
}

// 1. Формування масиву структур
void Create(Student* s, const int N)
{
    int spec;
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;
        cin.get();
        cin.sync();

        cout << "  прізвище: ";
        getline(cin, s[i].prizv);
        cout << "  курс: ";
        cin >> s[i].kurs;
        cout << "  спеціальність (0 - Комп. науки, 1 - Інформатика, "
            << "2 - Мат. та екон., 3 - Фіз. та інф., 4 - Труд. навч.): ";
        cin >> spec;
        s[i].spec = (Specialnist)spec;

        cout << "  оцінка з фізики: ";
        cin >> s[i].fizyka;
        cout << "  оцінка з математики: ";
        cin >> s[i].matematyka;
        cout << "  оцінка з інформатики: ";
        cin >> s[i].informatyka;
        cout << endl;
    }
}

// 2. Вивід масиву у вигляді таблиці (7 стовпців)
void Print(const Student* s, const int N, const string* specStr)
{
    cout << "\nСписок студентів (Рівень А):" << endl;
    cout << "==============================================================================" << endl;
    cout << "|  №  |   Прізвище   | Курс | Спеціальність | Фізика | Математика | Інформат. |" << endl;
    cout << "------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(3) << right << i + 1 << " "
            << "| " << setw(12) << left << s[i].prizv << " "
            << "| " << setw(4) << right << s[i].kurs << " "
            << "| " << setw(13) << left << specStr[s[i].spec] << " "
            << "| " << setw(6) << right << s[i].fizyka << " "
            << "| " << setw(10) << right << s[i].matematyka << " "
            << "| " << setw(9) << right << s[i].informatyka << " |" << endl;
    }
    cout << "==============================================================================" << endl;
}

// 3. Вивід прізвищ студентів-відмінників (Пункт 1 варіанта)
void PrintExcellentStudents(const Student* s, const int N)
{
    cout << "\nПрізвища студентів, які вчаться на \"відмінно\":" << endl;
    int count = 0;

    for (int i = 0; i < N; i++)
    {
        if (s[i].fizyka == 5 && s[i].matematyka == 5 && s[i].informatyka == 5)
        {
            count++;
            cout << setw(3) << right << count << ". " << s[i].prizv << endl;
        }
    }

    if (count == 0)
    {
        cout << "  Відмінників немає." << endl;
    }
}

// 4. Обчислення проценту студентів із середнім балом > 4.5 (Пункт 2 варіанта)
double CalcPercentHighAvg(const Student* s, const int N)
{
    if (N == 0) return 0.0;

    int count = 0;
    for (int i = 0; i < N; i++)
    {
        double avg = (s[i].fizyka + s[i].matematyka + s[i].informatyka) / 3.0;
        if (avg > 4.5)
        {
            count++;
        }
    }

    return (100.0 * count) / N;
}