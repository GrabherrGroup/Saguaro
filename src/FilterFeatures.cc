#include <string>

#include "../ryggrad/src/base/CommandLineParser.h"
#include "../ryggrad/src/base/FileParser.h"
#include "HMMDistance.h"
#include "../ryggrad/src/general/DNAVector.h"


string Clean(const string & s) {
  string out = s;

  for (int i=0; i<s.size(); i++) {
    if (s[i] == '/') {
      out = &s[i+1];
    }
  }
  return out;
}

int main(int argc,char** argv)
{

  commandArg<string> aStringCmmd("-i","input feature file");
  commandArg<string> bStringCmmd("-o","output feature file");
  commandArg<string> cStringCmmd("-l","list of names to remove");
  commandLineParser P(argc,argv);
  P.SetDescription("Remove samples from a feature file");
  P.registerArg(aStringCmmd);
  P.registerArg(bStringCmmd);
  P.registerArg(cStringCmmd);
  
  P.parse();

  string infile = P.GetStringValueFor(aStringCmmd);
  string outfile = P.GetStringValueFor(bStringCmmd);
  string remove = P.GetStringValueFor(cStringCmmd);
  
  svec<string> names;

  FlatFileParser fileParser;
  fileParser.Open(remove);

  while (fileParser.ParseLine()) {
    if (fileParser.GetItemCount() == 0)
      continue;
    names.push_back(fileParser.AsString(0));
  }

  HMMFeatureVector in, out;

  cout << "Reading data" << endl;
  in.Read(infile);
  cout << "done." << endl;
 
  int i, j;

  svec<int> good;

  for (i=0; i<in.GetNameCount(); i++) {
    bool b = true;
    for (j=0; j<names.isize(); j++) {
      if (names[j] == in.GetName(i)) {
	b = false;
      }	
    }
    if (!b)
      continue;

    string clean = Clean(in.GetName(i));
    cout << "Adding sample " << clean << endl;
    out.Names().push_back(clean);
    good.push_back(i);

  }
  for (i=0; i<in.isize(); i++) {
    //cout << "Add feature " << i << endl;
    const HMMFeature & f = in.Data()[i];
    CompressedFeature & c = in.CompData()[i];
    HMMFeature fn;
    CompressedFeature cn;
    fn = f;
    //fn.resize(good.isize());    
    cn.Data().resize(good.isize());
    //cout << "f.size() " << f.isize() << endl;
    //cout << "Data " << c.Data().isize() << " floats " << c.Floats().isize() << endl;
    cout << f.Name() << " " << f.GetPosition();

    svec<double> nuke;
    nuke.resize(4, 0);
    int count = 0;
    svec<char> diff;
    for (j=0; j<good.isize(); j++) {
      //cout << " loop " << j << endl;
      //fn[j] = f[good[j]];
      cn.Data()[j] = c.Data()[good[j]];     
      diff.push_back(cn.Data()[j]);

      cout << " " << cn.Data()[j];

      if (c.Data()[good[j]] != '-' && c.Data()[good[j]] != '?')
	count++;
      
      nuke[0] += DNA_EqualAmb(cn.Data()[j], 'A');
      nuke[1] += DNA_EqualAmb(cn.Data()[j], 'C');
      nuke[2] += DNA_EqualAmb(cn.Data()[j], 'G');
      nuke[3] += DNA_EqualAmb(cn.Data()[j], 'T');
    }
    UniqueSort(diff);

    double max = 0.;
    for (j=0; j<nuke.isize(); j++) {
      if (nuke[j] > max)
	max = nuke[j];
    }
    if (good.isize() - count > 2) {
      cout << " -- bad pos, skipping." << endl;
      continue;
    }

    if (max > good.isize()-2) {
      cout << " -- too few disagree, skipping." << endl;
      continue;
    }
    if (diff.isize() == 1) {
      cout << " -- all heteros, skipping." << endl;
      continue;
    }
    cout << " ++ OK" << endl;
    out.Data().push_back(fn);
    out.CompData().push_back(cn);

  }
  
 
  cout << endl << "Data has " << out.GetNameCount() << " samples." << endl;
  cout << "Writing data" << endl;
  out.Write(outfile);
  cout << "done." << endl;

 

  return 0;

}
  
