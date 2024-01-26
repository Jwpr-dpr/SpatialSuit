#include "G4UserRunAction.hh"
#include "RunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4RootAnalysisManager.hh"

RunAction::RunAction() : G4UserRunAction()
{}

RunAction::~RunAction() 
{}

void RunAction::BeginOfRunAction(const G4Run* run)
{
  G4RootAnalysisManager* analysisManager = G4RootAnalysisManager::Instance();
  G4String fileName = "Humanito_espacial.root";
  analysisManager->OpenFile(fileName);

  analysisManager->CreateH1("Energía", "Histograma de Energía", 100.,0.,100.);
  analysisManager->CreateH1("Trayectoria", "Histograma de trayectoria", 100.,0.,100.);

}

void RunAction::EndOfRunAction(const G4Run* run)
{
  G4RootAnalysisManager* analysisManager = G4RootAnalysisManager::Instance();

  // save histograms & ntuple
  //
  analysisManager->Write();
  analysisManager->CloseFile();
}
