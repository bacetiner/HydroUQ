#ifndef SETTINGS_MPM_H
#define SETTINGS_MPM_H

/* *****************************************************************************
Copyright (c) 2016-2023, The Regents of the University of California (Regents).
All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the FreeBSD Project.

REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS 
PROVIDED "AS IS". REGENTS HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, 
UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

*************************************************************************** */

/**
 *  @author  fmckenna
 *  @date    2/2017
 *  @version 1.0
 *
 *  @section DESCRIPTION
 *
 *  This is the class providing the Settings Tab for the MPM application
 */

#include <SimCenterWidget.h>

class QJsonObject;
class SC_DoubleLineEdit;
class SC_IntLineEdit;
class SC_StringLineEdit;
class SC_CheckBox;
class SC_ComboBox;

class SettingsMPM : public SimCenterWidget
{
public:
    SettingsMPM(QWidget *parent = 0);
    virtual ~SettingsMPM();
    bool outputToJSON(QJsonObject &jsonObject);
    bool inputFromJSON(QJsonObject &jsonObject);

signals:

private:
  // domain settings
  SC_DoubleLineEdit *domainSizeX; // MPM background grid absolute max domain size
  SC_DoubleLineEdit *domainSizeY; 
  SC_DoubleLineEdit *domainSizeZ;  
  SC_CheckBox       *mirrorDomainX; // Mirror X- domain over YZ plane  
  SC_CheckBox       *mirrorDomainY; // Mirror Y- domain over XZ plane  
  SC_CheckBox       *mirrorDomainZ; // Mirror Z- domain over XY plane 
  SC_DoubleLineEdit *gridCellSize; // MPM background grid cell size 
  
  // time settings
  SC_DoubleLineEdit *initialTime; // MPM simulation start time
  SC_DoubleLineEdit *duration; // MPM simulation duration, [initialTime, initialTime + duration]
  SC_DoubleLineEdit *timeStep; // MPM time step size 
  SC_DoubleLineEdit *cflNumber; // Courant-Friedrichs-Lewy number (typically 0.5), dt = CFL * dx / v_max
  SC_IntLineEdit    *framesPerSecond; // Number of frames per second for full animation output
  SC_ComboBox       *timeIntegration; // Time integration scheme, e.g., Explicit, Semi-implicit, etc.
  // external field settings
  SC_DoubleLineEdit *gravityX; 
  SC_DoubleLineEdit *gravityY;
  SC_DoubleLineEdit *gravityZ;

  // similitude scaling
  SC_CheckBox       *froudeScaling; // apply Froude scaling to length, velocity
  SC_CheckBox       *cauchyScaling; // apply Cauchy scaling to bulk modulus, stress, pressure
  SC_DoubleLineEdit *froudeLengthRatio; // ratio of model length to prototype length
  SC_DoubleLineEdit *froudeTimeRatio; // ratio of model length to prototype length
  SC_DoubleLineEdit *cauchyBulkRatio; // ratio of model bulk modulus to prototype bulk modulus

  // computational facility, CPU/GPU hardware, and precompiled ClaymoreUW software-hardware settings
  SC_ComboBox *hpc; // High-performance computing facility 
  SC_StringLineEdit *hpcCardBrand; // Ratio of double-precision to single-precision performance
  SC_StringLineEdit *hpcCardName; // GPU name
  SC_StringLineEdit *hpcCardArchitecture; // GPU architecture
  SC_IntLineEdit *hpcCardGlobalMemory; // GPU global memory (GB)
  SC_IntLineEdit *hpcCardComputeCapability; // GPU compute capability (sm_XY)
  SC_IntLineEdit *numGPUs; // Number of GPUs to use
  SC_IntLineEdit *modelsPerGPU; // Number of models to run per GPU
};

#endif // SETTINGS_DIGITAL_TWIN_H
