### Use Case 1: RegisterAppInterface - alternative flow (success = true; resultCode ≠ success).

#### 1. **Alternative flow - WRONG_LANGUAGE languageDesired.**
If SDL receives RegisterAppInterface RPC from mobile app with languageDesired different from current VR+TTS language on HMI, SDL registers application successfuly and return resultCode WRONG_LANGUAGE and success:"true" value to mobile application.    
**_Precondition:_** An application with appID is intended to be registered on SDL with languageDesired != TTS+VR current on HMI.    
**_Steps:_** appID->RegisterAppInterface(params, languageDesired).    
**_Expected:_** SDL->appID->(WRONG_LANGUAGE, success:true) RegisterAppInterface().
    
#### 2. **Alternative flow - WRONG_LANGUAGE hmiDisplayLanguageDesired.**
In case SDL receives RegisterAppInterface RPC from mobile app with `<hmiDisplayLanguageDesired>` different from current display language on HMI, SDL registers application successfuly and return resultCode WRONG_LANGUAGE and success:"true" value to mobile application.    
**_Precondition:_** An application with appID is intended to be registered on SDL with hmiDisplayLanguageDesired != (current display language on HMI).   
**_Steps:_** appID->RegisterAppInterface(params, hmiDisplayLanguageDesired).   
**_Expected:_** SDL->appID->(WRONG_LANGUAGE, success:true) RegisterAppInterface().


#### 3. **Alternative flow - WRONG_LANGUAGE.**
**_Preconditions:_** An application with appID is intended to be registered on SDL with:   
 hmiDisplayLanguageDesired != (current display language on HMI) or   
 with languageDesired != TTS+VR current on HMI.   
**_Steps:_** appID->RegisterAppInterface(params, hmiDisplayLanguageDesired) or   
appID->RegisterAppInterface(params, languageDesired).   
**_Expected:_** SDL->appID->(WRONG_LANGUAGE, success:true) RegisterAppInterface().

**3.1.** If mobile app registers at the **very first** ignition cycle (or after Master Reset) and SDL does NOT receive at least one UI and\or [VR or TTS] GetLanguage_response from HMI yet (SDL\`s watchdog timeout is NOT expired yet)
and UI and\or [VR or TTS] languages from RegisterAppInterface does NOT match to default UI and\or [VR or TTS] languages from 'HMI_capabilities.json' file
SDL responds RegisterAppInterface (WRONG_LANGUAGE, success:true, `<default_UI_languages>`, `<default_VR_or_TTS_languages>`) to mobile app.

**3.2.** If mobile app registers at the next ignition cycle (**not first**)
and SDL does NOT receive at least one UI and\or [VR or TTS] GetLanguage_response from HMI yet (SDL\`s watchdog timeout is NOT expired yet)
and UI and [VR or TTS] languages from RegisterAppInterface does NOT match to UI and [VR or TTS] languages stored at 'app_info.dat' file
SDL responds RegisterAppInterface (WRONG_LANGUAGE, success:true, `<stored_UI_languages>`, `<stored_VR_or_TTS_languages>`) to mobile app.

#### 4. **Alternative flow - UNSUPPORTED_RESOURCE.**
**_Preconditions:_** application with appID is registered on SDL an RPC references a few components on HMI (UI and/or TTS and/or VR).    **_Steps:_** app->SDL: RPC(params)   
SDL->UI.RPC()   
SDL->VR.RPC()   
SDL->TTS.RPC()    
**_Observed:_** The one of the components returned UNSUPPORTED_RESOURCE:   
HMI->SDL: (UNSUPPORED_RESOURCE, info: "The issue was caused by..."):UI.RPC()   
HMI->SDL:SUCCESS: VR.RPC()   
HMI->SDL:SUCCESS: TTS.RPC()   
**_Expected:_** SDL->appID: (UNSUPPORTED_RESOURCE, success:true):RPC().

#### 5. **Alternative flow - WARNINGS (RegisterAppInterface).**
If SDL receives _RegisterAppInterface_ RPC from mobile app with appHMIType(s) _**partially or not coincided**_ with current non-empty data stored in PolicyTable for the specified application, SDL:   
1) allows appHMIType(s) registered in PT ONLY.   
2) registers an application successfuly and return resultCode "WARNINGS, success: true" value.   
3) provides an additional information to mobile application in the "info" parameter about appHMITypes received not listed in PT.   
**_Preconditions:_** Local PT has several values in "AppHMIType" field in 'value-of-appID-the-app-has-registered-with' subsection of "app_policies" section.   
**_Steps:_** Mobile app with appID sends RegisterAppInterface with several values of AppHMIType, all types do NOT exist in local PT or/ only some types exist in local PT:   
app->SDL: ResgiterAppInterface(params, AppHMIType[`<appHMIType_1>`, `<appHMIType_2>`]).    
**_Expected:_**   
1) SDL allows AppHMIType that exists in local PT for appID.   
2) SDL disallows AppHMIType that does not exist in local PT for appID.   
3) SDL->apps: (WARNINGS, success: true, 'info': "all HMI types that are got in request but disallowed: `<appHMIType_1>`, `<appHMIType_2>`):RegisterAppInterface().
