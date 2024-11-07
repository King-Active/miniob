#include "common/log/log.h"
#include "common/type/vector_type.h"
#include "common/myVector.h"
#include "common/type/attr_type.h"
#include "common/value.h"
#include "cmath"

/* Acking666 */
RC VectorType::to_string(const Value &val, string &result) const
{
  /* 检查类型是否契合 */
  if(val.attr_type() != AttrType::VECTORS){
    LOG_WARN("Invalid dataType, expected VECTORS, but get %s", val.attr_type());
    return RC::INTERNAL;
  }
  
  myVector myVec = val.get_myVector();
  result = "";
  float* it = myVec.getVector();
  auto tmp = it;
  /* 特殊处理第一个数字 */
  if(myVec.vecNum() >= 1){
    result.append(std::to_string(*it++));
  }
  int num = myVec.vecNum() - 1;
  while(num > 0){
    result.append("," + std::to_string(*it++));
    num--;
  }

  delete[] tmp;
  return RC::SUCCESS;
}

int VectorType::compare(const Value &left, const Value &right) const{
  // -1  ->  left < right
  // 0   ->  left = right
  // 1   ->  left > right
  auto leftVec  = left.get_myVector().getVector();  
  auto rightVec = right.get_myVector().getVector();  
  const int   vecNum   = left.get_myVector().vecNum();

  for(int i = 0; i < vecNum; i++){
    if(leftVec[i] > rightVec[i]){
      return 1;
    }
    if(leftVec[i] < rightVec[i]){
      return -1;
    }
  }

  delete[] leftVec;
  delete[] rightVec;
  return 0;
}

/* 比较 */
RC  VectorType::max(const Value &left, const Value &right, Value &result) const{
  // 相等情况取left
    if(this->compare(left, right) == -1){
      result = right;
    }
    else {
      result = left;
    }
    return RC::SUCCESS;
}

/* 比较 */
RC  VectorType::min(const Value &left, const Value &right, Value &result) const{
    // 相等情况取left
    if(this->compare(left, right) == 1){
      result = right;
    }
    else {
      result = left;
    }
    return RC::SUCCESS;
}

/* 统计 */
RC  VectorType::count(const int num, Value &result) const{
  result.set_int(num);
  return RC::SUCCESS;
}

/* 逐元素加 */
RC  VectorType::add(const Value &left, const Value &right, Value &result) const {
    if(left.get_myVector().vecNum() != right.get_myVector().vecNum()){
      LOG_WARN("Cannot use use operator add to 2 vectors with different size");
    }

    auto leftVec  = left.get_myVector().getVector();  
    auto rightVec = right.get_myVector().getVector();   
    const int   vecNum   = left.get_myVector().vecNum();

    float* res_val = new float[vecNum];
    for(int i = 0; i < vecNum; i++){
      res_val[i] = leftVec[i] + rightVec[i];
    }
    result.set_myVector(myVector(res_val, vecNum));
    delete[] leftVec;
    delete[] rightVec;
    return RC::SUCCESS;
}

/* 逐元素减 */
RC  VectorType::subtract(const Value &left, const Value &right, Value &result) const{
      if(left.get_myVector().vecNum() != right.get_myVector().vecNum()){
      LOG_WARN("Cannot use use operator sub to 2 vectors with different size");
    }

    auto leftVec  = left.get_myVector().getVector();  
    auto rightVec = right.get_myVector().getVector();  
    const int   vecNum   = left.get_myVector().vecNum();

    float* res_val = new float[vecNum];
    for(int i = 0; i < vecNum; i++){
      res_val[i] = leftVec[i] - rightVec[i];
    }
    result.set_myVector(myVector(res_val, vecNum));

    delete[] leftVec;
    delete[] rightVec;
    return RC::SUCCESS;
}

/* 逐元素乘 */
RC  VectorType::multiply(const Value &left, const Value &right, Value &result) const{
    if(left.get_myVector().vecNum() != right.get_myVector().vecNum()){
      LOG_WARN("Cannot use use operator multiply to 2 vectors with different size");
    }
    
    auto leftVec  = left.get_myVector().getVector();  
    auto rightVec = right.get_myVector().getVector();   
    const int   vecNum   = left.get_myVector().vecNum();

    float* res_val = new float[vecNum];
    for(int i = 0; i < vecNum; i++){
      res_val[i] = leftVec[i] * rightVec[i];
    }
    result.set_myVector(myVector(res_val, vecNum));
    
    delete[] leftVec;
    delete[] rightVec; 
    return RC::SUCCESS;
}

/* 所有数取相反数 */
RC  VectorType::negative(const Value &val, Value &result) const{
    auto valVec = val.get_myVector().getVector();
    const int   vecNum = val.get_myVector().vecNum();

    float* res_val = new float[vecNum];
    for(int i = 0; i < vecNum; i++){
      res_val[i] = -valVec[i];
    }
    result.set_myVector(myVector(res_val, vecNum));
    
    delete[] valVec;
    return RC::SUCCESS;
}

/* l2距离表达式 */
RC VectorType::l2Distance(const Value &left, const Value &right, Value &result) const {
    auto leftVec  = left.get_myVector().getVector();  
    auto rightVec = right.get_myVector().getVector();  
    const int   vecNum   = left.get_myVector().vecNum();

    float sum = 0.0f;  
    for(int i = 0; i < vecNum; i++){ 
        sum += pow((leftVec[i] - rightVec[i]), 2);  
    }  
    result.set_float(sqrt(sum));  

    delete[] leftVec;
    delete[] rightVec;
    return RC::SUCCESS;  
}

/* 余弦距离表达式 */
RC VectorType::cosDistance(const Value &left, const Value &right, Value &result) const {
    auto leftVec  = left.get_myVector().getVector();  
    auto rightVec = right.get_myVector().getVector();  
    const int   vecNum   = left.get_myVector().vecNum();

    float t1 = 0.0f, t2 = 0.0f, t3 = 0.0f;
    for(int i = 0; i < vecNum; i++){ 
        t1 += leftVec[i] * rightVec[i];
        t2 += pow(leftVec[i], 2);
        t3 += pow(rightVec[i], 2);
    }  
    result.set_float(1 - t1 / (sqrt(t2)*sqrt(t3)));

    delete[] leftVec;
    delete[] rightVec;
    return RC::SUCCESS;
}

/* 向量内积 */
RC VectorType::innerProduct(const Value &left, const Value &right, Value &result) const{
    auto leftVec  = left.get_myVector().getVector();  
    auto rightVec = right.get_myVector().getVector();  
    const int   vecNum   = left.get_myVector().vecNum();
    
    float sum = 0.0f;
    for(int i = 0; i < vecNum; i++){ 
      sum += leftVec[i] * rightVec[i];
    }  
    result.set_float(sum);

    delete[] leftVec;
    delete[] rightVec;
    return RC::SUCCESS;
}

RC VectorType::cast_to(const Value &val, AttrType type, Value &result) const {
  return RC::INTERNAL;
}

int VectorType::cast_cost(AttrType type){
  return -1;
}
