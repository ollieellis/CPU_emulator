Individual Reflection
=====================

Imperial Login : es5017

Group Name : help

Guidance
--------

The aim is to get you to think about specific things that you
have learnt, or things that went well or less well. For each
of the areas identified below, write (at most) 100 words on how
well that area went. Examples of things that you might address
are:

- Some kind of concept or approach that became clearer

- A skill or tool that you found useful

- Identifying where some choices were poor

- A change in approach that improved your solution

- Changes in strategy that could help in future projects



You should identify things specific to you and this coursework,
not just general things, and link them to specific features or
activities of the coursework. In some cases you may want to refer
to classes, functions, or source files in your submission,
and/or highlight specific commits (e.g. by hash) in order to
show changes.

For example, these is quite generic and doesn't tell us anything:

> I learnt how to use classes more effectively.

> I hadn't used the command line much before, and now have got used to it.

Whereas these are more specific (don't use these as a template, you
have to word):

> Originally I wasn't sure how to map part A of the simulator into
> structs, so I originally thought about mapping each B to an
> struct. However, this turned out to be the wrong approach
> because C, so we ended up using D.

> I suggested that we use method A to build the testbench, as I
> thought it would have benefit B. While it worked well enough,
> in future I might choose to do C, because D. 

There is no "right" answer, and there is no particular
requirement on how "big" each thing is, either in concept
size or the number of words. There is also no bias towards
whether a strength or weakness is better - either could be
relevant. The only requirements are that the answers should be:

- Specific to you

- Specific to this coursework

- Be some sort of genuine reflection on your practise

- Related to the specific topic

This will be assessed, and is not just a tick box exercise.

Submission
----------

This should be submitted individually via blackboard (not
via the group repo).

Group working
-------------

We worked great as a group, and managed to distribute tasks evenly and fairly to suit each of our strengths and areas for improvement. While initially it was a challenge to organise opportunities to meet and work on the project, we quickly realised that creating a schedule is the best way to ensure group synergy throughout the project. Group working ensured we learnt how to use git and github properly, and despite initial frustration at invalid merges and remote syncs, the concept of branches became apparent and utilised plentifully within the group.

Time management
---------------

I knew cramming was absolutely not an option, hence setting specific goals to accomplish by certain deadlines was crucial during development to stay on track, and was what allowed us to submit a functional interim submission, which unfortunately could not compile using make as I hadn't added the mips_simulator to the .gitignore. Being a large project with lots of opportunities to learn, I worked multiple hours every day on the project since day 1. Using other peoples testbenches and simulators on our testbenches definitely helped speed up production as it identified core issues with our simulator.


Software skills (e.g. debugging, design, coding)
------------------------------------------------

The simulator was made in with an OOP approach, and functionality was abstracted away as much as possible. For example, the Bitwise_helper class contained many static functions that performed general operations on containers of bits, eg overwrite_bits, sign_extend_to_32, extract_bits etc. There was a class for registers, memory, instructions, and even file io, which proved to be an excellent decision when implementing more difficult functionality down the line. The way we designed the testbench meant that debugging was very simple; it created a log file for every test it ran which contained all the stderr from the simulator.


Tools and Infrastructure (e.g. OS, automation, ...)
---------------------------------------------------

I developed on Unix based MacOS, a similar environment to the target machines. I used VSCode for both simulator and testbench. From the start I made a run.sh bash script that ran make simulator and make testbench, then bin/mips_testbench bin/mips_simulator so the whole thing could be run in one quick command. The testbench converts the user generated .s assembly files into binary files using a mips converter project made in C++ by some peers, and is hence very extensible on any platform, and didn't require a mips conversion using linux only tools every time I added a new test.

Understanding of computer architecture
--------------------------------------

This project forced the tiny details that are often overlooked to be presented. Specifically with branches and jumps, I learnt that due to the pipelining of a MIPS cpu, it is necessary to have a branch delay slot - but it can be used cleverly by programmers. Reading a lot about undefined behaviour also ensured I thought about the differences between a CPU and the simulator, and if simulating the process of a CPU was actually the best approach, for example load delay, which has extra time to load from memory, which is a side effect of hardware rather than ideal functionality. 