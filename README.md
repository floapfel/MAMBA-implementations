## Implementation of a simple linear regression algorithm in MAMBA

MAMBA is a special language from the [SCALE-MAMBA library](https://github.com/KULeuven-COSIC/SCALE-MAMBA).
The algorithm is an adapted version of the one [here](https://machinelearningmastery.com/implement-simple-linear-regression-scratch-python/).

### Requirements

- Python + pip, GCC, OpenSSL and homebrew for MacOS.
- Reasonable knowledge of multi-party computation and working with PKIs.

### Installing and running

The neural net is located in the neural_network branch.

#### Install required packages:

```
brew install autogen autoconf automake libtool yasm mpc libmpc mpfr doxygen openssl@1.1
```
On Linux, use `apt-gen install` to get the same packages.


#### Install required Python libraries:

```
pip install gmpy2 numpy
```


#### Install MPIR:

Get the code:
```
git clone git://github.com/wbhart/mpir.git mpir
cd mipr
```

Configure with CXX:
```
autoreconf -i
./configure --enable-cxx
```

Make:
```
make
```

Check the uninstalled binaries:
```
make check
```

Install:
```
make install
```

Check the installed binaries:
```
make installcheck
```

Clean up the directory:
```
make clean
```


#### Install SCALE-MAMBA:

```
git clone https://github.com/KULeuven-COSIC/SCALE-MAMBA.git
cd SCALE-MAMBA
cp CONFIG CONFIG.mine
```

Open `CONFIG.mine` in a text editor of your choice. Next:
1. Change the `ROOT` variable to the path of your SCALE-MAMBA repo.
2. Change the `OSSL` variable to the path of your OpenSSL 1.1 installation.
  - This can be a bit tricky on MacOS, `which openssl` shows the system's LibreSSL location. OpenSSL 1.1 can be found at `/usr/local/Cellar/openssl@1.1/1.1.1/` with the 1.1.1 changing with your version.

Next, set up certificates.

In the following, every player *must* have a unique Common Name (CN) with no spaces. Distinguished Name (DN) information should also be filled in without spaces.

Go into the certificate store in the SCALE-MAMBA repo:
```
cd Cert-Store
```

Generate the private key for the root Certificate Authority (CA):
```
openssl genrsa -out RootCA.key 4096
```

Generate the CA's self-signed certificate:
```
openssl req -new -x509 -days 1826 -key RootCA.key -out RootCA.crt
```

For each player in the MPC (your choice of total number of players, e.g. 4) create a player certificate. For example, Player 0:
```
openssl genrsa -out Player0.key 2048
openssl req -new -key Player0.key -out Player0.csr
openssl x509 -req -days 1000 -in Player0.csr -CA RootCA.crt -CAkey RootCA.key -set_serial 0101 -out Player0.crt -sha256
```
The above assumes a global shared filesystem (local testing).

For an online environment, the private key for each player is kept in the Cert-Store on their computer only, and the player public keys for all players are copied to the Cert-Store on each player’s computer.

For example, if you are Player3, the only `.key` file on your computer is `Player3.key`, but you have `.crt` files for all players as well as the RootCA.


#### Install MAMBA-implementations:

Make sure you are in the SCALE-MAMBA directory.

Clone MAMBA-implementations into the `Programs` folder:
```
cd Programs
git clone https://github.com/floapfel/MAMBA-implementations.git
```

Relocate I/O files:
```
mv Input_Output_DataSet.cpp Input_Output_DataSet.h ../../src/Input_Output/
```

Next, open `src/Input_Output/IO.h` with a text editor of your choice.

Replace the line
```
#include "Input_Output_Simple.h"
```
with
```
#include "Input_Output_DataSet.h"
```
Save the file and close it.

Next, open `SCALE-MAMBA/src/Player.cpp`.
You need to change line 359 and 360. Originally:
```
unique_ptr<Input_Output_Simple> io(new Input_Output_Simple);
io->init(cin, cout, true);
```
Change these to:
```
unique_ptr<Input_Output_DataSet> io(new Input_Output_DataSet);
ifstream input;
ofstream output;
io->init(input, output, false);
```
Save the file and close it.

Navigate to the main folder of SCALE-MAMBA and rebuild with:
```
make
```

#### Configure MPC and run:

Setup the multi-party computation:
```
./Setup.x
```
Set up both the certificates and secret sharing.

For the certificates, set the number of players to that you chose earlier and specify certificates when on each prompt.

For secret sharing, use the following options:
- LSS: Shamir
- Modulus: 156567778759397001155884582490857862191
- Threshold: 1

Next, compile:
```
./compile.py Programs/MAMBA-implementations/slr/
```

Finally, run:
```
./Scripts/run-online.sh Programs/slr/
```
