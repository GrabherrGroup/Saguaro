#include "../ryggrad/visual/Whiteboard.h"

#include "../ryggrad/base/CommandLineParser.h"
#include "../ryggrad/base/FileParser.h"
#include "../ryggrad/base/SVector.h"
#include "../ryggrad/visual/Color.h"

#include "../ryggrad/visual/Axes.h"
#include "DNAVector.h"

class Chr
{
public:
  Chr() {
    m_y = 0.;  
    m_len = 0;
    m_width = 10.;
  }

  Chr(double y, double l, const string &c, double w, color col) {
    m_y = y;
    m_name = c;
    m_len = l;
    m_width = w;
    m_color = col;
  }

  void Set(double y, double l, const string &c, double w = 10.) {
    m_y = y;
    m_name = c;
    m_len = l;
    m_width = w;
  }

  

  const string & Name() const {return m_name;}
  color Color() const {return m_color;}
  
  void DrawFill(ns_whiteboard::whiteboard & board, double scale, double x_offset, double from, double to, color col) {
    //cout << "Filling." << endl;
    board.Add( new ns_whiteboard::rect( ns_whiteboard::xy_coords(x_offset + from/scale, m_y + m_width ), 
                                        ns_whiteboard::xy_coords(x_offset + to/scale, m_y),
                                        col) );

  }

  double DrawBorder(ns_whiteboard::whiteboard & board, double scale, double x_offset) {
    double w = 1.;
    board.Add( new ns_whiteboard::rect( ns_whiteboard::xy_coords(x_offset-w, m_y + m_width + w), 
                                        ns_whiteboard::xy_coords(x_offset + m_len/scale+w, m_y - w),
                                        color(0, 0, 0)) );
    board.Add( new ns_whiteboard::rect( ns_whiteboard::xy_coords(x_offset, m_y + m_width), 
                                        ns_whiteboard::xy_coords(x_offset + m_len/scale, m_y),
                                        color(0.99, 0.99, 0.99)) );
    
    board.Add( new ns_whiteboard::text( ns_whiteboard::xy_coords(x_offset + m_len/scale + 8, m_y + m_width/2),
					m_name, color(0,0,0), 8., "Times-Roman", 0, true));
 
    
    double shift = 13;
    /*    board.Add( new ns_whiteboard::rect( ns_whiteboard::xy_coords(x_offset-w-1.5*m_width-shift, m_y + m_width + w), 
					ns_whiteboard::xy_coords(x_offset+w-1.5*m_width-shift + m_width, m_y - w),
					color(0, 0, 0)) );
    //board.Add( new ns_whiteboard::rect( ns_whiteboard::xy_coords(x_offset-1.5*m_width-shift, m_y + m_width), 
    //					ns_whiteboard::xy_coords(x_offset-1.5*m_width-shift + m_width, m_y),
    //					m_color) );*/

   return x_offset + m_len/scale;

  }

private:
  double m_y;
  double m_len;
  string m_name;
  double m_width;

  color m_color;
  
};

color GetColor(int i) 
{
  //cout << "GetColor" << endl;
  return MakeUpColor(i);

}


double PaintFrames(const vecDNAVector & dna, svec<Chr> &chr, double off, int min)
{
  int i, j;

  for (j=0; j<dna.isize(); j++) {
    int n = dna[j].isize();
    if (n < min)
      continue;

    chr.push_back(Chr(off, n, dna.NameClean(j), 10., GetColor(0)));
    off += 14.;
  }
 
  return off;
}
 

int FindChr(const svec<Chr> & c, const string & name) 
{
  for (int i=0; i<c.isize(); i++) {
    if (c[i].Name() == name)
      return i;
  }
  
  return -1;
}


class CactusList
{
public:
  CactusList() {}
  int isize() const {return m_cacti.isize();}
  const string & operator[] (int i) const {return m_cacti[i];}
  const color & Color() const {return m_color;}
  
  void push_back(const string & s) {m_cacti.push_back(s);}
  void SetColor(const color & c) {m_color = c;}

private:
  svec<string> m_cacti;
  color m_color;
};

class AllCacti
{
public:
  AllCacti() {}
  void Read(const string & fileName) {
    FlatFileParser parser;
    
    parser.Open(fileName);
    while(parser.ParseLine()) {
      if (parser.GetItemCount() == 0)
	continue;
      if (parser.AsString(0) == "color") {
	CactusList dummy;
	dummy.SetColor(color(parser.AsFloat(1), parser.AsFloat(2), parser.AsFloat(3)));
	m_groups.push_back(dummy);
	continue;
      }
      m_groups[m_groups.isize()-1].push_back(parser.AsString(0));
    }
  }


  int Get(const string & s) {
    int i, j;
    for (i=0; i<m_groups.isize(); i++) {
      const CactusList & l = m_groups[i];
      for (j=0; j<l.isize(); j++) {
	if (l[j] == s) 
	  return i;
      }
    } 
    return -1;
  }
  const color & Color(int i) const {return m_groups[i].Color();}

private:
  svec<CactusList> m_groups;
};

 
int main( int argc, char** argv )
{
 
  commandArg<string> aStringI1("-i","Saguaro output file (coordinates only, grep from LocalTrees.out)");
  commandArg<string> fastaString("-f","Genome fasta file");
  commandArg<string> cfgString("-c","Configuration file");
  commandArg<int> minCmmd("-m","Minimum scaffold/chromosome size", 10000000);
  commandArg<string> aStringO("-o","outfile (post-script)");
  commandArg<double> dotSize("-d","dot size", 1.);
  commandArg<double> aScale("-s","scale", 60000.);

  
  commandLineParser P(argc,argv);
  P.SetDescription("Paints chromosomes by Saguaro regions/cacti");

  P.registerArg(aStringI1);
  P.registerArg(aStringO);
  P.registerArg(fastaString);
  P.registerArg(cfgString);
  P.registerArg(minCmmd);
  P.registerArg(dotSize);
 P.registerArg(aScale);
 
  P.parse();

  string i1 = P.GetStringValueFor(aStringI1);
  string o = P.GetStringValueFor(aStringO);
  string fasta = P.GetStringValueFor(fastaString);
  string cfg = P.GetStringValueFor(cfgString);
  int min = P.GetIntValueFor(minCmmd);
  double dd = P.GetDoubleValueFor(dotSize);
 

  int i, j;

  
  vecDNAVector dna;
  dna.Read(fasta);

  ns_whiteboard::whiteboard board;

  int x_offset = 100;
  int y_offset = 100;

  double scale = P.GetDoubleValueFor(aScale);
  double x_scale = scale;
  double x_max = 0;
  double y_max = 0;

  FlatFileParser parser;

  parser.Open(i1);
  
  svec<Chr> target;
  //svec<Chr> query;

  //string name1, name2;
  double d = PaintFrames(dna, target, x_offset, min);

  
  AllCacti cacti;
  cacti.Read(cfg);

  y_max = d;

  for (i=0; i<target.isize(); i++) {
    d = target[i].DrawBorder(board, scale, x_offset);
    if (d > x_max)
      x_max = d;
  }

  int lastIndex = -1;
  int lastStart = 0;
  int lastStop = -1;
  string lastChr;
  int iT;

  int paintcounter = 0;
  int groupcounter = 0;
  //parser.ParseLine();
  while(parser.ParseLine()) {
    if (parser.GetItemCount() < 10)
      continue;

    char chr[256];
    strcpy(chr, parser.AsString(1).c_str());
    chr[strlen(chr)-1] = 0;
 	
    int from = parser.AsInt(2); 
    int to = parser.AsInt(4); 
 
    iT = FindChr(target, chr);
    if (iT < 0)
      continue;
 
    const string & c = parser.AsString(0);
   
    int index = cacti.Get(c);
    if (index < 0) {
      cout << "Could not find " << c << endl;
      cout << "Check the configuration file!!!" << endl;
      return -1;
    }
    if (index == lastIndex && lastChr == chr) {
      lastStop = to;
      //cout << "Grouping." << endl;
      continue;
    }

    if (lastIndex != -1) {
      iT = FindChr(target, lastChr);
      target[iT].DrawFill(board, scale, x_offset, lastStart, lastStop, cacti.Color(lastIndex));
      paintcounter++;
      //cout << "Painting." << endl;
    }

    lastIndex = index;
    lastChr = chr;
    lastStart = from;
    lastStop = to;

  }
  iT = FindChr(target, lastChr);
  target[iT].DrawFill(board, scale, x_offset, lastStart, lastStop, cacti.Color(lastIndex));
  paintcounter++;

  cout << "Painted " << paintcounter << " regions." << endl;

  ofstream out (o.c_str());
  ns_whiteboard::ps_display display(out, x_max + x_offset, y_max + x_offset);
  board.DisplayOn(&display);
  
  
  return 0;
}
