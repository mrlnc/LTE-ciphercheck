Security Algorithm Support in LTE Networks
========

This software tests the network-side support of security algorithms in LTE. We show the impact of misconfigured networks in a research paper ([PDF](https://www.infsec.ruhr-uni-bochum.de/media/infsec/veroeffentlichungen/2019/04/23/wisec19-final123.pdf)):
> Merlin Chlosta, David Rupprecht, Thorsten Holz, and Christina Pöpper. 2019. LTE Security Disabled—Misconfiguration in Commercial Networks. In 12th ACM Conference on Security and Privacy in Wireless and Mobile Networks (WiSec ’19), May 15–17, 2019, Miami, FL, USA. ACM, New York, NY, USA, 6 pages. https://doi.org/10.1145/3317549.3324927

This software enhances [srsLTE](https://github.com/srslte/srsLTE)'s User Equipment (UE) component `srsUE` with a mode for testing LTE networks.

srsLTE is a free and open-source LTE software suite developed by SRS (www.softwareradiosystems.com). srsLTE is released under the AGPLv3 license and uses software from the OpenLTE project (http://sourceforge.net/projects/openlte) for some security functions and for RRC/NAS message parsing.

## Disclaimer

This software is intended to be used by operators to check their own networks, or with operator permission. We cannot guarantee that it doesn't cause disturbance if used improperly.

Features
--------------
* connect to LTE networks with SIM card
* Snow3G, AES and ZUC security algorithms
* NULL-algorithm support
* automatically test which security algorithms the network accepts


Hardware
--------

We currently base on the srsLTE release 18.06, which should support USRP, BladeRF and LimeSDR. LimeSDR mini support was added in later releases and is not included here, yet.

We have tested the following hardware: 
 * USRP B210

Accessing commercial networks requires a SIM card and a `pcsc` compatible SIM card reader.

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
Note that depending on your flavor and version of Linux, the actual package names may be different.

* Optional requirements: 
  * srsgui:              https://github.com/srslte/srsgui - for real-time plotting.
  * libpcsclite-dev:     https://pcsclite.apdu.fr/ - for accessing smart card readers

* RF front-end driver:
  * UHD:                 https://github.com/EttusResearch/uhd
  * SoapySDR:            https://github.com/pothosware/SoapySDR
  * BladeRF:             https://github.com/Nuand/bladeRF

Download and build srsLTE: 
```
git clone https://github.com/mrlnc/srsUE-test-network-security.git
cd srsLTE
mkdir build
cd build
cmake ../
make
```
The binary is located at `build/srsue/src/srsue`.

Execution Instructions
----------------------

The srsUE application includes an example configuration file
that should be copied and modified to meet the system configuration.
By default, all applications will search for config files in the user's home
directory (~/.srs) upon startup.

Note that you have to execute the applications with root privileges to enable
real-time thread priorities and to permit creation of virtual network interfaces.

### srsUE

