/*
 *  mw_conversion_helpers.cpp
 *  DynamicRandomDots
 *
 *  Created by David Cox on 2/1/11.
 *  Copyright 2011 Harvard University. All rights reserved.
 *
 */

#include "mw_conversion_helpers.h"
#include <string>
#include <MWorksCore/ComponentRegistry.h>
 

namespace mw {

using namespace std;

// -----------------------------------------
// <string>
// Pass a string through unchanged
// -----------------------------------------
template <>
string mw_cast<string>(const string& s,
                       ComponentRegistryPtr reg){
    string newstr(s);
    return newstr;
}

// -----------------------------------------
// <VariablePtr>
// Get a pointer to a variable from the component registry
// -----------------------------------------
template <>
VariablePtr mw_cast<VariablePtr>(const string& s,
                                 ComponentRegistryPtr reg){
    cerr << "converting variable: " << s << endl;
    VariablePtr return_var = reg->getVariable(s);
    if(return_var == NULL){
      throw UnknownVariableException(s);
    }
    
    return return_var;
}

// -----------------------------------------
// <StimulusPtr>
// Get a pointer to a stimulus from the component registry
// -----------------------------------------
template <>
StimulusPtr mw_cast<StimulusPtr>(const string& s,
                                 ComponentRegistryPtr reg){
    cerr << "converting stimulus: " << s << endl;
    return reg->getStimulus(s);
}


template <>
ColorTriple mw_cast<ColorTriple>(const string& s,
                                 ComponentRegistryPtr reg){
    ColorTriple color;
    
    // TODO: this PCT thing is kludgey
    ParsedColorTrio pct(reg, s);
    //ParsedColorTrio pct(reg.get(), s);
    color.r = pct.getR()->getValue();
    color.g = pct.getG()->getValue();
    color.b = pct.getB()->getValue();
    
    return color;
}

}
