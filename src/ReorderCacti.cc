#ifndef FORCE_DEBUG
#define NDEBUG
#endif


#include <string>
#include "ryggrad/src/base/CommandLineParser.h"
#include "ryggrad/src/base/FileParser.h"
#include "Cactus.h"
#include "MCLClustCactus.h"

int main( int argc, char** argv )
{

  commandArg<string> cactiCmmd("-c","cacti file");
  commandArg<string> orderCmmd("-i","order file");
  commandArg<string> outputCmmd("-o","output file");
  commandLineParser P(argc,argv);
  P.SetDescription("Reorders Cacti with the given order");
  P.registerArg(cactiCmmd);
  P.registerArg(orderCmmd);
  P.registerArg(outputCmmd);
  
  
  P.parse();
  
  string cactiFileName  = P.GetStringValueFor(cactiCmmd);
  string orderFileName  = P.GetStringValueFor(orderCmmd);
  string outputFileName = P.GetStringValueFor(outputCmmd);

  svec<Cactus> cacti;
  svec<Cactus> cacti_reordered();

  LoadCacti(cacti, cactiFileName);

  MCLClustCactus mclClust;

  svec<string> orderedItems;
  FlatFileParser ffParser;
  ffParser.Open(orderFileName);
  mclClust.ReadClust(ffParser, orderedItems);

  Cactus cactus_reordered;
  mclClust.Reorder(cacti[0], orderedItems, cactus_reordered);

  //SaveCacti(cacti_reordered, outputFileName);
  FILE * outFile = fopen(outputFileName.c_str(), "w");
  cactus_reordered.Write(outFile);

  return 0;
}
