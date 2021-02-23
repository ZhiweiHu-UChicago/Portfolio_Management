//
//  Varying American Options.cpp
//  Level 9 - Group B
//
//  Created by 胡志伟 on 2019/8/17.
//  Copyright © 2019 Zhiwei Hu(Raphael Hu). All rights reserved.
//

#include "Varying American Options.hpp"
#include "Option_Exceptions.hpp"
#include <iostream>
using namespace std;

namespace Zhiwei_Hu
{
    namespace Containers
    {
        //constructors, destructor and the assignment operator //
        
        Varying_American_Options::Varying_American_Options(){};
        
        Varying_American_Options::Varying_American_Options(const amr_option& option_source):varying_american_option(option_source){};
        
        Varying_American_Options::Varying_American_Options(const Varying_American_Options& copy):varying_american_option(copy.varying_american_option){};
        
        Varying_American_Options Varying_American_Options::operator=(const Varying_American_Options &source)
        {
            varying_american_option.operator=(source.varying_american_option);
            return *this;
        };
        
        Varying_American_Options::~Varying_American_Options(){};
        
        
        // The varying_S function //
        vector<double> Varying_American_Options::Varying_S(vector<double> array)
        {

            vector<double> Price_result;
            //vector<double> Delta_result;
            for (int i=0; i<array.size(); ++i)
            {
                varying_american_option.S = array[i];
                Price_result.push_back(this->varying_american_option.Price());
            };

            return Price_result;
        };
        
        // The matrix function
        //Assume the function receives a 3*n matrix with varying S, sig and r
        vector<double> Varying_American_Options::varying_parameters(vector<vector<double>> matrix)
        {
            vector<double> result_price;
            
            if (matrix[0].size() != matrix[1].size() || matrix[0].size() != matrix[1].size() || matrix[1].size() != matrix[2].size())
            {
                throw vector_size_unequal();
            }
            else
            {
                for (int i=0; i<matrix[0].size(); ++i)
                {
                    this->varying_american_option.S = matrix[0][i];
                    this->varying_american_option.sig = matrix[1][i];
                    this->varying_american_option.r = matrix[2][i];
                    result_price.push_back(varying_american_option.Price());
                }
            }
            return result_price;

        }
    }
}
