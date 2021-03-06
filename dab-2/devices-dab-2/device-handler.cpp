#
/*
 *    Copyright (C) 2010, 2011, 2012
 *    Jan van Katwijk (J.vanKatwijk@gmail.com)
 *    Lazy Chair Computing
 *
 *    This file is part of the sdrplayDab program
 *    sdrplayDab is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    sdrplayDab is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with sdrplayDab; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * 	Default (void) implementation of
 * 	virtual input class
 */
#include	"device-handler.h"
#include	"dab-processor.h"

	deviceHandler::deviceHandler	(void) {
}

	deviceHandler::~deviceHandler	(void) {
}

bool	deviceHandler::restartReader	(int32_t f) {
	(void)f;
	return false;
}

void	deviceHandler::stopReader	(void) {
}

void	deviceHandler::resetBuffer	(void) {
}

int32_t	deviceHandler::getVFOFrequency	(void) {
	return -1;
}

QString	deviceHandler::deviceName	() {
	return "";
}

void	deviceHandler::set_Values	(int freq, float lowVal, float highVal) {
	handle_Value (freq, lowVal, highVal);
}

void	deviceHandler::handle_Value	(int freq, float lowVal, float highVal) {
	fprintf (stderr, "%d %f %f\n", freq, lowVal, highVal);
	(void)freq; (void)lowVal; (void)highVal;
}

