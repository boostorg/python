//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#ifndef ERRORS_DWA052500_H_
# define ERRORS_DWA052500_H_

namespace py {

struct ErrorAlreadySet {};
struct ArgumentError : ErrorAlreadySet {};

// Handles exceptions caught just before returning to Python code.
void handle_exception();

template <class T>
T* expect_non_null(T* x)
{
    if (x == 0)
        throw ErrorAlreadySet();
    return x;
}

} // namespace py

#endif // ERRORS_DWA052500_H_
