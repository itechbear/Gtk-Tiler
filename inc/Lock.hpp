#ifndef _LOCK_HPP_
#define _LOCK_HPP_

#include <sys/file.h>
#include <unistd.h>

#include <cassert>
#include <iostream>

class Lock {
 private:
  int fid;

 public:
  Lock() {
    int fid = open("/tmp/.gtk-tiler.lock", O_CREAT | O_RDWR, 0666);
    assert(fid != -1);

    int lock = flock(fid, LOCK_EX | LOCK_NB);
    assert(lock == 0);

    std::cout << "Started!" << std::endl;
  };

  ~Lock() {
    close(fid);
  }
};

#endif