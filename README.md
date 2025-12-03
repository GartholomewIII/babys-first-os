# What is This?

In an attempt to learn more about what goes on behind the endless layers of abstraction.
I will be creating my very own operating system. This README will serve as a kind of documentation on things I learn.
I will be writing down every new discovery, definition and documenting what breaks.
In the beginning I will be using the OSdev Wiki to guide me in creating a 'bare-bones' OS

## 12/01/2025

Today we are compiling! And its successful! I have attached an image below showing what the QEMU virtual machine looks like with the kernel running.

![kernel_running](readme-assets/kernel-running.png)

### What I've Learned:

I've learned what bootloaders are. Bootloaders are the first thing that is ran when you power on a computer and it loads the main OS in memeory.
OS development requires a LOT more reasoning than simple web/desktop development where 90% of the effort is on the GUI.
I've also learned that Linux really is the only platform you can realistically develop an operating system.

#### Goals for next session:

Get the OS to play a song

## 12/02/2025

Today I learned a very valuable lesson... You really have to go 10x slower when writing in C. The idea to play a song was WAY too ambitious, but I did make some progress.
I am now able to read keyboard input

![keyboard_input](readme-assets/keyboard-input.gif)

### What I've Learned:

I've learned about Global Descriptor Tables, the VM I am using comes pre packages with GDT, but it is apparently a good idea to set up one of your own if you are doing complex tasks 
such as audio input and output. The first GDT entry needs to be Null, the CPU never references this location and it designates the beginning of the table. The two other entries define the kernel code segment
and the kernel data segment. I also implimented a bare bones IDT, ISR and IRQ. The IDT (interrupt descriptor table) is an array of 256 entries index 0-31 are CPU exceptions, the rest are 
software and hardware interrupts, each entry in an IDT says that if this happens or if this 'flag' is hit, jump to this address, in the above snippet the flag is the enter key
and it then prints a return statement. The ISR (interrupt Service Routine) which is an exception handler is the actual code that runs when an interrupt happens. And then the IRQ is the 
hardware interrupt line, it allows you to read input from hardware, for example the IRQ1 line is responsible for the keyboard.

#### Goals for Next Session:

Impliment a simple beep when the enter key is pressed (far more realistic)


