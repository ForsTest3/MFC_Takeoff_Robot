# MFC Take-Off Robot - Team ACI

A WiFi-controlled robot built for the Met Firsts Create Take-Off challenge.


## Competition Objective
Designed to maximize point score in head-to-head matches by efficiently collecting blocks of varying sizes and shapes while maintaining maneuverability throughout the arena.

## Design Overview:

#### Control System/Interface:
- An ESP32 microcontroller
- L298N H-bridge motor driver
- WiFi-based web control

#### Mobility:
- 4x DC motors & wheels
- 1x SG90 Servo (actuates the gear-based claw mechanism)
- 1x MG996R Servo (controls vertical movement of the claw arm)

#### Structure
- 1x LiPo battery pack
- Chassis & arm designed in OnShape CAD and manufactured through 3D-printing


## The Final Design
<img width="436" height="350" alt="image" src="https://github.com/user-attachments/assets/752077ef-62a0-46b7-a1f9-ef8ba10d69a2" /><img width="466" height="360" alt="image" src="https://github.com/user-attachments/assets/21a49c8a-8dfa-4a33-8fe0-6766ecc941ab" />

---

Clip compilation. https://youtu.be/pTwNambUDn0

### Takeaways
- The meta seemed to heavily favour shovelling blocks into the zones, rather than carrying them within
- The claw itself had a limited range of motion and restricted mobility, with its ability to pick up blocks largely hinging on operator skill (it proved reasonably operable, but could use improvements)
- And notably, we could've taken more liberties with our design and decorations
