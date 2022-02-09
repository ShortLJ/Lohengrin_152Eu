//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Feb  7 10:01:46 2022 by ROOT version 6.24/06
// from TTree Lst2RootTree_PhyDet/Lst2RootTree_PhyDet
// found on file: Lst2RootTree_PhyDet.root
//////////////////////////////////////////////////////////

#ifndef Lst2RootTree_PhyDet_h
#define Lst2RootTree_PhyDet_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class Lst2RootTree_PhyDet {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
   static constexpr Int_t kMaxHPGe_Hits = 4;
   static constexpr Int_t kMaxLaBr_Hits = 4;
   static constexpr Int_t kMaxTAC_Hits = 2;

   // Declaration of leaf types
   Int_t           HPGe_Hits_;
   Int_t           HPGe_Hits_ADC[kMaxHPGe_Hits];   //[HPGe_Hits_]
   Double_t        HPGe_Hits_CalibE[kMaxHPGe_Hits];   //[HPGe_Hits_]
   Short_t         HPGe_Hits_Channel[kMaxHPGe_Hits];   //[HPGe_Hits_]
   Short_t         HPGe_Hits_TimeStamp[kMaxHPGe_Hits];   //[HPGe_Hits_]
   Bool_t          HPGe_Hits_isClean[kMaxHPGe_Hits];   //[HPGe_Hits_]
   Int_t           LaBr_Hits_;
   Int_t           LaBr_Hits_ADC[kMaxLaBr_Hits];   //[LaBr_Hits_]
   Double_t        LaBr_Hits_CalibE[kMaxLaBr_Hits];   //[LaBr_Hits_]
   Short_t         LaBr_Hits_Channel[kMaxLaBr_Hits];   //[LaBr_Hits_]
   Short_t         LaBr_Hits_TimeStamp[kMaxLaBr_Hits];   //[LaBr_Hits_]
   Bool_t          LaBr_Hits_isClean[kMaxLaBr_Hits];   //[LaBr_Hits_]
   Int_t           TAC_Hits_;
   Int_t           TAC_Hits_ADC[kMaxTAC_Hits];   //[TAC_Hits_]
   Double_t        TAC_Hits_CalibT[kMaxTAC_Hits];   //[TAC_Hits_]
   Short_t         TAC_Hits_Channel[kMaxTAC_Hits];   //[TAC_Hits_]
   Short_t         TAC_Hits_TimeStamp[kMaxTAC_Hits];   //[TAC_Hits_]
   Bool_t          TAC_Hits_isClean[kMaxTAC_Hits];   //[TAC_Hits_]

   // List of branches
   TBranch        *b_HPGe_Hits_;   //!
   TBranch        *b_HPGe_Hits_ADC;   //!
   TBranch        *b_HPGe_Hits_CalibE;   //!
   TBranch        *b_HPGe_Hits_Channel;   //!
   TBranch        *b_HPGe_Hits_TimeStamp;   //!
   TBranch        *b_HPGe_Hits_isClean;   //!
   TBranch        *b_LaBr_Hits_;   //!
   TBranch        *b_LaBr_Hits_ADC;   //!
   TBranch        *b_LaBr_Hits_CalibE;   //!
   TBranch        *b_LaBr_Hits_Channel;   //!
   TBranch        *b_LaBr_Hits_TimeStamp;   //!
   TBranch        *b_LaBr_Hits_isClean;   //!
   TBranch        *b_TAC_Hits_;   //!
   TBranch        *b_TAC_Hits_ADC;   //!
   TBranch        *b_TAC_Hits_CalibT;   //!
   TBranch        *b_TAC_Hits_Channel;   //!
   TBranch        *b_TAC_Hits_TimeStamp;   //!
   TBranch        *b_TAC_Hits_isClean;   //!

   Lst2RootTree_PhyDet(TTree *tree=0);
   virtual ~Lst2RootTree_PhyDet();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

Lst2RootTree_PhyDet::Lst2RootTree_PhyDet(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Lst2RootTree_PhyDet.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("Lst2RootTree_PhyDet.root");
      }
      f->GetObject("Lst2RootTree_PhyDet",tree);

   }
   Init(tree);
}

Lst2RootTree_PhyDet::~Lst2RootTree_PhyDet()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Lst2RootTree_PhyDet::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Lst2RootTree_PhyDet::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Lst2RootTree_PhyDet::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("HPGe_Hits", &HPGe_Hits_, &b_HPGe_Hits_);
   fChain->SetBranchAddress("HPGe_Hits.ADC", HPGe_Hits_ADC, &b_HPGe_Hits_ADC);
   fChain->SetBranchAddress("HPGe_Hits.CalibE", HPGe_Hits_CalibE, &b_HPGe_Hits_CalibE);
   fChain->SetBranchAddress("HPGe_Hits.Channel", HPGe_Hits_Channel, &b_HPGe_Hits_Channel);
   fChain->SetBranchAddress("HPGe_Hits.TimeStamp", HPGe_Hits_TimeStamp, &b_HPGe_Hits_TimeStamp);
   fChain->SetBranchAddress("HPGe_Hits.isClean", HPGe_Hits_isClean, &b_HPGe_Hits_isClean);
   fChain->SetBranchAddress("LaBr_Hits", &LaBr_Hits_, &b_LaBr_Hits_);
   fChain->SetBranchAddress("LaBr_Hits.ADC", LaBr_Hits_ADC, &b_LaBr_Hits_ADC);
   fChain->SetBranchAddress("LaBr_Hits.CalibE", LaBr_Hits_CalibE, &b_LaBr_Hits_CalibE);
   fChain->SetBranchAddress("LaBr_Hits.Channel", LaBr_Hits_Channel, &b_LaBr_Hits_Channel);
   fChain->SetBranchAddress("LaBr_Hits.TimeStamp", LaBr_Hits_TimeStamp, &b_LaBr_Hits_TimeStamp);
   fChain->SetBranchAddress("LaBr_Hits.isClean", LaBr_Hits_isClean, &b_LaBr_Hits_isClean);
   fChain->SetBranchAddress("TAC_Hits", &TAC_Hits_, &b_TAC_Hits_);
   fChain->SetBranchAddress("TAC_Hits.ADC", TAC_Hits_ADC, &b_TAC_Hits_ADC);
   fChain->SetBranchAddress("TAC_Hits.CalibT", TAC_Hits_CalibT, &b_TAC_Hits_CalibT);
   fChain->SetBranchAddress("TAC_Hits.Channel", TAC_Hits_Channel, &b_TAC_Hits_Channel);
   fChain->SetBranchAddress("TAC_Hits.TimeStamp", TAC_Hits_TimeStamp, &b_TAC_Hits_TimeStamp);
   fChain->SetBranchAddress("TAC_Hits.isClean", TAC_Hits_isClean, &b_TAC_Hits_isClean);
   Notify();
}

Bool_t Lst2RootTree_PhyDet::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Lst2RootTree_PhyDet::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Lst2RootTree_PhyDet::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
