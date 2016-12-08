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
