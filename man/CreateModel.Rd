\name{CreateModel}
\alias{CreateModel}
\title{
Create and initialize the model object
}
\description{
This is the fist function to be called to use he package, which create a model object that will be referenced in all following calls.
}
\usage{
CreateModel(X, MCZ, K, Nmax, aalpha, balpha)
}
\arguments{
  \item{X}{ a dataframe for input categorical data.}
  \item{MCZ}{ a dataframe for input structural zeros.}
  \item{K}{the number of mixture compoments.
}
  \item{Nmax}{the maximum number of observations that can be sampled from structural zero regions.}
  \item{aalpha}{the hyper parameter 'a' for alpha in stick-breaking prior distribution.}
  \item{balpha}{the hyper parameter 'b' for alpha in stick-breaking prior distribution.}
}
\details{This is the first function one should call to use the library. It will first do the data conversion from R dataframes to C++ objects. It will also generate the disjointed MCZs from input structrual zeros. The returned model object will be referenced in all subsequent calls. }

\value{
The returned model object will be referenced in all subsequent calls.
}
\examples{
require(NPBayesImpute)
data('NYexample')

#create the model
model <- CreateModel(X,MCZ,100,20000,0.25,0.25)
#run 100 burnins, 1000 mcmc iterations and thin every 10 iterations
model$Run(1000,2000,100)

#retrieve parameters from the final iteration
result <- model$snapshot

}
