#include "Lst2RootTree_PhyDet.h"
#include "HPGe_Hit.h"
#include "LaBr_Hit.h"
#include "TAC_Hit.h"

void Ehist(){
//	gROOT->ProcessLine("gInterpreter->GenerateDictionary(\"vector<HPGe_Hit>\", \"vector;HPGe_Hit.h\");");
//	gROOT->ProcessLine("gInterpreter->GenerateDictionary(\"vector<LaBr_Hit>\", \"vector;LaBr_Hit.h\");");
//	gROOT->ProcessLine("gInterpreter->GenerateDictionary(\"vector<TAC_Hit>\", \"vector;TAC_Hit.h\");");

	Lst2RootTree_PhyDet *tree = new Lst2RootTree_PhyDet();
	const Long64_t Entries = tree->fChain->GetEntries();
	const Long64_t permille = Entries/1000;

	TH1D *h1_EHPGe[4];
	for (int ich_HPGe=0; ich_HPGe<4; ich_HPGe++){
		h1_EHPGe[ich_HPGe] = new TH1D(Form("h1_EHPGe_ch%d", ich_HPGe), Form("h1_EHPGe_ch%d; ADC; count", ich_HPGe), 32768/ 8 *5/8, 0, 32768/4*5/8);
	}
	TH1D *h1_ELaBr[4];
	for (int ich_LaBr=0; ich_LaBr<4; ich_LaBr++){
		h1_ELaBr[ich_LaBr] = new TH1D(Form("h1_ELaBr_ch%d", ich_LaBr), Form("h1_ELaBr_ch%d; ADC; count", ich_LaBr), 32768/ 8*5/8, 0, 32768/2*5/8);
	}

	TH2D *h2_EHPGe_ELaBr[4][4];
	for (int ich_HPGe=0; ich_HPGe<4; ich_HPGe++){
		for (int ich_LaBr=0; ich_LaBr<4; ich_LaBr++){
			h2_EHPGe_ELaBr[ich_HPGe][ich_LaBr] = new TH2D(Form("h2_EHPGe_ch%d_ELaBr_ch%d", ich_HPGe, ich_LaBr), Form("h2_EHPGe_ch%d_ELaBr_ch%d; HPGe; LaBr3", ich_HPGe, ich_LaBr), 32768/ 8 *5/8, 0, 32768/4*5/8, 32768/ 8*5/8, 0, 32768/2*5/8);
		}
	}

	TH2D *h2_EHPGe_EHPGe[4][4];
	for (int ich_HPGe=0; ich_HPGe<4; ich_HPGe++){
		for (int jch_HPGe=0; jch_HPGe<4; jch_HPGe++){
			h2_EHPGe_EHPGe[ich_HPGe][jch_HPGe] = new TH2D(Form("h2_EHPGe_ch%d_EHPGe_ch%d", ich_HPGe, jch_HPGe), Form("h2_EHPGe_ch%d_EHPGe_ch%d; HPGe; HPGe3", ich_HPGe, jch_HPGe), 32768/ 8 *5/8, 0, 32768/4*5/8, 32768/ 8*5/8, 0, 32768/4*5/8);
		}
	}

	TH2D *h2_ELaBr_ELaBr[4][4];
	for (int ich_LaBr=0; ich_LaBr<4; ich_LaBr++){
		for (int jch_LaBr=0; jch_LaBr<4; jch_LaBr++){
			h2_ELaBr_ELaBr[ich_LaBr][jch_LaBr] = new TH2D(Form("h2_ELaBr_ch%d_ELaBr_ch%d", ich_LaBr, jch_LaBr), Form("h2_ELaBr_ch%d_ELaBr_ch%d; LaBr; LaBr3", ich_LaBr, jch_LaBr), 32768/ 8 *5/8, 0, 32768/2*5/8, 32768/ 8*5/8, 0, 32768/2*5/8);
		}
	}




	Long64_t ient=0;
	for (/*Long64_t*/ ient=0; ient<Entries; ient++){
		tree->GetEntry(ient);
		if(ient%permille==0){
			printf("\r%lld ent of %lld, %.1f%%", ient, Entries, (float)ient/Entries*100);
			fflush(stdout);
		}
		//// filling HPGe Energy histogram ////
		for(int ihit=0; ihit<tree->HPGe_Hits_; ihit++){
//	printf("tree->HPGe_Hits_ %d\t", tree->HPGe_Hits_);
//	printf("tree->HPGe_Hits_Channel[ihit] %d\n", tree->HPGe_Hits_Channel[ihit]);
			h1_EHPGe[tree->HPGe_Hits_Channel[ihit]]->Fill(tree->HPGe_Hits_ADC[ihit]);
		}
		//// Filling LaBr Energy histogram ////
		for(int ihit=0; ihit<tree->LaBr_Hits_; ihit++){
			h1_ELaBr[tree->LaBr_Hits_Channel[ihit]]->Fill(tree->LaBr_Hits_ADC[ihit]);
		}

		//// Filling 2-D histograms ////
		for(int ihit=0; ihit<tree->HPGe_Hits_; ihit++){
			for(int jhit=0; jhit<tree->HPGe_Hits_; jhit++){
				h2_EHPGe_EHPGe[tree->HPGe_Hits_Channel[ihit]][tree->HPGe_Hits_Channel[jhit]]->Fill(tree->HPGe_Hits_ADC[ihit],tree->HPGe_Hits_ADC[jhit]);
			}
		}
		for(int ihit=0; ihit<tree->LaBr_Hits_; ihit++){
			for(int jhit=0; jhit<tree->LaBr_Hits_; jhit++){
				h2_ELaBr_ELaBr[tree->LaBr_Hits_Channel[ihit]][tree->LaBr_Hits_Channel[jhit]]->Fill(tree->LaBr_Hits_ADC[ihit],tree->LaBr_Hits_ADC[jhit]);
			}
		}
		for(int ihit=0; ihit<tree->HPGe_Hits_; ihit++){
			for(int jhit=0; jhit<tree->LaBr_Hits_; jhit++){
				h2_EHPGe_ELaBr[tree->HPGe_Hits_Channel[ihit]][tree->LaBr_Hits_Channel[jhit]]->Fill(tree->HPGe_Hits_ADC[ihit],tree->LaBr_Hits_ADC[jhit]);
			}
		}


	}
	printf("\r%lld ent of %lld, %.1f%%", ient, Entries, (float)ient/Entries*100);
	printf("\n");


	TFile *ofile = new TFile("Ehist.root", "recreate");


	TCanvas *c1 = new TCanvas("c_h1_EHPGe", "c_h1_EHPGe", 1600,  600);
	c1->Divide(4,1);
	for (int ich_HPGe=0; ich_HPGe<4; ich_HPGe++){
		c1->cd(1+ich_HPGe)->SetLogy();
		h1_EHPGe[ich_HPGe]->Draw();
		h1_EHPGe[ich_HPGe]->Write();
	}

	TCanvas *c2 = new TCanvas("c_h1_ELaBr", "c_h1_ELaBr", 1600,  600);
	c2->Divide(4,1);
	for (int ich_LaBr=0; ich_LaBr<4; ich_LaBr++){
		c2->cd(1+ich_LaBr)->SetLogy();
		h1_ELaBr[ich_LaBr]->Draw();
		h1_ELaBr[ich_LaBr]->Write();
	}

	TCanvas *c3 = new TCanvas("c_h2_EHPGe_ELaBr", "c_h2_EHPGe_ELaBr", 1600, 1000);
	c3->Divide(4,4);
	for(int ich_HPGe=0; ich_HPGe<4; ich_HPGe++){
		for(int ich_LaBr=0; ich_LaBr<4; ich_LaBr++){
			c3->cd(1+ich_HPGe+4*ich_LaBr)->SetLogz();
			h2_EHPGe_ELaBr[ich_HPGe][ich_LaBr]->Draw("colz");
			h2_EHPGe_ELaBr[ich_HPGe][ich_LaBr]->Write();
		}
	}
	TCanvas *c4 = new TCanvas("c_h2_EHPGe_EHPGe", "c_h2_EHPGe_EHPGe", 1600, 1000);
	c4->Divide(4,4);
	for(int ich_HPGe=0; ich_HPGe<4; ich_HPGe++){
		for(int jch_HPGe=0; jch_HPGe<4; jch_HPGe++){
			c4->cd(1+ich_HPGe+4*jch_HPGe)->SetLogz();
			h2_EHPGe_EHPGe[ich_HPGe][jch_HPGe]->Draw("colz");
			h2_EHPGe_EHPGe[ich_HPGe][jch_HPGe]->Write();
		}
	}
	TCanvas *c5 = new TCanvas("c_h2_ELaBr_ELaBr", "c_h2_ELaBr_ELaBr", 1600, 1000);
	c5->Divide(4,4);
	for(int ich_LaBr=0; ich_LaBr<4; ich_LaBr++){
		for(int jch_LaBr=0; jch_LaBr<4; jch_LaBr++){
			c5->cd(1+ich_LaBr+4*jch_LaBr)->SetLogz();
			h2_ELaBr_ELaBr[ich_LaBr][jch_LaBr]->Draw("colz");
			h2_ELaBr_ELaBr[ich_LaBr][jch_LaBr]->Write();
		}
	}



}
