  #include <hp_BH1750.h>

class Sensor: public hp_BH1750 {
  public:

    void connect() {
      begin(35);      
    }

    float read() {
      start();
      return getLux();
    }
};
