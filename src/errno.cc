#include <errno.h>

// http://linux.die.net/man/3/strerror
#include <string.h>
#include <v8.h>
#include <node.h>

using namespace v8;
using namespace node;

namespace NodeOS
{
  
  static Handle<Value> GetLastErrorNumber(const Arguments& args){
    HandleScope scope;
    return scope.Close(Integer::New(errno));
  }
  
  static Handle<Value> GetErrorString(const Arguments& args){
    HandleScope scope;
    int err = Local<Number>::Cast(args[0])->Value();
    char *errmsg = strerror(err);
    return scope.Close(String::New(errmsg));
  }
  
  static void init(Handle<Object> target) {
    
    // handle errors
    target->Set(String::NewSymbol("getLastErrorNumber"),
      FunctionTemplate::New(GetLastErrorNumber)->GetFunction());
    target->Set(String::NewSymbol("getErrorString"),
      FunctionTemplate::New(GetErrorString)->GetFunction());
    
  }
}

NODE_MODULE(binding, NodeOS::init)
