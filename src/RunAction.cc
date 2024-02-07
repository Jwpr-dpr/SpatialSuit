//Archivo RunAction.cc del proyecto Spatial Suit.
//
//Este archivo nos permitirá controlar las acciones que debe realizar la
//aplicación al finalizar su ejecución. En este caso vamos a guardar los
//valores de energía depositados en el cuerpo y la trayectoria de las 
//partículas cargadas al interior del mismo.


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

//Al iniciar el run, lo primero que se hará es crear el archivo que 
//almacenará los valores recolectados por la aplicación.
void RunAction::BeginOfRunAction(const G4Run* run)
{
  G4RootAnalysisManager* analysisManager = G4RootAnalysisManager::Instance();
  G4String fileName = "Humanito_espacial.root";
  analysisManager->OpenFile(fileName);
  //Por medio de la herramienta AnalysisManager crearemos los contenedores
  //de los datos, en este caso serán histogramas.
  analysisManager->CreateH1("Energía", "Histograma de Energía", 100.,0.,100.);
  analysisManager->CreateH1("Trayectoria", "Histograma de trayectoria", 100.,0.,100.);

}

void RunAction::EndOfRunAction(const G4Run* run)
{
  G4RootAnalysisManager* analysisManager = G4RootAnalysisManager::Instance();

  // save histograms & ntuple
  //Al finalizar escribimos y cerramos el archivo.
  analysisManager->Write();
  analysisManager->CloseFile();
}
