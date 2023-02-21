# C++ pointer passing pitfalls

These examples show five ways you can incorrectly pass a pointer to a wrapped class, as well as two correct ways.

You can build and run valgrind on all by doing
```
make valgrind
```

## The bad ways

### 1-3. `bad_weak_ptr` errors from improper use of `shared_from_this()`
```
terminate called after throwing an instance of 'std::bad_weak_ptr'
  what():  bad_weak_ptr
```
`shared_from_this()` can only be called on an object that is _already being managed by a shared pointer_. There are a couple of ways to run afoul of this prerequisite.

### 4. double free from bad multiple ownership
```
double free or corruption (out)
[1]    646944 abort (core dumped)  ./bin/double-free.cpp.out
```
Thinking you can get around the restrictions imposed by `shared_from_this`, you might try to just construct a new owning, smart pointer from the raw pointer `this`. However, this makes multiple owners that don't communicate, and they both try to free when going out of scope, which results in a double free.

### 5. memory leak from `shared_from_this()` reference cycle
By passing a `std::shared_ptr` into the wrapped class, it increments the reference counter, but when the wrapper class goes out of scope, it doesn't call the destructor because there is an extra reference count that will be decremented. This code runs to completion, but leaks memory.

## The good ways

### 6. Using a non-owning raw pointer
By passing a raw pointer to the wrapped class, it doesn't do any reference count incrementing, and the wrapped class doesn't try to do a free when it is done. It is purely referential. However, you have to beware not to do `delete` it!

### 7. Using a `std::weak_ptr`
If the wrapper class is being owned by a `std::shared_ptr`, then you can give a `std::weak_ptr` to the wrapped class with `weak_from_this()`. This lets the wrapped class only increment the reference count when it actually needs to use it, rather than holding onto a reference forever like in #5.

### 8. Using a reference
This is similar to using a raw pointer, but this requires that the reference variable be initialized in the constructor, rather than deferred in an init method.

### 9. Workaround for 5. when shared_ptr is required (additional wrapper)
If you have a class interface that requires receiving a shared pointer, if you can refactor other classes to make that shared ptr not own the inside class that requires the shared pointer.