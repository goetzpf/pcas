//
// Operator new does not throw a bad_alloc exception
// when it fails. It simply returns a null pointer.
// This behavior is not in conformance with the 
// ANSI / ISO C++.
// 
#if _MSC_VER > 1000

#include <new>
#include <new.h>

// instruct loader to call this gllobal object 
// constructor before user global object constructors
#pragma warning (disable: 4073)
#pragma init_seg(lib)
#pragma warning (default: 4073)

static int my_new_handler (size_t size)
{
    throw std::bad_alloc();
    return 0;
}

class my_new_handler_obj
{
public:
    my_new_handler_obj()
    {
        //_old_new_mode = _set_new_mode(1); // cause malloc to throw like new
        _old_new_handler = _set_new_handler(my_new_handler);
    }

    ~my_new_handler_obj()
    {
        _set_new_handler(_old_new_handler);
        //_set_new_mode(_old_new_mode);
    }

private:
    _PNH _old_new_handler;
    //int _old_new_mode;
};

static my_new_handler_obj _g_new_handler_obj;

#endif
