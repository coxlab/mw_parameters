#ifndef MW_CONVERSION_HELPERS_H_
#define MW_CONVERSION_HELPERS_H_


#include <string>
#include <boost/lexical_cast.hpp>
#include <MWorksCore/ParsedColorTrio.h>
#include <MWorksCore/ComponentRegistry.h>
#include <MWorksCore/GenericVariable.h>
#include <MWorksCore/Stimulus.h>
#include "mw_abbreviations.h"
  
namespace mw{

  using namespace std;
  using namespace boost;

  // -----------------------------------------
  // Conversion Helpers
  // -----------------------------------------

  // -----------------------------------------
  // <typename T>
  // Generic converter
  // This should catch most of the numeric casts
  // This will throw if an appriate conversion is unavailable
  // -----------------------------------------
  template <typename T>
  T mw_cast(const string& s, 
            ComponentRegistry* reg){
            //shared_ptr<ComponentRegistry> reg){
    cerr << "converting: " << s << endl;
    
    T val; // the return val
    
    // Try to cast the string using lexical_cast
    try {
        val = lexical_cast<T>(s);
    } catch (bad_lexical_cast& e){
        // That didn't work
        // Maybe it's a variable?
        VariablePtr var = mw_cast<VariablePtr>(s, reg);
        val = (T)(var->getValue());
    }
    
    return val;
  }

  // -----------------------------------------
  // <string>
  // Pass a string through unchanged
  // -----------------------------------------
  template <>
  string mw_cast<string>(const string& s,
                         ComponentRegistry* reg);
                          //shared_ptr<ComponentRegistry> reg);  
  // -----------------------------------------
  // <VariablePtr>
  // Get a pointer to a variable from the component registry
  // -----------------------------------------
  template <>
  VariablePtr mw_cast<VariablePtr>(const string& s,
                                   ComponentRegistry* reg);
                                  //shared_ptr<ComponentRegistry> reg);                                      
  // -----------------------------------------
  // <StimulusPtr>
  // Get a pointer to a stimulus from the component registry
  // -----------------------------------------
  template <>
  StimulusPtr mw_cast<StimulusPtr>(const string& s,
                                   ComponentRegistry* reg);
                                  //shared_ptr<ComponentRegistry> reg);
  template <>
  ColorTriple mw_cast<ColorTriple>(const string& s,
                                   ComponentRegistry* reg);
                                  //shared_ptr<ComponentRegistry> reg);

}

#endif
