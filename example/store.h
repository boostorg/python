#ifndef STORE_H
#define STORE_H

class store
{
  private:
    store(const store&) { } // Disable the copy constructor.
    int number;
  public:
    store(const int i) : number(i) { }
    int recall() const { return number; }
};

#endif // STORE_H
