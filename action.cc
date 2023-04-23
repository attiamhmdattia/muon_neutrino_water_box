#include "action.hh"
#include "generator.hh"
#include "B1RunAction.hh"
#include "B1EventAction.hh"
#include "B1SteppingAction.hh"

MyActionInitialization::MyActionInitialization()
{
}

MyActionInitialization::~MyActionInitialization()
{
}

void MyActionInitialization::BuildForMaster() const
{
    SetUserAction(new B1RunAction);
}

void MyActionInitialization::Build() const
{
    SetUserAction(new MyPrimaryGenerator);
    B1RunAction *runAction = new B1RunAction;
    SetUserAction(runAction);

    B1EventAction *eventAction = new B1EventAction;
    SetUserAction(eventAction);
    G4cout << "steppingaction előtt" << G4endl;
    SetUserAction(new B1SteppingAction(eventAction));
    // SetUserAction(new StackingAction(runaction,eventAction,cut));
}
