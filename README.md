[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Q-Urnqos)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-2e0aaae1b6195c2367325f4f02e2d04e9abb55f0b24a779b69b11b9e10269abc.svg)](https://classroom.github.com/online_ide?assignment_repo_id=16511807&assignment_repo_type=AssignmentRepo)

# Train Monitoring System

## Overview
The Train Monitoring System is an embedded application for an International Airport that utilizes a finite state machine (FSM) to manage train operations and control indicator lights.

## Features
- State Management
- LED Control with PWM
- Emergency Button Handling
- UART for Debugging

## System Architecture
- **Microcontroller**: STM32 Nucleo-64
- **LEDs**: User LED (ULED) and External LED (ELED)
- **User Input**: B1 USER button
- **Communication**: UART
## Know Bugs
- Timing during emergency release when doing transition is appoximate

## Getting Started

### Prerequisites
- STM32 Nucleo-64 board
- STM32CubeIDE
- ST-Link programmer

### Installation
1. Clone the repository:
   ```bash
   git clone git@github.com:ECEN5813/assignment4-airporttrains-nidhi142.git

2. Open the project in STM32CubeIDE.
Build the project.
Usage
- Upload the firmware to the STM32 microcontroller using the ST-Link.
- Connect to the serial output to monitor debugging information.
- The system starts in STATE_TERMINAL. Press the emergency button to switch to STATE_EMERGENCY.
## Testing
- Test each state transition and LED operation.
- Check the serial output for debug messages.
- Refer FSM pdf for more details

## Contributing
Contributions are welcome! Please fork the repository, create a branch, and submit a pull request.


## Acknowledgements
Thanks to the STM32 community for their support and resources.

