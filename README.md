# Laser Harp
## Overview
The *Laser Harp* is our final project for our ECEN 361 (Embedded System) course. The basic idea is that when a user breaks or "plucks" a string a note of a corresponding frequency is played. 

This project requires a basic real time operating system (RTOS), different types of inputs and outputs, utlizing common peripharal communction standards, and basic introductions to digtal signal processing (DSP).

## Team
**Team Lead** - Marshall Potts

**Hardware Lead** - Sawyer Evans

**Software Lead** - Jared Swasey

**Component Coordinator** - Ian Searle

**Creative Design Assurance** - Joseph Wisden

## Bill Of Materials
| Item Name       | Quantity | Link                           |
|-----------------|----------|---------------------------------------|
| Photoresitors  | 12        | N/A |
| Laser Diode   | 12        | [Link](https://www.amazon.com/HiLetgo-10pcs-650nm-Diode-Laser/dp/B071FT9HSV/ref=sr_1_3?crid=3H3MM61YSYGM1&dib=eyJ2IjoiMSJ9.9Ml-QAMuxixZG9GYrtqWh0ONodM0ILt-aNh3FtSPJwc0VMtrFR2xtxfixFhiu35O900vpFOStWr_u29nQ-SZhsa9B-sUFyNqmgN7di__fyvRhhRSgDr4xzSZpqkAIRsjxb1oN3n3VRECbx71xOqbXCrsBjXx_CzSwJjfV-SHUGTRRO1rx9WGUstkfuSYzVysJAAe9ZmQhV0ukAT88GfIXy3Bmgmopqz1rqT-U6FoyYg.bpC9aeLP98DVx9chbGsdqRm7ij2zGCO98jQP-9tFrV4&dib_tag=se&keywords=laser+diode&qid=1720821173&sprefix=laser+diod%2Caps%2C151&sr=8-3) |
| 10KΩ Resistor   | 1 2       | N/A |
| STM 32 L476RG      | 1        | [Link](https://www.digikey.com/en/products/detail/stmicroelectronics/NUCLEO-L476RG/5347711) |
| Pushbutton Switch SPST-NO Keyswitch Through Hole            | 1        | [Link](https://www.digikey.com/en/products/detail/cherry-americas-llc/MX1A-11NW/91134) |
| PAM8610 Mini Stereo AMP Audio      | 1    | [Link](https://www.amazon.com/HiLetgo-PAM8610-Amplify-Portable-Amplifier/dp/B01DK29KYG/ref=sr_1_2_sspa?dib=eyJ2IjoiMSJ9.TBzGFAz1qul_n-oSouJJpgKW6yZdShq-Q57eK6gmlsBxhC72-SthU_X1GkphLKrWgX1RqhwlLFHQ_LIcgKats4xFbeDid_IsYkIZ3mJjuJNH9uFHDVZ-eenm5TYeYMbMgpTpi_-NSOfvXE54lDwrRfktCU4OZRpBfs-OAeMUgpVuuilCQqG_0g4uoJ2JT1fhaaYytisUAZd35V1ZQLrKud_KBUhiSfO7EjsQmNwRXt8.nvdErzkhf1dhIM7AwAVq-HVQJDCi3Q_qwbJ--hRPp3Y&dib_tag=se&keywords=audio+amplifier+board&qid=1720820937&sr=8-2-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&psc=1) |
| Speakers | 2|[Link](https://www.amazon.com/Gikfun-Speaker-Stereo-Loudspeaker-Arduino/dp/B01LN8ONG4/ref=sr_1_3?dib=eyJ2IjoiMSJ9.M0WqXdKcR1EYeSlhAZFffFtE2dXpMI1sKd9Toi4QG0KjS9XE1gR4r-GyYChlQUig5EACX50z7cn_PIjM8F59ZNJna4asXVzXc4WSbgBfItB9B8bhdZLbTO5ThnUkW2Ki1E5Rz-IxIslBKRy6cQj9-Fp6aTvX8XIRAj3UHIJ06t2xWVllWSrY-61uDWGVaxJmxduxY_mvSF8_JBnoSGXjjw5Bd5WY-H4WWW4TFyCZqvg.r3dsg3EtQmGc4s1Y27Od0nZIhKLb3tBR26EEpjiaCkw&dib_tag=se&keywords=speaker+component&qid=1714489710&sr=8-3)



## Possible Improvments
One improvement that can be made is the improve the CADD Models. The photoresistors are not a perfect fits. It would be nice if they were a tighter fit. We could also try to make things smaller and improve the time it takes to make everything.

We could also work on having a custom PCB. This would include implenting a power regualtor to the project. This would make it so we could power it of a USB power bank. We would also work to include the amplifer on this board. There would be two main sections. We would have one section in the top, and the second one would be in the bottom and handle most things.

A further improvemetn would be adding in bluetooth. This would allow a user to play the music to an external speaker.

- More Modes
- Instrument Sounds
- Caps for the buttons

