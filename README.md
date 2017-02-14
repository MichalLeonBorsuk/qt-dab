==================================================================
Qt-DAB
==================================================================
Qt-DAB is a Software for Windows, Linux and Raspberry Pi for Digital Audio Broadcasting (DAB and DAB+).

------------------------------------------------------------------
Table of Contents
------------------------------------------------------------------

* [Introduction](#introduction)
* [Features](#features)
* Installation
 * [Windows](#windows)
 * [Ubuntu Linux](#ubuntu-linux)
  - [Configuring using the qt-dab.pro file](#configuring-using-the-qt-dabpro-file)
  - [Configuring using CMake](#configuring-using-cmake)
  - [Qt](#qt)
 * [Raspberry PI](#raspberry-pi)

![Qt-DAB with SDR file loaded](/screenshot_qt-dab.png?raw=true)

------------------------------------------------------------------
Features
------------------------------------------------------------------

* DAB (mp2) and DAB+ (HE-AAC v1, v2 and LC-AAC) decoding
* Slideshow
* Dynamic Label (DLS) 
* Both European bands supported: 
 * VHF Band III
 * L-Band 
* Spectrum view (incl. constellation diagram)
* Scanning function (scan the subsequent channels in the selected band until a channel is encountered where a DAB signal is detected)
* Detailled information for selected service (SNR, bitrate, frequency, ensemble name, ensemble ID, subchannel ID, protection level, CPU usage, language, 4 quality bars)
* Dumping of the complete DAB channel (produces large raw files!) and playing them again later
* Saving audio as wave file
* Supports various inputs from Airspy, Airspy mini, SDR DAB sticks (RTL2838U or similar), SDRplay and prerecorded dump (*.raw and *.sdr) 
 
Not implemented:

* DMB (Audio and Video)
* Other bands than used for terrestrical broadcasting 
* HackRF


------------------------------------------------------------------
Introduction
------------------------------------------------------------------

![Qt-DAB with SDR file loaded](/screenshot_qt-dab.png?raw=true)

Qt-DAB is the result of merging the dab-rpi and the sdr-j-dab programs of the
author. It became more and more complex to maintain different versions: 
modifications made in one version, did not always end up in the other versions so the
versions started to diverge.

Since furthermore a separate "command line only" version was (is being) developed 
(a version not using Qt at all), while much of the sources is also used in the 
development of a version handling ETI files, there was a real need to
reorganize.

I decided to merge the dab-rpi and sdr-j-dab version and rename
the result - to distinguish from the Qt-free version -  Qt-DAB.

The Qt-free version, the "command line only" version,  is named "dab-cmdline"
and has its own repository.

The software - both the Qt-DAB and the dab-cmdline version - supports decoding 
of terrestrial DAB and DAB+ reception with as input the  samplestream from either 
an AIRSPY, a SDRplay, a dabstick (rtl_sdr), a rtl_tcp server.

The Qt-DAB version also supports input from a (prerecorded) file (*.sdr, which
obviously provides the opportunity of dumping the input into a file). 

Since the Qt-DAB version has to run on a headless RPI 2, using the home WiFi,
the spectrum display, showing the spectrum and the constellation over the WiFi,
can be left out of the configuration. 

Again, as the Qt-DAB version has to run on a headless RPI 2,
an option is included to configure the sound output to deliver its
samples through a TCP connection.

=======
------------------------------------------------------------------
Windows
------------------------------------------------------------------

There is an executable to be found under https://github.com/JvanKatwijk/qt-dab/releases

If you want to compile it yourself, please install Qt through their online installer, see https://www.qt.io/ 

------------------------------------------------------------------
Ubuntu Linux
------------------------------------------------------------------

For generating an executable under Ubuntu, you can put the following
commands into a script. 

1. Fetch the required components
   
		sudo apt-get update
		sudo apt-get install qt4-qmake build-essential g++
		sudo apt-get install libsndfile1-dev qt4-default libfftw3-dev portaudio19-dev 
		sudo apt-get install libfaad-dev zlib1g-dev rtl-sdr libusb-1.0-0-dev mesa-common-dev 
		sudo apt-get install libgl1-mesa-dev libqt4-opengl-dev libsamplerate-dev libqwt-dev
		cd

2. Fetch the required libraries 

	a) Assuming you want to use a dabstick as device, fetch a version of the library for the dabstick
 
		wget http://sm5bsz.com/linuxdsp/hware/rtlsdr/rtl-sdr-linrad4.tbz
		tar xvfj rtl-sdr-linrad4.tbz 
		cd rtl-sdr-linrad4
   		sudo autoconf
		sudo autoreconf -i
		./configure --enable-driver-detach
		make
		sudo make install
		sudo ldconfig
		cd
   
	b) Assuming you want to use an Airspy as device, fetch a version of the 
	  library for the Airspy
   
		sudo apt-get install build-essential cmake libusb-1.0-0-dev pkg-config
		wget https://github.com/airspy/host/archive/master.zip
		unzip master.zip
		cd host-master
		mkdir build
		cd build
		cmake ../ -DINSTALL_UDEV_RULES=ON
		make
		sudo make install
		sudo ldconfig
   
	 Clean CMake temporary files/dirs:

		cd host-master/build
		rm -rf *
   

3. Get a copy of the Qt-DAB sources

		git clone https://github.com/JvanKatwijk/qt-dab.git
		cd qt-dab

4. Edit the qt-dab.pro file for configuring the supported devices and other 
   options. Comment the respective lines out if you don't own an Airspy (mini) or an SDRplay.

5. If DAB spectrum should be displayed, check the installation path to qwt. If you were downloading it from  http://qwt.sourceforge.net/qwtinstall.html please mention the correct path in qt-dab.pro file: 

		INCLUDEPATH += /usr/local/include  /usr/local/qwt-6.1.3

6. Build and make

		qmake qt-dab.pro
		make
		
  You could also use QtCreator, load the qt-dab.pro file and build the executable.
  
  Remark: The excutable file can be found in the sub-directory linux-bin. A make install command is not implemented.


------------------------------------------------------------------
Configuring using the qt-dab.pro file
------------------------------------------------------------------

Options in the configuration are:

a) select or unselect devices

b) select the output: soundcard or tcp connection

c) select or unselect basic MSC data handling

Adding or removing from the configuration is in all cases by commenting or 
uncommenting a line in the configuration file.

Comment the lines out by prefixing the line with a #
in the qt-dab.pro file (section "unix") for the device(s)
you want to exclude in the configuration.

	CONFIG          += dabstick
	CONFIG          += sdrplay-exp
	CONFIG          += rtl_tcp
	CONFIG          += airspy

Input from prerecorded files is always part of the configuration.

Having the spectrum and the constellation shown, uncomment

	CONFIG          += spectrum  

For selecting the output to be sent to a RCP port, uncomment

	CONFIG         += tcp-streamer         # use for remote listening

For showing some information on the selected program uncomment

	DEFINES         += TECHNICAL_DATA

For basic MSC data handling, i.e. pad handling etc, uncomment

	DEFINES         += MSC_DATA__           # use at your own risk

The sourcetree contains a directory "sound-client", that contains
sources to generate a simple "listener" for remote listening.


------------------------------------------------------------------
Configuring using CMake
------------------------------------------------------------------

The CMakeLists.txt file has as defaults all devices and the spectrum switched
off.
You can select a device (or more devices) without altering the CMakeLists.txt
file, but by passing on definitions to the command line.

An example

	cmake .. -DDABSTICK=ON -DRTLTCP=ON -DSPECTRUM=ON
	
will generate a makefile with both support for the dabstick and
for the remote dabstick (using the rtl_tcp connection) and for
the spectrum in the configuration.

Devices that can be selected this way are, next to the dabstick and
rtl_tcp, the sdrplay and the airspy.

For other options, see the CMakeLists.txt file.

Note that CMake expects Qt5 to be installed.

------------------------------------------------------------------
Raspberry PI
------------------------------------------------------------------

The Qt-DAB software runs pretty well on my RPI-2. The average
load on the 4 cores is somewhat over 60 percent.

However, note that the arch system, the one I am running,
provides the gcc 6.XX compilers rather than the GCC 4.9 on Jessie. 
On Jessie the load is higher, up to 75 or 80 percent.

One remark: getting "sound" is not always easy. Be certain that you have
installed the alsa-utils, and that you are - as non-root user - able
to see devices with aplay -L

In arch, it was essential to add the username to the group "audio".

------------------------------------------------------------------
Qt
------------------------------------------------------------------

The software uses the Qt library and - for the spectrum and the constellation
diagram - the qwt library.

The CMakeLists.txt assumes Qt5, if you want to use Qt4, and you want
to have the spectrum in the configuration, be aware of the binding 
of the qwt library (i.e. Qt4 and a qwt that uses Qt5 does not work well)





============================================================================


	Copyright (C)  2013, 2014, 2015, 2016, 2017
	Jan van Katwijk (J.vanKatwijk@gmail.com)
	Lazy Chair Programming

	The Qt-DAB software is made available under the GPL-2.0.
	Qt-DAB is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.


