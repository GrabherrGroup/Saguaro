#include <string>
#include "ryggrad/src/base/CommandLineParser.h"
#include "ryggrad/src/base/FileParser.h"
#include "Cactus.h"





int main( int argc, char** argv )
{

  commandArg<string> cCmmd("-c","cacti file");
  commandArg<string> outCmmd("-o", "output name", "mclData");
  commandLineParser P(argc,argv);
  P.SetDescription("Convert Cacti format to MCL abc format.");
  P.registerArg(cCmmd);
  P.registerArg(outCmmd);
  
  
  P.parse();
  
  string cName   = P.GetStringValueFor(cCmmd);
  string outName = P.GetStringValueFor(outCmmd);
  if(outName=="") { outName = "mclData"; }
  
  svec<Cactus> cacti;
  LoadCacti(cacti, cName);
  for(int i=0; i<cacti.isize(); i++) {
    char outFile[256];
    sprintf(outFile, "%s_%d.abc", outName.c_str(), i);
    FILE* fOut = fopen(outFile, "w");
    cacti[i].WriteMCL(fOut);
    fclose(fOut);
  }

  return 0;
}
