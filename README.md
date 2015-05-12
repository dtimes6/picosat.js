#picosat.js

bindings to picosat (a SAT solver)

PicoSAT is a popular SAT solver written by Armin Biere in pure C.

see: http://fmv.jku.at/picosat/ for more details

## Build:

    node-gyp configure
    node-gyp build
 
## Install:

    sudo npm install -g
 
## Usage:

    sat = require("bindings")("picosat")
    picosat = new sat.PicoSAT;
    picosat.add_clause([1,-5,4]);
    picosat.add_clause([-1,5,3,4]);
    picosat.add_clause([-3,-4]);
    console.log(picosat.solve());
    ##Out[1]: [ 1, -2, -3, -4, 5 ]
  
