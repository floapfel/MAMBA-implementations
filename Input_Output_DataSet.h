/*
Copyright (c) 2017, The University of Bristol, Senate House, Tyndall Avenue, Bristol, BS8 1TH, United Kingdom.
Copyright (c) 2018, COSIC-KU Leuven, Kasteelpark Arenberg 10, bus 2452, B-3001 Leuven-Heverlee, Belgium.

All rights reserved
*/
#ifndef _InputOutputDataSet
#define _InputOutputDataSet

/* A simple IO class which just uses standard
 * input/output to communicate values
 *
 * Whereas share values are input/output using
 * a steam, with either human or non-human form
 */

#include "Input_Output_Base.h"

#include <fstream>
using namespace std;

class Input_Output_DataSet : public Input_Output_Base
{
  ifstream *inpf;
  ofstream *outf;

  bool human; // Only affects share output#

  // for sfloat read in
  // int iter_ = 0;
  int iter_;
  int float_array[4] = {-1,-1,-1,0};

  int float_v;
  int float_p;
  int float_s;
  int float_z;

public:
  Input_Output_DataSet()
      : Input_Output_Base()
  {
    iter_ = 0;
  }

  void init(ifstream &ifs, ofstream &ofs, bool human_type)
  {
    inpf= &ifs;
    outf= &ofs;
    human= human_type;
    cout << "in the init+++++++++" << endl;
    iter_ = 0;
    float_v = -1;
    float_p = -1;
    float_s = -1;
    float_z = 0;
  }

  virtual void open_channel(unsigned int channel);
  virtual void close_channel(unsigned int channel);

  virtual gfp private_input_gfp(unsigned int channel);
  virtual void private_output_gfp(const gfp &output, unsigned int channel);

  virtual void public_output_gfp(const gfp &output, unsigned int channel);
  virtual gfp public_input_gfp(unsigned int channel);

  virtual void public_output_int(const long output, unsigned int channel);
  virtual long public_input_int(unsigned int channel);

  virtual void output_share(const Share &S, unsigned int channel);
  virtual Share input_share(unsigned int channel);

  virtual void trigger(Schedule &schedule);

  virtual void debug_output(const stringstream &ss);

  virtual void crash(unsigned int PC, unsigned int thread_num);
};

#endif
