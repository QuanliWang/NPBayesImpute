\name{Rcpp_Lcm-class}
\Rdversion{1.1}
\docType{class}
\alias{Rcpp_Lcm-class}

\title{Class \code{"Rcpp_Lcm"}}
\description{
This is the Rcpp class that implements the main functionalities wihin the library.
}
\section{Extends}{
Class \code{"\linkS4class{C++Object}"}, directly.

All reference classes extend and inherit methods from \code{"\linkS4class{envRefClass}"}.
}

\examples{
showClass("Rcpp_Lcm")
}
\keyword{classes}
\section{Fields}{
  \describe{
    \item{\code{CurrentIteration}:}{The total number of iterations that have been run so far.
  }
    \item{\code{EnableTracer}:}{To check tracer status or to enable/disable the tracer.}
    \item{\code{MCZ}:}{the disjointed structural zero matrix.}
    \item{\code{snapshot}:}{fitted model parameters from the last ierations.}
    \item{\code{traceable}:}{list of model parameters that can be traced by the tracer.}
    \item{\code{traced}:}{list of model parameters that are traced.}
  }
}
\section{Methods}{
  \describe{
    \item{\code{SetTrace(paralist,num_of_iterations)}:}{set parameters to be traced.\describe{
            \item{paralist:}{a list of parameters to be traced.}
            \item{num_of_iterations:}{the maximum number of traced iterations.}
            }
    }
    \item{\code{Run(burnin, iter, thinning)}:}{run MCMC iterations.
      \describe{
            \item{burnin:}{number of burnins}
            \item{iter:}{number of MCMC iterations.}
            \item{thinning:}{thinning parameter.}
            }
    }
    \item{\code{Resume()}:}{resume from an interrupted call to run method.}
    \item{\code{Parameters(paralist)}:}{retrieve a selected list of model parameters from last MCMC iteration.\describe{
            \item{paralist:}{a list of parameters to be traced.}
            }
    }
    \item{\code{GetTrace()}:}{retrieve all traced iterations. }
  }
}
