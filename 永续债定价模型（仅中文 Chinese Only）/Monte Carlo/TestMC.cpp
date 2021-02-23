// HardCoded.cpp
//
// C++ code to price an option, essential algorithms.
//
// We take CEV model with a choice of the elaticity parameter
// and the Euler method. We give option price and number of times
// S hits the origin.
//
// (C) Datasim Education BC 2008-2011
//

#include "OptionData.hpp" 
#include "NormalGenerator.hpp"
#include "Range.hpp"
#include <cmath>
#include <iostream>
using namespace std;

namespace SDEDefinition
{ // Defines drift + diffusion + data

	OptionData* data;				// The data for the option MC

	double drift(double t, double X)
	{ // Drift term
	
		return (data->r)*X; // r - D
	}

	
	double diffusion(double t, double X)
	{ // Diffusion term
	
		double betaCEV = 1.0;
		return data->sig * pow(X, betaCEV);
		
	}

	double diffusionDerivative(double t, double X)
	{ // Diffusion term, needed for the Milstein method
	
		double betaCEV = 1.0;
		return 0.5 * (data->sig) * (betaCEV) * pow(X, 2.0 * betaCEV - 1.0);
	}
} // End of namespace

//define two global functions to calculate the standard deviation and the standard error
namespace Deviation_and_Error
{
    double SD(vector<double> prices, double r, double T)
    {
        vector<double>::const_iterator vector_iterator;
        double sum_of_price = 0;
        double sum_of_price_square = 0;
        for (vector_iterator=prices.begin(); vector_iterator != prices.end(); vector_iterator++)
        {
            double tmp = *vector_iterator;
            sum_of_price += tmp;
            sum_of_price_square += pow(tmp,2);
        }
        return (sqrt((sum_of_price_square-(1.0/prices.size()) * pow(sum_of_price,2))/ ((prices.size()-1)))*exp(-1*(r*T)));
    };
    
    double SE(double Standard_deviation, vector<double> prices)
    {
        return Standard_deviation / sqrt(prices.size());
    };
} //end of namespace

int main()
{
    //MARK:OPTION DATA MODIFIED HERE
	std::cout <<  "1 factor MC with explicit Euler\n";
	OptionData myOption;
    myOption.K = 8.46;
	myOption.T = 5;
	myOption.r = 0.0329;
	myOption.sig = 0.4439;
	myOption.type = +1;	// Put -1, Call +1
    double S_0 = 4.69;
	
	long N = 100;
	std::cout << "Number of subintervals in time: ";
	std::cin >> N;

	// Create the basic SDE (Context class)
    Range<double> range;
    range.low(0.0);
    range.high(myOption.T);
	double VOld = S_0;
    double VNew = 0.0;

	std::vector<double> x = range.mesh(N);

	// V2 mediator stuff
	long NSim = 0;
	std::cout << "Number of simulations: ";
	std::cin >> NSim;

	double k = myOption.T / double (N);
	double sqrk = sqrt(k);

	// Normal random number
	double dW;
	double price = 0.0;	// Option price

	// NormalGenerator is a base class
	NormalGenerator* myNormal = new BoostNormal();

	using namespace SDEDefinition;
	SDEDefinition::data = &myOption;

	std::vector<double> res;
	int coun = 0; // Number of times S hits origin

	// A.
    vector<double> prices_array; //for storing each price at T for each simulation
    
	for (long i = 1; i <= NSim; ++i)
	{ // Calculate a path at each iteration
			
		if ((i/10000) * 10000 == i)
		{// Give status after each 1000th iteration

				std::cout << i << std::endl;
		}

		VOld = S_0;
		for (unsigned long index = 1; index < x.size(); ++index)
		{

			// Create a random number
			dW = myNormal->getNormal();
				
			// The FDM (in this case explicit Euler)
			VNew = VOld  + (k * drift(x[index-1], VOld))
						+ (sqrk * diffusion(x[index-1], VOld) * dW);

			VOld = VNew;

			// Spurious values
			if (VNew <= 0.0) coun++;
		}
			
		double tmp = myOption.myPayOffFunction(VNew);
        prices_array.push_back(tmp);
		price += (tmp)/double(NSim);
	}
    
	//Testing the deviation and the error
    using namespace Deviation_and_Error;
    double standard_deviation = SD(prices_array, myOption.r, myOption.T);
    //cout<<"The standard deviation is: "<<standard_deviation<<endl;
    
    double standard_error = SE(standard_deviation, prices_array);
    //cout<<"The standard error is: "<<standard_error<<endl;
    
	// D. Finally, discounting the average price
	price *= exp(-myOption.r * myOption.T);

	// Cleanup; V2 use scoped pointer
	delete myNormal;

	std::cout << "Price, after discounting: " << price << ", " << std::endl;
	//std::cout << "Number of times origin is hit: " << coun << endl;

	return 0;
}
