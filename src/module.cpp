//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#include <boost/python/detail/module_base.hpp>
#include <boost/python/detail/module_init.hpp>
#include <boost/python/detail/module_info.hpp>
#include <boost/python/object/function.hpp>
#include <boost/python/object/class.hpp>
#include <boost/python/cast.hpp>

namespace boost { namespace python { namespace detail {

namespace {

object getattr_or_none(object const &obj, const char *name)
{
    if(PyObject_HasAttrString(obj.ptr(), const_cast<char*>(name)))
        return obj.attr(name);
    else
        return object();
}

// Initialise a new sub-module, or return an existing one.
// This will also create any missing parents along the way.
handle<> init_sub_module(const char* name, PyMethodDef *initial_methods, module_info* pmi)
{
    if(name == NULL)
        // just create a dummy module with an empty reference
        return handle<>();
    // initialise various iterators, etc.
    object parent_module(pmi->get_module()), current_module(parent_module);
    std::string s_name(name), b_name;
    if(s_name.size() == 0)
        // use the default module name if it is not supplied
        s_name = pmi->get_module_name();
    std::string::size_type p_pos(0);
    for(int l = 0;;++l) {
        // find the next module name in the 'dotted' name
        std::string::size_type dot_pos = s_name.find('.', p_pos);
        // p_pos is the absolute position, but the length is needed
        if(dot_pos != std::string::npos)
            dot_pos -= p_pos;
        // the current module name being processed, iterating from the parent
        //   to the right hand sub-modules
        b_name = s_name.substr(p_pos, dot_pos);
        if(l == 0) {
            // process the top level parent module name
            if(dot_pos == 0)
                // allow a shortcut module notation so we can do module(".submodule")
                b_name = pmi->get_module_name();
            // check the base name is the correct parent name else assert
            assert(b_name.compare(pmi->get_module_name()) == 0);
            if(!parent_module) {
                // The main parent module does not exist yet, so create it here
                parent_module = object(python::borrowed(Py_InitModule(
                                       const_cast<char*>(b_name.c_str()),
                                       initial_methods)));
                //   and set up the module iterator
                current_module = parent_module;
                // initialise the global parent module so it can be found later
                pmi->set_module(parent_module);
            }
        } else {
            // now processing a sub-module
            // try to find and verify an existing sub-module of the correct name and type
            object existing_sub_module(getattr_or_none(current_module, b_name.c_str()));
            if(existing_sub_module) {
                // An attribute of the same name has been found
                object module_type((python::detail::new_reference)PyObject_Type(parent_module.ptr()));
                // test its type against the parent
                if(!PyObject_IsSubclass(existing_sub_module.ptr(), module_type.ptr()))
                    // not actually a module, so it can't be used
                    existing_sub_module = object();
            }
            // was an existing sub-module found ?
            if(!existing_sub_module) {
                // no, then it is created here
                // build up the full path name up to and including the current sub-module
                std::string full_name(s_name.substr(0, dot_pos));
                // create the module
                existing_sub_module = object(python::borrowed(Py_InitModule(
                                             const_cast<char*>(full_name.c_str()),
                                             initial_methods)));
                // add the sub-module to the attributes of its immediate parent
                current_module.attr(b_name.c_str()) = existing_sub_module;
            }
            // we now have a new current module to iterate
            current_module = existing_sub_module;
        }
        // no more modules ?
        if(dot_pos == std::string::npos)
            break;
        // advance over the dot
        p_pos += dot_pos + 1;
    }
    // return the actual sub-module that was either found or created
    return handle<>(python::borrowed(current_module.ptr()));
}

}

module_base::module_base(const char* name)
    : m_module(init_sub_module(name, initial_methods, get_module_info()))
{
    set_prior_module(m_module);
}

module_base::~module_base()
{
}

void module_base::setattr(const char* name, PyObject* x)
{
    setattr(name, handle<>(x));
}

void module_base::setattr(char const* name, handle<> const& x)
{
    // Use function::add_to_namespace to achieve overloading if
    // appropriate.
    objects::function::add_to_namespace(m_module, name, x);
}

void module_base::add(type_handle const& x)
{
    this->setattr(x->tp_name, x);
}

void module_base::add_class(type_handle const& class_obj)
{
    add_class(class_obj, objects::class_base::
                            get_class_context_object(class_obj.get()->tp_name, class_obj));
}

void module_base::add_class(type_handle const& class_obj, handle<> const& context)
{
    if(context.get()) {
        objects::function::
            add_to_namespace(context, ((PyTypeObject*)class_obj.get())->tp_name, class_obj);
    }
    
    handle<> module_name(
        PyObject_GetAttrString(
            m_module.get(), const_cast<char*>("__name__"))
        );
    
    int status = PyObject_SetAttrString(
        handle<>(class_obj).get(), const_cast<char*>("__module__"), module_name.get());
    
    if (status == -1)
        throw_error_already_set();
}

void module_base::set_module_info(module_info & mi)
{
    get_module_info_ref() = &mi;
}

module_info* module_base::get_module_info()
{
    return get_module_info_ref();
}

module_info*& module_base::get_module_info_ref()
{
    static module_info* pmi = NULL;
    return pmi;
}

void module_base::set_prior_module(handle<> const& m)
{
    get_module_info()->set_prior_module(python::object(m));
}

handle<> module_base::get_prior_module()
{
    return handle<>(python::borrowed(get_module_info()->get_prior_module().ptr()));
}

PyMethodDef module_base::initial_methods[] = { { 0, 0, 0, 0 } };

}}} // namespace boost::python::detail
