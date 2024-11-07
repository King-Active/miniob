/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#pragma once

#include "common/type/data_type.h"

#ifndef VECTOR_TYPE_H_
#define VECTOR_TYPE_H_

/**
 * @brief 向量数据类型
 * @ingroup DataType
 */
class VectorType : public DataType
{
public:
  VectorType() : DataType(AttrType::VECTORS) {}
  ~VectorType(){};

  RC to_string(const Value &val, string &result) const override;

  /* Acking666 */
  /* 比较 */
  int compare(const Value &left, const Value &right) const override;
  /* 逐元素加 */
  RC add(const Value &left, const Value &right, Value &result) const override;
  /* 比较 */
  RC max(const Value &left, const Value &right, Value &result) const override;
  /* 比较 */
  RC min(const Value &left, const Value &right, Value &result) const override;
  /* 统计 */
  RC count(const int num, Value &result) const override;
  /* 逐元素减 */
  RC subtract(const Value &left, const Value &right, Value &result) const override;
  /* 逐元素乘 */
  RC multiply(const Value &left, const Value &right, Value &result) const override;
  /* 所有数取相反数 */
  RC negative(const Value &val, Value &result) const override;

  /* l2距离表达式 */
  RC l2Distance(const Value &left, const Value &right, Value &result) const override;

  /* 余弦距离表达式 */
  RC cosDistance(const Value &left, const Value &right, Value &result) const override;

  /* 向量内积 */
  RC innerProduct(const Value &left, const Value &right, Value &result) const override;
  
  /* 向量不能数据类型转换 */
  RC cast_to(const Value &val, AttrType type, Value &result) const override;        

  /* 代价无穷大 */
  int cast_cost(AttrType type) override;
};

#endif