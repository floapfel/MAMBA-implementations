## Implementation of a simple linear regression algorithm in MAMBA

MAMBA is a special language from the [SCALE-MAMBA library](https://github.com/KULeuven-COSIC/SCALE-MAMBA).
The algorithm is an adapted version of the one [here](https://machinelearningmastery.com/implement-simple-linear-regression-scratch-python/).

### How to run
* Install SCALE-MAMBA, following the instructions on their git repository.
* Clone this repository into Programs/
```
cd Programs
git clone https://github.com/floapfel/MAMBA-implementations.git
```
* Move Input_Outout_DataSet.cpp and .h into src/Input_Output/
```
mv Input_Output_DataSet.cpp Input_Output_DataSet.h ../src/Input_Output/
```
* Add Input_Output_DataSet.h to src/Input_Output/IO.h. Comment out the previous input function Input_Output_Simple.h. The file should then look like this:
```
#ifndef _IO
#define _IO

// Built in input functionality commented out:
// #include "Input_Output_Simple.h"

// New input functionality:
#include "Input_Output_DataSet.h"

#endif
```
* Configure the IO in the machine. To do so, change src/Player.cpp from line 359 on such that the new code is:
```
// unique_ptr<Input_Output_Simple> io(new Input_Output_Simple);
// io->init(cin, cout, true);
unique_ptr<Input_Output_DataSet> io(new Input_Output_DataSet);
ifstream input;
ofstream output;
io->init(input , output, false);
```
* Bulid changed files again using make in main folder
* Create certificates (see SCALE-MAMBA documentation, page 12 in v1.1)
* Setup the MPC with
```
Setup.x
```
Tested with the following setup:
```
LSSS: Option 2) Shamir
modulus: 156567778759397001155884582490857862191
threshold: 1
```
* Compile the slr.mpc file with
```
./compile.py Programs/slr/
```
* **Run** the .mpc file with
```
./Scripts/run-online.sh Programs/slr/
```
