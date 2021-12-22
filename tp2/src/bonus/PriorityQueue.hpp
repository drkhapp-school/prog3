/**
 * @file PriorityQueue.hpp
 * @brief Bonus - File avec priorité dynamique
 * @author 1927230 - Jean-Philippe
 * @version 1.0.0
 * @date 2021-12-21
 */
#include "PQNode.hpp"
#pragma once

template<typename T>
class PriorityQueue {
private:
    PQNode<T> *first;
    size_t count;

public:
    PriorityQueue() {
        first = nullptr;
        count = 0;
    }

    ~PriorityQueue() {
        while (count)
            pop();
    }

    void push(T data, size_t priority) {
        if (!first) {
            first = new PQNode<T>(priority, data);
        } else if (priority < first->priority) {
            first = new PQNode<T>(priority, data, first);
        } else {
            PQNode<T> *runner = first;
            while (runner->next != nullptr && runner->next->priority <= priority) {
                runner = runner->next;
            }
            runner->next = new PQNode<T>(priority, data, runner->next);
        }
        count++;
    }


    void pop() {
        if (count) {
            PQNode<T> *temp = first;
            first = first->next;
            delete temp;
            count--;
        }
    }

    T front_data() { return first ? first->data : NULL; }
    size_t front_priority() { return first ? first->priority : NULL; }
    size_t size() { return count; }
};
