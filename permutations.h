#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

using namespace std;

// функция, записывающая элементы диапазона в строку
template <typename It>
string PrintRangeToString(It range_begin, It range_end) {
    // удобный тип ostringstream -> https://ru.cppreference.com/w/cpp/io/basic_ostringstream
    ostringstream out;
    for (auto it = range_begin; it != range_end; ++it) {
        out << *it << " "s;
    }
    out << endl;
    // получаем доступ к строке с помощью метода str для ostringstream
    return out.str();
}

template <typename BidirIt>
vector<string> GetPermutations(BidirIt begin, BidirIt end) {
    vector<string> result;
    // Сортируем контейнер. Используем компаратор greater с параметрами 
    // по умолчанию для сортировки в обратном порядке.
    sort(begin, end, greater<>());

    // prev_permutation ->
    //     http://ru.cppreference.com/w/cpp/algorithm/prev_permutation
    // Преобразует диапазон в предыдущую (лексикографически) перестановку,
    // если она существует, и возвращает true,
    // иначе (если не существует) - в последнюю (наибольшую) и возвращает false
    do {
        result.push_back(PrintRangeToString<BidirIt>(begin, end));
    } while (prev_permutation(begin, end));

    return result;
}
