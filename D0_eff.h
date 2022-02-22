#include "TFile.h"
#include "TString.h"
#include "TH1D.h"
#include "TFile.h"
#include "TString.h"
#include "TStyle.h"
#include "TDirectoryFile.h"
#include "TH1D.h"
#include "TCanvas.h"
//#include "AliCFTaskVertexingHF.h"
//#include "AliCFContainer.h"
#include "TLegend.h"
#include <Riostream.h>


void MakeD0AccEff(int u){
    
    TString cent1[4]={"0100","05","1060","60100"};
    int bunch=16;
///Users/criter3/cernbox2/Lc/VsMult/tagliChrisJaime/allStat_highMult/allstat_2/CheckEqualization/newEqualiz_fix/newStat_July/MC_july/rootfiles
    
  
    TString suffix = "WithD";
    
    TFile *_file16 = TFile::Open(Form("output_EvWithD_16merged_D0_%s.root",cent1[u].Data()));
    TFile *_file17 = TFile::Open(Form("output_EvWithD_16merged_D0_%s.root",cent1[u].Data()));
    TFile *_file18 = TFile::Open(Form("output_EvWithD_16merged_D0_%s.root",cent1[u].Data()));
    TH1F *hWeights;
    if(bunch==16) hWeights = (TH1F*)_file16->Get("Weights0");
    else if(bunch==17) hWeights = (TH1F*)_file17->Get("Weights0");
    else if(bunch==18) hWeights = (TH1F*)_file18->Get("Weights0");
    else {
        Printf("Wrong bunch number, check!");
        return;
    }
     
    
    
//    _fromB_13t_centralnoeq
//_prompt_2016noeq
    TString nameP="_prompt_2016_central";
    TString nameF="_fromB_2016_central";//PWG3_D2H_CFtaskD0toKpiKeepDfromBOnly_fromB_13t_central
    TString fileNameEff;
    
    
  if(bunch==16)fileNameEff= Form("AnalysisResults_final_MC_LcD0_1295_1294.root");
  if(bunch==17) fileNameEff = Form("AnalysisResults_final_MC_LcD0_1295_1294.root");
  if(bunch==18) fileNameEff = Form("AnalysisResults_final_MC_LcD0_1295_1294.root");
    
    

    
    
    
    
    TString baseDirFilNameEff=Form("PWG3_D2H_CFtaskD0toKpi%s",nameP.Data());//PR o FD
    TString baseContainerNameEff=Form("CFHFccontainer0%s",nameP.Data());
    //PWG3_D2H_CFtaskD0toKpi_prompt_2016_central
    
    TString baseDirFilNameBEff=Form("PWG3_D2H_CFtaskD0toKpiKeepDfromBOnly%s",nameF.Data());
    TString baseContainerNameBEff=Form("CFHFccontainer0DfromB%s",nameF.Data());
    //PWG3_D2H_CFtaskD0toKpiKeepDfromBOnly_fromB_2016_central
    
    const Int_t nPtBins=6;
    Double_t ptLimits[nPtBins+1];
  
    ptLimits[0]=1.;
    ptLimits[1]=2.;
    ptLimits[2]=4.;
    ptLimits[3]=6.;
    ptLimits[4]=8.;
    ptLimits[5]=12.;
    ptLimits[6]=24.;


  //  const int nMultBins = 3;
  //  Double_t multLims[nMultBins+1] = {1,40,65,200};
    
    
    const int nMultBins = 1;
    Double_t multLims[nMultBins+1] = {0,200};
    
    
    
     

  //  Int_t middle=0;//AliCFTaskVertexingHF::kStepAcceptance;//mesoni Ds con tutte le figlie in accettanza
  //  Int_t numer=AliCFTaskVertexingHF::kStepRecoPID;//mesoni Ds selezionati dopo tagli+PID
    
    
    //Int_t middle=AliCFTaskVertexingHF::kStepAcceptance;
    Int_t middle=AliCFTaskVertexingHF::kStepGeneratedLimAcc;
    Int_t numer=AliCFTaskVertexingHF::kStepRecoPID;
    
    TFile* fileff = new TFile(fileNameEff.Data());
    cout<<baseDirFilNameEff.Data()<<"  "<<baseDirFilNameBEff.Data()<<endl;
    TDirectoryFile* dfeff=(TDirectoryFile*)fileff->Get(Form("%s",baseDirFilNameEff.Data()));
    if(!dfeff) Printf("dfeff not exists");
    TDirectoryFile* dfeffB=(TDirectoryFile*)fileff->Get(Form("%s",baseDirFilNameBEff.Data()));
    
    AliCFContainer* conteff=(AliCFContainer*)dfeff->Get(Form("%s",baseContainerNameEff.Data()));
    AliCFContainer* conteffB=(AliCFContainer*)dfeffB->Get(Form("%s",baseContainerNameBEff.Data()));
    
    cout<< " conteffB " << conteffB << " dfeffB " << dfeffB << endl;
    
    TH1D* hpt;
    TH1D* hrec;
    TH1D* hrecB;
    TH1D* hgeneff;
    TH1D* hgeneffB;
    
    TH1D* hnum[nMultBins+1];
    TH1D* hnumB[nMultBins+1];
    TH1D* hden[nMultBins+1];
    TH1D* hdenB[nMultBins+1];

    for(int iMultBin = 0; iMultBin <= nMultBins; iMultBin++) {
        if(iMultBin<nMultBins) {
            if(iMultBin==0){
          cout<< " i " << iMultBin << " mult inf " << multLims[iMultBin] << " mult sup " << multLims[iMultBin+1]-1 <<endl;
            hnum[iMultBin]  = new TH1D(Form("hnumMultBin%.0f%.0f",multLims[iMultBin],multLims[iMultBin+1]-1),"",nPtBins,ptLimits);
            hnumB[iMultBin] = new TH1D(Form("hnumBMultBin%.0f%.0f",multLims[iMultBin],multLims[iMultBin+1]-1),"",nPtBins,ptLimits);
            hden[iMultBin]  = new TH1D(Form("hdenMultBin%.0f%.0f",multLims[iMultBin],multLims[iMultBin+1]-1),"",nPtBins,ptLimits);
            hdenB[iMultBin] = new TH1D(Form("hdenBMultBin%.0f%.0f",multLims[iMultBin],multLims[iMultBin+1]-1),"",nPtBins,ptLimits);
            }
            
            if(iMultBin>0){
          cout<< " i " << iMultBin << " mult inf " << multLims[iMultBin] << " mult sup " << multLims[iMultBin+1]-1 <<endl;
            hnum[iMultBin]  = new TH1D(Form("hnumMultBin%.0f%.0f",multLims[iMultBin],multLims[iMultBin+1]-1),"",nPtBins,ptLimits);
            hnumB[iMultBin] = new TH1D(Form("hnumBMultBin%.0f%.0f",multLims[iMultBin],multLims[iMultBin+1]-1),"",nPtBins,ptLimits);
            hden[iMultBin]  = new TH1D(Form("hdenMultBin%.0f%.0f",multLims[iMultBin],multLims[iMultBin+1]-1),"",nPtBins,ptLimits);
            hdenB[iMultBin] = new TH1D(Form("hdenBMultBin%.0f%.0f",multLims[iMultBin],multLims[iMultBin+1]-1),"",nPtBins,ptLimits);
            }
        }
        else {//minimum bias
          cout<< " MB i " << iMultBin << " mult inf " << multLims[iMultBin] << " mult sup " << multLims[iMultBin+1]-1 <<endl;
            hnum[nMultBins]  = new TH1D(Form("hnumMultBin%.0f%.0f",multLims[0],multLims[nMultBins]-1),"",nPtBins,ptLimits);
            hnumB[nMultBins] = new TH1D(Form("hnumBMultBin%.0f%.0f",multLims[0],multLims[nMultBins]-1),"",nPtBins,ptLimits);
            hden[nMultBins]  = new TH1D(Form("hdenMultBin%.0f%.0f",multLims[0],multLims[nMultBins]-1),"",nPtBins,ptLimits);
            hdenB[nMultBins] = new TH1D(Form("hdenBMultBin%.0f%.0f",multLims[0],multLims[nMultBins]-1),"",nPtBins,ptLimits);
        }
    }
    
    for(int iPtBin = 0; iPtBin < nPtBins; iPtBin++) {
cout<< " for iPtBin " << iPtBin <<endl;

   
        conteff->SetRangeUser(0,0.,24.);
        conteffB->SetRangeUser(0,0.,24.);

        conteff->SetRangeUser(0,ptLimits[iPtBin],ptLimits[iPtBin+1]-0.001);
        conteffB->SetRangeUser(0,ptLimits[iPtBin],ptLimits[iPtBin+1]-0.001);
      
    
        for(int iMultBin = 0; iMultBin <= nMultBins; iMultBin++) {
          cout<< " iMultBin "<< iMultBin <<endl;
            
            //reset range multiplicity
            conteff->SetRangeUser(3,0.,1000.);
           conteffB->SetRangeUser(3,0.,1000.);
            //set new range
            
            
            
            
            if(iMultBin<nMultBins) {
                
                if(iMultBin==0){
              cout<< " i " << iMultBin << " multLims[iMultBin] " << multLims[iMultBin] << " sup " << multLims[iMultBin+1]-0.001 << endl;
               conteff->SetRangeUser(3,multLims[iMultBin]+1,multLims[iMultBin+1]-0.001);
                conteffB->SetRangeUser(3,multLims[iMultBin]+1,multLims[iMultBin+1]-0.001);
                }
                if(iMultBin>0){
                    cout<< " i " << iMultBin << " multLims[iMultBin] " << multLims[iMultBin] << " sup " << multLims[iMultBin+1]-0.001 << endl;
                     conteff->SetRangeUser(3,multLims[iMultBin]+0.001,multLims[iMultBin+1]-0.001);
                      conteffB->SetRangeUser(3,multLims[iMultBin]+0.001,multLims[iMultBin+1]-0.001);
            }
            }
            else {
           conteff->SetRangeUser(3,multLims[0]+0.001,multLims[nMultBins]-0.001);
           conteffB->SetRangeUser(3,multLims[0]+0.001,multLims[nMultBins]-0.001);
            }
            
            
            
            
            hpt     = (TH1D*)conteff->Project(numer,0);
            TCanvas *cpt=new TCanvas("cp","cp");
            hpt->Draw();
            Printf("pt lims %f-%f",hpt->GetBinLowEdge(1),hpt->GetBinLowEdge(hpt->GetNbinsX()+1));

            hrec     = (TH1D*)conteff->Project(numer,3);
            hrecB    = (TH1D*)conteffB->Project(numer,3);
            hgeneff  = (TH1D*)conteff->Project(middle,3);
            hgeneffB = (TH1D*)conteffB->Project(middle,3);
            
            hrec->Sumw2();
            hrecB->Sumw2();
            hgeneff->Sumw2();
            hgeneffB->Sumw2();
            
            
            Printf("mult %f-%f",hrec->GetBinLowEdge(1),hrec->GetBinLowEdge(hrec->GetNbinsX()+1));

            for(int j = 1; j <= hrec->GetNbinsX(); j++) {
                double mult = hrec->GetBinCenter(j)-0.5;
                cout<< " mult " << mult << " original " << hrec->GetBinCenter(j) <<endl;
                double w = hWeights->GetBinContent(hWeights->FindBin(mult));
              //  double w = 1;
                double y = hrec->GetBinContent(j);
                cout<<"w="<<" "<<w<<endl;
                hrec->SetBinContent(j,y*w);
                hrec->SetBinError(j,TMath::Sqrt(y)*w);
                y = hrecB->GetBinContent(j);
                hrecB->SetBinContent(j,y*w);
                hrecB->SetBinError(j,TMath::Sqrt(y)*w);
                y = hgeneff->GetBinContent(j);
                hgeneff->SetBinContent(j,y*w);
                hgeneff->SetBinError(j,TMath::Sqrt(y)*w);
                y = hgeneffB->GetBinContent(j);
                hgeneffB->SetBinContent(j,y*w);
                hgeneffB->SetBinError(j,TMath::Sqrt(y)*w);
            }
            hnum[iMultBin]->SetBinContent(iPtBin+1,hrec->Integral());
            hnumB[iMultBin]->SetBinContent(iPtBin+1,hrecB->Integral());
            hden[iMultBin]->SetBinContent(iPtBin+1,hgeneff->Integral());
            hdenB[iMultBin]->SetBinContent(iPtBin+1,hgeneffB->Integral());

        }
    }
    

   // TFile* outfil=new TFile(Form("D0Eff_year%d_1_1000_Ntrkl_%s_W_less.root",bunch,suffix.Data()),"recreate");
    TFile* outfil=new TFile(Form("D0Eff_%d_%s.root",bunch,suffix.Data()),"recreate");
    for(int iMultBin = 0; iMultBin <= nMultBins; iMultBin++) {
        hnum[iMultBin]->Write();
        hnumB[iMultBin]->Write();
        hden[iMultBin]->Write();
        hdenB[iMultBin]->Write();
    }
    outfil->Close();
 
    
}




void doDsEffMergingBunches(int u) {
    
    TString cent[4]={"0100","010","1060","60100"};
    int nameCase=0;
    TString suffix = "WithD";
    int bunch=16;


    TFile *_file0;
  //  const int nmult = 4;
  //  TString mult[nmult] = {"1199","139","4064","65199"};
    
    
    const int nmult = 2;
    TString mult[nmult] = {"0199","0199"};
    
    TH1D *hnum;
    TH1D *hnumB;
    TH1D *hden;
    TH1D *hdenB;
    
    TH1D *hNumer[nmult];
    TH1D *hNumerB[nmult];
    TH1D *hDenom[nmult];
    TH1D *hDenomB[nmult];
    TH1D *hEff[nmult];
    TH1D *hEffB[nmult];
    
   /*
    TString fileNameAcc = "LcAcc_FONLL5mio_Bin6.root";
    TFile *fileacc = TFile::Open(fileNameAcc.Data());
    TH1D *hAcc = (TH1D*)fileacc->Get("hAcc");
*/
    
    for(int ibunch=16; ibunch<=16; ibunch++) {
        _file0 =
        TFile::Open(Form("D0Eff_%d_%s.root",bunch,suffix.Data()));
         // D0Eff_year16_1_1000_Ntrkl_EvWithD_W_less.root
         // D0Eff_year16_1_100_Ntrkl_EvWithD.root
       _file0->ls();
        for(int jmult=0; jmult<nmult; jmult++) {
          cout<<  " nome mult " <<mult[jmult] <<endl;
            hnum  = (TH1D*)_file0->Get(Form("hnumMultBin%s",mult[jmult].Data()));
            hnumB = (TH1D*)_file0->Get(Form("hnumBMultBin%s",mult[jmult].Data()));
            hden  = (TH1D*)_file0->Get(Form("hdenMultBin%s",mult[jmult].Data()));
            hdenB = (TH1D*)_file0->Get(Form("hdenBMultBin%s",mult[jmult].Data()));
            
            hnum->Sumw2();
            hnumB->Sumw2();
            hden->Sumw2();
            hdenB->Sumw2();
            
            
            
            if(ibunch==16) {
                hNumer[jmult] = (TH1D*)hnum->Clone(Form("hNumMult%s",mult[jmult].Data()));
                hNumerB[jmult] = (TH1D*)hnumB->Clone(Form("hNumB%s",mult[jmult].Data()));
                hDenom[jmult] = (TH1D*)hden->Clone(Form("hDen%s",mult[jmult].Data()));
                hDenomB[jmult] = (TH1D*)hdenB->Clone(Form("hDenB%s",mult[jmult].Data()));
                hNumer[jmult]->Sumw2();
                hNumerB[jmult]->Sumw2();
                hDenom[jmult]->Sumw2();
                hDenomB[jmult]->Sumw2();
            }
            else {
                hNumer[jmult]->Add(hnum);
                hNumerB[jmult]->Add(hnumB);
                hDenom[jmult]->Add(hden);
                hDenomB[jmult]->Add(hdenB);
            }
             
            
        }
        
    }
    
    

    
    for(int jmult=0; jmult<nmult; jmult++) {
        hEff[jmult] = 0x0;
        hEffB[jmult] = 0x0;
        
        hEff[jmult]  = (TH1D*)hNumer[jmult]->Clone(Form("hEff_C_Mult%s",mult[jmult].Data()));
        hEffB[jmult] = (TH1D*)hNumerB[jmult]->Clone(Form("hEff_B_Mult%s",mult[jmult].Data()));
   
        hEff[jmult]->Divide(hNumer[jmult],hDenom[jmult],1,1,"B");
        hEffB[jmult]->Divide(hNumerB[jmult],hDenomB[jmult],1,1,"B");
        hEff[jmult]->SetName("hEff_C");//Form("hEff_C_Mult%s",mult[jmult].Data()));
        hEffB[jmult]->SetName("hEff_B");//Form("hEff_B_Mult%s",mult[jmult].Data()));

      /*  for(int ibin=1;ibin<=hEff[jmult]->GetNbinsX();ibin++){
            double ptcenter = hEff[jmult]->GetBinCenter(ibin);
            hEff[jmult]->SetBinContent(ibin,hEff[jmult]->GetBinContent(ibin));
            hEffB[jmult]->SetBinContent(ibin,hEffB[jmult]->GetBinContent(ibin));
            
        }*/
        
        for(int ibin=1;ibin<=hEff[jmult]->GetNbinsX();ibin++){
            double ptcenter = hEff[jmult]->GetBinCenter(ibin);
         //   int accbin = hAcc->FindBin(ptcenter);
            hEff[jmult]->SetBinContent(ibin,hEff[jmult]->GetBinContent(ibin));
            hEffB[jmult]->SetBinContent(ibin,hEffB[jmult]->GetBinContent(ibin));
        }
        
        
        TFile* outfil=new TFile(Form("D0AccEff_%s_%s_%s.root",mult[jmult].Data(),suffix.Data(),cent[u].Data()),"recreate");
        hEff[jmult]->Write();
        hEffB[jmult]->Write();
        outfil->Close();

    }
    
    
}

