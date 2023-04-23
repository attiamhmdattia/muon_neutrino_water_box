#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
}

MyDetectorConstruction::~MyDetectorConstruction()
{
}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager *nist = G4NistManager::Instance();
  // G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material *worldMat = nist->FindOrBuildMaterial("G4_Galactic");
  //  World
  G4Box *solidWorld = new G4Box("solidWorld", 500. * m, 500. * m, 500. * m);
  G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
  G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

  // World visualization attributes
  G4VisAttributes *worldVisAtt = new G4VisAttributes(G4Colour(1., 1., 1., 0.2));
  worldVisAtt->SetForceSolid(true);
  logicWorld->SetVisAttributes(worldVisAtt);

  // Water box
  G4Material *waterMat = nist->FindOrBuildMaterial("G4_WATER");
  G4Box *solidWater = new G4Box("Water", 50. * m, 50. * m, 50. * m);
  G4LogicalVolume *logicWater = new G4LogicalVolume(solidWater, waterMat, "logicWater");

  // Water box visualization attributes
  G4VisAttributes *waterVisAtt = new G4VisAttributes(G4Colour(1., 1., 0., 0.2));
  waterVisAtt->SetForceSolid(true);
  logicWater->SetVisAttributes(waterVisAtt);

  // Place water box inside world
  // G4double pos_water = 0.5 * (world_size - water_size);
  G4VPhysicalVolume *physWater = new G4PVPlacement(0, G4ThreeVector(0., 0., 450. * m), logicWater, "physWater", logicWorld, false, 0, true);

  return physWorld;
}
