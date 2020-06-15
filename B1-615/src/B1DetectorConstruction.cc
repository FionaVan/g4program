//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh" 
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
  //color
  //
  G4VisAttributes *red = new G4VisAttributes(G4Colour(1., 0., 0.,0.1));//red
  G4VisAttributes *green = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0,0.1));//green
  G4VisAttributes *blue = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0,0.2));//blue
  G4VisAttributes *yellow = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0,0.2));//yellow
  G4VisAttributes *white = new G4VisAttributes(G4Colour());//white
  G4VisAttributes *cyan = new G4VisAttributes(G4Colour(0.0, 1.0, 1.0,0.5));//cyan
  G4VisAttributes *magenta = new G4VisAttributes(G4Colour(1.0, 0.0, 1.0,0.5));//Magenta
  G4VisAttributes * color[]={red,green,blue,yellow,cyan,magenta};
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
G4NistManager* nist_manager = G4NistManager::Instance(); 
  //elements
 G4Element* elC = nist_manager->FindOrBuildElement("C");
 G4Element* elS = nist_manager->FindOrBuildElement("S");
 G4Element* elN = nist_manager->FindOrBuildElement("N");
 G4Element* elO = nist_manager->FindOrBuildElement("O");
 G4Element* elCl = nist_manager->FindOrBuildElement("Cl");
	G4Element* elNa = nist_manager->FindOrBuildElement("Na");
	G4Element* elP = nist_manager->FindOrBuildElement("P");
	G4Element* elCr = nist_manager->FindOrBuildElement("Cr");
	G4Element* elMn = nist_manager->FindOrBuildElement("Mn");
	G4Element* elFe = nist_manager->FindOrBuildElement("Fe");
	G4Element* elNi = nist_manager->FindOrBuildElement("Ni");
	G4Element* elMo = nist_manager->FindOrBuildElement("Mo");//Z42
	G4Element* elW = nist_manager->FindOrBuildElement("W");//Z74
	G4Material* Ge = nist_manager->FindOrBuildMaterial("G4_Cd");//Cd, not Cr

	//WuNieTie 18.0*g / cm3	
	G4Material* WuNieTie = new G4Material("WuNieTie",
		18.0*g / cm3, 3,
		kStateSolid);
	WuNieTie->AddElement(elFe, 2. * perCent);
	WuNieTie->AddElement(elNi, 2. * perCent);
	WuNieTie->AddElement(elW, 96. * perCent);	
	//SiO2: 2.32 g/cm3
	G4Material* SiO2 = nist_manager->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
	//H2O:1 g/cm3
	G4Material* H2O = nist_manager->FindOrBuildMaterial("G4_WATER");
	//Al2O3: 3.97g/cm3
	G4Material* Al2O3 = nist_manager->FindOrBuildMaterial("G4_ALUMINUM_OXIDE");
	//TiO2: 4.26 g/cm3
	G4Material* TiO2 = nist_manager->FindOrBuildMaterial("G4_TITANIUM_DIOXIDE");
	//Fe2O3: 5.2 g/cm3
	G4Material* Fe2O3 = nist_manager->FindOrBuildMaterial("G4_FERRIC_OXIDE");
	//CaCO3: 2.6 g/cm3
	G4Material* CaCO3 = nist_manager->FindOrBuildMaterial("G4_CALCIUM_CARBONATE");
       	//MgCO3: 2.958g/cm3
	 G4Material* MgCO3 = nist_manager->FindOrBuildMaterial("G4_MAGNESIUM_CARBONATE");
	//Na2O: 2.27 g/cm3
	G4Material* Na2O = nist_manager->FindOrBuildMaterial("G4_SODIUM_MONOXIDE");

	//K2O:2.32 g/cm3
	G4Material* K2O = nist_manager->FindOrBuildMaterial("G4_POTASSIUM_OXIDE");

	//P2O5 0.9 g/cm3
	G4Material* P2O5 = new G4Material("P2O5", 0.9*g / cm3, 2);
	P2O5->AddElement(elP, 2);
	P2O5->AddElement(elO, 5);
	//MnO2: 5.026g/cm3
	G4Material* MnO2 = new G4Material("MnO2", 5.026*g / cm3, 2);
	MnO2->AddElement(elMn, 1);
	MnO2->AddElement(elO, 2);
	//NaCl 2.16 g/cm3
	G4Material* NaCl = new G4Material("NaCl", 2.16*g / cm3, 2);
	NaCl->AddElement(elCl, 1);
	NaCl->AddElement(elNa, 1);
	//HuiYan: 2.703 g/cm3
	G4Material *HuiYan = new G4Material("HuiYan", 2.703*g/cm3, 11);
	HuiYan->AddMaterial(SiO2, 1.3*perCent);
	HuiYan->AddMaterial(H2O, 0.05*perCent);
	HuiYan->AddMaterial(Al2O3, 0.54*perCent);
	HuiYan->AddMaterial(TiO2, 0.01*perCent);
	HuiYan->AddMaterial(Fe2O3, 0.12*perCent);
	HuiYan->AddMaterial(CaCO3, 96.16*perCent);
	HuiYan->AddMaterial(MgCO3, 1.67*perCent);
	HuiYan->AddMaterial(K2O, 0.01*perCent);
	HuiYan->AddMaterial(P2O5, 0.11*perCent);
	HuiYan->AddMaterial(MnO2, 0.01*perCent);
	HuiYan->AddMaterial(Na2O, 0.02*perCent);
	//P550 7.85 g/cm3
	G4Material* P550 = new G4Material("P550", 7.85*g / cm3, 9);
	P550->AddElement(elC, 0.06*perCent);
	P550->AddElement(elS, 0.02*perCent);
	P550->AddElement(elCr, 19.5*perCent);
	P550->AddElement(elMo, 0.5*perCent);
	P550->AddElement(elN, 0.35*perCent);
	P550->AddElement(elFe, 57.935*perCent);
	P550->AddElement(elMn, 21.0*perCent);
	P550->AddElement(elP, 0.035*perCent);
	P550->AddElement(elNi, 0.6*perCent);
	//WuNieTie
	WuNieTie = new G4Material("WuNieTie",
		18.0*g / cm3, 3,
		kStateSolid);
	WuNieTie->AddElement(elFe, 2. * perCent);
	WuNieTie->AddElement(elNi, 2. * perCent);
	WuNieTie->AddElement(elW, 96. * perCent);
  //formation-material
  //kuanghuadu
  //density=HuiYan(1-pu_precent)+pu_precent cause the fractionmass of NaCl is little 
  G4double frac_water = 0.5; 
  G4double frac_NaCl = 0.00025;// 0.25*10(-3);0.2*10(-3)
  G4double KHD_density=2.703*(1- frac_water)+ frac_water;
  G4Material*  KuangHuaDu = new G4Material("KuangHuaDu", KHD_density, 3);
  KuangHuaDu->AddMaterial(HuiYan,(1- frac_water)*100*perCent);
  KuangHuaDu->AddMaterial(H2O,(frac_water-frac_NaCl)*100*perCent);
  KuangHuaDu->AddMaterial(NaCl,frac_NaCl*100*perCent);
  // Envelope parameters
  //
 
  //G4Material* env_mat = nist->FindOrBuildMaterial("HuiYan");
   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_oR = 1*m;
  G4double world_hz  = 2.5*m;

  G4Tubs* solidWorld =    
    new G4Tubs("World",0,world_oR,                      //its name
	       world_hz, 0*deg, 360*deg);     //its size
       
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        KuangHuaDu,           //its material
                        "World");            //its name
  // logicWorld->SetVisAttributes(white);                                              
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
               //     


  // well
  //  
  G4double well_oR = 10*cm, well_hz = 2.*m;
  G4Material* well_mat = nist->FindOrBuildMaterial("G4_WATER");
   
  G4Tubs* solidwell =    
    new G4Tubs("well",0,well_oR,                      //its name
	       well_hz, 0*deg, 360*deg                   //its name
        ); //its size
      
  G4LogicalVolume* logicwell =                         
    new G4LogicalVolume(solidwell,            //its solid
                        well_mat,             //its material
                        "well");         //its name
  logicwell->SetVisAttributes(color[1]);             
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicwell,                //its logical volume
                    "well",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  
  //     
  // shell-waike
  //  
	//G4Material* shape1_mat = nist->FindOrBuildMaterial("G4_A-150_TISSUE");
  G4ThreeVector pos1 = G4ThreeVector(0, 0, 0);
        
  // Conical section shape       
  G4double shell_oR =  9.5*cm, shell_hz = 1.5*m;
  G4double shell_iR =  0*cm;
  G4Tubs* solidshell =    
    new G4Tubs("shell", shell_iR,
    shell_oR, shell_hz,
	       0*deg,360*deg);
             
  G4LogicalVolume* logicshell =                         
    new G4LogicalVolume(solidshell,         //its solid
                        P550,          //its material
                        "shell");           //its name
  logicshell->SetVisAttributes(color[2]);    //its colour           
  new G4PVPlacement(0,                       //no rotation
                    pos1,                    //at position
                    logicshell,             //its logical volume
                    "shell",                //its name
                    logicwell,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  // nijiangtongdao
  //  
 G4double inwell_oR = 1*cm, inwell_hz = 1.3*m;

   
  G4Tubs* solidinwell =    
    new G4Tubs("inwell",0,inwell_oR,                      //its name
	       inwell_hz, 0*deg, 360*deg                   //its name
); //its size
      
  G4LogicalVolume* logicinwell =                         
    new G4LogicalVolume(solidinwell,            //its solid
                        well_mat,             //its material
                        "nijiangtongdao");         //its name
   
  logicinwell->SetVisAttributes(blue);             
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicshell,                //its logical volume
                    "nijiangtongdao",              //its name
                    logicwell,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
		    checkOverlaps);       //overlaps checking
//pingbiti
//在源和探测器之间
 G4double PBT_oR = 9*cm, PBT_hz = 3.*cm;

   
  G4Tubs* solidPBT =    
    new G4Tubs("PBT",1.*cm,PBT_oR,                      //its name
	       PBT_hz, 0*deg, 360*deg                   //its name
); //its size
      
  G4LogicalVolume* logicPBT =                         
    new G4LogicalVolume(solidPBT,            //its solid
                        WuNieTie,             //its material
                        "PBT");         //its name
   
  logicinwell->SetVisAttributes(color[4]);             
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,5.*cm),         //at (0,0,0)
                    logicPBT,                //its logical volume
                    "PBT",              //its name
                    logicshell,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
		    checkOverlaps);       //overlaps checking


  // scintillation_s
  //
  G4Isotope* IsotopeHe3 = new G4Isotope("He3", 2, 3, 3.0*g / mole);
  G4Element* elHe3 = new G4Element("Helium-3", "He3", 1);
  elHe3->AddIsotope(IsotopeHe3, 1);
  G4Material *He3 = new G4Material("He3", 0.001345*g / cm3, 1, kStateGas);
  He3->AddElement(elHe3, 100.0*perCent);

 
  G4double  scintillation_siR =  0.*cm, scintillation_soR= 1.215*cm;
  G4double  scintillation_shz =  8.35*cm;   
   
  G4Tubs* solidShape2 =    
    new G4Tubs("s_s",                      //its name
              scintillation_siR,scintillation_soR, 
             scintillation_shz,0*deg, 360*deg); //its size

  //s_s1
  G4LogicalVolume* logicss1 =                         
    new G4LogicalVolume(solidShape2,         //its solid
			He3,          //its material
                        "s1");  
    G4ThreeVector pos2 = G4ThreeVector(6*cm, 0*cm, 25*cm);     
    new G4PVPlacement(0,                       //no rotation
                    pos2,                    //at position
                    logicss1,             //its logical volume
                    "s1",                //its name
                    logicshell,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking     

   //     
  // scintillation_l11
  //               
  G4LogicalVolume* logicsl_11 =                         
    new G4LogicalVolume(solidShape2,         //its solid
			He3,          //its material
                        "l11");           //its name
  logicsl_11->SetVisAttributes(color[3]);    //its colour   
  G4ThreeVector pos3 = G4ThreeVector(6*cm, -1.5*cm,57*cm);                   
  new G4PVPlacement(0,                       //no rotation
                    pos3,                    //at position
                    logicsl_11,             //its logical volume
                    "l11",                //its name
                    logicshell,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
   //     
  // scintillation_l_12
  //               
  G4LogicalVolume* logicsl_12 =                         
    new G4LogicalVolume(solidShape2,         //its solid
			He3,          //its material
                        "l12");           //its name
  logicsl_12->SetVisAttributes(color[4]);    //its colour   
  G4ThreeVector pos4 = G4ThreeVector(6*cm, 1.5*cm,57*cm);                   
  new G4PVPlacement(0,                       //no rotation
                    pos4,                    //at position
                    logicsl_12,             //its logical volume
                    "l12",                //its name
                    logicshell,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  //s_s2
  G4LogicalVolume* logicss2 =                         
    new G4LogicalVolume(solidShape2,         //its solid
			He3,          //its material
                        "s2");  
  logicss2->SetVisAttributes(color[5]);    //its colour 
    G4ThreeVector pos5 = G4ThreeVector(-6*cm, 0*cm, 25*cm);     
    new G4PVPlacement(0,                       //no rotation
                    pos5,                    //at position
                    logicss2,             //its logical volume
                    "s2",                //its name
                    logicshell,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking  
   //     
  // scintillation_l21
  //               
  G4LogicalVolume* logicsl_21 =                         
    new G4LogicalVolume(solidShape2,         //its solid
			He3,          //its material
                        "l21");           //its name
  logicsl_21->SetVisAttributes(color[5]);    //its colour   
  G4ThreeVector pos6 = G4ThreeVector(-6*cm, 1.5*cm,57*cm);                   
  new G4PVPlacement(0,                       //no rotation
                    pos6,                    //at position
                    logicsl_21,             //its logical volume
                    "l21",                //its name
                    logicshell,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking 
   //     
  // scintillation_l_22
  //               
  G4LogicalVolume* logicsl_22 =                         
    new G4LogicalVolume(solidShape2,         //its solid
			He3,          //its material
                        "l22");           //its name
  logicsl_22->SetVisAttributes(yellow);    //its colour   
  G4ThreeVector pos7 = G4ThreeVector(-6*cm, -1.5*cm,57*cm);                   
  new G4PVPlacement(0,                       //no rotation
                    pos7,                    //at position
                    logicsl_22,             //its logical volume
                    "l22",                //its name
                    logicshell,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


 //
  G4double  ge_siR =  1.215*cm, ge_soR= 1.345*cm;
  G4double  ge_shz =  8.5*cm;   
   
  G4Tubs* solidge =    
    new G4Tubs("ge",                      //its name
              ge_siR,ge_soR, 
             ge_shz,0*deg, 360*deg); //its size  
   G4LogicalVolume* logicsge1 =                         
    new G4LogicalVolume(solidge,         //its solid
			Ge,          //its material
                        "ge1");   
  logicsge1->SetVisAttributes(white);    //its colour     
  new G4PVPlacement(0,                       //no rotation
                    pos2, //at position
                    logicsge1,             //its logical volume
                    "ge1",                //its name
                    logicshell,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking  

   G4LogicalVolume* logicsge2 =                         
    new G4LogicalVolume(solidge,         //its solid
			Ge,          //its material
                        "ge2");   
  logicsge2->SetVisAttributes(white);    //its colour     
  new G4PVPlacement(0,                       //no rotation
                    pos3, //at position
                    logicsge2,             //its logical volume
                    "ge2",                //its name
                    logicshell,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking  
  //ge3
   G4LogicalVolume* logicsge3 =                         
    new G4LogicalVolume(solidge,         //its solid
			Ge,          //its material
                        "ge3");   
  logicsge3->SetVisAttributes(cyan);    //its colour     
  new G4PVPlacement(0,                       //no rotation
                    pos4, //at position
                    logicsge3,             //its logical volume
                    "ge3",                //its name
                    logicshell,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking  

  //
  //ge4
   G4LogicalVolume* logicsge4 =                         
    new G4LogicalVolume(solidge,         //its solid
			Ge,          //its material
                        "ge4");   
  logicsge4->SetVisAttributes(cyan);    //its colour     
  new G4PVPlacement(0,                       //no rotation
                    pos5, //at position
                    logicsge4,             //its logical volume
                    "ge4",                //its name
                    logicshell,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking  
  //          //
  //ge5
   G4LogicalVolume* logicsge5 =                         
    new G4LogicalVolume(solidge,         //its solid
			Ge,          //its material
                        "ge5");   
  logicsge5->SetVisAttributes(cyan);    //its colour     
  new G4PVPlacement(0,                       //no rotation
                    pos6, //at position
                    logicsge5,             //its logical volume
                    "ge5",                //its name
                    logicshell,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking  
  //          //
  //ge6
   G4LogicalVolume* logicsge6 =                         
    new G4LogicalVolume(solidge,         //its solid
			Ge,          //its material
                        "ge6");   
  logicsge6->SetVisAttributes(cyan);    //its colour     
  new G4PVPlacement(0,                       //no rotation
                    pos7, //at position
                    logicsge6,             //its logical volume
                    "ge6",                //its name
                    logicshell,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking  
 
  //        
  //        
  // Set Shape2 as scoring volume
  //

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
