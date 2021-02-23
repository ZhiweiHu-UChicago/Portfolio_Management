//
//  European(Plain)_Options.hpp
//  Level 9 - Group A
//
//  Created by 胡志伟 on 2019/8/10.
//  Copyright © 2019 Zhiwei Hu(Raphael Hu). All rights reserved.
//

#ifndef European_Plain__Options_hpp
#define European_Plain__Options_hpp
//To include the boost library
#include "boost/tuple/tuple.hpp"  //Tuple Class
#include "boost/tuple/tuple_io.hpp"  //T/O for Tuple
#include <string>
#include <iostream>
using namespace std;

class European_Option
{
    typedef tuple<double,double,double,double,double,double,std::string> option;
    //use a tuple to store the S(asset price); K(strike price); T(maturity date); r(risk-free interest rate); sig(volatility); b(cost of carry) and option type(put or call)
    
private:
    option european_option;
    
public:
    //For simplicity, retrive the data here to be used in functions defined below.
    double S = get<0>(european_option); //asset price
    double K = get<1>(european_option); //strike price
    double T = get<2>(european_option); //maturity date
    double r = get<3>(european_option); //risk-free rate
    double sig = get<4>(european_option); //constant volitality
    double b = get<5>(european_option); //cost of carry
    std::string type = get<6>(european_option); // option type
    
    //Default constructor
    European_Option();
    
    //Copy constructor
    European_Option(const European_Option& source);
    
    //Parameter constructor
    European_Option(const option& source);
    
    //Deconstructor
    ~European_Option();
    
    //tuple getter
    option Get() const;
    
    //overloaded assignment operator
    European_Option& operator = (const European_Option& copy);
    
    //Calculators
    //To calculate the option price using the Black-Scholes formula
    double Price();
    
    double CallPrice();
    double PutPrice();
    //I put these two sub-calculator here, and these two functions will be intergrated into the generic Price() function.
    
    //Gaussian Functions
    double d_1(option& example_option) const;
    double d_2(option& example_option) const;
    double N(double x)const;
    double n(double x)const;
    
    //Put-Call Parity Checker
    void parity_checker(double price_given, std::string type);
    void parity_checker(double price_1, double price_2);
    
    //delta function
    double Delta();
    double call_delta();
    double put_delta();
    
    //gamma function
    double Gamma();
    double call_gamma();
    double put_gamma();
    
};


#endif /* European_Plain__Options_hpp */
