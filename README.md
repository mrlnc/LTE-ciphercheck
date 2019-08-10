Security Algorithm Support in LTE Networks
========

LTE supports several modes for encryption and integrity protection. Both the mobile handset (User Equipment, UE) and the network must support the Snow3G and AES. Optionally, ZUC can be supported. Therefore, during connection establishment, the algorithms are negotiated between UE and network, until finally the network selects one algorithm to use. The "null"-algorithm EEA0 disables encryption, and null-integrity EIA0 completely bypasses LTE security and must *never* be selected by the network.

Commercial networks often do not follow the LTE standard. In a research paper ([PDF](https://www.infsec.ruhr-uni-bochum.de/media/infsec/veroeffentlichungen/2019/04/23/wisec19-final123.pdf)), we show that several operators allow non-encrypted and unprotected connections. Full read:
> Merlin Chlosta, David Rupprecht, Thorsten Holz, and Christina Pöpper. 2019. LTE Security Disabled—Misconfiguration in Commercial Networks. In 12th ACM Conference on Security and Privacy in Wireless and Mobile Networks (WiSec ’19), May 15–17, 2019, Miami, FL, USA. ACM, New York, NY, USA, 6 pages. https://doi.org/10.1145/3317549.3324927

This repository contains the software used for the research paper. It enhances [srsLTE](https://github.com/srslte/srsLTE)'s User Equipment (UE) component `srsUE` with a mode for testing LTE networks.

## Disclaimer

This software is intended to be used by operators to check their own networks, or with operator permission. We cannot guarantee that it doesn't cause disturbance if used improperly.

## Support

Drop me a message if you are interested in this project or other network tests: merlin.chlosta+github@rub.de

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

Check out the instructions at [srsLTE](https://github.com/srslte/srsLTE). The binary is located at `build/srsue/src/srsue` for this project is

srsLTE is a free and open-source LTE software suite developed by SRS (www.softwareradiosystems.com). srsLTE is released under the AGPLv3 license and uses software from the OpenLTE project (http://sourceforge.net/projects/openlte) for some security functions and for RRC/NAS message parsing.
