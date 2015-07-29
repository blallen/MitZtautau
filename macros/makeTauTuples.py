from MitAna.TreeMod.bambu import mithep, analysis
import os

mitdata = os.environ['MIT_DATA']

goodPV = mithep.GoodPVFilterMod(
    MinVertexNTracks = 0,
    MinNDof = 4,
    MaxAbsZ = 24.,
    MaxRho = 2.,
    IsMC = True,
    VertexesName = mithep.Names.gkPVBrn
)

Mods = []

pfPU = mithep.SeparatePileUpMod(
    PFNoPileUpName = "pfNoPU",
    PFPileUpName = "pfPU",
    CheckClosestZVertex = False
)
Mods.append(pfPU)

tauIdMod = mithep.PFTauIdMod('TauPtCut20','TauPtCut20')
tauIdMod.SetInputName('HPSTaus')
tauIdMod.SetOutputName('TausPt20')
tauIdMod.SetIsFilterMode(True)
tauIdMod.SetPtMin(20.)
tauIdMod.SetEtaMax(2.5)
tauIdMod.SetIsHPSSel(True)
# tauIdMod.AddDiscriminator(discriminator[1])
# Mods.append(tauIdMod)


discriminators = [ ('DecayModeFindingOldDMs', mithep.PFTau.kDiscriminationByDecayModeFindingOldDMs),
                   ('DecayModeFindingNewDMs', mithep.PFTau.kDiscriminationByDecayModeFindingNewDMs),
                   ('LooseCombinedIsolationDBSumPtCorr3Hits', mithep.PFTau.kDiscriminationByLooseCombinedIsolationDBSumPtCorr3Hits),
                   ('MediumCombinedIsolationDBSumPtCorr3Hits', mithep.PFTau.kDiscriminationByMediumCombinedIsolationDBSumPtCorr3Hits),
                   ('TightCombinedIsolationDBSumPtCorr3Hits', mithep.PFTau.kDiscriminationByTightCombinedIsolationDBSumPtCorr3Hits),
                   ('RawCombinedIsolationDBSumPtCorr3Hits', mithep.PFTau.kDiscriminationByRawCombinedIsolationDBSumPtCorr3Hits),
                   ('LooseMuonRejection3', mithep.PFTau.kDiscriminationByLooseMuonRejection3),
                   ('TightMuonRejection3', mithep.PFTau.kDiscriminationByTightMuonRejection3),
                   ('MVA5VLooseElectronRejection', mithep.PFTau.kDiscriminationByMVA5VLooseElectronRejection),
                   ('MVA5LooseElectronRejection', mithep.PFTau.kDiscriminationByMVA5LooseElectronRejection),
                   ('MVA5MediumElectronRejection', mithep.PFTau.kDiscriminationByMVA5MediumElectronRejection) 
                   ]

for discriminator in discriminators:
    tauIdMod = mithep.PFTauIdMod(discriminator[0],discriminator[0])
    # tauIdMod.SetInputName('TausPt20') 
    tauIdMod.SetInputName('HPSTaus')
    tauIdMod.SetOutputName(discriminator[0])
    tauIdMod.SetIsFilterMode(False)
    tauIdMod.SetPtMin(20.)
    tauIdMod.SetEtaxoMax(2.5)
    tauIdMod.SetIsHPSSel(True)
    tauIdMod.AddDiscriminator(discriminator[1])
    Mods.append(tauIdMod)
    print 'Added '+discriminator[0]+' to Mods'

ZtautauMod = mithep.ZtautauMod()
ZtautauMod.SetMCParticlesName("MCParticles")
# ZtautauMod.SetTausName('TausPt20')
ZtautauMod.SetTausName("HPSTaus")
for discriminator in discriminators:
    ZtautauMod.AddTauIdFlag(discriminator[0],discriminator[1])
Mods.append(ZtautauMod)

seq = goodPV
for Mod in Mods:
    seq *= Mod
analysis.setSequence(seq)
