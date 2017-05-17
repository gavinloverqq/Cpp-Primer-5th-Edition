//
// Created by kunwan on 3/17/17.
//

#ifndef CHAPTER13_STRVEC_H
#define CHAPTER13_STRVEC_H

#include <memory>
#include <string>
#include <utility>


class StrVec{
public:
    StrVec():elements(nullptr),first_free(nullptr),cap(nullptr){}
    StrVec(const StrVec&);

//    移动构造函数
    StrVec(StrVec &&s) noexcept
        :elements(s.elements), first_free(s.first_free), cap(s.cap){
        s.elements = s.first_free = s.cap = nullptr;
    }

    StrVec& operator =(const StrVec&);

//    移动赋值运算符
    StrVec& operator = (StrVec &&rhs) noexcept{
        if(this != &rhs){//检测自赋值问题
            free();
            elements = rhs.elements;
            first_free = rhs.first_free;
            cap = rhs.cap;
            rhs.elements = rhs.cap = rhs.first_free = nullptr;
        }
        return *this;
    }

    ~StrVec();

    void push_back(const std::string&);
    size_t size() const { return first_free - elements;}
    size_t capacity()const { return cap - first_free;}
    std::string* begin() const { return elements;}
    std::string* end() const { return first_free;}


private:
    static std::allocator<std::string> alloc;
    void chk_n_alloc(){
        if(size() == capacity())
            reallocate();
    }

    std::pair<std::string*, std::string* >alloc_N_copy
            (const std::string*, const std::string*);

    void free();
    void reallocate();
    std::string* elements;
    std::string* first_free;
    std::string* cap;
};

void StrVec::push_back(const std::string& s) {
    chk_n_alloc();
    alloc.construct(first_free++,s);
}

std::pair<std::string*, std::string* > StrVec::alloc_N_copy
        (const std::string* b, const std::string* e){
    auto data = alloc.allocate(e - b);
    return {data, uninitialized_copy(b, e, data)};
}

void StrVec::free(){
    if(elements){
        for(auto p = first_free; p != elements; /*null*/){
            alloc.destroy(--p);
        }
        alloc.deallocate(elements,cap - elements);
    }
}

StrVec::StrVec(const StrVec& s) {
    auto newdata = alloc_N_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::~StrVec() {
    free();
}

StrVec& StrVec::operator= (const StrVec& s) {
    auto data = alloc_N_copy(s.begin(), s.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

void StrVec::reallocate() {
    auto newcapacity = size() ? 2 * size() : 1;
    auto newdata = alloc.allocate(newcapacity);

    auto dest = newdata;
    auto elem = elements;

    for (size_t i = 0; i != size(); ++i) {
        alloc.construct(dest++, std::move(*elem++));
    }
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}

#endif //CHAPTER13_STRVEC_H
