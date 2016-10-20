#include <string>
#include "../ryggrad/src/base/CommandLineParser.h"
#include "../ryggrad/src/base/FileParser.h"



int main( int argc, char** argv )
{

  commandArg<string> fileCmmd("-i","cactus input file");
  commandArg<bool> oCmmd("-outgroup","add a dummy outgroup", false);
  commandArg<double> dCmmd("-dist","distance for the outgroup", 1.0);
  commandLineParser P(argc,argv);
  P.SetDescription("Makes phyloP compatible distance matrices.");
  P.registerArg(fileCmmd);
  P.registerArg(oCmmd);
  P.registerArg(dCmmd);
  
  P.parse();
  
  string fileName = P.GetStringValueFor(fileCmmd);
  bool bOut = P.GetBoolValueFor(oCmmd);
  double dist = P.GetDoubleValueFor(dCmmd);
  

  //comment. ???
  FlatFileParser parser;
  
  parser.Open(fileName);
  
  FILE * p = NULL;
  int i;
  int k = 0;
  while (parser.ParseLine()) {
    if (parser.GetItemCount() == 0)
      continue;
    if (parser.GetItemCount() == 1) {
      if (p != NULL)
	fclose(p);
      p = fopen(parser.AsString(0).c_str(), "w");
      parser.ParseLine();
      int plus = 0;
      if (bOut)
	plus = 1;
      fprintf(p, "%d\n", (parser.GetItemCount()+plus));
      k = 0;
      if (bOut) {
	fprintf(p, "outgroup  0.000");
	for (i=0; i<parser.GetItemCount(); i++) {
	  fprintf(p, " %1.3f", dist);
	}
	fprintf(p, "\n");
      }
      continue;
    }

    char tmp[256];
    strcpy(tmp, parser.AsString(0).c_str());
    tmp[9] = 0;
    fprintf(p, "%s", tmp);
    for (i= strlen(tmp); i<10; i++)
      fprintf(p, " ");
    if (bOut)
      fprintf(p, "%1.3f ", dist);
    for (i=1; i<parser.GetItemCount(); i++) {
      if (i-1 == k)
	fprintf(p, "0.000 ");
      else
	fprintf(p, "%1.3f ", parser.AsFloat(i));
    }
    fprintf(p, "\n");
    k++;
  }
  fclose(p);
  return 0;
}
