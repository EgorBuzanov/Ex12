// Copyright 2021 Egor Buzanov

#include "TimedDoor.h"

void DoorTimerAdapter::Timeout() { door.DoorTimeOut(); }

TimedDoor::TimedDoor(int _iTimeout) {
  iTimeout = _iTimeout;
  opened = false;
  adapter = new DoorTimerAdapter(*this);
}

bool TimedDoor::isDoorOpened() { return opened; }

void TimedDoor::unlock() {
  opened = true;
  Timer timer;
  timer.tregister(iTimeout, adapter);
}

void TimedDoor::lock() { opened = false; }

void TimedDoor::DoorTimeOut() { throw std::string("close the door!"); }

void TimedDoor::throwState() {
  if (opened) {
    throw std::string("the door is opened!");
  } else {
    throw std::string("the door is closed!");
  }
}

void Timer::sleep(int _time) {
  time_t start = time(nullptr);
  time_t finish = start;
  while (finish - start < _time) {
    finish = time(nullptr);
  }
}

void Timer::tregister(int _time, TimerClient* _timer_client) {
  sleep(_time);
  _timer_client->Timeout();
}
