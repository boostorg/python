template<typename T>
class A
{
public:
   void set(T v) { mData = v; }

   T get() const { return mData; }

private:
   T mData;
};


class B : public A<int>
{
public:
   int go() { return get(); }
};
