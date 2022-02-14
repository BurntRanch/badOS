# badOS
my OS that does nothing but print.

Update: It is time for my return, i have rewritten my code and got access to VGA functions, expect a complete rewrite!

BUILD INSTRUCTIONS

Usually there is an ISO file in /dist/x86_64, but if you made changes and would like to compile them, then do the following depending on your branch:
Main branch:
     1. Install docker
     2. Build an image for our build-environment:
     `docker build buildenv -t myos-buildenv`
     3. run the following command depending on your OS and environment:
      - Linux or MacOS: `docker run --rm -it -v "$(pwd)":/root/env myos-buildenv`
      - Windows (CMD): `docker run --rm -it -v "%cd%":/root/env myos-buildenv`
      - Windows (PowerShell): `docker run --rm -it -v "${pwd}:/root/env" myos-buildenv`
     4. Finally, build the os by typing `make build-x86_64` into the command line.
Beta branch:
     1. Run the script from https://github.com/mell-o-tron/MellOs/blob/main/A_Setup/setup-gcc.sh
     2. Just run setup.sh from the dfirectory.
