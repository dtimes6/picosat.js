#ifndef PICOSAT_OBJECT_HH
#define PICOSAT_OBJECT_HH

#include <node.h>

extern "C" {
#include "picosat.h"
}

class PicoSATObj : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> target);

 private:
  PicoSATObj();
  ~PicoSATObj();

  static v8::Handle<v8::Value> New(const v8::Arguments& args);
  static v8::Handle<v8::Value> AddClause(const v8::Arguments& args);
  static v8::Handle<v8::Value> Solve(const v8::Arguments& args);

  PicoSAT* sat;
};

#endif