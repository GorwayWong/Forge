#pragma once

#include <cstddef>
#include <utility>

namespace cs106l {

/**
 * @brief A smart pointer that owns an object and deletes it when it goes out of scope.
 * @tparam T The type of the object to manage.
 * @note This class is a simpler version of `std::unique_ptr`.
 */
template <typename T> class unique_ptr {
private:
  /* STUDENT TODO: What data must a unique_ptr keep track of? */
  T* pointerT;

public:
  /**
   * @brief Constructs a new `unique_ptr` from the given pointer.
   * @param ptr The pointer to manage.
   * @note You should avoid using this constructor directly and instead use `make_unique()`.
   */
  unique_ptr(T* ptr) {
    /* STUDENT TODO: Implement the constructor */
    this->pointerT = ptr;
    // throw std::runtime_error("Not implemented: unique_ptr(T* ptr)");
  }

  /**
   * @brief Constructs a new `unique_ptr` from `nullptr`.
   */
  unique_ptr(std::nullptr_t) {
    /* STUDENT TODO: Implement the nullptr constructor */
    this->pointerT = nullptr;
    // throw std::runtime_error("Not implemented: unique_ptr(std::nullptr_t)");
  }

  /**
   * @brief Constructs an empty `unique_ptr`.
   * @note By default, a `unique_ptr` points to `nullptr`.
   */
  unique_ptr() : unique_ptr(nullptr) {}

  /**
   * @brief Dereferences a `unique_ptr` and returns a reference to the object.
   * @return A reference to the object.
   */
  T& operator*() {
    /* STUDENT TODO: Implement the dereference operator */
    // 如果 pointerT 是 T* 类型（指针），则 *pointerT 就是对指针解引用，得到的是 T&（即 T 的引用），不是单纯的 T 类型！
    return *(this->pointerT);
    // throw std::runtime_error("Not implemented: operator*()");
  }

  /**
   * @brief Dereferences a `unique_ptr` and returns a const reference to the object.
   * @return A const reference to the object.
   */
  const T& operator*() const {
    /* STUDENT TODO: Implement the dereference operator (const) */
    // 解引用返回的T& 可以隐式转为 const T&
    return *(this->pointerT);
    // throw std::runtime_error("Not implemented: operator*() const");
  }

  /**
   * @brief Returns a pointer to the object managed by the `unique_ptr`.
   * @note This allows for accessing the members of the managed object through the `->` operator.
   * @return A pointer to the object.
   */
  T* operator->() {
    /* STUDENT TODO: Implement the arrow operator */
    return this->pointerT;
    // throw std::runtime_error("Not implemented: operator->()");
  }

  /**
   * @brief Returns a const pointer to the object managed by the `unique_ptr`.
   * @note This allows for accessing the members of the managed object through the `->` operator.
   * @return A const pointer to the object.
   */
  const T* operator->() const {
    /* STUDENT TODO: Implement the arrow operator */
    return this->pointerT;
    // throw std::runtime_error("Not implemented: operator->() const");
  }

  /**
   * @brief Returns whether or not the `unique_ptr` is non-null.
   * @note This allows us to use a `unique_ptr` inside an if-statement.
   * @return `true` if the `unique_ptr` is non-null, `false` otherwise.
   */
  operator bool() const {
    /* STUDENT TODO: Implement the boolean conversion operator */
    if (this->pointerT != nullptr){
      return true;
    }else{
      return false;
    }
    // throw std::runtime_error("Not implemented: operator bool() const");
  }

  /** STUDENT TODO: In the space below, do the following:
   * - Implement a destructor
   * - Delete the copy constructor
   * - Delete the copy assignment operator
   * - Implement the move constructor
   * - Implement the move assignment operator
   */
  ~unique_ptr(){
    delete this->pointerT;// 专门管理外部分配的动态资源，其他普通类的析构函数只释放自己拥有的资源，不会释放外部资源。unique_ptr不一样
  }
  unique_ptr(const unique_ptr& other) = delete;
  unique_ptr& operator=(const unique_ptr& other) = delete;
  unique_ptr(unique_ptr&& other){// 应该接受非const的右值引用
    // delete this->pointerT; // 移动构造中，此时this->pointerT还没有资源，直接调用delete会报错
    this->pointerT = other.pointerT;
    // delete other.pointerT; // 不能delete掉，移动语义的目的是高效地转移资源的所有权，而不是复制或销毁资源。
    other.pointerT = nullptr;
    // 将 other 的资源“偷”过来，并确保 other 处于有效但空的状态（通常是 nullptr）。
  }
  unique_ptr& operator=(unique_ptr&& other){
    if (this == &other){// this是指针类型，other是引用类型，不能直接比较
      return *this;
    }
    delete this->pointerT;
    this->pointerT = other.pointerT;
    // delete other.pointerT; // 不能delete掉，移动语义的目的是高效地转移资源的所有权，而不是复制或销毁资源。
    // 先释放当前资源（如果有），然后“偷” other 的资源，并确保 other 处于空状态。
    other.pointerT = nullptr;
    return *this;// 应该返回*this，this是指针，*this是解引用的对象
  }
  /*
  在模板类的成员函数实现中，当你在类内部定义成员函数时，不需要在类名后面加 <T>。因为此时你已经在类的模板作用域内，编译器知道 unique_ptr 是一个模板类。
  但是，当你在类外部定义成员函数时（即分离声明和实现），就需要写成 template <typename T> unique_ptr<T>::~unique_ptr() 这样的形式。
 */
};

/**
 * @brief Creates a new unique_ptr for a type with the given arguments.
 * @example auto ptr = make_unique<int>(5);
 * @tparam T The type to create a unique_ptr for.
 * @tparam Args The types of the arguments to pass to the constructor of T.
 * @param args The arguments to pass to the constructor of T.
 */
template <typename T, typename... Args> 
unique_ptr<T> make_unique(Args&&... args) {
  return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

}