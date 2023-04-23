
#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "construction.hh"

#include "G4SteppingManager.hh"

#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "math.h"
#include "G4SystemOfUnits.hh"

#include "G4AnalysisManager.hh"

B1SteppingAction::B1SteppingAction(
    B1EventAction *eventAction)
    : G4UserSteppingAction(),
      fEventAction(eventAction),

      fScoringVolume(0)

{
}

B1SteppingAction::~B1SteppingAction()
{
}

void B1SteppingAction::UserSteppingAction(const G4Step *fStep)
{

  // Get the track associated with this step
  G4Track *track = fStep->GetTrack();

  if (track->GetTrackStatus() != fAlive)
  {
    return;
  }
  // Get the particle name
  G4String particleName = track->GetParticleDefinition()->GetParticleName();

  // Print the particle name for debugging purposes
  // G4cout << "Particle name: " << particleName << G4endl;

  G4double postZ = fStep->GetPostStepPoint()->GetPosition().z();
  G4double Gtime = fStep->GetPostStepPoint()->GetGlobalTime();
  G4VPhysicalVolume *prevolume = fStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  G4VPhysicalVolume *postvolume = fStep->GetPostStepPoint()->GetTouchableHandle()->GetVolume();

  if (particleName == "nu_mu" && prevolume->GetName() == "physWorld" && postvolume->GetName() == "physWater")
  {
    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID(); // event number

    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->FillNtupleIColumn(0, evt);
    man->FillNtupleDColumn(1, postZ / m);
    man->FillNtupleDColumn(2, Gtime / ns);
    man->AddNtupleRow(0);
  }

  // Check if particle was created in water
  if (track->GetParentID() == 0 || track->GetVolume()->GetName() != "physWater")
  {
    return;
  }

  const G4VProcess *creatorProcess = track->GetCreatorProcess();

  // Print out particle information for particles created in water
  if (creatorProcess != NULL)
  {
    G4String processName = creatorProcess->GetProcessName();
    G4double creationTime = track->GetGlobalTime();
    G4int particleID = track->GetTrackID();
    G4int pdgCode = track->GetParticleDefinition()->GetPDGEncoding();

    // G4cout << "Particle ID " << particleID << " (" << particleName << ") created by " << processName << " at time " << creationTime / second << " s. PDG code: " << pdgCode << G4endl;

    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->FillNtupleIColumn(1, 0, pdgCode);
    man->FillNtupleDColumn(1, 1, creationTime);
    man->FillNtupleSColumn(1, 2, processName);
    man->AddNtupleRow(1);
  }
}