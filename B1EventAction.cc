

#include "B1EventAction.hh"
#include "B1Run.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

B1EventAction::B1EventAction()
    : G4UserEventAction(),
      fEdep(0.)
{
}

B1EventAction::~B1EventAction()
{
}

void B1EventAction::BeginOfEventAction(const G4Event *evt)
{
  G4int evtNb = evt->GetEventID();
  G4cout << "EventNumber " << evtNb << G4endl;
  fEdep = 0.;
  for (G4int i = 0; i < 10000000; i++)
  {
    pID[i] = 0;
    pTrackID[i] = 0;
    x[i] = 0.0;
    y[i] = 0.0;
    z[i] = 0.0;
    E[i] = 0.0;
    Th[i] = 0.0;
    Ph[i] = 0.0;
    momx[i] = 0.0;
    momy[i] = 0.0;
    momz[i] = 0.0;
  }
  maxTrackID = 0;
  oldTrackID = -1;
}

void B1EventAction::EndOfEventAction(const G4Event *)
{
  // accumulate statistics in B1Run
  B1Run *run = static_cast<B1Run *>(
      G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  run->AddEdep(fEdep);

  //  G4cout<<maxTrackID<<G4endl;
}
