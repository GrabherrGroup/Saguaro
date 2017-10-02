#ifndef FORCE_DEBUG
#define NDEBUG
#endif

#include "ryggrad/src/base/CommandLineParser.h"
#include "Cactus.h"
#include "MCLClustCactus.h"


bool MCLClustCactus::ReadClust(FlatFileParser & f, svec<string>& items)
{
  while(f.ParseLine()) {
    for (int i=0; i<f.GetItemCount(); i++) {
      items.push_back(f.AsString(i));    
    }
  }
  return true;
}

void MCLClustCactus::Reorder(const Cactus & cactus, const svec<string> & order, Cactus & cactus_reordered)
{
  if(cactus.Size()!=order.isize()) { 
    cout<<"Warning: Cactus could not be reordered - wrong size of order vector - Cactus size: "
        << cactus.Size()<<" Order list size: " << order.isize() << endl;
    return;
  }
  
  // Cactus labels - mapping id to location
  map<string, int> orderLocMap; 
  for(int i=0; i<cactus.Size(); i++) {
    orderLocMap[cactus.GetLabel(i)] = i; 
  }

  // Start completing cactus_reordered with reordered data (according to the order vector)
  cactus_reordered.SetSize(order.isize());
  for(int reordered_i=0; reordered_i<order.isize(); reordered_i++) {
    cactus_reordered.SetLabel(reordered_i, order[reordered_i]);
    int cactus_i = orderLocMap[order[reordered_i]];   //Corresponding cactus index
    for(int reordered_j=0; reordered_j<order.isize(); reordered_j++) {
      int cactus_j = orderLocMap[order[reordered_j]]; //Corresponding cactus index 
      cactus_reordered.Set(reordered_i, reordered_j, cactus.Get(cactus_i, cactus_j));
    }
  }

  return;
}

