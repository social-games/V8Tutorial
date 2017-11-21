V8 Tutorial is a series of project samples to get started with embedding V8 in android.

This project shows the most basic project structure of a V8 enabled android application.
Tutorial series will contain more advanced stuff like adding `requestAnimationFrame`, making a webgl binding, or plugin in developer tools `inspector` support.

## How to run

Before running the project, you must get any compiled V8 like the ones found (https://github.com/social-games/CompiledV8)[here].
Then expand it in the project's `jni` folder. The folder structure must look something like:

```
jni
 |
 +- Android.mk
 +- Application.mk
 +- arm64-v8a
 |     |
 |     + libv8_base.a
 |     + ...
 |
 + armeabi-v7a
 |     |
 |     + libv8_base.a
 |     + ...
 |
 + include
 + main.cpp
 + main.h
 + v8_include_src
```

## Project contents

This project is intended for begginners, to get a grasp on Android project structure and configuration, and how to initialize V8.
This example does not interact with javascript itself, it just creates the application and initializes V8 at a platform level.

It uses compiled default snapshots which are linked along with the application.

See how the file Android.mk references v8 library files based on the currently selected architecture.
These architectures are defined in the file app/build.gradle as two product flavours using different abi filters.

`If you know how javascript works, you already know a lot about v8.`