### Use Case 1: RegisterAppInterface - alternative flow (FAILED).

#### :one: **Alternative flow - INVALID_DATA.**   

**_Preconditions:_**   
1) connection, session and service \#7 are initialized for the application
2) the request one of the defined in [mobile API]() is intended to be sent from mobile applicaton with appID.   
**1.1.** If the request comes to SDL with wrong json syntax, SDL responds with resultCode "INVALID_DATA" and success:"false" value.   
**1.2.** If request comes to SDL with empty value "" in "String" type parameters (including parameters of the structures), SDL responds with resultCode "INVALID_DATA" and success:"false" value.   
:grey_exclamation: _Exception:_ Sending empty value "" in String type parameters in textFields of Show/ShowConstantTBT request + "text" parameter SoftButton () for SoftButtonType=IMAGE.   
**1.3.** If the request comes to SDL with wrong type parameters (including parameters of the structures), SDL must respond with resultCode "INVALID_DATA" and success:"false" value.   
:grey_exclamation: _Exception:_ Sending enum values as "Integer" ones must be process successfully as the position number in the enum (in case not out of range, otherwise the rule above is applied).   
:book: _Example:_ sending "String" type values instead of "Integer" ones.   
**1.4.** If the request comes without parameters defined as mandatory in mobile API, SDL responds with resultCode "INVALID_DATA" and success:"false" value.   
:grey_exclamation: _Exception:_ For _Show_ request which contains all parameters as _mandatory=false_, SDL returns INVALID data if the request doesn't contain any parameters at all.   
**1.5.** If the request comes with '\n' and-or '\t' and-or 'whitespace'-as-the-only-symbol(s) at any "String" type parameter in the request structure, SDL _must_ respond with resultCode "INVALID\_DATA" and success: "false" value.   
:grey_exclamation: _Exception 1:_ "\n and \t" are allowed for ScrollableMessage "text" parameter.   
:grey_exclamation: _Exception 2:_ The characters of "#", "-", "\_", "(", ")" must be allowed by SDL, (that is, string-type param coming with one of "#", "-", "\_", "(", ")" should be transferred by SDL to HMI).

**_Steps:_**  appID->SDL: Request(parameters)

**_Expected:_**  SDL->appID: (INVALID_DATA, success:"false"): ResponseToTheRequest()


#### :two: **Alternative flow - DUPLICATE_NAME.**
When SDL receives RegisterAppInterface RPC from mobile app, SDL must validate "appName" at first and validate the "appID" at second.   
**_Preconditions:_**   
a. SDL and HMI are running.   
b. app_1 is registered with ``<appName_1>`` and ``<appID1>`` and ``<vrSynonim_1>`` with SDL.   
**_Steps:_**  
Another app_2 is registering on SDL:   
1) app_2 >SDL: RegisterAppInterface
{appName_2= `<VrSynonim_1>`, VrSynonim_2, params}
or   
2) app_2 (different app, not app_1 within the same session)->SDL: RegisterAppInterface
{`<appName_1>`, `<appID_1>`, params}
or   
3) app_2->SDL: RegisterAppInterface
{`<appName_1>`, `<appID_2>`, params}
or   
4) app_2->SDL: RegisterAppInterface {appName_1, appID_1, params}
or   
5) app_2->SDL:RegisterAppInterface (appName_2, appID_1, params).   
**_Expected:_**   
1) SDL->app_2: RegisterAppInterface (DUPLICATE_NAME, success: "false")
or   
2) SDL->app_2: RegisterAppInterface (DISALLOWED, success: false)


#### :three: **Alternative flow - DISALLOWED.**
PoliciesManager disallows the app\`s registration IF the app\`s nickname does not match those listed in Policy Table under the appID this app registers with.   
**_Precondition_**:   
a. SDL and HMI are running.
b. Local Policy Table has section `<appID>`.
c. section `<appID>` has sub-section "nicknames": ["SyncProxyTester"].   
**_Steps:_**   
1) Start mobile app with the name "ABCD" and `<appID>` (=value in PT).   
2) app->SDL: RegisterAppInterface(appName: "ABCD", appID, params).   
**_Expected:_**
SDL->app: RegisterAppInterface(DISALLOWED, success:false).


#### :four: **Alternative flow - OUT_OF_MEMORY.**
In case there is no free disk space for the new application registering even if the app’s disk quotes are not exceeded completely, SDL must return OUT_OF_MEMORY response code and "success":"false" value.   
:information_source: _Information:_ "AppDirectoryQuota" parameter in smartDeviceLink.ini file must define a folder size limitation in bytes for any application on SDL.   
**_Preconditions:_**   
a. M, N are the whole numbers.   
b. AppDirectoryQuota=N.   
c. N\*(M-1)\<AllowedDiscSpaceToWritebySDL\<N\*M.
d. There're (M-1) apps connected.   
**_Steps:_**
application M is trying to register:
app_M->SDL: RegisterAppInterface(params)   
**_Expected:_**
SDL->app_M->(OUT_OF_MEMORY, success:false) RegisterAppInterface().

#### :five: **Alternative flow - APPLICATION_REGISTERED_ALREADY.**
**_Preconditions:_**   
1) app_1 is SDL-enabled and successfully opens session with SDL.   
2) app_1 successfully registers on SDL.   
**_Steps:_** app_1 -> SDL: RegisterAppInterface (params).   
**_Expected:_**   
SDL -> app_1: RegisterAppInterface (APPLICATION_REGISTERED_ALREADY, success:false).   
SDL keeps session active and valid with this app.   

#### :six: **Alternative flow - UNSUPPORTED_VERSION.**
**6.1.** If HMI sends OnVehilceData_notification with;
-> 'gpsData'
and this structure is empty (has no parameters).   
SDL treats OnVehicleData_response as invalid log corresponding error internally
ignore received notification (thus, should NOT send this notification to mobile app(s)).

**_Preconditions:_**   
a. app successfully regiaters and running on SDL.   
b. app successfully subscribed to `<gpsData>`.   
**_Steps:_** HMI -> SDL: OnVehicleData (`<gpsData>`: []).   
**_Expected:_** SDL logs error internally and ignores received notification.

**6.2.** mobile app connects **over protocol v1** and sends RegisterAppInterface_request to SDL. SDL responds RegisterAppInterface (UNSUPPORTED_VERSION) to this mobile app.   
**_Preconditions:_** app connects over protocol v1   
**_Steps:_** app -> SDL: RegisterAppInterface (params).   
**_Expected:_** SDL -> app: RegisterAppinterface (UNSUPPORTED_VERSION)

#### :seven: **Alternative flow - WRONG_LANGUAGE.**
**_Preconditions:_** An application with appID is intended to be registered on SDL with:   
 hmiDisplayLanguageDesired != (current display language on HMI) or   
 with languageDesired != TTS+VR current on HMI.   
**_Steps:_** appID->RegisterAppInterface(params, hmiDisplayLanguageDesired) or   
appID->RegisterAppInterface(params, languageDesired).   
**_Expected:_** SDL->appID->(WRONG_LANGUAGE, success:true) RegisterAppInterface().


**7.1.** If mobile app registers at the **very first** ignition cycle (or after Master Reset) and SDL does NOT receive at least one UI and\or [VR or TTS] GetLanguage_response from HMI yet (SDL\`s watchdog timeout is NOT expired yet)
and UI and\or [VR or TTS] languages from RegisterAppInterface does NOT match to default UI and\or [VR or TTS] languages from 'HMI_capabilities.json' file
SDL responds RegisterAppInterface (WRONG_LANGUAGE, success:true, `<default_UI_languages>`, `<default_VR_or_TTS_languages>`) to mobile app.

**7.2.** If mobile app registers at the next ignition cycle (**not first**)
and SDL does NOT receive at least one UI and\or [VR or TTS] GetLanguage_response from HMI yet (SDL\`s watchdog timeout is NOT expired yet)
and UI and [VR or TTS] languages from RegisterAppInterface does NOT match to UI and [VR or TTS] languages stored at 'app_info.dat' file
SDL responds RegisterAppInterface (WRONG_LANGUAGE, success:true, `<stored_UI_languages>`, `<stored_VR_or_TTS_languages>`) to mobile app.


#### :eight: **Alternative flow - UNSUPPORTED_RESOURCE.**
**_Preconditions:_** application with appID is registered on SDL an RPC references a few components on HMI (UI and/or TTS and/or VR).    **_Steps:_** app->SDL: RPC(params)   
SDL->UI.RPC()   
SDL->VR.RPC()   
SDL->TTS.RPC()    
**_Observed:_** The one of the components returned UNSUPPORTED_RESOURCE:   
HMI->SDL: (UNSUPPORED_RESOURCE, info: "The issue was caused by..."):UI.RPC()   
HMI->SDL:SUCCESS: VR.RPC()   
HMI->SDL:SUCCESS: TTS.RPC()   
**_Expected:_** SDL->appID: (UNSUPPORTED_RESOURCE, success:true):RPC().


#### :nine: **Alternative flow - RESUME_FAILED.**
**_Preconditions:_** application with appID running on deviceID was disconnected by unexpected disconnect/IGN_Off less than 3 ignition cycles.   
**_Steps:_** app->SDL: RegisterAppInterface(appID, params) //hashID sent is NOT the same as stored for the pair `<appID, deviceID>` on SDL.   
**_Expected:_**   
1) SDL checks hashID obtained against of hashID stored for `<appID, deviceID>`
//NOT the same as the stored one for the pair `<appID, deviceID>` on SDL.  
2) SDL->appID: RESUME_FAILED:RegisterAppInterface().   
3) SDL->HMI: OnAppRegistered(params, resumeVrGrammars:false).   
4) SDL cleans up the persisted data stored fot pair `<appID, deviceID>`.


#### :keycap_ten: **Alternative flow - WARNINGS (RegisterAppInterface).**
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

#### :one::one:. **Alternative flow - APPLICATION_NOT_REGISTERED.**
11.1) If mobile app connects over protocol v1 and sends any RPC except RegisterAppInterface_request to SDL.
SDL responds APPLICATION_NOT_REGISTERED to this mobile app.

**_Preconditions:_** app connects over protocol v1   
**_Steps:_** app -> SDL: AddCommand (params).   
**_Expected:_** SDL -> app: AddCommand (APPLICATION_NOT_REGISTERED).

11.2) If an application sends a request before an application has been registered on SDL via RegisterAppInterface within the current session, SDL responds with resultCode "APPLICATION_NOT_REGISTERED" and success:"false" value.   
**_Preconditions:_**    
1) connection, session and service #7 are initialized for the application.   
2) the Request one of the defined in mobile API is intended to be sent from mobile applicaton with appID before RegisterAppInterface got on SDL.   
**_Steps:_** appID->SDL: any_RPC_except_RAI(parameters).    
**_Expected:_** SDL->appID: any_RPC_except_RAI (APPLICATION_NOT_REGISTERED, success:"false").


**_Preconditions:_**    
**_Steps:_**    
**_Expected:_**


**_Preconditions:_**    
**_Steps:_**    
**_Expected:_**


**_Preconditions:_**    
**_Steps:_**    
**_Expected:_**
