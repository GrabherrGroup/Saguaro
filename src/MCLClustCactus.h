#ifndef MCLCLUSTCACTUS_H_
#define MCLCLUSTCACTUS_H_

#include <string>
#include <stdio.h>
#include "ryggrad/src/base/SVector.h"
#include "ryggrad/src/base/StringUtil.h"

class FlatFileParser;
class Cactus;

class MCLClustCactus
{
public:
  MCLClustCactus() {} 
  bool ReadClust(FlatFileParser & f, svec<string> & items);
  void Reorder(const Cactus & cactus, const svec<string> & order, Cactus & cactus_reordered);
};

#endif  //MCLCLUSTCACTUS_H

