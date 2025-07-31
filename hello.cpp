
#include <node.h>
#include <raylib.h>
#include <v8.h>

using std::printf;

void InitWindowAdapter(const v8::FunctionCallbackInfo<v8::Value> &args) {
  v8::Isolate *isolate = args.GetIsolate();
  std::printf("InitWindowAdapter called with %d arguments\n", args.Length());
  if (args.Length() > 0) {
    std::printf("Desde raylib\n");
    v8::String::Utf8Value title(isolate, args[0]->TypeOf(isolate));
    std::printf("Title: %s\n", *title);
    if (args[0]->IsNumber()) {
      std::printf("Argument 0 is a number\n");
      int w = args[0]
                  ->ToInt32(isolate->GetCurrentContext())
                  .ToLocalChecked()
                  ->Value();
      int h = args[1].As<v8::Number>()->Value();

      std::printf("Width: %d\n Height: %d\n", w, h);
    }
  }
  // printf("Creating window %s\n", *title);
  //  InitWindow(800, 600, "Hello World");
}

void Method(const v8::FunctionCallbackInfo<v8::Value> &args) {
  std::printf("Hello, World!\n");
}
void Method2(const v8::FunctionCallbackInfo<v8::Value> &args) {
  static int numero = 0;
  std::printf("Method2 called %d times\n", ++numero);
}
void testArtgs(const v8::FunctionCallbackInfo<v8::Value> &args) {
  v8::Isolate *isolate = args.GetIsolate();
  for (int i = 0; i < args.Length(); i++) {
    v8::String::Utf8Value type(isolate, args[i]);
    std::printf("%s\n", *type);
  }
}
void Initialize(v8::Local<v8::Object> exports) {
  NODE_SET_METHOD(exports, "hello", Method);
  NODE_SET_METHOD(exports, "method2", Method2);
  NODE_SET_METHOD(exports, "testArgs", testArtgs);
  NODE_SET_METHOD(exports, "initWindow", InitWindowAdapter);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize);
