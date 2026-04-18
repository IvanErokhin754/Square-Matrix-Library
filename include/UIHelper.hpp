#ifndef UI_HELPER_HPP
#define UI_HELPER_HPP

#include <iostream>
#include <limits>
#include <string>
#include "Sequence.hpp"

inline void ClearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template<typename Seq>
void PrintSequence(const Seq& seq) {
    std::cout << "[ ";
    for (size_t i = 0; i < seq.GetLength(); i++) {
        std::cout << seq.Get(i) << ' ';
    }
    std::cout << "]\n";
}

template<typename Seq>
void PrintSequenceWithIterator(const Seq& seq)  {
    std::cout << "[ ";
    for (auto it = seq.begin(); it != seq.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << "]\n";
}

inline int DoubleValue(const int& value) {
    return value * 2;
}

inline bool IsEven(const int& value) {
    return value % 2 == 0;
}

inline int Sum(const int& value1, const int& value2) {
    return value1 + value2;
}

inline bool GreaterThanTen(const int& value) {
    return value > 10;
}

inline void PrintSequenceMenu(const std::string& title) {
        std::cout << "\n" << title << " menu:\n";
        std::cout << "1) Append\n";
        std::cout << "2) Prepend\n";
        std::cout << "3) InsertAt\n";
        std::cout << "4) Remove\n";
        std::cout << "5) Get\n";
        std::cout << "6) GetFirst\n";
        std::cout << "7) GetLast\n";
        std::cout << "8) GetSubsequence\n";
        std::cout << "9) Concat\n";
        std::cout << "10) Print\n";
        std::cout << "11) Print with iterator\n";
        std::cout << "12) Map (*2)\n";
        std::cout << "13) Where (even)\n";
        std::cout << "14) Reduce (sum)\n";
        std::cout << "15) FindFirst (>10)\n";
        std::cout << "0) Back\n";
        std::cout << "Your choice: ";
}

template<typename Seq>
bool HandleMutableCommonCommands(Seq &seq, int choice) {
    switch(choice) {
        case 5: {
            size_t index;
            std::cout << "Index: ";
            std::cin >> index;
            std::cout << "Element = " << seq.Get(index) << '\n';
            return true;
        }

        case 6: {
            std::cout << "First = " << seq.GetFirst() << '\n';
            return true;
        }

        case 7: {
            std::cout << "Last = " << seq.GetLast() << '\n';
            return true;
        }

        case 8: {
            size_t left, right;
            std::cout << "Start and end indices: ";
            std::cin >> left >> right;
            Sequence<int>* sub = seq.GetSubsequence(left, right);
            std::cout << "Subsequence: [ ";
            for (size_t i = 0; i < sub->GetLength(); i++) {
                std::cout << sub->Get(i) << ' ';
            }
            std::cout << "]\n";
            delete sub;
            return true;
        }

        case 9: {
            int n, x;
            std::cout << "How many elements in second sequence? ";
            std::cin >> n;

            Seq other;
            std::cout << "Enter elements: ";
            
            for (int i = 0; i < n; i++) {
                std::cin >> x;
                other.Append(x);
            }

            Sequence<int>* result = seq.Concat(other);
            std::cout << "Concatenation: [ ";
            for (size_t i = 0; i < result->GetLength(); i++) {
                std::cout << result->Get(i) << ' ';
            }
            std::cout << "]\n";
            delete result;
            return true;
        }

        case 10: {
            PrintSequence(seq);
            return true;
        }

        case 11: {
            PrintSequenceWithIterator(seq);
            return true;
        }

        case 12: {
            Sequence<int>* result = seq.Map(DoubleValue);
            std::cout << "Mapped: [ ";
            for (size_t i = 0; i < result->GetLength(); i++) {
                std::cout << result->Get(i) << ' ';
            }
            std::cout << "]\n";
            delete result;
            return true;
        }

        case 13: {
            Sequence<int>* result = seq.Where(IsEven);
            std::cout << "Filtered: [ ";
            for (size_t i = 0; i < result->GetLength(); i++) {
                std::cout << result->Get(i) << ' ';
            }
            std::cout << "]\n";
            delete result;
            return true;
        }

        case 14: {
            int result = seq.Reduce(Sum, 0);
            std::cout << "Reduce result = " << result << '\n';
            return true;
        }
        
        case 15: {
            long long pos = seq.FindFirst(GreaterThanTen);
            std::cout << "FindFirst result = " << pos << '\n';
            return true;
        }

        default:
            return false;
    }
        
}

#endif /* UI_HELPER_HPP */
