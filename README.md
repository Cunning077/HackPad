This is the beggining of the Hackpad project i mainly created this section ot allow me to start posting devblogs and attempt to get started on this project.
This is an update the the readme i have finished the pcb design and have now moved on to the case design after finishing the case i will start with the software behind the system, the point of the software will be simple and easy setup


Software writeup:

Goal:
design a fully customizable macropad that allows quick opens for all sorts of things.

Background:
On my desktop i have like 4 different .sh files designed to literally just open up a project with 4 windows open to basically support the style of workspace i like for that project the idea is im gonna stick those files on the macropad where it simply just runs the .sh file. In addition there is a few keymaps i like in nvim and will also add functionality for them for example, to generate markdown todo lists i have to press 3 buttons maybe i want to simply press an external. There is alot i could try the point of the project tho is to design the software to simply allow any tech savy person to input whatever functionality they want for there macropad. so readability will be a core staple of this project.

1-Brainstorm:
I will have the system staged into 3 sets.
    1-Screen rendering: Here the 6 tft display screens will be rendered with the images provided.
    2-event handler: simply handle button presses, and will send off the trigger to the final set
    3-handle request: when button 2 is pressed the preset load for 2 will trigger simple as that.

Length Is defined as the Cmd received and any additional information this excludes bytes for images and text
During text related commands the length of text sent is also embedded in the packet information.
