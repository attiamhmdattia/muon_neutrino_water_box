
#include "B1RunAction.hh"
#include "generator.hh"
#include "construction.hh"
#include "B1Run.hh"
#include "SiPMParameters.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"

#include <sstream>

B1RunAction::B1RunAction()
    : fSaveRndm(0), fAutoSeed(true), G4UserRunAction()
{

  G4AnalysisManager *man = G4AnalysisManager::Instance();
  man->CreateNtuple("muon neutrinos as a primary particle", "muon neutrinos as a primary particle");
  man->CreateNtupleIColumn("fEvent");
  man->CreateNtupleDColumn("fZm");
  man->CreateNtupleDColumn("fTime");
  man->FinishNtuple(0);

  man->CreateNtuple("Particle Creation Information", "Particle Creation Information");
  man->CreateNtupleIColumn("pdgCode");
  man->CreateNtupleDColumn("creationTime");
  man->CreateNtupleSColumn("processName");
  man->FinishNtuple(1);

  // SiPMParameters &parameters = SiPMParameters::GetInstance();
}

B1RunAction::~B1RunAction()
{
}

G4Run *B1RunAction::GenerateRun()
{
  return new B1Run;
}

void B1RunAction::BeginOfRunAction(const G4Run *run)
{

  G4RunManager::GetRunManager()->SetRandomNumberStore(true);
  G4RunManager::GetRunManager()->SetRandomNumberStoreDir("random/");

  if (fAutoSeed)
  {
    // automatic (time-based) random seeds for each run
    G4cout << "*******************" << G4endl;
    G4cout << "*** AUTOSEED ON ***" << G4endl;
    G4cout << "*******************" << G4endl;
    long seeds[2];
    time_t systime = time(NULL);
    seeds[0] = (long)systime;
    seeds[1] = (long)(systime * G4UniformRand());
    G4Random::setTheSeeds(seeds);
    G4Random::showEngineStatus();
  }
  else
  {
    G4Random::showEngineStatus();
  }

  if (fSaveRndm > 0)
    G4Random::saveEngineStatus("BeginOfRun.rndm");

  SiPMParameters &parameters = SiPMParameters::GetInstance();

  G4AnalysisManager *man = G4AnalysisManager::Instance();

  G4int runID = run->GetRunID();

  std::stringstream strRunID;
  strRunID << runID;

  std::stringstream outputFileName{};
  outputFileName << "output"
                 << "_nOE" << parameters.GetNumberOfEvents()
                 //<< "_run" << strRunID.str() // Add the run number to the output file name
                 << ".root";

  man->OpenFile(outputFileName.str());
}

void B1RunAction::EndOfRunAction(const G4Run *)
{
  if (fSaveRndm == 1)
  {
    G4Random::showEngineStatus();
    G4Random::saveEngineStatus("endOfRun.rndm");
  }

  G4AnalysisManager *man = G4AnalysisManager::Instance();

  man->Write();
  man->CloseFile();
}
