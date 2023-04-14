//
// Created by Steven on 5/17/2021.
//

#ifndef _H_SUBJECT_
#define _H_SUBJECT_

// classes
#include "observer.hpp"

// libs
#include <vector>

// subject
class Subject
{
public:
    virtual ~Subject() = default;

    void attach(Observer& observer);

    void detach(int index);

    void notify();

protected:
    std::vector<Observer*> observerList;
};

#endif // _H_SUBJECT_
