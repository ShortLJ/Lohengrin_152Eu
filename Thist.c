#include "Lst2RootTree_PhyDet_Ecalib.h"


void Thist(){
	Lst2RootTree_PhyDet_Ecalib *tree = new Lst2RootTree_PhyDet_Ecalib();
	const Long64_t Entries = tree->fChain->GetEntries();
	const Long64_t permille = Entries/1000;
	

	TH1D *h1_raw_tac[2];
	h1_raw_tac[0] = new TH1D("0","0", 32768/16, 0, 32768);
	h1_raw_tac[1] = new TH1D("1","1", 32768/16, 0, 32768);
	

	TH1D *h1_tac[2][4][4];
	for (int ich=0; ich<4; ich++){
		for (int jch=0; jch<4; jch++){
			h1_tac[0][ich][jch] = new TH1D(Form("h1_tac0_ch%d_ch%d", ich, jch), Form("h1_tac0_ch%d_ch%d;TAC; count", ich, jch), 32768/32, 0, 32768);
			h1_tac[1][ich][jch] = new TH1D(Form("h1_tac1_ch%d_ch%d", ich, jch), Form("h1_tac1_ch%d_ch%d;TAC; count", ich, jch), 32768/32, 0, 32768);
		}
	}


	Long64_t ient=0;
	for (/*Long64_t*/ ient=0; ient<Entries; ient++){
		tree->GetEntry(ient);
		if(ient%permille==0){
			printf("\r%lld ent of %lld, %.1f%%", ient, Entries, (float)ient/Entries*100);
			fflush(stdout);
		}

		for (int khit=0; khit<tree->TAC_Hits_; khit++){
		}

//printf("tree->LaBr_Hits_ %d tree->TAC_Hits_ %d \n", tree->LaBr_Hits_, tree->TAC_Hits_);
		for (int khit=0; khit<tree->TAC_Hits_; khit++){
			h1_raw_tac[tree->TAC_Hits_Channel[khit]]->Fill(tree->TAC_Hits_ADC[khit]);
			for (int ihit=0; ihit<tree->LaBr_Hits_; ihit++){
				if( tree->LaBr_Hits_CalibE[ihit]<122-4.2*3 || 122+4.2*3<tree->LaBr_Hits_CalibE[ihit] ) continue;
				for (int jhit=0; jhit<tree->LaBr_Hits_; jhit++){
					if(ihit==jhit) continue;
					if( tree->LaBr_Hits_CalibE[jhit]<1408-15*3 || 1408+15*3<tree->LaBr_Hits_CalibE[jhit] ) continue;
					h1_tac[tree->TAC_Hits_Channel[khit]][tree->LaBr_Hits_Channel[ihit]][tree->LaBr_Hits_Channel[jhit]]->Fill(tree->TAC_Hits_ADC[khit]);
//printf("tree->TAC_Hits_Channel[khit] %d tree->LaBr_Hits_Channel[ihit] %d tree->LaBr_Hits_Channel[jhit] %d tree->TAC_Hits_ADC[khit] %d \n", tree->TAC_Hits_Channel[khit], tree->LaBr_Hits_Channel[ihit], tree->LaBr_Hits_Channel[jhit], tree->TAC_Hits_ADC[khit]);
				}
			}
		}
	}
	printf("\r%lld ent of %lld, %.1f%%", ient, Entries, (float)ient/Entries*100);
	printf("\n");


	TFile *ofile = new TFile("Thist.root", "recreate");

	TCanvas *c1 = new TCanvas("c1_TAC0", "c1_TAC0", 1200, 900);
	c1->Divide(4,4);
	for (int ich=0; ich<4; ich++){
		for (int jch=0; jch<4; jch++){
			c1->cd(1+ich+4*jch)->SetLogy();
			h1_tac[0][ich][jch]->Draw();
			h1_tac[0][ich][jch]->Write();
		}
	}
	TCanvas *c2 = new TCanvas("c1_TAC1", "c1_TAC1", 1200, 900);
	c2->Divide(4,4);
	for (int ich=0; ich<4; ich++){
		for (int jch=0; jch<4; jch++){
			c2->cd(1+ich+4*jch)->SetLogy();
			h1_tac[1][ich][jch]->Draw();
			h1_tac[1][ich][jch]->Write();
		}
	}

	TCanvas *c3 = new TCanvas("raw", "raw", 1200, 600);
	c3->Divide(2,1);
	c3->cd(1);
	h1_raw_tac[0]->Draw();
	c3->cd(2);
	h1_raw_tac[1]->Draw();



}
