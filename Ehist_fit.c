//#include "Lst2RootTree_PhyDet.h"
//#include "HPGe_Hit.h"
//#include "LaBr_Hit.h"
//#include "TAC_Hit.h"
#include "Energy_fit_para.h"

void Ehist_fit(){
	TFile *histfile = new TFile("Ehist.root", "read");

	TH1D *h1_EHPGe[4];
	for (int ich_HPGe=0; ich_HPGe<4; ich_HPGe++){
		h1_EHPGe[ich_HPGe] = (TH1D*) histfile->Get(Form("h1_EHPGe_ch%d", ich_HPGe));
//new TH1D(Form("h1_EHPGe_ch%d", ich_HPGe), Form("h1_EHPGe_ch%d; ADC; count", ich_HPGe), 32768/ 8 *5/8, 0, 32768/4*5/8);
	}
	TH1D *h1_ELaBr[4];
	for (int ich_LaBr=0; ich_LaBr<4; ich_LaBr++){
		h1_ELaBr[ich_LaBr] = (TH1D*) histfile->Get(Form("h1_ELaBr_ch%d", ich_LaBr));
//new TH1D(Form("h1_ELaBr_ch%d", ich_LaBr), Form("h1_ELaBr_ch%d; ADC; count", ich_LaBr), 32768/ 8*5/8, 0, 32768/2*5/8);
	}

/*
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
*/

	const Double_t width=3;


	TH1D *h1_EHPGe_fit[2][hpge_nch];
	TF1 *f1_HPGe[2][hpge_nch];
	for (int ipeak=0; ipeak<2; ipeak++){
		for (int ich_HPGe=0; ich_HPGe<hpge_nch; ich_HPGe++){
			h1_EHPGe_fit[ipeak][ich_HPGe] = new TH1D();
			h1_EHPGe[ich_HPGe]->Copy(*h1_EHPGe_fit[ipeak][ich_HPGe]);

			f1_HPGe[ipeak][ich_HPGe] = new TF1(Form("f1_HPGe_peak%d_ch%d", ipeak, ich_HPGe), "gaus(0)+[3]+[4]*(x-[1])", hpge_mean[ipeak][ich_HPGe]-width*hpge_sigma[ipeak][ich_HPGe], hpge_mean[ipeak][ich_HPGe]+width*hpge_sigma[ipeak][ich_HPGe]);
			f1_HPGe[ipeak][ich_HPGe]->SetParameter(0, hpge_amp[ipeak][ich_HPGe]);
			f1_HPGe[ipeak][ich_HPGe]->SetParameter(1, hpge_mean[ipeak][ich_HPGe]);
			f1_HPGe[ipeak][ich_HPGe]->SetParameter(2, hpge_sigma[ipeak][ich_HPGe]);

			f1_HPGe[ipeak][ich_HPGe]->SetParLimits(0, 0, 100000000);
			f1_HPGe[ipeak][ich_HPGe]->SetParLimits(1, hpge_mean[ipeak][ich_HPGe]-width*hpge_sigma[ipeak][ich_HPGe], hpge_mean[ipeak][ich_HPGe]+width*hpge_sigma[ipeak][ich_HPGe]);
			f1_HPGe[ipeak][ich_HPGe]->SetParLimits(2, 0.3*hpge_sigma[ipeak][ich_HPGe], 5*hpge_sigma[ipeak][ich_HPGe]);
			f1_HPGe[ipeak][ich_HPGe]->SetParLimits(3, 0, 100000000);
		}
	}

	TCanvas *c1 = new TCanvas("c_h1_EHPGe", "c_h1_EHPGe", 1600, 1000);
	c1->Divide(4,2);
	for (int ipeak=0; ipeak<2; ipeak++){
		for (int ich_HPGe=0; ich_HPGe<4; ich_HPGe++){
			c1->cd(1+ich_HPGe+ipeak*hpge_nch)->SetLogy();
			c1->cd(1+ich_HPGe+ipeak*hpge_nch)->SetGridx();
			h1_EHPGe_fit[ipeak][ich_HPGe]->GetXaxis()->SetRangeUser(hpge_mean[ipeak][ich_HPGe]-2*width*hpge_sigma[ipeak][ich_HPGe], hpge_mean[ipeak][ich_HPGe]+2*width*hpge_sigma[ipeak][ich_HPGe]);
			h1_EHPGe_fit[ipeak][ich_HPGe]->Draw();
			h1_EHPGe_fit[ipeak][ich_HPGe]->Fit(f1_HPGe[ipeak][ich_HPGe], "R EM");
		}
	}


	TH1D *h1_ELaBr_fit[2][labr_nch];
	TF1 *f1_LaBr[2][labr_nch];
	for (int ipeak=0; ipeak<2; ipeak++){
		for (int ich_LaBr=0; ich_LaBr<labr_nch; ich_LaBr++){
			h1_ELaBr_fit[ipeak][ich_LaBr] = new TH1D();
			h1_ELaBr[ich_LaBr]->Copy(*h1_ELaBr_fit[ipeak][ich_LaBr]);

			f1_LaBr[ipeak][ich_LaBr] = new TF1(Form("f1_LaBr_peak%d_ch%d", ipeak, ich_LaBr), "gaus(0)+[3]+[4]*(x-[1])", labr_mean[ipeak][ich_LaBr]-width*labr_sigma[ipeak][ich_LaBr], labr_mean[ipeak][ich_LaBr]+width*labr_sigma[ipeak][ich_LaBr]);
			f1_LaBr[ipeak][ich_LaBr]->SetParameter(0, labr_amp[ipeak][ich_LaBr]);
			f1_LaBr[ipeak][ich_LaBr]->SetParameter(1, labr_mean[ipeak][ich_LaBr]);
			f1_LaBr[ipeak][ich_LaBr]->SetParameter(2, labr_sigma[ipeak][ich_LaBr]);

			f1_LaBr[ipeak][ich_LaBr]->SetParLimits(0, 0, 100000000);
			f1_LaBr[ipeak][ich_LaBr]->SetParLimits(1, labr_mean[ipeak][ich_LaBr]-width*labr_sigma[ipeak][ich_LaBr], labr_mean[ipeak][ich_LaBr]+width*labr_sigma[ipeak][ich_LaBr]);
			f1_LaBr[ipeak][ich_LaBr]->SetParLimits(2, 0.3*labr_sigma[ipeak][ich_LaBr], 5*labr_sigma[ipeak][ich_LaBr]);
			f1_LaBr[ipeak][ich_LaBr]->SetParLimits(3, 0, 100000000);
		}
	}

	TCanvas *c2 = new TCanvas("c_h1_ELaBr", "c_h1_ELaBr", 1600, 1000);
	c2->Divide(4,2);
	for (int ipeak=0; ipeak<2; ipeak++){
		for (int ich_LaBr=0; ich_LaBr<4; ich_LaBr++){
			c2->cd(1+ich_LaBr+ipeak*labr_nch)->SetLogy();
			c2->cd(1+ich_LaBr+ipeak*labr_nch)->SetGridx();
			h1_ELaBr_fit[ipeak][ich_LaBr]->GetXaxis()->SetRangeUser(labr_mean[ipeak][ich_LaBr]-2*width*labr_sigma[ipeak][ich_LaBr], labr_mean[ipeak][ich_LaBr]+2*width*labr_sigma[ipeak][ich_LaBr]);
			h1_ELaBr_fit[ipeak][ich_LaBr]->Draw();
			h1_ELaBr_fit[ipeak][ich_LaBr]->Fit(f1_LaBr[ipeak][ich_LaBr], "R EM");
		}
	}


	

	printf("HPGe\n");
	for (int ipeak=0; ipeak<2; ipeak++){
		for (int ich_HPGe=0; ich_HPGe<4; ich_HPGe++){
			printf("%.5e, ", f1_HPGe[ipeak][ich_HPGe]->GetParameter(0));
		}
		printf("\b\b \t // amp peak%d \n", ipeak);
	}
	for (int ipeak=0; ipeak<2; ipeak++){
		for (int ich_HPGe=0; ich_HPGe<4; ich_HPGe++){
			printf("%.5e, ", f1_HPGe[ipeak][ich_HPGe]->GetParameter(1));
		}
		printf("\b\b \t // mean peak%d \n", ipeak);
	}
	for (int ipeak=0; ipeak<2; ipeak++){
		for (int ich_HPGe=0; ich_HPGe<4; ich_HPGe++){
			printf("%.5e, ", f1_HPGe[ipeak][ich_HPGe]->GetParameter(2));
		}
		printf("\b\b \t // sigma peak%d \n", ipeak);
	}

	printf("LaBr\n");
	for (int ipeak=0; ipeak<2; ipeak++){
		for (int ich_LaBr=0; ich_LaBr<4; ich_LaBr++){
			printf("%.5e, ", f1_LaBr[ipeak][ich_LaBr]->GetParameter(0));
		}
		printf("\b\b \t // amp peak%d \n", ipeak);
	}
	for (int ipeak=0; ipeak<2; ipeak++){
		for (int ich_LaBr=0; ich_LaBr<4; ich_LaBr++){
			printf("%.5e, ", f1_LaBr[ipeak][ich_LaBr]->GetParameter(1));
		}
		printf("\b\b \t // mean peak%d \n", ipeak);
	}
	for (int ipeak=0; ipeak<2; ipeak++){
		for (int ich_LaBr=0; ich_LaBr<4; ich_LaBr++){
			printf("%.5e, ", f1_LaBr[ipeak][ich_LaBr]->GetParameter(2));
		}
		printf("\b\b \t // sigma peak%d \n", ipeak);
	}








/*	TCanvas *c3 = new TCanvas("c_h2_EHPGe_ELaBr", "c_h2_EHPGe_ELaBr", 1600, 1000);
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
*/


}
