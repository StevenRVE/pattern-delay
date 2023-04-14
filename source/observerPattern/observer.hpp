//
// Created by Steven on 5/17/2021.
//

#ifndef _H_OBSERVER_
#define _H_OBSERVER_

// classes
class Subject;

// libs
#include <array>

class Observer
{
public:
    virtual ~Observer() = default;

    virtual void update(Subject&) = 0;

protected:

};

#endif // _H_OBSERVER_
