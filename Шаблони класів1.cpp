#include <iostream>

template<typename T>
class Array {
private:
    T* data;
    int size;
    int capacity;
    int grow;

public:
    // Конструкторы
    Array() : data(nullptr), size(0), capacity(0), grow(1) {}
    
    Array(int initialSize, int g = 1) : grow(g) {
        capacity = size = initialSize;
        data = new T[capacity]{};
    }
    
    ~Array() {
        delete[] data;
    }
    
    // Получение размера (выделенной памяти)
    int GetSize() const {
        return capacity;
    }
    
    // Установка размера
    void SetSize(int newSize, int g = 1) {
        grow = g;
        if (newSize > capacity) {
            // Увеличиваем емкость с учетом grow
            int newCapacity = newSize + (grow - newSize % grow) % grow;
            T* newData = new T[newCapacity]{};
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = newCapacity;
        } else {
            // Уменьшаем размер
            size = newSize;
            if (newSize < capacity - grow) {
                T* newData = new T[newSize]{};
                for (int i = 0; i < size; i++) {
                    newData[i] = data[i];
                }
                delete[] data;
                data = newData;
                capacity = newSize;
            }
        }
    }
    
    // Получение последнего допустимого индекса
    int GetUpperBound() const {
        return size - 1;
    }
    
    // Проверка на пустоту
    bool IsEmpty() const {
        return size == 0;
    }
    
    // Удаление лишней памяти
    void FreeExtra() {
        if (size < capacity) {
            T* newData = new T[size]{};
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = size;
        }
    }
    
    // Удаление всех элементов
    void RemoveAll() {
        delete[] data;
        data = nullptr;
        size = capacity = 0;
    }
    
    // Получение элемента по индексу
    T GetAt(int index) const {
        return data[index];
    }
    
    // Установка элемента по индексу
    void SetAt(int index, const T& value) {
        data[index] = value;
    }
    
    // Оператор []
    T& operator[](int index) {
        return data[index];
    }
    
    const T& operator[](int index) const {
        return data[index];
    }
    
    // Добавление элемента
    void Add(const T& value) {
        if (size >= capacity) {
            SetSize(capacity + grow, grow);
        }
        data[size++] = value;
    }
    
    // Объединение двух массивов
    void Append(const Array& other) {
        for (int i = 0; i < other.size; i++) {
            Add(other[i]);
        }
    }
    
    // Оператор присваивания
    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            grow = other.grow;
            data = new T[capacity];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    // Получение указателя на данные
    T* GetData() const {
        return data;
    }
    
    // Вставка элемента
    void InsertAt(int index, const T& value) {
        if (size >= capacity) {
            SetSize(capacity + grow, grow);
        }
        for (int i = size; i > index; i--) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        size++;
    }
    
    // Удаление элемента
    void RemoveAt(int index) {
        for (int i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        size--;
    }
    
    // Вывод массива
    void Print() const {
        std::cout << "Массив [размер: " << size << ", емкость: " << capacity << "]: ";
        for (int i = 0; i < size; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

// Демонстрация
int main() {
    Array<int> arr;
    
    std::cout << "=== Тестирование Array ===" << std::endl;
    
    // Добавление элементов
    for (int i = 0; i < 5; i++) {
        arr.Add(i * 10);
    }
    arr.Print();
    
    std::cout << "GetSize: " << arr.GetSize() << std::endl;
    std::cout << "GetUpperBound: " << arr.GetUpperBound() << std::endl;
    std::cout << "IsEmpty: " << arr.IsEmpty() << std::endl;
    
    // Доступ по индексу
    std::cout << "arr[2]: " << arr[2] << std::endl;
    arr[2] = 999;
    std::cout << "После изменения arr[2]: " << arr[2] << std::endl;
    
    // Вставка и удаление
    arr.InsertAt(1, 555);
    std::cout << "После InsertAt(1, 555): ";
    arr.Print();
    
    arr.RemoveAt(2);
    std::cout << "После RemoveAt(2): ";
    arr.Print();
    
    // SetSize с grow
    arr.SetSize(8, 3);
    std::cout << "После SetSize(8, 3): ";
    arr.Print();
    std::cout << "GetSize: " << arr.GetSize() << std::endl;
    
    // Объединение массивов
    Array<int> arr2;
    arr2.Add(100);
    arr2.Add(200);
    arr.Append(arr2);
    std::cout << "После Append: ";
    arr.Print();
    
    // Очистка
    arr.RemoveAll();
    std::cout << "После RemoveAll - IsEmpty: " << arr.IsEmpty() << std::endl;
    
    return 0;
}