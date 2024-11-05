#pragma once
#include <list>
#include <iostream>

/**
 * @struct MyComparator
 * @brief Default comparator for priority queue elements.
 */
template <typename T>
struct MyComparator {

    /**
     * @brief Compares two elements.
     * @param a First element.
     * @param b Second element.
     * @return True if a is less than b.
     */
    bool operator()(const T& a, const T& b) const {
        return a < b;
    }
};

/**
 * @class PriorityQueue
 * @brief Implements a priority queue with a maximum size.
 */
template <typename T, typename Comparator = MyComparator<T>>
class PriorityQueue {
private:
    std::list<T> queue;
    Comparator comparator;
    size_t max_size;
    size_t print_size;

public:

    /**
     * @brief Constructs a PriorityQueue with the specified maximum size and print size.
     * @param maxSize Maximum size of the queue.
     * @param printSize Number of top elements to print.
     */
    PriorityQueue(size_t maxSize, size_t printSize);

    /**
     * @brief Pushes an element into the queue.
     * @param element The element to push.
     */
    void push(const T& element);

    /**
     * @brief Polls the highest priority element from the queue.
     * @return The highest priority element.
     * @throws std::out_of_range if the queue is empty.
     */
    T poll();

    /**
     * @brief Checks if the queue is empty.
     * @return True if the queue is empty, otherwise false.
     */
    bool isEmpty() const;

    /**
     * @brief Prints the top moves in the queue.
     * @param os Output stream to print the moves.
     */
    void printTopMoves(std::ostream& os) const;

    /**
     * @brief Gets the maximum size of the queue.
     * @return The maximum size of the queue.
     */
    size_t getMaxSize() const { return max_size; }

    /**
     * @brief Gets the number of top elements to print.
     * @return The number of top elements to print.
     */
    size_t getPrintSize() const { return print_size; }
};

template <typename T, typename Comparator>
PriorityQueue<T, Comparator>::PriorityQueue(size_t maxSize, size_t printSize)
        : max_size(maxSize), print_size(printSize) {}

template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::push(const T& element) {
    auto it = queue.begin();
    while (it != queue.end() && comparator(*it, element)) {
        ++it;
    }
    queue.insert(it, element);
    if (queue.size() > max_size) {
        queue.pop_back();
    }
}

template <typename T, typename Comparator>
T PriorityQueue<T, Comparator>::poll() {
    if (queue.empty()) {
        throw std::out_of_range("PriorityQueue is empty");
    }
    T highestPriorityElement = queue.front();
    queue.pop_front();
    return highestPriorityElement;
}

template <typename T, typename Comparator>
bool PriorityQueue<T, Comparator>::isEmpty() const {
    return queue.empty();
}

template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::printTopMoves(std::ostream& os) const {
//    auto it = queue.begin();
//    for (size_t i = 0; i < print_size && it != queue.end(); ++i, ++it) {
//        std::cout << *it << std::endl;
//    }
    size_t count = 0;
    for (const auto& move : queue) {
        if (print_size && count >= print_size) break;
        os <<count+1<<". "<<move << std::endl;
        ++count;
    }
}
