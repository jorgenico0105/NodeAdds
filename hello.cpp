
#include <node.h>
#include <raylib.h>
#include <string>
#include <v8.h>

using std::printf;

void InitWindowAdapter(const v8::FunctionCallbackInfo<v8::Value> &args) {
  v8::Isolate *isolate = args.GetIsolate();
  auto context = isolate->GetCurrentContext();
  int w = 0;
  int h = 0;
  std::string title = "";
  // string title = "Hello World";
  //  std::printf("InitWindowAdapter called with %d arguments\n",
  //  args.Length());
  if (args.Length() > 0) {
    // v8::String::Utf8 ee Value title(isolate, args[0]->TypeOf(isolate));
    // std::printf("Title: %s\n", *title);
    if (args[0]->IsNumber() && args[1]->IsNumber()) {
      // std::printf("Argument 0 is a number\n");
      //  Two ways to get the width and height
      w = args[0]->Int32Value(isolate->GetCurrentContext()).FromJust();
      h = args[1].As<v8::Number>()->Value();
    }
    if (args[2]->IsString()) {
      v8::String::Utf8Value titulo(isolate, args[2]);
      title = *titulo;
      std::printf("Title: %s\n", title.c_str());
    }
    // std::printf("Width: %d\n Height: %d\n", w, h);
  }
  InitWindow(w, h, title.c_str());
}
void WindowShouldCloseAdapter(const v8::FunctionCallbackInfo<v8::Value> &args) {
  v8::Isolate *isolate = args.GetIsolate();
  auto context = isolate->GetCurrentContext();
  args.GetReturnValue().Set(v8::Boolean::New(isolate, WindowShouldClose()));
}
void BeginDrawingAdapter(const v8::FunctionCallbackInfo<v8::Value> &args) {
  v8::Isolate *isolate = args.GetIsolate();
  BeginDrawing();
}
void EndDrawingAdapter(const v8::FunctionCallbackInfo<v8::Value> &args) {
  v8::Isolate *isolate = args.GetIsolate();
  EndDrawing();
}
void ClearBackgroundAdapter(const v8::FunctionCallbackInfo<v8::Value> &args) {
  v8::Isolate *isolate = args.GetIsolate();
  unsigned char r =
      args[0]->Int32Value(isolate->GetCurrentContext()).FromJust();
  unsigned char g =
      args[1]->Int32Value(isolate->GetCurrentContext()).FromJust();
  unsigned char b =
      args[2]->Int32Value(isolate->GetCurrentContext()).FromJust();
  if (args.Length() > 3 && args[3]->IsInt32()) {
    unsigned char a =
        args[3]->Int32Value(isolate->GetCurrentContext()).FromJust();
    ClearBackground((Color){r, g, b, a});
  } else {
    ClearBackground((Color){r, g, b, 255});
  }
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
  NODE_SET_METHOD(exports, "windowShouldClose", WindowShouldCloseAdapter);
  NODE_SET_METHOD(exports, "beginDrawing", BeginDrawingAdapter);
  NODE_SET_METHOD(exports, "endDrawing", EndDrawingAdapter);
  NODE_SET_METHOD(exports, "clearBackground", ClearBackgroundAdapter);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize);
