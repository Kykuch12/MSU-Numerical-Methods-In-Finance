#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>

using namespace std;

size_t GIGABYTE = 1024 * 1024 * 1024;
char FILL_CHAR = ' ';
uint64_t PATTERN_64 = 0x2020202020202020ULL; // 8 пробелов

// 1. Обычный цикл
double test_standard_for(char* a, size_t n) {
    clock_t begin = clock();
    for (size_t i = 0; i < n; i++) {
        a[i] = FILL_CHAR;
    }
    clock_t end = clock();
    return (double)(end - begin) / CLOCKS_PER_SEC;
}

// 2. Встроенный memset
double test_memset(char* a, size_t n) {
    clock_t begin = clock();
    memset(a, FILL_CHAR, n);
    clock_t end = clock();
    return (double)(end - begin) / CLOCKS_PER_SEC;
}

// 3. Ускоренный цикл блоками по 64 бита
double test_fast_for(char* a, size_t n) {
    clock_t begin = clock();
    
    uint64_t* ptr64 = (uint64_t*)a;
    size_t blocks = n / 8;
    
    for (size_t i = 0; i < blocks; i++) {
        ptr64[i] = PATTERN_64;
    }
    
    // Обработка хвоста
    char* tail = a + blocks * 8;
    size_t remainder = n - blocks * 8;
    for (size_t i = 0; i < remainder; i++) {
        tail[i] = FILL_CHAR;
    }
    
    clock_t end = clock();
    return (double)(end - begin) / CLOCKS_PER_SEC;
}

int main() {
    size_t N = GIGABYTE;
    char* a = (char*)malloc(N);
    
    if (a == nullptr) {
        cerr << "Ошибка выделения памяти!" << endl;
        return 1;
    }

    cout << "Размер массива: 1 ГБ" << endl;
    cout << "----------------------" << endl;
    cout << "время for:           " << test_standard_for(a, N) << " с" << endl;
    cout << "время memset:        " << test_memset(a, N) << " с" << endl;
    cout << "время ускоренного for: " << test_fast_for(a, N) << " с" << endl;

    free(a);
    return 0;
}

