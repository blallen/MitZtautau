// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIhomedIballendIcmsdIcmsswdI041dICMSSW_7_4_6dItmpdIslc6_amd64_gcc491dIMitZtautauMods_LinkDefDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "MitZtautau/Mods/interface/ZtautauMod.h"

// Header files passed via #pragma extra_include

namespace mithep {
   namespace ROOT {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *mithep_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("mithep", 0 /*version*/, "MitAna/DataCont/interface/BaseCollection.h", 14,
                     ::ROOT::DefineBehavior((void*)0,(void*)0),
                     &mithep_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *mithep_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}

namespace ROOT {
   static void *new_mithepcLcLZtautauMod(void *p = 0);
   static void *newArray_mithepcLcLZtautauMod(Long_t size, void *p);
   static void delete_mithepcLcLZtautauMod(void *p);
   static void deleteArray_mithepcLcLZtautauMod(void *p);
   static void destruct_mithepcLcLZtautauMod(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::mithep::ZtautauMod*)
   {
      ::mithep::ZtautauMod *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::mithep::ZtautauMod >(0);
      static ::ROOT::TGenericClassInfo 
         instance("mithep::ZtautauMod", ::mithep::ZtautauMod::Class_Version(), "MitZtautau/Mods/interface/ZtautauMod.h", 16,
                  typeid(::mithep::ZtautauMod), DefineBehavior(ptr, ptr),
                  &::mithep::ZtautauMod::Dictionary, isa_proxy, 4,
                  sizeof(::mithep::ZtautauMod) );
      instance.SetNew(&new_mithepcLcLZtautauMod);
      instance.SetNewArray(&newArray_mithepcLcLZtautauMod);
      instance.SetDelete(&delete_mithepcLcLZtautauMod);
      instance.SetDeleteArray(&deleteArray_mithepcLcLZtautauMod);
      instance.SetDestructor(&destruct_mithepcLcLZtautauMod);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::mithep::ZtautauMod*)
   {
      return GenerateInitInstanceLocal((::mithep::ZtautauMod*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::mithep::ZtautauMod*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace mithep {
//______________________________________________________________________________
atomic_TClass_ptr ZtautauMod::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *ZtautauMod::Class_Name()
{
   return "mithep::ZtautauMod";
}

//______________________________________________________________________________
const char *ZtautauMod::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::mithep::ZtautauMod*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int ZtautauMod::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::mithep::ZtautauMod*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *ZtautauMod::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::mithep::ZtautauMod*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *ZtautauMod::Class()
{
   if (!fgIsA) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::mithep::ZtautauMod*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace mithep
namespace mithep {
//______________________________________________________________________________
void ZtautauMod::Streamer(TBuffer &R__b)
{
   // Stream an object of class mithep::ZtautauMod.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(mithep::ZtautauMod::Class(),this);
   } else {
      R__b.WriteClassBuffer(mithep::ZtautauMod::Class(),this);
   }
}

} // namespace mithep
namespace ROOT {
   // Wrappers around operator new
   static void *new_mithepcLcLZtautauMod(void *p) {
      return  p ? new(p) ::mithep::ZtautauMod : new ::mithep::ZtautauMod;
   }
   static void *newArray_mithepcLcLZtautauMod(Long_t nElements, void *p) {
      return p ? new(p) ::mithep::ZtautauMod[nElements] : new ::mithep::ZtautauMod[nElements];
   }
   // Wrapper around operator delete
   static void delete_mithepcLcLZtautauMod(void *p) {
      delete ((::mithep::ZtautauMod*)p);
   }
   static void deleteArray_mithepcLcLZtautauMod(void *p) {
      delete [] ((::mithep::ZtautauMod*)p);
   }
   static void destruct_mithepcLcLZtautauMod(void *p) {
      typedef ::mithep::ZtautauMod current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::mithep::ZtautauMod

namespace {
  void TriggerDictionaryInitialization_MitZtautauMods_LinkDefDict_Impl() {
    static const char* headers[] = {
"MitZtautau/Mods/interface/ZtautauMod.h",
0
    };
    static const char* includePaths[] = {
"/home/ballen/cms/cmssw/041/CMSSW_7_4_6/src",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/lcg/root/6.02.00-odfocd4/include",
"/home/ballen/cms/cmssw/041/CMSSW_7_4_6/src/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
namespace mithep{class __attribute__((annotate("$clingAutoload$MitZtautau/Mods/dict/MitZtautauModsLinkDef.h")))  ZtautauMod;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "MitZtautau/Mods/interface/ZtautauMod.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"mithep::ZtautauMod", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("MitZtautauMods_LinkDefDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_MitZtautauMods_LinkDefDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_MitZtautauMods_LinkDefDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_MitZtautauMods_LinkDefDict() {
  TriggerDictionaryInitialization_MitZtautauMods_LinkDefDict_Impl();
}
