/*
****Compton Scattering*****
*
*Calculates energy, momentum, and angles for real Compton scattering events in lab and CM frames.
*Graphs scattered photon energy, recoil proton kinetic energy, recoil proton angle,
*for set incident photon energy over a range of scattered photon angles.
*
* ****Alicia Postuma, Mount Allison University, 2020*****
*/

#include "physics.h"

//function for finding momentum from energy and mass
Double_t momentum(Double_t energy, Double_t mass){
  if (energy>=mass) { //necessary condition for particle
    return(sqrt(energy*energy - mass*mass));
  } else {
    return(-1); //error
  }
}

//function for finding energy from momentum and mass
Double_t energy(Double_t momentum, Double_t mass){
  return(sqrt(momentum*momentum+mass*mass));
}

//macro to find Compton Scattering quantities in the lab frame
void ComptonLab(Double_t kE=200, Double_t qth=45){ //input initial photon energy and scattering angle

  //define variables
  //k: initial photon, p: target proton, q: scattered photon, p1: recoil proton
  //E: energy, m: mass, P: momentum, th: theta (polar angle), phi: phi (azimulthal angle); 
  Double_t km, kP, kth, kphi; 
  Double_t pE, pm, pP, pth, pphi;
  Double_t qE, qm, qP, qphi;
  Double_t p1E, p1m, p1P, p1th, p1phi;

  TLorentzVector k,p,q,p1; //represent each particle by energy-momentum 4-vector

  //define all quantities for incident photon
  //kE defined in input of macro
  km=0; //mass of photon
  kth=0; //choose reference frame such that initial angles are zero
  kphi=0;
  kP=momentum(kE,km); //use pre-defined function to calculate momentum

  k.SetPxPyPzE(0,0,kP,kE); //set 4-vector for photon beam with z as direction of motion

  //define all quantities for target proton
  pm=kMP_MEV; //proton mass from physics.h
  pP=0; //target is at rest
  pE=energy(pP,pm); //use pre-defined function to calculate energy
  pth=0; //initial angles are zero
  pphi=0;

  p.SetPxPyPzE(0,0,0,pE); //4-vector for a stationary target with no momentum

  //calculate quantities for scattered photon
  //qth defined in input of macro
  qth*=kD2R; //convert to radians
  qE=kE/(1+(kE/pE)*(1-cos(qth))); //Compton scattering equation
  qm=km; //mass does not change in collision
  qP=momentum(qE,qm); //calculate new total momentum
  qphi=0; //because of definition of phi in our reference frame

  //calculate components of momentum to set the 4-vector
  Double_t qPx, qPy, qPz;
  qPx=qP*sin(qth)*cos(qphi);
  qPy=qP*sin(qth)*sin(qphi);
  qPz=qP*cos(qth);

  q.SetPxPyPzE(qPx,qPy,qPz,qE); //4-vector for the scattered photon

  p1=k+p-q; //conservation of 4-momentum

  //now, calculate all quantities for the recoil proton
  p1E=p1.E(); //calculate energy from the 4-vector
  p1m=pm; //mass does not change in collision
  p1P=p1.Vect().Mag(); //calculate momentum from the 4-vector
  p1th=p1.Theta(); //find angles from the 4-vector
  p1phi=p1.Phi();


  //print all results
  cout<<"  Energy    Mass   Kinetic E.   Momentum  Theta  Phi"<<endl; //titles for a result table
  cout<<"  (MeV)   (MeV/c^2)   (MeV)      (MeV/c)  (deg) (deg)"<<endl;

  TString line; //define a string: a bunch of characters that will make up each line of the table
  //for each line of the table, assign a set of variables with a certain pecision to the string "line", then print the string
  line=Form("k: %5.1f   %5.1f      %5.1f      %5.1f   %5.1f %5.1f\n", kE, km, kE-km, kP, kth/kD2R, kphi/kD2R);
  cout<<line; //first line: incident photon k
  line=Form("p: %5.1f   %5.1f      %5.1f      %5.1f   %5.1f %5.1f\n", pE, pm, pE-pm, pP, pth/kD2R, pphi/kD2R);
  cout<<line; //second line: target proton p
  line=Form("q: %5.1f   %5.1f      %5.1f      %5.1f   %5.1f %5.1f\n", qE, qm, qE-qm, qP, qth/kD2R, qphi/kD2R);
  cout<<line; //third line: scattered photon q
  line=Form("p1: %5.1f  %5.1f      %5.1f      %5.1f   %5.1f %5.1f\n", p1E, p1m, p1E-p1m, p1P, p1th/kD2R, p1phi/kD2R);
  cout<<line; //fourth line: recoil proton p1
}


//find Compton Scattering quantities in CM frame using TLorentzVector Boost capabilities
//uses TwoBodyCM() from TwoBodyMacros.C by DH as a template
void ComptonBoost(Double_t kE=200, Double_t qth_cm=45){
  Double_t km, qE_cm, qP_cm, pm; //only need a few variables if everything is in vectors
  TLorentzVector k, p, q, p1; //lab frame
  TLorentzVector pIn; //total incoming momentum, will be used to define the boost
  TLorentzVector k_cm, p_cm, q_cm, p1_cm; //cm frame
  TVector3 cmBoost, labBoost; //boosts: to switch between frames

  pm= kMP_MEV; //proton mass
  km=0; //photon mass

  k.SetPxPyPzE(0,0,kE,kE); //photon with kinetic energy in z direction
  p.SetPxPyPzE(0,0,0,pm); //stationary target

  pIn=k+p; //total incoming momentum and energy

  labBoost=pIn.BoostVector(); //to change from cm to lab frame
  cmBoost=-pIn.BoostVector(); //to change from lab to CM frame

  //find intial momentums and energies in CM frame
  k_cm=k; //initially take cm momentum as lab momentum k
  k_cm.Boost(cmBoost); //then apply a Lorentz boost to get into cm frame
  p_cm=p; //similarly, take lab momentum p
  p_cm.Boost(cmBoost); //and boost to cm frame

  Double_t S=2*kE*pm+pm*pm; //kinematic paramater - for intermediate calculations
  qE_cm=(S-pm*pm+km*km)/(2*sqrt(S)); //equation derived in notes by DH
  qP_cm=momentum(qE_cm,km); //use momentum function

  //find cm momentum components
  Double_t qphi_cm=0; //azimulthal angle zero in our coordinate system
  qth_cm*=kD2R; //convert angle to radians
  Double_t qPx_cm, qPy_cm, qPz_cm;
  qPx_cm=qP_cm*sin(qth_cm)*cos(qphi_cm);
  qPy_cm=qP_cm*sin(qth_cm)*sin(qphi_cm);
  qPz_cm=qP_cm*cos(qth_cm);

  q_cm.SetPxPyPzE(qPx_cm,qPy_cm,qPz_cm,qE_cm); //create the four vector

  q=q_cm; //take calculated 4-vector
  q.Boost(labBoost); //and boost back to lab frame

  p1=k+p-q; //conservation of momentum and energy (in lab frame)

  p1_cm=p1; //take 4-vector calculated in lab frame
  p1_cm.Boost(cmBoost); //boost to cm frame

  //output: same form as before
  cout<<"     Energy    Mass   Kinetic E.  Momentum  Theta  Phi"<<endl;
  cout<<"     (MeV)  (MeV/c^2)   (MeV)      (MeV/c)  (deg) (deg)"<<endl;

  TString line;

  line=Form("k:    %5.1f   %5.1f     %5.1f       %5.1f  %5.1f %5.1f\n",  k.E(), km, k.E()-km, k.Vect().Mag(), k.Theta()/kD2R, k.Phi()/kD2R);
  cout<<line;
  line=Form("p:    %5.1f   %5.1f     %5.1f       %5.1f  %5.1f %5.1f\n",    p.E(), pm, p.E()-pm, p.Vect().Mag(), p.Theta()/kD2R, p.Phi()/kD2R);
  cout<<line;
  line=Form("q:    %5.1f   %5.1f     %5.1f       %5.1f  %5.1f %5.1f\n", q.E(), km, q.E()-km, q.Vect().Mag(), q.Theta()/kD2R, q.Phi()/kD2R);
  cout<<line;
  line=Form("p1:   %5.1f   %5.1f     %5.1f       %5.1f  %5.1f %5.1f\n",    p1.E(), pm, p1.E()-pm, p1.Vect().Mag(), p1.Theta()/kD2R, p1.Phi()/kD2R);
  cout<<line;
  line=Form("k_cm: %5.1f   %5.1f     %5.1f       %5.1f  %5.1f %5.1f\n",k_cm.E(), km, k_cm.E()-km, k_cm.Vect().Mag(), k_cm.Theta()/kD2R, k_cm.Phi()/kD2R);
  cout<<line;
  line=Form("p_cm: %5.1f   %5.1f     %5.1f       %5.1f  %5.1f %5.1f\n",p_cm.E(), pm, p_cm.E()-pm, p_cm.Vect().Mag(), p_cm.Theta()/kD2R, p_cm.Phi()/kD2R);
  cout<<line;
  line=Form("q_cm: %5.1f   %5.1f     %5.1f       %5.1f  %5.1f %5.1f\n",q_cm.E(), km, q_cm.E()-km, q_cm.Vect().Mag(), q_cm.Theta()/kD2R, q_cm.Phi()/kD2R);
  cout<<line;
  line=Form("p1_cm:%5.1f   %5.1f     %5.1f       %5.1f  %5.1f %5.1f\n",p1_cm.E(), pm, p1_cm.E()-pm, p1_cm.Vect().Mag(), p1_cm.Theta()/kD2R, p1_cm.Phi()/kD2R);
  cout<<line;
}

