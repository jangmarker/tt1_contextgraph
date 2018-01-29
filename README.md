[![Build status](https://ci.appveyor.com/api/projects/status/k8v7hgjtr1uh1qnp?svg=true)](https://ci.appveyor.com/project/jangmarker/tt1-contextgraph) [![Build Status](https://travis-ci.org/jangmarker/tt1_contextgraph.svg?branch=master)](https://travis-ci.org/jangmarker/tt1_contextgraph) [![codecov](https://codecov.io/gh/jangmarker/tt1_contextgraph/branch/master/graph/badge.svg)](https://codecov.io/gh/jangmarker/tt1_contextgraph)

# TT1 Context Graph - Lösung Jan Marker

## Dependencies
The program is mainly based on the C++ standard library, except for:

- Catch (http://catch-lib.net/) - a unit testing framework for C++
- CLI11 (https://github.com/CLIUtils/CLI11) - framework to parse CLI parameters

The two dependencies are included in `3rdparty/` and are to no concern of a user.

The code uses features of C++17, including:

- string_view
- experimental/filesystem

It was tested with Visual Studio 15.0 2017 and GCC 7.2.1.

## Usage
`--help` can be used to gain information about possible parameters:
```bash
./tt1_contextgraph --help
Text Technologie 1 - Aufgabe 5 - Lösung Jan Marker
Usage: ./tt1_contextgraph [OPTIONS]

Options:
  -h,--help                   Print this help message and exit
  -i TEXT                     Path to the vector file.
  -o TEXT                     Path to the output GML file.
  -s TEXT                     Search term.
  -t UINT                     Number of neighbors per node.
  -d UINT                     Depth of search
```

See `./00_EXAMPLE_CALLS.md` for some sample invocations.

## Code Organisation

### `clip.cpp`
- orchestrator
- command line parsing
- reading of *.vec file (supplied via `-i`)
- search for the graph according to `-t` and `-d`
- output of GML to file

### `database.{h,cpp}`
- storage of vectors read from *.vec file
- implementation cosine similarity
- search for t most similar to a given word

### `file_access.{h,cpp}`
- reading of *.vec file
- the file is parsed according to its first line
  which contains vector count and column count
- if that information is accurate, parsing of the
  file may fail

### `gml_generation.{h,cpp}`
- generation of GML structure out of search tree
  provided by `search`
- the `Graph` type contains pointer to root of
  search tree and desired depth
- the depth is required to also emit edges for
  leaf nodes that connect the leaf node and
  another _existing_ node

### `helper_tst.{h,cpp}`
helpers to generate test data in various unit tests

### `main.cpp`
connects `main` with `cli`

### `search.{h,cpp}`
- use `Database::most_similar(WordView, std::size_t)`
  to build a tree of nodes
- root is the search term
- every node has neighbors, neighbors of one level
  of deepness have the same distance from the root
  node
- it is implemented as a tree but models a graph:
  for every edge a node is duplicated in the tree
  
#### performance consideration
- this has performance drawbacks when searching, because
  `Database::most_similar` has a long run time and is
  called multiple times for the same search term without
  cache
- however, for d=2 the implementation is still sufficiently
  fast
  
### `vector.{h,cpp}`
- internal representation of a vector as a Word (string),
  a vector of doubles (columns) and euclideanNorm (cached)

### `tst_*.cpp`
unit tests for the respective modules