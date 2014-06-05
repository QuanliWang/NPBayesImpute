/*
	CData class declaration.
	This function holds the data for the computations.
	It includes accessors and a function for reading the data from files
*/

#if !defined(_CDATA_H)
#define _CDATA_H
#include <vector>
class CData {
public:
	CData(); //Constructor
	~CData(); //destructor

	//data storage. These should be private, but this is going to be more efficient.
	int n; //sample size
	int J;
	int L; //max #of levels (for dimentions)
	int **x; //responses vector
	
	int *levelsJ; // (levelsJ[j] = #levels of variable j)
	int *cumLevelsJ; 

	int** ZeroMC_IJ;
	int nZeroMC;	

	int M; //number of patterns
	int *cell_countM; //count of the cell.
	
	
	void Process_MC();
	void SetData(int *x_flat, int J, int n, int* ZeroMC_flat, int nZeroMC, int *levels);
	void SetData(std::vector<int>& x_flat, int J, int n, std::vector<int>& ZeroMC_flat, int nZeroMC, std::vector<int>& levels);
};

#endif  //_CDATA_H
