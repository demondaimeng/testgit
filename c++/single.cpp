#include <stdio.h> 
#include <mutex>
#include <iostream>
using namespace std;
 // namespace std;
// 饿汉式
// class single_h
// {
// private:
//     single_h(){};
//     static single_h *p;
//     // static mutex _lock;
// public:
//     static single_h* getinstance();
// };

// single_h* single_h::p = new single_h();
// single_h* single_h::getinstance(){
//     return p;
// };

//懒汉式
// class single
// {
// private:
//     single(){};
//     static single* p;
//     static mutex _lock;
// public:
//     static single* getinstance();
//     class cgarbo
//     {
//         public:
//             ~cgarbo()
//             {
//                 if(single::p)
//                 {
//                     delete single::p;
//                 }
//             }
//     };
//     static cgarbo garbo;
// };

// single* single::p = nullptr;

// single* single::getinstance(){
//     if(p==nullptr){

    
//         lock_guard<mutex> guard(_lock);
        
//         if(p==nullptr){
//             p = new single();
//         }
//     }
//     return p;
// }

//懒汉式
class singleton {
private:
    singleton() {}

    static singleton *p;
    static mutex lock_;
public:
    static singleton *instance();

    // 实现一个内嵌垃圾回收类
    class CGarbo
    {
    public:
        ~CGarbo()
        {
            if(singleton::p)
                delete singleton::p;
        }
    };
    static CGarbo Garbo; // 定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数从而释放单例对象
};

singleton *singleton::p = nullptr;
singleton::CGarbo Garbo;
mutex singleton::lock_;

singleton* singleton::instance() {
    if (p == nullptr) {
        lock_guard<mutex> guard(lock_);
        if (p == nullptr)
            p = new singleton();
    }
    return p;
}


int main(void) 
{ 
    
    singleton* x = singleton::instance();
    cout<<x<<endl;
    return 0;
} 