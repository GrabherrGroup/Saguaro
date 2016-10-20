#include <string>

#include "../ryggrad/src/base/CommandLineParser.h"
#include "../ryggrad/src/base/FileParser.h"
#include "HMMDistance.h"
#include "DNAVector.h"








int main(int argc,char** argv)
{

  
  commandArg<string> aStringCmmd("-i","input file (plain text)");
  commandArg<string> bStringCmmd("-o","binary output file");
  commandArg<int> naCmmd("-na","max NA calls", 2);
  commandLineParser P(argc,argv);
  P.SetDescription("Converts a methylation or allele frequency data file into a Saguaro-digestable file of features");
  P.registerArg(aStringCmmd);
  P.registerArg(bStringCmmd);
  P.registerArg(naCmmd);
  
  P.parse();

  string in = P.GetStringValueFor(aStringCmmd);
  string out = P.GetStringValueFor(bStringCmmd);
  int maxNA = P.GetIntValueFor(naCmmd);

  

  HMMFeatureVector f;
  
   
  int i, j, l;
 
  cout << "Adding genomes..." << endl;
  
  FlatFileParser parser;
  parser.Open(in);
  parser.ParseLine();
  
  int n = 0;
  for (i=2; i<parser.GetItemCount(); i++) {
    f.SetName(i-2, parser.AsString(i));
    cout << "Adding " << parser.AsString(i) << endl; 
    n++;
  }

  // HMMFeature feature;
  //feature.resize(n * n);
  int k = 0;
  svec<double> data;
  data.resize(n);

  while (parser.ParseLine()) {
    if (parser.GetItemCount() == 0)
      continue;
    //feature.SetName(parser.AsString(0));
    //feature.SetPosition(parser.AsInt(1));
    if (k >= f.isize())
      f.resize(k + 5000000);
    //SetCompressedFloat(k, data, n, 
    int na = 0;
    for (i=0; i<n; i++) {
      if (parser.AsString(i+2) == "NA" ||
	  parser.AsString(i+2) == "na" ||
	  parser.AsString(i+2) == "N/A" ||
	  parser.AsString(i+2) == "n/a") {
	data[i] = -1.;
	na++;
      } else {
	data[i] = parser.AsFloat(i+2);
      }
      
    }
    if (na <= maxNA) {
      f.SetCompressedFloat(k, data, n, parser.AsString(0), parser.AsInt(1));    
      k++;
    }
  }
      
  
  
  f.resize(k);


  cout << "Writing data" << endl;
  f.Write(out);
  cout << "done." << endl;

 

  return 0;

}
  
