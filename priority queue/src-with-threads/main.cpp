#include "priority_queue.h"
#include <iostream>
#include <chrono>

int
main()
{
    std::vector<int> vv;
    int n, t;
    std::cin >> n;
    while (n--) {
        std::cin >> t;
        vv.push_back(t);
    }

    auto start = std::chrono::high_resolution_clock::now();
    srand((unsigned)time(0));
 
    PriorityQueue<int> pq(3, 0.5);
    pq.massivePush(vv);
    // pq.displayList();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout << "Test time: "<< duration.count() << std::endl;
    return 0;
}
