//
//  Varying American Options.hpp
//  Level 9 - Group B
//
//  Created by 胡志伟 on 2019/8/17.
//  Copyright © 2019 Zhiwei Hu(Raphael Hu). All rights reserved.
//

#ifndef Varying_American_Options_hpp
#define Varying_American_Options_hpp
#include "American_Options.hpp"
#include <iostream>
#include <vector>
using namespace std;

namespace Zhiwei_Hu
{
    namespace Containers
    {
        typedef tuple<double,double,double,double,double,std::string> amr_option;
        
        class Varying_American_Options
        {
        private:
            American_Options varying_american_option;
            
        public:
            
            //default constructor
            Varying_American_Options();
            
            //parameter constructor
            Varying_American_Options(const amr_option& option_source);
            
            //copy constructor
            Varying_American_Options(const Varying_American_Options& copy);
            
            //Assignment operator
            Varying_American_Options operator=(const Varying_American_Options& source);
            
            //destructor
            ~Varying_American_Options();
            
            /* Here we defined a varying_S function to output a vector of doubles.
             showing if S is a sequence of values, how other measurements are going to be affected.
             */
            vector<double> Varying_S (vector<double> array);
            
            
            //and also the matrix function
            vector<double> varying_parameters (vector<vector<double>> matrix);
        };
        
    }
}


#endif /* Varying_American_Options_hpp */
