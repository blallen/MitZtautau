import ROOT
ROOT.gROOT.SetBatch(True)

ROOT.gSystem.Load('libMitAnaDataTree.so')
ROOT.gSystem.Load('libMitPhysicsMods.so')
ROOT.gSystem.Load('libMitZtautauMods.so')

mithep = ROOT.mithep

analysis = mithep.Analysis()
analysis.SetOutputName('ntuples_taus.root')
analysis.SetKeepHierarchy(False)

# analysis.AddFile('/mnt/hadoop/cms/store/user/paus/filefi/032/SingleElectron+Run2012A-22Jan2013-v1+AOD/3EE27797-3773-E211-B2A6-00266CF27430.root')
analysis.AddFile('/mnt/hadoop/cms/store/user/paus/filefi/032/s12-zll-ptz100-v7c/001B91CE-7639-E211-B7D1-00261894385A.root')
analysis.SetProcessNEvents(10000)

Mods = []

hltMod = mithep.HLTMod()
hltMod.SetBitsName('HLTBits')
hltMod.SetTrigObjsName('SingleElectronTriggerObjects')
hltMod.AddTrigger('HLT_Ele27_WP80_v*')
# Mods.append[hltMod]

goodPVMod = mithep.GoodPVFilterMod()
goodPVMod.SetMinVertexNTracks(0)
goodPVMod.SetMinNDof(4)
goodPVMod.SetMaxAbsZ(24.0)
goodPVMod.SetMaxRho(2.0)
goodPVMod.SetIsMC(False)
goodPVMod.SetVertexesName('PrimaryVertexes')
goodPVMod.SetOutputName('GoodVertexes')
Mods.append(goodPVMod)
print 'Added GoodPVFilterMod to Mods'

discriminators = { 'DecayModeFindingOldDMs' : mithep.PFTau.kDiscriminationByDecayModeFindingOldDMs,
                   'DecayModeFindingNewDMs' : mithep.PFTau.kDiscriminationByDecayModeFindingNewDMs,
                   'LooseCombinedIsolationDBSumPtCorr3Hits' : mithep.PFTau.kDiscriminationByLooseCombinedIsolationDBSumPtCorr3Hits,
                   'MediumCombinedIsolationDBSumPtCorr3Hits' : mithep.PFTau.kDiscriminationByMediumCombinedIsolationDBSumPtCorr3Hits,
                   'TightCombinedIsolationDBSumPtCorr3Hits' : mithep.PFTau.kDiscriminationByTightCombinedIsolationDBSumPtCorr3Hits,
                   'RawCombinedIsolationDBSumPtCorr3Hits' : mithep.PFTau.kDiscriminationByRawCombinedIsolationDBSumPtCorr3Hits,
                   'LooseMuonRejection3' : mithep.PFTau.kDiscriminationByLooseMuonRejection3,
                   'TightMuonRejection3' : mithep.PFTau.kDiscriminationByTightMuonRejection3,
                   'MVA5VLooseElectronRejection' : mithep.PFTau.kDiscriminationByMVA5VLooseElectronRejection,
                   'MVA5LooseElectronRejection' : mithep.PFTau.kDiscriminationByMVA5LooseElectronRejection,
                   'MVA5MediumElectronRejection' : mithep.PFTau.kDiscriminationByMVA5MediumElectronRejection 
                   }

for key, discriminator in discriminators.iteritems():
    tauIdMod = mithep.PFTauIdMod(key,key)
    # generic id stuff
    tauIdMod.SetInputName('HPSTaus')
    tauIdMod.SetOutputName(key)
    tauIdMod.SetIsFilterMode(False)
    tauIdMod.SetPtMin(20.)
    tauIdMod.SetEtaMax(2.5)
    tauIdMod.SetIsHPSSel(True)
    tauIdMod.AddDiscriminator(discriminator)
    Mods.append(tauIdMod)
    print 'Added '+key+' to Mods'

ZtautauMod = mithep.ZtautauMod()
ZtautauMod.SetMCParticlesName("MCParticles")
ZtautauMod.SetTausName("HPSTaus")
for key, discriminator in discriminators.iteritems():
    ZtautauMod.AddTauIdFlag(key,discriminator)
Mods.append(ZtautauMod)

### Add mods for analysis ###
analysis.AddSuperModule(goodPVMod)
# hltMod.Add(goodPVMod)
for Base,Attach in zip(Mods,Mods[1:]):
    Base.Add(Attach)
    # print str(Base), str(Attach)

analysis.Run(False)



"""
# tau id
tauIdMod = mithep.PFTauIdMod()
# generic id stuff
tauIdMod.SetInputName('PFTaus')
tauIdMod.SetOutputName('SelectedTaus')
tauIdMod.SetIsFilterMode(False)
tauIdMod.SetPtMin(20.)
tauIdMod.SetEtaMax(2.5)
# tauIdMod.SetIdType(UInt_t t) # was CustomTight for electrons
# tauIdMod.SetIsoType(UInt_t t) # PFIso ??
'''
tauIdMod.SetTriggerObjectsName(const char* n)       { fAuxInputNames[kTrigObjects] = n; }
tauIdMod.SetConversionsName(const char* n)          { fAuxInputNames[kConversions] = n; }
tauIdMod.SetElectronsName(const char* n)            { fAuxInputNames[kElectrons] = n; }
tauIdMod.SetVertexName(const char* n)               { fAuxInputNames[kVertices] = n; }
tauIdMod.SetBeamSpotName(const char* n)             { fAuxInputNames[kBeamSpot] = n; }
tauIdMod.SetPFCandidatesName(const char* n)         { fAuxInputNames[kPFCandidates] = n; }
tauIdMod.SetPFNoPileupCandidatesName(const char* n) { fAuxInputNames[kPFNoPileupCandidates] = n; }
tauIdMod.SetPFPileupCandidatesName(const char* n)   { fAuxInputNames[kPFPileupCandidates] = n; }
tauIdMod.SetPileupEnergyDensityName(const char* n)  { fAuxInputNames[kPileupEnergyDensity] = n; }
tauIdMod.SetNonIsolatedMuonsName(const char* n)     { fAuxInputNames[kNonIsolatedMuons] = n; }
tauIdMod.SetNonIsolatedElectronsName(const char* n) { fAuxInputNames[kNonIsolatedElectrons] = n; }
'''
# tau specific id stuff
tauIdMod.SetIsHPSSel(True)
tauIdMod.AddDiscriminator(kDiscriminationByDecayModeFindingOldDMs)
tauIdMod.AddDiscriminator(kDiscriminationByDecayModeFindingNewDMs) # for high pt only?
tauIdMod.AddDiscriminator(kDiscriminationByLooseCombinedIsolationDBSumPtCorr3Hits)
tauIdMod.AddDiscriminator(kDiscriminationByMediumCombinedIsolationDBSumPtCorr3Hits)
tauIdMod.AddDiscriminator(kDiscriminationByTightCombinedIsolationDBSumPtCorr3Hits)
tauIdMod.AddDiscriminator(kDiscriminationByRawCombinedIsolationDBSumPtCorr3Hits)
tauIdMod.AddDiscriminator(kDiscriminationByLooseMuonRejection3)
tauIdMod.AddDiscriminator(kDiscriminationByTightMuonRejection3)
tauIdMod.AddDiscriminator(kDiscriminationByMVA5VLooseElectronRejection)
tauIdMod.AddDiscriminator(kDiscriminationByMVA5LooseElectronRejection)
tauIdMod.AddDiscriminator(kDiscriminationByMVA5MediumElectronRejection)
# non-HPS settings
'''
tauIdMod.SetPtLeadChargedHadronPFCandMin(Double_t x) { fPtLeadChargedHadronPFCandMin = x; }
tauIdMod.SetIsoChargedHadronPtSumMax(Double_t x)     { fIsoChargedHadronPtSumMax = x; }
tauIdMod.SetIsoGammaEtSumMax(Double_t x)             { fIsoGammaEtSumMax = x; }
tauIdMod.SetSignalMassMin(Double_t x)                { fSignalMassMin = x; }
tauIdMod.SetSignalMassMax(Double_t x)                { fSignalMassMax = x; }
'''
"""
