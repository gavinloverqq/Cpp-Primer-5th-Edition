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



#endif //CHAPTER13_MESSAGE_H
