# ARM STM32 bare metal examples
 
Basic examples of STM32 bare-metal programming. 

*If you've never programmed on MCU registers I suggest to see my bare metal AVR repository before going into STM32. I found that there aren't many resources that cover the very basics of STM32 without HAL. There is a huge gap between working with Arduino and without it, with ARM difficulty increases exponentially.*

*Link to my AVR repository: https://github.com/ErniW/AVR-bare-metal-examples*

*Examples and their code are made and changed gradually so functions may differ between examples.*

**TODO**
- Fix the DMA serial bi-directional communication.
- I2C interrupts (and DMA?).
- SPI.
- RTC.
- IWDG, WWDG.

### Board:
I'm using the **STM32f446RE** board with ARM Cortex M4 CPU. If you're using other STM32 board be aware that things may not work on your board and you must change files and settings.

### Documentation:
- **UM1724 User manual** - for your board pinout, if you have the original plastic package of your board it's on its back. https://www.st.com/resource/en/user_manual/um1724-stm32-nucleo64-boards-mb1136-stmicroelectronics.pdf
- **RM0390 Reference manual** - for STM32f446RE registers. https://www.st.com/resource/en/reference_manual/rm0390-stm32f446xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf
- **STM32F446xC/E** - for STM32f446RE block diagram and alternate functions table https://www.st.com/resource/en/datasheet/stm32f446re.pdf


### Toolchain:
- **Make sure you've installed ARM toolchain.** To check if everything is ok type `arm-none-eabi-gcc -v` in your terminal.
- We will use **GNU Make** for build process.
- To upload the code I'm using **STLink** https://github.com/stlink-org/stlink which is included.

*You can see that most of STM32 examples found in the internet are using STM32 IDE and most tutorials are using STM32 HAL library - there are many reasons to not use it so I will work with ARM toolchain and Visual Studio Code. More complex builds are using CMake instead of GNU Make but I want to stay with the basics so you can follow along.*

### Folder structure & libraries.
**You need to download the STM32 drivers** unless you probably already have them if you used STM32 IDE. In Makefile change the include directory for CMSIS.

I've put the necessary files in STM32F446RE folder:
- `startup_stm32f446xx.s`
- `STM32F446RETX_FLASH.ld`
- `stm32f446xx.h stm32f4xx.h system_stm32f4xx.h` headers.

*These files can be found inside drivers. If you are using different board you have to include similar files. Remember about changing the makefile variables.*

### Setting the Visual Studio Code:
In `c_cpp_properties.json` inside .vscode folder:
- **Add includes:** for CMSIS in STM32 drivers, they should be located in: `STM32Cube_FW_F4_V1.26.1/Drivers/CMSIS/Include`
- **Add defines:**  `STM32F446xx`, `__CC_ARM`

*Otherwise the code will compile but it will highlight undefined references.*

### Compile and upload:
In terminal type:

`make compile`

`make upload`

or `make compile upload`
