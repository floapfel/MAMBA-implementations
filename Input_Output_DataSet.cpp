/*
Copyright (c) 2017, The University of Bristol, Senate House, Tyndall Avenue, Bristol, BS8 1TH, United Kingdom.
Copyright (c) 2018, COSIC-KU Leuven, Kasteelpark Arenberg 10, bus 2452, B-3001 Leuven-Heverlee, Belgium.

All rights reserved
*/

#include "Input_Output_DataSet.h"
#include "Exceptions/Exceptions.h"

#include <string>
#include "math.h"

void Input_Output_DataSet::open_channel(unsigned int channel)
{
  cout << "Opening channel " << channel << endl;

  string filename;
  // input_1.txt and input_2.txt can be used for testing
  if (channel <= 10) {
    filename = "input_1.txt";
    inpf->open(filename);
  } else if (channel > 10 && channel <= 20){
    filename = "input_2.txt";
    inpf->open(filename);
  } else if (channel > 20 && channel <= 30) {
    filename = "Programs/slr/input/AutoInsurSweden_x.txt";
    inpf->open(filename);
  } else if (channel > 30 && channel <= 40) {
    filename = "Programs/slr/input/AutoInsurSweden_y.txt";
    inpf->open(filename);
  } else if (channel > 40 && channel <= 50) {
    filename = "output_1.txt";
    outf->open(filename);
  } else {
    filename = "output_2.txt";
    outf->open(filename);
  }

  if (channel <= 40) {
    if (inpf->fail()) {
      cout << "Could not find file!" << endl;
    } else {
      cout << "Found file " << filename << endl;
    }
  } else {
    if (outf->fail()) {
      cout << "Could not find file!" << endl;
    } else {
      cout << "Found file " << filename << endl;
    }
  }
}

void Input_Output_DataSet::close_channel(unsigned int channel)
{
  cout << "Closing channel " << channel << endl;
  inpf->close();
  outf->close();
}


gfp Input_Output_DataSet::private_input_gfp(unsigned int channel)
{
  // cout << "Input channel " << channel << " : " << endl;
  int NULL_for_passing_to_mpc = -123456789;
  string str;
  float x;
  int var = -1;
  if (inpf->good()) {
    (*inpf) >> x;
    if (!inpf->eof()) {
      x = round(x);
      var = static_cast<int>(x);
    } else {
      var = NULL_for_passing_to_mpc;
    }
  }

  gfp y;
  y.assign(var);
  return y;
}

void Input_Output_DataSet::private_output_gfp(const gfp &output, unsigned int channel)
{
  cout << "Output channel " << channel << " : ";
  output.output(cout, true);
}

gfp Input_Output_DataSet::public_input_gfp(unsigned int channel)
{
  cout << "Enter value on channel " << channel << " : ";
  word x;
  cin >> x;
  gfp y;
  y.assign(x);

  // Important to have this call in each version of public_input_gfp
  Update_Checker(y, channel);

  return y;
}

void Input_Output_DataSet::public_output_gfp(const gfp &output, unsigned int channel)
{
  cout << "Output channel " << channel << " : ";
  output.output(cout, true);
  cout << endl;
}

long Input_Output_DataSet::public_input_int(unsigned int channel)
{
  cout << "Enter value on channel " << channel << " : ";
  long x;
  cin >> x;

  // Important to have this call in each version of public_input_gfp
  Update_Checker(x, channel);

  return x;
}

void Input_Output_DataSet::public_output_int(const long output, unsigned int channel)
{
  cout << "Output channel " << channel << " : " << output << endl;
}

void Input_Output_DataSet::output_share(const Share &S, unsigned int channel)
{
  (*outf) << "Output channel " << channel << " : ";
  S.output(*outf, human);
}

Share Input_Output_DataSet::input_share(unsigned int channel)
{
  cout << "Enter value on channel " << channel << " : ";
  Share S;
  S.input(*inpf, human);
  return S;
}

void Input_Output_DataSet::trigger(Schedule &schedule)
{
  printf("Restart requested: Enter a number to proceed\n");
  int i;
  cin >> i;

  // Load new schedule file program streams, using the original
  // program name
  //
  // Here you could define programatically what the new
  // programs you want to run are, by directly editing the
  // public variables in the schedule object.
  unsigned int nthreads= schedule.Load_Programs();
  if (schedule.max_n_threads() < nthreads)
    {
      throw Processor_Error("Restart requires more threads, cannot do this");
    }
}

void Input_Output_DataSet::debug_output(const stringstream &ss)
{
  printf("%s", ss.str().c_str());
  fflush(stdout);
}

void Input_Output_DataSet::crash(unsigned int PC, unsigned int thread_num)
{
  printf("Crashing in thread %d at PC value %d\n", thread_num, PC);
  throw crash_requested();
}
