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
* Make changes in src/Input_Output/ to enable input funtion from file
```
(will be added soon)
```
* Setup the MPC with
```
Setup.x
```
* Compile the slr.mpc file with
```
./compile.py Programs/slr/
```
* **Run** the .mpc file with
```
./Scripts/run-online.sh Programs/slr/
```

