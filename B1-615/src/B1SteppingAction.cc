
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
/// \file B1SteppingAction.cc
/// \brief Implementation of the B1SteppingAction class

#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "B1DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::B1SteppingAction(B1EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fEventAction1(eventAction),
  fScoringVolume(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::~B1SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1SteppingAction::UserSteppingAction(const G4Step* step)
{
  /*if (!fScoringVolume) { 
    const B1DetectorConstruction* detectorConstruction
      = static_cast<const B1DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();   
  }
 
  // check if we are in scoring volume
  if (volume != fScoringVolume) return;

  // collect energy deposited in this step
  G4double edepStep = step->GetTotalEnergyDeposit();
  fEventAction->AddEdep(edepStep);  
  */
  // get volume of the current step
     G4Track *track = step->GetTrack();
     G4String ParticleName =track->GetDynamicParticle()->GetParticleDefinition()->GetParticleName();

    const G4VPhysicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
    G4String VolumeName_Pre = "Out of World";
    if (volume) VolumeName_Pre = volume->GetName();

    const G4VPhysicalVolume *volume1 = step->GetPostStepPoint()->GetTouchableHandle()->GetVolume();
    G4String VolumeName_Post = "Out of World";
    if (volume1) VolumeName_Post = volume1->GetName();

     G4double NnumStep = 0.;
     G4double NnumStep1 = 0.;


     G4String particlename = step->GetTrack()->GetDefinition()->GetParticleName();
    //G4double TrackWeight = aStep->GetTrack()->GetWeight();
     G4double StepID = step->GetTrack()->GetCurrentStepNumber();
     G4int TrackID = step->GetTrack()->GetTrackID();
     G4double Energy = step->GetTrack()->GetKineticEnergy();
     G4int ParentTrackID = step->GetTrack()->GetParentID();
     G4double GlobalTime = step->GetTrack()->GetGlobalTime();
     G4ThreeVector momentum = step->GetTrack()->GetMomentumDirection();

     const G4VProcess *CurrentProcess = step->GetPostStepPoint()->GetProcessDefinedStep();
     G4String CurrentProcessName = "PrimaryGenerated";
     if (CurrentProcess) CurrentProcessName = CurrentProcess->GetProcessName();

	//Event
     const G4Event *aEvent = G4RunManager::GetRunManager()->GetCurrentEvent();
     G4int EventId = aEvent->GetEventID();
    //point
     G4ThreeVector presteppoint = step->GetPreStepPoint()->GetPosition();
     G4ThreeVector poststeppoint = step->GetPostStepPoint()->GetPosition();
     const G4VProcess *CreatorProcess = step->GetTrack()->GetCreatorProcess();
     G4String CreatorProcessName = "PrimaryGenerated";
     //G4String Rootprocess = "undefined";

    if (CreatorProcess) CreatorProcessName = CreatorProcess->GetProcessName();
  //   if (StepID == 1 && particlename == "neutron")// && ParentTrackID == 0  
	// {
	// 	std::fstream file("test.csv", std::ios::out | std::ios::app);
	// 	file  << "Particlename = " << particlename << " "
  //              << "ParentID = " << ParentTrackID << " "
  //              << "TrackID = " << TrackID << " "
  //              << "EventID = " << EventId << " "
  //              << "Energy = " << Energy << " "
  //              << "CreatorPross = " << CreatorProcessName << " "
  //              << "GlobalTime = " << GlobalTime << " "
  //              << "CurrentProcess = " << CurrentProcessName << " "
  //              << momentum.x()<<" "<<momentum.y()<<"  "<<momentum.z()<< G4endl;
	//        file.close();
	// }

    if ((particlename == "neutron") &&(VolumeName_Post== "s1") &&(VolumeName_Pre!="s1" ))//&&(Energy <= 0.1)
    {       
        std::fstream file("s1_Received.csv", std::ios::out | std::ios::app);
        file //<< "Energy // MeV " << "GlobalTime // ns "<< "x "<< "y "<< "z "<< "VolumeName_Post "<< "CreatorProcessName " <<"CurrentProcessName  "
             << " " << EventId << " " << TrackID
             << " " << Energy // MeV
             << " " << GlobalTime // ns
             << " " << poststeppoint.x() // mm
             << " " << poststeppoint.y() // mm
             << " " << poststeppoint.z() // mm
             << " " << VolumeName_Post
             << " " << CreatorProcessName
             << " " << CurrentProcessName 
	        << " " << StepID
	        << " " << ParentTrackID<<G4endl;
             step->GetTrack()->SetTrackStatus(fStopAndKill);
        file.close();
    }
    if ((particlename == "neutron") &&(VolumeName_Post== "s2") &&(VolumeName_Pre!="s2" ) )//&&(Energy <= 0.1)
    {       
        std::fstream file("s2_Received.csv", std::ios::out | std::ios::app);
        file  << " " << EventId << " " << TrackID
             << " " << EventId << " " << TrackID
             << " " << Energy // MeV
             << " " << GlobalTime // ns
             << " " << poststeppoint.x() // mm
             << " " << poststeppoint.y() // mm
             << " " << poststeppoint.z() // mm
             << " " << VolumeName_Post
             << " " << CreatorProcessName
             << " " << CurrentProcessName 
	        << " " << StepID
	        << " " << ParentTrackID<<G4endl;
             step->GetTrack()->SetTrackStatus(fStopAndKill);
        file.close();
    }


    if ((particlename == "neutron") &&(VolumeName_Post== "l11") &&(VolumeName_Pre!="l11" ) )//&&(Energy <= 0.1)
    {       
        std::fstream file("l11_Received.csv", std::ios::out | std::ios::app);
        file  << " " << EventId << " " << TrackID
             << " " << EventId << " " << TrackID
             << " " << Energy // MeV
             << " " << GlobalTime // ns
             << " " << poststeppoint.x() // mm
             << " " << poststeppoint.y() // mm
             << " " << poststeppoint.z() // mm
             << " " << VolumeName_Post
             << " " << CreatorProcessName
             << " " << CurrentProcessName 
	        << " " << StepID
	        << " " << ParentTrackID<<G4endl;
             step->GetTrack()->SetTrackStatus(fStopAndKill);
        file.close();
    }
    if ((particlename == "neutron") &&(VolumeName_Post== "l12") &&(VolumeName_Pre!="l12" ))//&&(Energy <= 0.1) 
    {       
        std::fstream file("l12_Received.csv", std::ios::out | std::ios::app);
      file   << " " << EventId << " " << TrackID
             << " " << Energy // MeV
             << " " << GlobalTime // ns
             << " " << poststeppoint.x() // mm
             << " " << poststeppoint.y() // mm
             << " " << poststeppoint.z() // mm
             << " " << VolumeName_Post
             << " " << CreatorProcessName
             << " " << CurrentProcessName 
	        << " " << StepID
	        << " " << ParentTrackID<<G4endl;
             step->GetTrack()->SetTrackStatus(fStopAndKill);
        file.close();
    }
    if ((particlename == "neutron") &&(VolumeName_Post== "l21") &&(VolumeName_Pre!="l21" ))//&&(Energy <= 0.1) 
    {       
        std::fstream file("l21_Received.csv", std::ios::out | std::ios::app);
        file 
             << " " << EventId << " " << TrackID
             << " " << Energy // MeV
             << " " << GlobalTime // ns
             << " " << poststeppoint.x() // mm
             << " " << poststeppoint.y() // mm
             << " " << poststeppoint.z() // mm
             << " " << VolumeName_Post
             << " " << CreatorProcessName
             << " " << CurrentProcessName 
	        << " " << StepID
	        << " " << ParentTrackID<<G4endl;
             step->GetTrack()->SetTrackStatus(fStopAndKill);
        file.close();
    }
    if ((particlename == "neutron") &&(VolumeName_Post== "l22") &&(VolumeName_Pre!="l22" ) )//&&(Energy <= 0.1)
    {       
        std::fstream file("l22_Received.csv", std::ios::out | std::ios::app);
        file 
             << " " << EventId << " " << TrackID
             << " " << Energy // MeV
             << " " << GlobalTime // ns
             << " " << poststeppoint.x() // mm
             << " " << poststeppoint.y() // mm
             << " " << poststeppoint.z() // mm
             << " " << VolumeName_Post
             << " " << CreatorProcessName
             << " " << CurrentProcessName 
	        << " " << StepID
	        << " " << ParentTrackID<<G4endl;
             step->GetTrack()->SetTrackStatus(fStopAndKill);
        file.close();
    }
 fEventAction->AddNnum(NnumStep);
 fEventAction1->AddNnum(NnumStep1);

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

