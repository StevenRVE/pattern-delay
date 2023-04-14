//
// Created by Steven on 5/17/2021.
//

#include "observerPattern/subject.hpp"

void Subject::attach(Observer& observer)
{
    observerList.push_back(&observer);
}

void Subject::detach(int index)
{
    observerList.erase(observerList.begin()+index);
}

void Subject::notify()
{
    for (auto* obs : observerList)
    {
        obs->update(*this);
    }
}
