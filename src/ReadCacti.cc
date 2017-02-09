#include <string>
#include "ryggrad/src/base/CommandLineParser.h"
#include "ryggrad/src/base/FileParser.h"
#include "src/Cactus.h"


int main( int argc, char** argv )
{

  commandArg<string> fileCmmd("-i","input file");
  commandLineParser P(argc,argv);
  P.SetDescription("Example program.");
  P.registerArg(fileCmmd);
 
  P.parse();
  
  string fileName = P.GetStringValueFor(fileCmmd);

  svec<Cactus> cacti;
  
  LoadCacti(cacti, fileName);
  int i, j;

  const Cactus & c = cacti[2];

  for (i=0; i<c.Size(); i++)  {
    cout << c.GetLabel(i);
    for (j=0; j<c.Size(); j++)  {
      cout << " " << c.Get(i, j);
    }
    cout << endl;
  }

  return 0;
}

