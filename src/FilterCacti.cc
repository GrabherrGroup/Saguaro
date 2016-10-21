#include <string>
#include "ryggrad/src/base/CommandLineParser.h"
#include "ryggrad/src/base/FileParser.h"
#include "Cactus.h"

//#define FORCE_DEBUG


int Len(const string & l) 
{
  char tmp[256];
  strcpy(tmp, &(l.c_str()[2]));
  tmp[strlen(tmp)-1] = 0;
  return atol(tmp);
}

int main( int argc, char** argv )
{

  commandArg<string> fileCmmd("-i","LocalTree file");
  commandArg<string> cCmmd("-c","cacti file");
  commandArg<int> minCmmd("-m","minimum length covered", 2);
  commandLineParser P(argc,argv);
  P.SetDescription("Eliminates cacti that are not used.");
  P.registerArg(fileCmmd);
  P.registerArg(cCmmd);
  P.registerArg(minCmmd);
  
  
  P.parse();
  
  string fileName = P.GetStringValueFor(fileCmmd);
  string cName = P.GetStringValueFor(cCmmd);
  int min = P.GetIntValueFor(minCmmd);

  
  int i, j;
  svec<Cactus> cacti;
  LoadCacti(cacti, cName);

  svec<int> nukes;
  nukes.resize(cacti.isize(), 0);

  //comment. ???
  FlatFileParser parser;
  
  parser.Open(fileName);
  bool b = true;
  svec<string> used;
  while (parser.ParseLine()) {
    if (parser.GetItemCount() == 0)
      continue;
    if (parser.AsString(0) == "Reading")
      b = false;
    if (parser.AsString(0) == "REPORTING")
      b = true;

    if (!b)
      continue;

    if (parser.GetItemCount() > 6 && parser.AsString(5) == "length:") {
      const string len = parser.AsString(9);
      int l = Len(len);
      if (l >= min)       
	used.push_back(parser.AsString(0));     
      for (i=0; i<cacti.isize(); i++) {
	if (cacti[i].Name() == parser.AsString(0))
	  nukes[i] += parser.AsInt(4) - parser.AsInt(2);

       }
     }    

   }
   //cout << "Added" << endl;
   UniqueSort(used);

   FILE* pStats = fopen("cactusstats.out", "w");

   for (i=0; i<cacti.isize(); i++) {
     const string & name = cacti[i].Name();
     if (nukes[i] > 10) {
       fprintf(pStats, "%s %d\n", name.c_str(), nukes[i]);
     }
     for (j=0; j<used.isize(); j++) {
       if (used[j] == name) {
	 cacti[i].Print();
	 break;
       }
     }
   }
   fclose(pStats);

  return 0;
}
