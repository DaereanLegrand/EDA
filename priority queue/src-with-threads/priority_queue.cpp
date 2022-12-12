#include <iostream>
#include <thread>
#include "stdlib.h"
#include "priority_queue.h"

template<typename T>
Node<T>::Node(T key, int level)
{
	this->key = key;

	forward = new Node*[level + 1];
	memset(forward, 0, sizeof(Node*) * (level + 1));
};

template<typename T>
PriorityQueue<T>::PriorityQueue(int MAXLVL, float P)
{
    this->MAXLVL = MAXLVL;
    this->P = P;
    level = 0;
    header = new Node<T>(-1, MAXLVL);
};
 
template<typename T>
int 
PriorityQueue<T>::randomLevel()
{
    float r = (float)rand()/RAND_MAX;
    int lvl = 0;

    while (r < P && lvl < MAXLVL) {
        lvl++;
        r = (float)rand()/RAND_MAX;
    }

    return lvl;
};
 
template<typename T>
Node<T>*
PriorityQueue<T>::createNode(T key, int level)
{
    Node<T> *n = new Node<T>(key, level);
    return n;
};
 
template<typename T>
void 
PriorityQueue<T>::insertElement(T key)
{
 
    Node<T> *current = header;
    Node<T> *update[MAXLVL+1];
    memset(update, 0, sizeof(Node<T>*)*(MAXLVL+1));
 
    mtx.lock();
    for (int i = level; i >= 0; i--) {
        while (current->forward[i] != NULL &&
              current->forward[i]->key < key)
            current = current->forward[i];
        update[i] = current;
    }
    current = current->forward[0];
    mtx.unlock();
 
    if (current == NULL || current->key != key) {
        int rlevel = randomLevel();
 
    
        if (rlevel > level) {
            for (int i = level + 1; i < rlevel + 1; i++) {
                mtx.lock();
                update[i] = header;
                mtx.unlock();
            }
            level = rlevel;
        }
 
        mtx.lock();
        Node<T>* n = createNode(key, rlevel);
 
        for (int i = 0; i <= rlevel; i++) {
            n->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = n;
        }
        mtx.unlock();
    }
};
 
template<typename T>
void 
PriorityQueue<T>::displayList()
{
    for (int i = 0; i <= level; i++) {
        Node<T> *node = header->forward[i];
        std::cout << "Nivel: " << i << ": ";
        while (node != NULL) {
            std::cout << node->key<<" ";
            node = node->forward[i];
        }
        std::cout << "\n";
    }
};
 
template<typename T>
void 
PriorityQueue<T>::deleteElement(T key)
{
    Node<T> *current = header;
  
    Node<T> *update[MAXLVL+1];
    memset(update, 0, sizeof(Node<T>*)*(MAXLVL+1));
  
    mtx.lock();
    for(int i = level; i >= 0; i--)
    {
        while(current->forward[i] != NULL  &&
              current->forward[i]->key < key)
            current = current->forward[i];
        update[i] = current;
    }
  
    current = current->forward[0];
    mtx.unlock();
  
    if(current != NULL and current->key == key) {
        for(int i=0;i<=level;i++) {
            if(update[i]->forward[i] != current)
                break;
            mtx.lock(); 
            update[i]->forward[i] = current->forward[i];
            mtx.unlock();
        }
  
        while(level>0 && header->forward[level] == 0)
            level--;
    }
};
  
template<typename T>
void 
PriorityQueue<T>::searchElement(T key)
{
    Node<T> *current = header;
  
    for(int i = level; i >= 0; i--) {
        while(current->forward[i] && current->forward[i]->key < key)
            current = current->forward[i];
  
    }
  
    current = current->forward[0];
  
    if(current and current->key == key) 
        std::cout << "Se encontro en: "<< key <<"\n";
};

template<typename T>
void
PriorityQueue<T>::push(T t)
{
    insertElement(t);
}

template<typename T>
void
PriorityQueue<T>::pop()
{
    deleteElement(front());
}

template<typename T>
T
PriorityQueue<T>::front()
{
    return header->forward[0]->key;
}

template<typename T>
void
PriorityQueue<T>::massivePush(std::vector<T> vv)
{
    std::thread *ths = new std::thread[std::thread::hardware_concurrency()];
    int limths = 10;//std::thread::hardware_concurrency();
    int cths = 0;
    int cont = 0;
    while (cont < vv.size()) {
        while (cont < vv.size() && cths < limths) {
            ths[cths++] = std::thread(&PriorityQueue::push, this, vv[cont++]);
        }

        for (int i = 0; i < cths; i++) {
            ths[i].join();
        }
        cths = 0;
        delete [] ths;
        std::thread *ths = new std::thread[std::thread::hardware_concurrency()];
    }
}
