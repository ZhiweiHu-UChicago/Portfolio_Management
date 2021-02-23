//
//  Varying Options.hpp
//  Level 9 - Group A
//
//  Created by 胡志伟 on 2019/8/15.
//  Copyright © 2019 Zhiwei Hu(Raphael Hu). All rights reserved.
//

#ifndef Varying_Options_hpp
#define Varying_Options_hpp
#include "European(Plain)_Options.hpp"
#include <vector>
#include <iostream>

namespace Zhiwei_Hu
{
    namespace Containers
    {
        
        class Varying_options
        {
        private:
            European_Option varying_option;
            
        public:
            
            //default constructor
            Varying_options();
            
            //parameter constructor
            Varying_options(const European_Option& option_source);
            
            //copy constructor
            Varying_options(const Varying_options& copy);
            
            //Assignment operator
            Varying_options operator=(const Varying_options& source);
            
            //destructor
            ~Varying_options();
            
            /* Here we defined a varying_S function to output a vector of vectors.
             showing if S is a sequence of values, how other measurements are going to be affected.
             */
            
            vector<vector<double>> Varying_S (vector<double> varying_S);
            
            /* If we need to observe more varying parameters' effects on the price, delta, gamma etc, we can follow this path to create more functions like
             
             vector<vector<double>> Varying_K (double end_K, double step);
             
             vector<vector<double>> Varying_sig (double end_sig, double step_;
             
             etc....
             */
            
            vector<vector<double>> Varying_matrix(vector<vector<double>> matrix);
            
        };
        
        
        
        
        
    }
}

#endif /* Varying_Options_hpp */
