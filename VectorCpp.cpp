// VectorCpp.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>

namespace whoami_vector {
    template<class T>
    struct node {
        T _data;
        node* _left;
        node* _right;
        node<T>(T data, node* l = nullptr, node* r = nullptr) {
            _data = data;
            _left = l;
            _right = r;
        }
    };
    template<class T>
    class Vector {
    private:
        node<T>* _begin;
        node<T>* _end;
        size_t _size;
    public:
        Vector() {
            _begin = nullptr;
            _end = nullptr;
            _size = 0;
        }
        Vector(T data) {
            if (_begin == nullptr && _end == nullptr) {
                _begin = new node<T>(data);
                _end = _begin;
                _size = 1;
            }
            else throw std::out_of_range("Error with vector occured...");
        }
        void push_back(T data) {
            if (_begin == nullptr && _end == nullptr) {
                _begin = new node<T>(data);
                _end = _begin;
                _size = 1;
            }
            else {
                auto iterator = _begin;
                while (iterator != _end) {
                    iterator = iterator->_right;
                }
                iterator->_right = new node<T>(data, iterator);
                _end = iterator->_right;
                _size++;

            }
        }
        void pop_back() {
            if (_begin != nullptr && _end != nullptr) {
                if (_begin == _end) {
                    auto tmp = _begin;
                    _begin = _end = nullptr;
                    delete tmp;
                    _size = 0;
                }
                else {
                    auto tmp = _end;
                    _end = _end->_left;
                    delete tmp;
                    _size--;
                }
            }
        }
        size_t size() const {
            return _size;
        }
        T& operator[](size_t index) const {
            if (index >= _size) throw std::out_of_range("Vector index is out of bound...");
            else {
                auto iterator = _begin;
                for (int i = 0; i < index; ++i) {
                    iterator = iterator->_right;
                }
                return iterator->_data;
            }
        }
        T& at(size_t index) const {
            return this->operator[](index);
        }

    };
}

int main()
{
    try {
        whoami_vector::Vector<int> vector(10);
        vector.push_back(10);
        vector.push_back(20);
        vector.push_back(30);
        for (size_t i = 0; i < vector.size(); ++i) {
            std::cout << vector[i] << " ";
        }
        std::cout << std::endl;
        vector.pop_back();
        vector.pop_back();
        vector.pop_back();
        for (size_t i = 0; i < vector.size(); ++i) {
            std::cout << vector[i] << " ";
        }
    }
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}