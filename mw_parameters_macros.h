// ---------------------------------------
// Boilerplate macros
// ---------------------------------------


// ------------------------------------------------------
// Automatically generate the plugin boilerplate (TODO)
// ------------------------------------------------------
#define MW_PLUGIN(PLUGIN_NAME)                                              \
  class PLUGIN_NAME##_plugin {                                              \
    public:                                                                 \
      static const int a = 4;                                               \
  };                                                                        \
  namespace mw                                


// ------------------------------------------------------
// Open an inner class for specifying a strongly
// typed argument list
// ------------------------------------------------------

#define BEGIN_MW_PARAMETERS                                                 \
  class parameters :  public MWBaseParameters {                             \
    public:                                                                 \
      parameters() : MWBaseParameters(){ }                                  \
      virtual ~parameters(){ }                                              \
      static void id(){}                                                    \
      static vector<MWParameterDescription> getParameters(){                \
        return MWBaseParameters::getParameters(&id);                        \
      }                                                                     \
      static shared_ptr<parameters> populate(map<string, string> args,      \
                                      ComponentRegistry *reg){              \
        return MWBaseParameters::populate<parameters>(args,reg);            \
      }


// ------------------------------------------------------
// Macros for the individual parameter fields, with a 
// meta-registration call
// ------------------------------------------------------

#define MW_PARAMETER(NAME, TYPE, DEFAULT_VAL)  \
        MW_REQ_PARAM(NAME, TYPE, DEFAULT_VAL)

#define MW_REQ_PARAM(NAME, TYPE, DEFAULT_VAL)  \
        MW_PARAMETER_ENTRY(NAME, TYPE, DEFAULT_VAL, true)

#define MW_OPT_PARAM(NAME, TYPE, DEFAULT_VAL) \
        MW_PARAMETER_ENTRY(NAME, TYPE, DEFAULT_VAL, false)
         
#define MW_PARAMETER_ENTRY(NAME, TYPE, DEFAULT_VAL, REQUIRED)               \
  public:                                                                   \
    TYPE NAME;                                                              \
    static void static_setter_##NAME(shared_ptr<MWBaseParameters> _p,       \
                                     string val,                            \
                                     ComponentRegistry* reg){               \
        shared_ptr<parameters> p =                                          \
            dynamic_pointer_cast<parameters, MWBaseParameters>(_p);         \
        p-> NAME = mw_cast<TYPE>(val, reg);                                 \
    }                                                                       \
    static void register_parameter_##NAME (){                               \
        parameters::registerParameter    (&id,                              \
                                          #NAME,                            \
                                          &static_setter_##NAME,            \
                                          DEFAULT_VAL,                      \
                                          REQUIRED);                        \
    }                                                                       \
    meta_hook <&register_parameter_##NAME> hook_##NAME;                                                                                                                                         


// ------------------------------------------------------
// Convenience macro for defining the 'signature' of the component 
// ------------------------------------------------------

#define MW_SIGNATURE(SIG)                                                   \
  static std::string getSignature(){                                        \
    std::string signature(SIG);                                             \
    return signature;                                                       \
  }

// ------------------------------------------------------
// Close out the nested parameters class
// and define a related glue method
// ------------------------------------------------------

#define END_MW_PARAMETERS                                                   \
  };                                                                        \
  public:                                                                   \
  static shared_ptr<Component> createComponent(map<string,string> args,     \
                                      ComponentRegistry *reg){              \
    shared_ptr<parameters> p = parameters::populate(args,reg);              \
    return createComponent(p);                                              \
  }  

// ------------------------------------------------------
// The sole purpose of this macro is to demarcate that 
// there be dragons
// ------------------------------------------------------
#define MW_PARAMETERS  shared_ptr<parameters>

