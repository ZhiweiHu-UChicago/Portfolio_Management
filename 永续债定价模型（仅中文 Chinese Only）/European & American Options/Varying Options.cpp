//
//  Varying Options.cpp
//  Level 9 - Group A
//
//  Created by 胡志伟 on 2019/8/15.
//  Copyright © 2019 Zhiwei Hu(Raphael Hu). All rights reserved.
//

#include "Varying Options.hpp"
#include <iostream>
#include "Option_Exceptions.hpp"
using namespace std;

namespace Zhiwei_Hu
{
    namespace Containers
    {
        //constructors, destructor and the assignment operator //
        
        Varying_options::Varying_options(){};
        
        Varying_options::Varying_options(const European_Option& option_source):varying_option(option_source){};
        
        Varying_options::Varying_options(const Varying_options& copy):varying_option(copy.varying_option){};
        
        Varying_options Varying_options::operator=(const Varying_options &source)
        {
            varying_option.operator=(source.varying_option);
            return *this;
        };
        
        Varying_options::~Varying_options(){};
        
        // The varying_S function //
        
        vector<vector<double>> Varying_options::Varying_S(vector<double> varying_S)
        {
            vector<vector<double>>  aggr_result;
            vector<double> Price_result;
            vector<double> Delta_result;
            
            for (int i=0; i<varying_S.size(); ++i)
            {
                this->varying_option.S = varying_S[i];
                Price_result.push_back(this->varying_option.Price());
                Delta_result.push_back(this->varying_option.Delta());
                
                //  If we need to observe more measurements like gamma, vaga etc, that how they're going to behave once S(asset price) changes, we can call more member functions here //
            };
            
                aggr_result.push_back(Price_result);
                aggr_result.push_back(Delta_result);
            
            return aggr_result;
        };
        
        
        //The matrix function, for exercise d)
        vector<vector<double>> Varying_options::Varying_matrix(vector<vector<double>> matrix)
        {
            vector<double> result_price;
            vector<double> result_delta;
            
            if (matrix[0].size() != matrix[1].size() || matrix[0].size() != matrix[1].size() || matrix[1].size() != matrix[2].size())
            {
                throw vector_size_unequal();
            }
            
            else
            {
                for (int i=0; i<matrix[0].size(); ++i)
                {
                    this->varying_option.S = matrix[0][i];
                    this->varying_option.T = matrix[1][i];
                    this->varying_option.sig = matrix[2][i];
                    result_price.push_back(varying_option.Price());
                    result_delta.push_back(varying_option.Delta());
                }
            };
            
            //to build the output matrix(vector of vectors)
            vector<vector<double>> output = {result_price,result_delta};
            
            return output;
        };
        
        
        
        
    }
}
