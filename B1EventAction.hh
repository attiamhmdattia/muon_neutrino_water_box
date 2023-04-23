

#ifndef B1EventAction_h
#define B1EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

/// Event action class
///

class B1EventAction : public G4UserEventAction
{
public:
  B1EventAction();
  virtual ~B1EventAction();

  virtual void BeginOfEventAction(const G4Event *event);
  virtual void EndOfEventAction(const G4Event *event);

  void AddEdep(G4double edep) { fEdep += edep; }
  G4int pID[10000000];
  G4int pTrackID[10000000];
  G4double x[10000000];
  G4double y[10000000];
  G4double z[10000000];
  G4double E[10000000];
  G4double Th[10000000];
  G4double Ph[10000000];
  G4double momx[10000000];
  G4double momy[10000000];
  G4double momz[10000000];
  G4int maxTrackID;
  G4int oldTrackID;

  // accessors
  // G4int GetNcerenkov() const { return fNcerenkov; }
  // G4int GetNscint() const { return fNscint; }

  // modifiers
  // void IncrementNcerenkov() { ++fNcerenkov; }
  // void IncrementNscint() { ++fNscint; }

private:
  G4double fEdep;
};

#endif
