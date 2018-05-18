# Bulls and Cows
###### A game based on mastermind

      _____________________________________
    / Welcome to Bulls and Cows, a fun word \
    \ game!                                 /
      -------------------------------------
             \   ^__^
              \  (oo)\_______
                 (__)\       )\/\
                     ||----w |
                     ||     ||

## build

    $ rdm &  # r-tag daemon
    $ cd <project_dir>
    $ cmake . -DCMAKE_EXPORT_COMPILE_COMMANDS=1
    $ rc -J .  # generate compile_commands.json
    $ make

## run
    $ ./bullcow

## requirements
- g++
- probably `base-devel` or `build-essentials` or whatever your distros equivalent
