# Smart RFID-Based Inventory & Material Monitoring System

A smart inventory monitoring prototype developed during a **24-hour hackathon** by a **4-member team** to reduce manual stock checking and improve real-time visibility of products and materials.

The system combines embedded sensing, RFID identification, computer vision, cloud connectivity, and automated alerts to monitor inventory and support timely replenishment decisions.

## Problem

Manual inventory checking can be time-consuming and may lead to inaccurate stock information or delayed identification of low-stock conditions.

## Solution

The system automates product identification and inventory monitoring using multiple sensing approaches:

- RFID-based product identification
- Weight-based quantity measurement using a load cell and HX711
- Camera-based shelf monitoring using YOLOv8
- ESP32-based embedded control and data processing
- OLED display for local inventory status
- Firebase connectivity for cloud-based inventory data
- Email alerts for low-stock conditions
- MicroSD-based offline data storage concept
- API-based automated restocking concept

## System Workflow

```text
              Products / Shelf
                     |
        +------------+-------------+
        |            |             |
       RFID        Weight        Camera
        |            |             |
      RC522        HX711         YOLOv8
        |            |             |
        +------------+-------------+
                     |
              Inventory Logic
                     |
          +----------+----------+
          |                     |
      Normal Stock          Low Stock
          |                     |
     Update Status          Alert User
                                |
                    +-----------+-----------+
                    |           |           |
                  Email      Firebase    Restocking
                                           API
