#ifndef _CLcm_H
#define _CLcm_H

#include <stdio.h>
#include <stdlib.h>
#include "CParam.h"
#include "MersenneTwister.h"
#include "SpecialFunctions.h"

class CLcm {
public:
	//Constructors
	CLcm(CData *_data, CParam *_par) : par(_par), data(_data){
		class_construct(data, par);
	}
	CLcm(CData* _data, int K, int Nmis_max,  double a_alpha, double b_alpha)
			: data(_data){
				par = new CParam(data->J, K, data->L, data->levelsJ, data->cumLevelsJ,data->n, Nmis_max, data->ZeroMC_IJ, data->nZeroMC, a_alpha, b_alpha,data->x);
		class_construct(data, par);
	}
	void Update();
	
	double predict(int* xJ);
	double predict_renorm(int* xJ);
	void Initializes(); //a more careful initialization than the defalt.
  void Initializes_no_MCZ();
	
	CParam *par;
	CParam *par_temp; //temp solution, only to be used during initialization

	MTRand mt;
	int NmisOverflow;
private:
	CData* data;
	void class_construct(CData* data, CParam* par){
		//r = dan_initRandom(); //initializes a random number generator
		//mt.seed(1234);
		mt.seed();
		current_iteration = 0;
		burnin=1;
		thining=1;
		iterations = 99;

		K = par->K;
		J = data->J; 
		n = data->n; 

	}
protected:
	int J, n, K; //local copies. bad idea...
	//Full conditional samplers
	void sam_x(); //imputation step.
	void sam_nu(); 
	void sam_psi();
	void sam_z();
	void sam_Z2_X2();
	void sam_Nmis();
	void sam_alpha();
	void compute_probs_miss();

protected:
	int iterations;
	int current_iteration;
	int thining;
	int burnin;
};


#endif  //_CLcm_H
