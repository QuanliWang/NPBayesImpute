
#include <Rcpp.h>
#include <stdio.h>
#include <stdlib.h>
#include "CData.h"
#include "CLcm.h"
#include "CTrace.h"
#include "CEnv.h"

/*
void Iterate(CEnv* model, int iters) {
	for (int i = 0; i < iters; i++){
		model->m->Update();
		Rprintf( "iter = %d  kstar = %d alpha = %g Nmis = %d\n", i, model->m->par->k_star,model->m->par->alpha, model->m->par->Nmis ) ;
	}
}
*/

RCPP_MODULE(clcm){
    using namespace Rcpp;
	using namespace R;
	
	class_<CEnv>( "Lcm" )
    // expose the default constructor
    .constructor<Rcpp::IntegerMatrix, Rcpp::IntegerMatrix, int, int,  double, double>()

	.method( "SetTrace", &CEnv::SetTrace, "Set parameters to be traced" )
	.method( "GetTrace", &CEnv::GetTrace, "Get parameters to be traced" )
	.method( "SetXAsDataframe", &CEnv::SetXAsDataframe, "test" )
	
	.method( "Run", &CEnv::Run, "Run MCMC")
	.method( "Resume", &CEnv::Resume, "Resume MCMC")

	.method( "Parameters", &CEnv::GetParameters, "Output specified parameters" )
	.property( "snapshot", &CEnv::GetData, "Retrieve iteration result" )
	.property( "traceable", &CEnv::traceable, "list traceable parameters" )
	.property( "traced", &CEnv::traced, "list traceable parameters" )
	.property( "CurrentIteration", &CEnv::GetCurrentIter, "Show current iteration" )
	.property( "EnableTracer", &CEnv::GetTracerStatus, &CEnv::EnableTracer, "Show current iteration" )
	.property( "MCZ", &CEnv::GetMCZ, "Retrieve MCZ matrix" )

    ;
	/* disable this interface for now
	class_<CEnv>( "Lcm2" )
    // expose the default constructor
    .constructor<Rcpp::IntegerMatrix, Rcpp::IntegerMatrix, int, int,  double, double>()	
	
	.method( "Initialize", &CEnv::Initialize, "MCMC Initializztion" )
	.method( "Update", &CEnv::Update, "Do one MCMC iteration" )
	.method( "Iterate", &CEnv::Iterate, "Do iters iteration" )
	
	.method( "Parameters", &CEnv::GetParameters, "Output specified parameters" )
	.property( "snapshot", &CEnv::GetData, "Retrieve iteration result" )
	.property( "parameterlist", &CEnv::traceable, "list traceable parameters" )

    ;
	*/
}                     

