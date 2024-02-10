# FireBridge - Serial Monitor Application

<img src="https://github.com/Byte-White/FireBridge/assets/51212450/f422afad-f797-433f-9ffa-a19c77e53138" width=400 alt="logo">

FireBridge is a Serial Monitor Application powered by Magma, designed to facilitate real-time communication with devices through serial ports. Whether you're debugging, monitoring sensor data, or interfacing with hardware, FireBridge provides a streamlined interface for sending and receiving serial data.


## Screenshots: 

![image](https://github.com/Byte-White/FireBridge/assets/51212450/4016da80-e1dc-46cb-8fd2-d225bfb6aac8)

```c++
void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("Serial Setup.\n\n");
}

void loop() {
  delay(5000);
  Serial.println("a message after 5 seconds delay.");
  delay(2000);
  Serial.print("a message after 2 seconds delay");
  delay(250);
  Serial.println("...");
}
```