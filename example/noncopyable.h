#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

class store
{
  private:
    store(const store&) { } // Disable the copy constructor.
    int number;
  public:
    store(const int i) : number(i) { }
    int recall() const { return number; }
};

#endif // NONCOPYABLE_H
