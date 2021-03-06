//#ifndef FORCE_DEBUG
//#define NDEBUG
//#endif

#include <string>

#include "ryggrad/src/base/CommandLineParser.h"
#include "HMMDecode.h"
#include "HMMDistance.h"
#include "ryggrad/src/base/FileParser.h"

#include "SOM.h"
#include "HMMDistance.h"
#include "ryggrad/src/base/RandomStuff.h"


class HMMMatrixScores : public HMMStateFrameScoreSource
{
 public:
  HMMMatrixScores(HMMTrees * pTrees) {
    m_pTrees = pTrees;
  } 
  virtual ~HMMMatrixScores() {}

  void SetFeature(const HMMFeature & f) {
    m_feature = f;
    m_pTrees->ClearCache();
  }

  virtual double GetScore(const string & stateName) const {
    //out << "Getting score..." << endl;
    return m_pTrees->GetScore(stateName, m_feature);
  }

private:
  HMMTrees * m_pTrees;
  HMMFeature m_feature;
};


bool F2F(svec<double> & feat, svec<int> & valid, const svec<double> & f)
{  
  int k = f.isize();
  if (f[f.isize()-1] < 0.)
    return false;
     
  feat.resize(k, 0.);
  
  valid.resize(k, 1);
  int total = 0;
  for (int x=0; x<f.isize(); x++) {
    
    if (f[x] < 0.) {
      valid[x] = 0;
    } else {
      valid[x] = 1;
      feat[x] = f[x];
      total++;
    }
  }
  double ratio = (double)total / (double)f.isize();
  double div = (double)f.isize();
  //cout << "Good " << total << " total " << f.isize() << endl;
  //cout << ratio << " >= " << div << endl;
  if (ratio >= 0.5)
    return true;
  else
    return false;
}



 
int main(int argc,char** argv)
{

  
  commandArg<string> aStringCmmd("-c","Configuration file that specifies the structure of the HMM");
  commandArg<string> bStringCmmd("-i","Feature vector", "");
  commandArg<string> lStringCmmd("-l","Feature vector list file", "");
  commandArg<string> cStringCmmd("-m","Distance matrices");
  commandArg<string> gStringCmmd("-g","Garbage matrix");
  commandArg<string> oStringCmmd("-o","Distance matrices output");
  commandArg<int> iterCmmd("-iter","# of iterations", 5);
  commandArg<int> somCmmd("-neurons","# of SOM neurons", 800);
  commandArg<bool> eucCmmd("-e","use the euclidean distance", false);
  commandLineParser P(argc,argv);
  P.SetDescription("Generic and configurable HMM training.");
  P.registerArg(aStringCmmd);
  P.registerArg(bStringCmmd);
  P.registerArg(lStringCmmd);
  P.registerArg(cStringCmmd);
  P.registerArg(oStringCmmd);
  P.registerArg(gStringCmmd);
  P.registerArg(iterCmmd);
  P.registerArg(somCmmd);
  P.registerArg(eucCmmd);

  P.parse();

  string config = P.GetStringValueFor(aStringCmmd);
  string in = P.GetStringValueFor(bStringCmmd);
  string lst = P.GetStringValueFor(lStringCmmd);
  string matrix = P.GetStringValueFor(cStringCmmd);
  string garbageFile = P.GetStringValueFor(gStringCmmd);
  string output = P.GetStringValueFor(oStringCmmd);
  int numIter = P.GetIntValueFor(iterCmmd);
  int neurons = P.GetIntValueFor(somCmmd);

  bool bEuc = P.GetBoolValueFor(eucCmmd);

  if (lst == "" && in == "") {
    cout << "You MUST specify either -i or -l!" << endl;
    return -1;
  }

  int i, j, k;


  HMMFeatureVector features;

  if (in != "") {
    cout << "Reading features..." << endl;
    features.Read(in);
    cout << "done!" << endl;
  } else {
    FlatFileParser parserIn;
    parserIn.Open(lst);

    while (parserIn.ParseLine()) {
      if (parserIn.GetItemCount() == 0)
	continue;
      cout << "Reading features from " << parserIn.AsString(0) << endl;
      features.MergeRead(parserIn.AsString(0));
      
    } 
  }



  HMMTrees model;
  if (bEuc)
    model.SetEuclidean();

  HMMMatrixScores scores(&model);

  cout << "Reading models." << endl;
 
  model.AddRead(matrix);
  cout << "OK" << endl;
  cout << "Read garbage" << endl;

  HMMTrees garbage;
  if (bEuc)
    garbage.SetEuclidean();


  if (garbageFile != "")
    garbage.AddRead(garbageFile);
  garbage.Sort();

  cout << "OK" << endl;
  //-------------------------------------------
  //cout << "Adding fake model" << endl;
  //model.Add(features[0], "Tree_1");
  //for (i=0; i<features.GetNameCount(); i++)
  //model.SetMatrixName(i, features.GetName(i));
  

  int nLoops = numIter;


  double worstScore = 0.;
  int worstStart = -1;
  int worstEnd = -1;
  svec<double> allscores;

  int wordCount = 0;
  
  svec<int> segment;
  segment.resize(features.isize(), -1);

  //features.resize(100000);

  for (k=0; k<nLoops; k++) {

    cout << "Dynprog'ing, iteration # " << k << endl;
    HMMUpdate update;
    Read(update, config);
    wordCount = update.GetWordCount();
    cout << "Number of frames: " << features.isize() << endl;
    for (i=0; i<features.isize(); i++) {
      scores.SetFeature(features[i]);
      update.Update(scores);
      if (i > 0 && i % 10000 == 0) {
	cout << "Processed: " << i << " (" << 100. * (double)i/(double)features.isize() << " %)"  << endl;
//	return 0;
      }

      //if (i > 3000000)
      //break;
    }
    cout << "REPORTING Traceback and Update" << endl;  
    vec<HMMTracebackNode> out;
    update.TraceBack(out);
    cout << "Done" << endl;
    model.ResetSameDiff(); 
    
    worstScore = -1.;
    double lastScore = 0;
    allscores.clear();
    allscores.resize(out.isize(), 0.);
    for (i=0; i<out.isize(); i++) {  
      int len = features[out[i].To()].GetPosition() - features[out[i].From()+1].GetPosition();
      int frames = out[i].To() - out[i].From() - 1;
      cout << out[i].Name() << "\t" << features[out[i].To()].Name() << ": " << features[out[i].From()+1].GetPosition();
      cout << " - " << features[out[i].To()].GetPosition() << "\tlength: " << len;
      cout << "\t(frames " << out[i].From()+1 << "-" << out[i].To() << " l=" << frames << ") \tscore=" << (out[i].Score() - lastScore)/double(out[i].To()-out[i].From());
      cout << endl;
      
      for (j=out[i].From()+1; j<=out[i].To(); j++) {
	model.Update(out[i].Name(), features[j]);
	segment[j] = out[i].Index();
      }

      double score = out[i].Score() - lastScore;

      score = score/(double)(out[i].To()-out[i].From()+3);
      allscores[i] = score;
      
      if (score > worstScore) {
	worstScore = score;
	worstStart = out[i].From()+1;
	worstEnd = out[i].To();
      }
      lastScore = out[i].Score();
    }
    cout << "REPORTING End Traceback and Update" << endl;  
  
    model.PrettyPrint(); //modified by pam
    
    cout << "Done printing." << endl;
    //Sort(allscores);
  
    /*
    if (garbageFile != "") {
      cout << "Update worst fit from " << worstStart << " to " << worstEnd << endl;
      lastScore = 0;
      double cutoff = allscores[allscores.isize()/2]-1.;
      //cutoff = -1.;
      for (i=0; i<out.isize(); i++) {  
	double score = out[i].Score() - lastScore;
	
	score = score/(double)(out[i].To()-out[i].From()+3);
	if (score >= cutoff) {
	  cout << "Adding " << out[i].From()+1 << " - " << out[i].To() << endl;
	  for (j=out[i].From()+1; j<=out[i].To(); j++) {
	    garbage.Update(0, features[j]);
	  }
	}
	lastScore = out[i].Score();
      }
    }
      //}
      garbage.PrettyPrint();*/
  }

  cout << "Running SOM." << endl;
 

  if (garbageFile != "") {

    string outVec = garbageFile + ".vec";

    CoordsList used;
    used.Read(outVec);


    svec<SelfOrgFeatMap> som;
    som.resize(wordCount);
    OneDimSOMOrganizer one;

    int somSize = neurons;
    svec<double> dummy;
    features.SimpleFeature(dummy, 0);
    int k = dummy.isize();
    one.SetDimRange(k, 0., 1.);

    cout << "Organizing SOM nodes..." << endl;
    for (i=0; i<som.isize(); i++)
      som[i].Organize(one, somSize);
    cout << "done!" << endl;



    cout << "Num features: " << features.isize() << endl;
    int reallyProcessed = 0;
    for (j=0; j<features.isize(); j++) {
      //if (j > 150000)
      //break;
      
      svec<double> f;
      
      int rand =(int) RandomInt(features.isize());
      

      int segIndex = segment[rand];

      features.SimpleFeature(f, rand);
      svec<double>  feat;
      svec<int>  valid;


      if (!F2F(feat, valid, f)) {
	//cout << "Skipping feature, trying again... " << j << endl;
	//j--;
	continue;
      }

      if (j % 10000 == 0) {
	cout << "Training feature " << j << " -> really " << reallyProcessed << endl;
      }

      reallyProcessed++;

      if (segIndex < 0)
	cout << "Unassigned SNP" << endl;
      else
	som[segIndex].Train(feat, valid);
    }
    for (i=0; i<som.isize(); i++)
      cout << i << " WEIGHT: " << som[i].Weight() << endl;

  

    //som.Print();
    int top = -1;
    int second = -1;
    double dist = 0.;
    int bestSom = -1;

    double maxWeight = 0.25;
    bool bGoodMax = false;
    for (i=0; i<som.isize(); i++) {
      if (som[i].Weight() < maxWeight) {
	bGoodMax = true;
	break;
      }
    }

    for (i=0; i<som.isize(); i++) {
      if (bGoodMax && som[i].Weight() > maxWeight)
	continue;
      if (used.isize() > 0)
	cout << endl << "SOM " << i << "  densest: " << som[i].DensestNode(used) << endl;
      else
 	cout << endl << "SOM " << i << "  densest: " << som[i].DensestNode() << endl;
      int localtop = som[i].GetTop();
      int localsecond = som[i].GetSecond();
      double localdist = som[i].GetDist();
      cout << "=======================================================" << endl;
      cout << "WINNER: " << localtop << endl;
      som[i].GetNode(localtop).Print();
      cout << "MOST CONTRARY: " << localsecond << endl;
      som[i].GetNode(localsecond).Print();
      cout << "=======================================================" << endl;
      if (localdist >= dist) {
	bestSom = i;
	dist = localdist;
	top = localtop;
	second = localsecond;
      }
    }

 

    SOMNode & node = som[bestSom].GetNode(second);
 
    const svec<double> & cc = node.Coords();
    FILE * pVec = fopen(outVec.c_str(), "a");
    for (i=0; i<cc.isize(); i++) 
      fprintf(pVec, "%f  ", cc[i]);
    fprintf(pVec, "\n");
    fclose(pVec);

    cout << "Training new cactus..." << endl;
    int processedHits = 0;
    for (j=0; j<features.isize(); j++) {
      if (segment[j] != bestSom)
	continue;
      if (j % 10000 == 0)
	cout << j << endl;
      svec<double> f;

      features.SimpleFeature(f, j);
      svec<double>  feat;
      svec<int>  valid;

      //cout << "Train?" << endl;

      if (!F2F(feat, valid, f))
	continue;
      //cout << "Train (2)?" << endl;
      int w = som[bestSom].BestMatch(feat, valid);
      if (w == second) {
	//cout << "Train (3)?" << endl;
 	//cout << "Feature:" << endl;
	//for (int xx=0; xx<feat.isize(); xx++)
	//cout << xx << "\t" << feat[xx] << "\t" << valid[xx] << "\t" << f[xx] << endl;
	
	//exit(0);

	processedHits++;
	garbage.Update(0, features[j]);
      }
    }
    cout << "Processed: " << processedHits << endl;
  }


  //cout << "Fake update" << endl;
  //for (i=0; i<features.isize(); i++) {
  //model.Update("Tree_1", features[i]);
  //}

  cout << "Writing output." << endl;
  // model.PrettyPrint();
  model.PrettyPrint(output);
  if (garbageFile != "")
    garbage.PrettyPrint(garbageFile);

  cout << "All done here." << endl;

  return 0;

}
  
