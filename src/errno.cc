#include <errno.h>

// http://linux.die.net/man/3/strerror
#include <string.h>
#include <v8.h>
#include <node.h>
#include <nan.h>

using namespace v8;
using namespace node;


NAN_METHOD(GetLastErrorNumber) {
  Nan::EscapableHandleScope scope;
  info.GetReturnValue().Set(scope.Escape(Nan::New<Integer>(errno)));
}

NAN_METHOD(GetErrorString) {
  Nan::EscapableHandleScope scope;
  int err = Local<Number>::Cast(info[0])->Value();
  char *errmsg = strerror(err);
  info.GetReturnValue().Set(scope.Escape(Nan::New<String>(errmsg).ToLocalChecked()));
}

void init(Handle<Object> exports) {
  exports->Set(Nan::New<String>("getLastErrorNumber").ToLocalChecked(),
    Nan::New<FunctionTemplate>(GetLastErrorNumber)->GetFunction());
  exports->Set(Nan::New<String>("getErrorString").ToLocalChecked(),
    Nan::New<FunctionTemplate>(GetErrorString)->GetFunction());
}

NODE_MODULE(binding, init)
