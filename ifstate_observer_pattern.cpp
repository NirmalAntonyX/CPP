#include <iostream>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <memory>

using namespace std;
class ifstate;

class ifs // subject
{
private:
    vector<ifstate *> observer_list;

public:
    void attach(ifstate *);
    void detach(ifstate *);
    void notify(string str);
};

class ifstate //observer class
{
private:
    shared_ptr<ifs> _ifl_state;
    shared_ptr<ifs> _iff_state;

public:
    ifstate(shared_ptr<ifs> ifls, shared_ptr<ifs> iffs) : _ifl_state(ifls), _iff_state(iffs)
    {
        _ifl_state->attach(this);
        _iff_state->attach(this);
    }

    virtual void update(string str);
};

class ifls : public ifs // subject concrete
{
};

class iffs : public ifs // subject concrete
{
};

class smgd : public ifstate // observer concrete1
{

public:
    smgd(shared_ptr<ifs> ifls, shared_ptr<ifs> iffs) : ifstate(ifls, iffs) {}

    void update(string str)
    {
        cout << "SMGD\t";
        cout << str << endl;
    }
};

class jpppd : public ifstate // observer concrete2
{
public:
    jpppd(shared_ptr<ifs> ifls, shared_ptr<ifs> iffs) : ifstate(ifls, iffs) {}

    void update(string str)
    {
        cout << "JPPPD\t";
        cout << str << endl;
    }
};


void ifs::attach(ifstate *observer)
{
    observer_list.push_back(observer);
}

void ifs::detach(ifstate *observer)
{
    for (int i = 0; i < observer_list.size(); i++)
    {
        if (observer == observer_list.at(i))
        {
            observer_list.erase(observer_list.begin() + i);
        }
    }
}

void ifs::notify(string str)
{
    for (auto &obs : observer_list) //vector<ifstate *>::iterator obs;
    {
        obs->update(str);
    }
}

   void ifstate::update(string str)
    {
        cout << "IFSTATE\t";
        cout << str << endl;
    }

int main(void)
{
    shared_ptr<ifs> iflState(new ifls());
    shared_ptr<ifs> iffState(new iffs());

    smgd smg(iflState, iffState);
    jpppd pppoed(iflState, iffState);

    iflState->notify("pp0.32427543434 ADD");
    iflState->notify("pp0.32427543434 CHANGE");
    iflState->notify("pp0.32427543434 DELETE");

    iffState->notify("pp0.32427543434 inet ADD");
    iffState->notify("pp0.32427543434 inet6 ADD");

    iffState->notify("pp0.32427543434 inet DELETE");
    iffState->notify("pp0.32427543434 inet6 DELETE");

    return 0;
}