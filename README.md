# test_glog
This repository contains some basic examples of using Google Logging Library(glog).

## Install glog
Clone glog from [glog GitHub repository](https://github.com/google/glog) and follow the instructions.
Some may find it more convenient to use CMake since the above link uses Automake.
One possible choice is [glog_catkin](https://github.com/ethz-asl/glog_catkin).
It can be used as a plain CMake project as well as a catkin package despite of its name.

Refer to the [CMakeLists.txt](https://github.com/zhangzichao/test_glog/blob/master/CMakeLists.txt) in this repository about how to use glog in your project.

## Important flags
The behavior of glog is affected by many flags. Some important ones are
- `minloglevel`(default: 2, i.e. ERROR) controls `LOG()`. `LOG()` whose level is __greater than or equal to__ this flag will be logged.
- `v`(default: 0) controsl `VLOG()`. `VLOG()` whose level is __smaller than or equal to__ this flag will be logged.
- `logtostderr`(default: 0). You can set this flag to write log to `stderr` __instead of__ files.
- `alsologtostderr`(default: 0). Set this flag if you want to log to `stderr` as well as to files.
- `logdir`(default: ""). When set, this flag gives the directory that your log files will go into.
- `colorlogtostderr`(default: 0). Set this flag if you like some colors.

## How to add flags
The flags can be add and set via command line or in your code.
In command line, if you want to log to `stderr` and only log verbose level below or euqal to 3, you can do
```
GLOG_logtostderr=1 GLOG_v=3 ./yourapplication
```

## Where're my log files
If you don't set the `logdir` flag, the log files go into `/tmp` directory.
There may be several files corresponding to different severity levels.
Note that `VLOG()` actually belongs severity level `INFO`.

## Reference
[How To Use GLOG](https://google-glog.googlecode.com/svn/trunk/doc/glog.html)
