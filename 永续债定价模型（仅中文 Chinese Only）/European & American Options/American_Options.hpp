//
//  American_Options.hpp
//  Level 9 - Group B
//
//  Created by 胡志伟 on 2019/8/15.
//  Copyright © 2019 Zhiwei Hu(Raphael Hu). All rights reserved.
//

#ifndef American_Options_hpp
#define American_Options_hpp

#include <iostream>
#include "boost/tuple/tuple.hpp"  //Tuple Class
#include "boost/tuple/tuple_io.hpp"  //T/O for Tuple
#include <string>
using namespace std;

typedef tuple<double,double,double,double,double,std::string> amr_option;
//use a tuple to store the S(asset price); K(strike price); r(risk-free interest rate); sig(volatility); b(cost of carry) and option type(put or call)

namespace Zhiwei_Hu
{
    namespace Containers
    {
        class American_Options
        {
        private:
            amr_option american_option;
        public:
            double S = get<0>(american_option); //asset price
            double K = get<1>(american_option); //strike price
            double r = get<2>(american_option); //risk-free interest rate
            double sig = get<3>(american_option); //volatility
            double b = get<4>(american_option); //cost of carry
            std::string type = get<5>(american_option); //option type (call/put)
            
            //default constructor
            American_Options();
            
            //parameter constructor
            American_Options(const amr_option& source);
            
            //copy constructor
            American_Options(const American_Options& copy);
            
            //destructor
            ~American_Options();
            
            //overloaded assignment operator
            American_Options operator=(const American_Options& copy);
            
            //price calculator
            double Price();

            
        };
    }
}


#endif /* American_Options_hpp */
