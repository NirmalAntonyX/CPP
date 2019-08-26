#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;
class Radius;
class flatfile;

// command
class accountingCmd
{
public:
    virtual void execute() = 0;
};

//concrete command
class RadiusAccountingCmd : public accountingCmd
{
private:
    // Radius *radius;
    shared_ptr<Radius> radius;

public:
    RadiusAccountingCmd(shared_ptr<Radius> rad)
    {
        radius = rad;
    }
    void execute();
};

class NullCmd : public accountingCmd
{
public:
    void execute() { cout << "NOP" << endl; }
};
// concrete command
class FlatfileAccountingCmd : public accountingCmd
{
private:
    shared_ptr<flatfile> _ff;

public:
    FlatfileAccountingCmd(shared_ptr<flatfile> ff) : _ff(ff) {}

    void execute();
};

// Receiver class
class Radius
{
public:
    void sendVolTimeAccounting()
    {
        cout << "Radius Accounting...." << endl;
    }
};

// Receiver class
class flatfile
{
public:
    void writeFlatFile()
    {
        cout << "FLAT FILE written" << endl;
    }
};

enum accountingTypes
{
    RADIUS_ACCOUNTING,
    FLAT_FILE_ACCOUNTING,
    MAX_ACCOUNTING,
};

// invoker class
class AAA
{
private:
    vector<accountingCmd *> _accountingCmdList;
    int _accType;

public:
    AAA()
    {
        NullCmd *nullCmd = new NullCmd();
        for (int i = 0; i <= MAX_ACCOUNTING; i++)
        {
            _accountingCmdList.push_back(nullCmd);
        }
    }

    void setAccountingModes(int accType, accountingCmd *cmd)
    {
        if (accType >= MAX_ACCOUNTING)
        {
            cout << "invalid accType" << accType;
            return;
        }
        _accountingCmdList[accType] = cmd;
    }

    void performAccounting(int accType)
    {
        if (accType >= MAX_ACCOUNTING)
        {
            cout << "invalid accType" << accType;
            return;
        }
        _accountingCmdList.at(accType)->execute();
    }
};

void RadiusAccountingCmd::execute()
{
    radius->sendVolTimeAccounting();
}

void FlatfileAccountingCmd::execute()
{
    _ff->writeFlatFile();
}
int main(void)
{
    shared_ptr<AAA> auth(new AAA());

    auto radius = shared_ptr<Radius>();
    auto ff = shared_ptr<flatfile>();

    RadiusAccountingCmd *radiusAccCmd = new RadiusAccountingCmd(radius);
    FlatfileAccountingCmd *flatfileCmd = new FlatfileAccountingCmd(ff);

    auth->setAccountingModes(RADIUS_ACCOUNTING, radiusAccCmd);
    auth->setAccountingModes(FLAT_FILE_ACCOUNTING, flatfileCmd);

    auth->performAccounting(RADIUS_ACCOUNTING);
    auth->performAccounting(FLAT_FILE_ACCOUNTING);

    return 0;
}