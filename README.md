<p align="center">
    <img src="https://github.com/Amrita-TIFAC-Cyber-Blockchain/.github/blob/main/profile/img/AVV_CYS_Logo.png" alt ="Amrita TIFAC" width="700" />
</p>

# 24CYS333 - Internet of Things

## IoT#18 - Smart Monitoring of LPG Utility Pipelines Using Sensor-Based Leakage Detection and Metering

![](https://img.shields.io/badge/Member-Ponvedica%20M%20S-gold) ![](https://img.shields.io/badge/Member-Soffia%20K%20N-gold) ![](https://img.shields.io/badge/Member-Vedhavarshini%20Vijayakumar-gold) <br/> 
![](https://img.shields.io/badge/SDG%207-Affordable%20and%20Clean%20Energy-darkgreen)
![](https://img.shields.io/badge/SDG%209-Industry%2C%20Innovation%20and%20Infrastructure-darkgreen)
![](https://img.shields.io/badge/SDG%2011-Sustainable%20Cities%20and%20Communities-darkgreen) <br/>
![](https://img.shields.io/badge/Reviewed--brown) <br/>
![](https://img.shields.io/badge/PRISM_Expo-12_Mar_2026_14:21_to_14:33-gold) <br/> 
![](https://img.shields.io/badge/NIR-IR2026--1009659-purple) 

------

### Problem Statement
![](https://img.shields.io/badge/Clarity-Clear-green) 
![](https://img.shields.io/badge/Problem_Defined-Clear-green)<br>
![](https://img.shields.io/badge/Existing_Solutions-Defined-green)
![](https://img.shields.io/badge/Gaps_in_Existing_Solutions-Addressed-green) <br/> 
![](https://img.shields.io/badge/Proposed_Solutions-Clear-green) <br/> 

In metropolitan cities of India, LPG gas is increasingly supplied to households through direct utility pipeline connections laid across underground tunnels and corridors. Monitoring these pipelines is challenging, and undetected gas leaks can lead to serious hazards such as fires, explosions, and health risks. Existing gas safety systems are mostly limited to local alarms at the consumer end, which may go unnoticed when users are away and do not provide information about the exact location or severity of leaks occurring within the utility pipelines.

This project proposes a Smart Gas Leakage Detection and Emergency Control System with Smart Metering for urban LPG pipeline networks. The system includes a smart gas meter for consumption monitoring and a mobile device capable of traveling inside utility pipelines to detect gas leakage, measure leak intensity, and identify the exact location of the fault. The solution aims to improve safety, enable early leak detection, and support efficient monitoring of LPG utility pipelines in urban environments.
   
-----
## Hardware Requirements

### Common Components

| ✅ Acquired | Components | Purpose |
|-------------|------------|---------|
|       ✅      | **Breadboard** | Circuit prototyping  |
|             | **Jumper Wires & Foam Board** | Robot connections and Support|
|             | **Connecting Wires** | Circuit connections|

---

| ✅ Acquired | Components | Purpose |
|--------------|------------|----------|
|              | **NodeMCU (ESP8266)** | Used to control the robot car using its wifi |
|     ✅       | **NEO-6M GPS Module** | Identifies exact location of gas leaks within the pipeline network |
|              | **ESP32** | Used to connect GPS module & MQ-6 sensor and to send the data to web page using wifi |
|              | **MQ-6 Gas Sensor** | Primary sensor for LPG gas leakage detection inside pipelines | 
|              | **LCD Display** | To show the gas leakage level and GPS status|
|              | **DC Gear Motors (4x)** | Provides movement inside underground utility pipelines |
|              | **L293D Motor Driver** | Alternative compact motor driver for controlling DC motors |
|              | **Li-Ion Rechargeable Batteries (18650, 3.7V, 2000–3000mAh)** | Energy storage for continuous underground operation |
|              | **Battery Holder (18650 x2 / x3)** | Secure mounting and series/parallel battery configuration |
|              | **Robot Wheels (4x)** | Enables stable navigation inside confined pipeline tunnels |
|              | **Arduino (Uno)** | To Process hall effect sensor code (Smart gas metering) |
|              | **Hall Effect Sensor** | Detects magnetic field (Smart gas metering) |

---- 



## Software Requirements

| ✅ Available | Components | Purpose |
|-------------|------------|---------|
|             | **Arduino IDE** | Programming environment for ESP32/Arduino development |
|             | **Python 3.x** | Backend server development and data processing |
|             | **Blynk IoT Platform** | Mobile app interface for real-time monitoring and alerts |
|             | **Google Maps API** | Location mapping and visualization of leak points |
|             | **Git/GitHub** | Version control and collaboration |
|             | **VS Code / PyCharm** | Integrated development environments |
|             | **HTML / CSS** | Used to structure and style the web dashboard interface|
|             | **Flask**      | A lightweight Python web framework used to build the web server and handle API routes |
|             | **JSON**       | Used as the data format to send sensor data (gas value, GPS location) to the server |
|             | **REST API (POST endpoint)** | Allows external devices (like IoT sensors) to send data to the server |
|             | **Web Browser (Chrome/Edge etc.)** | Used by users to view the dashboard interface | 

------ 
## [Literature Survey](./R1/README.md)  

------
## Proposed Solution

### Problem Statement Recap
In metropolitan cities of India, LPG gas is increasingly supplied to households through direct utility pipeline connections laid across underground tunnels and corridors. Monitoring these pipelines is challenging, and undetected gas leaks can lead to serious hazards such as fires, explosions, and health risks. Existing gas safety systems are mostly limited to local alarms at the consumer end, which may go unnoticed when users are away and do not provide information about the exact location or severity of leaks occurring within the utility pipelines.

### Our Solution
**Smart Gas Leakage Detection and Emergency Control System with Smart Metering** that includes:

1. **Smart Gas Meters** at consumer endpoints for consumption monitoring
   - A Hall Effect sensor is used to detect the magnetic field from a magnet attached to a gas stove knob.
   - When the knob is turned ON, the sensor detects the magnetic field generated by the magnet.
   - The system then starts measuring the duration for which the stove remains active.
   - This active usage time is recorded by the system.
   - Based on this duration, the system estimates gas consumption and calculates usage-based billing.
2. **Mobile Pipeline Inspection Device** - a battery-powered robot capable of traveling inside utility pipelines to:
   - Detect gas leakage using MQ-6 sensors
   - Measure leak intensity and severity
   - Identify exact GPS location of faults
4. **IoT-Based Monitoring Platform** with real-time alerts and data analytics
5. **Emergency Control Systems** with automated responses

---
## Architecture Diagram
<img width="1105" height="810" alt="image" src="https://github.com/user-attachments/assets/0eec0106-3bbd-4e04-ad59-92559f60cd25" />


----

## Usecases

#### Use Case 1: Gas Leak Detection in Pipeline
The system uses a mobile inspection unit that travels through underground pipelines to monitor gas levels. An MQ-6 sensor is used to detect the presence of LPG gas continuously. When a leakage occurs, the sensor identifies an abnormal increase in gas concentration. The system then records the exact location using a GPS module and sends this information for monitoring. This helps in identifying leaks at an early stage and reduces the chances of accidents.


#### Use Case 2: Consumer Gas Usage Monitoring
At the consumer end, a smart gas metering system is implemented using a Hall Effect sensor. A magnet attached to the stove knob helps in detecting when the stove is turned ON or OFF. Based on this, the system records the duration of usage. The total gas consumption is estimated using this usage time, providing a simple and cost-effective alternative to traditional flow-based metering systems.


#### Use Case 3:  Real-Time Alert Generation
Whenever a gas leak is detected in the pipeline, the system generates an alert immediately. The alert includes information about the presence of leakage and its severity. This notification can be viewed through the monitoring platform, allowing quick action to be taken. This feature helps in preventing dangerous situations by ensuring timely response.


#### Use Case 4: Pipeline Inspection Using Mobile Unit
The mobile inspection device is designed to move inside pipelines and perform regular checks. It continuously collects data from sensors while traveling through the pipeline, enabling monitoring over long distances without manual intervention. The device operates on battery power, allowing it to function independently inside the pipeline.

---
### Deliverables

- Smart gas meter prototype with real time LPG consumption monitoring
- Working pipeline inspection robot with gas sensor, LCD and GPS module
- IoT monitoring dashboard with live data visualization

------

### Mapping the Project to Relevant Sustainable Development Goals (SDGs)
| SDG | Alignment |
|-----|-----------|
| <img src="https://github.com/user-attachments/assets/d7b14d63-4d05-440e-b072-a6d3a24fce1c" width="191" height="184"> <br> **SDG 7: Affordable and Clean Energy** | This project supports efficient energy utilization by integrating smart gas metering and real-time leakage detection in utility pipelines. Continuous monitoring helps reduce gas wastage, prevents energy loss due to undetected leaks, and promotes responsible consumption of LPG resources, contributing to sustainable and cleaner energy management. |
| <img src="https://github.com/user-attachments/assets/2ec8a467-d845-43df-a4ed-fb2a16239d50" width="194" height="188"> <br> **SDG 9: Industry, Innovation and Infrastructure** | The proposed system enhances modern urban infrastructure by introducing an IoT-based monitoring solution for utility pipelines. By combining smart sensing, wireless communication, and real-time data analysis, the project improves safety, reliability, and efficiency of industrial gas distribution networks, aligning with the goal of building resilient and innovative infrastructure. |
| <img src="https://github.com/user-attachments/assets/15356780-6ed5-482f-a009-6983c28c2e37" width="191" height="189"> <br> **SDG 11: Sustainable Cities and Communities** | Gas leakage detection and monitoring in underground utility pipelines contribute to safer urban environments by reducing risks of explosions, environmental hazards, and public safety incidents. The system supports the development of smart-city solutions that enhance community safety through proactive monitoring and early warning mechanisms. |

---

### References


| S.No | Research Paper Title | 
|------|----------------------|
| 1 | [Industrial IoT based Hazardous Gas Leakage Detection and Notification](https://www.researchgate.net/publication/390991290_Industrial_IoT_based_Hazardous_Gas_Leakage_Detection_and_Notification) | 
| 2 | [Real-time Detection of Urban Gas Pipeline Leakage Based on Machine Learning of IoT Time-Series Data](https://www.sciencedirect.com/science/article/abs/pii/S0263224124018220)| 
| 3 | [IoT-Based Solar-Powered Gas Pipeline Leakage Detection Robot](https://www.e3s-conferences.org/articles/e3sconf/pdf/2024/94/e3sconf_icpgres2024_05003.pdf)| 
| 4 |  [Design of a Wireless Cyber-Physical System for Gas Leak Detection With LoRa](https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=10993435) | 
| 5 | [Development of Novel Fuel Efficient Domestic Cooking Burner for PNG (Piped Natural Gas) and Commercialization in India](https://www.pngrb.gov.in/pdf/press-note/CSIR_IIP_20240627.pdf) | 















































