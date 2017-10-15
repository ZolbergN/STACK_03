#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <stdexcept>
#include <algorithm>
using namespace std;

template <typename T>
class Stack
{
    size_t array_size_; // размер массива
    size_t count_ = 0; // сколько элементов в стеке
    T* array_; // указатель на первый элемент
public:
    Stack() :   array_size_{100},
                array_{new T[array_size_]} {}
    
    Stack(size_t n) :   array_size_{n},
                        array_{new T[n]} {}
    
    // копирования
    Stack(const Stack& S) :   array_size_{S.array_size_},
                        count_{S.count_},
                        array_ {new T[array_size_]}
    {
        copy(S.array_, S.array_ + array_size_, array_);
    }
    
    // перемещения
    Stack(Stack&& S) :  array_size_{S.array_size_},
                        count_{S.count_},
                        array_{S.array_}
    {
        S.array_ = nullptr;
        S.array_size_ = 0;
        S.count_ = 0;
    }
    
    Stack(size_t size_, size_t count_, T* arr) :    array_size_{size_ },
                                                    count_{ count_ },
                                                    array_{arr} {}
    
    size_t count() const noexcept{ // так как метод только возвращает количество элементов в стеке, а не изменяет его поля, делаем его const
        return count_;
    }
    
    void push(T const &value) noexcept{ // принимает константный параметр, чтобы случайно не изменить значение переменной по ссылке
        reinitializeMemory();
        array_[count_] = value;
        ++count_;
    }
    
    void reinitializeMemory() noexcept{
        // c точки зрения логики блок if должен находиться в push, но так как данная функция сделана для того, чтобы избавиться от большой вложенности, я помещаю ее сюда
        if (count_ == array_size_){
            T* new_array_ = new T[2*array_size_]; // перераспределение памяти (выделение новой)
            for (size_t i = 0; i != array_size_; ++i){
                new_array_[i] = array_[i]; // перезапись из старого массива в новый
            }
            delete[] array_; // удаление старого массива
            array_ = new_array_; // теперь указатель указывает на новый массив
        }
    }
    // удалить верхний элемент
    void pop() noexcept{
        if (count_ == 0){
            throw runtime_error( "Ошибка при удалении элемента: стек пуст" );
        }
        --count_;
    }
    //только показать верхний элемент, без его удаления
    T top() noexcept{
        if (count_ == 0){
            throw runtime_error( "Cтек пуст" );
        }
        T c = count_ - 1;
        return array_[c];
    }
    
    bool empty() noexcept{
        return count_ == 0; // if stack has 0 elements, return true. Else more - false.
    }
    
    void swap(Stack& S){
        swap(this->array_size_, S.array_size_);
        swap(this->count_, S.count_);
        swap(this->array_, S.array_);
    }
    
    Stack operator =(const Stack& S){
        if(this != &S){
            Stack{ S }.swap(*this);
        }
        return *this;
    }
    
    Stack operator =(Stack&& S){
        if(this != &S){
            Stack{ std::move(S) }.swap(*this);
        }
        return *this;
    }
    
    friend auto operator<<(ostream& out, const Stack& S) -> ostream& {
        if (S.array_ == nullptr) {
            out << "Стек пуст";
        } else {
            out << "{";
            for (size_t i = 0; i < S.count_; ++i) {
                out <<  " " <<  S.array_[i];
            }
            out << " " << "}";
        }
        return out;
    }
    
    ~Stack<T>(){
        delete[] array_; //освобождение памяти
    }
};

#endif /* STACK_HPP */
