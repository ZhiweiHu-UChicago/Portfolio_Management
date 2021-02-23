//
//  European(Plain)_Options.cpp
//  Level 9 - Group A
//
//  Created by 胡志伟 on 2019/8/10.
//  Copyright © 2019 Zhiwei Hu(Raphael Hu). All rights reserved.
//
//To include the boost library
#include "European(Plain)_Options.hpp"
#include <cmath>
#include <boost/math/distributions/normal.hpp>
#include <iostream>
using namespace std;
using namespace boost::math;

typedef tuple<double,double,double,double,double,double,std::string> option;

//Default constructor
European_Option::European_Option():european_option(option{0,0,0,0,0,0,"C"}){};

//Copy constructor
European_Option::European_Option(const European_Option& source):european_option(source.european_option){};

//Parameter constructor
European_Option::European_Option(const option& source):european_option(source){};

//Destructor
European_Option::~European_Option(){};

//Overloaded assignment operator
European_Option& European_Option::operator=(const European_Option &copy)
{
    european_option = copy.european_option;
    return *this;
}

//option getter
option European_Option::Get() const
{
    return european_option;
}

//calculators
//Gaussian Functions
double European_Option::d_1(option& example_option) const
{
    return (log(S/K) + (b+sig*sig*0.5)*T)/(sig*sqrt(T));
};

double European_Option::d_2(option& example_option) const
{
    return d_1(example_option) - (sig*sqrt(T));
};

double European_Option::N(double x) const
{//using boots library to calculate the cumulative normal distribution
    
    normal_distribution<> myNormal(0,1);//standard normal distribution
    return cdf(myNormal, x);
};

double European_Option::n(double x) const
{//using boots library to calculate the normal probability density function
    
    normal_distribution<> myNormal(0,1);//standard normal distribution
    return pdf(myNormal, x);
}

//Option price calculators
double European_Option::CallPrice()
{
    return S*exp((b-r)*T)*N(d_1(european_option))-K*exp(-r*T)*N(d_2(european_option));
};

double European_Option::PutPrice()
{
    return K*exp(-r*T)*N(-d_2(european_option))-S*exp((b-r)*T)*N(-d_1(european_option));
};

//The aggragated price calculator
double European_Option::Price() 
{
    if (get<6>(european_option) == "Call")
    {
        return European_Option::CallPrice();
    }
    else
        return European_Option::PutPrice();
};

//parity checker version 1, to calculate the corresponding put/call price
void European_Option::parity_checker(double price_given, std::string type)
{
    if (type == "Call" || type == "call")
    {
        double put_price = price_given + (K*exp(-r*T)) - S*exp((b-r)*T);
        cout<<"\nThe corresponding put price should be: "<<put_price<<endl;
    }
    else
    {
        double call_price = price_given - (K*exp(-r*T)) + S*exp((b-r)*T);
        cout<<"\nThe corresponding call price should be: "<<call_price<<endl;
    }
};

//version 2. This is to test if the given two prices meet the put-call parity
void European_Option::parity_checker(double price_1, double price_2)
{
    if (abs(price_1 - price_2 + (K*exp(-r*T))-S*exp((b-r)*T))<0.001 || abs(price_2 = price_1 + (K*exp(-r*T))-S*exp((b-r)*T))<0.1)
    {
        cout<<"The given prices meet the put-call parity!"<<endl;
    }
    else
    {
        cout<<"The put-call parity fails!"<<endl;
    }
};


double European_Option::call_delta()
{
    return exp((b-r)*T)*N(d_1(european_option));
};

double European_Option::put_delta()
{
    return -exp((b-r)*T)*N(-d_1(european_option));
};

double European_Option::Delta()
{
    if (type == "Call" || type == "call")
    {
        return this->call_delta();
    }
    else
    {
        return this->put_delta();
    }
};


double European_Option::call_gamma()
{
    return (n(d_1(european_option))*exp((b-r)*T))/(S*sig*sqrt(T));
};

double European_Option::put_gamma()
{
    return (n(-d_1(european_option))*(-exp((b-r)*T)))/S*sig*sqrt(T);
};

double European_Option::Gamma()
{
    if (type =="Call" || type == "call")
    {
        return this->call_gamma();
    }
    else
    {
        return this->put_gamma();
    }
};
