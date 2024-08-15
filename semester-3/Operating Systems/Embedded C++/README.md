# embedded-c-plus-plus


## Introduction

[EduTools](https://plugins.jetbrains.com/plugin/10081-jetbrains-academy) is an IntelliJ plugin for teaching and learning programming langages. 
It allows to create a full course with lessons and tasks of different types. Refer to the documentation for more details.

## Installation
Teachers and students need to install the [EduTools plugin]((https://plugins.jetbrains.com/plugin/10081-jetbrains-academy) to their specific IntelliJ IDE. 
The plugin is compatible with IntelliJ IDEA, CLion and WebStorm, among other tools. For C++ lessons, one need to use CLion.

## For students
The course content can be distributed as a .zip file or through github. At this point, we tested only distribution as a .zip file.
Note that in this particular case, the course content cannot be updated anymore after distribution.

## For teachers
Follow the instructions on [course creator start guide](https://plugins.jetbrains.com/plugin/10081-jetbrains-academy/docs/educator-start-guide.html) for more information. 
A course can be split into sections, that may content a number of lessons. Lessons can be standard or framework lessons. Framework lessons contain tasks with dependencies 
while standard lessons contain independent tasks. Dependencies tasks allow to present a concept over multiple tasks - say if one wishes for instance to teach inheritance using
multiple tasks.

It is important to understand the different task types:

- Edu: coding task with validation based on a test program.
- Output: coding task with validation based on program output - program input can also be included in the task.
- Theory: task for presenting a concept, usually containing a demonstration program without validation.
- Multiple choice: quiz with one or multiple correct answers.
- IDE: task for learning the IDE itself.

More info is given [here]((https://plugins.jetbrains.com/plugin/10081-jetbrains-academy/docs/educator-start-guide.html).

## The project on git
Note that a tentative .gitignore file has been added to the project. Any suggestion for improving project sharing among teachers is welcome.
Once you clone this project on your local machine, you simply need to open it as a standard project in CLion. Make sure that Course Creator Features are enabled.