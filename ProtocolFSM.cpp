#include <iostream>
#include <memory>

using namespace std;

/* PPP Protocol state machine. */
enum class states
{
    LCP_CLOSED,
    LCP_OPEN,
    NCP_CLOSED,
    NCP_OPEN,
};
class PPP;
class PPPStates
{
  public:
    virtual void handleState(PPP &ppp, states state) = 0;
    virtual void execute() = 0;
    virtual string getState() = 0;
};
class lcpclosed : public PPPStates
{
    void execute() override
    {
    }
    void handleState(PPP &ppp, states state) override;
    string getState() override
    {
        return "LCPCLOSED";
    }
};

class lcpopen : public PPPStates
{
    void handleState(PPP &ppp, states state) override;
     void execute() override
    {
    }
    string getState() override
    {
        return "LCPOPEN";
    }
};

class ncpclosed : public PPPStates
{
    void handleState(PPP &ppp, states state) override;
  
    void execute() override
    {
    }
    string getState() override
    {
        return "NCPCLOSED";
    }
};

class ncpopen : public PPPStates
{
    void handleState(PPP &ppp, states state) override;
  
    void execute() override
    {
    }
    string getState() override
    {
        return "NCPOPEN";
    }
};

shared_ptr<lcpclosed> lcpclosedstate(new lcpclosed());
class PPP
{
  public:
    shared_ptr<PPPStates> _state;

    PPP()
    {
        _state = lcpclosedstate;
    }

    changeState(shared_ptr<PPPStates> newstate)
    {
        _state = newstate;
        _state->execute();
    }

    shared_ptr<PPPStates> getState() const
    {
        return _state;
    }

    void handleInput(states state)
    {

        _state->handleState(*this, state);
    }
};

    void lcpclosed::handleState(PPP &ppp, states state) 
    {
        switch (state)
        {
        case states::LCP_CLOSED:
               cout << "already in LCP CLOSED state" << endl;
            break;
        case states::LCP_OPEN:
                cout << "moving from LCP CLOSED to LCP OPEN" << endl;
                ppp.changeState(shared_ptr<lcpopen>(new lcpopen()));
            break;
        case states::NCP_CLOSED:
                 cout << "LCP not opened" << endl;
            break;
        case states::NCP_OPEN:
                cout << "LCP not opened" << endl;
            break;
        default:
            break;
        }
    }

        void lcpopen::handleState(PPP &ppp, states state) 
    {
        switch (state)
        {
        case states::LCP_CLOSED:
             cout << "moving to LCP closed state" << endl;
             ppp.changeState(shared_ptr<lcpclosed> (new lcpclosed()));
            break;
        case states::LCP_OPEN:
          cout << "Already in LCP OPEN. no action." << endl;
            break;
        case states::NCP_CLOSED:
            cout << "NCP is not yet OPEN. no action" << endl;
            break;
        case states::NCP_OPEN:
        cout << "moving to NCP OPEN state" << endl;
             ppp.changeState(shared_ptr<ncpopen> (new ncpopen()));
            break;
        default:
            break;
        }
    }


        void ncpclosed::handleState(PPP &ppp, states state) 
    {
        switch (state)
        {
        case states::LCP_CLOSED:
             cout << "moving to LCP closed state" << endl;
             ppp.changeState(shared_ptr<lcpclosed> (new lcpclosed()));
            break;
        case states::LCP_OPEN:
              cout << "moving to LCP OPEN state" << endl;
             ppp.changeState(shared_ptr<lcpopen> (new lcpopen()));
            break;
            break;
        case states::NCP_CLOSED:
        cout << "already in NCP CLOSED" << endl;
            break;
        case states::NCP_OPEN:
        cout << "moving to NCP OPEN state" << endl;
        ppp.changeState(shared_ptr<ncpopen> (new ncpopen()));
            break;
        default:
            break;
        }
    }

    
        void ncpopen::handleState(PPP &ppp, states state) 
    {
        switch (state)
        {
        case states::LCP_CLOSED:
             cout << "First need to close LCP" << endl;
             break;
        case states::LCP_OPEN:
        cout << "First need to close NCP" << endl;
            break;
        case states::NCP_CLOSED:
          cout << "moving to NCP CLOSED state" << endl;
        ppp.changeState(shared_ptr<ncpclosed> (new ncpclosed()));
            break;
        case states::NCP_OPEN:
        cout << "already in NCP OPEN" << endl;
            break;
        default:
            break;
        }
    }
states mapChoies(int ch)
{
    states st[] =
        {
            states::LCP_CLOSED,
            states::LCP_OPEN,
            states::NCP_CLOSED,
            states::NCP_OPEN,
        };
    return st[ch];
}

int main(void)
{
    PPP ppp;
    int ch;

    auto choicefn = [&ch, &ppp]() {
        states choice;
        cout << "current state is" << endl
             << ppp.getState()->getState() << endl
             << "enter new state" << endl;
        cin >> ch;
        choice = mapChoies(ch);
        ppp.handleInput(choice);
    };

    while (true)
    {
        choicefn();
    }
    return 1;
}