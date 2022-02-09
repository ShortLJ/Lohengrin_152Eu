#include "Lst2RootTree.h"
//#include "DetSys.h"
#include "HPGe_Hit.h"
#include "LaBr_Hit.h"
#include "TAC_Hit.h"

ClassImp(HPGe_Hit);
ClassImp(LaBr_Hit);
ClassImp(TAC_Hit);

void PhyDet(){
	gROOT->ProcessLine("gInterpreter->GenerateDictionary(\"vector<HPGe_Hit>\", \"vector;HPGe_Hit.h\");");
	gROOT->ProcessLine("gInterpreter->GenerateDictionary(\"vector<LaBr_Hit>\", \"vector;LaBr_Hit.h\");");
	gROOT->ProcessLine("gInterpreter->GenerateDictionary(\"vector<TAC_Hit>\", \"vector;TAC_Hit.h\");");


	Lst2RootTree *tree = new Lst2RootTree();
	const Long64_t Entries = tree->fChain->GetEntries();
	const Long64_t permille = Entries/1000;

	TFile *otree_file = new TFile("Lst2RootTree_PhyDet.root", "recreate");
	TTree *otree = new TTree("Lst2RootTree_PhyDet", "Lst2RootTree_PhyDet");

	const Short_t HPGe_minch=8;
	const Short_t HPGe_nch = 4;
	const Short_t LaBr_minch=8;
	const Short_t LaBr_nch = 4;
	const Short_t TAC_minch=12;
	const Short_t TAC_nch = 2;
	
	vector<HPGe_Hit> HPGe_Hits;
	vector<LaBr_Hit> LaBr_Hits;
	vector<TAC_Hit> TAC_Hits;

	otree->Branch("HPGe_Hits", &HPGe_Hits, 32*1024*1024,1);
	otree->Branch("LaBr_Hits", &LaBr_Hits, 32*1024*1024,1);
	otree->Branch("TAC_Hits", &TAC_Hits, 32*1024*1024,1);



	Long64_t ient=0;
	for(ient=0; ient<Entries; ient++){
		if(ient%permille==0){
			printf("\r%lld ent of %lld, %.1f%%", ient, Entries, (float)ient/Entries*100);
			fflush(stdout);
		}
		tree->GetEntry(ient);	

		for(int imult=0; imult<tree->multiplicity; imult++){
			if(0<=tree->adc[imult] && tree->adc[imult]<4){
				HPGe_Hit hpge_hit = {
					tree->energy[imult],
					-1,
					tree->adc[imult],
					tree->timeStamp[imult],
					tree->isClean[imult]
				};
				HPGe_Hits.push_back(hpge_hit);
			}
			else if(8<=tree->adc[imult] && tree->adc[imult]<12){
				LaBr_Hit labr_hit = {
					tree->energy[imult],
					-1,
					static_cast<Short_t>(tree->adc[imult]-LaBr_minch),
					tree->timeStamp[imult],
					tree->isClean[imult]
				};
				LaBr_Hits.push_back(labr_hit);
			}
			else if(12<=tree->adc[imult] && tree->adc[imult]<14){
				TAC_Hit tac_hit = {
					tree->energy[imult],
					-1,
					static_cast<Short_t>(tree->adc[imult]-TAC_minch),
					tree->timeStamp[imult],
					tree->isClean[imult]
				};
				TAC_Hits.push_back(tac_hit);
			}
			else if(14<=tree->adc[imult] && tree->adc[imult]<16){
				continue;
			}


			else printf("\nchannel???? %d\n",tree->adc[imult],stderr);

		}

		HPGe_Hits.shrink_to_fit();
		LaBr_Hits.shrink_to_fit();
		TAC_Hits.shrink_to_fit();
		otree->Fill();

		HPGe_Hits.clear();
		LaBr_Hits.clear();
		TAC_Hits.clear();


	}


	printf("\r%lld ent of %lld, %.1f%%", ient, Entries, (float)ient/Entries*100);
	printf("\n");
	fflush(stdout);

	otree->Write();
	otree_file->Close();




}

