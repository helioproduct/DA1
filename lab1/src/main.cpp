#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>

const size_t MAX_STRING_LEN = 2049;
const size_t RADIX_SIZE = 16;
const size_t RADIX_COUNT = 4;
const uint64_t RADIX_MASK = (1 << RADIX_SIZE) - 1;
const size_t BASE_CAPACITY = 10000;

struct MyString {
    static const size_t MAX_STRING_SIZE = 2049;

    size_t Size;
    char *Data;

    MyString() {
        Size = 0;
        Data = nullptr;
    }

    explicit MyString(const char str[MAX_STRING_SIZE]) {
        for (size_t i = 0; i < MAX_STRING_SIZE; ++i) {
            if (str[i] == 0) {
                Size = i;
                break;
            }
        }
        Data = new char[Size];
        for (size_t i = 0; i < Size; ++i) {
            Data[i] = str[i];
        }
    }

    MyString &operator=(const MyString &another) {
        delete[] Data;
        Size = another.Size;
        Data = new char[Size];
        for (size_t i = 0; i < Size; ++i) {
            Data[i] = another.Data[i];
        }
        return *this;
    }

    friend MyString operator<<(MyString out, const MyString &str) {
        for (size_t i = 0; i < str.Size; ++i) {
            out << str.Data[i];
        }
        return reinterpret_cast<const MyString &>(out);
    }

    ~MyString() { delete[] Data; }
};

typedef struct Item {
    uint64_t key;
    MyString value;
} item_t;

uint64_t get_radix(uint64_t number, size_t n) {
    return (number >> (RADIX_SIZE * n)) & RADIX_MASK;
}

void radix_sort(item_t *array, size_t len) {
    item_t *result;
    result = new item_t[len];

    for (size_t radix = 0; radix < RADIX_COUNT; radix++) {
        int *count;

        uint64_t max_key = 0;
        for (size_t i = 0; i < len; ++i) {
            if (get_radix(array[i].key, radix) > max_key) {
                max_key = get_radix(array[i].key, radix);
            }
        }

        count = new int[max_key + 1];
        memset(count, 0, (max_key + 1) * sizeof(int));

        for (size_t i = 0; i < len; i++) {
            count[get_radix(array[i].key, radix)]++;
        }
        for (size_t i = 1; i <= max_key; i++) {
            count[i] = count[i] + count[i - 1];
        }

        for (long long i = (long long)len - 1; i >= 0; --i) {
            size_t index = count[get_radix(array[i].key, radix)] - 1;
            result[index].key = array[i].key;
            result[index].value = array[i].value;
            count[get_radix(array[i].key, radix)]--;
        }

        for (size_t i = 0; i < len; i++) {
            array[i].key = result[i].key;
            array[i].value = result[i].value;
        }
        delete[] count;
    }
    delete[] result;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    char temp_value[MAX_STRING_LEN];

    uint64_t key;
    size_t capacity = BASE_CAPACITY;
    size_t size = 0;

    item_t *array;
    array = new item_t[capacity];

    while (std::cin >> key >> temp_value) {
        size++;
        if (size == capacity) {
            capacity *= 2;

            item_t *new_array;
            new_array = new item_t[capacity];
            for (int i = 0; i < size; i++) {
                new_array[i] = array[i];
            }
            delete[] array;
            array = new_array;
        }
        array[size - 1].key = key;
        array[size - 1].value = MyString(temp_value);
    }

    radix_sort(array, size);
    for (size_t i = 0; i < size; i++) {
        std::cout << array[i].key << "\t";
        std::cout << array[i].value << "\n";
    }

    delete[] array;

    return 0;
}