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

class str : public object
{
 public:
    BOOST_PYTHON_DECL str(); // new str
    
    BOOST_PYTHON_DECL str(const char* s); // new str
    explicit BOOST_PYTHON_DECL str(object_cref other);

    template <class T>
    explicit str(T const& other)
        : object(str::call(object(other)))
    {
    }

    BOOST_PYTHON_DECL str capitalize() const ;

    BOOST_PYTHON_DECL str center(object_cref width) const ;

    template <class T>
    str center(T const& width) const
    {
        return this->center(object(width));
    }

    BOOST_PYTHON_DECL long count(object_cref sub) const;

    template<class T>
    long count(T const& sub) const
    {
        return this->count(object(sub));
    }

    BOOST_PYTHON_DECL long count(object_cref sub, object_cref start) const;
    
    template<class T1, class T2>
    long count(T1 const& sub,T2 const& start) const
    {
        return this->count(object(sub), object(start));
    }

    BOOST_PYTHON_DECL long count(object_cref sub, object_cref start, object_cref end) const;

    template<class T1, class T2, class T3>
    long count(T1 const& sub,T2 const& start, T3 const& end) const
    {
        return this->count(object(sub), object(start));
    }

    BOOST_PYTHON_DECL object decode() const;
    BOOST_PYTHON_DECL object decode(object_cref encoding) const;

    template<class T>
    object decode(T const& encoding) const
    {
        return this->decode(object(encoding));
    }

    BOOST_PYTHON_DECL object decode(object_cref encoding, object_cref errors) const;

    template<class T1, class T2>
    object decode(T1 const& encoding, T2 const& errors) const
    {
        return this->decode(object(encoding),object(errors));
    }

    BOOST_PYTHON_DECL object encode() const;
    BOOST_PYTHON_DECL object encode(object_cref encoding) const;

    template <class T>
    object encode(T const& encoding) const
    {
        return this->encode(object(encoding));
    }

    BOOST_PYTHON_DECL object encode(object_cref encoding, object_cref errors) const;

    template <class T1, class T2>
    object encode(T1 const& encoding, T2 const& errors) const
    {
        return this->encode(object(encoding),object(errors));
    }

    BOOST_PYTHON_DECL bool endswith(object_cref suffix) const;
    
    template <class T>
    bool endswith(T const& suffix) const
    {
        return this->endswith(object(suffix));
    }

    BOOST_PYTHON_DECL bool endswith(object_cref suffix, object_cref start) const;
    
    template <class T1, class T2>
    bool endswith(T1 const& suffix, T2 const& start) const
    {
        return this->endswith(object(suffix), object(start));
    }

    BOOST_PYTHON_DECL bool endswith(object_cref suffix, object_cref start, object_cref end) const;
    
    template <class T1, class T2, class T3>
    bool endswith(T1 const& suffix, T2 const& start, T3 const& end) const
    {
        return this->endswith(object(suffix), object(start), object(end));
    }
    
    BOOST_PYTHON_DECL str expandtabs() const;
    BOOST_PYTHON_DECL str expandtabs(object_cref tabsize) const;

    template <class T>
    str expandtabs(T const& tabsize) const
    {
        return this->expandtabs(object(tabsize));
    }
    
    BOOST_PYTHON_DECL long find(object_cref sub) const;

    template <class T>
    long find(T const& sub) const
    {
        return this->find(object(sub));
    }

    BOOST_PYTHON_DECL long find(object_cref sub, object_cref start) const;

    template <class T1, class T2>
    long find(T1 const& sub, T2 const& start) const
    {
        return this->find(object(sub), object(start));
    }

    BOOST_PYTHON_DECL long find(object_cref sub, object_cref start, object_cref end) const;

    template <class T1, class T2, class T3>
    long find(T1 const& sub, T2 const& start, T3 const& end) const
    {
        return this->find(object(sub), object(start), object(end));
    }
    
    BOOST_PYTHON_DECL long index(object_cref sub) const;

    template <class T>
    long index(T const& sub) const
    {
        return this->index(object(sub));
    }
    
    BOOST_PYTHON_DECL long index(object_cref sub, object_cref start) const;

    template <class T1, class T2>
    long index(T1 const& sub, T2 const& start) const
    {
        return this->index(object(sub), object(start));
    }

    BOOST_PYTHON_DECL long index(object_cref sub, object_cref start, object_cref end) const;

    template <class T1, class T2, class T3>
    long index(T1 const& sub, T2 const& start, T3 const& end) const
    {
        return this->index(object(sub), object(start), object(end));
    }

    BOOST_PYTHON_DECL bool isalnum() const;
    BOOST_PYTHON_DECL bool isalpha() const;
    BOOST_PYTHON_DECL bool isdigit() const;
    BOOST_PYTHON_DECL bool islower() const;
    BOOST_PYTHON_DECL bool isspace() const;
    BOOST_PYTHON_DECL bool istitle() const;
    BOOST_PYTHON_DECL bool isupper() const;
    
    BOOST_PYTHON_DECL str join(object_cref sequence) const;

    template <class T>
    str join(T const& sequence) const
    {
        return this->join(object(sequence));
    }
    
    BOOST_PYTHON_DECL str ljust(object_cref width) const;

    template <class T>
    str ljust(T const& width) const
    {
        return this->ljust(object(width));
    }

    BOOST_PYTHON_DECL str lower() const;
    BOOST_PYTHON_DECL str lstrip() const;

    BOOST_PYTHON_DECL str replace(object_cref old, object_cref new_) const ;

    template <class T1, class T2>
    str replace(T1 const& old, T2 const& new_) const 
    {
        return this->replace(object(old),object(new_));
    }

    BOOST_PYTHON_DECL str replace(object_cref old, object_cref new_, object_cref maxsplit) const ;

    template <class T1, class T2, class T3>
    str replace(T1 const& old, T2 const& new_, T3 const& maxsplit) const 
    {
        return this->replace(object(old),object(new_),object(maxsplit));
    }
    
    BOOST_PYTHON_DECL long rfind(object_cref sub) const;

    template <class T>
    long rfind(T const& sub) const
    {
        return this->rfind(object(sub));
    }

    BOOST_PYTHON_DECL long rfind(object_cref sub, object_cref start) const;

    template <class T1, class T2>
    long rfind(T1 const& sub, T2 const& start) const
    {
        return this->rfind(object(sub), object(start));
    }
    
    BOOST_PYTHON_DECL long rfind(object_cref sub, object_cref start, object_cref end) const;

    template <class T1, class T2, class T3>
    long rfind(T1 const& sub, T2 const& start, T3 const& end) const
    {
        return this->rfind(object(sub), object(start), object(end));
    }
    
    BOOST_PYTHON_DECL long rindex(object_cref sub) const;

    template <class T>
    long rindex(T const& sub) const
    {
        return this->rindex(object(sub));
    }

    BOOST_PYTHON_DECL long rindex(object_cref sub, object_cref start) const;

    template <class T1, class T2>
    long rindex(T1 const& sub, T2 const& start) const
    {
        return this->rindex(object(sub), object(start));
    }

    BOOST_PYTHON_DECL long rindex(object_cref sub, object_cref start, object_cref end) const;

    template <class T1, class T2, class T3>
    long rindex(T1 const& sub, T2 const& start, T3 const& end) const
    {
        return this->rindex(object(sub), object(start), object(end));
    }

    BOOST_PYTHON_DECL str rjust(object_cref width) const;

    template <class T>
    str rjust(T const& width) const
    {
        return this->rjust(object(width));
    }
    
    BOOST_PYTHON_DECL str rstrip() const;
    
    BOOST_PYTHON_DECL list split() const; 
    BOOST_PYTHON_DECL list split(object_cref sep) const;
   
    template <class T>
    list split(T const& sep) const
    {
        return this->split(object(sep));
    }

    BOOST_PYTHON_DECL list split(object_cref sep, object_cref maxsplit) const; 
    
    template <class T1, class T2>
    list split(T1 const& sep, T2 const& maxsplit) const
    {
        return this->split(object(sep), object(maxsplit));
    }

    BOOST_PYTHON_DECL list splitlines() const;
    BOOST_PYTHON_DECL list splitlines(object_cref keepends) const;

    template <class T>
    list splitlines(T const& keepends) const
    {
        return this->splitlines(object(keepends));
    }

    BOOST_PYTHON_DECL bool startswith(object_cref prefix) const ;

    template <class T>
    bool startswith(T const& prefix) const
    {
        return this->startswith(object(prefix));
    }

    BOOST_PYTHON_DECL bool startswith(object_cref prefix, object_cref start) const ;

    template <class T1, class T2>
    bool startswidth(T1 const& prefix, T2 const& start) const
    {
        return this->startswidth(object(prefix), object(start));
    }
     
    BOOST_PYTHON_DECL bool startswith(object_cref prefix, object_cref start, object_cref end) const ;

    template <class T1, class T2, class T3>
    bool startswidth(T1 const& prefix, T2 const& start, T3 const& end) const
    {
        return this->startswidth(object(prefix), object(start), object(end));
    }

    BOOST_PYTHON_DECL str strip() const ;
    BOOST_PYTHON_DECL str swapcase() const ;
    BOOST_PYTHON_DECL str title() const ;
    
    BOOST_PYTHON_DECL str translate(object_cref table) const;

    template <class T>
    str translate(T const& table) const
    {
        return this->translate(object(table));
    }

    BOOST_PYTHON_DECL str translate(object_cref table, object_cref deletechars) const;

    template <class T1, class T2>
    str translate(T1 const& table, T2 const& deletechars) const
    {
        return this->translate(object(table), object(deletechars));
    }
    
    BOOST_PYTHON_DECL str upper() const;

 public: // implementation detail -- for internal use only
    BOOST_PYTHON_FORWARD_OBJECT_CONSTRUCTORS(str)
    
 private:
    static BOOST_PYTHON_DECL detail::new_reference call(object const&);
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
