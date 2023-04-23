//
//  Parameters.hh
//  Parameters
//
//  Created by Baranyai David on 2018. 06. 30..
//  Modified for SiPM Simulation on 2018. 08. 23..
//  Copyright © 2018. Baranyai David. All rights reserved.
//

#ifndef SiPMParameters_hh
#define SiPMParameters_hh

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"

class SiPMParameters
{
public:
    static SiPMParameters &GetInstance(const std::string &config_file_name = "../config.conf");
    ~SiPMParameters();

    //---Units---------------------------------------------------------------------------------------------
    enum lengthUnit
    {
        mm,
        cm,
        m
    };

    void SetGlobalLengthUnit(lengthUnit l) { globalLengthUnit = l; }
    double GetLengthMultiplier() // returns the correct length multiplier for the global length unit (use it instead of *cm/*mm/*m)
    {
        switch (globalLengthUnit)
        {
        case mm:
            return millimeter;
            break;
        case cm:
            return centimeter;
            break;
        case m:
            return meter;
            break;
        default:
            return centimeter;
            break;
        }
    }

    //---Config file---------------------------------------------------------------------------------------
    void ParseConfigFile();                         // Read the default config file
    void ParseConfigFile(std::string config_file1); // Read another config file

    G4double GetTargetWidth() {return targetWidth;}
    G4double GetMagneticField() {return magneticField;}
    G4int GetBBox() {return bBox;}
    G4int GetPhysicsListType() {return physicsListType;}
    G4int GetCutType() {return cutType;}
    G4int GetNumberOfCherenkovs (){return numberOfCherenkovs;}

    G4double GetstartingAngle(){return startingAngle;}
    //
     bool IsScoring() {return isScoring; }
    //---Particle Gun parameters---------------------------------------------------------------------------
    void SetParticleGunPosition(G4ThreeVector pgp) { particleGun_position = pgp; }
    void SetParticleGunPosition(G4double x, G4double y, G4double z) { particleGun_position.set(x, y, z); }
    G4ThreeVector GetParticleGunPosition() { return particleGun_position; }

    void SetParticleGunMomentumDirection(G4ThreeVector pgm) { particleGun_MomentumDirection = pgm; }
    void SetParticleGunMomentumDirection(G4double x, G4double y, G4double z) { particleGun_MomentumDirection.set(x, y, z); }
    G4ThreeVector GetParticleGunMomentumDirection() { return particleGun_MomentumDirection; }

    void SetParticleGunEnergy(G4double pge) { particleGun_energy = pge; }
    G4double GetParticleGunEnergy() { return particleGun_energy; }

    void SetParticleGunType(G4int pgt) { particleGun_type = pgt; }
    G4int GetParticleGunType() { return particleGun_type; }

    void SetParticleGunMonoEnergy(G4int pgme) { particleGun_MonoEnergy = pgme; }
    G4int GetParticleGunMonoEnergy() { return particleGun_MonoEnergy; }

    //---SiPM parameters-----------------------------------------------------------------------------------
    void SetSiPMSize(G4ThreeVector sipm_s) { sipm_Dimension = sipm_s; }
    void SetSiPMSize(G4double x, G4double y, G4double z) { sipm_Dimension.set(x, y, z); }
    G4ThreeVector GetSiPMSize() { return sipm_Dimension; }
    void FirstSiPMEnabled(bool enabled) { sipm1Enabled = enabled; }
    bool FirstSiPMEnabled() { return sipm1Enabled; }
    void SecondSiPMEnabled(bool enabled) { sipm2Enabled = enabled; }
    bool SecondSiPMEnabled() { return sipm2Enabled; }

    //---Scintillator parameters---------------------------------------------------------------------------
    void SetScintillatorLength(G4double sc_l)
    {
        scintillator_length = sc_l;
        scintillator_Dimension.setZ(sc_l);
    }
    G4double GetScintillatorLength() { return scintillator_length; }
    void SetScintillatorSize(G4double x, G4double y, G4double z) { scintillator_Dimension.set(x, y, z); }
    G4ThreeVector GetScintillatorSize() { return scintillator_Dimension; }
    double GetCoatingThickness() { return cThickness; }
    void SetCoatingThickness(double t) { cThickness = t; }

    //---Division parameters-------------------------------------------------------------------------------
    void SetDivision(G4int x, G4int y)
    {
        x_division = x;
        y_division = y;
    };
    void SetXDivision(G4int x) { x_division = x; }
    void SetYDivision(G4int y) { y_division = y; }
    G4int GetXDivison() { return x_division; }
    G4int GetYDivison() { return y_division; }

    //---Radius parameters---------------------------------------------------------------------------------
    void SetScintillatorRadius(G4double sc_r) { scint_radius = sc_r; }
    G4double GetScintillatorRadius() { return scintIsBox ? 0.0 : scint_radius; } // If it is a box, return 0

    //---Scintillator Tube vs box parameters---------------------------------------------------------------
    void ScintillatorIsBox(bool isBox) { scintIsBox = isBox; }
    bool ScintillatorIsBox() { return scintIsBox; }

    //---Number of Events, Particles per event and Threads-------------------------------------------------
    void SetNumberOfEvents(long unsigned int noe1) { numberofevents = noe1; }
    long long unsigned int GetNumberOfEvents() { return numberofevents; }
    void SetParticlesPerEvent(unsigned ppe1) { particlesperevent = ppe1; }
    unsigned GetParticlesPerEvent() { return particlesperevent; }
    void SetNumberOfThreads(unsigned not1) { numberofthreads = not1; }
    unsigned GetNumberOfThreads() { return numberofthreads; }

    // Absorption lenght
    void SetAbsorptionLength1(G4double l) { absLength1 = l; }
    G4double GetAbsorptionLength1() { return absLength1; }
    void SetAbsorptionLength2(G4double l) { absLength2 = l; }
    G4double GetAbsorptionLength2() { return absLength2; }

    // Refraction Index
    void SetRefractiveIndex1(G4double i) { refrIndex1 = i; }
    G4double GetRefractiveIndex1() { return refrIndex1; }
    void SetRefractiveIndex2(G4double i) { refrIndex2 = i; }
    G4double GetRefractiveIndex2() { return refrIndex2; }

    // Coating reflectivity
    void SetCoatingReflectivity1(G4double r) { coatingreflectivity1 = r; }
    G4double GetCoatingReflectivity1() { return coatingreflectivity1; }
    void SetCoatingReflectivity2(G4double r) { coatingreflectivity2 = r; }
    G4double GetCoatingReflectivity2() { return coatingreflectivity2; }

    //---Tissue parameters---------------------------------------------------------------------------
    void SetTissueSize(G4double x, G4double y, G4double z) { tissue_Dimension.set(x, y, z); }
    G4ThreeVector GetTissueSize() { return tissue_Dimension; }

    void SetTissuePosition(G4ThreeVector tp) { tissue_position = tp; }
    void SetTissuePosition(G4double x, G4double y, G4double z) { tissue_position.set(x, y, z); }
    G4ThreeVector GetTissuePosition() { return tissue_position; }

    void SetTissueRotation(G4ThreeVector tr) { tissue_rotation = tr; }
    void SetTissueRotation(G4double x, G4double y, G4double z) { tissue_rotation.set(x, y, z); }
    G4ThreeVector GetTissueRotation() { return tissue_rotation; }

    // Bone
    void SetBoneSize(G4double x, G4double y, G4double z) { bone_Dimension.set(x, y, z); }
    G4ThreeVector GetBoneSize() { return bone_Dimension; }

    void SetBonePosition(G4ThreeVector bp) { bone_position = bp; }
    void SetBonePosition(G4double x, G4double y, G4double z) { bone_position.set(x, y, z); }
    G4ThreeVector GetBonePosition() { return bone_position; }

    // Target
    void SetTargetType(G4int tp) { target_type = tp; }
    G4int GetTargetType() { return target_type; }

    // Giude parameters
    void SetGuideLength(G4double g_l) { guide_length = g_l; }
    G4double GetGuideLength() { return guide_length; }
    void SetGuideRadius(G4double g_r) { guide_radius = g_r; }
    G4double GetGuideRadius() { return guide_radius; }

    // Grid parameters
    void SetGridLength(G4double g_l) { grid_length = g_l; }
    G4double GetGridLength() { return grid_length; }
    void SetGridWidth(G4double g_w) { grid_width = g_w; }
    G4double GetGridWidth() { return grid_width; }

    //---Sipm left or right---------------------------------------------------------------
    void SipmLeft(bool isLeft) { sipm_left = isLeft; }
    bool SipmLeft() { return sipm_left; }

    void CheckOverlaps(bool check) { checkOverlaps = check; }
    bool CheckOverlaps() { return checkOverlaps; }

    // Init things
    bool initialized = false;

    void ResetToDefaults();

    SiPMParameters(const SiPMParameters &) = delete;
    SiPMParameters &operator=(const SiPMParameters &) = delete;

private:
    SiPMParameters(const std::string &config_file_name);
    void PrintUsedFilename();

    //---Config file---------------------------------------------------------------------------------------
    std::string config_file;
    void StoreConfigValues(std::string key1, std::string value1);
    void CheckValues();
    bool conf_loaded = false;

    G4double targetWidth;
    G4double magneticField;
    G4int bBox;
    G4int physicsListType;
    G4int cutType;


    G4ThreeVector particleGun_position;
    G4ThreeVector particleGun_MomentumDirection;
    G4double particleGun_energy; // in keV
    G4int particleGun_type;
    G4int particleGun_MonoEnergy;

    G4ThreeVector sipm_Dimension; // applies to both (in cm)
    G4double scintillator_length; // the size same as sipm
    G4double scint_radius;
    G4ThreeVector scintillator_Dimension;

    G4int x_division;
    G4int y_division;

    long long unsigned int numberofevents;
    unsigned numberofthreads;
    unsigned particlesperevent;

    G4double absLength1;
    G4double absLength2;
    G4double refrIndex1;
    G4double refrIndex2;

    G4double coatingreflectivity1;
    G4double coatingreflectivity2;

    bool scintIsBox = true;
    bool sipm1Enabled = true;
    bool sipm2Enabled = false;
    bool sipm_left = false;
    bool checkOverlaps = true;

    lengthUnit globalLengthUnit = cm; // default length is cm

    double cThickness = 1;

    G4ThreeVector tissue_Dimension;
    G4ThreeVector tissue_position;
    G4ThreeVector tissue_rotation;

    // G4double bonesize_z;
    G4ThreeVector bone_Dimension;
    G4ThreeVector bone_position;

    G4int target_type;

    G4double guide_length;
    G4double guide_radius;

    G4double grid_length;
    G4double grid_width;

    G4int numberOfCherenkovs;
    G4double startingAngle;
    bool isScoring;
};

#endif /* Parameters_hh */
