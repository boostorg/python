#ifndef DICT_20020706_HPP
#define DICT_20020706_HPP

#include <boost/python/object.hpp>
#include <boost/python/list.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/converter/pytype_object_mgr_traits.hpp>

namespace boost { namespace python {

class dict : public object
{
    public:
    // dict() -> new empty dictionary.
    // dict(mapping) -> new dictionary initialized from a mapping object's
    //     (key, value) pairs.
    // dict(seq) -> new dictionary initialized as if via:
    BOOST_PYTHON_DECL dict();   // new dict
    explicit BOOST_PYTHON_DECL dict(object_cref data);

    template <class T>
    explicit dict(T const& data)
        : object(dict::call(object(data)))
    {
    }

    // D.clear() -> None.  Remove all items from D.
    BOOST_PYTHON_DECL void clear();

    // D.copy() -> a shallow copy of D
    BOOST_PYTHON_DECL dict copy();

    // D.get(k[,d]) -> D[k] if D.has_key(k), else d.  d defaults to None.
    BOOST_PYTHON_DECL object get(object_cref k) const;
    
    template<class T>
    object get(T const& k) const 
    {
        return this->get(object(k));
    }
    
    BOOST_PYTHON_DECL object get(object_cref k, object_cref d) const;

    template<class T1, class T2>
    object get(T1 const& k, T2 const& d) const 
    {
        return this->get(object(k),object(d));
    }

    // D.has_key(k) -> 1 if D has a key k, else 0
    BOOST_PYTHON_DECL bool has_key(object_cref k) const;

    template<class T>
    bool has_key(T const& k) const
    {
        return this->has_key(object(k));
    }

    // D.items() -> list of D's (key, value) pairs, as 2-tuples
    BOOST_PYTHON_DECL list items() const;
 
    // D.iteritems() -> an iterator over the (key, value) items of D
    BOOST_PYTHON_DECL object iteritems() const;

    // D.iterkeys() -> an iterator over the keys of D
    BOOST_PYTHON_DECL object iterkeys() const;

    // D.itervalues() -> an iterator over the values of D
    BOOST_PYTHON_DECL object itervalues() const;
 
    // D.keys() -> list of D's keys
    BOOST_PYTHON_DECL list keys() const;
 
    // D.popitem() -> (k, v), remove and return some (key, value) pair as a
    // 2-tuple; but raise KeyError if D is empty
    BOOST_PYTHON_DECL tuple popitem();

    // D.setdefault(k[,d]) -> D.get(k,d), also set D[k]=d if not D.has_key(k)
    BOOST_PYTHON_DECL object setdefault(object_cref k);

    template<class T>
    object setdefault(T const& k)
    {
        return this->setdefault(object(k));
    }

    BOOST_PYTHON_DECL object setdefault(object_cref k, object_cref d);

    template<class T1, class T2>
    object setdefault(T1 const& k, T2 const& d)
    {
        return this->setdefault(object(k),object(d));
    }

    // D.update(E) -> None.  Update D from E: for k in E.keys(): D[k] = E[k]
    BOOST_PYTHON_DECL void update(object_cref E);

    template<class T>
    void update(T const& E)
    {
        this->update(object(E));
    }

    // D.values() -> list of D's values
    BOOST_PYTHON_DECL list values() const;

 public: // implementation detail -- for internal use only
    BOOST_PYTHON_FORWARD_OBJECT_CONSTRUCTORS(dict, object)
    
 private:
    static BOOST_PYTHON_DECL detail::new_reference call(object const&);
};


//
// Converter Specializations
//
namespace converter
{
  template <>
  struct object_manager_traits<dict>
      : pytype_object_manager_traits<&PyDict_Type,dict>
  {
  };
}

}}   // namespace boost::python

#endif

