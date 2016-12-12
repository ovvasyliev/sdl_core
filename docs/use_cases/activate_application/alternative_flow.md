## Alternative flow
SDL is built with EXTERNAL_PROPRIETARY  
**User-consent "NO"**  
_**Pre-conditions:**_  
Application HMI Type – any  
app is registered and is present in HMI-list-of-registered-apps  
_**Steps:**_  
1. HMI->SDL: SDL.ActivateApp_request // the User chooses the app either from UI or by VR  
2. SDL->HMI: SDL.ActivateApp_response 
{isSDLAllowed: false, params}
// there is no record about whether the named device is allowed for sending PTU by the User/HU system  
3. HMI does NOT activate the app  
4. HMI->SDL: GetUserFriendlyMessage (messageCodes: "DataConsent")  
5. SDL->HMI: GetUserFriendlyMessage_response  
{messages: "tts": "To use mobile apps with SYNC, SYNC will communicate with Ford at least once per month using your mobile device's data plan. Standard rates may apply. SYNC will send your VIN and SYNC module number to Ford U.S. Please press yes or no, or help for more information. ", "line1": "Enable Mobile Apps", "line2": "on SYNC? (Uses Data)"}  
6. HMI: request for user consent for device from UI: displaying Yes/No buttons  
7. Press **'No'**  
_**Expected:**_  
1. HMI->SDL: OnAllowSDLFunctionality  
{allowed: false, params}  
2. SDL->app: OnPermissionChanged{params} ("pre_DataConsent" sub-section of "app_policies" section of PT)  
3. app`s HMI level corresponds to one from "default_hmi" field (it does not matter whether the app ID exists in local PT or does not exist)  
4. HMI displays the list of registered applications. App from step 1 is NOT activated.

**User-consent "YES"**  
_**Pre-conditions:**_  
SDL and HMI are running  
\<Device> is connected to SDL and consented by the User, \<App> is running on that device.  
\<App> is registered with SDL and is present in HMI list of registered aps.  
Local PT has permissions for \<App> that require User`s consent.  
_**Steps:**_  
1. Choose \<App> in the list of registered aps on HMI.  
2. HMI->SDL: SDL.ActivateApp
{appID}  
3. SDL->HMI: SDL.ActivateApp_response{isPermissionsConsentNeeded: true, params} //HMI does not activete the app  
4. HMI->SDL: GetUserFriendlyMessage{params},  
5. SDL->HMI: GetUserFriendlyMessage_response{params}  
6. HMI->SDL: GetListOfPermissions{appID}  
7. SDL->HMI: GetListOfPermissions_response{}  
8. HMI: display the 'app permissions consent' message.  
9. The User allows or disallows displayed permissions  
_**Expected:**_  
1. HMI->SDL: OnAppPermissionConsent  
2. PoliciesManager: update \<appID> subsection of "user_consent_records" subsection of \<device_identifier> section of "device_data" section in Local PT.


---

#### App activation during active phone call  
_**Pre-conditions:**_  
Application HMI Type: Media  
OnEventChanged(PHONE_CALL, isActive=true)  

_**Steps:**_  
HMI -> SDL.ActivateApp(\<appID_of_media_app\>) (or \<appID_of_navigation_app\>, \<appID_of_communication_app\>)  

_**Expected:**_  
SDL -> HMI: SDL.ActivateApp (SUCCESS)  
SDL -> app: OnHMIStatus ("HMILevel: FULL, audioStreamingState: NOT_AUDIBLE")  
_when phone call ends_  
SDL -> HMI: (PHONE_CALL, isActive=false)  
SDL -> app: OnHMIStatus ("HMILevel: FULL, audioStreamingState: AUDIBLE")

---

#### App activation during active embedded audio source  
_**Pre-conditions:**_  
Application HMI Type – **Media app  or Communication**  
App in HMILevel: BACKGROUND and audioStreamingState: NOT_AUDIBLE   
Audio source state is active on HMI  
_**Steps:**_  
HMI -> SDL: OnEventChanged (AUDIO_SOURCE, isActive=false)   
HMI -> SDL: SDL. ActivateApp  
_**Expected:**_  
SDL ->app: OnHMIStatus (HMILevel: FULL, audioStreamingState: AUDIBLE)

_**Pre-conditions:**_  
Application HMI Type – **Navigation app**  
Navigation app in HMILevel:LIMITED and audioStreamingState: AUDIBLE  
Audio source state is active on HMI  
"MixingAudioSupported" = **true** at .ini file [link to .ini file]  
_**Steps:**_  
HMI -> SDL.ActivateApp (\<appID_of_navigation_app\>)  
_**Expected:**_    
SDL ->app: OnHMIStatus (HMILevel: FULL, audioStreamingState: AUDIBLE)

:grey_exclamation: **options**  
plication HMI Type – **Navigation app**  
Navigation app in HMILevel:LIMITED and audioStreamingState: AUDIBLE  
Audio source state is active on HMI  
"MixingAudioSupported" = **false** at .ini file [link to .ini file]  
_**Steps:**_  
HMI -> SDL.ActivateApp (\<appID_of_navigation_app\>)  
_**Expected:**_  
SDL -> HMI: SDL. ActivateApp (SUCCESS)  
SDL -> app: OnHMIStatus (HMILevel: FULL, audioStreamingState: AUDIBLE)

_**Pre-conditions:**_  
Application HMI Type – **Non-media app**  
Non-media app in BACKGROUND and NOT_AUDIBLE due to **active embedded audio source or embedded navigation**  
_**Steps:**_  
HMI -> SDL.ActivateApp(\<appID_of_non-media_app\>)  
_**Expected:**_   
SDL -> HMI: SDL. ActivateApp (SUCCESS)  
SDL -> app: OnHMIStatus (HMILevel: FULL, audioStreamingState: NOT_AUDIBLE)

---

#### App activation during active embedded navigation source
_**Pre-conditions:**_  
Application HMI Type – **Media app or Communication app**  
Media app in HMILevel: LIMITED and audioStreamingState: AUDIBLE  
Navi source state is active on HMI  
_**Steps:**_  
HMI -> SDL: SDL. ActivateApp  
_**Expected:**_  
SDL -> HMI: SDL. ActivateApp (SUCCESS)  
SDL -> app: OnHMIStatus (HMILevel: FULL, audioStreamingState: AUDIBLE)  
:grey_exclamation: _note_ (embedded navigation is still active)

_**Pre-conditions:**_  
Application HMI Type – **Navigational app**  
Navigation app in BACKGROUND and NOT_AUDIBLE  
Navi source state is active on HMI  
_**Steps:**_  
HMI -> SDL: OnEventChanged (EMBEDDED_NAVI, isActive=false)  
HMI -> SDL.ActivateApp (\<appID_of_navigation_app\>)  
_**Expected:**_  
SDL -> HMI: SDL.ActivateApp (SUCCESS)  
SDL -> app: OnHMIStatus (FULL, AUDIBLE) 

_**Pre-conditions:**_  
Application HMI Type – **Non-media app**  
Non-media app in BACKGROUND and NOT_AUDIBLE due to **active embedded audio source or embedded navigation**  
_**Steps:**_  
HMI -> SDL.ActivateApp(\<appID_of_non-media_app\>)  
_**Expected:**_  
SDL -> HMI: SDL. ActivateApp (SUCCESS)  
SDL -> app: OnHMIStatus (HMILevel: FULL, audioStreamingState: NOT_AUDIBLE)

