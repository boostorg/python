#ifndef STR_20020703_HPP
#define STR_20020703_HPP

#include <boost/python/object.hpp>
#include <boost/python/list.hpp>
#include <boost/python/converter/pytype_object_mgr_traits.hpp>

// disable defines in <cctype> provided by some system libraries
#undef isspace
#undef islower
#undef isalpha
#undef isdigit
#undef isalnum
#undef isupper

namespace boost { namespace python {

class BOOST_PYTHON_DECL str : public object
{
 public:
    str(); // new str
    
    str(const char* s); // new str
    explicit str(object_cref other);

    template <class T>
    explicit str(T const& other)
        : object(str::call(object(other)))
    {
    }

    str capitalize() const ;

    str center(object_cref width) const ;

    template <class T>
    str center(T const& width) const
    {
        return this->center(object(width));
    }

    long count(object_cref sub) const;

    template<class T>
    long count(T const& sub) const
    {
        return this->count(object(sub));
    }

    long count(object_cref sub, object_cref start) const;
    
    template<class T1, class T2>
    long count(T1 const& sub,T2 const& start) const
    {
        return this->count(object(sub), object(start));
    }

    long count(object_cref sub, object_cref start, object_cref end) const;

    template<class T1, class T2, class T3>
    long count(T1 const& sub,T2 const& start, T3 const& end) const
    {
        return this->count(object(sub), object(start));
    }

    object decode() const;
    object decode(object_cref encoding) const;

    template<class T>
    object decode(T const& encoding) const
    {
        return this->decode(object(encoding));
    }

    object decode(object_cref encoding, object_cref errors) const;

    template<class T1, class T2>
    object decode(T1 const& encoding, T2 const& errors) const
    {
        return this->decode(object(encoding),object(errors));
    }

    object encode() const;
    object encode(object_cref encoding) const;

    template <class T>
    object encode(T const& encoding) const
    {
        return this->encode(object(encoding));
    }

    object encode(object_cref encoding, object_cref errors) const;

    template <class T1, class T2>
    object encode(T1 const& encoding, T2 const& errors) const
    {
        return this->encode(object(encoding),object(errors));
    }

    bool endswith(object_cref suffix) const;
    
    template <class T>
    bool endswith(T const& suffix) const
    {
        return this->endswith(object(suffix));
    }

    bool endswith(object_cref suffix, object_cref start) const;
    
    template <class T1, class T2>
    bool endswith(T1 const& suffix, T2 const& start) const
    {
        return this->endswith(object(suffix), object(start));
    }

    bool endswith(object_cref suffix, object_cref start, object_cref end) const;
    
    template <class T1, class T2, class T3>
    bool endswith(T1 const& suffix, T2 const& start, T3 const& end) const
    {
        return this->endswith(object(suffix), object(start), object(end));
    }
    
    str expandtabs() const;
    str expandtabs(object_cref tabsize) const;

    template <class T>
    str expandtabs(T const& tabsize) const
    {
        return this->expandtabs(object(tabsize));
    }
    
    long find(object_cref sub) const;

    template <class T>
    long find(T const& sub) const
    {
        return this->find(object(sub));
    }

    long find(object_cref sub, object_cref start) const;

    template <class T1, class T2>
    long find(T1 const& sub, T2 const& start) const
    {
        return this->find(object(sub), object(start));
    }

    long find(object_cref sub, object_cref start, object_cref end) const;

    template <class T1, class T2, class T3>
    long find(T1 const& sub, T2 const& start, T3 const& end) const
    {
        return this->find(object(sub), object(start), object(end));
    }
    
    long index(object_cref sub) const;

    template <class T>
    long index(T const& sub) const
    {
        return this->index(object(sub));
    }
    
    long index(object_cref sub, object_cref start) const;

    template <class T1, class T2>
    long index(T1 const& sub, T2 const& start) const
    {
        return this->index(object(sub), object(start));
    }

    long index(object_cref sub, object_cref start, object_cref end) const;

    template <class T1, class T2, class T3>
    long index(T1 const& sub, T2 const& start, T3 const& end) const
    {
        return this->index(object(sub), object(start), object(end));
    }

    bool isalnum() const;
    bool isalpha() const;
    bool isdigit() const;
    bool islower() const;
    bool isspace() const;
    bool istitle() const;
    bool isupper() const;
    
    str join(object_cref sequence) const;

    template <class T>
    str join(T const& sequence) const
    {
        return this->join(object(sequence));
    }
    
    str ljust(object_cref width) const;

    template <class T>
    str ljust(T const& width) const
    {
        return this->ljust(object(width));
    }

    str lower() const;
    str lstrip() const;

    str replace(object_cref old, object_cref new_) const ;

    template <class T1, class T2>
    str replace(T1 const& old, T2 const& new_) const 
    {
        return this->replace(object(old),object(new_));
    }

    str replace(object_cref old, object_cref new_, object_cref maxsplit) const ;

    template <class T1, class T2, class T3>
    str replace(T1 const& old, T2 const& new_, T3 const& maxsplit) const 
    {
        return this->replace(object(old),object(new_),object(maxsplit));
    }
    
    long rfind(object_cref sub) const;

    template <class T>
    long rfind(T const& sub) const
    {
        return this->rfind(object(sub));
    }

    long rfind(object_cref sub, object_cref start) const;

    template <class T1, class T2>
    long rfind(T1 const& sub, T2 const& start) const
    {
        return this->rfind(object(sub), object(start));
    }
    
    long rfind(object_cref sub, object_cref start, object_cref end) const;

    template <class T1, class T2, class T3>
    long rfind(T1 const& sub, T2 const& start, T3 const& end) const
    {
        return this->rfind(object(sub), object(start), object(end));
    }
    
    long rindex(object_cref sub) const;

    template <class T>
    long rindex(T const& sub) const
    {
        return this->rindex(object(sub));
    }

    long rindex(object_cref sub, object_cref start) const;

    template <class T1, class T2>
    long rindex(T1 const& sub, T2 const& start) const
    {
        return this->rindex(object(sub), object(start));
    }

    long rindex(object_cref sub, object_cref start, object_cref end) const;

    template <class T1, class T2, class T3>
    long rindex(T1 const& sub, T2 const& start, T3 const& end) const
    {
        return this->rindex(object(sub), object(start), object(end));
    }

    str rjust(object_cref width) const;

    template <class T>
    str rjust(T const& width) const
    {
        return this->rjust(object(width));
    }
    
    str rstrip() const;
    
    list split() const; 
    list split(object_cref sep) const;
   
    template <class T>
    list split(T const& sep) const
    {
        return this->split(object(sep));
    }

    list split(object_cref sep, object_cref maxsplit) const; 
    
    template <class T1, class T2>
    list split(T1 const& sep, T2 const& maxsplit) const
    {
        return this->split(object(sep), object(maxsplit));
    }

    list splitlines() const;
    list splitlines(object_cref keepends) const;

    template <class T>
    list splitlines(T const& keepends) const
    {
        return this->splitlines(object(keepends));
    }

    bool startswith(object_cref prefix) const ;

    template <class T>
    bool startswith(T const& prefix) const
    {
        return this->startswith(object(prefix));
    }

    bool startswith(object_cref prefix, object_cref start) const ;

    template <class T1, class T2>
    bool startswidth(T1 const& prefix, T2 const& start) const
    {
        return this->startswidth(object(prefix), object(start));
    }
     
    bool startswith(object_cref prefix, object_cref start, object_cref end) const ;

    template <class T1, class T2, class T3>
    bool startswidth(T1 const& prefix, T2 const& start, T3 const& end) const
    {
        return this->startswidth(object(prefix), object(start), object(end));
    }

    str strip() const ;
    str swapcase() const ;
    str title() const ;
    
    str translate(object_cref table) const;

    template <class T>
    str translate(T const& table) const
    {
        return this->translate(object(table));
    }

    str translate(object_cref table, object_cref deletechars) const;

    template <class T1, class T2>
    str translate(T1 const& table, T2 const& deletechars) const
    {
        return this->translate(object(table), object(deletechars));
    }
    
    str upper() const;

 public: // implementation detail -- for internal use only
    BOOST_PYTHON_FORWARD_OBJECT_CONSTRUCTORS(str)
    
 private:
    static detail::new_reference call(object const&);
};

//
// Converter Specializations
//
namespace converter
{
  template <>
  struct object_manager_traits<str>
      : pytype_object_manager_traits<&PyString_Type,str>
  {
  };
}

}}  // namespace boost::python

#endif // STR_20020703_HPP
