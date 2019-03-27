#include <iostream>
#include <string>

using namespace std;


template <class Key>
class HashFunc
{
    public:
    int operator () (const Key & key)
    {
        return key;
    }
};

//模板特化
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

template <>
class HashFunc<int>
{
    public:
    int operator () (const int & key)
    {
        return key;
    }
};


template <class Key>
class EqualFunc
{
public:
    bool operator () (const Key & key1, const Key & key2)
    {
        return key1==key2;
    }
};

template <>
class EqualFunc<string>
{
public:
    bool operator () (const string & key1, const string & key2)
    {
        return !key1.compare(key2);
    }
};


template <>
class EqualFunc<int>
{
public:
    bool operator () (const int & key1, const int & key2)
    {
        return key1==key2;
    }
};


template<class Key, class Value>
class HashNode
{
private:
    /* data */
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

template <class Key, class Value, class HashFunc, class EqualFunc> class HashMap
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

template <class Key, class Value, class HashFunc, class EqualFunc>
HashMap<Key, Value, HashFunc, EqualFunc>::~HashMap()
{
    delete[] table;
}

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
