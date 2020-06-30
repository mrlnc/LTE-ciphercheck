FROM ubuntu:18.04

# avoid user interaction in APT (e.g. timezone selection)
ARG DEBIAN_FRONTEND=noninteractive

RUN apt update && \
    apt install -yy git cmake libfftw3-dev libmbedtls-dev\
                   libboost-program-options-dev libconfig++-dev\
                   libsctp-dev libuhd-dev libpcsclite-dev pcsc-tools pcscd

RUN mkdir lte-ciphercheck
# copies entire source code into container
COPY ./ lte-ciphercheck/

# build the tools
RUN rm -rf lte-ciphercheck/build
RUN mkdir lte-ciphercheck/build
WORKDIR /lte-ciphercheck/build

RUN cmake ..
RUN make -j `nproc` srsue

# download USRP firmware images
RUN /usr/lib/uhd/utils/uhd_images_downloader.py

# start pcscd for SIM reader access
RUN    echo "#!/bin/bash" >> /etc/startup.sh \
    && echo "pcscd" >> /etc/startup.sh \
    && echo "/lte-ciphercheck/build/srsue/src/srsue" >> /etc/startup.sh \
    && chmod u+x /etc/startup.sh

ENTRYPOINT ["/etc/startup.sh"]