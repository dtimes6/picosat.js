#include <node.h>
#include "picosat_object.hh"

using namespace v8;

PicoSATObj::PicoSATObj() : sat(picosat_init()) {};
PicoSATObj::~PicoSATObj() { picosat_reset(sat); };

void PicoSATObj::Init(Handle<Object> target) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("PicoSAT"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  // Prototype
  tpl->PrototypeTemplate()->Set(String::NewSymbol("add_clause"),
      FunctionTemplate::New(AddClause)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("solve"),
      FunctionTemplate::New(Solve)->GetFunction());

  Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
  target->Set(String::NewSymbol("PicoSAT"), constructor);
}

Handle<Value> PicoSATObj::New(const Arguments& args) {
  HandleScope scope;

  PicoSATObj* obj = new PicoSATObj();
  obj->Wrap(args.This());
  return args.This();
}

Handle<Value> PicoSATObj::AddClause(const Arguments& args) {
  HandleScope scope;
  PicoSATObj* obj = ObjectWrap::Unwrap<PicoSATObj>(args.This());

  if (args[0]->IsArray()) {
	Handle<Array> clause = Handle<Array>::Cast(args[0]);
	for (uint32_t i = 0; i < clause->Length(); ++i) {
	  Handle<Value> lit = clause->Get(i);
	  if (lit->IsInt32()) {
		int v = lit->Int32Value();
		if (v == 0) {
			ThrowException(Exception::TypeError(String::New("'0' cannot be used as lit!")));
			return scope.Close(Undefined());
		} else {
		  picosat_add(obj->sat, v);
		}
	  } else {
		ThrowException(Exception::TypeError(String::New("Lit must be none zero integer number.")));
		return scope.Close(Undefined());
	  }
	}
	picosat_add(obj->sat, 0);
	return args.This();
  }
  ThrowException(Exception::TypeError(String::New("An Array of lits is required!")));
  return scope.Close(Undefined());
}

Handle<Value> PicoSATObj::Solve(const Arguments& args) {
  HandleScope scope;
  PicoSATObj* obj = ObjectWrap::Unwrap<PicoSATObj>(args.This());
  int res = picosat_sat(obj->sat, -1);
  switch (res) {
  case PICOSAT_SATISFIABLE: {
	  int max_idx = picosat_variables(obj->sat);
	  Handle<Array> r = Array::New(max_idx);
	  for (int i = 1; i <= max_idx; ++i) {
		int v = picosat_deref(obj->sat, i) * i;
		r->Set(i-1, Integer::New(v));
	  }
      return scope.Close(r);
    }
  case PICOSAT_UNSATISFIABLE:
	return scope.Close(String::New("unsat"));
  case PICOSAT_UNKNOWN:
	return scope.Close(String::New("unknown"));
  }
  return scope.Close(Undefined());
}
