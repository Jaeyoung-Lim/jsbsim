/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

 Header:       FGFCSComponent.h
 Author:       Jon S. Berndt
 Date started: 05/01/2000

 ------------- Copyright (C)  -------------

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU General Public License as published by the Free Software
 Foundation; either version 2 of the License, or (at your option) any later
 version.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 details.

 You should have received a copy of the GNU General Public License along with
 this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 Place - Suite 330, Boston, MA  02111-1307, USA.

 Further information about the GNU General Public License can also be found on
 the world wide web at http://www.gnu.org.

HISTORY
--------------------------------------------------------------------------------

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
SENTRY
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#ifndef FGFCSCOMPONENT_H
#define FGFCSCOMPONENT_H

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
INCLUDES
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#ifdef FGFS
#  include <simgear/compiler.h>
#endif

#include <string>
#include <vector>
#include <FGJSBBase.h>
#include <input_output/FGPropertyManager.h>
#include <input_output/FGXMLElement.h>

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
DEFINITIONS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#define ID_FCSCOMPONENT "$Id: FGFCSComponent.h,v 1.4 2005/06/18 14:50:01 jberndt Exp $"

using std::string;

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
FORWARD DECLARATIONS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

namespace JSBSim {

class FGFCS;

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
CLASS DOCUMENTATION
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/** Base class for JSBSim Flight Control System Components.
    The Flight Control System (FCS) for JSBSim consists of the FCS container
    class (see \URL[FGFCS]{FGFCS.html}), the FGFCSComponent base class, and the
    component classes from which can be constructed a string, or channel. See:

    - FGSwitch
    - FGGain
    - FGKinemat
    - FGFilter
    - FGDeadBand
    - FGSummer
    - FGGradient

    @author Jon S. Berndt
    @version $Id: FGFCSComponent.h,v 1.4 2005/06/18 14:50:01 jberndt Exp $
    @see Documentation for the FGFCS class, and for the configuration file class
*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
CLASS DECLARATION
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

class FGFCSComponent : public FGJSBBase
{
public:
  /// Constructor
  FGFCSComponent(FGFCS* fcs, Element* el);
  /// Destructor
  virtual ~FGFCSComponent();

  virtual bool Run(void);
  virtual void SetOutput(void);
  inline double GetOutput (void) const {return Output;}
  inline FGPropertyManager* GetOutputNode(void) { return OutputNode; }
  inline string GetName(void) const {return Name;}
  inline string GetType(void) const { return Type; }
  virtual double GetOutputPct(void) const { return 0; }

protected:
  FGFCS* fcs;
  FGPropertyManager* PropertyManager;
  FGPropertyManager* treenode;
  FGPropertyManager* OutputNode;
  FGPropertyManager* ClipMinPropertyNode;
  FGPropertyManager* ClipMaxPropertyNode;
  vector <FGPropertyManager*> InputNodes;
  vector <float> InputSigns;
  string Type;
  string Name;
  double Input;
  double Output;
  double clipmax, clipmin;
  bool IsOutput;
  bool clip;

  void Clip(void);
  virtual void bind();
  FGPropertyManager* resolveSymbol(string token);

  virtual void Debug(int from);
};

} //namespace JSBSim

#include "../FGFCS.h"

#endif
