#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"

int main(int argc, char** argv)
{
  G4RunManager* runManager = new G4RunManager;

  G4UIExecutive* ui = new G4UIExecutive(argc, argv);
  // Create visualization manager 
  G4VisManager* visManager = new G4VisExecutive;
  visManager -> Initialize();

  // Set MANDATORY initialization classes
  runManager -> SetUserInitialization(new DetectorConstruction);
  runManager -> SetUserInitialization(new PhysicsList);

  // Set MANDATORY user action class
  runManager -> SetUserAction(new PrimaryGeneratorAction);

  // Run the kernel
  runManager -> Initialize();
  
  // get pointer to UI manager and set verbosities
  G4UImanager* UI = G4UImanager::GetUIpointer();
  UI -> ApplyCommand("/control/execute init_vis.mac");
  ui -> SessionStart();
  delete ui;

  // start a run
  int numberOfEvents = 3;
  runManager -> BeamOn(numberOfEvents);

  // Cleanup
  delete runManager;
  delete visManager; 

  return 0;
}

/*
* DETECTOR CONSTRUCTION specifies GEOMETRY, MATERIALS, SENSITIVE REGIONS, and READOUT schemes of sensitive regions
* PARTICLE LIST (from G4VUserPhysicsList) requires user define PARTICLES being used, RANGE CUTS for particles, and ALL PHYSICS PROCESSES to be simulated
* 
* GEANT does not check for mandatory classes till initialize() and BeamOn() are invoked 
* 
* OPTIONAL USER CLASSES
* UserRunAction, EventAction, StackingAction, TrackingAction, SteppingAction
*/
