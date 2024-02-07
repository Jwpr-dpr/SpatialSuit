// Archivo PrimaryGeneratorAction.cc del Proyecto Spatial Suit
//
//Este archivo nos permite crear las acciones que ocurriran en nuestras
//simulaciones, en este caso, se creo una G4ParticleGun, que disparará
//partículas cargadas en direcciones aleatorias del espacio que abarca
//la simulación, y de igual manera se define el evento, herramienta para
//aleatorizar las direcciones en que se lance la partícula


#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4PrimaryParticle.hh"
#include "G4PrimaryVertex.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
#include "G4ParticleGun.hh"
#include "Randomize.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//Instancia de la ParticleGun
PrimaryGeneratorAction::PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction(),
      fParticleGun(0),
      fRandom(true) 
{   //Establecemos las partículas que se van a lanzar en la simulación
    std::vector<G4String> particleNames = {"mu-","proton","gamma"};
    G4int nofParticles = 1;

    for (G4String ParticleName : particleNames) {
        fParticleGun = new G4ParticleGun(nofParticles);
        G4String particleName = ParticleName;
        //Establecemos la posición desde la cuál se lanzaran las 
        //partículas y el momento de las mismas
        G4ThreeVector position(-0.2*m,2.9*m,-1.*m);
        G4ThreeVector momentum(0,0,1.*GeV);

        G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
        G4ParticleDefinition *particle
        = particleTable->FindParticle(ParticleName);
       fParticleGun->SetParticleDefinition(particle);
       fParticleGun->SetParticlePosition(position);
       fParticleGun->SetParticleMomentum(momentum);

       //delete fParticleGun;

   }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
  //this function is called at the begining of each event  //
  //La partícula se define como un evento aleatorio, con los siguientes
  //ángulos como parámetros de dirección del lanzamiento.
  if(fRandom){
    G4double dtheta = 10.*deg;
    G4double dphi = 50.*deg;
    G4double theta = G4UniformRand()*dtheta;
    G4double phi = G4UniformRand()*dphi;
    fParticleGun->SetParticleMomentumDirection(
    G4ThreeVector(theta, -1, phi));

  }
  else{
     fParticleGun->SetParticleMomentumDirection(
      G4ThreeVector(0,-1,0));
  }
  fParticleGun->GeneratePrimaryVertex(event);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

