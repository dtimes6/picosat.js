var sat = require('./build/Release/picosat.node');
var s = new sat.PicoSAT();
s.add_clause([1,-5,4]);
s.add_clause([-1,5,3,4]);
s.add_clause([-3,-4]);

var res;
do {
  if (res) {
      console.log(res);
      var n = [];
      for(var i in res) {
          n.push(-res[i]);
      }
      s.add_clause(n);
  }
  res = s.solve();
} while(res instanceof Array);
