#pragma once
#include "common/log/log.h"

struct myVector {
private:

    /* 向量链表 */
    float* my_vector_value_ = nullptr;

    /* 向量元素的个数 */    
    int length_ = -1;       

public:

    myVector(const char* str) {
        if(str == nullptr){
            this->my_vector_value_ = nullptr;
            this->length_ = -1;
            return;
        }

        // 期望格式 num,num,num
        std::vector<float> floats;  
        std::istringstream stream(str);  
        std::string token;  
    
        // 使用逗号作为分隔符来分割字符串  
        // TODO: 检测字符串合法性
        while (std::getline(stream, token, ',')) {  
            char* endptr;  
            float value = std::strtod(token.c_str(), &endptr);  
            if (*endptr == '\0') { 
                floats.push_back(value);  
            } else {  
                LOG_WARN("can not transfer %s into float", token);
                return;
            }  
        }  
        
        this->my_vector_value_ = new float[floats.size()];
        for(size_t i = 0; i < floats.size(); i++){
            this->my_vector_value_[i] = floats.at(i);
        }
        this->length_ = floats.size();
     }

    myVector(const float* floats, int length){
        my_vector_value_ = new float[length];
        for (int i = 0; i < length; i++) {  
            my_vector_value_[i] = floats[i];  
        }  
        this->length_ = length;
    }

    /* Acking666 */
    float* getVector() const{ 
        float* floats = new float[length_];
        for(int i = 0; i < length_; i++){
            floats[i] = my_vector_value_[i];
        }
        return floats;
    } 

    void reset(){
        delete[] my_vector_value_;  ///< Attention: delete[] but not delete !!!
        my_vector_value_ = nullptr;
        length_ = -1;
    }

    /* 返回向量的字节长度 */
    int vecLength() const {
        return length_ * 4;
    }
    
    /* 返回向量元素的个数 */
    int vecNum() const {
        return length_ ;
    }
    
};
 