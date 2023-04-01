#include <thread>
#include <iostream>
#include <string>
#include <list>
#include <cstdlib> 
#include <ctime>
#include <random>
#include <mutex>
using namespace std;
mutex g_count_mutex;

int* random_generate(int COUNT_NUMBERS) {
    int* result = new int [COUNT_NUMBERS];
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 10000);
    for (int i = 0; i < COUNT_NUMBERS; i++) {
        result[i] = dist(gen);
    }
    return result;
}

void check(list<int> seq, int thr, int size, int SIZE_SEQ) {
    list <int> ::iterator it;
    int i;
    for (it = seq.begin(), i = 0; it != seq.end(); it++, i++) {
        string s = "Число " + to_string((*it)) + "     Позиция " + to_string(SIZE_SEQ*thr + i) + "     Номер потока " + to_string(thr) + "\n";
        if ((*it) % 3 == 0) cout << s;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int COUNT_THREAD;
    int SIZE_SEQ;
    const long int COUNT_NUMBERS = 100000000;
    cout << "COUNT_THREAD = ";
    cin >> COUNT_THREAD;
    cout << "SIZE_SEQ = ";
    cin >> SIZE_SEQ;
    int* numbers = random_generate(COUNT_NUMBERS);
    thread* Threads = new thread[COUNT_THREAD];

    int start_seq = 0;

    for (int i = 0; i < COUNT_THREAD; i++) {
        int end_seq = start_seq + SIZE_SEQ;
        if (end_seq > COUNT_NUMBERS) end_seq = COUNT_NUMBERS - 1;
        int size = end_seq - start_seq;
        list<int> seq;
        for (int j = 0; j < size; j++) {
            seq.push_back(numbers[i * SIZE_SEQ + j]);

        }
        Threads[i] = thread(check, seq, i, size, SIZE_SEQ);
        start_seq = end_seq;
    }
    for (int i = 0; i < COUNT_THREAD; i++) {
        Threads[i].join();
    }

    delete[] numbers;
}