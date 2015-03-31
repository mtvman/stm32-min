#!/bin/bash

# Start debug server: openocd -f openocd.cfg -c "init" -c "halt" -c "reset halt"
# Start debugger:

arm-none-eabi-gdb --tui --eval-command="target remote localhost:3333" main.elf
