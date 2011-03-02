#ifndef MW_ABBREV_H_
#define MW_ABBREV_H_

/*
 *  mw_abbreviations.h
 *  DynamicRandomDots
 *
 *  Created by David Cox on 2/1/11.
 *  Copyright 2011 Harvard University. All rights reserved.
 *
 */

#include <MWorksCore/GenericVariable.h>
#include <MWorksCore/Stimulus.h>


namespace mw {


    typedef shared_ptr<Variable>              VariablePtr;
    typedef shared_ptr<StimulusNode>          StimulusPtr;
    typedef ComponentRegistry*                ComponentRegistryPtr;
    
    typedef struct  ColorTriple_t{
        double r;
        double g;
        double b;
    } ColorTriple;
    

}


#endif