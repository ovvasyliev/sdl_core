### Use Case 1: RegisterAppInterface - alternative flow (success = true; resultCode ≠ success).



#### :one: **Alternative flow - WRONG_LANGUAGE languageDesired.**
If SDL receives RegisterAppInterface RPC from mobile app with languageDesired different from current VR+TTS language on HMI, SDL registers application successfuly and return resultCode WRONG_LANGUAGE and success:"true" value to mobile application.    
**_Precondition:_** An application with appID is intended to be registered on SDL with languageDesired != TTS+VR current on HMI.    
**_Steps:_** appID->RegisterAppInterface(params, languageDesired).    
**_Expected:_** SDL->appID->(WRONG_LANGUAGE, success:true) RegisterAppInterface().
    
#### :two: **Alternative flow - WRONG_LANGUAGE hmiDisplayLanguageDesired.**
In case SDL receives RegisterAppInterface RPC from mobile app with `<hmiDisplayLanguageDesired>` different from current display language on HMI, SDL registers application successfuly and return resultCode WRONG_LANGUAGE and success:"true" value to mobile application.    
**_Precondition:_** An application with appID is intended to be registered on SDL with hmiDisplayLanguageDesired != (current display language on HMI).   
**_Steps:_** appID->RegisterAppInterface(params, hmiDisplayLanguageDesired).   
**_Expected:_** SDL->appID->(WRONG_LANGUAGE, success:true) RegisterAppInterface().
