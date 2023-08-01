//Codigo na esp

#include <ros.h>
#include <std_msgs/Int32.h>

ros::NodeHandle nh;

int pwmChannel= 0;
int pwmPin = 34;
int frequence = 1000; // 1KHz
int resolution = 8;

void vcc (const std_msgs::Int32 &PwmReceive){
  int valorPwm = PwmReceive.data;
  ledcAttachPin(pwmPin, pwmChannel);
  ledcWrite(pwmChannel, valorPwm);
  
}

ros::Subscriber<std_msgs::Int32> sub("PwmReceive", &vcc);

void setup() {
  Serial.begin(9600);
  nh.getHardware()->setBaud(9600);
  sleep(1);

  ledcSetup(pwmChannel, frequence, resolution);
  
  nh.initNode();
  nh.subscribe(sub);

}

void loop() {
  nh.spinOnce();
  delay(1);
}
