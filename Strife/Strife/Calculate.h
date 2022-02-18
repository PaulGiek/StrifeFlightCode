#ifndef Calculate_h
#define Calculate_h


class Calculate {
  public:
    double calcThrust(float VehicleMass,float Accel);
    float calcMin(float normalMinPos, float otherAxicsAngle, float otherMinPos, float otherMaxPos);
    float calcMax(float normalMinPos, float otherAxicsAngle, float otherMinPos, float otherMaxPos);
    
  private:
    const float g = 9.81;
  
    float thrust; 
    float vehicleMass;
    float accel;

    float velocityX;
    float velocityY;
    float velocityZ;

    float now;
    float oldTime;

    //Min-Max
    float m = 0.0;
    float t = 0.0;
    float conVal = 0.0;
};

#endif
