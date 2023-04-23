#include <iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"

// #include "QGSP_BERT.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"

#include "SiPMParameters.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "QBBC.hh"
#include "QGSP_BIC_HP.hh"

#include "G4HadronPhysicsQGSP_BERT.hh"
#include "G4HadronPhysicsQGSP_BERT_HP.hh"
#include "G4HadronPhysicsQGSP_BIC.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4HadronPhysicsQGSP_FTFP_BERT.hh"
#include "G4HadronPhysicsQGS_BIC.hh"
#include "Randomize.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "G4ScoringManager.hh"

#include <ctime>

/*
int main(int argc, char **argv)
{

  G4RunManager *runManager = new G4RunManager();
  runManager->SetUserInitialization(new MyDetectorConstruction());
  runManager->SetUserInitialization(new MyPhysicsList());
  runManager->SetUserInitialization(new MyActionInitialization());

  runManager->Initialize();
  G4UIExecutive *ui = new G4UIExecutive(argc, argv);

  G4VisManager *visManager = new G4VisExecutive();
  visManager->Initialize();

  G4UImanager *UImanager = G4UImanager::GetUIpointer();
  UImanager->ApplyCommand("/vis/open OGL");
  UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
  UImanager->ApplyCommand("/vis/drawVolume");
  UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
  UImanager->ApplyCommand("vis/viewer/set/autoRefresh true");
  ui->SessionStart();

  return 0;
}
*/

int main(int argc, char **argv)
{
  time_t time_start = time(NULL);

  // Choose the Random engine
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);

  SiPMParameters &parameters = SiPMParameters::GetInstance();
  parameters.ParseConfigFile();

  // parameter from command line
  bool visualization = true;
  for (int i = 1; i < argc; i++)
  {
    if (!strcmp("-df", argv[i]))
    {
      std::cout << "Settings will be read from the default file." << std::endl;
      parameters.ParseConfigFile();
    }
    else if (!strcmp("-pf", argv[i]))
    {
      std::cout << "Settings will be read from the plotting file." << std::endl;
      parameters.ParseConfigFile("../config_forplot.conf");
    }
    else if (!strcmp("-f", argv[i]))
    {
      std::string filename;
      if (argc - 1 >= i + 1)
      {
        filename = argv[i + 1];
        std::cout << "Settings will be read from " << filename << "." << std::endl;
        parameters.ParseConfigFile(filename);
      }
      if (filename.empty())
      {
        std::cout << "File name not given, using the default values" << std::endl;
      }
    }
    else if (!strcmp("-v", argv[i]))
    {
      std::cout << "Visualization disabled." << std::endl;
      visualization = false;
    }
    // else if(!strcmp("-d", argv[i])) //datafile
    // {
    //     data_filename = argv[i+1];
    //     std::cout << "Using output file: " << data_filename << "." << std::endl;
    // }
  }

  // G4MTRunManager can't work with magnetic field crash with the Navigation
#ifdef G4MULTITHREADED
  unsigned nthreads = parameters.GetNumberOfThreads();
  G4MTRunManager *runManager = new G4MTRunManager;
  runManager->SetNumberOfThreads(nthreads);
  G4cout << "\n\n\thajlit running in multithreaded mode with " << nthreads
         << " threads\n\n"
         << G4endl;
#else
  G4RunManager *runManager = new G4RunManager;
  G4cout << "\n\n\t hajlit running in serial mode\n\n"
         << G4endl;
#endif

  // G4RunManager *runManager = new G4RunManager;

  // G4ScoringManager::GetScoringManager();

  runManager->SetUserInitialization(new MyDetectorConstruction());
  runManager->SetUserInitialization(new MyPhysicsList());
  runManager->SetUserInitialization(new MyActionInitialization());

  runManager->Initialize();

  // Initialize visualization

  G4VisManager *visManager{};
  if (visualization) // default
  {                  // interactive mode : define UI session
    visManager = new G4VisExecutive;
    visManager->Initialize();
  }

  // Get the pointer to the User Interface manager
  G4UIExecutive *ui = nullptr;
  if (visualization)
    ui = new G4UIExecutive(argc, argv);
  G4UImanager *UImanager = G4UImanager::GetUIpointer();
  UImanager->ApplyCommand("/control/macroPath ./macros"); // set for your environment
  if (visualization)
    UImanager->ApplyCommand("/control/execute vis.mac");

  if (parameters.IsScoring())
  {
    UImanager->ApplyCommand("/control/execute scoring_initialize.mac");
    runManager->BeamOn(parameters.GetNumberOfEvents());
    UImanager->ApplyCommand("/control/execute scoring_dump.mac");
  }
  else
    runManager->BeamOn(parameters.GetNumberOfEvents());

  if (visualization)
  {
    ui->SessionStart();
    delete visManager;
  }
  delete ui;
  delete runManager;

  time_t time_end = time(NULL);
  std::cout << "It took " << (double)(time_end - time_start) / 60.0 / 60.0 << " hours, i.e., "
            << (double)(time_end - time_start) / 60.0 << " minutes" << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
