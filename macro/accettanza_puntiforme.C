#define N 1E7

void accettanza_puntiforme()
    {
        TCanvas *c[4];                                          
        Double_t D,R;                                                 
        cout<<"distanza dal rivelatore: ";                              
        cin>>D;
        cout<<"raggio del rivelatore: ";
        cin>>R;
        Double_t theta,phi,x,y,z;                                       
        Double_t theta_max,X,Y,a,err_a;                                 
        Int_t count=0;
        TH3D *htot=new TH3D("","",100,-1,1,100,-1,1,100,-1,1);          
        TH3D *hinc=new TH3D("","",100,-1,1,100,-1,1,100,-1,1);          
        TH2D *hrivelatore=new TH2D("","rivelatore",100,-R,R,100,-R,R);    
        TF1 *f=new TF1("f","TMath::Sin(x)",0,TMath::Pi()/2.);          

        theta_max=TMath::ATan(R/D);
        for(Int_t i=0;i<N;i++)
            {
                theta=f->GetRandom(0,TMath::Pi()/2.);                   
                phi=gRandom->Uniform(0,2*TMath::Pi());
                x=TMath::Sin(theta)*TMath::Cos(phi);
                y=TMath::Sin(theta)*TMath::Sin(phi);
                z=TMath::Cos(theta);
                htot->Fill(x,y,z);

                if(theta<theta_max)                                     
                    {
                        X=D*TMath::Tan(theta)*TMath::Cos(phi);
                        Y=D*TMath::Tan(theta)*TMath::Sin(phi);
                        count++;
                        hinc->Fill(x,y,z);
                        hrivelatore->Fill(X,Y);
                    }
            }

        a=count/(2*N);                                                      
        err_a=TMath::Sqrt(count)/(2*N);
        cout<<"accettanza: "<<a<<" pm " <<err_a<<endl;
        for(Int_t i=0;i<4;i++)
            {
                c[i]=new TCanvas("","",500,500);
            }
        c[0]->cd();
        htot->SetStats(0);
        htot->Draw();
        c[1]->cd();
        hinc->SetStats(0);
        hinc->Draw();
        c[2]->cd();
        hrivelatore->SetStats(0);
        hrivelatore->Draw("COLZ");
        c[3]->cd();
        hrivelatore->SetStats(0);
        hrivelatore->Draw("LEGO2Z");
    }