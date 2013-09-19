#include "Reaction.h" // Include the declaration of the Reaction..

reactor::Reaction::Reaction(RateConstant rate):
    rate(rate), reactants(), products()
  {
    // do nothing
  }

reactor::RateConstant reactor::Reaction::GetRate() const // const because it doesn't change the rate
{ 
	return rate; // give the rate result back
}

void reactor::Reaction::ContributeToRatesOfChange() const 
{
	double flux=GetFlux();
	// for each species in the reactants
	for (std::vector<Species *>::const_iterator each_reactant=GetReactants().begin(); each_reactant!=GetReactants().end(); each_reactant++)
	{
		// subtract the flux from the rate
		(*each_reactant)->ContributeToRateOfChange(-1.0*flux);
	}

	// for each species in the products
	for (std::vector<Species *>::const_iterator each_product=GetProducts().begin(); each_product!=GetProducts().end(); each_product++)
	{
		// add the flux to the rate
		(*each_product)->ContributeToRateOfChange(flux);
	}

}

double  reactor::Reaction::GetFlux() const {
	// the product of the concentrations of the reactants, times the rate constant
	double flux=rate;
	for (std::vector<Species *>::const_iterator each_reactant=GetReactants().begin(); each_reactant!=GetReactants().end(); each_reactant++)
	{
		flux*=(*each_reactant)->GetConcentration();
	}
	return flux;
}