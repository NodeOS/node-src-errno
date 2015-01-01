#include <errno.h>

// http://linux.die.net/man/3/strerror
#include <string.h>
#include <v8.h>
#include <node.h>
#include <nan.h>

using namespace v8;
using namespace node;


NAN_METHOD(GetLastErrorNumber) {
  NanEscapableScope();
  NanReturnValue(NanEscapeScope(NanNew<Integer>(errno)));
}

NAN_METHOD(GetErrorString) {
  NanEscapableScope();
  int err = Local<Number>::Cast(args[0])->Value();
  char *errmsg = strerror(err);
  NanReturnValue(NanEscapeScope(NanNew<String>(errmsg)));
}

void init(Handle<Object> exports) {
  exports->Set(NanNew<String>("getLastErrorNumber"),
    NanNew<FunctionTemplate>(GetLastErrorNumber)->GetFunction());
  exports->Set(NanNew<String>("getErrorString"),
    NanNew<FunctionTemplate>(GetErrorString)->GetFunction());
}

NODE_MODULE(binding, init)
