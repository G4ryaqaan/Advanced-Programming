#pragma once
#include <algorithm>
#include <vector>
#include <memory>

/**
 * @class Sorter
 * @brief This class is used to simply and apply the DRY concept, for the sorting aspect of the application.
 */
template<typename T>
class Sorter {
public:
    using CompareFunction = bool(*)(const T&, const T&);

    static void sort(std::vector<T>& items, CompareFunction comp) {
        std::sort(items.begin(), items.end(), comp);
    }
};
