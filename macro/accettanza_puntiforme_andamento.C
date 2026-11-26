#define N 1E7
#define n 10

void accettanza_puntiforme_andamento()
    {        
        Double_t R=0.1;
        Double_t D[n],epsilon[n],err_D[n],err_epsilon[n];
        Double_t theta,phi,x,y,z;                                      
        Double_t theta_max,X,Y;
        Int_t count=0;
        TCanvas *c=new TCanvas("","",600,600);
        TMultiGraph *mg=new TMultiGraph();
        TGraphErrors *acc[n];
        TF1 *f=new TF1("f","TMath::Sin(x)",0,TMath::Pi()/2.);    

        for(Int_t i=0;i<n;i++)
            {
                D[i]=0.2*i;
                err_D[i]=0;
            }
        for(Int_t i=0;i<n;i++,R+=0.1)
            {
                for(Int_t j=0;j<n;j++,count=0)
                    { 
                        theta_max=TMath::ATan(R/D[j]);
                        for(Int_t k=0;k<N;k++)
                            {
                                theta=f->GetRandom(0,TMath::Pi()/2.);                                
                                phi=gRandom->Uniform(0,2*TMath::Pi());
                                if(theta<theta_max)
                                    {
                                        count++;
                                    }
                                else
                                    {
                                        continue;
                                    }
                            }
                        epsilon[j]=count/(2*N);
                        err_epsilon[j]=sqrt(count)/(2*N);                                        
                    }
                acc[i]=new TGraphErrors(n,D,epsilon,err_D,err_epsilon);
                acc[i]->SetMarkerColor(i+1);
                acc[i]->SetLineColor(i+1);
                acc[i]->SetMarkerStyle(20);
                acc[i]->GetXaxis()->SetTitle("distanza D (m)");
                acc[i]->GetYaxis()->SetTitle("accettanza #epsilon");
                mg->Add(acc[i]);
            }
            mg->Draw("ALP");
        
    }