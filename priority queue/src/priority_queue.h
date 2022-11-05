#include <iostream>
#include <math.h>
#include <functional>
#include <type_traits>
#include <vector>

template <typename T, bool m>
class priority_queue2 {
public:
    priority_queue2();
    T front();
    bool isempty();
    void is_full();
    bool find(T, int);
    bool findinsert(T, int);
    void resize_data();
    void pop();
    void push(T);
    void swap(int, int);
    void print();
private:
    int size, resize, height, elements, npow;
    std::vector<T> data;
};

template <typename T, bool m>
priority_queue2<T, m>::priority_queue2():
    resize(2), height(1), elements(4), npow(0)
{
    data.resize(4);
}

template <typename T, bool m>
T
priority_queue2<T, m>::front()
{
    return data.at(0);
}

template <typename T, bool m>
bool 
priority_queue2<T, m>::isempty()
{
    if (elements)
        return true;
    return false;
}


template <typename T, bool m>
void
priority_queue2<T, m>::is_full()
{
    height++;
    npow = pow(2, resize + 1);
    data.resize(data.size() + npow);
    resize++;
}

template <typename T, bool m>
void 
priority_queue2<T, m>::resize_data()
{
    height++;
    //std::cout << pow(2, resize + 1) << "\t" << resize + 1 << std::endl;
    npow = pow(2, ++resize);
    data.resize(data.size() + npow);
}

template <typename T, bool m>
void 
priority_queue2<T, m>::pop()
{
    data[1] = data[--elements];
    data[elements] = 0;
    if (elements < npow / 2)
        height--;
    int size = 1, maxt=0,maxi=0,it=0;
    if (m == 1) {
        for (int i = 0; i < height; i++) {
            maxt = -100000000;
            for (int j = 0; j < 2; j++) {
                it = 2 * size + j;
                if (maxt < data[it]) {
                    maxt = data[it];
                    maxi = it;
                }
            }
            if (data[size] < data[maxi] && data[maxi] != 0) {
                swap(size, maxi);
                size = maxi;
                continue;
            }
            break;
        }
    }
    else {
        maxt = 100000000;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < 2; j++) {
                it = 2 * size + j;
                if (maxt >= data[it]) {
                    maxt = data[it];
                    maxi = it;
                }
            }
            if (data[size] >= data[maxi] && data[maxi]!=0) {
                swap(size, maxi);
                size = maxi;
                continue;
            }
            break;
        }
    }
}

template <typename T, bool m>
void 
priority_queue2<T, m>::push(T a)
{
    if (findinsert(a, 1)) {
        return;
    }

    if (elements == 1) {
        data[elements++] = a;
        return;
    }

    if (data.capacity() == elements)
        resize_data();

    int size = elements;
    data[size] = a;

    if (m == 1) {
        for (int i = 0; i < height; i++) {
            if (data[size] >= data[size / 2]) {
                swap(size, size / 2);
                size = size / 2;
                continue;
            }
            break;
        }
    }
    else {
        for (int i = 0; i < height; i++) {
            if (data[size] < data[size / 2]) {
                swap(size, size / 2);
                size = size / 2;
                continue;
            }
            break;
        }
    }
    elements++;
}

template <typename T, bool m>
void 
priority_queue2<T, m>::swap(int i, int j)
{
    std::swap(data[i], data[j]);
}

template<typename T, bool m>
void 
priority_queue2<T, m>::print() {
    int count = 0, i = 0, insert = 0;
    while (count + 1 < elements) {
        int pot = pow(2, i);
        while (pot + insert != count && count + 1 < elements) {
            std::cout << "\t" << data[count + 1];
            count++;
        }
        std::cout << "\n";
        insert = count;
        i++;
    }
}

template<typename T, bool m>
bool
priority_queue2<T, m>::find(T n, int i) {
    if (i >= elements)
        return false;

    if (data[i] == n) {
        return true;
    } else if (m == 1) {
        if (data[i] <= n)
            return false;
    } else {
        if (data[i] > n)
            return false;
    }
    if (find(n, i * 2) || find(n, i * 2 + 1))
        return true;
}


template<typename T, bool m>
bool 
priority_queue2<T, m>::findinsert(T n, int i) {
    if (i >= elements)
        return false;

    if (data[i] == n) {
        return true;
    } else if (m == 1) {
        if (data[i] <= n)
            return false;
    } else {
        if (data[i] > n)
            return false;
    }
    if (findinsert(n, i * 2) || findinsert(n, i * 2 + 1))
        return true;
    return false;
}
