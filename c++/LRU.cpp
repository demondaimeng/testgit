#include<iostream>
#include<map>

using namespace std;
class listnode
{
public:
    listnode(int t, int k):val(t),key(k),pre(nullptr),next(nullptr){};
public:
    int val;    
    int key;
    listnode* pre;
    listnode* next;
    
};

class hash_list
{
public:
    hash_list(int capactiy){
        size = capactiy;
        head = nullptr;
        tail = nullptr;
    };
    int get(int key)
    {
        map<int,listnode*>::iterator it = cache.find(key);
        if(it != cache.end())
        {
            listnode* node = it->second;
            remove(node);
            sethead(node);
            return node->val; 
        }
        else
        {
            return -1;
        }
        
    }
    void sethead(listnode* node)
    {
        node -> next = head;
        node -> pre = nullptr;
        
        if(head!= nullptr)
        {
            head -> pre = node; 
        }
        head = node;
        if(tail == nullptr)
        {
            tail = head;
        }
    }

    void set(int key,int value){
        map<int, listnode*>::iterator it = cache.find(key);
        if(it != cache.end())
        {
            listnode* node = it -> second;
            node -> val = value;
            remove(node);
            sethead(node);
            
        }
        else
        {
            listnode* newnode = new listnode(value,key);
            if(cache.size()>=size)
            {
                map<int,listnode*>::iterator it = cache.find(tail->key);
                remove(tail);
                cache.erase(it);
            }
            sethead(newnode);
            cache[key] = newnode;
        }
        

    }

    void remove(listnode* node){
        if(node -> pre != nullptr)
        {
            node -> pre -> next = node -> next;
        }
        else
        {
            head = node ->next;
        }
        if(node -> next !=nullptr)
        {
            node -> next -> pre = node -> pre;
        }
        else
        {
            tail = node ->pre;
        }
        
        
    }



private:
    map<int,listnode*> cache;
    int size;
    listnode* head;
    listnode* tail;
};



int main(int argc, char **argv){
    hash_list* lrucache = new hash_list(2);
    lrucache -> set(2, 1);
    lrucache -> set(1, 1);
    cout << lrucache->get(2) << endl;
    lrucache -> set(4, 1);
    cout << lrucache->get(1) << endl;
    cout << lrucache -> get(2) << endl;
}
