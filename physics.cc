#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
    // SetVerboseLevel(1);

    RegisterPhysics(new G4EmStandardPhysics());
    RegisterPhysics(new G4HadronElasticPhysics());
    RegisterPhysics(new G4HadronInelasticQBBC());
    RegisterPhysics(new G4IonPhysics());
    RegisterPhysics(new G4StoppingPhysics());
    RegisterPhysics(new G4RadioactiveDecayPhysics());
    RegisterPhysics(new G4EmStandardPhysics_option4());
    RegisterPhysics(new G4EmExtraPhysics());
    RegisterPhysics(new G4HadronPhysicsQGSP_BERT_HP());
}

MyPhysicsList::~MyPhysicsList()
{
}

void MyPhysicsList::ConstructParticle()
{
    AddTransportation();
    // Define particles for which interactions will be simulated
    G4VModularPhysicsList::ConstructParticle();
}

void MyPhysicsList::ConstructProcess()
{
    // Define physics processes for the particles
    G4VModularPhysicsList::ConstructProcess();
}

void MyPhysicsList::SetCuts()
{
    // Set the cuts
    G4VModularPhysicsList::SetCuts();
}
