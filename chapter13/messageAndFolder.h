//
// Created by kunwan on 3/17/17.
//

#ifndef CHAPTER13_MESSAGE_H
#define CHAPTER13_MESSAGE_H


#include <string>
#include <set>

class Folder;
class Message{
    friend class Folder;

public:
    explicit Message(const std::string& str = ""):contents(str){}
    Message (const Message& msg){
        contents = msg.contents;
        folders = msg.folders;
        addToFolder(msg);
    }

//    移动构造函数
    Message(Message && m) noexcept: contents(std::move(m.contents)){
        move_Folders(&m);
    }
//    移动赋值运算符
    Message& operator = (Message && rhs){
        if(&rhs != this){
            removeFromFolders();
            contents = std::move(rhs.contents);
            move_Folders(&rhs);
        }
        return *this;
    }

    Message& operator = (const Message& msg){
        removeFromFolders();//并为删除set中folder指针
        this->contents = msg.contents;
        this->folders = msg.folders;
        addToFolder(msg);
        return *this;
    }

    ~Message(){
        removeFromFolders();
    }

    void swap(Message& lhs, Message& rhs);
    void save(Folder& f);
    void remove(Folder& f);
    void addFolder(Folder* f){
        folders.insert(f);
    }
    void rmFolder(Folder* f){
        folders.erase(f);
    }

private:
    std::string contents;
    std::set <Folder*> folders;

    void addToFolder(const Message& m);

    void removeFromFolders();

    void move_Folders(Message *m);
};



class Folder{
public:
    void addMsg(Message* m){
        msg.insert(m);
    }
    void remMsg(Message* m){
        msg.erase(m);
    }

    void addToMsg(const Folder& f){
        for (auto m : f.msg)
            m->addFolder(this);
    }
    void rmFromMsg(){//msg 中 删除当前的folder
        for (auto m : (*this).msg)
            m->rmFolder(this);
    }

    Folder(const Folder& f):msg(f.msg){
        addToMsg(f);
    }

    Folder&operator = (const Folder& f){
        rmFromMsg();
        msg = f.msg;
        addToMsg(f);
        return *this;
    }

    ~Folder(){
        rmFromMsg();
    }

private:
    std::set <Message*> msg;
};

// 下面几个函数必须定义在Folder 类下面，否则发生错误 error：member access into incomplete type 'Folder'
void Message::swap(Message& lhs, Message& rhs){
    using std::swap;
    for (auto f: lhs.folders)
        f->remMsg(&lhs);
    for (auto f: lhs.folders)
        f->remMsg(&rhs);
    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);
    for (auto f: lhs.folders)
        f->addMsg(&lhs);
    for (auto f: lhs.folders)
        f->addMsg(&rhs);
}

void Message::save(Folder& f){
    folders.insert(&f);
    f.addMsg(this);
}

void Message::remove(Folder& f){
    folders.erase(&f);
    f.remMsg(this);
}

void Message::addToFolder(const Message& m){
    for(auto f : m.folders)
        f->addMsg(this);
}

void Message::removeFromFolders(){
    for (auto f : folders) {
        f->remMsg(this);
    }
}

void Message::move_Folders(Message *m){
    folders = std::move(m->folders);
    for (auto f : folders) {
        f->remMsg(m);
        f->addMsg(m);
    }
    m->folders.clear();
}

#endif //CHAPTER13_MESSAGE_H
