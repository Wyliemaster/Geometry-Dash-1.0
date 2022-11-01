#ifndef __DEFINES__
#define __DEFINES__

// creates a default getter/setter method
#define CREATE_GET_SET(MEMBER, CLASS, TYPE, TYPE_PREFIX) \
    inline TYPE CLASS::get##MEMBER() \
    { \
        return m_##TYPE_PREFIX##MEMBER; \
    } \
    \
    inline void CLASS::set##MEMBER(TYPE MEMBER)\
    {\
        m_##TYPE_PREFIX##MEMBER = MEMBER; \
    }


#endif