# Rotary table motor controller firmware
Repo contains a firmware for a *STM8L101K3T* microcontroller on rotary table motor controler's PCB. Firmware is written in C using a periperial library from IAR Embedded Workbench for STM8.
Motor controller driving a stepper motor by an A5977GLPTR integrated circuit. Commands for motor controller are sent via dedicated API (described in **repo**) that used RS485 as physical layer.
