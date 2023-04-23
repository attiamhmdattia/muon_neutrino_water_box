#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{

    G4int nofParticles = 1;
    fParticleGun = new G4ParticleGun(nofParticles);

    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particle = particleTable->FindParticle("nu_mu");
    fParticleGun->SetParticleDefinition(particle);

    // G4ThreeVector pos(0., 0., 0.);
    G4ThreeVector mom(0., 0., 1.);

    // fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleMomentum(100. * GeV);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    int particlesPerEvent = 1;
    for (int i = 0; i < particlesPerEvent; i++)

    {
        fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., 0.));
        fParticleGun->GeneratePrimaryVertex(anEvent);
    }
}