
#ifndef B1SteppingAction_h
#define B1SteppingAction_h 1
#include "G4Trajectory.hh"
#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include "SiPMParameters.hh"
#include "G4OpticalPhoton.hh"
class B1EventAction;
class B1RunAction;

class G4LogicalVolume;

/// Stepping action class
///

class B1SteppingAction : public G4UserSteppingAction
{
public:
  B1SteppingAction(B1EventAction *eventAction);
  virtual ~B1SteppingAction();

  // method from the base class
  virtual void UserSteppingAction(const G4Step *);
  G4Trajectory *GetParentTrajectory(G4int parentID);

private:
  B1EventAction *fEventAction;
  G4LogicalVolume *fScoringVolume;
  B1RunAction *fRunAction;
  G4int whereItWas;
  // G4int particleID, parentID, GrandParentID, GreatGrandParentID;

  // G4double xPosition, yPosition, zPosition;
};

#endif
