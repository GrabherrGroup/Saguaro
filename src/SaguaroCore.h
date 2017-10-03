#ifndef _SAGUAROCORE_H_
#define _SAGUAROCORE_H_

#include <string>
#include "ryggrad/src/base/FileParser.h"
#include "HMMDecode.h"
#include "HMMDistance.h"


class CactusLine
{
public:
  CactusLine() {}

  double & operator [] (int i) {return m_data[i];}
  void resize(int i) {m_data.resize(i);}
  int isize() const {return m_data.isize();}

private:
  svec<double> m_data;
};


class Cactus
{
public:
  Cactus(int size); 

  void Read(FlatFileParser & parser, const string & name, int size); 
  void WriteLine(FILE * p, int i); 
  void Add(double v); 
  void Scale(double v); 
  
private:
  string m_name;
  svec<CactusLine> m_data;
};

class HMMControl
{

public:
  HMMControl(const string & outDir); 

  void SetEuc(bool b)           { m_bEuc = b;      }
  void SetTransition(double d)  { m_trans = d;     }
  void SetNumStates(int s)      { m_numStates = s; }
  void SetExec(const string &s) { m_exec = s;      }
  void SetRunNum(int i)         { m_run = i;       }
  void SetupNames(const string & in, const string & lst); 
  void UpdateConfigs(); 
  void WriteInitialFiles(); 
  void Run(int iter);

  void SetNumNeurons(int k);
  void RunLocalTrees(); 

private:
  void Exec(const string & cmd, bool bIgnore = false); 

  int m_run;
  int m_numStates;
  svec<string> m_names;
  string m_outDir;
  string m_config;
  string m_trees;
  string m_feat;
  string m_list;
  string m_log;
  string m_garbage;

  string m_exec;
  string m_neurons;

  bool m_bEuc;

  double m_trans;
};

#endif //_SAGUAROCORE_H_
