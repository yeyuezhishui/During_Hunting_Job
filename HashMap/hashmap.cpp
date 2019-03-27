#include <iostream>
#include <string>

using namespace std;

/********************************
 * 仿函数定义为模板函数
 * HashFunc的功能是计算key的
 * hash处理后的值
*********************************/
template <class Key>
class HashFunc
{
    public:
    int operator () (const Key & key)
    {
        return key;
    }
};

/*********************************
 * 特化模板函数
 * 方便对string类型的变量进行hash
 *********************************/
template <>
class HashFunc<string>
{
private:
    /* data */
public:
    int operator () (const string & key)
    {
        int hash = 0;
        for(unsigned i = 0; i<key.length(); i++)
        {
            hash = hash << 7 ^ key[i];
        }
        return (hash & 0x7FFFFFFF);
    }
};

/*********************************
 * 特化模板函数
 * 方便对int类型的变量进行hash
 *********************************/
template <>
class HashFunc<int>
{
    public:
    int operator () (const int & key)
    {
        return key;
    }
};

/********************************
 * 仿函数定义为模板函数
 * EqualFunc的功能是比较两个key值
 * 是否相等
*********************************/
template <class Key>
class EqualFunc
{
public:
    bool operator () (const Key & key1, const Key & key2)
    {
        return key1==key2;
    }
};

/*********************************
 * 特化模板函数
 * 方便对string类型的key值进行比较
 *********************************/
template <>
class EqualFunc<string>
{
public:
    bool operator () (const string & key1, const string & key2)
    {
        return !key1.compare(key2);
    }
};

/*********************************
 * 特化模板函数
 * 方便对int类型的key值进行比较
 *********************************/
template <>
class EqualFunc<int>
{
public:
    bool operator () (const int & key1, const int & key2)
    {
        return key1==key2;
    }
};

/*********************************
 * HashNode模板函数
 *********************************/
template<class Key, class Value>
class HashNode
{
public:
    Key _key;
    Value _val;
    HashNode * next;
    HashNode(Key key, Value val)
    {
        this->_key = key;
        this->_val = val;
        this->next = NULL;
    }
    ~HashNode(){}
    HashNode & operator = (const HashNode &node)
    {
        _key = node._key;
        _val = node._val;
        next = node.next;
        return *this;
    }

};

/*********************************
 * HashMap模板函数
 *********************************/
template <class Key, class Value, class HashFunc, class EqualFunc> 
class HashMap
{
private:
    HashFunc hash;
    EqualFunc equal;
    HashNode<Key, Value> **table;
    unsigned int _size;
    Value ValueNULL;
public:
    HashMap(int size);
    ~HashMap();
    bool insert(const Key& key, const Value & val); //插入操作
    bool del(const Key& key);   //删除操作
    Value & operator [](const Key& key);    //高级查找
};

/*********************************
 * HashMap成员函数：
 * 构造函数Hashmap
 *********************************/
template <class Key, class Value, class HashFunc, class EqualFunc>
HashMap<Key, Value, HashFunc, EqualFunc>::HashMap(int size)
{
    this->_size = size;
    hash = HashFunc();
    equal = EqualFunc();
    table = new HashNode<Key, Value> * [size];
    for(int i = 0; i<size; i++)
        table[i] = NULL;
}

/*********************************
 * HashMap成员函数：
 * 析构函数~Hashmap
 *********************************/
template <class Key, class Value, class HashFunc, class EqualFunc>
HashMap<Key, Value, HashFunc, EqualFunc>::~HashMap()
{
    delete[] table;
}

/*********************************
 * HashMap成员函数：
 * 插入函数insert
 *********************************/
template <class Key, class Value, class HashFunc, class EqualFunc>
bool HashMap<Key, Value, HashFunc, EqualFunc>::insert(const Key & key, const Value & val)
{
    unsigned index;
    index = hash(key) % this->_size;
    HashNode<Key, Value> * newnode = new HashNode<Key, Value>(key,val);
    newnode->next = table[index];
    table[index] = newnode;
    return true;
}

/*********************************
 * HashMap成员函数：
 * 删除函数del
 *********************************/
template <class Key, class Value, class HashFunc, class EqualFunc>
bool HashMap<Key, Value, HashFunc, EqualFunc>::del(const Key & key)
{
    unsigned index;
    index = hash(key)%this->_size;
    if(table == NULL)    return false;
    if(equal(table[index]->_key,key))
    {
        HashNode<Key, Value> * temp = table[index];
        table[index] = table[index]->next;
        delete temp;
        return true;
    }
    HashNode<Key, Value> * node = table[index] -> next;
    HashNode<Key, Value> * pre = table[index];
    while(node)
    {
        if(equal(node->_key,key))
        {
            pre->next = node->next;
            delete node;
            return true;
        }
        else
        {
            pre = node;
            node = node->next;
        }
    }
    return false;
}

/*********************************
 * HashMap重载[]运算符实现查找操作
 *********************************/
template <class Key, class Value, class HashFunc, class EqualFunc>
Value & HashMap<Key, Value, HashFunc, EqualFunc>::operator [] (const Key & key)
{
    unsigned index = hash(key)%this->_size;
    HashNode<Key, Value> * node = table[index];
    while(node)
    {
        if(equal(node->_key,key))
        {
            return node->_val;
        }
        node = node->next;
    }
    cout << "the key does not exit" << endl;
    return ValueNULL;
}
