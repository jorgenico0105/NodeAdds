const raylib = require('./hello.node');
//import raylib from './hello.node' assert { type: "node" };

console.log(raylib);
//raylib.testArgs(6, 7, "Hola");
raylib.initWindow(800, 900, "Hellp");
while (!raylib.windowShouldClose()) {
  raylib.beginDrawing();
  raylib.clearBackground(0, 0, 255);
  raylib.endDrawing();
}
