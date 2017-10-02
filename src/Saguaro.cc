#include <string>
#include "ryggrad/src/base/CommandLineParser.h"
#include "SaguaroCore.h"


int main( int argc, char** argv )
{

  //cout << argv[0] << endl;

  char tmpPath[512];
  strcpy(tmpPath, argv[0]);
  tmpPath[strlen(tmpPath)-7] = 0;
  cout << "Path to executable: " << tmpPath << endl;
  

  //commandArg<string> fileCmmd("-i","feature input file");
  commandArg<string> bStringCmmd("-f","Feature vector", "");
  commandArg<string> lStringCmmd("-l","Feature vector list file", "");
  commandArg<string> oStringCmmd("-o","output directory");
  commandArg<int> iterCmmd("-cycle","iterations per cycle", 2);
  commandArg<int> allCmmd("-iter","iterations with split", 40);
  commandArg<int> stateCmmd("-state","Number of states to use", 3);
  commandArg<double> transCmmd("-t","transition penalty", 150.);
  commandArg<int> resumeCmmd("-resume","resume w/ iteration #", 0);
  commandArg<int> neuronCmmd("-neurons","number of neurons in the SOM", 800);
  commandArg<bool> eucCmmd("-e","use euclidean distance", false);
  commandLineParser P(argc,argv);
  P.SetDescription("Smoothly, automatically and generically uncover the ancestry of related organisms.");
  //P.registerArg(fileCmmd);
  P.registerArg(bStringCmmd);
  P.registerArg(lStringCmmd);
  P.registerArg(oStringCmmd);
  P.registerArg(iterCmmd);
  P.registerArg(allCmmd);
  P.registerArg(stateCmmd);
  P.registerArg(transCmmd);
  P.registerArg(resumeCmmd);
  P.registerArg(neuronCmmd);
  P.registerArg(eucCmmd);
 
  P.parse();
  
  //string fileName = P.GetStringValueFor(fileCmmd);
  string in = P.GetStringValueFor(bStringCmmd);
  string lst = P.GetStringValueFor(lStringCmmd);
  string outdir = P.GetStringValueFor(oStringCmmd);
  int numIter = P.GetIntValueFor(iterCmmd);
  int allIter = P.GetIntValueFor(allCmmd);
  int numStates = P.GetIntValueFor(stateCmmd);
  double transPen = P.GetDoubleValueFor(transCmmd);
  int resume = P.GetIntValueFor(resumeCmmd);
  int neurons = P.GetIntValueFor(neuronCmmd);
  bool bEuc = P.GetBoolValueFor(eucCmmd);
  
  HMMControl control(outdir);
  control.SetExec(tmpPath);
  control.SetNumStates(numStates);
  control.SetTransition(transPen);
  control.SetNumNeurons(neurons);
  control.SetEuc(bEuc);

  control.SetupNames(in, lst);

  if (resume == 0) {
    control.WriteInitialFiles();
    control.Run(1);
  } else {
    control.SetRunNum(resume);
    cout << "WARNING: Skipping initial file write due to the -resume option" << endl;
  }


  //control.Run(numIter);

  int i;
  for (i=resume; i<allIter; i++) {
    cout << "Iteration # " << i << endl;
    control.UpdateConfigs();
    control.Run(numIter);
  }

  cout << "Computing local phylogienies." << endl;
  control.RunLocalTrees();
  cout << "All done!" << endl;

  return 0;
}
