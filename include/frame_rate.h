#ifndef FRAME_RATE
#define FRAME_RATE

class FrameRate {
  public:
    FrameRate();
    void stat();

  private:
    double last_time;
    int frames = 0;
};

#endif
