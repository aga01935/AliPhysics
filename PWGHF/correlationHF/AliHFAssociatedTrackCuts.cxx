/**************************************************************************
 * Copyright(c) 1998-2010, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

/* $Id$ */

////////////////////////////////////////////////////////////////////////
//
// Base class for cuts on Associated tracks for HF Correlation analysis
//
// Author: S.Bjelogrlic (Utrecht) sandro.bjelogrlic@cern.ch
////////////////////////////////////////////////////////////////////////
#include <Riostream.h>
#include "AliHFAssociatedTrackCuts.h"
#include "AliAODPidHF.h"
#include "AliESDtrackCuts.h"
#include "AliESDtrack.h"
#include "AliAODv0.h"
#include "AliAODVertex.h"
#include "AliAODMCParticle.h"
#include "TString.h"

using std::cout;
using std::endl;

ClassImp(AliHFAssociatedTrackCuts)

//--------------------------------------------------------------------------
AliHFAssociatedTrackCuts::AliHFAssociatedTrackCuts():
AliAnalysisCuts(),
fESDTrackCuts(0),
fPidObj(0),

fPoolMaxNEvents(0), 
fPoolMinNTracks(0), 
fMinEventsToMix(0),
fNzVtxBins(0), 
fNzVtxBinsDim(0), 
fZvtxBins(0), 
fNCentBins(0), 
fNCentBinsDim(0), 
fCentBins(0),

fNTrackCuts(0),
fAODTrackCuts(0),
fTrackCutsNames(0),
fNvZeroCuts(0),
fAODvZeroCuts(0),
fvZeroCutsNames(0)

{
	//
	//default constructor
	//
	//
	//default constructor
	//
	
}

//--------------------------------------------------------------------------
AliHFAssociatedTrackCuts::AliHFAssociatedTrackCuts(const char* name, const char* title):
AliAnalysisCuts(name,title),
fESDTrackCuts(0),
fPidObj(0),

fPoolMaxNEvents(0), 
fPoolMinNTracks(0), 
fMinEventsToMix(0),
fNzVtxBins(0), 
fNzVtxBinsDim(0), 
fZvtxBins(0), 
fNCentBins(0), 
fNCentBinsDim(0), 
fCentBins(0),

fNTrackCuts(0),
fAODTrackCuts(0),
fTrackCutsNames(0),
fNvZeroCuts(0),
fAODvZeroCuts(0),
fvZeroCutsNames(0)

{
	//
	//default constructor
	//
	
}
//--------------------------------------------------------------------------
AliHFAssociatedTrackCuts::AliHFAssociatedTrackCuts(const AliHFAssociatedTrackCuts &source) :
AliAnalysisCuts(source),
fESDTrackCuts(source.fESDTrackCuts),
fPidObj(source.fPidObj),

fPoolMaxNEvents(source.fPoolMaxNEvents), 
fPoolMinNTracks(source.fPoolMinNTracks), 
fMinEventsToMix(source.fMinEventsToMix),
fNzVtxBins(source.fNzVtxBins), 
fNzVtxBinsDim(source.fNzVtxBinsDim), 
fZvtxBins(source.fZvtxBins), 
fNCentBins(source.fNCentBins), 
fNCentBinsDim(source.fNCentBinsDim), 
fCentBins(source.fCentBins),

fNTrackCuts(source.fNTrackCuts),
fAODTrackCuts(source.fAODTrackCuts),
fTrackCutsNames(source.fTrackCutsNames),
fNvZeroCuts(source.fNvZeroCuts),
fAODvZeroCuts(source.fAODvZeroCuts),
fvZeroCutsNames(source.fvZeroCutsNames)
{
	//
	// copy constructor
	//
	

        AliInfo("AliHFAssociatedTrackCuts::Copy constructor ");
	if(source.fESDTrackCuts) AddTrackCuts(source.fESDTrackCuts);
	if(source.fAODTrackCuts) SetAODTrackCuts(source.fAODTrackCuts);
	if(source.fAODvZeroCuts) SetAODvZeroCuts(source.fAODvZeroCuts);
	if(source.fPidObj) SetPidHF(source.fPidObj);
}
//--------------------------------------------------------------------------
AliHFAssociatedTrackCuts &AliHFAssociatedTrackCuts::operator=(const AliHFAssociatedTrackCuts &source)
{
	//
	// assignment operator
	//	
	if(&source == this) return *this;
	
	AliAnalysisCuts::operator=(source);
	fESDTrackCuts=source.fESDTrackCuts;
	fPidObj=source.fPidObj;
	fNTrackCuts=source.fNTrackCuts;
	fAODTrackCuts=source.fAODTrackCuts;
	fTrackCutsNames=source.fTrackCutsNames;
	fNvZeroCuts=source.fNvZeroCuts;
	fAODvZeroCuts=source.fAODvZeroCuts;
	fvZeroCutsNames=source.fvZeroCutsNames;
	
	return *this;

}


//--------------------------------------------------------------------------
AliHFAssociatedTrackCuts::~AliHFAssociatedTrackCuts()
{
	if(fESDTrackCuts) {delete fESDTrackCuts; fESDTrackCuts = 0;}
	if(fPidObj) {delete fPidObj; fPidObj = 0;}
	if(fZvtxBins) {delete[] fZvtxBins; fZvtxBins=0;} 
	if(fCentBins) {delete[] fCentBins; fCentBins=0;}
	if(fAODTrackCuts) {delete[] fAODTrackCuts; fAODTrackCuts=0;}
	if(fTrackCutsNames) {delete[] fTrackCutsNames; fTrackCutsNames=0;}
	if(fAODvZeroCuts){delete[] fAODvZeroCuts; fAODvZeroCuts=0;}
	if(fvZeroCutsNames) {delete[] fvZeroCutsNames; fvZeroCutsNames=0;}
	
}
//--------------------------------------------------------------------------
Bool_t AliHFAssociatedTrackCuts::IsInAcceptance()
{
	printf("Careful: method AliHFAssociatedTrackCuts::IsInAcceptance is not implemented yet \n");
	return kFALSE;
}
//--------------------------------------------------------------------------
Bool_t AliHFAssociatedTrackCuts::IsHadronSelected(AliAODTrack * track)
{
	AliESDtrack esdtrack(track);
	if(!fESDTrackCuts->IsSelected(&esdtrack)) return kFALSE;
	return kTRUE;
	
}

//--------------------------------------------------------------------------
Bool_t AliHFAssociatedTrackCuts::CheckHadronKinematic(Double_t pt, Double_t d0) 
{
	
	
	
	if(pt < fAODTrackCuts[0]) return kFALSE;
	if(pt > fAODTrackCuts[1]) return kFALSE;
	if(d0 < fAODTrackCuts[2]) return kFALSE;
	if(d0 > fAODTrackCuts[3]) return kFALSE;
	
	return kTRUE;

	
}
//--------------------------------------------------------------------------
Bool_t AliHFAssociatedTrackCuts::CheckKaonCompatibility(AliAODTrack * track, Bool_t useMc, TClonesArray* mcArray, Int_t method)
{
	Bool_t isKaon = kFALSE;
	
	if(useMc) { // on MC
		Int_t hadLabel = track->GetLabel();
		if(hadLabel < 0) return kFALSE;
		AliAODMCParticle* hadron = dynamic_cast<AliAODMCParticle*>(mcArray->At(hadLabel));
		Int_t pdg = TMath::Abs(hadron->GetPdgCode()); 
		if (pdg == 321) isKaon = kTRUE;
	}
	
	if(!useMc) { // on DATA
          switch(method) {
	  case(1): {
		Bool_t isKTPC=kFALSE;
		Bool_t isPiTPC=kFALSE;
		Bool_t isPTPC=kFALSE;
		Bool_t isKTOF=kFALSE;
		Bool_t isPiTOF=kFALSE;
		Bool_t isPTOF=kFALSE;
		
		Bool_t KaonHyp = kFALSE;
		Bool_t PionHyp = kFALSE;
		Bool_t ProtonHyp = kFALSE;
		
		if(fPidObj->CheckStatus(track,"TOF")) {
			isKTOF=fPidObj->IsKaonRaw(track,"TOF");
			isPiTOF=fPidObj->IsPionRaw(track,"TOF");
			isPTOF=fPidObj->IsProtonRaw(track,"TOF");
		}
		if(fPidObj->CheckStatus(track,"TPC")){
			isKTPC=fPidObj->IsKaonRaw(track,"TPC");
			isPiTPC=fPidObj->IsPionRaw(track,"TPC");
			isPTPC=fPidObj->IsProtonRaw(track,"TPC");		
		}
		
		if (isKTOF && isKTPC) KaonHyp = kTRUE;
		if (isPiTOF && isPiTPC) PionHyp = kTRUE;
		if (isPTOF && isPTPC) ProtonHyp = kTRUE;
		
		if(KaonHyp && !PionHyp && !ProtonHyp) isKaon = kTRUE; 
	        break;
	      }
      case(2): {
		if(fPidObj->MakeRawPid(track,3)>=1) isKaon = kTRUE;
		break;
	      }
      }
	}
	
	return isKaon;
	
}
//--------------------------------------------------------------------------
Bool_t AliHFAssociatedTrackCuts::IsKZeroSelected(AliAODv0 *vzero, AliAODVertex *vtx1)
{
	
	if(vzero->DcaV0Daughters()>fAODvZeroCuts[0]) return kFALSE;
	if(vzero->Chi2V0()>fAODvZeroCuts[1]) return kFALSE;
	if(vzero->DecayLength(vtx1) < fAODvZeroCuts[2]) return kFALSE;
	if(vzero->DecayLength(vtx1) > fAODvZeroCuts[3]) return kFALSE;
	if(vzero->OpenAngleV0() > fAODvZeroCuts[4]) return kFALSE;
	if(vzero->Pt() < fAODvZeroCuts[5]) return kFALSE;
	if(TMath::Abs(vzero->Eta()) > fAODvZeroCuts[6]) return kFALSE;

	
	return kTRUE;
}
//--------------------------------------------------------------------------
Int_t AliHFAssociatedTrackCuts::IsMCpartFromHF(Int_t label, TClonesArray*mcArray){
  // Check origin in MC

  AliAODMCParticle* mcParticle;
  Int_t pdgCode = -1;
  if (label<0) return 0;
  Bool_t isCharmy = kFALSE;
  Bool_t isBeauty = kFALSE;
  Bool_t isD = kFALSE;
  Bool_t isB = kFALSE;

  while(pdgCode!=2212){ // loops back to the collision to check the particle source

    mcParticle = dynamic_cast<AliAODMCParticle*>(mcArray->At(label));
    if(!mcParticle) {AliError("NO MC PARTICLE"); break;}
    pdgCode =  TMath::Abs(mcParticle->GetPdgCode());

    label = mcParticle->GetMother();


    if((pdgCode>=400 && pdgCode <500) || (pdgCode>=4000 && pdgCode<5000 )) isD = kTRUE;
    if((pdgCode>=500 && pdgCode <600) || (pdgCode>=5000 && pdgCode<6000 )) {isD = kFALSE; isB = kTRUE;}


    if(pdgCode == 4) isCharmy = kTRUE;
    if(pdgCode == 5) {isBeauty = kTRUE; isCharmy = kFALSE;}
    if(label<0) break;

  }
  if (isCharmy && isD) return 44; // the first 4(5) indicates the charm/beauty quark, the second the charmy meson
  if (isBeauty && isD) return 54;
  if (isBeauty && isB) return 55;
  return 0;
}

//--------------------------------------------------------------------------
Bool_t AliHFAssociatedTrackCuts::InvMassDstarRejection(AliAODRecoDecayHF2Prong* d, AliAODTrack *track, Int_t hypD0) const {
	//
	// Calculates invmass of track+D0 and rejects if compatible with D*
	// (to remove pions from D*)
	// 
	Double_t nsigma = 3.;
	
	Double_t mD0, mD0bar;
	d->InvMassD0(mD0,mD0bar);
	
	Double_t invmassDstar1 = 0, invmassDstar2 = 0; 
	Double_t e1Pi = d->EProng(0,211), e2K = d->EProng(1,321); //hyp 1 (pi,K) - D0
	Double_t e1K = d->EProng(0,321), e2Pi = d->EProng(1,211); //hyp 2 (K,pi) - D0bar
	Double_t psum2 = (d->Px()+track->Px())*(d->Px()+track->Px())
	+(d->Py()+track->Py())*(d->Py()+track->Py())
	+(d->Pz()+track->Pz())*(d->Pz()+track->Pz());
	
	switch(hypD0) {
		case 1:
			invmassDstar1 = TMath::Sqrt(pow(e1Pi+e2K+track->E(0.1396),2.)-psum2);
			if ((TMath::Abs(invmassDstar1-mD0)-0.14543) < nsigma*800.*pow(10.,-6.)) return kFALSE;
			break;
		case 2:
			invmassDstar2 = TMath::Sqrt(pow(e2Pi+e1K+track->E(0.1396),2.)-psum2);
			if ((TMath::Abs(invmassDstar2-mD0bar)-0.14543) < nsigma*800.*pow(10.,-6.)) return kFALSE;
			break;
		case 3:
			invmassDstar1 = TMath::Sqrt(pow(e1Pi+e2K+track->E(0.1396),2.)-psum2);
			invmassDstar2 = TMath::Sqrt(pow(e2Pi+e1K+track->E(0.1396),2.)-psum2);
			if ((TMath::Abs(invmassDstar1-mD0)-0.14543) < nsigma*800.*pow(10.,-6.)) return kFALSE;
			if ((TMath::Abs(invmassDstar2-mD0bar)-0.14543) < nsigma*800.*pow(10.,-6.)) return kFALSE;
			break;
	}
	
	return kTRUE;
}
//________________________________________________________
void AliHFAssociatedTrackCuts::SetAODTrackCuts(Float_t *cutsarray)
{
	cout << "Check 1" << endl;
	if(!fAODTrackCuts) fAODTrackCuts = new Float_t[fNTrackCuts];
	cout << "Check 2" << endl;
	for(Int_t i =0; i<fNTrackCuts; i++){
		cout << "Check 2." << i << endl;
		fAODTrackCuts[i] = cutsarray[i];
	}
	cout << "Check 3" << endl;
	SetTrackCutsNames();
	cout << "Check 4" << endl;
	return;
}
//________________________________________________________
void AliHFAssociatedTrackCuts::SetTrackCutsNames(/*TString *namearray*/){
	
	fTrackCutsNames = new TString[4];
	fTrackCutsNames[0]= "associated track:: pt min [GeV/c]................: ";
	fTrackCutsNames[1]= "associated track:: pt max [GeV/c]................: ";
	fTrackCutsNames[2]= "associated track:: d0 min [cm]...................: ";
	fTrackCutsNames[3]= "associated track:: d0 max [cm]...................: ";
	

	
	return;
}
//--------------------------------------------------------------------------
void AliHFAssociatedTrackCuts::SetAODvZeroCuts(Float_t *cutsarray)
{
	

	if(!fAODvZeroCuts) fAODvZeroCuts = new Float_t[fNvZeroCuts];
	for(Int_t i =0; i<fNvZeroCuts; i++){
		fAODvZeroCuts[i] = cutsarray[i];
	}
	SetvZeroCutsNames();
	return;
}
//--------------------------------------------------------------------------
void AliHFAssociatedTrackCuts::SetvZeroCutsNames(/*TString *namearray*/){
	
	fvZeroCutsNames = new TString[7];
	fvZeroCutsNames[0] = "vZero:: max DCA between two daughters [cm].......: ";
	fvZeroCutsNames[1] = "vZero:: max fit Chi Square between two daughters.: ";
	fvZeroCutsNames[2] = "vZero:: min decay length [cm]....................: ";
	fvZeroCutsNames[3] = "vZero:: max decay length [cm]....................: ";
	fvZeroCutsNames[4] = "vZero:: max opening angle between daughters [rad]: ";
	fvZeroCutsNames[5] = "vZero:: pt min [Gev/c]...........................: ";
	fvZeroCutsNames[6] = "vZero:: |Eta| range <............................: ";
	
	
	return;
}

//--------------------------------------------------------------------------
void AliHFAssociatedTrackCuts::PrintAll()
{
	printf("\nCuts for the associated track: \n \n");
	       
	printf("ITS Refit........................................: %s\n",fESDTrackCuts->GetRequireITSRefit() ? "Yes" : "No");
	printf("TPC Refit........................................: %s\n",fESDTrackCuts->GetRequireTPCRefit() ? "Yes" : "No");
	printf("ITS SA...........................................: %s\n",fESDTrackCuts->GetRequireITSStandAlone() ? "Yes" : "No");
	printf("TPC SA...........................................: %s\n",fESDTrackCuts->GetRequireTPCStandAlone() ? "Yes" : "No");
	printf("Min number of ITS clusters.......................: %d\n",fESDTrackCuts->GetMinNClustersITS());
	printf("Min number of TPC clusters.......................: %d\n",fESDTrackCuts->GetMinNClusterTPC());
	Int_t spd = fESDTrackCuts->GetClusterRequirementITS(AliESDtrackCuts::kSPD);
	if(spd==0) cout <<  "SPD..............................................: kOff"  << endl;
	if(spd==1) cout <<  "SPD..............................................: kNone"  << endl;
	if(spd==2) cout <<  "SPD..............................................: kAny"  << endl;
	if(spd==3) cout <<  "SPD..............................................: kFirst"  << endl;
	if(spd==4) cout <<  "SPD..............................................: kOnlyFirst"  << endl;
	if(spd==5) cout <<  "SPD..............................................: kSecond"  << endl;
	if(spd==6) cout <<  "SPD..............................................: kOnlySecond"  << endl;
	if(spd==7) cout <<  "SPD..............................................: kBoth"  << endl;
		
	for(Int_t j=0;j<fNTrackCuts;j++){
		cout << fTrackCutsNames[j] << fAODTrackCuts[j] << endl;
	}
	
	printf("\nCuts for the K0 candidates: \n \n");
	for(Int_t k=0;k<fNvZeroCuts;k++){
		cout << fvZeroCutsNames[k] <<  fAODvZeroCuts[k] << endl;
	}
	cout << " " << endl;
	PrintPoolParameters();

}

//--------------------------------------------------------------------------
void AliHFAssociatedTrackCuts::PrintPoolParameters()
{
	printf("\nEvent Pool settings: \n \n");
	
	printf("Number of zVtx Bins: %d\n", fNzVtxBins);
	printf("\nzVtx Bins:\n");
	//Double_t zVtxbinLims[fNzVtxBins+1] = fNzVtxBins;
	for(Int_t k=0; k<fNzVtxBins; k++){
		printf("Bin %d..............................................: %.1f - %.1f cm\n ", k, fZvtxBins[k], fZvtxBins[k+1]);	
	}
	
	printf("\nNumber of Centrality(multiplicity) Bins: %d\n", fNCentBins);
	printf("\nCentrality(multiplicity) Bins:\n");
	for(Int_t k=0; k<fNCentBins; k++){
		printf("Bin %d..............................................: %.1f - %.1f\n ", k, fCentBins[k], fCentBins[k+1]);
	}
	
	
	
}


