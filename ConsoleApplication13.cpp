#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class rewers {
private:
    string n1;
    double w1;
    double leng;
    double maxdep;
    string type;

public:
    // Конструктор за замовчуванням
    rewers() : n1("Unknown"), w1(0), leng(0), maxdep(0), type("Unknown") {}

    // Конструктор з параметрами
    explicit rewers(const string& n1, double w1, double leng, double maxdep, const string& type)
        : n1(n1), w1(w1), leng(leng), maxdep(maxdep), type(type) {}

    // Конструктор копіювання
    rewers(const rewers& other)
        : n1(other.n1), w1(other.w1), leng(other.leng), maxdep(other.maxdep), type(other.type) {}

    // Деструктор
    ~rewers() {}

    // Методи set
    void setn1(const string& n1) { this->n1 = n1; }
    void setwleng(double w1) { this->w1 = w1; }
    void setleng(double leng) { this->leng = leng; }
    void setmaxdepMmaxdep(double maxdep) { this->maxdep = maxdep; }
    void settype(const string& type) { this->type = type; }

    // Методи get
    string getn1() const { return n1; }
    double getwleng() const { return w1; }
    double getleng() const { return leng; }
    double getmaxdep() const { return maxdep; }
    string gettype() const { return type; }

    // Визначення приблизного обсягу (ширина * довжина * максимальна глибина)
    double getVolume() const {
        return w1 * leng * maxdep;
    }

    // Визначення площі водної поверхні (ширина * довжина)
    double gethol() const {
        return w1 * leng;
    }

    // Метод для перевірки, чи належать водойми до одного типу
    bool getlok(const rewers& other) const {
        return this->type == other.type;
    }

    // Метод для порівняння площі водної поверхні водойм одного типу
    bool compareSurfaceArea(const rewers& other) const {
        if (this->getlok(other)) {
            return this->gethol() > other.gethol();
        }
        cerr << "Водойми не одного типу для порівняння!\n";
        return false;
    }

    // Метод для копіювання об'єкта
    rewers& operator=(const rewers& other) {
        if (this != &other) {
            this->n1 = other.n1;
            this->w1 = other.w1;
            this->leng = other.leng;
            this->maxdep = other.maxdep;
            this->type = other.type;
        }
        return *this;
    }

    // Метод для відображення даних про водойму
    void display() const {
        cout << "Назва: " << n1 << "\nТип: " << type
            << "\nШирина: " << w1 << " м\nДовжина: " << leng
            << " м\nМаксимальна глибина: " << maxdep << " м\n"
            << "Площа поверхні: " << gethol() << " м²\n"
            << "Об'єм: " << getVolume() << " м³\n";
    }

    // Запис інформації про об'єкт у текстовий файл
    void savetont(const string& filename) const {
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << n1 << "," << type << "," << w1 << "," << leng << "," << maxdep << "\n";
            file.close();
        }
        else {
            cerr << "Не вдалося відкрити файл!\n";
        }
    }

    // Запис інформації про об'єкт у бінарний файл
    void savetont(const string& filename) const {
        ofstream file(filename, ios::binary | ios::app);
        if (file.is_open()) {
            size_t nameLen = n1.length();
            file.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
            file.write(n1.c_str(), nameLen);

            size_t typeLen = type.length();
            file.write(reinterpret_cast<const char*>(&typeLen), sizeof(typeLen));
            file.write(type.c_str(), typeLen);

            file.write(reinterpret_cast<const char*>(&w1), sizeof(w1));
            file.write(reinterpret_cast<const char*>(&leng), sizeof(leng));
            file.write(reinterpret_cast<const char*>(&maxdep), sizeof(maxdep));
            file.close();
        }
        else {
            cerr << "Не вдалося відкрити файл!\n";
        }
    }
};

// Динамічний масив об'єктів Reservoir
class ReservoirArray {
private:
    vector<rewers> reservoirs;

public:
    // Додати нову водойму
    void rewers1(const rewers& reservoir) {
        reservoirs.push_back(reservoir);
    }

    // Видалити водойму за індексом
    void removeReservoir(size_t index) {
        if (index < reservoirs.size()) {
            reservoirs.erase(reservoirs.begin() + index);
        }
        else {
            cerr << "Неправильний індекс!\n";
        }
    }

    // Відобразити інформацію про всі водойми
    void displayAll() const {
        for (const auto& reservoir : reservoirs) {
            reservoir.display();
            cout << "-------------------------\n";
        }
    }

    // Запис усіх об'єктів у текстовий файл
    void sevekron(const string& filename) const {
        for (const auto& reservoir : reservoirs) {
            reservoir.savetont(filename);
        }
    }

    // Запис усіх об'єктів у бінарний файл
    void sevea(const string& filename) const {
        for (const auto& reservoir : reservoirs) {
            reservoir.savetont(filename);
        }
    }
};

int main() {
    ReservoirArray array;

    // Створення кількох водойм
    rewers r1("Море", 2000, 5000, 200, "Море");
    rewers r2("Озеро", 1000, 1500, 50, "Озеро");
    rewers r3("Ставок", 300, 400, 10, "Ставок");

    // Додавання у масив
    array.rewers1(r1);
    array.rewers1(r2);
    array.rewers1(r3);

    // Відображення всіх водойм
    array.displayAll();


    array.sevekron("reservoirs.txt");
    array.sevea("reservoirs.bin");

    return 0;
}
