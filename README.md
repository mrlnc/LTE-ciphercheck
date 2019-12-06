
[![Build Status](https://travis-ci.org/srsLTE/srsLTE.svg?branch=master)](https://travis-ci.org/srsLTE/srsLTE)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/srsLTE/srsLTE.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/srsLTE/srsLTE/context:cpp)
[![Coverity](https://scan.coverity.com/projects/10045/badge.svg)](https://scan.coverity.com/projects/srslte)

srsLTE is a free and open-source LTE software suite developed by SRS (www.softwareradiosystems.com). 
See the srsLTE project pages (www.srslte.com) for documentation, guides and project news.

It includes:
  * srsUE - a complete SDR LTE UE application featuring all layers from PHY to IP
  * srsENB - a complete SDR LTE eNodeB application 
  * srsEPC - a light-weight LTE core network implementation with MME, HSS and S/P-GW
  * a highly modular set of common libraries for PHY, MAC, RLC, PDCP, RRC, NAS, S1AP and GW layers. 

srsLTE is released under the AGPLv3 license and uses software from the OpenLTE project (http://sourceforge.net/projects/openlte) for some security functions and for NAS message parsing.

Common Features
---------------

 * LTE Release 10 aligned
 * Tested bandwidths: 1.4, 3, 5, 10, 15 and 20 MHz
 * Transmission mode 1 (single antenna), 2 (transmit diversity), 3 (CCD) and 4 (closed-loop spatial multiplexing)
 * Frequency-based ZF and MMSE equalizer
 * Evolved multimedia broadcast and multicast service (eMBMS)
 * Highly optimized Turbo Decoder available in Intel SSE4.1/AVX2 (+100 Mbps) and standard C (+25 Mbps)
 * MAC, RLC, PDCP, RRC, NAS, S1AP and GW layers
 * Detailed log system with per-layer log levels and hex dumps
 * MAC layer wireshark packet capture
 * Command-line trace metrics
 * Detailed input configuration files
 * Channel simulator for EPA, EVA, and ETU 3GPP channels
 * ZeroMQ-based fake RF driver for I/Q over IPC/network  

srsUE Features
--------------

 * FDD and TDD configuration
 * Carrier Aggregation support
 * Cell search and synchronization procedure for the UE
 * Soft USIM supporting Milenage and XOR authentication
 * Hard USIM support using PCSC framework
 * Virtual network interface *tun_srsue* created upon network attach
 * QoS support
 * 150 Mbps DL in 20 MHz MIMO TM3/TM4 configuration in i7 Quad-Core CPU.
 * 75 Mbps DL in 20 MHz SISO configuration in i7 Quad-Core CPU.
 * 36 Mbps DL in 10 MHz SISO configuration in i5 Dual-Core CPU.

srsUE has been fully tested and validated with the following network equipment: 
 * Amarisoft LTE100 eNodeB and EPC
 * Nokia FlexiRadio family FSMF system module with 1800MHz FHED radio module and TravelHawk EPC simulator
 * Huawei DBS3900 
 * Octasic Flexicell LTE-FDD NIB

srsENB Features
---------------

 * FDD configuration
 * Round Robin MAC scheduler with FAPI-like C++ API
 * SR support
 * Periodic and Aperiodic CQI feedback support
 * Standard S1AP and GTP-U interfaces to the Core Network
 * 150 Mbps DL in 20 MHz MIMO TM3/TM4 with commercial UEs
 * 75 Mbps DL in SISO configuration with commercial UEs
 * 50 Mbps UL in 20 MHz with commercial UEs
 * User-plane encryption

srsENB has been tested and validated with the following handsets:
 * LG Nexus 5 and 4
 * Motorola Moto G4 plus and G5
 * Huawei P9/P9lite, P10/P10lite, P20/P20lite
 * Huawei dongles: E3276 and E398

srsEPC Features
---------------

 * Single binary, light-weight LTE EPC implementation with:
   * MME (Mobility Management Entity) with standard S1AP and GTP-U interface to eNB
   * S/P-GW with standard SGi exposed as virtual network interface (TUN device)
   * HSS (Home Subscriber Server) with configurable user database in CSV format
 * Support for paging

Hardware
--------

The library currently supports the Ettus Universal Hardware Driver (UHD) and the bladeRF driver. Thus, any hardware supported by UHD or bladeRF can be used. There is no sampling rate conversion, therefore the hardware should support 30.72 MHz clock in order to work correctly with LTE sampling frequencies and decode signals from live LTE base stations. 

We have tested the following hardware: 
 * USRP B210
 * USRP B205mini
 * USRP X300
 * limeSDR
 * bladeRF

Build Instructions
------------------

* Mandatory requirements: 
  * Common:
    * cmake              https://cmake.org/
    * libfftw            http://www.fftw.org/
    * PolarSSL/mbedTLS   https://tls.mbed.org
  * srsUE:
    * Boost:             http://www.boost.org
  * srsENB:
    * Boost:             http://www.boost.org
    * lksctp:            http://lksctp.sourceforge.net/
    * config:            http://www.hyperrealm.com/libconfig/
  * srsEPC:
    * Boost:             http://www.boost.org
    * lksctp:            http://lksctp.sourceforge.net/
    * config:            http://www.hyperrealm.com/libconfig/

For example, on Ubuntu 17.04, one can install the required libraries with:
```
sudo apt-get install cmake libfftw3-dev libmbedtls-dev libboost-program-options-dev libconfig++-dev libsctp-dev
```
or on Fedora:
```
dnf install cmake fftw3-devel polarssl-devel lksctp-tools-devel libconfig-devel boost-devel
```

Note that depending on your flavor and version of Linux, the actual package names may be different.

* Optional requirements: 
  * srsgui:              https://github.com/srslte/srsgui - for real-time plotting.
  * libpcsclite-dev:     https://pcsclite.apdu.fr/ - for accessing smart card readers

* RF front-end driver:
  * UHD:                 https://github.com/EttusResearch/uhd
  * SoapySDR:            https://github.com/pothosware/SoapySDR
  * BladeRF:             https://github.com/Nuand/bladeRF
  * ZeroMQ:              https://github.com/zeromq

Download and build srsLTE: 
```
git clone https://github.com/srsLTE/srsLTE.git
cd srsLTE
mkdir build
cd build
cmake ../
make
make test
```

Install srsLTE:

```
sudo make install
srslte_install_configs.sh user
```

This installs srsLTE and also copies the default srsLTE config files to
the user's home directory (~/.config/srslte).


Execution Instructions
----------------------

The srsUE, srsENB and srsEPC applications include example configuration files
that should be copied (manually or by using the convenience script) and modified,
if needed, to meet the system configuration.
On many systems they should work out of the box.

By default, all applications will search for config files in the user's home
directory (~/.config/srslte) upon startup.

Note that you have to execute the applications with root privileges to enable
real-time thread priorities and to permit creation of virtual network interfaces.

srsENB and srsEPC can run on the same machine as a network-in-the-box configuration.
srsUE needs to run on a separate machine.
=======
This tool quickly tests LTE networks for their cipher support. It's for use by telecom operators only.

# Encryption in LTE Networks

LTE networks protect user traffic and control data with encryption, and additionally integrity-protect control data. We're going to have a look at the method that is used for securing the data.

![Transport Security](./img/transport_security.png)

There are multiple ciphers available, thus, smartphone and network need to negotiate which one to use. Snow3G, AES and ZUC actually protect the messages. However, there's a 'NULL' algorithm for testing purposes and emergency calls -- it does not provide any protection.

![Cipher Support](./img/cipher_support.png)

Networks and smartphones must support AES and Snow3G. ZUC is optional. The NULL algorithm may only be selected for emergency purposes.

## Impact of Misconfigurations

If a network is poorly configured, man-in-the-middle attacks become trivial. If a network accepts unprotected connections, attackers can impersonate benign users.

![MitM](./img/mitm.png)

# Setup

The whole setup looks like this:

![Setup](./img/system_overview.png)

Basically, this software is just [srsLTE](https://github.com/srsLTE/srsLTE) with minor changes. See the [srsLTE README](https://github.com/srsLTE/srsLTE/blob/master/README.md) for detailed build instructions, and [www.srslte.com](srslte.com) for documentation, guides and project news. srsLTE is released under the AGPLv3 license and uses software from the OpenLTE project (http://sourceforge.net/projects/openlte) for some security functions and for NAS message parsing.

# Testing Procedure

When the UE starts the connection procedure, it will transmit a list of supported ciphers. The network then selects one of these, based on it's own capabilities. If there's no match, or some policy prohibits some cipher (e.g., NULL), the network must reject the connection attempt.

For example, if the UE signals only NULL ciphers for encryption and integrity protection, the network should not establish a connection as in this example:
![Setup](./img/test_procedure.png)

We perform one connection setup for each possible combination of ciphers and check whether the network accepts or denies. Since there are 256 combinations, a single test run performs at least that many attaches to the network.

# Credits

srsLTE is a free and open-source LTE software suite developed by SRS (www.softwareradiosystems.com).