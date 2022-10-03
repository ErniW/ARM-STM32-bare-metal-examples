# ARM-STM32-bare-metal-examples
 
Basic examples of STM32 bare-metal programming. 

*If you've never programmed on MCU registers I suggest to see my bare metal AVR repository  before going into STM32. I found that there are almost zero resources that cover the very basics of STM32 without HAL. There is a huge gap between working with Arduino and without it and difficulty increases exponentially.*

### Board:
I'm using the **STM32f446RE** board which has ARM Cortex M4 CPU. If you're using other STM32 board be aware that things may not work on your board.

### Toolchain:
- **Make sure you've installed ARM toolchain.** To check if everything is ok type `arm-none-eabi-gcc -v` in your terminal
- We will use **GNU Make** for build process.
- To upload the code I'm using **STLink** which is included.

*You can see that most of STM32 examples are using STM32 IDE and most tutorials are using it with STM32 HAL library -there are many reasons to not like it so I will work with ARM toolchain and Visual Studio Code. More complex builds are using CMake instead of GNU Make but I want to stay with the basics so you can follow along.*

### Folder structure & libraries.
**You need to download the STM32 drivers** unless you probably already have them if you used STM32 IDE. In Makefile change the include directory.

I've put the necessary files in each folder:
- `startup_stm32f446xx.s`
- `STM32F446RETX_FLASH.ld`
- `stm32f446xx.h stm32f4xx.h system_stm32f4xx.h` headers.

*These files can be found inside drivers.*

### Setting the Visual Studio Code:
In c_cpp_properties.json inside .vscode folder:
- add includes for CMSIS in STM32 drivers, they should be located in: `STM32Cube_FW_F4_V1.26.1/Drivers/CMSIS/Include`
- add defines  `STM32F446xx`, `__CC_ARM`

*Otherwise the code will compile but it will highlight undefined references.*