# Sudoku Solver

Master: [![Build Status](https://travis-ci.org/lucasguesserts/sudoku_solver.svg?branch=master)](https://travis-ci.org/lucasguesserts/sudoku_solver)
Develop: [![Build Status](https://travis-ci.org/lucasguesserts/sudoku_solver.svg?branch=develop)](https://travis-ci.org/lucasguesserts/sudoku_solver)

C++ library to support solving sudoku games. It defines methods, algoritms and computacional structures for development and also applications for non-developers.

To know more about the sudoku game, see [wikipedia](en.wikipedia.org/wiki/Sudoku).

---

## Dependencies

To build, it is necessary:

- C++ compiler.
- cmake
- make
- HDF5

To install these dependencies, there are two options, described below.

### Install by Your Own

In most linux distributions, it can be done using the package manager. For example, on Ubuntu (and other Debian based):

```shell
$ sudo apt install g++
$ sudo apt install make
$ sudo apt install cmake
$ sudo apt install libhdf5-serial-dev
```

### Install Using Conda

- Install conda following the [instructions](https://conda.io/docs/user-guide/install/index.html) provided by the [conda](conda.io) or executing:
  ```shell
    $ wget https://repo.continuum.io/miniconda/Miniconda3-latest-Linux-x86_64.sh -O miniconda.sh;
    $ bash miniconda.sh -b -p $HOME/miniconda
    $ export PATH="$HOME/miniconda/bin:$PATH"
    $ hash -r
    $ conda config --set always_yes yes
    $ conda update -q conda
  ```
- Create a conda environment with the configurations and packages:
  ```shell
    $ conda env create -f SudokuSolverEnv.yml
  ```
- Load the project environment _SudokuSolverEnv_:
  ```shell
	$ source activate SudokuSolverEnv
  ```

That's it!. Remember that to build the project, the _SudokuSolverEnv_ must be loaded (last command above).

## Building

Simply execute:

```shell
$ mkdir build
$ cd build
$ cmake ..
$ make
```

If you'd like to run the tests:
```shell
$ make test
```

If you'd like to install the applications:
```shell
$ make install
```
