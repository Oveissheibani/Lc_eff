#include "TFile.h"
#include "TString.h"
#include "TH1D.h"
#include "TStyle.h"
#include "TDirectoryFile.h"
#include "TCanvas.h"
//#include "AliCFTaskVertexingHF.h"
//#include "AliCFContainer.h"
#include "TLegend.h"
#include <Riostream.h>



void MakeD0AccEff(int Resonance, int k ){
    int ApplyWeigth=1;
    TString suffix;
    if (ApplyWeigth==1){suffix= "WithD";}
    if (ApplyWeigth==0){suffix= "WithoutD";}
    TString nameP;
    TString nameF;
    
    TString cent[4]={"0100","010","1060","60100"};
    
    TString fileW[3]={
        Form("output_EvWithD_16merged_%s.root",cent[k].Data()),
         Form("output_EvWithD_16merged_%s.root",cent[k].Data()),
        Form("output_EvWithD_16merged_%s.root",cent[k].Data())
     };
      
    
    
    
    
    TFile* filw[3];
    TH1F** hWeight=new TH1F*[3];
    for(Int_t iw=0;iw<3; iw++){
      filw[iw]=new TFile(fileW[iw].Data());
    //  hWeight[iw]=(TH1F*)filw[iw]->Get("Weights_0100");//centrality
        hWeight[iw]=(TH1F*)filw[iw]->Get("Weights0");//centrality
    //  hWeight[iw]->SetLineColor(wcol[iw]);
      hWeight[iw]->SetStats(0);
      hWeight[iw]->GetXaxis()->SetTitle("Ntracklets in |#eta|<1");
      hWeight[iw]->GetYaxis()->SetTitle("");
      hWeight[iw]->GetYaxis()->SetTitleOffset(1.4);
      hWeight[iw]->SetMaximum(3.);
      hWeight[iw]->SetMinimum(0.);
    }
    
    
    
    TCanvas* cw1=new TCanvas("cw1","Event vs Tracklet",1200,600);
  //cw->cd(2);
  gPad->SetLeftMargin(0.12);
    hWeight[0]->GetXaxis()->SetRangeUser(0,200);
    hWeight[0]->SetLineColor(kRed);
    hWeight[0]->SetMarkerColor(kRed);
    hWeight[1]->SetLineColor(kBlue);
    hWeight[1]->SetMarkerColor(kBlue);
    hWeight[2]->SetLineColor(kGreen);
    hWeight[2]->SetMarkerColor(kGreen);
  hWeight[0]->Draw();
  hWeight[1]->Draw("same");
  hWeight[2]->Draw("same");
  TLegend* legw=new TLegend(0.55,0.65,0.89,0.89);
  legw->SetFillStyle(0);
  legw->AddEntry(hWeight[0],"EvSel Weight","L");
  legw->AddEntry(hWeight[1],"Candidate Weight","L");
  legw->AddEntry(hWeight[2],"D Weight","L");
  legw->Draw();
    
    
    
    
    
    

    
    
//t determines which resonace should be used
   
        if (Resonance==0){
         nameP="Prod_5pPb_promptAll";
         nameF="Prod_fdAllb";
        }
    
        if (Resonance==1){
         nameP="Prod_5pPb_promptNonResonant";
         nameF="Prod_fdNonResonantb";
        }
        
        if (Resonance==2){
         nameP="Prod_5pPb_promptL1520";
         nameF="Prod_fdL1520b";
        }
    
   
    
        if (Resonance==3){
         nameP="Prod_5pPb_promptDelta";
         nameF="Prod_fdDeltab";
        }
    
        if (Resonance==4){
         nameP="Prod_5pPb_promptKstar";
         nameF="Prod_fdKstarb";
        }
    
 
    TString fileNameEff;
    
    fileNameEff= Form("AnalysisResults_final_LcD0_MC_1280_1281.root");

//PWG3_D2H_CFtaskLctopKpiKeepDfromBOnly_CommonFrameworkProd_fdAllb
//PWG3_D2H_CFtaskLctopKpi_CommonFrameworkProd_5pPb_promptAll
    TString baseDirFilNameEff=Form("PWG3_D2H_CFtaskLctopKpi_CommonFramework%s",nameP.Data());//PR o FD
    TString baseContainerNameEff=Form("CFHFccontainer0_3Prong_CommonFramework%s",nameP.Data());
    TString baseDirFilNameBEff=Form("PWG3_D2H_CFtaskLctopKpiKeepDfromBOnly_CommonFramework%s",nameF.Data());
    TString baseContainerNameBEff=Form("CFHFccontainer0DfromB_3Prong_CommonFramework%s",nameF.Data());

    const Int_t nPtBins=6;
    Double_t ptLimits[nPtBins+1];
  
    ptLimits[0]=1.;
    ptLimits[1]=2.;
    ptLimits[2]=4.;
    ptLimits[3]=6.;
    ptLimits[4]=8.;
    ptLimits[5]=12.;
    ptLimits[6]=24.;

  const int nMultBins = 1;
  Double_t multLims[nMultBins+1] = {0,200};

    
  //  const int nMultBins = 3;
 //   Double_t multLims[nMultBins+1] = {1,40,65,200};
     
    

  //  Int_t middle=AliCFTaskVertexingHF::kStepAcceptance;
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
    
    TH1D* hpt1;   //for without weigth
    TH1D* hrec1;
    TH1D* hrecB1;
    TH1D* hgeneff1;
    TH1D* hgeneffB1;
    
    TH1D* hnum[nMultBins+1];
    TH1D* hnumB[nMultBins+1];
    TH1D* hden[nMultBins+1];
    TH1D* hdenB[nMultBins+1];
    
    TCanvas *RecGen[nPtBins];
    for (int i=0;i<nPtBins;i++)
    {
        RecGen[i]=new TCanvas(Form("Pt bins: %d",i),Form("Pt bins: %d",i));
       // RecGen[i]->Divide(2);
    }
    
  //  RecGen->Divide(2,6);
    for(int iMultBin = 0; iMultBin <= nMultBins; iMultBin++) {
        if(iMultBin<nMultBins) {
            if(iMultBin==0){
            hnum[iMultBin]  = new TH1D(Form("hnumMultBin%.0f%.0f",multLims[iMultBin],multLims[iMultBin+1]-1),"",nPtBins,ptLimits);
            hnumB[iMultBin] = new TH1D(Form("hnumBMultBin%.0f%.0f",multLims[iMultBin],multLims[iMultBin+1]-1),"",nPtBins,ptLimits);
            hden[iMultBin]  = new TH1D(Form("hdenMultBin%.0f%.0f",multLims[iMultBin],multLims[iMultBin+1]-1),"",nPtBins,ptLimits);
            hdenB[iMultBin] = new TH1D(Form("hdenBMultBin%.0f%.0f",multLims[iMultBin],multLims[iMultBin+1]-1),"",nPtBins,ptLimits);
            }
        
            if(iMultBin>0){
            hnum[iMultBin]  = new TH1D(Form("hnumMultBin%.0f%.0f",multLims[iMultBin],multLims[iMultBin+1]-1),"",nPtBins,ptLimits);
            hnumB[iMultBin] = new TH1D(Form("hnumBMultBin%.0f%.0f",multLims[iMultBin],multLims[iMultBin+1]-1),"",nPtBins,ptLimits);
            hden[iMultBin]  = new TH1D(Form("hdenMultBin%.0f%.0f",multLims[iMultBin],multLims[iMultBin+1]-1),"",nPtBins,ptLimits);
            hdenB[iMultBin] = new TH1D(Form("hdenBMultBin%.0f%.0f",multLims[iMultBin],multLims[iMultBin+1]-1),"",nPtBins,ptLimits);
            }
            
            
        }
        else {//minimum bias
            hnum[nMultBins]  = new TH1D(Form("hnumMultBin%.0f%.0f",multLims[0],multLims[nMultBins]-1),"",nPtBins,ptLimits);
            hnumB[nMultBins] = new TH1D(Form("hnumBMultBin%.0f%.0f",multLims[0],multLims[nMultBins]-1),"",nPtBins,ptLimits);
            hden[nMultBins]  = new TH1D(Form("hdenMultBin%.0f%.0f",multLims[0],multLims[nMultBins]-1),"",nPtBins,ptLimits);
            hdenB[nMultBins] = new TH1D(Form("hdenBMultBin%.0f%.0f",multLims[0],multLims[nMultBins]-1),"",nPtBins,ptLimits);
        }
    }
    
    for(int iPtBin = 0; iPtBin < nPtBins; iPtBin++) {

        //reset range
        conteff->SetRangeUser(0,0.,24.);
        conteffB->SetRangeUser(0,0.,24.);
        //set new range
         conteff->SetRangeUser(0,ptLimits[iPtBin],ptLimits[iPtBin+1]-0.001);
        conteffB->SetRangeUser(0,ptLimits[iPtBin],ptLimits[iPtBin+1]-0.001);
      
    
        for(int iMultBin = 0; iMultBin <= nMultBins; iMultBin++) {
       //   cout<< " iMultBin "<< iMultBin <<endl;
            
            //reset range multiplicity
             conteff->SetRangeUser(3,0.,1000.);
            conteffB->SetRangeUser(3,0.,1000.);
            //set new range
            
            if(iMultBin<nMultBins) {
                if(iMultBin==0){
                
                 conteff->SetRangeUser(3,multLims[iMultBin]+1,multLims[iMultBin+1]-0.001);
                conteffB->SetRangeUser(3,multLims[iMultBin]+1,multLims[iMultBin+1]-0.001);
                }
                
                if(iMultBin>0){
                    
                    conteff->SetRangeUser(3,multLims[iMultBin],multLims[iMultBin+1]-0.001);
                   conteffB->SetRangeUser(3,multLims[iMultBin],multLims[iMultBin+1]-0.001);
                }
            }
            else {
                 conteff->SetRangeUser(3,multLims[0],multLims[nMultBins]-0.001);
                conteffB->SetRangeUser(3,multLims[0],multLims[nMultBins]-0.001);
            }
            
         //   cout<< " conteff " << conteff << endl;
             hpt     = (TH1D*)conteff->Project(numer,0);
             
         //   Printf("pt lims %f-%f",hpt->GetBinLowEdge(1),hpt->GetBinLowEdge(hpt->GetNbinsX()+1));

            /*
            
            hrec     = (TH1D*)conteff->Project(numer,3);
            hrecB    = (TH1D*)conteffB->Project(numer,3);
            hgeneff  = (TH1D*)conteff->Project(middle,3);
            hgeneffB = (TH1D*)conteffB->Project(middle,3);
            
             */
          
            
            hrec     = (TH1D*)conteff->Project(numer,3);
            hrec1     = (TH1D*)conteff->Project(numer,3);
            
          
            
            hrecB    = (TH1D*)conteffB->Project(numer,3);
            hrecB1    = (TH1D*)conteffB->Project(numer,3);
            
            hgeneff  = (TH1D*)conteff->Project(middle,3);
            hgeneff1  = (TH1D*)conteff->Project(middle,3);
            
            hgeneffB = (TH1D*)conteffB->Project(middle,3);
            hgeneffB1 = (TH1D*)conteffB->Project(middle,3);
            
         
            
            
            
            
            
            
            hrec->Sumw2();
            hrecB->Sumw2();
            hgeneff->Sumw2();
            hgeneffB->Sumw2();
            
        
            
            
          
            
        //    Printf("mult %f-%f",hrec->GetBinLowEdge(1),hrec->GetBinLowEdge(hrec->GetNbinsX()+1));

            for(int j = 1; j <= hrec->GetNbinsX(); j++) {
                double mult = hrec->GetBinCenter(j)-0.5;
             //   cout<< " mult " << mult << " original " << hrec->GetBinCenter(j) <<endl;
                double w;
                
                if(ApplyWeigth==1)  {  w = hWeight[2]->GetBinContent(hWeight[2]->FindBin(mult));}
                cout<<"w="<<w<<endl;
                if(ApplyWeigth==0)  {    w =1.; }
                
                
                
                double y = hrec->GetBinContent(j);
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
            
            
         
          
                RecGen[iPtBin]->cd();
                hgeneff->SetMarkerStyle(22);
                hrec->SetMarkerStyle(22);
                hgeneff1->SetMarkerStyle(23);
                hrec1->SetMarkerStyle(23);
                
                hgeneff->SetMarkerColor(kBlue);
                hrec->SetMarkerColor(kRed);
                hgeneff1->SetMarkerColor(kGreen);
                hrec1->SetMarkerColor(kViolet+1);
                
                hgeneff->SetLineColor(kBlue);
                hrec->SetLineColor(kRed);
                hgeneff1->SetLineColor(kGreen);
                hrec1->SetLineColor(kViolet+1);
                
            
       
                
                // RecGen[iPtBin]->cd(2);
                hgeneff->SetStats(0);
                hgeneff->SetTitle("");
                TLegend *leg=new TLegend();
                leg->AddEntry(hrec1,"reconstructed");
                leg->AddEntry(hgeneff1,"genereated");
                leg->AddEntry(hrec,"reconstructed corected with Tracklet weigth");
                leg->AddEntry(hgeneff,"genereated corected with Tracklet weigth");
                 hgeneff->Draw();
                 hrec->Draw("same");
            
      
                
         //       RecGen[iPtBin]->cd(1);
                hgeneff1->Draw("same");
                hrec1->Draw("same");
                leg->Draw("same");
        
                

          
            
       
            
            hnum[iMultBin]->SetBinContent(iPtBin+1,hrec->Integral());
            hnumB[iMultBin]->SetBinContent(iPtBin+1,hrecB->Integral());
            hden[iMultBin]->SetBinContent(iPtBin+1,hgeneff->Integral());
            hdenB[iMultBin]->SetBinContent(iPtBin+1,hgeneffB->Integral());
           
            
            
        }
    }
    
 
    
        TFile* outfil;

   if(Resonance==2)  outfil=new TFile(Form("LcEff_L1520_mult_%s.root",suffix.Data()),"recreate");
   if(Resonance==3)  outfil=new TFile(Form("LcEff_delta_mult_%s.root",suffix.Data()),"recreate");
   if(Resonance==0)  outfil=new TFile(Form("LcEff_all_mult_%s.root",suffix.Data()),"recreate");
   if(Resonance==4)   outfil=new TFile(Form("LcEff_kstar_mult_%s.root",suffix.Data()),"recreate");
   if(Resonance==1)  outfil=new TFile(Form("LcEff_non_mult_%s.root",suffix.Data()),"recreate");
    for(int iMultBin = 0; iMultBin <= nMultBins; iMultBin++) {
        hnum[iMultBin]->Write();
        hnumB[iMultBin]->Write();
        hden[iMultBin]->Write();
        hdenB[iMultBin]->Write();
    }
    outfil->Close();
    
        
    
}


void doDsEffMergingBunches(int t) {
    
    int ApplyWeigth=1;
    TString suffix;
    if (ApplyWeigth==1){suffix= "WithD";}
    if (ApplyWeigth==0){suffix= "WithoutD";}

    
  /*  TString fileNameAcc = "LcAcc_FONLL5mio_Bin6.root";
    TFile *fileacc = TFile::Open(fileNameAcc.Data());
    TH1D *hAcc = (TH1D*)fileacc->Get("hAcc");

   
   */
    TFile *_file0;
   
    
    
    
    
 //  const int nmult = 4;
 //   TString mult[nmult] = {"1199","139","4064","65199"};
    
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


     
//    LcEff_1_1000_Ntrkl_EvWithD_MB.root
     if (t==2)  _file0 = TFile::Open(Form("LcEff_L1520_mult_%s.root",suffix.Data()));
    if (t==0)  _file0 = TFile::Open(Form("LcEff_all_mult_%s.root",suffix.Data()));
    if (t==3)    _file0 = TFile::Open(Form("LcEff_delta_mult_%s.root",suffix.Data()));
  if (t==4) _file0 = TFile::Open(Form("LcEff_kstar_mult_%s.root",suffix.Data()));
  if (t==1)  _file0 = TFile::Open(Form("LcEff_non_mult_%s.root",suffix.Data()));
    
       _file0->ls();
        for(int jmult=0; jmult<nmult; jmult++) {
            hnum  = (TH1D*)_file0->Get(Form("hnumMultBin%s",mult[jmult].Data()));
            TString nome=Form("hnumMultBin%s",mult[jmult].Data());
            hnumB = (TH1D*)_file0->Get(Form("hnumBMultBin%s",mult[jmult].Data()));
            hden  = (TH1D*)_file0->Get(Form("hdenMultBin%s",mult[jmult].Data()));
            hdenB = (TH1D*)_file0->Get(Form("hdenBMultBin%s",mult[jmult].Data()));
            
            hnum->Sumw2();
            hnumB->Sumw2();
            hden->Sumw2();
            hdenB->Sumw2();
            
                hNumer[jmult] = (TH1D*)hnum->Clone(Form("hNumMult%s",mult[jmult].Data()));
                hNumerB[jmult] = (TH1D*)hnumB->Clone(Form("hNumB%s",mult[jmult].Data()));
                hDenom[jmult] = (TH1D*)hden->Clone(Form("hDen%s",mult[jmult].Data()));
                hDenomB[jmult] = (TH1D*)hdenB->Clone(Form("hDenB%s",mult[jmult].Data()));
            
                hNumer[jmult]->Sumw2();
                hNumerB[jmult]->Sumw2();
                hDenom[jmult]->Sumw2();
                hDenomB[jmult]->Sumw2();
        }
    for(int jmult=0; jmult<nmult; jmult++) {
        hEff[jmult] = 0x0;
        hEffB[jmult] = 0x0;

        hEff[jmult]  = (TH1D*)hNumer[jmult]->Clone(Form("hEff_C_Mult%s",mult[jmult].Data()));
        hEffB[jmult] = (TH1D*)hNumerB[jmult]->Clone(Form("hEff_B_Mult%s",mult[jmult].Data()));
        cout<< " prima del divide num " << hEff[jmult] << " effB " << hEffB[jmult] <<endl;
   
        hEff[jmult]->Divide(hNumer[jmult],hDenom[jmult],1,1,"B");
        hEffB[jmult]->Divide(hNumerB[jmult],hDenomB[jmult],1,1,"B");
        hEff[jmult]->SetName("hEff_C");//Form("hEff_C_Mult%s",mult[jmult].Data()));
        hEffB[jmult]->SetName("hEff_B");//Form("hEff_B_Mult%s",mult[jmult].Data()));

        for(int ibin=1;ibin<=hEff[jmult]->GetNbinsX();ibin++){
            double ptcenter = hEff[jmult]->GetBinCenter(ibin);
          //  int accbin = hAcc->FindBin(ptcenter);
         //   hEff[jmult]->SetBinContent(ibin,hEff[jmult]->GetBinContent(ibin)*hAcc->GetBinContent(accbin));
         //   hEffB[jmult]->SetBinContent(ibin,hEffB[jmult]->GetBinContent(ibin)*hAcc->GetBinContent(accbin));
            
            hEff[jmult]->SetBinContent(ibin,hEff[jmult]->GetBinContent(ibin));
            hEffB[jmult]->SetBinContent(ibin,hEffB[jmult]->GetBinContent(ibin));
        }
        
        TFile* outfil;
        
        if (t==2)     outfil=new TFile(Form("LcAccEff_16pPb_%s_%s__MBL1520.root",mult[jmult].Data(),suffix.Data()),"recreate");
        if (t==0)    outfil=new TFile(Form("LcAccEff_16pPb_%s_%s__MBall.root",mult[jmult].Data(),suffix.Data()),"recreate");
        if (t==3)    outfil=new TFile(Form("LcAccEff_16pPb_%s_%s__MBdelta.root",mult[jmult].Data(),suffix.Data()),"recreate");
        if (t==4)   outfil=new TFile(Form("LcAccEff_16pPb_%s_%s__MBkstar.root",mult[jmult].Data(),suffix.Data()),"recreate");
        if (t==1)    outfil=new TFile(Form("LcAccEff_16pPb_%s_%s__MBnon.root",mult[jmult].Data(),suffix.Data()),"recreate");

        
        
        hEff[jmult]->Write();
        hEffB[jmult]->Write();
        outfil->Close();

}
}





void wEff(int u){
    
TString cent[4]={"0100","010","1060","60100"};
//TString name[4]={"1199","139","4064","65199"};//,"1029","3059","1999"};
 TString name[2]={"0199","0199"};;//,"1029","3059","1999"};

    
    
//mbWW
    int ApplyWeigth=1;
    TString suffix;
    if (ApplyWeigth==1){suffix= "WithD";}
    if (ApplyWeigth==0){suffix= "WithoutD";}
    
    TCanvas *MultConvas[4];
    TCanvas *MultConvas1[4];
    
for(Int_t k=0;k<2;k++){
TString f[5]={
Form("LcAccEff_16pPb_%s_%s__MBall.root",name[k].Data(),suffix.Data()),
Form("LcAccEff_16pPb_%s_%s__MBnon.root",name[k].Data(),suffix.Data()),//NonResonant
Form("LcAccEff_16pPb_%s_%s__MBdelta.root",name[k].Data(),suffix.Data()),//Delta
Form("LcAccEff_16pPb_%s_%s__MBkstar.root",name[k].Data(),suffix.Data()),//L1520
Form("LcAccEff_16pPb_%s_%s__MBL1520.root",name[k].Data(),suffix.Data())//kstar
};

TFile *file[5];
for(Int_t i=0;i<5;i++){
file[i]=TFile::Open(f[i].Data());
}
    
    
    
    
Double_t BR[5]={
  6.84*1e-02,
  3.8*1e-02,
  1.18*1e-02,
  2.13*1e-02,
  2.4*1e-02

};
    
 
    
for(Int_t i=0;i<5;i++)cout<< " BR " << BR[i]<< endl;

TH1D *effC[5];
TH1D *effB[5];
TH1D *effTB;
TH1D *effTC;
for(Int_t i=0;i<5;i++){
  cout<< " prendo eff " << i << endl;
effC[i]=(TH1D*)file[i]->Get("hEff_C");
effB[i]=(TH1D*)file[i]->Get("hEff_B");
    
  
//(eff1*BR1 + eff2*BR2 + eff3*BR3 + eff4*BR4) / (BR1+BR2+BR3+BR4)
cout<< " n bins " << effC[i]->GetNbinsX() << endl;
}
effTC=(TH1D*)effC[2]->Clone("hEff_C");
effTC->Reset("icse");
effTB=(TH1D*)effB[2]->Clone("hEff_B");
effTB->Reset("icse");
cout<< " ho clonato i file " << effTC << " b " << effTB<< endl;
    
    
for(Int_t k=0;k<6;k++){
//  cout<<  " loop sui bin " << effTC->GetNbinsX() << " k " << k << endl;
effTC->SetBinContent(k+1,((effC[1]->GetBinContent(k+1)*BR[1])+(effC[2]->GetBinContent(k+1)*BR[2])+(effC[3]->GetBinContent(k+1)*BR[3])+(effC[4]->GetBinContent(k+1)*BR[4]))/(BR[1]+BR[2]+BR[3]+BR[4]));
effTC->SetBinError(k+1,effC[0]->GetBinError(k+1));

effTB->SetBinContent(k+1,(effB[1]->GetBinContent(k+1)*BR[1]+effB[2]->GetBinContent(k+1)*BR[2]+effB[3]->GetBinContent(k+1)*BR[3]+effB[4]->GetBinContent(k+1)*BR[4])/(BR[1]+BR[2]+BR[3]+BR[4]));
effTB->SetBinError(k+1,effB[0]->GetBinError(k+1));
}

    
 
TCanvas *c=new TCanvas("ciao","ciao");
    
    
    const Int_t colors[] = {kBlack,kTeal+3,kBlue,kViolet+1,kOrange+7,kCyan,kGreen};
    const Int_t colors1[] = {kGray,kTeal+10,kAzure+10,kPink-9,kOrange,kYellow,kGreen+3};
    
    const Int_t markers[] = {kFullCircle,kFullSquare,kFullDiamond,kFullTriangleUp,kFullTriangleDown,kFullCircle,kOpenSquare,kOpenDiamond,kOpenTriangleUp,kOpenTriangleDown};
    
    
    MultConvas[k]=new TCanvas(Form("%dprompt",k),Form("prompt:%d",k));
    MultConvas1[k]=new TCanvas(Form("%dFed_Down:",k),Form("Fed_Down%d",k));
    
    
    
 
    
    for (int i=0;i<5;i++){
effC[i]->SetLineColor(colors[i+1]);
effC[i]->SetMarkerColor(colors1[i+1]);
effC[i]->SetMarkerStyle(markers[i+1]);
        
effB[i]->SetLineColor(colors[i+1]);
effB[i]->SetMarkerColor(colors1[i+1]);
effB[i]->SetMarkerStyle(markers[i+1]);
        
        effC[i]->GetYaxis()->SetRangeUser(0,0.3);
        effB[i]->GetYaxis()->SetRangeUser(0,0.33);
        
        effC[i]->GetYaxis()->SetTitle("Prompt Acc #times eff");
        effB[i]->GetYaxis()->SetTitle("Fed Down Acc #times eff");
        
        
        effC[i]->GetXaxis()->SetTitle("P_{T} (GeV/c)");
        effB[i]->GetXaxis()->SetTitle("P_{T} (GeV/c)");
        
        
        effC[i]->SetStats(0);
        effB[i]->SetStats(0);
        MultConvas1[k]->cd();
      effB[i]->Draw("same");
        MultConvas[k]->cd();
        effC[i]->Draw("same");
       
        
    }
    
    effTC->SetLineColor(kBlack);
    effTC->SetMarkerColor(kBlack);
    effTC->SetMarkerStyle(markers[6]);
    
    effTB->SetLineColor(kBlack);
    effTB->SetMarkerColor(kBlack);
    effTB->SetMarkerStyle(markers[6]);
    
    MultConvas[k]->cd();
    effTC->Draw("same");
    MultConvas1[k]->cd();
    effTB->Draw("same");
   
    
    TLegend *leg=new TLegend();//Form("Multiplicity:%s",name[k].Data())
    leg->SetHeader(Form("Multiplicity:%s",name[k].Data()));
    leg->AddEntry(effC[0],"#Lambda_{c}");
    leg->AddEntry(effC[1],"Non-Resonance");
    leg->AddEntry(effC[2],"#Delta(1232)");
    leg->AddEntry(effC[3],"kstar");
    leg->AddEntry(effC[4],"#Lambda(1520)");
    leg->AddEntry(effTC,"average");
    
    
    MultConvas[k]->cd();
    leg->Draw("same");
    MultConvas1[k]->cd();
    leg->Draw("same");

   

    TFile* outfil=new TFile(Form("LcAccEff_final_eff_%s_%s_V0_%s.root",name[k].Data(),suffix.Data(),cent[u].Data()),"recreate");
        effTC->Write();
        effTB->Write();
        outfil->Close();
    

TCanvas *cd=new TCanvas ("cd","cd");
TH1D *hR=(TH1D*)effTC->Clone("ratio");
hR->Divide(effTC,effC[0],1,1,"B");
hR->Draw();
}
    }


