#define N 1E5
#define n 100
#define d 0.3

void accettanza_super()
    {
        TH2D *h2=new TH2D("","",n,d,d*n,n,0,d*(n-1));
        TF2 *ffit=new TF2("ffit","[0]-[0]*(x/pow(x*x+y*y,0.5))",d,d*n,0,d*(n-1));
        TF1 *f=new TF1("f","TMath::Sin(x)",0,TMath::Pi()/2);
        TCanvas *c=new TCanvas("","",700,700);
        Int_t count=0;
        Double_t theta,phi,theta_max,a,chi2;
        Double_t R=d,D=0;
        for(Int_t i=0;i<n;i++,R+=d,D=0)
            {
                for(Int_t j=0;j<n;j++,D+=d,count=0)
                    {
                        theta_max=TMath::ATan(R/D);
                        for(Int_t k=0;k<N;k++)
                            {
                                theta=f->GetRandom(0,TMath::Pi()/2);
                                if(theta<theta_max)
                                    {
                                        count++;
                                    }
                            }
                        a=count/(2*N);
                        h2->Fill(D,R,a);
                    }
            }
        h2->Draw("LEGO2Z");
        ffit->SetParameter(0,0.5);
        h2->Fit(ffit);
        gStyle->SetOptFit(0100);
    }
