//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Jan 30 14:18:36 2022 by ROOT version 6.24/06
// from TTree Lst2RootTree/Lst2RootTree
// found on file: ../146129.root
//////////////////////////////////////////////////////////

#ifndef Lst2RootTree_h
#define Lst2RootTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class Lst2RootTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           multiplicity;
   Int_t           energy[10];   //[multiplicity]
   Short_t         adc[10];   //[multiplicity]
   Short_t         timeStamp[10];   //[multiplicity]
   Bool_t          isClean[10];   //[multiplicity]

   // List of branches
   TBranch        *b_multiplicity;   //!
   TBranch        *b_energy;   //!
   TBranch        *b_adc;   //!
   TBranch        *b_timeStamp;   //!
   TBranch        *b_isClean;   //!

   Lst2RootTree(TTree *tree=0);
   virtual ~Lst2RootTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

Lst2RootTree::Lst2RootTree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../../146129.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("../../146129.root");
      }
      f->GetObject("Lst2RootTree",tree);

   }
   Init(tree);
}

Lst2RootTree::~Lst2RootTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Lst2RootTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Lst2RootTree::LoadTree(Long64_t entry)
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

void Lst2RootTree::Init(TTree *tree)
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

   fChain->SetBranchAddress("multiplicity", &multiplicity, &b_multiplicity);
   fChain->SetBranchAddress("energy", energy, &b_energy);
   fChain->SetBranchAddress("adc", adc, &b_adc);
   fChain->SetBranchAddress("timeStamp", timeStamp, &b_timeStamp);
   fChain->SetBranchAddress("isClean", isClean, &b_isClean);
   Notify();
}

Bool_t Lst2RootTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Lst2RootTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Lst2RootTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
