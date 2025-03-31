FROM alpine:latest


# Dependencies

# For the first step, we’ll install the dependencies needed to build and run InspIRCd,
#  starting with git:

RUN apk update && apk add --no-cache \
    wget \
    perl \
    g++ \
    make \
    git

# Download source

# The latest version of InspIRCd can be downloaded from: 
# https://github.com/inspircd/inspircd/releases/latest

# As we’re going to be building the latest version from the source code, 
# we need to grab the tar.gz archive either with your browser or from the command line. 
# To take version 2.0.25 as an example, you could use the following command to download 
# the archive:
RUN wget https://github.com/inspircd/inspircd/archive/v2.0.25.tar.gz inspircd | ls
RUN tar xvf ./v2.0.25.tar.gz


CMD sleep infinity  

# cd inspircd-2.0.25/
# perl ./configure