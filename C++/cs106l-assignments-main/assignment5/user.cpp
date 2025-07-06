#include "user.h"

/**
 * Creates a new User with the given name and no friends.
 */
User::User(const std::string& name)
  : _name(name)
  , _friends(nullptr)
  , _size(0)
  , _capacity(0)
{
}

/**
 * Adds a friend to this User's list of friends.
 * @param name The name of the friend to add.
 */
void
User::add_friend(const std::string& name)
{
  if (_size == _capacity) {
    _capacity = 2 * _capacity + 1;
    std::string* newFriends = new std::string[_capacity];
    for (size_t i = 0; i < _size; ++i) {
      newFriends[i] = _friends[i];
    }
    delete[] _friends;
    _friends = newFriends;
  }

  _friends[_size++] = name;
}

/**
 * Returns the name of this User.
 */
std::string
User::get_name() const
{
  return _name;
}

/**
 * Returns the number of friends this User has.
 */
size_t
User::size() const
{
  return _size;
}

/**
 * Sets the friend at the given index to the given name.
 * @param index The index of the friend to set.
 * @param name The name to set the friend to.
 */
void User::set_friend(size_t index, const std::string& name)
{
  _friends[index] = name;
}

std::ostream& operator << (std::ostream& out, const User& user){
  out << "User(name=" <<user.get_name()<<", "<<"friends=[";
  std::string* str = user._friends;
  for (size_t i = 0; i < user._size; i++)
  {
    if(i != user._size - 1){
      out << *str <<", ";
    }else{
      out << *str;
    }
    ++str;
  }
  out << "])";
  return out;
}

User::~User(){
  delete[] this->_friends;// 删除数组必须带方括号
}

// 避免只拷贝指针导致的指向同一块内存
User::User(const User& user) 
: _name(user._name),_capacity(user._capacity),_size(user._size){
  // 不能在成员初始化列表中写_friends(new std::string[_capacity]),此时_capacity没有值
  //当初始化_friends时，它使用了_capacity的值。但根据C++标准，成员变量的初始化顺序只取决于类定义中的声明顺序，而不是初始化列表中的顺序。
  this->_friends = new std::string[this->_capacity];
  for (size_t i = 0; i < this->_size; i++)
  {
    this->_friends[i] = user._friends[i];
  }
}

User& User::operator = (const User& user){
  this->_name = user._name;
  this->_size = user._size;
  this->_capacity = user._capacity;
  delete[] this->_friends;// 不加这个旧的指针会内存泄漏
  this->_friends = new std::string[_capacity];
    for (size_t i = 0; i < this->_size; i++)
  {
    this->_friends[i] = user._friends[i];
  }
  
  return *this;
}

User& User::operator+=(User& rhs) {
  if(this->_size<=_capacity){
    this->add_friend(rhs.get_name());
  }
  if(rhs._size<=rhs._capacity){
    rhs.add_friend(this->get_name());
  }
  return *this;
}

bool User::operator<(const User& rhs) const{
  return this->_name < rhs._name;
}