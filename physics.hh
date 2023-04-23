#ifndef PHYSICS_HH
#define PHYSICS_HH

#include "G4VModularPhysicsList.hh"

#include "G4EmStandardPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4IonPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

#include "G4MuonNuclearProcess.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmExtraPhysics.hh"
#include "G4HadronPhysicsQGSP_BERT_HP.hh"

class MyPhysicsList : public G4VModularPhysicsList
{
public:
    MyPhysicsList();
    ~MyPhysicsList();

    virtual void SetCuts();
    virtual void ConstructParticle();
    virtual void ConstructProcess();
};

#endif
