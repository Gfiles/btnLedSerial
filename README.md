# btnLedSerial
Arduino projet to Read buttons and control the internal LED trough Serial comunication

When a Button is Presses you will receive de number of the buttin pressed. First Button = 0, 2nd Button = 1, and so on.

To turn off the LEd send "00" First Number de led position 2nd Number the LED State.
To turn on "01".

Ser2Key Python Reads the Serial port anda Converts de serial input into keyboard Presses.
In response a timer is activated anda the respective led is switched of the the duration of the timer.
