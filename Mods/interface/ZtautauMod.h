#ifndef MITZTAUTAU_MODS_ZTAUTAUMOD_H
#define MITZTAUTAU_MODS_ZTAUTAUMOD_H

#include <vector>

#include "MitAna/TreeMod/interface/BaseMod.h"
#include "MitAna/DataTree/interface/Names.h"


#include "TString.h" 
#include "TH1D.h"
#include "TTree.h"

namespace mithep {

  class ZtautauMod : public BaseMod {
  public:
  ZtautauMod(char const* name = "ZtautauMod", char const* title = "Z->tautau CR module") : BaseMod(name, title) {}
    ~ZtautauMod() {}
    
    char const* GetMCParticlesName() const { return fMCParticlesName; }
    char const* GetTausName() const { return fTausName; }
    UInt_t GetNumTauIds() const { return fNumTauIds; }
    char const* GetTauIdFlagName(UInt_t i) const { return fTauIdFlagNames[i]; }

    void SetMCParticlesName(char const* n) { fMCParticlesName = n; }
    void SetTausName(char const* n) { fTausName = n; }
    // void SetNumTauIds(UInt_t n) { fNumTauIds = n; }
    void AddTauIdFlag(char const* n, Int_t v) { fTauIdFlagNames[fNumTauIds] = n; fTauIdFlagEnums[fNumTauIds] = v; fNumTauIds++; }
    
    
  protected:
    void Process() override;
    void SlaveBegin() override;
    
    TString fMCParticlesName = "MCParticles";
    TString fTausName = mithep::Names::gkHPSTauBrn; // "HPSTaus";
    
    static const UInt_t fMaxExpNumTaus = 64;

    UInt_t fNumTauIds = 0;
    TString fTauIdFlagNames[64];
    UInt_t fTauIdFlagEnums[64];
    
    TTree *fTree = 0;

    UInt_t fNumTaus = 0;

    Bool_t fTauMatchedToGen[fMaxExpNumTaus];
    Float_t fGenTauPt[fMaxExpNumTaus];
    Float_t fGenTauEta[fMaxExpNumTaus];
    Float_t fGenTauPhi[fMaxExpNumTaus];
    Float_t fGenTauEnergy[fMaxExpNumTaus];
    Int_t fGenTauCharge[fMaxExpNumTaus];

    Float_t fGenTauNeuPt[fMaxExpNumTaus];
    Float_t fGenTauNeuEta[fMaxExpNumTaus];
    Float_t fGenTauNeuPhi[fMaxExpNumTaus];
    Float_t fGenTauNeuEnergy[fMaxExpNumTaus];

    Float_t fTauDeltaR[fMaxExpNumTaus];
    // Float_t fTauDeltaPt[fMaxExpNumTaus];

    Bool_t fTauMatchedToPF[fMaxExpNumTaus];
    Float_t fPFTauPt[fMaxExpNumTaus];
    Float_t fPFTauEta[fMaxExpNumTaus];
    Float_t fPFTauPhi[fMaxExpNumTaus];
    Float_t fPFTauEnergy[fMaxExpNumTaus];
    Int_t fPFTauCharge[fMaxExpNumTaus];

    Float_t fTauDiscrimPass[64][fMaxExpNumTaus]; // fTDP[nTauId][nTau]
    Float_t fTauDiscrimVals[64][fMaxExpNumTaus]; // fTDV[nTauId][nTau]

    TH1F* hPfTausMatched = 0;

    ClassDef(ZtautauMod, 0)
      };

}

#endif
