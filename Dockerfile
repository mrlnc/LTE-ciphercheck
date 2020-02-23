FROM ubuntu:18.04

# avoid user interaction in APT (e.g. timezone selection)
ARG DEBIAN_FRONTEND=noninteractive

RUN apt update && \
    apt install -yy git cmake libfftw3-dev libmbedtls-dev\
                   libboost-program-options-dev libconfig++-dev\
                   libsctp-dev libuhd-dev libpcsclite-dev pcsc-tools pcscd

RUN mkdir srsLTE_sec-algo-test
# copies entire source code into container
COPY ./ srsLTE_sec-algo-test/

# build the tools
RUN mkdir srsLTE_sec-algo-test/build
WORKDIR /srsLTE_sec-algo-test/build

RUN cmake ..
RUN make -j `nproc` srsue

# download USRP firmware images
RUN /usr/lib/uhd/utils/uhd_images_downloader.py

# start pcscd for SIM reader access
RUN    echo "#!/bin/bash" >> /etc/startup.sh \
    && echo "pcscd" >> /etc/startup.sh \
    && echo "/srsLTE_sec-algo-test/build/srsue/src/srsue --fast-test true" >> /etc/startup.sh \
    && chmod u+x /etc/startup.sh

ENTRYPOINT ["/etc/startup.sh"]