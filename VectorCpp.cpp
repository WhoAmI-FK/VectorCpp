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
    
       
   /* template <>
    constexpr double default_value<double> = std::numeric_limits<double>::lowest();
    */


    template<class T>
    class Iterator {
    private:
        node<T>* _ptr;
    public:
        explicit Iterator() : _ptr(nullptr) {

        }
        explicit Iterator(node<T>* ptr) : _ptr(ptr) {

        }
        bool operator==(const Iterator& r) const {
            return this->_ptr == r._ptr;
        }
        bool operator!=(const Iterator& r) const {
            return !(*this == r);
        }
        Iterator& operator++() {
            if (_ptr->_right != nullptr) _ptr = _ptr->_right;
            return *this;
        }
        Iterator& operator++(int) {
            if (_ptr->_right != nullptr) {
                Iterator<T> tmp(*this);
                ++*this;
                return tmp;
            }
        }
        Iterator& operator+(int num) {
            for (int i = 0; i < num; ++i) {
                if (_ptr->_right != nullptr) {
                    _ptr = _ptr->_right;
                }
                else break;
            }
            return *this;
        }
        Iterator& operator-(int num) {
            for (int i = 0; i < num; ++i) {
                if (_ptr->_left != nullptr) {
                    _ptr = _ptr->_left;
                }
                else break;
            }
            return *this;
        }
         node<T>* operator*() {
            return _ptr;
        }
    };
    template <class T> T default_value = T{};

    template<class T>
    class Vector {
    private:
        node<T>* _begin;
        node<T>* _end;
        size_t _size;
    public:
        explicit Vector() {
            _begin = nullptr;
            _end = nullptr;
            _size = 0;
        }
        explicit Vector(T data) {
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
        // need rework
        void insert(Iterator<T> iterator, const T& val) {
            node<T>* pointer = *iterator;
            if (pointer == _begin && pointer != _end) {
                node<T>* new_node = new node<T>(val, nullptr, _begin);
                _begin = new_node;
                _size++;
                return;
            }
            if (pointer != _begin && pointer == _end) {
                node<T>* new_node = new node<T>(val, _end, nullptr);
                _end->_right = new_node;
                _end = new_node;
                _size++;
                return;
            }
            if (pointer == _begin && pointer == _end) {
                node<T>* new_node = new node<T>(val, nullptr, _begin);
                _begin->_right = _end;
                _begin = new_node;
                _size++;
                return;
            }
            if (pointer != _begin && pointer != _end) {
                auto tmp = _begin;
                while (tmp != pointer) {
                    if(tmp->_right)
                    tmp = tmp->_right;
                }
                 node<T>* new_node = new node<T>(val, tmp->_left, tmp);
                    (tmp->_left)->_right = new_node;
                    tmp->_left = new_node;
                _size++;
                return;
            }
        }
       Iterator<T> begin() const {
            return Iterator<T>(_begin);
        }
       Iterator<T> end() const {
           return Iterator<T>(_end);
       }
    };
}

int main()
{
    try {
        //
    }
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}