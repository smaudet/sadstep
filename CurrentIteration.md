# Risk Elimination #

  1. GameCanvas is moving things across the screen at variable framerates but constant speeds
  1. Timeline code is dry-benchmarked, i.e. testing is done privately to determine that the math, in fact, does make sense, and it isn't a matter of eyeballing the distance on screen. This can be done with code (where I don't really care as long as it doesn't permanently break anything by resisting being commented out) that calls timers on every arrow time, sequentially, plays the music, and displays textual output as to when the arrow actually got across screen, when it was spawned, etc. The math for faking getting it to move across the screen is simple; whatever your speed is (in single bpm at least) gives you a time that you display the text output.
  1. Timeline code supports multi-bpm. If the math was right for the single bpm, odds are it should be right for the multi-bpm. This involves actual coding
  1. Finishing getting the scores to NOTIFY in the OBSERVER PATTERN the mainwindow that it needs to tell to GameCanvas to display something to do with scores.
  1. ? Getting movies to show up in the GameCanvas background
    * Asking mainwindow for the background
    * Blitting movies (somehow) onto the screen (probably from VLC)
    * ? Performing movie magic like fading, etc. on the backgrounds
  1. ? Cleaning up the GUI
    * Agar/SDL compatible rewrite?
    * Qt Animation Framework rewrite (yes, 4.6.0 includes the entire Animation Framework!!)
    * ?Skins
  1. ? Start on Song Analysis
    * Getting the main beat
    * Dividing the beat according to difficulty
    * Extracting useful Tonal input
    * Mapping Tonal input to notes

Risk Responsibility
  1. Sebastian Audet - 100%
  1. Dan Wiehe - 60% Sebastian Audet - 30% Scott Tollas 10%
  1. Dan Wiehe - 70% Sebastian Audet - 30%
  1. Scott Tollas - 90% Sebastian Audet - 10%
  1. Sebastian Audet - 100%
  1. Scott Tollas - 95% Sebastian Audet - 5%
  1. Sebastian Audet - 75% Dan Wiehe - 25%


# Issues #

  1. We need an InputManager class, and some way to generalize that input. The code right now that sits inside of Keypress events needs to disappear or be replaced with something very generic. It needs to be generic, because if we ever A. change libraries B. have multiple libraries with key press events in them, we would have to perform a rewrite of that code. E.g., with the SDL code, SDL has its own little separate input management libraries, as does Qt, and I can only use Qt's stuff atm (only code implemented), but this means when using the SDL window, I have to un-fullscreen both screens, and keep the qt window in focus to trigger anything. No good.
  1. The timeline code "works"...that is it works backwards AFAIK. The beats are synchronized at the bottom of the screen, otherwise they are completely off.
  1. Our code is very slow/process intensive. The new SDL stuff works fast, and it works at variable fps (so same speed, but rendering as fast as possible), but on Challenging I saw the frame rate slow to about 12 - 20 fps. Working on speeding things up though, and a lot faster/more consistent that before.
  1. There is various confusion in the code as to whether to support 4 or 9 lanes. We are supporting 9 lanes(four base, four sides, 1 jump)  - either putting a 9 in or looping dynamically through your code is not that hard to do, and where I've seen this I've attempted to correct it for the most part, except in score (where there are things present such as hard-coded switch/if statements, i.e. also know as bad programming) and practically in GameCanvas (it will look a bit funky). Support 9 where you can, if you see code that doesn't support this, fix it (especially if its your code). Like I said, not that hard to do to support scoring one lane at a time, and then just generalize to n lanes. Code should NOT be crashing because a stepfile happens to have more than 4 lanes of data in it (like is happening with Daft Punk). If its "unsupported" just make it so it won't matter and will DISREGARD THE DATA and not CRASH THE PROGRAM. But, officially, we are supporting n lanes of data, and, practically, 9. When I finally get around to loading in the images a bit more cleanly (from disk instead of from memory), we will have graphical support for 9 lanes, right now you'll just get funny behavior that shouldn't crash the program.
  1. There is some slowdown in the program, due to rounding errors. GameCanvas will probably be the first to get this fixed (distance rounding errors), but Timeline definitely should be fixed to reduce the error.