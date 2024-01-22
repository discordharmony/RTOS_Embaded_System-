This project involves an RTOS system designed for a calculator. The goal is to complete the project within a six-day timeframe.

The kit includes a keypad with 16 pushbuttons, a slide switch, an LCD, and LEDs.

Task 1: Read the state of the slide switch and use a mailbox to send data to a specific task based on the switch state.

Slide switch state 0 (MODE1): Task 1 reads the switch state and transmits data to Task 2, 3, 4, and 5 through the Tx1Mbox mailbox.

Slide switch state 1 (MODE2): Tasks 2, 3, 4, and 5 perform addition, subtraction, multiplication, and division, respectively.

Slide switch state 2 (MODE3): Tasks 6, 7, 8 handle sine, cosine, and tangent calculations.

Slide switch state 3 (MODE4): Tasks 9, 10, 11, 12 handle exponentiation, square root, natural logarithm, and logarithm operations.



The project utilizes mailboxes as follows:

Tx1Mbox: Task 1 transmits data to Tasks 2, 3, 4, 5.

Tx2Mbox: Task 1 transmits data to Tasks 2, 3, 4, 5.

Tx3Mbox: Task 1 transmits data to Tasks 6, 7, 8.

Tx4Mbox: Task 1 transmits data to Tasks 9, 10, 11, 12.
