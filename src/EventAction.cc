//Archivo EventAction.cc del proyecto Spatial suit
//
//Este es un archivo muy básico, pero necesario debido a la jerarquia de
//funcionamiento de Geant4. Este nos permitirá iniciar las acciones 
//contenidas en el archivo RunAction.cc
 
#include "EventAction.hh"

#include "G4Run.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"
#include "G4RootAnalysisManager.hh"
#include "globals.hh"

#include "Randomize.hh"
#include <iomanip>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
EventAction::EventAction()
 : G4UserEventAction(),
   fRun(0)
{}

EventAction::~EventAction()
{}

void EventAction::SetRun(G4Run* run)
{
   fRun = run;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* /*event*/)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
