# badOS
my OS that does nothing but print.


BUILD INSTRUCTIONS

Usually there is an ISO file in /dist/x86_64, but if you made changes and would like to compile them, then do the following:
1. Install docker
2. Build an image for our build-environment:
`docker build buildenv -t myos-buildenv`
3. run the following command depending on your OS and environment:
 - Linux or MacOS: `docker run --rm -it -v "$(pwd)":/root/env myos-buildenv`
 - Windows (CMD): `docker run --rm -it -v "%cd%":/root/env myos-buildenv`
 - Windows (PowerShell): `docker run --rm -it -v "${pwd}:/root/env" myos-buildenv`
4. Finally, build the os by typing `make build-x86_64` into the command line, more architectures coming later!
