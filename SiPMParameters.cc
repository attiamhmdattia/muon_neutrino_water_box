//
//  Parameters.cc
//  Parameters
//
//  Created by Baranyai David on 2018. 06. 30..
//  Modified for SiPM Simulation on 2018. 08. 23..
//  Copyright © 2018. Baranyai David. All rights reserved.
//

#include "SiPMParameters.hh"

SiPMParameters& SiPMParameters::GetInstance(const std::string& config_file_name)
{
    static SiPMParameters instance(config_file_name);
    //instance.PrintUsedFilename();
    return instance;
}

SiPMParameters::SiPMParameters(const std::string& config_file_name) : config_file(config_file_name)
{
    ResetToDefaults();
}

SiPMParameters::~SiPMParameters()
{
}

void SiPMParameters::PrintUsedFilename()
{
    if(initialized && conf_loaded) return;
    std::cout << config_file << (conf_loaded ? " loaded." : " will be loaded. Call ParseConfigFile().") << std::endl;
    initialized = true;
}

void SiPMParameters::ResetToDefaults()
{
    particleGun_position = G4ThreeVector(0, 0, -5);
    particleGun_MomentumDirection = G4ThreeVector(0, 0, 1);
    particleGun_energy = 500; //in KeV

    sipm_Dimension = G4ThreeVector(2, 2, 10); //applies to both (in cm)
    scintillator_length = 10; //the size same as sipm


    x_division = 1;
    y_division = 1;

    scint_radius = 0.25; //in cm

    numberofevents = 10;

    scintIsBox = true;
    sipm1Enabled = true;
    sipm2Enabled = false;

    absLength1 = 35.0;
    absLength2 = 35.0;

    refrIndex1 = 1.59;
    refrIndex2 = 1.57;

    coatingreflectivity1 = 0.9;
    coatingreflectivity2 = 0.9;
}

void SiPMParameters::ParseConfigFile()
{
    PrintUsedFilename();

    std::string line;
    try
    {
        std::ifstream configfile(config_file);
        if(configfile.is_open())
        {
            while (getline(configfile, line))
            {
                std::istringstream is_line(line);
                std::string key;
                if (std::getline(is_line, key, '='))
                {
                    std::string value;
                    if(std::getline(is_line, value))
                    {
                        StoreConfigValues(key, value);
                    }
                }
            }
        }
        CheckValues();
        conf_loaded = true;
    }
    catch (char param)
    {
        std::cout << param << std::endl;
    }
}

void SiPMParameters::ParseConfigFile(std::string config_file1)
{
    config_file = config_file1;
    ParseConfigFile();
}

void SiPMParameters::StoreConfigValues(std::string key1, std::string value1)
{
    if(key1.compare("targetWidth") == 0)
    {
        targetWidth = std::stod(value1);
        std::cout << "targetWidth parsed from config file! Value = " << targetWidth << std::endl;
    }
    else if(key1.compare("magneticField") == 0)
    {
        magneticField = std::stod(value1);
        std::cout << "magneticField parsed from config file! Value = " << magneticField << std::endl;
    }
    else if(key1.compare("bBox") == 0)
    {
        bBox = std::stoi(value1);
        std::cout << "bBox parsed from config file! Value = " << bBox << std::endl;
    }
    else if(key1.compare("physicsListType") == 0)
    {
        physicsListType = std::stoi(value1);
        std::cout << "physicsListType parsed from config file! Value = " << physicsListType << std::endl;
    }
    else if(key1.compare("cutType") == 0)
    {
        cutType = std::stoi(value1);
        std::cout << "cutType parsed from config file! Value = " << cutType << std::endl;
    }

    else if(key1.compare("numberOfCherenkovs") == 0)
    {
        numberOfCherenkovs = std::stoi(value1);
        std::cout << "numberOfCherenkovs parsed from config file! Value = " << numberOfCherenkovs << std::endl;
    }

    else if(key1.compare("startingAngle") == 0)
    {
        startingAngle = std::stod(value1);
        std::cout << "startingAngle parsed from config file! Value = " << startingAngle << std::endl;
    }
    //---Particle gun position---------------------------------------------------------------------------------------------------
    else if(key1.compare("pgpositionx") == 0)
    {
        particleGun_position.setX(std::stod(value1));
        std::cout << "Particle Gun X position parsed from config file! Value = " << particleGun_position.getX() << std::endl;
    }
    else if(key1.compare("pgpositiony") == 0)
    {
        particleGun_position.setY(std::stod(value1));
        std::cout << "Particle Gun Y position parsed from config file! Value = " << particleGun_position.getY() << std::endl;
    }
    else if(key1.compare("pgpositionz") == 0)
    {
        particleGun_position.setZ(std::stod(value1));
        std::cout << "Particle Gun Z position parsed from config file! Value = " << particleGun_position.getZ() << std::endl;
    }

    //---Particle gun momentum----------------------------------------------------------------------------------------------------
    else if(key1.compare("pgmomentumx") == 0)
    {
        particleGun_MomentumDirection.setX(std::stod(value1));
        std::cout << "Particle Gun X momentum parsed from config file! Value = " << particleGun_MomentumDirection.getX() << std::endl;
    }
    else if(key1.compare("pgmomentumy") == 0)
    {
        particleGun_MomentumDirection.setY(std::stod(value1));
        std::cout << "Particle Gun Y momentum parsed from config file! Value = " << particleGun_MomentumDirection.getY() << std::endl;
    }
    else if(key1.compare("pgmomentumz") == 0)
    {
        particleGun_MomentumDirection.setZ(std::stod(value1));
        std::cout << "Particle Gun Z momentum parsed from config file! Value = " << particleGun_MomentumDirection.getZ() << std::endl;
    }

    //---Particle gun energy------------------------------------------------------------------------------------------------------
    else if(key1.compare("pgenergy") == 0)
    {
        particleGun_energy = std::stod(value1);
        std::cout << "Particle Gun energy parsed from config file! Value = " << particleGun_energy << std::endl;
    }

    //---Particle gun type------------------------------------------------------------------------------------------------------
    else if(key1.compare("pgtype") == 0)
    {
        particleGun_type = std::stoi(value1);
        std::cout << "Particle Gun type parsed from config file! Value = " << particleGun_type << std::endl;
    }

    //---Particle gun monoenergy------------------------------------------------------------------------------------------------------
    else if(key1.compare("pgmonoenergy") == 0)
    {
        particleGun_MonoEnergy = std::stoi(value1);
        std::cout << "Particle Gun Mono Energy parsed from config file! Value = " << particleGun_MonoEnergy << std::endl;
    }

    //---SiPM dimensions----------------------------------------------------------------------------------------------------------
    else if(key1.compare("sipmsizex") == 0)
    {
        sipm_Dimension.setX(std::stod(value1));
        std::cout << "SiPM X size parsed from config file! Value = " << sipm_Dimension.getX() << std::endl;
    }
    else if(key1.compare("sipmsizey") == 0)
    {
        sipm_Dimension.setY(std::stod(value1));
        std::cout << "SiPM Y size parsed from config file! Value = " << sipm_Dimension.getY() << std::endl;
    }
    else if(key1.compare("sipmsizez") == 0)
    {
        sipm_Dimension.setZ(std::stod(value1));
        std::cout << "SiPM Z size parsed from config file! Value = " << sipm_Dimension.getZ() << std::endl;
    }

    //---Sscintillator------------------------------------------------------------------------------------------------------------
    else if(key1.compare("scintillatorlength") == 0)
    {
        scintillator_length = std::stod(value1);
        scintillator_Dimension.setZ(std::stod(value1));
        std::cout << "Scintillator length parsed from config file! Value = " << scintillator_length << std::endl;
    }
    else if(key1.compare("scintillatorradius") == 0)
    {
        scint_radius = std::stod(value1);
        std::cout << "Scintillator radius parsed from config file! Value = " << scint_radius << std::endl;
    }

    //---Sscintillator------------------------------------------------------------------------------------------------------------
    else if(key1.compare("xdivision") == 0)
    {
        x_division = std::stod(value1);
        std::cout << "X division parsed from config file! Value = " << x_division << std::endl;
    }
    else if(key1.compare("ydivision") == 0)
    {
        y_division = std::stod(value1);
        std::cout << "Y division parsed from config file! Value = " << y_division << std::endl;
    }


    else if (key1.compare("scintillatorsizex") == 0)
    {
        scintillator_Dimension.setX(std::stod(value1));
        std::cout << "Scintillator X size set from config file! Value = " << scintillator_Dimension.getX() << std::endl;
    }
    else if (key1.compare("scintillatorsizey") == 0)
    {
        scintillator_Dimension.setY(std::stod(value1));
        std::cout << "Scintillator Y size set from config file! Value = " << scintillator_Dimension.getY() << std::endl;
    }
    else if (key1.compare("scintillatorsizez") == 0)
    {
        scintillator_Dimension.setZ(std::stod(value1));
        std::cout << "Scintillator Z size set from config file! Value = " << scintillator_Dimension.getZ() << std::endl;
    }

    else if (key1.compare("scintillatorisbox") == 0)
    {
        if (std::stod(value1) != 0)
        {
            scintIsBox = true;
            std::cout << "Using box scintillator." << std::endl;
        }
        else
        {
            scintIsBox = false;
            std::cout << "Using tube scintillator." << std::endl;
        }
    }

    else if (key1.compare("firstsipmenabled") == 0)
    {
        if (std::stod(value1) != 0)
        {
            sipm1Enabled = true;
            std::cout << "First SiPM enabled." << std::endl;
        }
        else
        {
            sipm1Enabled = false;
            std::cout << "First SiPM disabled." << std::endl;
        }
    }

    else if (key1.compare("secondsipmenabled") == 0)
    {
        if (std::stod(value1) != 0)
        {
            sipm2Enabled = true;
            std::cout << "Second SiPM enabled." << std::endl;
        }
        else
        {
            sipm2Enabled = false;
            std::cout << "Second SiPM disabled." << std::endl;
        }
    }

    else if (key1.compare("coatingthickness") == 0)
    {
        cThickness = std::stod(value1);
        std::cout << "Coating thickness set to " << cThickness << std::endl;
    }

    else if (key1.compare("lengthunit") == 0)
    {
        if (value1.compare("mm") == 0)
        {
            std::cout << "Length unit is mm." << std::endl;
            globalLengthUnit = mm;
        }
        else if (value1.compare("cm") == 0)
        {
            std::cout << "Length unit is cm." << std::endl;
            globalLengthUnit = cm;
        }
        else if (value1.compare("m") == 0)
        {
            std::cout << "Length unit is m." << std::endl;
            globalLengthUnit = m;
        }
    }

    //---Number of events and threads---------------------------------------------------------------------------------------------------------
    else if(key1.compare("numberofevents") == 0)
    {
        numberofevents = std::stoull(value1);
        std::cout << "Number of events parsed from config file! Value = " << numberofevents << std::endl;
    }

    else if(key1.compare("particlesperevent") == 0)
    {
        particlesperevent = std::stod(value1);
        std::cout << "Number of particles per event parsed from config file! Value = " << particlesperevent << std::endl;
    }

    else if(key1.compare("numberofthreads") == 0)
    {
        numberofthreads = std::stod(value1);
        std::cout << "Number of threads parsed from config file! Value = " << numberofthreads << std::endl;
    }

    //---Absorption Length--------------------------------------------------------------------------------------------------------
    else if(key1.compare("abslength1") == 0)
    {
        absLength1 = std::stod(value1);
        std::cout << "Absorption Length1 parsed from config file! Value = " << absLength1 << std::endl;
    }
    else if(key1.compare("abslength2") == 0)
    {
        absLength2 = std::stod(value1);
        std::cout << "Absorption Length2 parsed from config file! Value = " << absLength2 << std::endl;
    }

    //---Refractive Index---------------------------------------------------------------------------------------------------------
    else if(key1.compare("refrindex1") == 0)
    {
        refrIndex1 = std::stod(value1);
        std::cout << "Refractive Index1 parsed from config file! Value = " << refrIndex1 << std::endl;
    }
    else if(key1.compare("refrindex2") == 0)
    {
        refrIndex2 = std::stod(value1);
        std::cout << "Refractive Index2 parsed from config file! Value = " << refrIndex2 << std::endl;
    }

    //---Coating reflectivity-----------------------------------------------------------------------------------------------------
    else if(key1.compare("coatingreflectivity1") == 0)
    {
        coatingreflectivity1 = std::stod(value1);
        std::cout << "Coating reflectivity1 parsed from config file! Value = " << coatingreflectivity1 << std::endl;
    }
    else if(key1.compare("coatingreflectivity2") == 0)
    {
        coatingreflectivity2 = std::stod(value1);
        std::cout << "Coating reflectivity2 parsed from config file! Value = " << coatingreflectivity2 << std::endl;
    }

    //---Tissue-----------------------------------------------------------------------------------------------------
    //Tissue Position
    else if(key1.compare("tissuepositionx") == 0)
    {
        tissue_position.setX(std::stod(value1));
        std::cout << "Tissue X position parsed from config file! Value = " << tissue_position.getX() << std::endl;
    }
    else if(key1.compare("tissuepositiony") == 0)
    {
        tissue_position.setY(std::stod(value1));
        std::cout << "Tissue Y position parsed from config file! Value = " << tissue_position.getY() << std::endl;
    }
    else if(key1.compare("tissuepositionz") == 0)
    {
        tissue_position.setZ(std::stod(value1));
        std::cout << "Tissue Z position parsed from config file! Value = " << tissue_position.getZ() << std::endl;
    }

    //Tissue Rotation
    else if(key1.compare("tissuerotx") == 0)
    {
        tissue_rotation.setX(std::stod(value1));
        std::cout << "Tissue X rotation parsed from config file! Value = " << tissue_rotation.getX() << std::endl;
    }
    else if(key1.compare("tissueroty") == 0)
    {
        tissue_rotation.setY(std::stod(value1));
        std::cout << "Tissue Y rotation parsed from config file! Value = " << tissue_rotation.getY() << std::endl;
    }
    else if(key1.compare("tissuerotz") == 0)
    {
        tissue_rotation.setZ(std::stod(value1));
        std::cout << "Tissue Z rotation parsed from config file! Value = " << tissue_rotation.getZ() << std::endl;
    }

    //Tissue Size
    else if (key1.compare("tissuesizex") == 0)
    {
        tissue_Dimension.setX(std::stod(value1));
        std::cout << "Tissue X size set from config file! Value = " << tissue_Dimension.getX() << std::endl;
    }
    else if (key1.compare("tissuesizey") == 0)
    {
        tissue_Dimension.setY(std::stod(value1));
        std::cout << "Tissue Y size set from config file! Value = " << tissue_Dimension.getY() << std::endl;
    }
    else if (key1.compare("tissuesizez") == 0)
    {
        tissue_Dimension.setZ(std::stod(value1));
        std::cout << "Tissue Z size set from config file! Value = " << tissue_Dimension.getZ() << std::endl;
    }

    //---Bone-----------------------------------------------------------------------------------------------------
    //Bone size
    else if (key1.compare("bonesizex") == 0)
    {
        bone_Dimension.setX(std::stod(value1));
        std::cout << "Bone X size set from config file! Value = " << bone_Dimension.getX() << std::endl;
    }
    else if (key1.compare("bonesizey") == 0)
    {
        bone_Dimension.setY(std::stod(value1));
        std::cout << "Bone Y size set from config file! Value = " << bone_Dimension.getY() << std::endl;
    }
    else if (key1.compare("bonesizez") == 0)
    {
        bone_Dimension.setZ(std::stod(value1));
        std::cout << "Bone Z size set from config file! Value = " << bone_Dimension.getZ() << std::endl;
    }

    //Bone position
    else if(key1.compare("bonepositionx") == 0)
    {
        bone_position.setX(std::stod(value1));
        std::cout << "Bone X position parsed from config file! Value = " << bone_position.getX() << std::endl;
    }
    else if(key1.compare("bonepositiony") == 0)
    {
        bone_position.setY(std::stod(value1));
        std::cout << "Bone Y position parsed from config file! Value = " << bone_position.getY() << std::endl;
    }
    else if(key1.compare("bonepositionz") == 0)
    {
        bone_position.setZ(std::stod(value1));
        std::cout << "Bone Z position parsed from config file! Value = " << bone_position.getZ() << std::endl;
    }

    else if(key1.compare("targettype") == 0)
    {
        target_type = std::stoi(value1);
        std::cout << "Target type parsed from config file! Value = " << target_type << std::endl;
    }

    //Guide
    else if (key1.compare("guidelength") == 0)
    {
        guide_length = std::stod(value1);
        std::cout << "Guide length Z set from config file! Value = " << guide_length << std::endl;
    }
    else if (key1.compare("guideradius") == 0)
    {
        guide_radius = std::stod(value1);
        std::cout << "Guide length Z set from config file! Value = " << guide_radius << std::endl;
    }

    //Grid
    else if (key1.compare("gridlength") == 0)
    {
        grid_length = std::stod(value1);
        std::cout << "Grid length Z set from config file! Value = " << grid_length << std::endl;
    }
    else if (key1.compare("gridwidth") == 0)
    {
        grid_width = std::stod(value1);
        std::cout << "Grid width set from config file! Value = " << grid_width << std::endl;
    }

    //Sipm left or right
    else if (key1.compare("sipmleft") == 0)
    {
        if (std::stod(value1) != 0)
        {
            sipm_left = true;
            std::cout << "SiPM is on the left." << std::endl;
        }
        else
        {
            sipm_left = false;
            std::cout << "SiPM is on the right." << std::endl;
        }
    }

    //Check overlaps or not
    else if (key1.compare("checkoverlaps") == 0)
    {
        if (std::stod(value1) != 0)
        {
            checkOverlaps = true;
            std::cout << "Set to check overlaps." << std::endl;
        }
        else
        {
            checkOverlaps = false;
            std::cout << "Set to NOT check overlaps." << std::endl;
        }
    }
}

void SiPMParameters::CheckValues()
{
    if(x_division <= 0)
    {
        std::cout << "X division is at least 1, setting back the default value." << std::endl;
        x_division = 1;
    }
    if(y_division <= 0)
    {
        std::cout << "Y division is at least 1, setting back the default value." << std::endl;
        y_division = 1;
    }
    /*if(scint_radius*2 > sipm_Dimension.getX() || scint_radius*2 > sipm_Dimension.getY())
    {
        std::cout << "Scintillator diameter can not be larger than the SiPM, ";
        if(sipm_Dimension.getX() < sipm_Dimension.getY())
        {
            scint_radius = sipm_Dimension.getX() / 2;
            std::cout << "changed to " << scint_radius * 2 << std::endl;
        }
        else
        {
            scint_radius = sipm_Dimension.getY() / 2;
            std::cout << "changed to " << scint_radius * 2 << std::endl;
        }
    }
    */
}
