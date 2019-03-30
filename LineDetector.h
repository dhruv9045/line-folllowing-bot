#ifndef LINEDETECTOR_H
#define LINEDETECTOR_H

#define MAX_SENSOR 8

struct IRSensor {
  int pin,      // The pin to which the sensor is connected
      weight,   // The weight assigned to each pin
      val;
};

class LineDetector {
private:
  IRSensor sensor[MAX_SENSOR];
  int zeroSensor, onSensor;

public:
  LineDetector(int pins[]) {
    zeroSensor = 0;

    // Assigning pins to each sensor
    for(int i = 0; i < MAX_SENSOR; i++) {
      sensor[i].pin = pins[i];
      pinMode(sensor[i].pin, INPUT);
    }

    // Assigning weight to each sensor
    int even = !(MAX_SENSOR % 2); // Checking if total sensors are even or odd
    int value = even ? -(MAX_SENSOR/2 - 1) : -(MAX_SENSOR/2) ; //Weight which is to be assigned
    for(int i = 0; i < MAX_SENSOR; i++, value++) {
      if(even && i == MAX_SENSOR/2)
        // Additional condition for even sensors
        // Two sensors in middle should have weight = 0
        value--;
      sensor[i].weight = value; //Adding weight to each sensor
    }
  }

  int calcDeviation() {
    bool lim_l = false, lim_h = false,
      l_val, h_val;
    int err = 0;
    for (int l = MAX_SENSOR/2-1, h = MAX_SENSOR/2; l > -1 && h < MAX_SENSOR; l--, h++) {
      l_val = digitalRead(sensor[l].pin);
      h_val = digitalRead(sensor[h].pin);
      if (l_val == HIGH) lim_l = true;
      else if (lim_l == false)
        err += sensor[l].weight;
      
      if (h_val == HIGH) lim_h = true;
      else if (lim_h == false)
        err += sensor[h].weight;
    }
    /*int motorPins[] = {4, 5, 2, 3};
    MotorDriver motor(motorPins);
    motor.stop();
    delay(100);
    int err = 0;
    for(int i = 0; i < MAX_SENSOR; i++) {
      int temp = sensor[i].weight;
      sensor[i].val = digitalRead(sensor[i].pin);
      if(sensor[i].val == LOW) {
        // Current IR sensor is on the black strip
        sensor[i].weight = 0;
        zeroSensor++;
      }
      err += sensor[i].weight;
      sensor[i].weight = temp;
    }*/

    return err;
  }

  int isCrossSection() {
    /*
    Function to check if the bot is at a cross section using the weight of the sensors
    */
    if(zeroSensor == MAX_SENSOR) {
      // All sensors have zero weight
      zeroSensor = 0;
      return 1;
    }
    else {
      zeroSensor = 0;
      return 0;
    }
  }

  int is90Turn() {
    int is90 = 1;
    for(int i = 0; i < MAX_SENSOR/2; i++)
      if (sensor[i].val == 1) {
        is90 = 0;
        break;
      }
    if (!is90)
      for (int i = MAX_SENSOR/2; i < MAX_SENSOR; i++)
        if (sensor[i].val == 1) {
        is90 = 0;
        break;
      }
    return is90;
  }

  int is120Junction() {
  	int pattern[3][8] = {
  		{0, 0, 0, 1, 1, 0, 0, 0},
  		{1, 0, 1, 1, 0, 0, 0, 0},
  		{0, 0, 0, 0, 1, 1, 0, 1}
  	};
	for (int i = 0; i < 3; i++) {
		int matched = 1;
		for (int j = 0; j < 8; j++)
			if (pattern[i][j] != sensor[j].val) {
				matched = 0;
				break;
			}
		if (matched == 1) return 1;
	}
	return 0;
  }
};

#undef MAX_SENSOR

#endif
