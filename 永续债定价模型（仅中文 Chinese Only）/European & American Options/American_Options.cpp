//
//  American_Options.cpp
//  Level 9 - Group B
//
//  Created by 胡志伟 on 2019/8/15.
//  Copyright © 2019 Zhiwei Hu(Raphael Hu). All rights reserved.
//

#include "American_Options.hpp"
#include <iostream>
#include <cmath>
#include <boost/math/distributions/normal.hpp>
using namespace std;
typedef tuple<double,double,double,double,double,std::string> amr_option;

namespace Zhiwei_Hu
{
    namespace Containers
    {
        //constructors, destructor and the overloaded assignment operator
        American_Options::American_Options(){};
        
        American_Options::American_Options(const amr_option& source):american_option(source){};
        
        American_Options::American_Options(const American_Options& copy):american_option(copy.american_option){};
        
        American_Options American_Options::operator=(const American_Options &copy)
        {
            american_option = copy.american_option;
            return *this;
        };
        
        American_Options::~American_Options(){};
        
        
        //the price calculator
        double American_Options::Price()
        {
            if (std::get<5>(american_option) == "Call" || std::get<5>(american_option) == "call")
            {
                double y1 = 0.5-(b/(sig*sig))+sqrt(pow((b/(sig*sig)-0.5), 2)+(2*r)/pow(sig, 2));
                return (K/(y1-1))*pow((((y1-1)/y1)*S/K),y1);
            }
            else
            {
                double y2 = 0.5-(b/(sig*sig)) - sqrt(pow((b/(sig*sig)-0.5), 2)+(2*r)/pow(sig, 2));
                return (K/(1-y2))*pow((((y2-1)/y2)*S/K),y2);
            };
        };
        
        
        
        
    }
}
