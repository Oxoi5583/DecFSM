# DecFSM
A Easy-to-use enum driven Header Only Finite State Machine for My Personal Game

## Introduction
This is just a sharing of source code for a Finite State Machine I used in my Project.

## Usage
1. Include the header "DecFSM.h"<br/>
![image](https://github.com/user-attachments/assets/34b3fd40-10f1-4b6b-a59d-53b1deb17bc1)


2. Declare a enum for repesenting states.<br/>
![image](https://github.com/user-attachments/assets/b6cf44da-105a-4850-9549-9494c901faac)

3. Declare a struct for repesenting event data.<br/>
![image](https://github.com/user-attachments/assets/af4ec36f-1470-497f-9a6b-77bd0ce3276e)

4. Declare a struct for repesenting transition.(inherit from DecFSM::base_transition<evt>)<br/>   The base struct will need a class argument which should be your event data struct.<br/>   Remember to tell the transition what is the from state and to state and the condition to decide when to transit.<br/>   Set priority if needed.<br/>
![image](https://github.com/user-attachments/assets/ac58bf72-7ec8-454b-815a-40a55b18421b)

5. Instance the FSM, transitions and register them to FSM.<br/>
![image](https://github.com/user-attachments/assets/300158dc-f275-483a-86b4-56dfd761fb5a)

6. Instance a Event data struct, prvoke the process() function in FSM. And change Event data.<br/>
![image](https://github.com/user-attachments/assets/9fb01e45-fade-4306-9ab2-68bed4f3eb4e)

<br/><br/>
Result : <br/>
![image](https://github.com/user-attachments/assets/24c4aad1-a79d-46e4-888d-57d3b58358af)
<br/><br/>
Programme Diagram : <br/>
![image](https://github.com/user-attachments/assets/7e67bd2a-5b20-4ae3-9922-cda3983fe652)
