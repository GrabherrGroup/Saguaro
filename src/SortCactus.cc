#define FORCE_DEBUG

#include <string>
#include "base/CommandLineParser.h"
#include "base/FileParser.h"

class Pair
{
public:
  int index;
  double val;
  bool operator < (const Pair & p) const {
    return val < p.val;
  }
};

class Line
{
public:
  string name;
  svec<double> data;
};

int main( int argc, char** argv )
{

  commandArg<string> fileCmmd("-i","input file");
  commandArg<int> bCmmd("-c","column");
  commandLineParser P(argc,argv);
  P.SetDescription("Testing the file parser.");
  P.registerArg(fileCmmd);
  P.registerArg(bCmmd);
 
  P.parse();
  
  string fileName = P.GetStringValueFor(fileCmmd);
  int from = P.GetIntValueFor(bCmmd);
 

  //comment. ???
  FlatFileParser parser;
  
  parser.Open(fileName);
  parser.ParseLine();
  cout << parser.Line() << endl;
  parser.ParseLine();
  //cout << parser.Line() << endl;
  int n = parser.GetItemCount();

  svec<Line> line;
  int i, j;
  int k = 0;
  svec<Pair> s;
  while (parser.ParseLine()) {
    if (parser.GetItemCount() == 0)
      continue;
    Line l;
    l.name = parser.AsString(0);
    for (i=1; i<parser.GetItemCount(); i++) {
      l.data.push_back(parser.AsFloat(i));
      //cout << "Push " << parser.AsFloat(i) << " " << i-1 << endl;
      if (k == from) {
	Pair p;
	p.index = i-1;
	p.val = parser.AsFloat(i);
	s.push_back(p);
      }
    } 
    //cout << "Read data: " << l.data.isize() << endl;
    line.push_back(l);
    k++;
    if (k == n) {
      Sort(s);
      for (i=0; i<line.isize(); i++) {    
	cout << line[s[i].index].name << " ";
      }
      cout << endl;
      
      for (i=0; i<line.isize(); i++) {    
	cout << line[s[i].index].name;
	for (j=0; j<s.isize(); j++) {
	  cout << " " <<  line[s[i].index].data[s[j].index];
	}
	cout << endl;
      }
      
      line.clear();
      s.clear();

      parser.ParseLine();
      if (parser.GetItemCount() == 0)
	break;
      cout << parser.Line() << endl;
      parser.ParseLine();
      k = 0;
      //cout << parser.Line() << endl;

    }
  }

  //cout << "Cacti: " << k << endl;
  //cout << "Data for " << line[0].data.isize() << endl;


  return 0;
}
