Grove_Drivers_for_mbed
==========================

The full name of "suli" is "seeed unified library interface", the latest version is 2.0. It's a cross-platform middle layer between Grove libraries and platform API. If a Grove driver was wrote based on suli2, it's very easy to port it to any platform suli2 supports.

Traditionally, Grove drivers were code on specific platform, such as Arduino, we share them to other people, it's wonderful thing! But in recent years, many new platforms appear, such as mbed. Now, I would like to port libraries from Arduino to mbed, Oh my god, too much workload for us, we have 180+ Groves!

So we thought of a way to solve this problem and considering port all Grove drivers to mainstream platforms in future, such as LaunchPad, RasPi and so on. Now the suli2 support Arduino and mbed.

Let us understand it's structure first: In a general way, user's project may include many layers like this:

![](http://www.seeedstudio.com/wiki/images/c/c6/Normal_Arduino_Platform.png)

or this:

![](http://www.seeedstudio.com/wiki/images/8/8e/Normal_mbed_Platform.png)

If we write each driver on all platform, it will take a few times as long to do this, and mistakes may generate when porting. So a good method is to insert a middle layer, when porting to new platform, we just need to modify this layer. So the new structure is:

![](http://www.seeedstudio.com/wiki/images/f/f6/Suli2_Platoform.png)

In the new structure, we abstracted the lowest API of the Grove driver to a new layer. and we can modify the macro in suli2.h to define which platform we choose, it's so easy!

The middle layer, suli2 includes two files suli2.cpp and suli2.h, while each Grove driver has four files: grove_example.cpp, grove_example.h, grove_example_class_cpp and grove_example_class.h.

![](http://www.seeedstudio.com/wiki/images/9/9d/Suli2_structure.png)

Grove Drivers has been ported:
------------------------------

####I2C device
* grove_acceleromete ---- MMA7660FC
* grove_gyroscope ---- ITG-3200
* grove_compass ---- HMC5883L
* grove_barometer ---- BMP180
* grove_digital_light ---- TSL2561
* grove_heartrate

####UART device
* grove_fingerprint
* grove_esp8266

####Digital device
* grove_temp_hum ---- DHT11

####Analog device
* grove_moisture


----
This software is written by Jacky Zhang (![](http://www.seeedstudio.com/wiki/images/8/8f/Email_addr_of_jacky_zhang.png)) from [Seeed Technology Inc.](http://www.seeed.cc) and is licensed under [The MIT License](http://opensource.org/licenses/mit-license.php). Check License.txt/LICENSE for the details of MIT license.<br>



