# Smart Inventory & Shelf Management System

## About Me

**Name:** S VIDISHA  
**College:** Sahyadri College of Engineering and Management  
**Branch:** Electronics and Communication Engineering

### Linked in
[![linkedin](https://img.shields.io/badge/linkedin-0A66C2?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/s-vidisha-4b1144293?utm_source=share&utm_campaign=share_via&utm_content=profile&utm_medium=android_app)
---

## Project Overview

The **Smart Inventory & Shelf Management System** is a hackathon prototype developed to explore automated, real-time inventory monitoring using embedded systems and IoT technologies.

The system uses an **ESP32** as the primary embedded controller. An **MFRC522 RFID reader** identifies tagged products, while the system maintains item-wise inventory counts and displays the current stock status on an **OLED display**. The ESP32 connects to Wi-Fi and can automatically send an **email notification when the stock level of a tracked item falls below a predefined threshold**.

The overall project concept was designed to be extended with **weight-based quantity verification, centralized processing using Raspberry Pi, cloud-based inventory monitoring, and camera-based product identification**.

---

## Problem Statement

Traditional inventory monitoring often relies on manual stock counting, which can result in delayed updates, inaccurate stock information, and difficulty identifying low-stock items.

The objective of this project was to develop a prototype for an **automated shelf-monitoring system** that can identify products, maintain inventory information, provide local status feedback, and generate alerts when stock levels become low.

---

## Features

### Implemented in the Prototype

- RFID-based product identification using MFRC522
- ESP32-based inventory processing
- Individual product identification using RFID UID
- Automatic inventory count update
- OLED-based local inventory display
- Wi-Fi connectivity
- Configurable low-stock threshold
- Automatic email notification for low-stock conditions
- Serial monitoring for debugging and system status

### Explored / Proposed Extensions

- Weight-based quantity verification using load cells and HX711
- Centralized inventory processing using Raspberry Pi
- Cloud-based inventory database
- Web-based inventory dashboard
- Camera-based product detection using computer vision
- Automated shelf-level product tracking

> **Note:** The above extensions represent the broader hackathon system concept. They were not all integrated into the final ESP32 prototype shown in this repository.

---

## System Workflow

```text
             ┌──────────────────┐
             │   RFID Product   │
             │      Tag         │
             └────────┬─────────┘
                      │
                      ▼
             ┌──────────────────┐
             │   MFRC522 RFID   │
             │      Reader      │
             └────────┬─────────┘
                      │
                      ▼
             ┌──────────────────┐
             │      ESP32       │
             │ Inventory Logic  │
             └───────┬───┬──────┘
                     │   │
             ┌───────┘   └──────────────┐
             ▼                          ▼
      ┌──────────────┐           ┌──────────────┐
      │ OLED Display │           │ Wi-Fi / SMTP │
      │ Stock Status │           │ Email Alert  │
      └──────────────┘           └──────────────┘
