**Detailed description**
HMI level of application varies according to Application HMI Type, policies, external environment and embedded sources.

_HMI Level_

| HMI Level Name        | Short description           |
| ------------- |:-------------:|
| FULL | An application is typically in Full when it is displayed in the HMI. In Full an application has access to the HMI supported resources, e.g. UI, VR, TTS, audio system,  etc.|
| LIMITED | Application can receive user input and can communicate to the user through the display, TTS, PerformInteraction, and audio streaming.|
| BACKGROUND | An application is typically in Background when it is not being displayed by the HMI.|
| NONE | When placed in None an application has no access to HMI supported resources.|

_AudioStreamingState_

| Value     | Short description           |
| ------------- |:-------------:|
| AUDIABLE|The app is in AUDIABLE when it is allowed to stream audio and audio may be heard by the user.|
|NOT_AUDIABLE|The app is in NOT_AUDIABLE when it is not allowed to stream audio and audio may not be heard by the user.|
|ATTENAUTED|The app is in ATTENAUTED when it is allowed to stream audio, volume of sound is reduced to inject another prompt or system event audio over it (e.g. a navigation prompt).|

_SystemContext_

| Value     | Short description           |
| ------------- |:-------------:|
|MAIN|The app's persistent display (whether media/non-media/navigation) is fully visible onscreen.|
|VRSESSION|The system is currently in a VR session (with whatever dedicated VR screen being overlaid onscreen).|
|MENU|The system is currently displaying an in-App menu onscreen.|
|HMI_OBSCURED|The app's display HMI is currently being obscured by either a system or other app's overlay.|
|ALERT|Broadcast only to whichever app has an alert currently being displayed.|

## **Main Flow**
SDL must allow to activate app from any HMILevel
**Pre-conditions:**
Application HMI Type: any 
app_1 successfully registers on SDL [link on Register app requirement]
app_1 in other-than-NULL policies
**Steps**
HMI -> SDL: SDL.ActivateApp (appID_1)
**Expected**
SDL -> HMI: SDL.ActivateApp (SUCCESS)
SDL -> app_1: OnHMIStatus maximum possible HMILevel
