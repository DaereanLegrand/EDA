#include <iostream>
#include <chrono>
#include "priority_queue.h"

void
test(int n)
{
    std::cout << "Test with " << n <<  " elements.\n";
    auto start = std::chrono::high_resolution_clock::now();
    priority_queue2<int, 1> A;
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        A.push(rand() % n);

    for (int i = 0; i < (n / 2); i++)
        A.pop();
    A.print();
    //std::cout << std::endl;
    //for (int i = 0; i < 10; i++)
    //    A.pop();
    //A.print();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout << "Test time: "<< duration.count() << std::endl;
}

int
main()
{
    for (long long i = 10; i < 1000000; i*=10) {
        test(i);
    }
    /*
    // T 1
    std::cout << "Test with 20 elements, 10 pops.\n";
    auto start = std::chrono::high_resolution_clock::now();
    priority_queue2<int, 1> A;
    srand(time(NULL));
    for (int i = 0; i < 20; i++)
        A.push(rand() % 100+1);
    A.print();
    std::cout << std::endl;
    for (int i = 0; i < 10; i++)
        A.pop();
    A.print();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Test time: "<< duration.count() << std::endl;

    // T 2
    std::cout << "Test with 1000 elements.\n";
    start = std::chrono::high_resolution_clock::now();
    priority_queue2<int, 0> B;
    for (int i = 0; i < 10000; i++) {
        B.push(rand() % 1000 + 1);
    }
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Test time: " << duration.count() << std::endl;
    */
    return 0;
}
