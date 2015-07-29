#include "MitZtautau/Mods/interface/ZtautauMod.h" 

#include "MitAna/DataCont/interface/Types.h"
#include "MitAna/DataTree/interface/PFTauCol.h"
#include "MitAna/DataTree/interface/PFTau.h"
#include "MitAna/DataTree/interface/MCParticle.h"
#include "MitAna/DataTree/interface/MCParticleCol.h"

#include "MitCommon/MathTools/interface/MathUtils.h"

#include "TMath.h"
#include "TLorentzVector.h"

#include <iostream>

ClassImp(mithep::ZtautauMod)
// using namespace mithep;
void
mithep::ZtautauMod::Process()
{

  fNumTaus = 0;

  // std::cout << "Start" << std::endl;

  // load objects
  auto* genParts = GetObject<mithep::MCParticleCol>(fMCParticlesName);
  auto* taus = GetObject<mithep::PFTauCol>(fTausName);
  mithep::NFArrBool *tauIdFlags[fNumTauIds];
  for (UInt_t i0 = 0; i0 < fNumTauIds;i0++) {
    tauIdFlags[i0] = GetObject<mithep::NFArrBool>(fTauIdFlagNames[i0]);
  }

  // std::cout << "Loaded objects" << std::endl;

  // check that everything loaded
  if (!genParts) {
    std::cerr << "Failed to load gen particles" << std::endl;
    return;
  }
  if (!taus) {
    std::cerr << "Failed to load taus" << std::endl;
    return;
  }
  for (UInt_t i0 = 0; i0 < fNumTauIds;i0++) {
    if (!tauIdFlags[i0]) {
      std::cerr << "Failed to load tauIdFlag " << fTauIdFlagNames[i0] << std::endl;
      return;
    }
  }
  
  // std::cout << "Checked loaded objects" << std::endl;

  TLorentzVector genTauAll, genTauNeu, genTauVis;
  // get gen taus and save
  for (unsigned iG(0); iG != genParts->GetEntries(); ++iG) {
    mithep::MCParticle const& genPart(*genParts->At(iG));
    if (TMath::Abs(genPart.PdgId()) != 15) continue;
    // if (!genPart.StatusFlag(13)) continue; //kIsLastCopy
    //this particle is the last copy of the particle in the chain with the same pdg id
    //(and therefore is more likely, but not guaranteed, to carry the final physical momentum)  
    if (genPart.FindDaughter(genPart.PdgId(),true)) continue;
    if (TMath::Abs(genPart.DistinctMother()->PdgId()) != 23) continue;

    genTauAll.SetPtEtaPhiE(genPart.Pt(), genPart.Eta(), genPart.Phi(), genPart.E());

    mithep::MCParticle const *neu = genPart.FindDaughter(16,false);
    if (neu) {
      genPart.Print(TString("l"));
      genTauNeu.SetPtEtaPhiE(neu->Pt(), neu->Eta(), neu->Phi(), neu->E());
      genTauVis = genTauAll - genTauNeu;

      fGenTauNeuPt[fNumTaus] = neu->Pt();
      fGenTauNeuEta[fNumTaus] = neu->Eta();
      fGenTauNeuPhi[fNumTaus] = neu->Phi();
      fGenTauNeuEnergy[fNumTaus] = neu->E();
    }
    else {

      genTauVis = genTauAll;

      fGenTauNeuPt[fNumTaus] = -9.99;
      fGenTauNeuEta[fNumTaus] = -9.99;
      fGenTauNeuPhi[fNumTaus] = -9.99;
      fGenTauNeuEnergy[fNumTaus] = -9.99;
    }

    // fill the branches
    fTauMatchedToGen[fNumTaus] = true;
    fGenTauPt[fNumTaus] = genTauVis.Pt(); // genPart.Pt();
    fGenTauEta[fNumTaus] = genTauVis.Eta(); // genPart.Eta();
    fGenTauPhi[fNumTaus] = genTauVis.Phi(); // genPart.Phi();
    fGenTauEnergy[fNumTaus] = genTauVis.E(); // genPart.E();
    fGenTauCharge[fNumTaus] = genPart.Charge();


    fTauDeltaR[fNumTaus] = 999999.;
    // fTauDeltaPt[fNumTaus] = 999999.;
    
    fTauMatchedToPF[fNumTaus] = false;
    fPFTauPt[fNumTaus] = -9.99;
    fPFTauEta[fNumTaus] = -9.99;
    fPFTauPhi[fNumTaus] = -9.99;
    fPFTauEnergy[fNumTaus] = -9.99;
    fPFTauCharge[fNumTaus] = -9.99;
                                                                   
    for (unsigned iD(0); iD < fNumTauIds; iD++) {                                       
      fTauDiscrimPass[iD][fNumTaus] = -1.;
      fTauDiscrimVals[iD][fNumTaus] = -1.;
    }

    Float_t DeltaR; // , DeltaPt;
    UInt_t numPfTausMatched = 0;
    //  Bool_t genMatched;
    // get pf taus and save
    for (unsigned iT(0); iT != taus->GetEntries(); ++iT) {
      mithep::PFTau const& tau(*taus->At(iT));
      
      // check if matched to a gen tau
      // genMatched = false;
      
      DeltaR = mithep::MathUtils::DeltaR(tau.Phi(),tau.Eta(),fGenTauPhi[fNumTaus],fGenTauEta[fNumTaus]);
      if (DeltaR < fTauDeltaR[fNumTaus]) fTauDeltaR[fNumTaus] = DeltaR;
      if (!fTauMatchedToGen[fNumTaus]) continue;
      if (tau.Charge() != fGenTauCharge[fNumTaus]) continue;
      // std::cout << "deltaR is: " << DeltaR << std::endl;
      if (fTauDeltaR[fNumTaus] > 0.15) continue; // dR = 0.15
      // genMatched = true;
      // std::cout << "passed iso cut" << std::endl;
      // DeltaPt = TMath::Abs(tau.Pt() - fGenTauPt[fNumTaus]);
      // if (DeltaPt > fTauDeltaPt[fNumTaus]) continue;
      // fTauDeltaPt[fNumTaus] = DeltaPt;
      if (tau.Pt() < fPFTauPt[fNumTaus]) continue;
      
      // re-fill the branches with pf info
      fTauMatchedToPF[fNumTaus] = true;
      fPFTauPt[fNumTaus] = tau.Pt();
      fPFTauEta[fNumTaus] = tau.Eta();
      fPFTauPhi[fNumTaus] = tau.Phi();
      fPFTauEnergy[fNumTaus] = tau.E();
      fPFTauCharge[fNumTaus] = tau.Charge();
      
      numPfTausMatched++;

      // pass the discrims
      for (unsigned iD(0); iD < fNumTauIds; iD++) {
	fTauDiscrimPass[iD][fNumTaus] = tauIdFlags[iD]->At(iT);
	fTauDiscrimVals[iD][fNumTaus] = tau.PFTauDiscriminator(fTauIdFlagEnums[iD]);
      }
      
    }
    
    hPfTausMatched->Fill(numPfTausMatched);

    fNumTaus++;

    if (fNumTaus == fMaxExpNumTaus) break;
  }

  fTree->Fill();

  // std::cout << "Filled tree" << std::endl;
}

void
mithep::ZtautauMod::SlaveBegin()
{
  fTree = new TTree("ZttTree", "ZttTree");

  fTree->Branch("nTaus",&fNumTaus,"nTaus/i");

  fTree->Branch("TauMatchedToGen",fTauMatchedToGen,"TauMatchedToGen[nTaus]/O");
  fTree->Branch("GenTauPt",fGenTauPt,"GenTauPt[nTaus]/F");
  fTree->Branch("GenTauEta",fGenTauEta,"GenTauEta[nTaus]/F");
  fTree->Branch("GenTauPhi",fGenTauPhi,"GenTauPhi[nTaus]/F");
  fTree->Branch("GenTauEnergy",fGenTauEnergy,"GenTauEnergy[nTaus]/F");
  fTree->Branch("GenTauCharge",fGenTauCharge,"GenTauCharge[nTaus]/I");
  
  fTree->Branch("GenTauNeuPt",fGenTauNeuPt,"GenTauNeuPt[nTaus]/F");
  fTree->Branch("GenTauNeuEta",fGenTauNeuEta,"GenTauNeuEta[nTaus]/F");
  fTree->Branch("GenTauNeuPhi",fGenTauNeuPhi,"GenTauNeuPhi[nTaus]/F");
  fTree->Branch("GenTauNeuEnergy",fGenTauNeuEnergy,"GenTauNeuEnergy[nTaus]/F");

  fTree->Branch("TauDeltaR",fTauDeltaR,"TauDeltaR[nTaus]/F");
  // fTree->Branch("TauDeltaPt",fTauDeltaPt,"TauDeltaPt[nTaus]/F");

  fTree->Branch("TauMatchedToPF",fTauMatchedToPF,"TauMatchedToPF[nTaus]/O");
  fTree->Branch("PFTauPt",fPFTauPt,"PFTauPt[nTaus]/F");
  fTree->Branch("PFTauEta",fPFTauEta,"PFTauEta[nTaus]/F");
  fTree->Branch("PFTauPhi",fPFTauPhi,"PFTauPhi[nTaus]/F");
  fTree->Branch("PFTauEnergy",fPFTauEnergy,"PFTauEnergy[nTaus]/F");
  fTree->Branch("PFTauCharge",fPFTauCharge,"PFTauCharge[nTaus]/I");

  for (unsigned iId(0); iId != fNumTauIds; ++iId) {
    fTree->Branch(fTauIdFlagNames[iId] + "Pass", fTauDiscrimPass[iId], fTauIdFlagNames[iId] + "Pass[nTaus]/F");
    fTree->Branch(fTauIdFlagNames[iId] + "Vals", fTauDiscrimVals[iId], fTauIdFlagNames[iId] + "Vals[nTaus]/F");
  }
  /*
  fTree->Branch("NumTauIds",&fNumTauIds,"fNumTauIds/i");
  fTree->Branch("TauIdFlagNames",fTauIdFlagNames,"fTauIdFlagNames[fNumTauIds]/C");
  fTree->Branch("TauDiscrimVals",fTauDiscrimVals,"fTauDiscrimVals[nTaus][fNumTauIds]");
  */
  AddOutput(fTree);

  AddTH1(hPfTausMatched, "pftausmatched", "# of PF Taus matched to a Gen Tau", 40, 0., 40.);

}
