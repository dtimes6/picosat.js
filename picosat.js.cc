#include <node.h>
#include "picosat_object.hh"

using namespace v8;

void InitAll(Handle<Object> exports) {
    PicoSATObj::Init(exports);
}

NODE_MODULE(picosat, InitAll)