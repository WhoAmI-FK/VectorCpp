
#include <iostream>

namespace whoami_vector {
    template<class T>
    struct node {
        T _data;
        node* _left;
        node* _right;
        static size_t _elements;
        size_t tmp;
        node<T>(T data, node* l = nullptr, node* r = nullptr) {
            _data = data;
            _left = l;
            _right = r;
            _elements++;
            tmp = 0;
        }
    };
    template<class T>
    size_t node<T>::_elements = 0;

    template<class T>
    class ReverseIterator {
    private:
        node<T>* _ptr;
    public:
        explicit ReverseIterator() : _ptr(nullptr) {

        }
        explicit ReverseIterator(node<T>* ptr) : _ptr(ptr) {

        }
        ReverseIterator& operator++() {
            if (_ptr->_left != nullptr) _ptr = _ptr->_left;
            return *this;
        }
        ReverseIterator& operator++(int) {
            if (_ptr->_left != nullptr) {
                ReverseIterator<T> tmp(*this);
                ++*this;
                return tmp;
            }
        }
        ReverseIterator& operator+(size_t num) {

            for (int i = 0; i < num; ++i) {
                if (_ptr->_left != nullptr) {
                    _ptr = _ptr->_left;
                }
                else break;
            }
         //   this->_ptr->tmp = num;
            return *this;
        }
        ReverseIterator& operator-(int num) {
            for (int i = 0; i < num; ++i) {
                if (_ptr->_right != nullptr) {
                    _ptr = _ptr->_right;
                }
                else break;
            }
            //this->_ptr->tmp = this->_ptr->_elements - num;
            return *this;
        }
        node<T>* operator*() {
            return _ptr;
        }
    };

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
        Iterator& operator+(size_t num) {
    
                for (int i = 0; i < num; ++i) {
                    if (_ptr->_right != nullptr) {
                        _ptr = _ptr->_right;
                    }
                    else break;
                }
                this->_ptr->tmp = num;
            return *this;
        }
        Iterator& operator-(int num) {
            for (int i = 0; i < num; ++i) {
                if (_ptr->_left != nullptr) {
                    _ptr = _ptr->_left;
                }
                else break;
            }
            this->_ptr->tmp = this->_ptr->_elements - num;
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
        void resetBegin() {
            if (_begin != nullptr) {
                while (_begin->_left != nullptr) {
                    _begin = _begin->_left;
                }
            }
        }
        void resetEnd() {
            if (_end != nullptr) {
                while (_end->_right != nullptr) {
                    _end = _end->_right;
                }
            }
        }
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
        /*
        void insert(Iterator<T> iterator, const T& val) {
            node<T>* pointer = *iterator;
            if((pointer->tmp+1)==(pointer->_elements)){
                node<T>* new_node = new node<T>(val, pointer->_left, pointer);
                (pointer->_left)->_right = new_node;
                pointer->_left = new_node;
                _size++;
                return;
            }
            else {
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
                        if (tmp->_right)
                            tmp = tmp->_right;
                    }
                    node<T>* new_node = new node<T>(val, tmp->_left, tmp);
                    (tmp->_left)->_right = new_node;
                    tmp->_left = new_node;
                    _size++;
                    return;
                }
            }
        }
        void insert2(Iterator<T> iterator, const T& val) {
            node<T>* pointer = *iterator;
            if (pointer == _end) {
                node<T>* new_node = new node<T>(val, _end, nullptr);
                _end->_right = new_node;
                resetBegin();
                resetEnd();
                _size++;
                return;
            }
            else if (pointer == _begin) {
                node<T>* new_node = new node<T>(val, nullptr, _begin);
                _begin->_left = new_node;
                resetBegin();
                resetEnd();
                _size++;
                return;
            }
            else {
                node<T>* new_node = new node<T>(val, pointer, pointer->_right);
                pointer->_right = new_node;
                _size++;
                return;
            }
           
        }
        */
       Iterator<T> begin() const {
            return Iterator<T>(_begin);
        }
       Iterator<T> end() const {
           return Iterator<T>(_end);
       }
       ReverseIterator<T> rbegin() {
           return ReverseIterator<T>(_end);
       }
       ReverseIterator<T> rend() {
           return ReverseIterator<T>(_begin->_left);
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