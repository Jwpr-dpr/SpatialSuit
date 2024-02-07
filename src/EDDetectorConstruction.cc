//Archivo EDDetectorConstruction.cc del proyecto Spatial Suit.
//
//Este archivo contiene la construcción de cada una de las geometrías 
//involucradas en el proyecto, es decir, todo lo que tiene un cuerpo 
//solido. Estos son el traje espacial y el cuerpo humano con cada organo.


#include "EDDetectorConstruction.hh"
#include "G4Sphere.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4UnionSolid.hh"
#include "G4Material.hh"
#include "G4SDManager.hh"
#include "G4Ellipsoid.hh"
#include "G4EllipticalTube.hh"
#include "G4Cons.hh"
#include "globals.hh"
#include "G4SubtractionSolid.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EDDetectorConstruction::EDDetectorConstruction()
: G4VUserDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EDDetectorConstruction::~EDDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* EDDetectorConstruction::Construct()
{  
  // Obtener el nist material manager para importar cada material
  G4NistManager* nistManager = G4NistManager::Instance();
  
  // contruir cada material y almacenarlo en una variable
  G4Material* galactic = nistManager->FindOrBuildMaterial("G4_Galactic");
  G4Material* soft = nistManager->FindOrBuildMaterial("G4_TISSUE_SOFT_ICRP");
  G4Material* skeleton = nistManager->FindOrBuildMaterial("G4_B-100_BONE");
  G4Material* suit_material = nistManager->FindOrBuildMaterial("G4_POLYETHYLENE");
  G4Material* muscle = nistManager->FindOrBuildMaterial("G4_MUSCLE_WITHOUT_SUCROSE");

       // There is no need to test if materials were built/found
       // as G4NistManager would issue an error otherwise
       // Try the code with "XYZ".      
  
  // Esta opción es para ayudarnos a garantizar una adecuada ubicación de
  //cada organo, de modo que no permitira que se sobrepongan unos con otros
   G4bool checkOverlaps = true;

  //     
  // World
  //
  // Definición del mundo. Espacio físico que contendrá cada elemento de la
  //aplicación
  G4Box* worldS = new G4Box("World", 3.*m, 3.*m,3.*m); 
      
  G4LogicalVolume* worldLV                         
    = new G4LogicalVolume(worldS, galactic, "World");
                                   
  G4VPhysicalVolume* worldPV
    = new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      worldLV,               //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0);                    //copy number
                                             //overlaps checking

  auto* rm = new G4RotationMatrix();
  rm->rotateX(180.*deg);
  rm->rotateY(180.*deg);

  //
  //Super Traje espacial 
  //Casco
  G4VSolid* sphere = new G4Sphere("Sphere",0.,17.*cm,
                                   0.,360.*deg,0.,180.*deg);
  
   G4VSolid* cube = new G4Box("cube",20.*cm,20*cm,20.*cm);



  G4VSolid* helmetS = new G4SubtractionSolid("helmet_solid",sphere,cube,
                                 0, G4ThreeVector(0.,0.,-33.*cm));
  
  G4LogicalVolume* logic_helmet 
    = new G4LogicalVolume(helmetS,suit_material,"helmet_logical");

  G4VPhysicalVolume* helmet = 
    new G4PVPlacement(rm,G4ThreeVector(0.,0.,77.75*cm),
                      logic_helmet,
                      "helmet_physical",
                      worldLV,
                      false,
                      0);
  //
  //Tronco
  G4VSolid* bodysuitS = new G4EllipticalTube("bodysuit_solid",22.*cm,12.*cm,30.5*cm);

  G4LogicalVolume* logicbodysuit
    = new G4LogicalVolume(bodysuitS,suit_material,"bodysuit_logical");

  G4VPhysicalVolume* bodysuit = new G4PVPlacement(rm,
                             G4ThreeVector(0,0,35.*cm),
                             logicbodysuit,
                             "bodysuit_physical",
                             worldLV,
                             false,
                             0);
  //Piernas del traje
  
  //Pierna I
  //Pierna I
  G4VSolid* left_suitlegS = new G4Cons("leftsuitLeg_solid",0.,4.*cm,0.,12.*cm,42.0*cm,
                                    0,360.*deg);

  G4LogicalVolume* logic_suitleft_leg = new G4LogicalVolume(left_suitlegS,
                                                  suit_material,"left_suitleg_logical");

  G4VPhysicalVolume* left_suitleg = new G4PVPlacement(rm,
                                    G4ThreeVector(10.*cm,0.*cm,-37.*cm),
                                    logic_suitleft_leg,
                                    "left_suitleg_physical",
                                    worldLV,
                                    false,
                                    0);

   G4VPhysicalVolume* right_leg = new G4PVPlacement(rm,
                                    G4ThreeVector(-10.*cm,0.*cm,-37.*cm),
                                    logic_suitleft_leg,
                                    "right_leg_physical",
                                    worldLV,
                                    false,
                                    0);
  
  //Brazos del traje
   G4VSolid* left_suitarmS = new G4EllipticalTube("leftsuitarm_solid",2.4*cm * 2.,4.7*cm * 2.,36.5*cm);

  G4LogicalVolume* logic_leftsuit_arm = new G4LogicalVolume(left_suitarmS,
                                                  suit_material,"left_suitarm_logical");

  G4VPhysicalVolume* left_suitarm = new G4PVPlacement(rm,
                                    G4ThreeVector(23.*cm,0.*cm,27.5*cm),
                                    logic_leftsuit_arm,
                                    "left_suitarm_physical",
                                    worldLV,
                                    false,
                                    0); 
  
  G4VPhysicalVolume* right_suitarm = new G4PVPlacement(rm,
                                    G4ThreeVector(-23.*cm,0.*cm,27.5*cm),                                        logic_leftsuit_arm,
                                    "left_suitarm_physical",
                                    worldLV,
                                    false,
                                    0);
  //
  // Humanito xd
  //
  //Cabeza
  G4Color pink(1,0.89,0.8);

  //G4HumanPhantomMaterial* material = new G4HumanPhantomMaterial();

  //G4Material* soft = material -> GetMaterial("soft_tissue");

  G4VSolid* headS = new G4Sphere("Head_solid",0.,15.*cm,
                                 0.,360.*deg,0,180.*deg);

  G4LogicalVolume* logicHead 
    = new G4LogicalVolume(headS,muscle,"Head_logical");

  G4VPhysicalVolume* head
    = new G4PVPlacement(rm,
                       G4ThreeVector(0.,0.,0),
                       logicHead,
                       "Head_physical",
                       logic_helmet,
                       false,
                       0);

  G4VisAttributes* headVisAtt = new G4VisAttributes(pink);
  logicHead->SetVisAttributes(headVisAtt);

  //Cerebro
  G4Color red(1.0,0.,0.);
  G4VSolid* brainS = new G4Sphere("Brain_solid",0.,10.*cm,
                                0.,270.*deg,0,180.*deg);

  G4LogicalVolume* logicBrain
    = new G4LogicalVolume(brainS,soft,"Brain_logical");

  G4VPhysicalVolume* brain
    = new G4PVPlacement(rm,
                       G4ThreeVector(),
                       logicBrain,
                       "Brain_physical",
                       logicHead,
                       false,
                       0);

  G4VisAttributes* brainVisAtt = new G4VisAttributes(red);
  brainVisAtt->SetForceSolid(true);
  brainVisAtt->SetVisibility(true);
  logicBrain->SetVisAttributes(brainVisAtt);

  // Torso
  G4VSolid* trunkS = new G4EllipticalTube("Trunk_solid",20.*cm,10.*cm,28.5*cm);
  
  G4LogicalVolume* logicTrunk
    = new G4LogicalVolume(trunkS,muscle,"Trunk_logical");
  
  G4VPhysicalVolume* trunk = new G4PVPlacement(rm,
                             G4ThreeVector(0,0,0),
                             logicTrunk,
                             "Trunk_physical",
                             logicbodysuit,
                             false,
                             0);
  
  G4VisAttributes* trunkVisAtt = new G4VisAttributes(pink);
  logicTrunk->SetVisAttributes(trunkVisAtt);
  //Pulmones
  //Izquierdo
  //G4Material* lung_material = material -> GetMaterial("lung_material");
  
  G4VSolid* left_lungS = new G4Ellipsoid("left_lung_solid",5.*cm,7.5*cm,20.*cm,
                                    0.0*cm,24.*cm);

  G4LogicalVolume* logic_left_lung = new G4LogicalVolume(left_lungS,
                                         soft, "left_Lung_logical");

  G4VPhysicalVolume* left_lung = new G4PVPlacement(rm,
                                 G4ThreeVector(8.5*cm,0.0,4.*cm),
                                 logic_left_lung,
                                 "left_lung_physical",
                                 logicTrunk,
                                 false,
                                 0);
  
  G4VisAttributes* lLungVisAtt = new G4VisAttributes(red);
  lLungVisAtt->SetForceSolid(true);
  lLungVisAtt->SetVisibility(true);
  logic_left_lung->SetVisAttributes(lLungVisAtt);


  //Derecho
  G4VSolid* right_lungS = new G4Ellipsoid("right_lung_solid",5.*cm,7.5*cm,20.*cm,
                                    0.0*cm,24.*cm);

  G4LogicalVolume* logic_right_lung = new G4LogicalVolume(right_lungS,
                                         soft, "right_Lung_logical");

  G4VPhysicalVolume* right_lung = new G4PVPlacement(rm,
                                 G4ThreeVector(-8.5*cm,0.0,4.*cm),
                                 logic_right_lung,
                                 "right_lung_physical",
                                 logicTrunk,
                                 false,
                                 0);

  G4VisAttributes* rLungVisAtt = new G4VisAttributes(red);
  rLungVisAtt->SetForceSolid(true);
  rLungVisAtt->SetVisibility(true);
  logic_right_lung->SetVisAttributes(rLungVisAtt);
  

  //Corazón <3
  G4Color purple(0.62,0.12,0.94);
  G4VSolid* heartS = new G4Ellipsoid("heart_solid",4.*cm,4*cm,7.*cm,
                                    -7.0*cm,0.*cm);

  G4LogicalVolume* logicheart = new G4LogicalVolume(heartS,
                                         soft, "heart_logical");

  G4VPhysicalVolume* heart = new G4PVPlacement(rm,
                                 G4ThreeVector(0*cm,0.0,15.*cm),
                                 logicheart,
                                 "heart_physical",
                                 logicTrunk,
                                 false,
                                 0);

  G4VisAttributes* heartVisAtt = new G4VisAttributes(purple);
  heartVisAtt->SetForceSolid(true);
  heartVisAtt->SetVisibility(true);
  logicheart->SetVisAttributes(heartVisAtt);

  //Estómago
  G4Color yellow(1,1,0);
  auto* rm_est = new G4RotationMatrix();
  rm_est->rotateY(180.*deg);
  
  G4VSolid* stomachS = new G4Ellipsoid("stomach_solid",4.*cm,3*cm,4.*cm);

  G4LogicalVolume* logicstomach = new G4LogicalVolume(stomachS,
                                         soft, "stomach_logical");

  G4VPhysicalVolume* stomach = new G4PVPlacement(rm_est,
                                 G4ThreeVector(-7.*cm,0.0,-2.*cm),
                                 logicstomach,
                                 "stomach_physical",
                                 logicTrunk,
                                 false,
                                 0);

  G4VisAttributes* stomachVisAtt = new G4VisAttributes(yellow);
  stomachVisAtt->SetForceSolid(true);
  stomachVisAtt->SetVisibility(true);
  logicstomach->SetVisAttributes(stomachVisAtt);


  //Hígado
  G4Color brown(0.58,0.29,0);
  
  G4VSolid* liverS = new G4Ellipsoid("liver_solid",8.*cm,4*cm,4.*cm);

  G4LogicalVolume* logicliver = new G4LogicalVolume(liverS,
                                         soft, "liver_logical");

  G4VPhysicalVolume* liver = new G4PVPlacement(rm,
                                 G4ThreeVector(5.*cm,0.0,-2.*cm),
                                 logicliver,
                                 "liver_physical",
                                 logicTrunk,
                                 false,
                                 0);

  G4VisAttributes* liverVisAtt = new G4VisAttributes(brown);
  liverVisAtt->SetForceSolid(true);
  liverVisAtt->SetVisibility(true);
  logicliver->SetVisAttributes(liverVisAtt);
  

  //Intestino (los dos intestinos son una caja de intestino general)
   G4Color green(0,1,0);

  G4VSolid* intestineS = new G4Box("intestine_solid",14.*cm,4*cm,6.*cm);

  G4LogicalVolume* logicintestine = new G4LogicalVolume(intestineS,
                                         soft, "intestine_logical");

  G4VPhysicalVolume* intestine = new G4PVPlacement(rm,
                                 G4ThreeVector(0,0.0,-14.*cm),
                                 logicintestine,
                                 "intestine_physical",
                                 logicTrunk,
                                 false,
                                 0);

  G4VisAttributes* intestineVisAtt = new G4VisAttributes(green);
  intestineVisAtt->SetForceSolid(true);
  intestineVisAtt->SetVisibility(true);
  logicintestine->SetVisAttributes(intestineVisAtt);

  // Piernas 

  //Pierna I
  G4VSolid* left_legS = new G4Cons("leftLeg_solid",0.,2.*cm,0.,10.*cm,40.0*cm,
                                    0,360.*deg);

  G4LogicalVolume* logic_left_leg = new G4LogicalVolume(left_legS,
                                                  muscle,"left_leg_logical");

  G4VPhysicalVolume* left_leg = new G4PVPlacement(rm,
                                    G4ThreeVector(0,0,2),
                                    logic_left_leg,
                                    "left_leg_physical",
                                    logic_suitleft_leg,
                                    false,
                                    0);

  G4VisAttributes* lLegVisAtt = new G4VisAttributes(pink);
  logic_left_leg->SetVisAttributes(lLegVisAtt);

  //Hueso-Pierna
  G4Color white(1,1,1);
  G4VSolid* leg_boneS = new G4Cons("legBone_solid",0.,1.*cm,0.,3.5*cm,39.*cm,
                                    0.,360.*deg);

  G4LogicalVolume* logic_leg_bone = new G4LogicalVolume(leg_boneS,
                                                 skeleton, "leg_bone_logical");

  G4VPhysicalVolume* leg_bone = new G4PVPlacement(0,
                                    G4ThreeVector(),
                                    logic_leg_bone,
                                    "leg_bone_physical",
                                    logic_left_leg,
                                    false,
                                    0);
  
  G4VisAttributes* legBoneVisAtt = new G4VisAttributes(white);
  legBoneVisAtt->SetForceSolid(true);
  legBoneVisAtt->SetVisibility(true);
  logic_leg_bone->SetVisAttributes(legBoneVisAtt);

  
  
  //Brazos
  

  //Brazo I
  G4VSolid* left_armS = new G4EllipticalTube("leftarm_solid",1.4*cm * 2.,2.7*cm * 2.,34.5*cm);

  G4LogicalVolume* logic_left_arm = new G4LogicalVolume(left_armS,
                                                  muscle,"left_arm_logical");

  G4VPhysicalVolume* left_arm = new G4PVPlacement(rm,
                                    G4ThreeVector(0,0,2.*cm),
                                    logic_left_arm,
                                    "left_arm_physical",
                                    logic_leftsuit_arm,
                                    false,
                                    0);

  G4VisAttributes* larmVisAtt = new G4VisAttributes(pink);
  logic_left_arm->SetVisAttributes(larmVisAtt);

  //Hueso-Brazo
  G4VSolid* arm_boneS = new G4EllipticalTube("armBone_solid",1.4*cm,2.7*cm,34.7*cm);

  G4LogicalVolume* logic_arm_bone = new G4LogicalVolume(arm_boneS,
                                                 skeleton, "arm_bone_logical");

  G4VPhysicalVolume* arm_bone = new G4PVPlacement(0,
                                    G4ThreeVector(),
                                    logic_arm_bone,
                                    "arm_bone_physical",
                                    logic_left_arm,
                                    false,
                                    0);

  G4VisAttributes* armBoneVisAtt = new G4VisAttributes(white);
  armBoneVisAtt->SetForceSolid(true);
  armBoneVisAtt->SetVisibility(true);
  logic_arm_bone->SetVisAttributes(armBoneVisAtt);

  G4VSensitiveDetector* trunkDetector = new SensitiveDetector("TrunkSD");
  //G4SDManager::GetSDMPointer()->AddNewDetector(trunkDetector);
  logicTrunk->SetSensitiveDetector(trunkDetector);
  logic_left_lung->SetSensitiveDetector(trunkDetector);
  logic_right_lung->SetSensitiveDetector(trunkDetector);
  logicheart->SetSensitiveDetector(trunkDetector);
  logicstomach->SetSensitiveDetector(trunkDetector);
  logicliver->SetSensitiveDetector(trunkDetector);
  logicintestine->SetSensitiveDetector(trunkDetector);


  
    
  return worldPV;
}

//....oooOO 0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
