/*
 *  Created on: 2018年8月2日
 */

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>

#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>
#include <signal.h>
#include <poll.h>
#include <fcntl.h>
#include <inttypes.h>
#include <fnmatch.h>
#include <getopt.h>
#include <assert.h>

#include <sys/wait.h>
#include <sys/epoll.h>
#include <sys/stat.h>
#include <sys/timerfd.h>
#include <sys/ioctl.h>

#include <linux/input.h>
//#include <libinput.h>
//#include <libudev.h>
//#include <libevdev-1.0/libevdev/libevdev.h>

#include <GL/glut.h>

////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <iostream>
#include <fstream>
#include <memory>
#include <cstddef>
#include <cmath>
#include <exception>
#include <stdexcept>
#include <typeinfo>

#include <string>
#include <utility>
#include <valarray>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <iterator>

#ifndef LOG
#define LOG(fmt, args...)			do{	\
	printf("tuxRacer--%-40s--%5d--%-10s-- " fmt "\n", __FUNCTION__, __LINE__, __FILE__, ##args);	\
	}while(0)
#endif

#define SMALL_FLOAT_NUMBER 0.01
#define LARGE_FLOAT_NUMBER (float)(RAND_MAX)

