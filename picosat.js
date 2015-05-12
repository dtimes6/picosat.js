var sat = require('./build/Release/picosat.node');
var s = new sat.PicoSAT();
s.add_clause([1,-5,4]);
s.add_clause([-1,5,3,4]);
s.add_clause([-3,-4]);
console.log(s.solve());
