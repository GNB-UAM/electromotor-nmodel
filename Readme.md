
# electromotor-nmodel

Computational model of the electromotor command network of pulse-type mormyrids. Code also includes the genetic algorithm used to automatically tune the parameters of the model to the target patterns.

Please, if you use this model or the code of the genetic algorithm, cite in your publication the following paper:
A. Lareo, P. Varona. F. Rodríguez. Modeling the variability of the electromotor command system of pulse mormyrids. BioRxiv 10.1101/2020.06.09.142083

## Requisites
```
sudo apt install libboost-all-dev libyaml-cpp libhdf5-dev git-all
git clone https://github.com/angellareo/electromotor-nmodel.git
cd electromotor-nmodel
```
## Compile
```
mkdir bin
cd bin
cmake ..
make
```

## emmodel

Simulates the model contained in the input file.
Prints in the output file v from VPd, DP, PCN and CN in every time step of the simulation described in the config input file.
With -s it prints synapse data.

### Usage

```
$ ./emmodel <option(s)> SOURCES
Options:
    -h, Show this message.
    -i, Input file.
    -o, Output file.
    -s, Print synapses.

```

## emmodelGAFit

Parameter adjusting based on genetic algorithm optimization.

### Usage

```
$ ./emmodelGAFit <option(s)> SOURCES

Options:
    -h, Show this message.
    -i, Input file.
    -o, Output file
    -h, Show this message.
    -i, Input file.
    -o, Output file
    -g, Number of generations.
    -e, Stop convergence value.
    -s, Statistics output file.
    -n, Number of individuals per generation.
    -a, Manual limits [-a,a] for alpha parameter.
    -b, Manual limits [-b,b] for beta parameter.
    -t, Manual limits [-t,t] for the conductivity parameter.
    -m, Manual limits [-m,m] for maximum release time parameter.
    -p, Percentual limits from the initial value of all parameters.
    -q, Print best GA each q generations.
    ```