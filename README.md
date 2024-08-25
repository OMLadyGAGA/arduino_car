# Arduino Car (CPSS)

This project is to build a vehicle using an arduino to follow people infront of him.


## Step1: Set up you vehicle

你們要確定你們車的向前， 向後， 轉左，轉右是正常的。 這裏有提供一個檔案 `move.ino`，他做的事是走某個方向一秒，然後停止2秒再走某個方向一秒，重複無限次。

這程式只是爲了讓你們測試，當軟體命令汽車向前（就是上次叫你們做的所以你們能直接把調整好的 copy 去這裏）他是不是可以向前。當軟體命令汽車向後，他是不是可以向后等等。。。

> 在程式裏面 `//` 的意思是 comment 也就是這個是給人看的，電腦讀到這個會當他不存在。

所以下面的程式只有 `moveForward()` 前面沒有 `//`， 意思是往前一秒停止倆秒。那要測試往後的時候就是把 `moveForward();` 前面加上 `//` 把 `moveBackward();` 前面的 `//` 拿掉。 

**那你們現在要做的事是弄完這四個**

```ino
void loop() {
  Serial.println("Moving forward");
  moveForward();        // Move forward
  // moveBackward();       // Move backward
  // turnLeft();           // Turn left
  // turnRight();          // Turn Right
  
  delay(1000);          // Wait for 1 seconds

  Serial.println("Stopping the car");
  stopCar();            // Stop the car
  delay(2000);          // Wait for 2 seconds
}
```

調整裏面的 `HIGH` 和 `LOW`。馬達轉動(輪子)的方向取決於 `in1` 是 `HIGH` pulse，`in2` 是 `LOW` 就是某個方向。`in1` 是 `LOW`，`in2` 是 `HIGH` 就是某方向。

### 1. 向前
```ino
void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
  digitalWrite(in7, HIGH);
  digitalWrite(in8, LOW);
}
```

### 2. 向後
```ino
void moveBackward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
  digitalWrite(in7, HIGH);
  digitalWrite(in8, LOW);
}
```

### 3. 轉左
```ino
void turnLeft() {
  // Adjust the motor outputs to turn left
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
  digitalWrite(in6, HIGH);
  digitalWrite(in7, HIGH);
  digitalWrite(in8, LOW);
}
```

### 4. 轉右
```ino
void turnRight() {
  // Adjust the motor outputs to turn right
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
  digitalWrite(in7, LOW);
  digitalWrite(in8, HIGH);
}
```


## Step2: Implement infrared


## Step3: Fine Tuning


