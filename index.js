const raylib = require('./hello.node');
//import raylib from './hello.node' assert { type: "node" };
console.log(raylib);
raylib.testArgs(6, 7, "Hola");
raylib.initWindow(8, 9);
