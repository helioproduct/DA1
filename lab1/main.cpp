#include <iostream>
#include <algorithm>
#include <cstring>

const size_t MAX_STRING_LEN = 2049;
const size_t RADIX_SIZE = 16;
const size_t RADIX_COUNT = 4;
const uint64_t RADIX_MASK = (1 << RADIX_SIZE) - 1;
const size_t BASE_CAPACITY = 100;

typedef struct Item {
    uint64_t key;
    char value[MAX_STRING_LEN];
} item_t;


uint64_t get_radix(uint64_t number, size_t n) {
    return (number >> (RADIX_SIZE * n)) & RADIX_MASK;
}

void radix_sort(item_t *array, size_t len) {
    int *count;
    item_t *result;

    for (size_t radix = 0; radix < RADIX_COUNT; radix++) {

        uint64_t max_key = 0;
        for (int i = 0; i < len; i++) {
            if (get_radix(array[i].key, radix) > max_key) {
                max_key = get_radix(array[i].key, radix);
            }
        }

        count = (int*) malloc((max_key + 1) * sizeof(int));
        memset(count, 0, max_key + 1);

        for (int i = 0; i < len; i++) {
            count[get_radix(array[i].key, radix)]++;
        }

        for (int i = 1; i <= max_key; i++) {
            count[i] = count[i] + count[i - 1];
        }

        result = (item_t *) malloc(sizeof(item_t) * len);

        for (int i = (int) len - 1; i >= 0; i--) {
            result[count[get_radix(array[i].key, radix)] - 1].key = array[i].key;
            strcpy(result[count[get_radix(array[i].key, radix)] - 1].value, array[i].value);
            count[get_radix(array[i].key, radix)]--;
        }

        for (int i = 0; i < len; i++) {
            array[i].key = result[i].key;
            strcpy(array[i].value, result[i].value);
        }
    }
    free(count);
    free(result);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    char value[MAX_STRING_LEN];
    uint64_t key;

    size_t capacity = BASE_CAPACITY;
    item_t *array;
    array = (item_t *) malloc(capacity * sizeof(item_t));
    size_t size = 0;

    while (std::cin >> key >> value) {
        size++;
        if (size == capacity) {
            capacity *= 2;
            array = (item_t *) realloc(array, capacity * sizeof(item_t));
        }
        array[size - 1].key = key;
        strcpy(array[size - 1].value, value);
    }

    radix_sort(array, size);
    for (int i = 0; i < size; i++) {
        std::cout << array[i].key << "\t" << array[i].value << std::endl;
    }
    free(array);

    return 0;
}
