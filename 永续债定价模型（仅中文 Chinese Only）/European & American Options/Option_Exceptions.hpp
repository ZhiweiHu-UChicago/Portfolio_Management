//
//  Option_Exceptions.hpp
//  Level 9 - Group A
//
//  Created by 胡志伟 on 2019/8/29.
//  Copyright © 2019 Zhiwei Hu(Raphael Hu). All rights reserved.
//

#ifndef Option_Exceptions_hpp
#define Option_Exceptions_hpp

#include <iostream>
using namespace std;

namespace Zhiwei_Hu
{
    namespace Containers
    {
        
        class Option_Exception
        {
        public:
            
            virtual std::string GetMessage() = 0;
        };
        
        
        //for the matrix function, in case the vectors in the same matrix have different sizes
        class vector_size_unequal:public Option_Exception
        {
        public:
            std::string GetMessage()
            {
                std::string message = "The vectors in the matrix have different sizes!";
                return message;
            }
        };

        
    }
}




#endif /* Option_Exceptions_hpp */
