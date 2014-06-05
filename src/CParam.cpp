#include "CData.h"
#include "CParam.h"
#include "margin_conditions.h"
CParam::~CParam() {
	/*
	delete [] zI;
	delete [] nuK;
	delete [] log_nuK;
	delete [] countK;


	delete [] pZeroMC_I;
	delete [] z2_Nmax;

	delete [] count_partition;
	*/
}

void CParam::class_construct(int J, int K, int L, int *levelsJ, int *cumLevelsJ, int n){
	//init members	
	this->J=J; this->K=K; this->n = n; 
	this->levelsJ = levelsJ;
	this->cumLevelsJ = cumLevelsJ;
	this->L = L;

	//allocate
	zI = new int[n];
	nuK = new double[K];
	log_nuK = new double[K];
	countK = new int[K];

	aux_dirCumJK = (int **)CArrayND<int>::CreateArray(2, cumLevelsJ[J], K);
	psiJKL = (double **) CArrayND<double>::CreateArray(2, cumLevelsJ[J], K);
}

void CParam::class_construct(int Nmis_max, int** MCZ_, int nZeroMC, int **x){
	//this assumes that base class has been initialized
	//initialize members.
	this->nZeroMC = nZeroMC;
	if (nZeroMC > 0) {
		this->Nmis = Nmis;
		this->N_mis_max = Nmis_max;
		//allocate extra.
		pZeroMC_I = new double[nZeroMC];
		z2_Nmax = new int[Nmis_max];
		count_partition = new unsigned int[nZeroMC];

		MCZ = (int **)CArrayND<int>::CreateArray(2, this->nZeroMC, J); 
		x2_NMax_J = (int**)CArrayND<int>::CreateArray(2, Nmis_max, J);
		//copy MCZ
		std::copy(MCZ_[0], MCZ_[0] + this->nZeroMC * J, this->MCZ[0]); 
	} else {
		this->Nmis = 0;
		this->N_mis_max = 0;
	}
	
	xIJ = (int **)CArrayND<int>::CreateArray(2, n, J); 
	//fill x with data
	std::copy(x[0], x[0] + this->n * J, xIJ[0]); //NOTE THAT HERE X INCLUDES MISSING VALUES!!! HAVE TO INITIALIZE.
	
}

void CParam::initizalize(MTRand& mt){
	//Initializes the parameters for the chain.
	int j,k,l;
	for (k =0; k < K; k++){
		this->nuK[k] = 1.0 / double(K);
	}

	for(j = 0; j < J; j++){
		for(k = 0; k < K; k++){
			for(l = 0; l < this->levelsJ[j]; l++){
				psiJKL[cumLevelsJ[j]+l][k] = 1.0 / double(levelsJ[j]);
			}
		}
	}

	//just the extra.
	double logk = -log(double(K));
	for( k = 0; k < K; k++) { log_nuK[k] = logk;}
	alpha = 1 ; //initialize at full spread: uniform prior.


	std::vector<double> p(this->L); //reserve at least the maximum number of levels.
	std::fill(p.begin(), p.end(), 1.0);

	prob_zero = 0;
	Nmis = 0;
	for (int i = 0; i < this->nZeroMC; i++){
		count_partition[i] = 0;
	}
	memset(this->countK, 0, sizeof(int)*this->K);
	//Initialize values for xIJ.
	bool badvalue;
	for(int i = 0; i < n; ++i){
		std::vector<int> x_working(xIJ[i], xIJ[i]+J);
		do{
			for (int j = 0; j < J; ++j){
				if (xIJ[i][j] == -1) {
					x_working[j] =SpecialFunctions::discreterand(this->levelsJ[j], &(p[0]),mt);
				}
			}
			//check
			badvalue = false;
      if (this->nZeroMC > 0) {
  			for (int ii  = 0; ii < this->nZeroMC; ++ii){
  				if (!check_x_notin_mu(x_working.begin(), x_working.end(), MCZ[ii])) {
  					badvalue = true; 
  					break; 
  				}
  			}
      }
		} while ( badvalue );
		std::copy<std::vector<int>::iterator, int*>(x_working.begin(), x_working.end(), xIJ[i]);
	}
}
